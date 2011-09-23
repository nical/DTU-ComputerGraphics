/*Appendix A1  -   02561-01-01-2011-a1        
*   
*   ogl_min.cpp
*    
*   
*
*	This program draws a yellow polygon
*
*/


#include <GL/glut.h>

 
void Display (void);

int main (int argc, char **argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (700, 500);
	glutInitWindowPosition (10, 10);
	glutCreateWindow ("Hello World");

	glClearColor (0., 0., 0., 0.);
	glColor3f (1., 1., 0.);
		
	glutDisplayFunc (Display);

	glutMainLoop ();
	return 0;
}


void Display (void){
	
	
	glClear (GL_COLOR_BUFFER_BIT);

	glBegin (GL_POLYGON);
		glVertex2f (-5.,-5.);
		glVertex2f (-5.,5.);
		glVertex2f (8.,5.);
		glVertex2f (8.,-5);
	glEnd ();

	glFlush ();
}

