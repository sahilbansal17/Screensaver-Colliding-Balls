#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "screen.h"

void init(void){
  glClearColor(0,0,0,0);
}

void reshape(int x, int y){
    if (y == 0 || x == 0) return;  // empty screen

    glMatrixMode(GL_PROJECTION); // set a projection matrix

    glLoadIdentity();

    //Angle of view: 60 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0

    // gluPerspective(60.0,(GLdouble)x/(GLdouble)y,0.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main(int argc, char** argv){

  int n; // number of balls

  cin >> n;

  initBalls(n); // initialize the properties of all the balls

  glutInit(&argc, argv); // initialize glut

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // create double buffer window

  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(SCREEN_X,SCREEN_Y);
  glutCreateWindow("ScreenSaver Colliding Balls");

  init(); // post window/context creation initialization

  glutDisplayFunc(drawCube); // set rendering function

  glutReshapeFunc(reshape); // set reshape function

  glutIdleFunc(drawCube); // runs this function continuously

  glutMainLoop(); // start glut main loop

  return 0;
}
