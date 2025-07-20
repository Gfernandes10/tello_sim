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
    params.yawp_K = params_values[0]
    params.yawp_max = params_values[1]
    params.yawp_tal = params_values[2]
    sim.set_params(params)

    # Initialize and run the simulator
    sim.initialize()
    sim.run_input_vector_based([], [], [], uyaw=data['u_control/uyaw'].tolist())

    # Get the simulated data
    output = sim.get_rtY_vector()
    simulationdata = {}
    simulationdata['dyaw_radps'] = [output_item.dyaw_radps for output_item in output]
    simulationdata['yaw_rad'] = [output_item.yaw_rad for output_item in output]

    # Ensure that the lengths of the data match
    min_len = min(len(data['filtered_pose/r']), len(simulationdata['dyaw_radps']))


    exp_vyaw = data['filtered_pose/r'][:min_len]
    sim_vyaw = simulationdata['dyaw_radps'][:min_len]

    # Calculate the MSE between the curves
    mse_vyaw = mean_squared_error(exp_vyaw, sim_vyaw)

    return [mse_vyaw]

class MultiObjectiveProblem(Problem):
    def __init__(self, sim, data):
        super().__init__(n_var=3,
                         n_obj=1,
                         n_constr=0,
                         xl=np.array([0.01, 0.01, 0.01]),
                         xu=np.array([10.0, 10.0, 10.0]))
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
        # If X is 1D (only one solution), reshape to (1, n_params)
        if X.ndim == 1:
            X = X.reshape(1, -1)
        fig, ax = plt.subplots()
        # Plot one box per parameter (columns)
        ax.boxplot(X.T, vert=True, patch_artist=True)
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
        ("experiments/ExpYaw_senoide_id1.csv", "Sine id 1"),
        ("experiments/ExpYaw_senoide_id2.csv", "Sine id 2"),
        ("experiments/ExpYaw_senoide_id3.csv", "Sine id 3"),
    ]
    file_path = "experiments/ExpYaw_senoide_id1.csv"
    results_path = "results/ExpYaw"
    os.makedirs(results_path, exist_ok=True)
    data = read_csv_and_adjust_time(file_path)
    # Normalize the initial position once
    data['filtered_pose/yaw'] = data['filtered_pose/yaw'] - data['filtered_pose/yaw'].iloc[0]
    print(data)

    sim = simulator.Simulator()
    sim.initialize()
    sim.run_input_vector_based([], [], [], uyaw=data['u_control/uyaw'].tolist())
    output = sim.get_rtY_vector()
    simdata = {}
    simdata['dyaw_radps'] = [output_item.dyaw_radps for output_item in output]
    simdata['yaw_rad'] = [output_item.yaw_rad for output_item in output]


    print("Pre-optimization MSE velocity:", mean_squared_error(data['filtered_pose/r'], simdata['dyaw_radps']))


    # Parameter optimization with NSGA-II
    result_nsga, problem = optimize_parameters_nsga2(sim, data)
    
    print("Multi-objective Optimization Results (Pareto Front):")
    print("Parameters (X):", result_nsga.X)
    print("Objectives (F):", result_nsga.F)

    # Choose the best compromise solution (smallest Euclidean distance from the origin)
    best_index = np.argmin(result_nsga.F)
    best_params = result_nsga.X
    best_objectives = result_nsga.F[best_index]

    print("\nBest Selected Parameters:", best_params)
    print("Best Objectives (MSEs):", best_objectives)

    sim_optimized = simulator.Simulator()
    params = sim_optimized.get_params()
    params.yawp_K = best_params[0]
    params.yawp_max = best_params[1]
    params.yawp_tal = best_params[2]
    sim_optimized.set_params(params)
    sim_optimized.initialize()
    sim_optimized.run_input_vector_based([], [], [], uyaw=data['u_control/uyaw'].tolist())
    output_oti = sim_optimized.get_rtY_vector()
    simOptimized = {}
    simOptimized['dyaw_radps'] = [output_item.dyaw_radps for output_item in output_oti]
    simOptimized['yaw_rad'] = [output_item.yaw_rad for output_item in output_oti]



    # Creating subplots for roll, dy_mps, and y_m
    fig, axs = plt.subplots(3, 1, figsize=(10, 8))

    # Plot for u_yaw
    axs[0].plot(data['time'], data['u_control/uyaw'], label='Sine id 1')
    axs[0].set_title('u_yaw')
    axs[0].set_xlabel('Time (s)')
    axs[0].set_ylabel('u_yaw')
    axs[0].legend(loc='upper right')

    # Plot for dyaw_radps
    axs[1].plot(data['time'], data['filtered_pose/r'], label='Experimental dyaw_radps')
    axs[1].plot(data['time'], simOptimized['dyaw_radps'], label='Optimized dyaw_radps', linestyle='--')
    axs[1].plot(data['time'], simdata['dyaw_radps'], label='Unoptimized dyaw_radps', linestyle=':')
    axs[1].set_title('dyaw_radps')
    axs[1].set_xlabel('Time (s)')
    axs[1].set_ylabel('dyaw_radps (rad/s)')
    axs[1].legend(loc='upper right')

    # Plot for yaw
    axs[2].plot(data['time'], data['filtered_pose/yaw'], label='Experimental yaw')
    axs[2].plot(data['time'], simOptimized['yaw_rad'], label='Optimized yaw', linestyle='--')
    axs[2].plot(data['time'], simdata['yaw_rad'], label='Unoptimized yaw', linestyle=':')
    axs[2].set_title('yaw')
    axs[2].set_xlabel('Time (s)')
    axs[2].set_ylabel('yaw (rad)')
    axs[2].legend(loc='upper right')






    # Add a general title for all subplots
    fig.suptitle('Experiment used for optimization', fontsize=16)

    # Adjust layout and save the figure
    plt.tight_layout()
    plt.savefig(results_path + "/optimization_experiment.png")
    plt.close()

    # NSGA-II analysis plots
    param_names = ["yawp_K", "yawp_max", "yawp_tal"]
    # plot_nsga2_analysis(result_nsga, problem, param_names=param_names,results_dir=results_path)

    # Accumulate MSE results for all sines and manual
    mse_results_all = {}

    for file_path, label in experiments:
        data = read_csv_and_adjust_time(file_path)
        data['filtered_pose/yaw'] = data['filtered_pose/yaw'] - data['filtered_pose/yaw'].iloc[0]

        sim_optimized = simulator.Simulator()
        params = sim_optimized.get_params()
        params.yawp_K = best_params[0]
        params.yawp_max = best_params[1]
        params.yawp_tal = best_params[2]
        sim_optimized.set_params(params)
        sim_optimized.initialize()
        sim_optimized.run_input_vector_based([], [], [], uyaw=data['u_control/uyaw'].tolist())
        output_oti = sim_optimized.get_rtY_vector()
        simOptimized = {
            'dyaw_radps': [output_item.dyaw_radps for output_item in output_oti],
            'yaw_rad': [output_item.yaw_rad for output_item in output_oti],
        }

        # Calculate MSE for this experiment
        mse_results_all[label] = {
            "dyaw_radps": mean_squared_error(data['filtered_pose/r'], simOptimized['dyaw_radps']),
            "yaw_rad": mean_squared_error(data['filtered_pose/yaw'], simOptimized['yaw_rad']),
        }

        # Create subplots for roll, dy_mps, and y_m
        fig, axs = plt.subplots(3, 1, figsize=(10, 8))

        # Plot for u_yaw
        axs[0].plot(data['time'], data['u_control/uyaw'], label=label)
        axs[0].set_title('u_z')
        axs[0].set_xlabel('Time (s)')
        axs[0].set_ylabel('u_z')
        axs[0].legend(loc='upper right')

        # Plot for dyaw_radps
        axs[1].plot(data['time'], data['filtered_pose/r'], label='Experimental dyaw_radps')
        axs[1].plot(data['time'], simOptimized['dyaw_radps'], label='Optimized dyaw_radps', linestyle='--')
        axs[1].set_title('dyaw_radps')
        axs[1].set_xlabel('Time (s)')
        axs[1].set_ylabel('dyaw (rad/s)')
        axs[1].legend(loc='upper right')

        # Plot for yaw
        axs[2].plot(data['time'], data['filtered_pose/yaw'], label='Experimental yaw')
        axs[2].plot(data['time'], simOptimized['yaw_rad'], label='Optimized yaw', linestyle='--')
        axs[2].set_title('yaw')
        axs[2].set_xlabel('Time (s)')
        axs[2].set_ylabel('yaw (rad)')
        axs[2].legend(loc='upper right')





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
        writer.writerow(["Experiment", "dyaw_radps", "yaw_rad"])

        for experiment, mse_values in mse_results_all.items():
            writer.writerow([experiment, mse_values["dyaw_radps"], mse_values["yaw_rad"]])

    print(f"MSE results saved at: {output_csv_path}")