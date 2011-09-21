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
	glutCreateWindow ("Week 1 - Part 1");

	glClearColor (0., 0., 0., 0.);
	glColor3f (1., 1., 0.);

    // Enter the Projection mode which means that next opengl matrix operations
    // will affect the projection matrix.
    glMatrixMode (GL_PROJECTION);
    // Reset the matrix (the projection matrix as mentionned above).
    glLoadIdentity ();
    // Transform the projection matrix into a orthographic 2d projection.
    // This means a matrix is computed internally and this transformation does
    // not take perspective into account (it just projects vertices on the view
    // plane perpendicularly). The projection matrix is then multiplied by this
    // matrix (which is why we nedd to reset it before). 
    gluOrtho2D (-10., 10., -10., 10.);
    // Enter the Projection mode which means that next opengl matrix operations
    // will affect the modelview matrix.
    glMatrixMode (GL_MODELVIEW);

		
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

