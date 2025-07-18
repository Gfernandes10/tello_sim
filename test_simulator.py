# from tello_sim import simulator
import simulator

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error, mean_absolute_error
from scipy.optimize import minimize
import csv



def read_csv_and_adjust_time(file_path):
    # Leia o arquivo CSV
    data = pd.read_csv(file_path)

    # Ajuste o vetor de tempo para começar do zero
    if 'time' in data.columns:
        data['time'] = data['time'] - data['time'].iloc[0]

    # Interpolação para lidar com valores NaN
    data = data.interpolate(method='linear', limit_direction='forward', axis=0)
    data = data.fillna(method='bfill').fillna(method='ffill')

    return data

def objective_function(params_values, sim, data):
    # Atualizar os parâmetros no simulador
    params = sim.get_params()
    params.pitch_K = params_values[0]
    params.pitch_omega = params_values[1]
    params.pitch_zeta = params_values[2]
    # params.pitch_max = best_params[3]
    params.pitch_max = 0.3
    params.Cx = params_values[3]
    sim.set_params(params)

    # Inicializar e rodar o simulador
    sim.initialize()
    sim.run_input_vector_based(upitch=data['u_control/ux'].tolist())

    # Obter os dados simulados
    output = sim.get_rtY_vector()
    simulationdata = {}
    simulationdata['dx_mps'] = [output_item.dx_mps for output_item in output]
    simulationdata['pitch'] = [output_item.pitch_rad for output_item in output]
    simulationdata['x_m'] = [output_item.x_m for output_item in output]

    # Calcular o MSE entre as curvas
    data['filtered_pose/xb'] = data['filtered_pose/xb'] - data['filtered_pose/xb'].iloc[0]
    # mse_pitch = mean_absolute_error(data['filtered_pose/pitch'], simulationdata['pitch'])
    mse_vxb = mean_squared_error(data['filtered_pose/vxb'], simulationdata['dx_mps'])
    # mse_xb = mean_squared_error(data['filtered_pose/xb'], simulationdata['x_m'])
    # total_mse =  mse_vxb
    return mse_vxb

def optimize_parameters(sim, data):
    # Valores iniciais para os parâmetros
    initial_params = [0.5, 0.1, 0.7, 0.5, 1.0]  # pitch_K, pitch_omega, pitch_zeta, pitch_max

    # Limites para os parâmetros
    bounds = [(0.01, 10.0), (0.01, 10.0), (0.01, 10.0), (0.01, 10.0), (0.01, 10.0)]

    # Otimização
    result = minimize(objective_function, initial_params, args=(sim, data), bounds=bounds, method='Powell')

    return result

if __name__ == "__main__":

    file_path = "experiments/ExpX_senoide_id1.csv" 
    data = read_csv_and_adjust_time(file_path)
    print(data)


    sim = simulator.Simulator()
    sim.initialize()
    sim.run_input_vector_based(upitch=data['u_control/ux'].tolist())
    output = sim.get_rtY_vector()
    simdata = {}
    simdata['dx_mps'] = [output_item.dx_mps for output_item in output]
    simdata['x_m'] = [output_item.x_m for output_item in output]
    simdata['pitch'] = [output_item.pitch_rad for output_item in output]

    print("MSE pré-otimização:", mean_squared_error(data['filtered_pose/vxb'], simdata['dx_mps']))

    # Otimização dos parâmetros
    result = optimize_parameters(sim, data)
    print("Parâmetros otimizados:", result.x)
    print("MSE mínimo:", result.fun)

    sim_otimizados = simulator.Simulator()
    params = sim_otimizados.get_params()
    params.pitch_K = result.x[0]
    params.pitch_omega = result.x[1]
    params.pitch_zeta = result.x[2]
    params.pitch_max = result.x[3]
    sim_otimizados.set_params(params)
    sim_otimizados.initialize()
    sim_otimizados.run_input_vector_based(upitch=data['u_control/ux'].tolist())
    output_oti = sim_otimizados.get_rtY_vector()
    simOtimizados = {}
    simOtimizados['dx_mps'] = [output_item.dx_mps for output_item in output_oti]
    simOtimizados['x_m'] = [output_item.x_m for output_item in output_oti]
    simOtimizados['pitch'] = [output_item.pitch_rad for output_item in output_oti]


    # Criando subplots para pitch, dx_mps e x_m
    fig, axs = plt.subplots(4, 1, figsize=(10, 8))

    # Plot para pitch
    # axs[0].plot(data['time'], simdata['pitch'], label='Simulated Pitch')
    axs[0].plot(data['time'], data['filtered_pose/pitch'], label='Experimental Pitch')
    axs[0].plot(data['time'], simOtimizados['pitch'], label='Optimized Pitch', linestyle='--')
    axs[0].set_title('Pitch')
    axs[0].set_xlabel('Time (s)')
    axs[0].set_ylabel('Pitch (rad)')
    axs[0].legend()

    # Plot para dx_mps
    # axs[1].plot(data['time'], simdata['dx_mps'], label='Simulated dx_mps')
    axs[1].plot(data['time'], data['filtered_pose/vxb'], label='Experimental dx_mps')
    axs[1].plot(data['time'], simOtimizados['dx_mps'], label='Optimized dx_mps', linestyle='--')
    axs[1].set_title('dx_mps')
    axs[1].set_xlabel('Time (s)')
    axs[1].set_ylabel('dx_mps (m/s)')
    axs[1].legend()

    # Plot para x_m
    data['filtered_pose/xb'] = data['filtered_pose/xb'] - data['filtered_pose/xb'].iloc[0]
    # axs[2].plot(data['time'], simdata['x_m'], label='Simulated x_m')
    axs[2].plot(data['time'], data['filtered_pose/xb'] , label='Experimental x_m')
    axs[2].plot(data['time'], simOtimizados['x_m'], label='Optimized x_m', linestyle='--')
    axs[2].set_title('x_m')
    axs[2].set_xlabel('Time (s)')
    axs[2].set_ylabel('x_m (m)')
    axs[2].legend()

    # Plot para u_theta
    axs[3].plot(data['time'], data['u_control/ux'] , label='Senoide id 1')
    axs[3].set_title('u_theta')
    axs[3].set_xlabel('Time (s)')
    axs[3].set_ylabel('u_theta')
    axs[3].legend()


    # Adicionar um título geral para todos os subplots
    fig.suptitle('Experement used for optimization', fontsize=16)


    # Lista de experimentos
    experiments = [
        ("ExpX_senoide_id1.csv", "Senoide id 1"),
        ("ExpX_senoide_id2.csv", "Senoide id 2"),
        ("ExpX_senoide_id3.csv", "Senoide id 3"),
        ("ExpTodos_manual_x.csv", "Manual Input")
    ]

    # Acumular resultados de MSE para todas as senoides e manual
    mse_results_all = {}

    for file_path, label in experiments:
        data = read_csv_and_adjust_time(f"experiments/{file_path}")

        sim_otimizados = simulator.Simulator()
        params = sim_otimizados.get_params()
        params.pitch_K = result.x[0]
        params.pitch_omega = result.x[1]
        params.pitch_zeta = result.x[2]
        params.pitch_max = result.x[3]
        params.pitch_K = 3.7890115621679845
        params.pitch_omega = 1.235277252913756
        params.pitch_zeta = 0.9439859168709424
        params.pitch_max = 0.3
        params.Cx = 8.1535879632004  
        sim_otimizados.set_params(params)
        sim_otimizados.initialize()
        sim_otimizados.run_input_vector_based(upitch=data['u_control/ux'].tolist())
        output_oti = sim_otimizados.get_rtY_vector()
        simOtimizados = {
            'dx_mps': [output_item.dx_mps for output_item in output_oti],
            'x_m': [output_item.x_m for output_item in output_oti],
            'pitch': [output_item.pitch_rad for output_item in output_oti]
        }

        # Calcular MSE para este experimento
        data['filtered_pose/xb'] = data['filtered_pose/xb'] - data['filtered_pose/xb'].iloc[0]
        mse_results_all[label] = {
            "Pitch": mean_squared_error(data['filtered_pose/pitch'], simOtimizados['pitch']),
            "dx_mps": mean_squared_error(data['filtered_pose/vxb'], simOtimizados['dx_mps']),
            "x_m": mean_squared_error(data['filtered_pose/xb'], simOtimizados['x_m'])
        }

        # Criar subplots para pitch, dx_mps e x_m
        fig, axs = plt.subplots(4, 1, figsize=(10, 8))

        # Plot para pitch
        axs[0].plot(data['time'], data['filtered_pose/pitch'], label='Experimental Pitch')
        axs[0].plot(data['time'], simOtimizados['pitch'], label='Optimized Pitch', linestyle='--')
        axs[0].set_title('Pitch')
        axs[0].set_xlabel('Time (s)')
        axs[0].set_ylabel('Pitch (rad)')
        axs[0].legend()

        # Plot para dx_mps
        axs[1].plot(data['time'], data['filtered_pose/vxb'], label='Experimental dx_mps')
        axs[1].plot(data['time'], simOtimizados['dx_mps'], label='Optimized dx_mps', linestyle='--')
        axs[1].set_title('dx_mps')
        axs[1].set_xlabel('Time (s)')
        axs[1].set_ylabel('dx_mps (m/s)')
        axs[1].legend()

        # Plot para x_m
        axs[2].plot(data['time'], data['filtered_pose/xb'], label='Experimental x_m')
        axs[2].plot(data['time'], simOtimizados['x_m'], label='Optimized x_m', linestyle='--')
        axs[2].set_title('x_m')
        axs[2].set_xlabel('Time (s)')
        axs[2].set_ylabel('x_m (m)')
        axs[2].legend()

        # Plot para u_theta
        axs[3].plot(data['time'], data['u_control/ux'], label=label)
        axs[3].set_title('u_theta')
        axs[3].set_xlabel('Time (s)')
        axs[3].set_ylabel('u_theta')
        axs[3].legend()

        # Adicionar um título geral para todos os subplots
        fig.suptitle(f'Optimization comparation for {label}', fontsize=16)

        # Ajustar layout
        plt.tight_layout()

        # Salvar a figura
        plt.savefig(f"results/{label.replace(' ', '_')}.png")
        plt.close()

    # Exibir a tabela de resultados de MSE para todos os experimentos
    print("Tabela de Resultados de MSE para todos os experimentos:")
    for experiment, mse_values in mse_results_all.items():
        print(f"\n{experiment}:")
        for key, value in mse_values.items():
            print(f"  {key}: {value:.4f}")

    # Salvar os resultados de MSE em um arquivo CSV
    output_csv_path = "results/mse_results.csv"

    with open(output_csv_path, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Experimento", "Pitch", "dx_mps", "x_m"])

        for experiment, mse_values in mse_results_all.items():
            writer.writerow([experiment, mse_values["Pitch"], mse_values["dx_mps"], mse_values["x_m"]])

    print(f"Resultados de MSE salvos em: {output_csv_path}")