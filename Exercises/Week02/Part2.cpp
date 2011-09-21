/* 02561-02-00-2011.cpp*/

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
        glutCreateWindow ("Week 2 - Part 2");
        initgl ();
        glutDisplayFunc (display);
        glutReshapeFunc (reshape);
        glutMainLoop ();
        return 0;
}

void setupProjection()
{
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        glOrtho (-6.0, 6.0, -6.0, 6.0, -6.0, 6.0);
        
}

void setupViewer()
{
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();

        // first set the z axis to point upward
        glRotatef( -90, 1, 0, 0 );

    
        glRotatef( 45, 1, 0, 0 );
        glRotatef( 45, 0, 0, 1 );

        // This could do it but we'd like the axis to face us
        // instead of looking away so just one more rotation
        glRotatef( 180, 0, 0, 1 );
}

void initgl (void) {
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glShadeModel (GL_FLAT);
		setupProjection();
		setupViewer();
        
}

void reshape (int w, int h) {
        glViewport (0, 0, (GLsizei) w, (GLsizei) h);
        setupProjection();
		setupViewer();
}


void display (void) {
                
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f (1.0,1.0,1.0);

        axis();
        
        glPushMatrix();        
            glTranslatef(0.5,0.5,0.5);
            glutWireCube (1.0);
        glPopMatrix();
        
        glFlush ();
        
}


void axis (void) {
        /*Plot part of axis and an auxiliary line*/
        GLfloat v0[]= {0.0, 0.0, 0.0};
        GLfloat vx[]= {4.0, 0.0, 0.0};
        GLfloat vy[]= {0.0, 4.0, 0.0};
        GLfloat vz[]= {0.0, 0.0, 4.0};

        GLfloat v0x1[] = {1.0, 0.0, 0.0};
        GLfloat vyx1[] = {1.0, 3.0, 0.0};
        
        glPushAttrib(GL_CURRENT_BIT);
        glColor3f (1.0, 0.0, 0.0);
        glBegin (GL_LINES);
                glVertex3fv (v0);
                glVertex3fv (vx);
        glEnd ();
        glColor3f (0.0, 1.0, 0.0);
        glBegin (GL_LINES);
                glVertex3fv (v0);
                glVertex3fv (vy);
        glEnd ();
        glColor3f (0.0, 0.0, 1.0);
        glBegin (GL_LINES);
                glVertex3fv (v0);
                glVertex3fv (vz);
        glEnd ();
      /*  
        glBegin (GL_LINES);
                glVertex3fv (v0x1);
                glVertex3fv (vyx1);
        glEnd ();
      */ 
        glPopAttrib();
}
