/*Appendix 3  -  02561-01-03-2011-a3
*  Tea pot
*
*
*/

#include <GL/glut.h>

int width = 500;
int height = 500;


void display() {
  
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,1.0,0.0);   
    
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  
  glTranslatef(width/2,height/2,0);
  glRotatef( 25, 1, 0, 0 );
  
  glutWireTeapot(width/4);
  glFlush();  
}


void reshape(int w, int h)  {         

  width = w;
  height = h;

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1000, 1000 );

  glViewport(0, 0, width, height);  
}


int main (int argc, char **argv){

  glutInit (&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGB);    
  
  glutCreateWindow("The Utah Teapot (modeled by Martin Newell in 1975)");  

  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

 // glutShowWindow();   
  glutMainLoop();

  return 0;
}