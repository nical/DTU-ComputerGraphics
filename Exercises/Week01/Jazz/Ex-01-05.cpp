/*
* The program draws a circle. 
* 	
*/

#include <GL/glut.h>
#include <math.h>

#define SEGS        100
#define CENTRE_X      0
#define CENTRE_Y      0
#define RADIUS      5.0

void Init (void);
void Display (void);
void Reshape (int w, int h);
void computeCircleVertices (double, double, float, double [][2], int);

int main (int argc, char **argv){
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 500);
	glutInitWindowPosition (10, 10);
	glutCreateWindow ("Hello World 2");
	
	glutDisplayFunc (Display);

  //  This is the function used when the window gets reshaped.
	glutReshapeFunc (Reshape);
	glutMainLoop ();
	return 0;
}


void Init (void) {

	glClearColor (0., 0., 0., 0.);
	glColor3f (1., 1., 0.);
	glShadeModel (GL_SMOOTH);
}

void computeCircleVertices (double x, double y, float radius, double vertices[][2], int segments_count){
  int i;
  double theta = 0;

  for (i = 0; i < segments_count; i++) {
    theta = 2.0 * M_PI * ( (double) i / segments_count);
    vertices[i][0] = ( cos(theta) * radius ) + x;
    vertices[i][1] = ( sin(theta) * radius ) + y;
  }
}

void drawAxes (float size_x, float size_y, double primary_scale, double secondary_scale) {
  int i, steps;

  glVertex2d (size_x, 0.);
  glVertex2d (-size_x, 0.);
  glVertex2d (0., size_y);
  glVertex2d (0., -size_y);

  steps = ceil(size_x / primary_scale);

  for (i = 1; i <= steps; i++) {
    glVertex2d (i * primary_scale, 0.);
    glVertex2d (i * primary_scale, 1.);
    
    glVertex2d (i * -primary_scale, 0.);
    glVertex2d (i * -primary_scale, 1.);
 }

}

void Display (void){
	
  double circle[SEGS][2];
  int i;

  computeCircleVertices (CENTRE_X, CENTRE_Y, RADIUS, circle, SEGS);

	glClear (GL_COLOR_BUFFER_BIT);
	 
  glColor3f (1., 1., 0.);
  glBegin (GL_LINE_LOOP);
		for (i = 0; i < SEGS; i++) {
		  glVertex2dv (circle[i]);
    }
	glEnd ();
/*
  glBegin (GL_LINES);
    glColor3f (0., 0.5, 1.);
    glVertex2f (15., 0.);
    glVertex2f (-15., 0.);
    glVertex2f (0., 15.);
    glVertex2f (0., -15.);
    
    glColor3f (1., 0., 0.);
    glVertex2f (RADIUS, 2.);
    glVertex2f (RADIUS, -2.);
    glVertex2f (-RADIUS, 2.);
    glVertex2f (-RADIUS, -2.);
    
    glVertex2f (2., RADIUS);
    glVertex2f (-2., RADIUS);
    glVertex2f (2., -RADIUS);
    glVertex2f (-2., -RADIUS);
    
  glEnd ();
*/
	glFlush ();
}

void Reshape (int w, int h){

	glViewport (0., 0., w, h);
	glClearColor (0., 0., 0., 0.);
	glColor3f (1., 1., 0.);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
  //  The h / w is needed to have fixed ratio. We don't want an ellipse
  //  while trying to draw a circle, right?
	gluOrtho2D (-15. , 15., -15. * (float) h / w, 15. * (float) h / w);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}
