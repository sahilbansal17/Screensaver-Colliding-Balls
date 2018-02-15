#include  "ball.h"
#include <pthread.h>
#include <vector>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_X 500
#define SCREEN_Y 100

// #ifdef __APPLE__
// #ifndef PTHREAD_BARRIER_H_
// #define PTHREAD_BARRIER_H_
//
// #include <pthread.h>
// #include <errno.h>
//
// typedef int pthread_barrierattr_t;
// typedef struct
// {
//     pthread_mutex_t mutex;
//     pthread_cond_t cond;
//     int count;
//     int tripCount;
// } pthread_barrier_t;
//
//
// int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count)
// {
//     if(count == 0)
//     {
//         errno = EINVAL;
//         return -1;
//     }
//     if(pthread_mutex_init(&barrier->mutex, 0) < 0)
//     {
//         return -1;
//     }
//     if(pthread_cond_init(&barrier->cond, 0) < 0)
//     {
//         pthread_mutex_destroy(&barrier->mutex);
//         return -1;
//     }
//     barrier->tripCount = count;
//     barrier->count = 0;
//
//     return 0;
// }
//
// int pthread_barrier_destroy(pthread_barrier_t *barrier)
// {
//     pthread_cond_destroy(&barrier->cond);
//     pthread_mutex_destroy(&barrier->mutex);
//     return 0;
// }
//
// int pthread_barrier_wait(pthread_barrier_t *barrier)
// {
//     pthread_mutex_lock(&barrier->mutex);
//     ++(barrier->count);
//     if(barrier->count >= barrier->tripCount)
//     {
//         barrier->count = 0;
//         pthread_cond_broadcast(&barrier->cond);
//         pthread_mutex_unlock(&barrier->mutex);
//         return 1;
//     }
//     else
//     {
//         pthread_cond_wait(&barrier->cond, &(barrier->mutex));
//         pthread_mutex_unlock(&barrier->mutex);
//         return 0;
//     }
// }
//
// #endif // PTHREAD_BARRIER_H_
// #endif // __APPLE__

// GLfloat xRotated = 0.0, yRotated = 0.0, zRotated = 0.0;

ball **b; // double pointer to ball
int num_balls; // number of balls
// pthread_barrier_t barrier; // create pthread barrier

// initialize balls
void initBalls(int n){
  num_balls = n; // assign proper value to global variable
  b = new ball*[n]; // b points to array of pointers
  for(int i = 0 ; i < n ; i++){
    b[i] = new ball(); // allocate memory to each ball
  }
  // b[0] = new ball(1.0, 0, 0, 0.1, 0, 0);
  // b[1] = new ball(0.1, 0, 0, 0.0, 0, 0);
  // b[2] = new ball(-1.0, 0, 0, 0.0, 0, 0);
  // b[3] = new ball(0.9, 0, 0, 0.0, 0, 0);
}

// temporary function to debug threads
void* tempDrawBalls(void* ballPtr){
  ball * b = (ball *) ballPtr;
  cout << "Ball created";
  // cout << b->getCenterX();
}

// function to render ball on screen
void drawBall(ball *b){

  vector <float> center = b->getCenter();
  vector <float> color = b->getColor();
  float rad = b->getRadius();

  glLoadIdentity();
  glTranslatef(center[0], center[1], center[2]);

  glBegin(GL_POLYGON);
  glColor3f(color[0], color[1], color[2]); // give color to the sphere
  glutSolidSphere(rad, 50, 50);
  glEnd();
}

// function to control ball coordinates
void* controlBallWall(void* ballPtr){

  ball * b = (ball*) ballPtr;

  // get center of the ball
  vector <float> center = b->getCenter();
  // get velocities of the ball
  vector <float> vel = b->getVel();
  // get color values of the ball
  vector <float> color = b->getColor();
  // get radius of the ball
  float rad = b->getRadius();

  // to make sure that ball does not go beyond the boundaries initially (2d boundary)
  for(int i = 0 ; i < 2 ; i++){
    if(center[i] > 1-rad){
      center[i] = 1 - rad;
    }
    else if(center[i] < -1+rad){
      center[i] = -1 + rad;
    }
  }
  // update the center of the ball using velocities, detecting collision with the walls
  for(int i = 0 ; i < 2 ; i++){
    if(center[i] + vel[i] <= 1-rad && center[i] + vel[i] >= -1+rad){
        center[i] += vel[i];
    }
    else{
      center[i] -= vel[i];
      vel[i] = -1*vel[i];
    }

  }

  // pthread_barrier_wait(&barrier);

  //update the center of the balls
  b->setCenter(center[0], center[1], center[2]);
  // update the velocities of the balls if req
  b->setVel(vel[0], vel[1], vel[2]);
  // b->printCenter();
}

void controlBallBall(ball* b1, ball* b2){

  // check whether collision has occurred
  bool res = b1->checkBallBall(b2);

  if(res == 1){
    // balls have collided
    // udpate their velocities

    // cout << "Balls collide.\n";
    // cout << "Intial:\n";
    // vector <float> c1 = b1->getCenter(), c2 = b2->getCenter();
    // vector <float> u1 = b1->getVel(), u2 = b2->getVel();
    // for(int i = 0 ; i < 2 ; i ++){
    //   cout << "x_1_" << i << " " << c1[i] << "\n";
    //   cout << "x_2_" << i << " " << c2[i] << "\n";
    //   cout << "u_1_" << i << " " << u1[i] << "\n";
    //   cout << "u_2_" << i << " " << u2[i] << "\n";
    // }

    b1->updateVel(b2);

    // cout << "Final:\n";
    // vector <float> v1 = b1->getVel(), v2 = b2->getVel();
    // for(int i = 0 ; i < 3 ; i ++){
    //   cout << "v_1_" << i << " " << v1[i] << "\n";
    //   cout << "v_2_" << i << " " << v2[i] << "\n";
    // }
  }
  return ;
}
float counter, p=0.0;
void drawCube(){

  glClear(GL_COLOR_BUFFER_BIT); // clear the buffer

  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  // glTranslatef(0.0,0.0,0.0);
  // glBegin(GL_QUADS);
 
  // glColor3f(0.0f,1.0f,0.0f);    // Color Blue
  // glVertex3f(-02.0f, 02.0f, 0.0f);    
  // glVertex3f(-05.0f, 02.0f, 0.0f);    
  // glVertex3f(-05.0f,-02.0f, 0.0f);    
  // glVertex3f(-02.0f,-02.0f, 0.0f); 

  // glColor3f(0.0f,1.0f,0.0f);    // Color Blue
  // glVertex3f( 02.0f, 02.0f, 0.0f);    
  // glVertex3f( 05.0f, 02.0f, 0.0f);    
  // glVertex3f( 05.0f,-02.0f, 0.0f);    
  // glVertex3f( 02.0f,-02.0f, 0.0f); 

  // glColor3f(1.0f,0.0f,0.0f);    // Color Blue
  // glVertex3f(-02.0f, 00.0f, 0.0f);    
  // glVertex3f( 02.0f, 00.0f, 0.0f);    
  // glVertex3f(-02.0f,-10.0f, 0.0f);    
  // glVertex3f( 02.0f,-10.0f, 0.0f); 

  // glEnd();
    glLoadIdentity();

    

    glTranslatef(counter+1.0,-0.7,0.0);
    // glRotatef(5, 0, 1, 0);
    glBegin(GL_QUADS);  

    // if(counter < 0.9 && p == 0)
    //  {
    //      counter -= 0.01;
    //      if(counter >= 0.8)
    //      {
    //         p=1;
    //      }
    //  }else
    //    if(p == 1)
    //    {
    //       counter=counter+0.01;
    //         if(counter<-0.8)
    //         {
    //           p=0;
    //         }
    //     }   

        if(counter < 5.0 && p == 0)
        {
           counter+=0.01;
           if(counter > 2.5)
           {
             p = 1;
           } 
        }else
             if(p == 1)
             {
                counter-=0.01;
                if(counter < -4.5)
                {
                  p = 0;
                }
             }

    
     glColor3f(1.0f,1.0f,0.0f);    
    glVertex3f( 5.0f,-0.5f,-0.5f);  
    glVertex3f(-5.0f,-0.5f,-0.5f);  
    glVertex3f(-5.0f, 0.0f,-0.5f);    
    glVertex3f( 5.0f, 0.0f,-0.5f);    
    
    
    //  glColor3f(0.0f,1.0f,1.0f);    
    // glVertex3f(-5.0f, 0.0f, 0.0f); 
    // glVertex3f(-4.0f, 0.0f, 0.0f);    
    // glVertex3f(-4.0f, 2.0f, 0.0f);    
    // glVertex3f(-5.0f, 2.0f, 0.0f);  
    

    //  glColor3f(0.0f,1.0f,1.0f);    
    // glVertex3f( 5.0f, 0.0f, 0.0f);   
    // glVertex3f( 4.0f, 0.0f, 0.0f);   
    // glVertex3f( 4.0f, 2.0f, 0.0f);   
    // glVertex3f( 5.0f, 2.0f, 0.0f); 

  glEnd();
    

  
   glTranslatef(0.0,0.0,0.0);
      
   glBegin(GL_TRIANGLES);


    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.0, 0.5, 0.0);

   glEnd();

   glTranslatef(0.0,0.0,0.0);
      
   glBegin(GL_TRIANGLES);


    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, -0.5, 0.0);
    glVertex3f(2.0, -0.5, 0.0);
    glVertex3f(1.5, 0.5, 0.0);

   glEnd();


   glTranslatef(0.0,0.0,0.0);
      
   glBegin(GL_TRIANGLES);


    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(2.5, -0.5, 0.0);
    glVertex3f(3.5, -0.5, 0.0);
    glVertex3f(3.0, 0.5, 0.0);

   glEnd();


   glTranslatef(-2.0,0.0,0.0);           
      
   glBegin(GL_TRIANGLES);


    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.0, 0.5, 0.0);

   glEnd();
    
   

  vector <pthread_t> balls(num_balls); // create n threads, one for each ball

  vector <int> bRet(num_balls); // to store values returned by each thread

  // pthread_barrier_init(&barrier, 0, num_balls);

  // check for ball to ball collsions and update velocities
  // also makes sure that initially no two balls are generated at same place
  for(int i = 0 ; i < num_balls ; i ++){
    for (int j = i+1; j < num_balls; j++){
      controlBallBall(b[i], b[j]);
    }
  }

  for(int i = 0 ; i < num_balls ; i ++){
    bRet[i] = pthread_create(&balls[i], NULL, &controlBallWall, (void*)b[i]); // create a thread
    // controlBallWall checks for ball to wall collisions and updates the coordinates

    pthread_join(balls[i], NULL);

  }
  // pthread_barrier_destroy(&barrier);

  for(int i = 0 ; i < num_balls ; i++){
    drawBall(b[i]);
  }


  glutSwapBuffers();
}
