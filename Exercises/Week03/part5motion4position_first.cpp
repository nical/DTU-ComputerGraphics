
/*	02501-03-03.cpp  (= OGLPG Exemple 5.6 movelight.c)
 *
 *  This program demonstrates when to issue lighting and
 *  transformation commands to render a model with a light
 *  which is moved by a modeling transformation (rotate or
 *  translate).  The light position is reset after the modeling
 *  transformation is called.  The eye position does not change.
 *
 *  A sphere is drawn using a grey material characteristic.
 *  A single light source illuminates the object.
 *
 *  Interaction:  pressing the left mouse button alters
 *  the modeling transformation (x rotation) by 30 degrees.
 *  The scene is then redrawn with the light in a new position.
 */

#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include <iostream>
#define MOTION 4
#define M_PI       3.14159265358979323846


static int spin = 0;
static float eye_poss= 0.0;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

/*  Here is where the light position is reset after the modeling
 *  transformation (glRotated) is called.  This places the
 *  light at a new position in world coordinates.  The cube
 *  represents the position of the light.
 */
void display(void)
{
   

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix ();
   glLoadIdentity();
   glTranslated (0.0, 1.5, 0.0);
    glColor3f (0.0, 1.0, 1.0);
	glDisable (GL_LIGHTING);
	gluLookAt (0.0, 0.0, 5.0 , 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glutWireCube (0.1);  
	glLoadIdentity();
   if(MOTION==1 || MOTION==3) gluLookAt (5.0* cos(eye_poss), 5.0*cos(eye_poss), 5.0*sin(eye_poss) , 0.0, 0.0, 0.0, 0.0, sin(eye_poss), -cos(eye_poss));
   else if(MOTION==4) gluLookAt (0.0, 5.0*cos(eye_poss), 5.0*sin(eye_poss) , 0.0, 0.0, 0.0, 0.0, sin(eye_poss), -cos(eye_poss));
   else gluLookAt (0.0, 0.0, 5.0 , 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   //std::cout<<sin(eye_poss)<<std::endl;
   glPushMatrix ();
   glRotated ((GLdouble) spin, 1.0, 0.0, 0.0);
   

   //glTranslated (0.0, 0.0, 1.5);
   //glDisable (GL_LIGHTING);
   glColor3f (0.0, 1.0, 1.0);
   //glutWireCube (0.1);
   glEnable (GL_LIGHTING);
   glPopMatrix ();

   glutSolidTorus (0.275, 0.85, 8, 15);
   glPopMatrix ();
   glFlush ();
}

void reshape (int w, int h)
{
   
		GLfloat position[] = { 0.0, 1.5,0.0, 1.0 };
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   //glRotated((GLdouble) eye_poss, 1.0, 0.0, 0.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
    
	   glLightfv (GL_LIGHT0, GL_POSITION, position);
}

/* ARGSUSED2 */
void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            spin = (spin + 30) % 360;
            glutPostRedisplay();
         }
         break;
	  case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN) {
            eye_poss = (eye_poss + 0.2);
		//	glFlush();
            glutPostRedisplay();
         }
         break;
      default:
         break;
   }
}

/* ARGSUSED1 */
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void timer(int value)
{
	switch(MOTION){
	case 1:
		spin = (spin + 2) % 360;
        glutPostRedisplay();
		break;

	case 2:
		eye_poss +=0.01;
		glutPostRedisplay();
		break;

	case 3:
		eye_poss +=0.01;
		spin = (spin + 2) % 360;
		glutPostRedisplay();
		break;

	case 4:
		eye_poss +=0.01;
		//spin = (spin + 2) % 360;
		//eye_poss =spin/360.0 * 2 * 3.14;
		glutPostRedisplay();
		break;
	default:
		break;
	
	}
	glutTimerFunc(40, timer, 0);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(40, timer, 0);
   glutMainLoop();
   return 0;
}