CXX = g++

CFLAGS = -std=c++11

ifeq ($(shell uname -s), Darwin)
    LFLAGS = -framework OpenGL -framework GLUT -lpthread
else
    LFLAGS = -lGL -lGLU -lglut -lpthread
endif

CODEDIR = code

MAIN = a.out

execute: $(MAIN)
	./$(MAIN) $(num_thread)

$(MAIN):
	$(CXX) $(CFLAGS) -o $(MAIN) $(LFLAGS) $(CODEDIR)/main.cpp

clean:
	rm $(MAIN)
