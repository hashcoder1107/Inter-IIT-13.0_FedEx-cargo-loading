generate_random_testcase:
	$(MAKE) clean
	mkdir Executables   
	g++ Code/testCaseGenerator.cpp -o Executables/testCaseGenerator 
	./Executables/testCaseGenerator 1000 5000 3 100 100 10 50 50 0.5 100 500 
	$(MAKE) clean

clean:
	rm -rf Executables

