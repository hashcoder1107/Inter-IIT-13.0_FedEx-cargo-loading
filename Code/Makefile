# Variables
CXX := g++-14
SRC := BottomLeftFillSolution.cpp
TARGET := a.out

# Default target
all: run

# Run the program 5 times with the given start index, compiling each time
run:
ifndef START_INDEX
	$(error Usage: make run START_INDEX=<start_index>)
endif
	@for ((i=$(START_INDEX); i<$(START_INDEX)+5; i++)); do \
		echo "Compiling and running iteration $$i"; \
		$(CXX) $(SRC) -o $(TARGET); \
		./$(TARGET) > "out$$i.txt"; \
		sleep 1; \
	done

# Clean generated files
clean:
	rm -f $(TARGET) out*.txt
