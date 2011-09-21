/* Appendix 7  - 02561-01-07-2011-a7.cpp
*
*
*/

#include <GL/glut.h>

void initgl(void);

void display (void);
void axis (void);
void reshape (int w, int h);

int main (int argc, char** argv) {
        
        glutInit (&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
        glutInitWindowSize (500, 500);
        glutInitWindowPosition (100, 100);
        glutCreateWindow ("Week 1 - Part 8");
        initgl ();
        glutDisplayFunc (display);
        glutReshapeFunc (reshape);
        glutMainLoop ();
        return 0;
}


void initgl (void) {
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glShadeModel (GL_FLAT);    
		
}

void reshape (int w, int h) {
        glViewport (0, 0, (GLsizei) w, (GLsizei) h);
        //
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluPerspective(45.0, (float)w/(float)h, 0, 1000); 
        //
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();        		
		gluLookAt(20.0, 5.0, 5.0
                 , 0.0, 5.0, 0.0
                 , 0.0, 1.0 ,0.0);


        glRotatef( 35.0, 0.0, 1.0, 0.0);
        // translate the cube upward to center it
		glTranslatef( 0.0, 5.0, 0.0 );
}


void display (void) {
                
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f (1.0,1.0,1.0);
      
		glutWireCube (10.0);
             
        axis();
        glFlush ();
        
}


void axis (void) {
        /*Plot part of axis and an auxiliary line*/
        GLfloat v0[] = {0.0, 0.0, 0.0};
        GLfloat vx[] = {4.0, 0.0, 0.0};
        GLfloat vy[] = {0.0, 4.0, 0.0};
        GLfloat vz[] = {0.0, 0.0, 4.0};

        GLfloat v0x1[] = {1.0, 0.0, 0.0};
        GLfloat vyx1[] = {1.0, 3.0, 0.0};
        
        glPushAttrib(GL_CURRENT_BIT);
        glColor3f (1.0, 0.0, 0.0);
        glBegin (GL_LINES);
                glVertex3fv (v0);
                glVertex3fv (vx);
        glEnd ();
        
        glBegin (GL_LINES);
                glVertex3fv (v0);
                glVertex3fv (vy);
        glEnd ();
        
        glBegin (GL_LINES);
                glVertex3fv (v0);
                glVertex3fv (vz);
        glEnd ();
        
        glBegin (GL_LINES);
                glVertex3fv (v0x1);
                glVertex3fv (vyx1);
        glEnd ();
        glPopAttrib();
}
