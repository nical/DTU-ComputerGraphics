/*02561-05-01 */

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define EDGE 3.0

void init (void);
void display (void);
void reshape (int w, int h);
void processSpecialKeys(int key, int xx, int yy);

float cam_x, cam_y, cam_z;

int main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB);
	glutInitWindowSize (500,500);
	glutInitWindowPosition (100,100);

	glutCreateWindow ("Shadows 002");
  cam_x = 10;
  cam_y = 10;
  cam_z = 5;

	init (); 
  glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutMainLoop ();

}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			cam_x -= 1;
			break;
		case GLUT_KEY_RIGHT :
			cam_x += 1;
      break;
		case GLUT_KEY_UP :
			cam_y += 1;
			break;
		case GLUT_KEY_DOWN :
			cam_y -= 1;
			break;
	}
}

void init (void)
{
	glClearColor (1.,1.,1.,1.);
	glShadeModel (GL_SMOOTH);
	glEnable (GL_DEPTH_TEST);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void myShadowMatrix(float ground[4], float light[4]) {
    
    float  dot;
    float  shadowMat[4][4];

    dot = ground[0] * light[0] +
          ground[1] * light[1] +
          ground[2] * light[2] +
          ground[3] * light[3];
    
    shadowMat[0][0] = dot - light[0] * ground[0];
    shadowMat[1][0] = 0.0 - light[0] * ground[1];
    shadowMat[2][0] = 0.0 - light[0] * ground[2];
    shadowMat[3][0] = 0.0 - light[0] * ground[3];
    
    shadowMat[0][1] = 0.0 - light[1] * ground[0];
    shadowMat[1][1] = dot - light[1] * ground[1];
    shadowMat[2][1] = 0.0 - light[1] * ground[2];
    shadowMat[3][1] = 0.0 - light[1] * ground[3];
    
    shadowMat[0][2] = 0.0 - light[2] * ground[0];
    shadowMat[1][2] = 0.0 - light[2] * ground[1];
    shadowMat[2][2] = dot - light[2] * ground[2];
    shadowMat[3][2] = 0.0 - light[2] * ground[3];
    
    shadowMat[0][3] = 0.0 - light[3] * ground[0];
    shadowMat[1][3] = 0.0 - light[3] * ground[1];
    shadowMat[2][3] = 0.0 - light[3] * ground[2];
    shadowMat[3][3] = dot - light[3] * ground[3];

    glMultMatrixf((const GLfloat*)shadowMat);
}

void display (void)
{
  GLfloat quad[][3] = {
    3, 0, 3,
    3, 0, 0,
    3, 3, 0,
    3, 3, 3
  };

  GLfloat plane[] = {
    1, 0, 0, 1
  };

  GLfloat lightPos[] = {
    10, 2, 0, 1
  };

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLightfv (GL_LIGHT0, GL_POSITION, lightPos);
  
  /*glPushMatrix();
  glTranslatef(0, 7, 0);
  glColor4f (0, 1, 0, 1);
  glutWireSphere (1, 10, 10);
  glPopMatrix();*/

  glNormal3f(0, 1, 0);

  glBegin (GL_LINES);
	  
    glColor4f (1, 0, 0, 1);
    
    glVertex3f (0, 0, 0);
    glVertex3f (10, 0, 0);

    glColor4f (0, 1, 0, 1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 10, 0);

    glColor4f (0, 0, 1, 1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, 10);

  glEnd();

  glPushMatrix();

  glTranslatef (EDGE/2., EDGE/2., EDGE/2.);
  glColor4f (1, 0, 0, 1);

  glutSolidCube(EDGE);

  glPopMatrix();

  glDisable (GL_LIGHT0);

  glBegin(GL_LINES);
    glColor3f (0, 1, 0);

    glVertex3f (-4, 10, 10);
    glVertex3f (-4, 10, -10);

    glVertex3f (-4, 10, -10);
    glVertex3f (-4, -10, -10);
    
    glVertex3f (-4, -10, -10);
    glVertex3f (-4, -10, 10);
    
    glVertex3f (-4, -10, 10);
    glVertex3f (-4, 10, 10);
    
    glVertex3f (-4, -10, -10);
    glVertex3f (-4, 10, 10);
    
    glVertex3f (-4, 10, -10);
    glVertex3f (-4, -10, 10);
  glEnd();

  glEnable(GL_LIGHT0);

  glPushMatrix();

  myShadowMatrix(plane, lightPos);

  glDisable(GL_LIGHT0);
 
  glTranslatef (EDGE/2., EDGE/2., EDGE/2.);
  glColor4f (0.4, 0.4, 0.4, 1);
  
  glutSolidCube(EDGE);

	/*glBegin (GL_POLYGON);

	  glVertex3fv (quad[0]);
	  glVertex3fv (quad[1]);
	  glVertex3fv (quad[2]);
	  glVertex3fv (quad[3]);
	
  glEnd ();*/

  glPopMatrix();

  glEnable (GL_LIGHT0);

	glFlush ();
}


void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (90., (GLfloat) w / (GLfloat) h, 4., 50.);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
  /*  The camera is positioned in [20, 10, 0] and is pointing toward [0,
   *  10, 0], while the up vector is toward [0, 0, 1]
   */
  gluLookAt (cam_x, cam_y, cam_z, 0., 0., 0., 0., 1., 0.);

}
