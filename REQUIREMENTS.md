# Requirements

This document serves as a guide to set up the environment and repository, install dependencies, and understand why each library is used.

---

## Table of Contents

1.⁠ ⁠[Environment Setup](#environment-setup)
2.⁠ ⁠[Dependencies](#dependencies)

---

## Environment Setup

### Python Installation

-   Ensure *Python 3.9 or above* is installed on your system.

-   Download Python from the [official Python website](https://www.python.org/downloads/).

-   Verify the installation by running:

⁠ bash
  python --version
 ⁠

### C++ Compiler Installation

-   Install minGW gcc compiler from the [official minGW website](https://sourceforge.net/projects/mingw-w64/).
-   Verify the installation by running:

⁠ bash
  g++ --version
 ⁠

---

## Dependencies

1.⁠ ⁠ORTOOLS :

-   Google Optimization Tools for solving optimization and mathematical problems.

⁠ bash
    python3 -m venv venv     # Set up virtual environment
    source venv/bin/activate # Activates the virtual environment
    pip install ortools
 ⁠

2.⁠ ⁠Pandas :

-  Facilitates data manipulation and analysis in a structured format (like DataFrames)

•⁠  ⁠This library is a dependency of OR-Tools and will be installed automatically during its setup process.

3.⁠ ⁠numpy :

-  Essential for numerical computations and efficient array handling
-  This library is a dependency of OR-Tools and will be installed automatically during its setup process.

4.⁠ ⁠MakeFile:
•⁠  ⁠Used for automating the compilation and build process for C++ programs.
-  Make sure that ⁠ GNU make ⁠ is installed.

5.⁠ ⁠Matplotlib:
•⁠  ⁠Used for graphs of variouis test results.
⁠ bash
    pip install matplotlib
 ⁠
6.⁠ ⁠Plotly:
•⁠  ⁠Used for visualisation of finally placed packages in the ULDs.
⁠ bash
    pip install plotly
 ⁠
---