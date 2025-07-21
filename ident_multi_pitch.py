import os
import simulator
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error, mean_absolute_error
from scipy.optimize import minimize
import csv
from pymoo.core.problem import Problem
from pymoo.algorithms.moo.nsga2 import NSGA2
from pymoo.optimize import minimize as pymoo_minimize
from pymoo.termination import get_termination
from pymoo.visualization.scatter import Scatter


def read_csv_and_adjust_time(file_path):
    # Read the CSV file
    data = pd.read_csv(file_path)

    # Adjust the time vector to start from zero
    if 'time' in data.columns:
        data['time'] = data['time'] - data['time'].iloc[0]

    # Interpolate to handle NaN values
    data = data.interpolate(method='linear', limit_direction='forward', axis=0)
    data = data.fillna(method='bfill').fillna(method='ffill')

    return data

def objective_function(params_values, sim, data):
    # Update the parameters in the simulator
    params = sim.get_params()
    params.pitch_K = params_values[0]
    params.pitch_omega = params_values[1]
    params.pitch_zeta = params_values[2]
    params.pitch_max = params_values[3]
    params.Cx = params_values[4]  # Adicionando o parâmetro Cx
    sim.set_params(params)

    # Initialize and run the simulator
    sim.initialize()
    sim.run_input_vector_based(upitch=data['u_control/ux'].tolist())

    # Get the simulated data
    output = sim.get_rtY_vector()
    simulationdata = {}
    simulationdata['dx_mps'] = [output_item.dx_mps for output_item in output]
    simulationdata['pitch'] = [output_item.pitch_rad for output_item in output]
    simulationdata['x_m'] = [output_item.x_m for output_item in output]

    # Ensure that the lengths of the data match
    min_len = min(len(data['filtered_pose/pitch']), len(simulationdata['pitch']))
    
    exp_pitch = data['filtered_pose/pitch'][:min_len]
    sim_pitch = simulationdata['pitch'][:min_len]
    
    exp_vxb = data['filtered_pose/vxb'][:min_len]
    sim_vxb = simulationdata['dx_mps'][:min_len]

    exp_xb = (data['filtered_pose/xb'] - data['filtered_pose/xb'].iloc[0])[:min_len]
    sim_xb = simulationdata['x_m'][:min_len]

    # Calculate the MSE between the curves
    mse_pitch = mean_squared_error(exp_pitch, sim_pitch)
    mse_vxb = mean_squared_error(exp_vxb, sim_vxb)
    
    return [mse_pitch, mse_vxb]

class MultiObjectiveProblem(Problem):
    def __init__(self, sim, data):
        super().__init__(n_var=5,
                         n_obj=2,
                         n_constr=0,
                         xl=np.array([0.01, 0.01, 0.01, 0.01, 0.01]),
                         xu=np.array([10.0, 10.0, 1.0, 10.0, 10.0]))
        self.sim = sim
        self.data = data

    def _evaluate(self, x, out, *args, **kwargs):
        out["F"] = np.array([objective_function(params_values, self.sim, self.data) for params_values in x])

def optimize_parameters_nsga2(sim, data):
    problem = MultiObjectiveProblem(sim, data)
    
    algorithm = NSGA2(pop_size=300)

    termination = get_termination("n_gen", 100)

    # Workaround: Save only objectives history manually
    history_F = []
    def callback(algorithm):
        if hasattr(algorithm, 'pop'):
            F = algorithm.pop.get('F')
            if F is not None:
                history_F.append(np.copy(F))

    res = pymoo_minimize(problem,
                       algorithm,
                       termination,
                       seed=1,
                       save_history=False,
                       verbose=True,
                       callback=callback)

    res.history_F = history_F
    return res, problem
def plot_nsga2_analysis(result_nsga, problem, history=None, param_names=None, results_dir="results"):
    # --- Plot all Pareto fronts (only Pareto points) for all generations in a single plot ---
    from pymoo.util.nds.non_dominated_sorting import NonDominatedSorting
    if hasattr(result_nsga, 'history_F') and result_nsga.history_F is not None and len(result_nsga.history_F) > 0:
        history_F = result_nsga.history_F
        # Individual plots per generation (keep this if you want both)
        pareto_dir = os.path.join(results_dir, "pareto_fronts_per_generation")
        os.makedirs(pareto_dir, exist_ok=True)
        for gen, Fgen in enumerate(history_F):
            Fgen = np.atleast_2d(Fgen)
            if Fgen.shape[1] < 2:
                continue  # Only plot for multi-objective
            nds = NonDominatedSorting()
            fronts = nds.do(Fgen, only_non_dominated_front=True)
            pareto_F = Fgen[fronts]
            plt.figure(figsize=(6, 5))
            plt.scatter(Fgen[:, 0], Fgen[:, 1], c='lightgray', label='Population')
            plt.scatter(pareto_F[:, 0], pareto_F[:, 1], c='red', label='Pareto Front')
            plt.xlabel('Objective 1')
            plt.ylabel('Objective 2')
            plt.title(f'Pareto Front - Generation {gen+1}')
            plt.legend()
            plt.tight_layout()
            plt.savefig(os.path.join(pareto_dir, f"pareto_front_gen_{gen+1}.png"))
            plt.close()

        # --- Generate GIF of Pareto front evolution ---
        try:
            import imageio
            image_files = sorted([f for f in os.listdir(pareto_dir) if f.endswith('.png')],
                                 key=lambda x: int(x.split('_')[-1].split('.')[0]))
            images = []
            for filename in image_files:
                file_path = os.path.join(pareto_dir, filename)
                images.append(imageio.imread(file_path))
            gif_path = os.path.join(results_dir, "pareto_evolution.gif")
            imageio.mimsave(gif_path, images, duration=0.3)
            print(f"GIF saved at: {gif_path}")
        except ImportError:
            print("imageio is not installed. Install it with 'pip install imageio' to generate the GIF.")

        # --- Generate GIF of Pareto front individuals only ---
        pareto_only_dir = os.path.join(results_dir, "pareto_fronts_only_per_generation")
        os.makedirs(pareto_only_dir, exist_ok=True)
        pareto_only_pngs = []
        for gen, Fgen in enumerate(history_F):
            Fgen = np.atleast_2d(Fgen)
            if Fgen.shape[1] < 2:
                continue
            nds = NonDominatedSorting()
            fronts = nds.do(Fgen, only_non_dominated_front=True)
            pareto_F = Fgen[fronts]
            plt.figure(figsize=(6, 5))
            plt.scatter(pareto_F[:, 0], pareto_F[:, 1], c='red', label='Pareto Front')
            plt.xlabel('Objective 1')
            plt.ylabel('Objective 2')
            plt.title(f'Pareto Front Only - Generation {gen+1}')
            plt.legend()
            plt.tight_layout()
            png_path = os.path.join(pareto_only_dir, f"pareto_only_gen_{gen+1}.png")
            plt.savefig(png_path)
            plt.close()
            pareto_only_pngs.append(png_path)
        # Create GIF from Pareto-only PNGs
        try:
            import imageio
            images = [imageio.imread(png) for png in pareto_only_pngs]
            gif_path = os.path.join(results_dir, "pareto_only_evolution.gif")
            imageio.mimsave(gif_path, images, duration=0.3)
            print(f"Pareto-only GIF saved at: {gif_path}")
        except ImportError:
            print("imageio is not installed. Install it with 'pip install imageio' to generate the Pareto-only GIF.")
    # --- Plot all Pareto fronts (only Pareto points) for all generations in a single plot ---
    from pymoo.util.nds.non_dominated_sorting import NonDominatedSorting
    if hasattr(result_nsga, 'history_F') and result_nsga.history_F is not None and len(result_nsga.history_F) > 0:
        history_F = result_nsga.history_F
        # Individual plots per generation (keep this if you want both)
        pareto_dir = os.path.join(results_dir, "pareto_fronts_per_generation")
        os.makedirs(pareto_dir, exist_ok=True)
        for gen, Fgen in enumerate(history_F):
            Fgen = np.atleast_2d(Fgen)
            if Fgen.shape[1] < 2:
                continue  # Only plot for multi-objective
            nds = NonDominatedSorting()
            fronts = nds.do(Fgen, only_non_dominated_front=True)
            pareto_F = Fgen[fronts]
            plt.figure(figsize=(6, 5))
            plt.scatter(Fgen[:, 0], Fgen[:, 1], c='lightgray', label='Population')
            plt.scatter(pareto_F[:, 0], pareto_F[:, 1], c='red', label='Pareto Front')
            plt.xlabel('Objective 1')
            plt.ylabel('Objective 2')
            plt.title(f'Pareto Front - Generation {gen+1}')
            plt.legend()
            plt.tight_layout()
            plt.savefig(os.path.join(pareto_dir, f"pareto_front_gen_{gen+1}.png"))
            plt.close()

        # Combined plot: all Pareto fronts in one figure with colorbar and normalized axes
        import matplotlib as mpl
        fig, ax = plt.subplots(figsize=(8, 6))
        cmap = plt.get_cmap('viridis')
        norm = mpl.colors.Normalize(vmin=0, vmax=len(history_F)-1)
        all_pareto = []
        for gen, Fgen in enumerate(history_F):
            Fgen = np.atleast_2d(Fgen)
            if Fgen.shape[1] < 2:
                continue
            nds = NonDominatedSorting()
            fronts = nds.do(Fgen, only_non_dominated_front=True)
            pareto_F = Fgen[fronts]
            all_pareto.append(pareto_F)
        # Stack all Pareto points to normalize
        if all_pareto:
            all_pareto_concat = np.vstack(all_pareto)
            min_vals = np.min(all_pareto_concat, axis=0)
            max_vals = np.max(all_pareto_concat, axis=0)
            # Avoid division by zero
            range_vals = np.where(max_vals - min_vals == 0, 1, max_vals - min_vals)
        else:
            min_vals = np.zeros(2)
            range_vals = np.ones(2)
        for gen, pareto_F in enumerate(all_pareto):
            normed = (pareto_F - min_vals) / range_vals
            ax.scatter(normed[:, 0], normed[:, 1], color=cmap(norm(gen)), s=20, alpha=0.7)
        sm = mpl.cm.ScalarMappable(cmap=cmap, norm=norm)
        sm.set_array([])
        cbar = fig.colorbar(sm, ax=ax, ticks=[0, len(history_F)-1])
        cbar.ax.set_yticklabels(['Gen 1', f'Gen {len(history_F)}'])
        ax.set_xlabel('Objective 1 (normalized)')
        ax.set_ylabel('Objective 2 (normalized)')
        ax.set_title('Pareto Fronts per Generation (Normalized)')
        ax.set_xlim(0, 0.05)
        ax.set_ylim(0, 0.05)
        fig.tight_layout()
        fig.savefig(os.path.join(results_dir, "all_pareto_fronts_generations.png"))
        plt.close(fig)
    # --- Save and plot objectives history (if available) ---
    if hasattr(result_nsga, 'history_F') and result_nsga.history_F is not None and len(result_nsga.history_F) > 0:
        history_F = result_nsga.history_F
        # Save objectives history as CSV
        history_csv_path = os.path.join(results_dir, "objectives_history.csv")
        with open(history_csv_path, "w", newline="") as f:
            writer = csv.writer(f)
            n_obj = result_nsga.F.shape[1] if len(result_nsga.F.shape) > 1 else 1
            writer.writerow(["Generation"] + [f"Objective_{i+1}" for i in range(n_obj)])
            for gen, Fgen in enumerate(history_F):
                Fgen = np.atleast_2d(Fgen)
                for row in Fgen:
                    writer.writerow([gen+1] + list(row))

        # Plot convergence of objectives over generations (best value per generation only)
        best_per_gen = []
        for Fgen in history_F:
            Fgen = np.atleast_2d(Fgen)
            best_per_gen.append(np.min(Fgen, axis=0))
        best_per_gen = np.array(best_per_gen)
        plt.figure(figsize=(8, 5))
        generations = np.arange(1, best_per_gen.shape[0]+1)
        for i in range(best_per_gen.shape[1]):
            plt.plot(generations, best_per_gen[:, i], label=f'Objective {i+1}')
        plt.xlabel('Generation')
        plt.ylabel('Best Objective Value')
        plt.title('Convergence of Best Objective Value per Generation')
        plt.legend()
        plt.tight_layout()
        plt.savefig(os.path.join(results_dir, "objectives_convergence_history.png"))
        plt.close()
    # --- Diversity Metrics: Spread (Δ) and Spacing ---
    def calc_spread(F):
        # Only for 2 or more objectives and at least 2 points
        if F.shape[0] < 2:
            return np.nan
        F_sorted = F[np.argsort(F[:, 0])]
        d_f = np.linalg.norm(F_sorted[0] - F_sorted[-1])
        d = np.linalg.norm(np.diff(F_sorted, axis=0), axis=1)
        d_bar = np.mean(d)
        delta = (d_f + np.sum(np.abs(d - d_bar))) / (d_f + (F.shape[0] - 1) * d_bar)
        return delta

    def calc_spacing(F):
        # Only for 2 or more points
        if F.shape[0] < 2:
            return np.nan
        d = np.linalg.norm(np.diff(np.sort(F, axis=0), axis=0), axis=1)
        d_bar = np.mean(d)
        spacing = np.sqrt(np.sum((d - d_bar) ** 2) / (len(d)))
        return spacing

    # Calculate and print diversity metrics if multi-objective
    F_metrics = np.array(result_nsga.F)
    if F_metrics.ndim == 1:
        F_metrics = F_metrics.reshape(-1, 1)
    diversity_txt_path = os.path.join(results_dir, "diversity_metrics.txt")
    with open(diversity_txt_path, "w", encoding="utf-8") as f:
        if F_metrics.shape[1] > 1 and F_metrics.shape[0] > 1:
            spread = calc_spread(F_metrics)
            spacing = calc_spacing(F_metrics)
            msg1 = f"Spread (Δ) of Pareto front: {spread:.4f}\n"
            msg2 = f"Spacing of Pareto front: {spacing:.4f}\n"
            print(msg1.strip())
            print(msg2.strip())
            f.write(msg1)
            f.write(msg2)
        else:
            msg = "Spread (Δ) and Spacing metrics require at least 2 objectives and 2 solutions.\n"
            print(msg.strip())
            f.write(msg)
    """
    Generates and saves NSGA-II analysis plots in the results folder.
    - Pareto Front
    - Objectives Convergence
    - Boxplot of parameters of non-dominated solutions
    - (Optional) Pareto front history
    """
    os.makedirs(results_dir, exist_ok=True)

    # 1. Pareto Front
    pareto_fig = Scatter()
    try:
        pf = problem.pareto_front()
        if pf is not None:
            pareto_fig.add(pf, plot_type="line", color="black", alpha=0.7)
    except Exception:
        pass
    pareto_fig.add(result_nsga.F, facecolor="none", edgecolor="red")
    pareto_fig.save(os.path.join(results_dir, "pareto_front.png"))
    plt.close()

    # 2. Objectives Convergence
    if hasattr(result_nsga, 'opt') and hasattr(result_nsga.opt, 'get'):
        F = result_nsga.opt.get("F")
    else:
        F = result_nsga.F
    if F is not None:
        F = np.array(F)
        fig, ax = plt.subplots()
        for i in range(F.shape[1]):
            ax.plot(np.sort(F[:, i]), label=f'Objective {i+1}')
        ax.set_title('Objectives Convergence (lowest values)')
        ax.set_xlabel('Ordered solutions')
        ax.set_ylabel('Objective value')
        ax.legend()
        plt.tight_layout()
        plt.savefig(os.path.join(results_dir, "objectives_convergence.png"))
        plt.close()

    # 3. Boxplot of parameters of non-dominated solutions
    if hasattr(result_nsga, 'X'):
        X = np.array(result_nsga.X)
        fig, ax = plt.subplots()
        ax.boxplot(X, vert=True, patch_artist=True)
        if param_names is not None:
            ax.set_xticklabels(param_names, rotation=30)
        else:
            ax.set_xticklabels([f'param_{i+1}' for i in range(X.shape[1])], rotation=30)
        ax.set_title('Boxplot of Parameters (Non-dominated Solutions)')
        plt.tight_layout()
        plt.savefig(os.path.join(results_dir, "boxplot_parameters.png"))
        plt.close()

    # 4. Pareto front history (if provided)
    if history is not None:
        for i, hist in enumerate(history):
            fig = Scatter()
            try:
                F_hist = hist.opt.get("F")
                fig.add(F_hist, facecolor="none", edgecolor="blue")
                fig.title(f"Pareto Front - Generation {i+1}")
                fig.save(os.path.join(results_dir, f"pareto_front_gen_{i+1}.png"))
                plt.close()
            except Exception:
                continue

if __name__ == "__main__":

    experiments = [
        ("experiments/ExpX_senoide_id1.csv", "Sine id 1"),
        ("experiments/ExpX_senoide_id2.csv", "Sine id 2"),
        ("experiments/ExpX_senoide_id3.csv", "Sine id 3"),
        ("experiments/ExpTodos_manual_x.csv", "Manual Input")
    ]
    file_path = "experiments/ExpX_senoide_id1.csv" 
    results_path = "results/ExpX"
    os.makedirs(results_path, exist_ok=True)
    data = read_csv_and_adjust_time(file_path)
    # Normalize the initial position once
    data['filtered_pose/xb'] = data['filtered_pose/xb'] - data['filtered_pose/xb'].iloc[0]
    print(data)

    sim = simulator.Simulator()
    sim.initialize()
    sim.run_input_vector_based(upitch=data['u_control/ux'].tolist())
    output = sim.get_rtY_vector()
    simdata = {}
    simdata['dx_mps'] = [output_item.dx_mps for output_item in output]
    simdata['x_m'] = [output_item.x_m for output_item in output]
    simdata['pitch'] = [output_item.pitch_rad for output_item in output]

    print("Pre-optimization MSE velocity:", mean_squared_error(data['filtered_pose/vxb'], simdata['dx_mps']))
    print("Pre-optimization MSE pitch:", mean_squared_error(data['filtered_pose/pitch'], simdata['pitch']))

    # Parameter optimization with NSGA-II
    result_nsga, problem = optimize_parameters_nsga2(sim, data)

    print("Multi-objective Optimization Results (Pareto Front):")
    print("Parameters (X):", result_nsga.X)
    print("Objectives (F):", result_nsga.F)

    # ...existing code...

    # Choose the best compromise solution (smallest Euclidean distance from the origin)
    best_index = np.argmin(np.linalg.norm(result_nsga.F, axis=1))
    best_params = result_nsga.X[best_index]
    best_objectives = result_nsga.F[best_index]

    print("\nBest Selected Parameters:", best_params)
    print("Best Objectives (MSEs):", best_objectives)

    sim_optimized = simulator.Simulator()
    params = sim_optimized.get_params()
    params.pitch_K = best_params[0]
    params.pitch_omega = best_params[1]
    params.pitch_zeta = best_params[2]
    params.pitch_max = best_params[3]
    params.Cx = best_params[4]
    sim_optimized.set_params(params)
    sim_optimized.initialize()
    sim_optimized.run_input_vector_based(upitch=data['u_control/ux'].tolist())
    output_oti = sim_optimized.get_rtY_vector()
    simOptimized = {}
    simOptimized['dx_mps'] = [output_item.dx_mps for output_item in output_oti]
    simOptimized['x_m'] = [output_item.x_m for output_item in output_oti]
    simOptimized['pitch'] = [output_item.pitch_rad for output_item in output_oti]


    # Creating subplots for pitch, dx_mps, and x_m
    fig, axs = plt.subplots(4, 1, figsize=(10, 8))

    # Plot for u_theta
    axs[0].plot(data['time'], data['u_control/ux'], label='Sine id 1')
    axs[0].set_title('u_theta')
    axs[0].set_xlabel('Time (s)')
    axs[0].set_ylabel('u_theta')
    axs[0].legend(loc='upper right')

    # Plot for pitch
    axs[1].plot(data['time'], data['filtered_pose/pitch'], label='Experimental Pitch')
    axs[1].plot(data['time'], simOptimized['pitch'], label='Optimized Pitch', linestyle='--')
    axs[1].plot(data['time'], simdata['pitch'], label='Unoptimized Pitch', linestyle=':')
    axs[1].set_title('Pitch')
    axs[1].set_xlabel('Time (s)')
    axs[1].set_ylabel('Pitch (rad)')
    axs[1].legend(loc='upper right')

    # Plot for dx_mps
    axs[2].plot(data['time'], data['filtered_pose/vxb'], label='Experimental dx_mps')
    axs[2].plot(data['time'], simOptimized['dx_mps'], label='Optimized dx_mps', linestyle='--')
    axs[2].plot(data['time'], simdata['dx_mps'], label='Unoptimized dx_mps', linestyle=':')
    axs[2].set_title('dx_mps')
    axs[2].set_xlabel('Time (s)')
    axs[2].set_ylabel('dx_mps (m/s)')
    axs[2].legend(loc='upper right')

    # Plot for x_m
    data['filtered_pose/xb'] = data['filtered_pose/xb'] - data['filtered_pose/xb'].iloc[0]
    axs[3].plot(data['time'], data['filtered_pose/xb'], label='Experimental x_m')
    axs[3].plot(data['time'], simOptimized['x_m'], label='Optimized x_m', linestyle='--')
    axs[3].plot(data['time'], simdata['x_m'], label='Unoptimized x_m', linestyle=':')
    axs[3].set_title('x_m')
    axs[3].set_xlabel('Time (s)')
    axs[3].set_ylabel('x_m (m)')
    axs[3].legend(loc='upper right')



    # Add a general title for all subplots
    fig.suptitle('Experiment used for optimization', fontsize=16)

    # Adjust layout and save the figure
    plt.tight_layout()
    plt.savefig(results_path + "/optimization_experiment.png")
    plt.close()

    # NSGA-II analysis plots
    param_names = ["pitch_K", "pitch_omega", "pitch_zeta", "pitch_max", "Cx"]
    plot_nsga2_analysis(result_nsga, problem, param_names=param_names,results_dir=results_path)

    # Accumulate MSE results for all sines and manual
    mse_results_all = {}

    for file_path, label in experiments:
        data = read_csv_and_adjust_time(file_path)
        data['filtered_pose/xb'] = data['filtered_pose/xb'] - data['filtered_pose/xb'].iloc[0]

        sim_optimized = simulator.Simulator()
        params = sim_optimized.get_params()
        params.pitch_K = best_params[0]
        params.pitch_omega = best_params[1]
        params.pitch_zeta = best_params[2]
        params.pitch_max = best_params[3]
        params.Cx = best_params[4]
        sim_optimized.set_params(params)
        sim_optimized.initialize()
        sim_optimized.run_input_vector_based(upitch=data['u_control/ux'].tolist())
        output_oti = sim_optimized.get_rtY_vector()
        simOptimized = {
            'dx_mps': [output_item.dx_mps for output_item in output_oti],
            'x_m': [output_item.x_m for output_item in output_oti],
            'pitch': [output_item.pitch_rad for output_item in output_oti]
        }

        # Calculate MSE for this experiment
        mse_results_all[label] = {
            "Pitch": mean_squared_error(data['filtered_pose/pitch'], simOptimized['pitch']),
            "dx_mps": mean_squared_error(data['filtered_pose/vxb'], simOptimized['dx_mps']),
            "x_m": mean_squared_error(data['filtered_pose/xb'], simOptimized['x_m'])
        }

        # Create subplots for pitch, dx_mps, and x_m
        fig, axs = plt.subplots(4, 1, figsize=(10, 8))

        # Plot for u_theta
        axs[0].plot(data['time'], data['u_control/ux'], label=label)
        axs[0].set_title('u_theta')
        axs[0].set_xlabel('Time (s)')
        axs[0].set_ylabel('u_theta')
        axs[0].legend(loc='upper right')

        # Plot for pitch
        axs[1].plot(data['time'], data['filtered_pose/pitch'], label='Experimental Pitch')
        axs[1].plot(data['time'], simOptimized['pitch'], label='Optimized Pitch', linestyle='--')
        axs[1].set_title('Pitch')
        axs[1].set_xlabel('Time (s)')
        axs[1].set_ylabel('Pitch (rad)')
        axs[1].legend(loc='upper right')

        # Plot for dx_mps
        axs[2].plot(data['time'], data['filtered_pose/vxb'], label='Experimental dx_mps')
        axs[2].plot(data['time'], simOptimized['dx_mps'], label='Optimized dx_mps', linestyle='--')
        axs[2].set_title('dx_mps')
        axs[2].set_xlabel('Time (s)')
        axs[2].set_ylabel('dx_mps (m/s)')
        axs[2].legend(loc='upper right')

        # Plot for x_m
        axs[3].plot(data['time'], data['filtered_pose/xb'], label='Experimental x_m')
        axs[3].plot(data['time'], simOptimized['x_m'], label='Optimized x_m', linestyle='--')
        axs[3].set_title('x_m')
        axs[3].set_xlabel('Time (s)')
        axs[3].set_ylabel('x_m (m)')
        axs[3].legend(loc='upper right')


        # Add a general title for all subplots
        fig.suptitle(f'Optimization comparison for {label}', fontsize=16)

        # Adjust layout
        plt.tight_layout()

        # Save the figure
        plt.savefig(f"{results_path}/{label.replace(' ', '_')}.png")
        plt.close()

    # Display the MSE results table for all experiments
    print("MSE Results Table for all experiments:")
    for experiment, mse_values in mse_results_all.items():
        print(f"\n{experiment}:")
        for key, value in mse_values.items():
            print(f"  {key}: {value:.4f}")

    # Save the MSE results to a CSV file
    output_csv_path = f"{results_path}/mse_results.csv"

    with open(output_csv_path, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Experiment", "Pitch", "dx_mps", "x_m"])

        for experiment, mse_values in mse_results_all.items():
            writer.writerow([experiment, mse_values["Pitch"], mse_values["dx_mps"], mse_values["x_m"]])

    print(f"MSE results saved at: {output_csv_path}")