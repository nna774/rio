all: app image
TERGET=rio
CXX=g++-10
CXXFLAGS=-Wall -Wextra -std=c++20 -fopenmp

app:
	$(CXX) $(CXXFLAGS) main.cpp -o $(TERGET)

image: app
	./$(TERGET) | convert ppm:- out.png
