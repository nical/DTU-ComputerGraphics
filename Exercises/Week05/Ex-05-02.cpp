/*02561-05-01 */

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void init (void);
void display (void);
void reshape (int w, int h);

int main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB);
	glutInitWindowSize (500,500);
	glutInitWindowPosition (100,100);

	glutCreateWindow ("Second Excercise");

	init (); 
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutMainLoop ();

}

void init (void)
{
	
  glClearColor (1.,1.,1.,1.);
	glShadeModel (GL_FLAT);
	glEnable (GL_DEPTH_TEST);

  
}

void display (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glColor3f (1., 0., 0.);

	glBegin (GL_LINES);
	glVertex3f (0., 0., 0.);
	glVertex3f  (15., 0., 0.);
	glEnd ();

	glBegin (GL_LINES);
	glVertex3f (0., 0., 0.);
	glVertex3f  (0., 15., 0.);
	glEnd ();

	glColor3f (0., 1., 0.);

	glBegin (GL_POLYGON);

	glVertex3f (13., 13, 13);
	glVertex3f (13., -13, 13);
	glVertex3f (13., -13, -13);
	glVertex3f (13., 13, -13);
	glEnd ();

	glColor3f (0., 1., 1.);

	glutSolidCube (6);

	glFlush ();
}


void reshape (int w, int h)
{
  GLdouble planeEqn[4] = {0, 1, 0, 0};
	
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (90., (GLfloat) w / (GLfloat) h, 4., 50.);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
  /*  The camera is positioned in [20, 10, 0] and is pointing toward [0,
   *  10, 0], while the up vector is toward [0, 0, 1]
   */
  gluLookAt (20., 20., 20., 0., 10., 0., 0., 0., 1.);

  //  We are going to do this here to use the World Coordinates instead of
  //  the Viewport coordinates
  glClipPlane (GL_CLIP_PLANE0, planeEqn);
  glEnable (GL_CLIP_PLANE0);
}
