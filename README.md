# Tello Drone Simulator and Parameter Identification

This repository contains a comprehensive system for simulating and identifying parameters of a Tello drone using Simulink models, C++ code generation, and multi-objective optimization techniques.

## 📋 Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Key Features](#key-features)
- [Installation](#installation)
- [Usage](#usage)
- [Parameter Identification Scripts](#parameter-identification-scripts)
- [Experimental Data](#experimental-data)
- [Results and Analysis](#results-and-analysis)
- [Build System](#build-system)
- [Requirements](#requirements)
- [Contributing](#contributing)

## 🎯 Overview

This project implements a complete pipeline for drone dynamics modeling and parameter identification:

1. **Simulink Model**: A nonlinear drone dynamics model created in MATLAB/Simulink
2. **C++ Code Generation**: Automatic C++ code generation from the Simulink model using Embedded Coder
3. **Python Bindings**: Python interface to the C++ simulator using pybind11
4. **Parameter Identification**: Multi-objective optimization using NSGA-II algorithm
5. **Experimental Validation**: Real flight data analysis and model validation

The system enables researchers and engineers to:
- Simulate drone dynamics with high fidelity
- Identify model parameters from experimental flight data
- Validate model accuracy across different flight maneuvers
- Perform multi-objective optimization for parameter estimation

## 📁 Repository Structure

```
tello_sim/
├── 📁 simulink models/          # Simulink model files
│   ├── NoLinearModel.slx        # Main nonlinear drone dynamics model
│   └── wrapper.slx              # Wrapper model for testing
├── 📁 NoLinearModel_ert_rtw/    # Generated C++ code from Simulink
│   ├── NoLinearModel.cpp        # Main model implementation
│   ├── NoLinearModel.h          # Model header file
│   └── ...                     # Additional generated files
├── 📁 scripts/                  # C++ simulator and Python bindings
│   ├── Simulator.cpp            # C++ simulator implementation
│   ├── Simulator.h              # Simulator header
│   └── simulator_bindings.cpp   # Python-C++ bindings using pybind11
├── 📁 experiments/              # Experimental flight data
│   ├── ExpX_senoide_id*.csv     # X-axis sinusoidal experiments
│   ├── ExpY*_senoide_id*.csv    # Y-axis sinusoidal experiments
│   ├── ExpZ_senoide_id*.csv     # Z-axis sinusoidal experiments
│   ├── ExpYaw_senoide_id*.csv   # Yaw sinusoidal experiments
│   └── ExpTodos_manual_*.csv    # Manual flight experiments
├── 📁 results/                  # Optimization results and analysis
│   ├── ExpX/                    # X-axis identification results
│   ├── ExpY/                    # Y-axis identification results
│   ├── ExpZ/                    # Z-axis identification results
│   └── ExpYaw/                  # Yaw identification results
├── 📁 tutoriais/                # Documentation and tutorials
├── 📄 ident_multi_pitch.py      # Pitch dynamics identification
├── 📄 ident_multi_roll.py       # Roll dynamics identification
├── 📄 ident_multi_yaw.py        # Yaw dynamics identification
├── 📄 ident_multi_z.py          # Vertical dynamics identification
├── 📄 setup.py                  # Python package build configuration
├── 📄 telo.py                   # Tello drone connection utility
└── 📄 simulator.pyd             # Compiled Python extension
```

## ✨ Key Features

### 🚁 Drone Dynamics Modeling
- **Nonlinear Model**: Comprehensive 6-DOF drone dynamics model
- **Multi-Axis Control**: Independent control for pitch, roll, yaw, and altitude
- **Aerodynamic Effects**: Drag coefficients and coupling between axes
- **Real-time Simulation**: Configurable real-time and accelerated simulation modes

### 🔧 Parameter Identification
- **Multi-Objective Optimization**: NSGA-II algorithm for Pareto-optimal solutions
- **Multiple Experiments**: Uses various flight patterns (sinusoidal, manual)
- **Comprehensive Metrics**: MSE analysis for position, velocity, and attitude
- **Visualization**: Detailed plots and convergence analysis

### 📊 Analysis Tools
- **Pareto Front Analysis**: Multi-objective trade-off visualization
- **Convergence Tracking**: Generation-by-generation optimization progress
- **Parameter Distribution**: Box plots and statistical analysis
- **Model Validation**: Cross-validation across different experiments

## 🛠 Installation

### Prerequisites
- Python 3.8+
- MATLAB/Simulink (for model modifications)
- Visual Studio Build Tools (Windows)
- Git

### Step 1: Clone Repository
```bash
git clone https://github.com/Gfernandes10/tello_sim.git
cd tello_sim
```

### Step 2: Install Python Dependencies
```bash
pip install -r requirements.txt
```

Required packages:
```
numpy
pandas
matplotlib
scikit-learn
scipy
pymoo
pybind11
djitellopy
imageio
```

### Step 3: Build C++ Extension
```bash
python setup.py build_ext --inplace
```

This compiles the C++ simulator code and creates Python bindings.

## 🚀 Usage

### Basic Simulator Usage
```python
import simulator
import numpy as np

# Create simulator instance
sim = simulator.Simulator()

# Initialize the simulator
sim.initialize()

# Set custom parameters
params = sim.get_params()
params.pitch_K = 2.5
params.pitch_omega = 3.0
sim.set_params(params)

# Run simulation with input vector
u_pitch = [0.1, 0.2, 0.1, 0.0, -0.1]  # Control inputs
sim.run_input_vector_based(upitch=u_pitch)

# Get simulation results
output = sim.get_rtY_vector()
positions = [out.x_m for out in output]
velocities = [out.dx_mps for out in output]
```

### Parameter Identification
Run any of the identification scripts:

```bash
# Identify pitch dynamics parameters
python ident_multi_pitch.py

# Identify roll dynamics parameters  
python ident_multi_roll.py

# Identify yaw dynamics parameters
python ident_multi_yaw.py

# Identify vertical dynamics parameters
python ident_multi_z.py
```

Each script will:
1. Load experimental data
2. Run NSGA-II optimization
3. Generate analysis plots
4. Save results to the `results/` directory

## 📈 Parameter Identification Scripts

### `ident_multi_pitch.py`
- **Purpose**: Identifies pitch dynamics parameters
- **Parameters Optimized**: `pitch_K`, `pitch_omega`, `pitch_zeta`, `pitch_max`, `Cx`
- **Objectives**: Minimizes MSE for pitch angle and longitudinal velocity
- **Experiments Used**: X-axis sinusoidal and manual maneuvers

### `ident_multi_roll.py`
- **Purpose**: Identifies roll dynamics parameters  
- **Parameters Optimized**: `roll_K`, `roll_omega`, `roll_zeta`, `roll_max`, `Cy`
- **Objectives**: Minimizes MSE for roll angle and lateral velocity
- **Experiments Used**: Y-axis sinusoidal and manual maneuvers

### `ident_multi_yaw.py`
- **Purpose**: Identifies yaw dynamics parameters
- **Parameters Optimized**: `yawp_K`, `yawp_max`, `yawp_tal`
- **Objectives**: Minimizes MSE for yaw rate
- **Experiments Used**: Yaw sinusoidal maneuvers

### `ident_multi_z.py`
- **Purpose**: Identifies vertical dynamics parameters
- **Parameters Optimized**: `zp_K`, `zp_max`, `zp_tal`  
- **Objectives**: Minimizes MSE for vertical velocity
- **Experiments Used**: Z-axis sinusoidal and manual maneuvers

## 🔬 Experimental Data

The `experiments/` directory contains real flight data from Tello drone experiments:

### Data Format
Each CSV file contains timestamped data with columns:
- **Time**: `time` - Timestamp in seconds
- **Position**: `filtered_pose/x`, `filtered_pose/y`, `filtered_pose/z`
- **Velocity**: `filtered_pose/vxb`, `filtered_pose/vyb`, `filtered_pose/dz`
- **Attitude**: `filtered_pose/pitch`, `filtered_pose/roll`, `filtered_pose/yaw`
- **Angular Rates**: `filtered_pose/p`, `filtered_pose/q`, `filtered_pose/r`
- **Control Inputs**: `u_control/ux`, `u_control/uy`, `u_control/uz`, `u_control/uyaw`

### Experiment Types
1. **Sinusoidal Experiments**: Controlled sinusoidal inputs for system identification
2. **Manual Experiments**: Human pilot inputs for validation
3. **Multi-axis**: Combined maneuvers testing coupling effects

## 📊 Results and Analysis

Each identification run generates comprehensive analysis in the `results/` directory:

### Generated Files
- **`optimization_experiment.png`**: Comparison of experimental vs. simulated data
- **`pareto_front.png`**: Pareto-optimal solutions visualization
- **`objectives_convergence.png`**: Optimization convergence analysis
- **`boxplot_parameters.png`**: Parameter distribution analysis
- **`mse_results.csv`**: Quantitative performance metrics
- **`objectives_history.csv`**: Detailed optimization history

### NSGA-II Optimization Features
- **Population Size**: 200-300 individuals
- **Generations**: 30-100 (depending on complexity)
- **Multi-objective**: Simultaneous optimization of multiple error metrics
- **Pareto Front**: Trade-off analysis between conflicting objectives
- **Diversity Metrics**: Spread and spacing analysis of solutions

## 🔧 Build System

### Python Extension Build (`setup.py`)
The build system uses pybind11 to create Python bindings for the C++ simulator:

```python
ext_modules = [
    Pybind11Extension(
        "simulator",
        [
            "scripts/simulator_bindings.cpp",
            "scripts/Simulator.cpp", 
            "NoLinearModel_ert_rtw/NoLinearModel.cpp"
        ],
        include_dirs=[".", "NoLinearModel_ert_rtw"],
        language="c++",
    ),
]
```

### Key Components
1. **Simulator Class**: Main C++ simulation engine
2. **NoLinearModel**: Generated Simulink model code
3. **Python Bindings**: pybind11 interface for Python access
4. **Parameter Interface**: Dynamic parameter modification

## 📋 Requirements

### Software Requirements
- **Python**: 3.8 or higher
- **MATLAB**: R2019b or higher (for model modifications)
- **Compiler**: Visual Studio 2019+ (Windows) or GCC 7+ (Linux)

### Hardware Requirements
- **RAM**: Minimum 8GB (16GB recommended for large optimizations)
- **CPU**: Multi-core processor (optimization is CPU-intensive)
- **Storage**: 2GB free space for results and data

### Python Package Dependencies
```
numpy>=1.19.0
pandas>=1.3.0
matplotlib>=3.3.0
scikit-learn>=0.24.0
scipy>=1.7.0
pymoo>=0.6.0
pybind11>=2.6.0
djitellopy>=2.4.0
imageio>=2.9.0
```

## 🤝 Contributing

We welcome contributions to improve the drone simulation and identification system:

### Areas for Contribution
1. **Model Enhancement**: Improving the Simulink dynamics model
2. **Optimization Algorithms**: Implementing additional optimization methods
3. **Data Processing**: Enhanced experimental data analysis tools
4. **Visualization**: Advanced plotting and analysis capabilities
5. **Documentation**: Tutorials and examples

### Development Workflow
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Code Style
- Follow PEP 8 for Python code
- Use meaningful variable names and comments
- Document new functions and classes
- Include unit tests for new functionality

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📞 Contact

- **Author**: Gabriel Fernandes
- **GitHub**: [@Gfernandes10](https://github.com/Gfernandes10)
- **Project Link**: [https://github.com/Gfernandes10/tello_sim](https://github.com/Gfernandes10/tello_sim)

## 🙏 Acknowledgments

- MATLAB/Simulink for model development platform
- pymoo library for multi-objective optimization algorithms
- pybind11 for seamless Python-C++ integration
- DJI Tello drone for experimental data collection
- NSGA-II algorithm developers for the optimization framework

---

*This project demonstrates the integration of model-based design, code generation, and advanced optimization techniques for drone system identification and validation.*
