all: app image
TERGET=rio

app:
	$(CXX) main.cpp -o $(TERGET)

image: app
	./$(TERGET) | convert ppm:- out.png
