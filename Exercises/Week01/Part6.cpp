/*Appendix 3  -  02561-01-03-2011-a3
*  Tea pot
*
*
*/

#include <GL/glut.h>
#include <math.h>
//#include <iostream>
#define PI 3.1413
int width = 500;
int height = 500;


void drawRectangle(float x, float y){
	glBegin(GL_POLYGON);
		glVertex2f (0.,0.);
		glVertex2f (0.,y);
		glVertex2f (x ,y);
		glVertex2f (x,0.);
	glEnd ();
}

void drawCircle(float r, int points, GLenum type=GL_TRIANGLE_FAN)
{
	glBegin(type);
	if(type==GL_TRIANGLE_FAN) glVertex3f(0.,0., 0.);
	float arg;
	
	for(float a=0; a<points; a++){
		arg=float(a/points*2*PI);
		glVertex3f(r*cos(arg), r*sin(arg), 0.);
	}
	glVertex3f(r, 0., 0.);
	glEnd();
	
}

void drawSmile(float size)
{
	glBegin(GL_LINES);
	glVertex2f(-size/2, size/2);
	glVertex2f(-size/2, -size/2);
	glVertex2f(size/2, size/2);
	glVertex2f(size/2, -size/2);
	glEnd();
	glBegin(GL_LINE_STRIP);
	
	for(float a=-PI/10; a>-3/2*PI; a=a-PI/10){
	
		glVertex3f(2*size*cos(a), 2*size*sin(a), 0.);
	}
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
   
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glColor3f(1.0, 0.0, 1.0);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0., 0., 0.);
  drawSmile(width/10);
  //glutWireTeapot(width/10);
  glPopMatrix();
  glFlush();
}


void reshape(int w, int h)  {         

  width = w;
  height = h;

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  glOrtho(-width/2, width/2, -height/2, height/2, -1000, 1000 );

  //glViewport(0, 0, width, height);  
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
