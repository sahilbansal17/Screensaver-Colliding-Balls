#include <GL/glut.h>
#include <math.h>
#include "ball.h"
#define  pi 3.142857

int p = 0;
float counter = 0.0;
GLfloat xRotated, yRotated, zRotated;

void init(void){
  glClearColor(0,0,0,0);
}

ball b;

void DrawCube(void){

  glMatrixMode(GL_MODELVIEW);
  // clear the drawing buffer.
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0,0.0,-5.0);
  // glRotatef(xRotated,1.0,0.0,0.0);
  //  // rotation about Y axis
  //  glRotatef(yRotated,0.0,1.0,0.0);
  //  // rotation about Z axis
  //  glRotatef(zRotated,0.0,0.0,1.0);   
  // glBegin(GL_QUADS);        // Draw The Cube Using quads
  // glColor3f(0.0f,1.0f,0.0f);    // Color Blue
  // glVertex3f( 02.0f, 02.0f,-02.0f);    // Top Right Of The Quad (Top)
  // glVertex3f(-02.0f, 02.0f,-02.0f);    // Top Left Of The Quad (Top)
  // glVertex3f(-02.0f, 02.0f, 02.0f);    // Bottom Left Of The Quad (Top)
  // glVertex3f( 02.0f, 02.0f, 02.0f);    // Bottom Right Of The Quad (Top)
  // glColor3f(1.0f,1.0f,0.0f);    // Color Orange
  // glVertex3f( 02.0f,-02.0f, 02.0f);    // Top Right Of The Quad (Bottom)
  // glVertex3f(-02.0f,-02.0f, 02.0f);    // Top Left Of The Quad (Bottom)
  // glVertex3f(-02.0f,-02.0f,-02.0f);    // Bottom Left Of The Quad (Bottom)
  // glVertex3f( 02.0f,-02.0f,-02.0f);    // Bottom Right Of The Quad (Bottom)
  // glColor3f(1.0f,0.0f,0.0f);    // Color Red    
  // glVertex3f( 02.0f, 02.0f, 02.0f);    // Top Right Of The Quad (Front)
  // glVertex3f(-02.0f, 02.0f, 02.0f);    // Top Left Of The Quad (Front)
  // glVertex3f(-02.0f,-02.0f, 02.0f);    // Bottom Left Of The Quad (Front)
  // glVertex3f( 02.0f,-02.0f, 02.0f);    // Bottom Right Of The Quad (Front)
  // glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
  // glVertex3f( 02.0f,-02.0f,-02.0f);    // Top Right Of The Quad (Back)
  // glVertex3f(-02.0f,-02.0f,-02.0f);    // Top Left Of The Quad (Back)
  // glVertex3f(-02.0f, 02.0f,-02.0f);    // Bottom Left Of The Quad (Back)
  // glVertex3f( 02.0f, 02.0f,-02.0f);    // Bottom Right Of The Quad (Back)
  // glColor3f(0.0f,0.0f,1.0f);    // Color Blue
  // glVertex3f(-02.0f, 02.0f, 02.0f);    // Top Right Of The Quad (Left)
  // glVertex3f(-02.0f, 02.0f,-02.0f);    // Top Left Of The Quad (Left)
  // glVertex3f(-02.0f,-02.0f,-02.0f);    // Bottom Left Of The Quad (Left)
  // glVertex3f(-02.0f,-02.0f, 02.0f);    // Bottom Right Of The Quad (Left)
  // glColor3f(1.0f,0.0f,1.0f);    // Color Violet
  // glVertex3f( 02.0f, 02.0f,-02.0f);    // Top Right Of The Quad (Right)
  // glVertex3f( 02.0f, 02.0f, 02.0f);    // Top Left Of The Quad (Right)
  // glVertex3f( 02.0f,-02.0f, 02.0f);    // Bottom Left Of The Quad (Right)
  // glVertex3f( 02.0f,-02.0f,-02.0f);    // Bottom Right Of The Quad (Right)
  // glEnd(); 
  
  float x = b.getCenterX();
  float y = b.getCenterY();
  float z = b.getCenterZ();


  float vx = b.getVelX();
  float vy = b.getVelY();
  float vz = b.getVelZ();

  if(x <= 2 && x >= -2){
    x += vx;
  }
  if(y <= 2 && y >= -2){
    y += vy;
  }
  // z += vz;

  b.setCenterX(x);
  b.setCenterY(y);
  b.setCenterZ(z); 
  glTranslatef( x, y, z);

  b.printCenter(); 
  // if(counter<=2.0 && p==0){
  //   counter+=0.01;
  //   if(counter>=1.7){
  //     p=1;
  //   }
  // }
  // else if(p == 1){
  //   counter=counter-0.01;
  //   if(counter<=-1.7){
  //     p=0;
  //   }
  // }
  glBegin(GL_POLYGON);
  // float x, y, i;
  float r = b.getRed();
  float g = b.getGreen();
  float blu = b.getBlue();
  glColor3f(r,g,blu);
  float rad = b.getRadius();
  glutSolidSphere(rad, 50, 50);
  
  glEnd();           // End Drawing The Cube
  glutSwapBuffers();
  yRotated += 1.01;
  xRotated += 1.01;
}

void reshape(int x, int y){
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(60.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main(int argc, char** argv){

  glutInit(&argc, argv);
  //we initizlilze the glut. functions
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(500,100);
  glutCreateWindow("sahil");
  init();
  glutDisplayFunc(DrawCube);
  glutReshapeFunc(reshape);
  //Set the function for the animation.
  glutIdleFunc(DrawCube);
  glutMainLoop();
  
  return 0;
}
 
  