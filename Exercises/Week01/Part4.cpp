//1.2
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
	glutInitWindowSize (210*2, 297*2);
	glutInitWindowPosition (10, 10);
	glutCreateWindow ("Week 1 - Part 4");
	
	glutDisplayFunc (Display);
	glutReshapeFunc (Reshape);
    
    Init();
	glutMainLoop ();
	return 0;
}


void Init (void) {

	glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f (1.0, 1.0, 0.0);
	glShadeModel (GL_SMOOTH);
}

void SetupProjection()
{
    glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, 21.0, 29.7, 0.0);
	//gluOrtho2D (0.0, 0.0, 1.0, 1.0);
}

void SetupViewer()
{
    glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void drawRect(float x, float y, float w, float h, float angle = 0.0)
{
    glTranslatef( x , y, 0.0 );
    glScalef( w, h, 0.0 );
    glRotatef( angle, 0.0, 0.0, 1.0 );
    
    glBegin( GL_POLYGON );
        glVertex2f(0.0,0.0);
        glVertex2f(1.0,0.0);
        glVertex2f(1.0,1.0);
        glVertex2f(0.0,1.0);
    glEnd();

    glLoadIdentity();
}

void grey(float intensity)
{
    glColor3f(intensity,intensity,intensity);
}

void Display (void){

    
	glClear (GL_COLOR_BUFFER_BIT);

    glLoadIdentity ();

    grey(0.91);
    drawRect(1.0 ,1.0 ,3.8 ,3.8);
                               
    grey(0.95);                
    drawRect(5.0 ,1.0 ,3.8 ,1.8);
                               
    grey(0.88);                
    drawRect(9.0, 1.0, 0.8, 0.8);
                               
    grey(0.97);                 
    drawRect(5.0, 3.0, 1.8, 1.8);
                               
    grey(0.9);                 
    drawRect(1.0, 5.0, 0.8, 0.8);
    


    grey(0.9);
    drawRect(18.0, 1.0, 1.8, 1.8);

    grey(0.95);
    drawRect(17.0, 1.0, 0.8, 0.8);

    grey(0.97);
    drawRect(19.0, 3.0, 0.8, 0.8);



    grey(0.92);
    drawRect(18.0, 26.7, 1.8, 1.8);

    grey(0.96);
    drawRect(1.0, 27.7, 16.8, 0.8);

    
	glFlush ();
}

void Reshape (int w, int h){

	glViewport (0.0, 0.0, w, h);
    
	SetupProjection();
	SetupViewer();
    Init();
}

