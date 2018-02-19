CXX = g++

CFLAGS = -std=c++11

ifeq ($(shell uname -s), Darwin)
    LFLAGS = -framework OpenGL -framework GLUT -lpthread
else
    LFLAGS = -lGL -lGLU -lglut -lpthread
endif

CODEDIR = code

MAIN_2D = a.out
MAIN_3D = $(CODEDIR)/a.out

execute:
	echo "Please type:\nmake execute_2d num_thread=n\nOR\nmake execute_3d num_thread=n"

execute_2d: $(MAIN_2D)
	./$(MAIN_2D) $(num_thread)

execute_3d:	$(MAIN_3D)
	$(MAIN_3D) $(num_thread)

$(MAIN_2D):
	git checkout master
	$(CXX) $(CODEDIR)/main.cpp $(CFLAGS) -o $(MAIN_2D) $(LFLAGS)

$(MAIN_3D):
	git checkout 3d_working
	$(CXX) $(CODEDIR)/main.cpp $(CFLAGS) -o $(MAIN_3D) $(LFLAGS)

clean_2d:
	rm $(MAIN_2D)
clean_3d:
	rm $(MAIN_3D)
