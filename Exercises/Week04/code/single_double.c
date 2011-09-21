/*
 *  double.c
 *  This program demonstrates double buffering for 
 *  flicker-free animation.  The left and middle mouse
 *  buttons start and stop the spinning motion of the square.
 */

/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */

#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0;
    int singleb, doubleb;

void displayd(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glRectf (-25.0, -25.0, 25.0, 25.0);

    glutSwapBuffers ();
}

void displays(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glRectf (-25.0, -25.0, 25.0, 25.0);

    glFlush();
}

void spinDisplay (void)
{
    spin = spin + 2.0;
    if (spin > 360.0)
	spin = spin - 360.0;
	glutSetWindow(singleb);
	glLoadIdentity();
    glRotatef (spin, 0.0, 0.0, 1.0);
    glutPostRedisplay(); 
	glutSetWindow(doubleb);
	glLoadIdentity();
    glRotatef (spin, 0.0, 0.0, 1.0);
    glutPostRedisplay();
}

void myinit (void)
{
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glColor3f (1.0, 1.0, 1.0);
    glShadeModel (GL_FLAT);
}

void mouse(int btn, int state, int x, int y)
{
if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)  glutIdleFunc(spinDisplay);
if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)   glutIdleFunc(NULL);
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) 
	glOrtho (-50.0, 50.0, -50.0*(GLfloat)h/(GLfloat)w, 
	    50.0*(GLfloat)h/(GLfloat)w, -1.0, 1.0);
    else 
	glOrtho (-50.0*(GLfloat)w/(GLfloat)h, 
	    50.0*(GLfloat)w/(GLfloat)h, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{

	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	singleb=glutCreateWindow("single buffered");
    myinit ();
	glutDisplayFunc(displays); 
    glutReshapeFunc (myReshape);
    glutIdleFunc (spinDisplay);
    glutMouseFunc (mouse);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	doubleb=glutCreateWindow("double buffered");
    myinit ();
	glutDisplayFunc(displayd);
    glutReshapeFunc (myReshape);
    glutIdleFunc (spinDisplay);
    glutMouseFunc (mouse);

	glutMainLoop();

}

