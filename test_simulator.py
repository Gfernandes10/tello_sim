import simulator
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Crie uma instância do simulador
# sim = simulator.Simulator()

# Criando o vetor upitch
# upitch = [0.0 if t < 1 else 1.0 for t in np.arange(0, 10.01, 0.01)]


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

if __name__ == "__main__":
    file_path = "experiments/ExpTodos_manual_x.csv"  # Substitua pelo caminho correto
    data = read_csv_and_adjust_time(file_path)
    print(data)

    # Exemplo de plotagem em relação ao tempo
    plt.figure(1)
    plt.plot(data['time'], data['filtered_pose/vxb'], label='filtered_pose/vxb')
    plt.plot(data['time'], data['u_control/ux'], label='u_control/ux')
    plt.xlabel('Time (s)')
    plt.ylabel('Values')
    plt.title('Data over Time')
    plt.legend()
    plt.show(block=False)

    # Criando uma segunda figura


    sim = simulator.Simulator()
    sim.initialize()
    sim.run_input_vector_based(upitch=data['u_control/ux'].tolist())
    output = sim.get_rtY_vector()
    simdata = {}
    simdata['dx_mps'] = [output_item.dx_mps for output_item in output]
    simdata['x_m'] = [output_item.x_m for output_item in output]
    
    plt.figure(2)
    plt.plot(data['time'], simdata['dx_mps'], label='dx_mps')
    plt.plot(data['time'], data['u_control/ux'], label='u_control/ux')
    plt.xlabel('Time (s)')
    plt.ylabel('Values')
    plt.title('Segunda Figura')
    plt.legend()
    plt.show(block=True)


