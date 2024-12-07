PYTHON = python3.10 # Python variable
CPP = g++  # Cpp variable

build_heuristic:
	$(CPP) ./Code/Heuristic/BottomLeftFillSolution.cpp 
	mv a.out ./Builds/blf_solution.exe

run_heuristic:
	./Builds/blf_solution.exe > ./Output/output_heuristic.txt

start_heuristic: build_heuristic run_heuristic

start_mips: 
	$(PYTHON) ./Code/MIPS/MIPS_Solution.py > ./Output/output_mips.txt
