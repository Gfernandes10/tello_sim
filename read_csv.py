import pandas as pd
import matplotlib.pyplot as plt

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

# Exemplo de uso
if __name__ == "__main__":
    file_path = "experiments/ExpTodos_manual_x.csv"  # Substitua pelo caminho correto
    data = read_csv_and_adjust_time(file_path)
    print(data)

    # Exemplo de plotagem em relação ao tempo

    plt.plot(data['time'], data['filtered_pose/vxb'], label='filtered_pose/vxb')
    plt.plot(data['time'], data['u_control/ux'], label='u_control/ux')
    plt.xlabel('Time (s)')
    plt.ylabel('Values')
    plt.title('Data over Time')
    plt.legend()
    plt.show()
