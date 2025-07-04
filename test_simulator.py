import simulator
import numpy as np

# Crie uma instância do simulador
sim = simulator.Simulator()

# Configure os parâmetros
sim.is_real_time = False
sim.base_rate = 0.01
sim.simulation_time = 5

# Criando o vetor upitch
upitch = [0.0 if t < 1 else 1.0 for t in np.arange(0, 10.01, 0.01)]

# Inicialize e execute
sim.initialize()
sim.run_input_vector_based(upitch=upitch)
# Obtenha os parâmetros atuais
params = sim.get_params()
print(f"Cx: {params.Cx}, Cy: {params.Cy}")

# Modifique os parâmetros
params.Cx = 1.5
params.Cy = 2.0

# Configure os novos parâmetros no simulador
sim.set_params(params)
for output in sim.get_rtY_vector():
    print(f"dx_mps: {output.dx_mps}, x_m: {output.x_m}")
test = 1