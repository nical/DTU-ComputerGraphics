/*  line.c    */

/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */


/* illustrates rubberband line drawing */

#include <GL/glut.h>

int ww;
float xm, ym, xmm, ymm;
int first = 0;

void init()
{
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glEnable(GL_COLOR_LOGIC_OP); 
	glLogicOp(GL_COPY);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glRectf(0.25, 0.25, 0.75, 0.75);
	glLogicOp(GL_XOR);
	glColor3f(1.0, 1.0, 0.0);
	glFlush();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0,  1.0, 0.0,  1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int btn, int state, int x, int y)
{

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		switch(first)
		{
		case 0: 
			xm = x/500.;
			ym = (500-y)/500.;
			first = 1;
			break;
		case 1:
			xmm = x/500.0;
			ymm = (500-y)/500.0;
			glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
			glEnd();
			glFlush();
			first = 2;
			break;
		case 2:
			glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
			glEnd();
			glFlush();
			xmm = x/500.0;
			ymm = (500-y)/500.0;
			glBegin(GL_LINES);
			glVertex2f(xm, ym);
			glVertex2f(xmm, ymm);
			glEnd();
			glFlush();
			break;
		}
	}
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
	{
		glLogicOp(GL_COPY);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex2f(xm, ym);
		glVertex2f(xmm, ymm);
		glEnd();
		glFlush();
		first = 0;
		glLogicOp(GL_XOR);
		glColor3f(0.0, 1.0, 0.0);
	}
}


int main(int argc, char** argv)
{

/* Initialize mode and open a window in upper left corner of screen */
/* Window title is name of program (arg[0]) */

	glutInit(&argc,argv); 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0); 
	glutCreateWindow("rubberband");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();

}

