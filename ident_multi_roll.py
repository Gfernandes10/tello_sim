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
    params.roll_K = params_values[0]
    params.roll_omega = params_values[1]
    params.roll_zeta = params_values[2]
    params.roll_max = params_values[3]
    params.Cy = params_values[4]  # Adicionando o parâmetro Cx
    sim.set_params(params)

    # Initialize and run the simulator
    sim.initialize()
    sim.run_input_vector_based([], uroll=data['u_control/uy'].tolist())

    # Get the simulated data
    output = sim.get_rtY_vector()
    simulationdata = {}
    simulationdata['dy_mps'] = [output_item.dy_mps for output_item in output]
    simulationdata['roll'] = [output_item.roll_rad for output_item in output]
    simulationdata['x_m'] = [output_item.x_m for output_item in output]

    # Ensure that the lengths of the data match
    min_len = min(len(data['filtered_pose/roll']), len(simulationdata['roll']))

    exp_roll = data['filtered_pose/roll'][:min_len]
    sim_roll = simulationdata['roll'][:min_len]

    exp_vyb = data['filtered_pose/vyb'][:min_len]
    sim_vyb = simulationdata['dy_mps'][:min_len]

    # Calculate the MSE between the curves
    mse_roll = mean_squared_error(exp_roll, sim_roll)
    mse_vyb = mean_squared_error(exp_vyb, sim_vyb)

    return [mse_roll, mse_vyb]

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
    
    algorithm = NSGA2(pop_size=200)

    termination = get_termination("n_gen", 50)

    res = pymoo_minimize(problem,
                       algorithm,
                       termination,
                       seed=1,
                       save_history=False,
                       verbose=True)

    return res, problem
def plot_nsga2_analysis(result_nsga, problem, history=None, param_names=None, results_dir="results"):
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
        ("experiments/ExpY1_senoide_id1.csv", "Sine id 1"),
        ("experiments/ExpY1_senoide_id2.csv", "Sine id 2"),
        ("experiments/ExpY2_senoide_id3.csv", "Sine id 3"),
        ("experiments/ExpTodos_manual_y.csv", "Manual Input")
    ]
    file_path = "experiments/ExpY1_senoide_id1.csv" 
    results_path = "results/ExpY"
    os.makedirs(results_path, exist_ok=True)
    data = read_csv_and_adjust_time(file_path)
    # Normalize the initial position once
    data['filtered_pose/yb'] = data['filtered_pose/yb'] - data['filtered_pose/yb'].iloc[0]
    print(data)

    sim = simulator.Simulator()
    sim.initialize()
    sim.run_input_vector_based([], uroll=data['u_control/uy'].tolist())
    output = sim.get_rtY_vector()
    simdata = {}
    simdata['dy_mps'] = [output_item.dy_mps for output_item in output]
    simdata['y_m'] = [output_item.y_m for output_item in output]
    simdata['roll'] = [output_item.roll_rad for output_item in output]

    print("Pre-optimization MSE velocity:", mean_squared_error(data['filtered_pose/vyb'], simdata['dy_mps']))
    print("Pre-optimization MSE roll:", mean_squared_error(data['filtered_pose/roll'], simdata['roll']))

    # Parameter optimization with NSGA-II
    result_nsga, problem = optimize_parameters_nsga2(sim, data)
    
    print("Multi-objective Optimization Results (Pareto Front):")
    print("Parameters (X):", result_nsga.X)
    print("Objectives (F):", result_nsga.F)

    # Choose the best compromise solution (smallest Euclidean distance from the origin)
    best_index = np.argmin(np.linalg.norm(result_nsga.F, axis=1))
    best_params = result_nsga.X[best_index]
    best_objectives = result_nsga.F[best_index]

    print("\nBest Selected Parameters:", best_params)
    print("Best Objectives (MSEs):", best_objectives)

    sim_optimized = simulator.Simulator()
    params = sim_optimized.get_params()
    params.roll_K = best_params[0]
    params.roll_omega = best_params[1]
    params.roll_zeta = best_params[2]
    params.roll_max = best_params[3]
    params.Cy = best_params[4]
    sim_optimized.set_params(params)
    sim_optimized.initialize()
    sim_optimized.run_input_vector_based([], uroll=data['u_control/uy'].tolist())
    output_oti = sim_optimized.get_rtY_vector()
    simOptimized = {}
    simOptimized['dy_mps'] = [output_item.dy_mps for output_item in output_oti]
    simOptimized['y_m'] = [output_item.y_m for output_item in output_oti]
    simOptimized['roll'] = [output_item.roll_rad for output_item in output_oti]


    # Creating subplots for roll, dy_mps, and y_m
    fig, axs = plt.subplots(4, 1, figsize=(10, 8))

    # Plot for u_roll
    axs[0].plot(data['time'], data['u_control/uy'], label='Sine id 1')
    axs[0].set_title('u_roll')
    axs[0].set_xlabel('Time (s)')
    axs[0].set_ylabel('u_roll')
    axs[0].legend(loc='upper right')

    # Plot for roll
    axs[1].plot(data['time'], data['filtered_pose/roll'], label='Experimental Roll')
    axs[1].plot(data['time'], simOptimized['roll'], label='Optimized Roll', linestyle='--')
    axs[1].plot(data['time'], simdata['roll'], label='Unoptimized Roll', linestyle=':')
    axs[1].set_title('Roll')
    axs[1].set_xlabel('Time (s)')
    axs[1].set_ylabel('Roll (rad)')
    axs[1].legend(loc='upper right')

    # Plot for dy_mps
    axs[2].plot(data['time'], data['filtered_pose/vyb'], label='Experimental dy_mps')
    axs[2].plot(data['time'], simOptimized['dy_mps'], label='Optimized dy_mps', linestyle='--')
    axs[2].plot(data['time'], simdata['dy_mps'], label='Unoptimized dy_mps', linestyle=':')
    axs[2].set_title('dy_mps')
    axs[2].set_xlabel('Time (s)')
    axs[2].set_ylabel('dy_mps (m/s)')
    axs[2].legend(loc='upper right')

    # Plot for x_m
    data['filtered_pose/yb'] = data['filtered_pose/yb'] - data['filtered_pose/yb'].iloc[0]
    axs[3].plot(data['time'], data['filtered_pose/yb'], label='Experimental y_m')
    axs[3].plot(data['time'], simOptimized['y_m'], label='Optimized y_m', linestyle='--')
    axs[3].plot(data['time'], simdata['y_m'], label='Unoptimized y_m', linestyle=':')
    axs[3].set_title('y_m')
    axs[3].set_xlabel('Time (s)')
    axs[3].set_ylabel('y_m (m)')
    axs[3].legend(loc='upper right')



    # Add a general title for all subplots
    fig.suptitle('Experiment used for optimization', fontsize=16)

    # Adjust layout and save the figure
    plt.tight_layout()
    plt.savefig(results_path + "/optimization_experiment.png")
    plt.close()

    # NSGA-II analysis plots
    param_names = ["roll_K", "roll_omega", "roll_zeta", "roll_max", "Cy"]
    plot_nsga2_analysis(result_nsga, problem, param_names=param_names,results_dir=results_path)

    # Accumulate MSE results for all sines and manual
    mse_results_all = {}

    for file_path, label in experiments:
        data = read_csv_and_adjust_time(file_path)
        data['filtered_pose/y'] = data['filtered_pose/y'] - data['filtered_pose/y'].iloc[0]

        sim_optimized = simulator.Simulator()
        params = sim_optimized.get_params()
        params.roll_K = best_params[0]
        params.roll_omega = best_params[1]
        params.roll_zeta = best_params[2]
        params.roll_max = best_params[3]
        params.Cy = best_params[4]
        sim_optimized.set_params(params)
        sim_optimized.initialize()
        sim_optimized.run_input_vector_based([], uroll=data['u_control/uy'].tolist())
        output_oti = sim_optimized.get_rtY_vector()
        simOptimized = {
            'dy_mps': [output_item.dy_mps for output_item in output_oti],
            'y_m': [output_item.y_m for output_item in output_oti],
            'roll': [output_item.roll_rad for output_item in output_oti]
        }

        # Calculate MSE for this experiment
        mse_results_all[label] = {
            "Roll": mean_squared_error(data['filtered_pose/roll'], simOptimized['roll']),
            "dy_mps": mean_squared_error(data['filtered_pose/vyb'], simOptimized['dy_mps']),
            "y_m": mean_squared_error(data['filtered_pose/y'], simOptimized['y_m'])
        }

        # Create subplots for roll, dy_mps, and y_m
        fig, axs = plt.subplots(4, 1, figsize=(10, 8))

        # Plot for u_roll
        axs[0].plot(data['time'], data['u_control/uy'], label=label)
        axs[0].set_title('u_roll')
        axs[0].set_xlabel('Time (s)')
        axs[0].set_ylabel('u_roll')
        axs[0].legend(loc='upper right')

        # Plot for roll
        axs[1].plot(data['time'], data['filtered_pose/roll'], label='Experimental Roll')
        axs[1].plot(data['time'], simOptimized['roll'], label='Optimized Roll', linestyle='--')
        axs[1].set_title('Roll')
        axs[1].set_xlabel('Time (s)')
        axs[1].set_ylabel('Roll (rad)')
        axs[1].legend(loc='upper right')

        # Plot for dy_mps
        axs[2].plot(data['time'], data['filtered_pose/vyb'], label='Experimental dy_mps')
        axs[2].plot(data['time'], simOptimized['dy_mps'], label='Optimized dy_mps', linestyle='--')
        axs[2].set_title('dy_mps')
        axs[2].set_xlabel('Time (s)')
        axs[2].set_ylabel('dy_mps (m/s)')
        axs[2].legend(loc='upper right')

        # Plot for y_m
        axs[3].plot(data['time'], data['filtered_pose/yb'], label='Experimental y_m')
        axs[3].plot(data['time'], simOptimized['y_m'], label='Optimized y_m', linestyle='--')
        axs[3].set_title('y_m')
        axs[3].set_xlabel('Time (s)')
        axs[3].set_ylabel('y_m (m)')
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
        writer.writerow(["Experiment", "Roll", "dy_mps", "y_m"])

        for experiment, mse_values in mse_results_all.items():
            writer.writerow([experiment, mse_values["Roll"], mse_values["dy_mps"], mse_values["y_m"]])

    print(f"MSE results saved at: {output_csv_path}")