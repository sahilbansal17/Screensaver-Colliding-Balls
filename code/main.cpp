#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "screen.h"

// set lighting intensity and color
GLfloat AmbientLight[] = {0.2, 0.2, 0.2, 1.0};
GLfloat DiffuseLight[] = {0.8, 0.8, 0.8, 1.0};
GLfloat SpecularLight[] = {1.0, 1.0, 1.0, 1.0};
GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.01};
GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0};

// light source position
GLfloat LightPosition[] = {0.5, 0, -3.5, 0.5};

void init(void){ 
  // initialize projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // initialize clear color
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // R, G, B, Alpha
  // glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  // glDepthMask(GL_TRUE);
  // glDepthRange(0.0f, 1.0f);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH); // enable smooth shading
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // nice perspective corrections
}

void initLighting(){
  // enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  // set lighting intensity and color
  glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
  // set the light position
  glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
}

void reshape(int x, int y){
    if (y == 0 || x == 0) return;  // empty screen

    glViewport(0, 0, x, y);  // use the whole window for rendering, 0, 0 specify the lower left side   

    glMatrixMode(GL_PROJECTION);

    // angle of view: 60 degrees
    // near clipping plane distance: 1.0 // > 0 value makes sure that Depth Buffer is enabled
    // far clipping plane distance: 10.0
    glLoadIdentity();

    gluPerspective(60.0, (GLdouble)x/(GLdouble)y, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

int main(int argc, char** argv){

  int n; // number of balls

  n = stoi(argv[1]); // take argument from a.out

  initBalls(n); // initialize the properties of all the balls
  initTerrain(); // initialize the terrian objects
  glutInit(&argc, argv); // initialize glut

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // create double buffer window
 
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(SCREEN_X,SCREEN_Y);
  glutCreateWindow("ScreenSaver Colliding Balls");
  // glutFullScreen(); // make the window full screen

  initLighting();

  glutDisplayFunc(drawCube); // set rendering function

  glutReshapeFunc(reshape); // set reshape function

  glutIdleFunc(drawCube); // runs this function continuously

  init(); // post window/context creation initialization

  glutMainLoop(); // start glut main loop

  return 0;
}
