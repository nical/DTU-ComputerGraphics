//1.3
/*Appendix 3  -  02561-01-03-2011-a3
*  Tea pot
*
*
*/

#include <GL/glut.h>

int width = 500;
int height = 500;


void display()
{
  
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 1.0, 0.0);   
    
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  
  glTranslatef( width/2.0, height/2.0, 0.0 );
  glRotatef( 25.0, 1.0, 0.0, 0.0 );
  
  glutWireTeapot(width/4.0);
  glFlush();  
}


void reshape(int w, int h)  {         

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1000, 1000 );

  glViewport(0, 0, w, h);  
}


int main (int argc, char **argv){

  glutInit (&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGB);    
  
  glutCreateWindow("Week 1 - Part 3 - The Utah Teapot");  

  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

 // glutShowWindow();   
  glutMainLoop();

  return 0;
}
