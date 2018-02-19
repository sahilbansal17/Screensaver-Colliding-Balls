# Screensaver-Colliding-Balls
First Project in COP290 (Design Practices) Course.

In this assignment, a simple screen saver is displayed with **n** (variable - user chosen) number of balls on the screen. The balls start from *random positions* on the screen and *random velocity*. For simplicity, the masses of all the balls are assumed to be the same. The collision of the ball with another ball, the wall or terrain on the ground is simulated using perfect reflection (using **e=1**).
Each of the ball is simulated using a single thread.

There are **two modes** provided (2D & 3D). In 2D mode, triangle objects are used as obstacles in the terrain whereas in the 3D mode, fixed spheres on the base of the cube are used.

***

# Code / Source Files
A **makefile** is made to directly compile and execute the C++ program using instructions mentioned in the **How to use** section.

All the source code is in the *code* directory.
The main program is in **main.cpp** file. Four **.h** files are made for various *class declarations* or *functions* including ***ball.h***, ***screen.h***, ***physics.h*** and ***terrain.h***.

The file ***pthread_barrier.h*** is used to include the pthread header file in the program as well as pthread_barrier.

For **testing** purpose, a file **testBallBall.cpp** contains a few test cases to verify that ball to ball collision is working properly.

The entire project was done using **Git** version control and all the commits and logs can easily be checked using git commands. There are two branches, **master** branch contains the code for 2D mode and the **3d_working** branch which contains the code for 3D mode.

***

# How to use

To use the 2D mode, type the following command : ```make execute_2d num_thread=n```

To use the 3D mode, type the following command :
```make execute_3d num_thread=n```
where n = number of balls.

## Keyboard controls

The following keyboard controls are provided:
* **f** : To toggle between normal and full screen mode.
* **spacebar** : To pause the screen
* **Number from 0-9** : To select balls from 1-10. A selected ball becomes white. Again pressing the same number brings back its original color.
* **+** : To increase the speed of the last selected ball.
* **-** : To decrease the speed of the last selected ball.
* **Up arrow key** : To increase the radius of the last selected ball.
* **Down arrow key** : To decrease the radius of the last selected ball.
* **ESC** : To exit.

***
# Code Structure
(generated using Sourcetrail)
## Files structure
![](/Images/Files.png)
## Functions in all files
![](/Images/Functions.png)
## Ball class along with functions linked from other files
![](/Images/Ball.png)
## Triangle class (2D mode)
![](/Images/Triangle.png)

***
# Working Snapshots
* **2D Mode** : ![](/Images/2D.png)

* **3D Mode** : ![](/Images/3D.png)
