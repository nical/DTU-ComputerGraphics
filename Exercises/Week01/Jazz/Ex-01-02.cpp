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


void Display (void){
	
	float V[][2] ={
 		-5.,-5.,
		-5., 5.,
		 8., 5.,
		 8.,-5.
	};

  float triangle[3][2] = {
    2, 2,
    5, 2,
    3.5, 5,
  };

	glClear (GL_COLOR_BUFFER_BIT);
	 
  //  We save the current translation matrix, which is in [0, 0, 0]
  glPushMatrix ();

  //  All right.  Here's the deal. I've done this since I needed to rotate
  //  the rectangle on the centre of the tirangle (if I didn't get the
  //  assignment wrong), so I have to add to the triangle's vector the
  //  position of its centre.
  glTranslatef ((6. + 3.5), (7. + 3.5), 0.);
  glRotatef (45., 0., 0., 1.);
  //  After the rotation I get back to the centre of the scene, mantaining
  //  the rotation
  glTranslatef (-8., -10.5, 0.);
  //  Draw the rectangle
  glColor3f (1., 1., 0.);
  glBegin (GL_POLYGON);
		glVertex2fv (V[0]);
		glVertex2fv (V[1]);
		glVertex2fv (V[2]);
		glVertex2fv (V[3]);
	glEnd ();

  glColor3f (0., 0.5, 1.);
  glBegin (GL_LINES);
    glVertex2f (-10., 0.);
    glVertex2f (10., 0.);
    glVertex2f (0, 7.5);
    glVertex2f (0, -7.5);
  glEnd ();

  //  And then, restore the transform matrix
  glPopMatrix();
  glPushMatrix();
   
  //  Shift the drawing origin by the vector [6, 7, 0]
  glTranslatef (6., 7., 0.);

  /*  Ok, this looks nice :3
   *  We'd use this: 
   *    glColor3f (1., 0., 0.);
   *  to draw the triangle all red. But since now we want the triangle to
   *  be shaded, we are going to give every single vertix a different
   *  colour.
   */
  glBegin (GL_TRIANGLES);
    glColor3f (1., 0., 0.);
    glVertex2fv (triangle[0]);
    
    glColor3f (0., 1., 0.);
    glVertex2fv (triangle[1]);

    glColor3f (0., 0., 1.);
    glVertex2fv (triangle[2]);
  glEnd ();

  //  Let's restore the matrix for the next drawing.
  glPopMatrix ();

	glFlush ();
}

void Reshape (int w, int h){

	glViewport (0., 0., w, h);
	glClearColor (0., 0., 0., 0.);
	glColor3f (1., 1., 0.);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (-15., 15., -10., 15.);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}
