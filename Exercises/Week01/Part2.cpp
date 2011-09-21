//1.2
/*Appendix A2  -  02561-01-02-2011
*
* The program draws a rectangle. 
* 	
* The program is a kind of template for simple 2D drawing.
*/

#include <GL/glut.h>

void Init (void);
void Display (void);
void Reshape (int w, int h);

int main (int argc, char **argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 500);
	glutInitWindowPosition (10, 10);
	glutCreateWindow ("Week 1 - Part 2");
	
	glutDisplayFunc (Display);

	glutReshapeFunc (Reshape);
	glutMainLoop ();
	return 0;
}


void Init (void) {

	glClearColor (0., 0., 0., 0.);
	glColor3f (1., 1., 0.);
	glShadeModel (GL_SMOOTH);
}

void SetupProjection()
{
    glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (-15., 15., -10., 15.);
}

void SetupViewer()
{
    glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void Display (void){
	
	float V[][2] ={
 		-5.,-5.,
		-5., 5.,
		 8., 5.,
		 8.,-5.
	};


	glClear (GL_COLOR_BUFFER_BIT);

    glLoadIdentity ();
	glTranslated(1.5,0,0);
	glRotated(45, 0, 0, 1);
	glTranslated(-1.5,0,0);
	glBegin (GL_POLYGON);
		glVertex2fv (V[0]);
		glVertex2fv (V[1]);
		glVertex2fv (V[2]);
		glVertex2fv (V[3]);
	glEnd ();

	glLoadIdentity();
	glTranslated(6,7,0);
	glBegin(GL_TRIANGLES);
		glColor3f (1.0, 0.0, 0.0);
		glVertex2f(2.0, 2.0);
		glColor3f (0.0, 1.0, 0.0);
		glVertex2f(5.0, 2.0);
		glColor3f (0.0, 0.0, 1.0);
		glVertex2f(3.5,5);
	glEnd();
    
	glFlush ();
}

void Reshape (int w, int h){

	glViewport (0.0, 0.0, w, h);
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glColor3f (1.0, 1.0, 0.0);
	
	SetupProjection();
	SetupViewer();
}

