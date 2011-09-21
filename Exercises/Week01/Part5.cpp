#include <GL/glut.h>
#include <math.h>
void Init (void);
void Display (void);
void Reshape (int w, int h);

int main (int argc, char **argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (10, 10);
	glutCreateWindow ("Week 1 - Part 5");
	
	glutDisplayFunc (Display);

	glutReshapeFunc (Reshape);
	glutMainLoop ();
	return 0;
}


void Init (void) {

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glColor3f (1.0, 1.0, 0.0);
	glShadeModel (GL_SMOOTH);
}

void DrawCircle(float cx, float cy, float r, int num_segments) 
{ 
	glBegin(GL_LINE_LOOP); 
	for(int i = 0; i < num_segments; i++) 
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); 

		float x = r * cosf(theta); 
		float y = r * sinf(theta); 

		glVertex2f(x + cx, y + cy);//output vertex 

	} 
	glEnd(); 
}

void DrawCircleFilled(float cx, float cy, float r, int num_segments) 
{
    glClear( GL_COLOR_BUFFER_BIT );
    
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(cx, cy);
	glColor3f(1.0, 1.0, 0.0);
	for(int ii = 0; ii < num_segments+1; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	} 
	glEnd(); 
}

void Display (void){
	DrawCircleFilled(0, 0, 10, 100);
	glFlush ();
}

void Reshape (int w, int h){

	glViewport (0.0, 0.0, w, h);
	glClearColor (0.0, 0.0, 0.0, 0.);
	glColor3f (1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (-15.0*w/h, 15.0*w/h, -15.0, 15.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}
