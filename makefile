PYTHON = python3.10 # Python variable
CPP = g++-14  # Cpp variable

build_heuristic:
	$(CPP) ./Code/Heuristic/solution.cpp 
	mkdir -p Builds
	mv a.out ./Builds/heuristic_solution.exe

run_heuristic:
	mkdir -p Output
	./Builds/heuristic_solution.exe > ./Output/output_heuristic.txt

start_heuristic: build_heuristic run_heuristic

start_mips: 
	mkdir -p Output
	$(PYTHON) ./Code/MIPS/MIPS_Solution.py > ./Output/output_mips.txt
