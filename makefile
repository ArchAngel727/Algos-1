CXX = clang++
CXXFLAGS = -I headers/ -std=c++17
SOURCES = src/*
OUTPUT = main

$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(OUTPUT)

clean:
	rm $(OUTPUT)
