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
	//  Initialise OpenGL
  glutInit (&argc, argv);
  //  Set the various flags for OpenGL, like Signle Buffered and... RGBA
  //  Mode
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	//  Set Windows properties.
  glutInitWindowSize (700, 500);
	glutInitWindowPosition (10, 10);
	glutCreateWindow ("Hello World");

	//  With this we specify which colour we use when we clear the colour
  //  buffers. I think that this is used every time we call glClear, look
  //  into the Display funcion
  glClearColor (0., 0., 0., 0.);

  //  This is the colour we'll use when we'll draw (until we change it
  //  using again glColor3f in GL_MODELVIEW, I think)
	glColor3f (1., 1., 0.);

  //  After this all the subsequent Matrix actions are applied to the
  //  Projection Matrix Stack
  glMatrixMode (GL_PROJECTION);
  //  This is to insert an Identity Matrix in the Projection Stack
  glLoadIdentity ();
  //  Then we set an orthografic viewport matrix to the stack
  gluOrtho2D (-10., 10., -10., 10.);
  // And, with this, we get back to the ModelView Matrix Stack (To
  // manipulate the vertices, not the projection or the textures)
  glMatrixMode (GL_MODELVIEW);

  //  Which is the function to call when we have to display something
	glutDisplayFunc (Display);

  //  Let's go!
	glutMainLoop ();
	return 0;
}


void Display (void){
	
	//  Clear the view (We want to redraw the scene. It's not useful now,
  //  since nothing moves, but we don't want to have all the old stuff that
  //  was drawn
	glClear (GL_COLOR_BUFFER_BIT);

  //  Begin the listing of primitives that will form a convex polygon
	glBegin (GL_POLYGON);
		glVertex2f (-5.,-5.);
		glVertex2f (-5.,5.);
		glVertex2f (8.,5.);
		glVertex2f (8.,-5);
	glEnd ();

  //  Force Draw.
	glFlush ();
}

