#include "Simulator.h"
#include <vector>
#include <algorithm>

Simulator::Simulator(void)
{
	is_real_time = false;
	base_rate = 0.01; // Default base rate in seconds (100 Hz)
	simulation_time = 10; // Default total simulation time in seconds
}

void Simulator::initialize(void)
{
	// Initialize the model
	rtObj.initialize();
	// Set default values for static members
	step_count = simulation_time / base_rate; // Default number of steps for non-real-time simulation

    printf("Simulator started with following parameters: base_rate = %f, simulation_time = %d, step_count = %d\n", base_rate, simulation_time, step_count);

}
void Simulator::run()
{
	if (is_real_time) {
		run_real_time();
	} else {
		run_non_real_time();
	}
	printf("Simulation completed.\n");
	fflush(stdout);
}
void Simulator::run_real_time(void)
{
	for (int i_step_count = 0; i_step_count <= step_count; ++i_step_count) {
		// Call the step function
		rt_OneStep();
		double sim_time = i_step_count * base_rate;
		printf("Simulation time %f s, dx_mps = %f , x_m = %f \n", sim_time, rtObj.rtY.dx_mps, rtObj.rtY.x_m);
		std::this_thread::sleep_for(std::chrono::milliseconds(int(base_rate * 1000)));
	}
}

void Simulator::run_non_real_time(void)
{
	for (int i_step_count = 0; i_step_count <= step_count; ++i_step_count) {
		// Call the step function
		rt_OneStep();
		printf("Simulation step %d/%d , dx_mps = %f , x_m = %f \n",i_step_count, step_count, rtObj.rtY.dx_mps, rtObj.rtY.x_m);
	}
}
void Simulator::run_input_vector_based(const std::vector<double>& upitch,
                                         const std::vector<double>& uroll,
                                         const std::vector<double>& uzp,
                                         const std::vector<double>& uyaw)
{
    // Descobrir o maior tamanho
    size_t max_size = std::max({upitch.size(), uroll.size(), uzp.size(), uyaw.size()});
    if (max_size == 0) {
        printf("Error: At least one input vector must be non-empty.\n");
        return;
    }
    // Preencher vetores vazios com zeros
    std::vector<double> upitch_filled = upitch;
    std::vector<double> uroll_filled = uroll;
    std::vector<double> uzp_filled = uzp;
    std::vector<double> uyaw_filled = uyaw;
    if (upitch_filled.size() < max_size) upitch_filled.resize(max_size, 0.0);
    if (uroll_filled.size() < max_size) uroll_filled.resize(max_size, 0.0);
    if (uzp_filled.size() < max_size) uzp_filled.resize(max_size, 0.0);
    if (uyaw_filled.size() < max_size) uyaw_filled.resize(max_size, 0.0);
	rtY_vector.clear();
	rtY_vector.push_back(rtObj.getExternalOutputs());
    // Executar a simulação
    for (size_t i = 0; i < max_size; ++i) {
        rtObj.setupitch(upitch_filled[i]);
        rtObj.seturoll(uroll_filled[i]);
        rtObj.setuzp(uzp_filled[i]);
        rtObj.setuyaw(uyaw_filled[i]);
        rt_OneStep();
		rtY_vector.push_back(rtObj.getExternalOutputs());
    }
}

void Simulator::rt_OneStep(void)
{
	static boolean_T OverrunFlag{ false };

	// Disable interrupts here

	// Check for overrun
	if (OverrunFlag) {
		return;
	}

	OverrunFlag = true;

	// Save FPU context here (if necessary)
	// Re-enable timer or interrupt here
	// Set model inputs here

	// Step the model
	rtObj.step();

	// Get model outputs here

	// Indicate task complete
	OverrunFlag = false;

	// Disable interrupts here
	// Restore FPU context here (if necessary)
	// Enable interrupts here
}

NoLinearModel::InstP Simulator::get_params() const {
	return rtObj.get_InstP();
}

void Simulator::set_params(const NoLinearModel::InstP& value) {
    printf("Setando InstP:\n");
    printf("  Cx = %f\n", value.Cx);
    printf("  Cy = %f\n", value.Cy);
    printf("  pitch_K = %f\n", value.pitch_K);
    printf("  pitch_max = %f\n", value.pitch_max);
    printf("  pitch_omega = %f\n", value.pitch_omega);
    printf("  pitch_zeta = %f\n", value.pitch_zeta);
    printf("  roll_K = %f\n", value.roll_K);
    printf("  roll_max = %f\n", value.roll_max);
    printf("  roll_omega = %f\n", value.roll_omega);
    printf("  roll_zeta = %f\n", value.roll_zeta);
    printf("  yawp_K = %f\n", value.yawp_K);
    printf("  yawp_max = %f\n", value.yawp_max);
    printf("  yawp_tal = %f\n", value.yawp_tal);
    printf("  zp_K = %f\n", value.zp_K);
    printf("  zp_max = %f\n", value.zp_max);
    printf("  zp_tal = %f\n", value.zp_tal);
	rtObj.set_InstP(value);
}



