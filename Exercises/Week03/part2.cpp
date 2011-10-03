
/*	02501-03-02.cpp (= OGLPG Example 8.1 material.c)
 * This program demonstrates the use of the GL lighting model.
 * Several objects are drawn using different material characteristics.
 * A single light source illuminates the objects.
 */

#include <stdlib.h>
#include <glut.h>

/*  Initialize z-buffer, projection matrix, light source, 
 *  and lighting model.  Do not specify a material property here.
 */
void myinit(void)
{
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };

	


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(0.0, 0.1, 0.1, 0.0);
}

/*  Draw twelve spheres in 3 rows with 4 columns.  
 *  The spheres in the first row have materials with no ambient reflection.
 *  The second row has materials with significant ambient reflection.
 *  The third row has materials with colored ambient reflection.
 *
 *  The first column has materials with blue, diffuse reflection only.
 *  The second column has blue diffuse reflection, as well as specular
 *  reflection with a low shininess exponent.
 *  The third column has blue diffuse reflection, as well as specular
 *  reflection with a high shininess exponent (a more concentrated highlight).
 *  The fourth column has materials which also include an emissive component.
 *
 *  glTranslatef() is used to move spheres to their appropriate locations.
 */

void display(void)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat arr[5][4]={*no_mat, *mat_ambient, *mat_ambient_color, *mat_diffuse, *mat_specular };
	GLfloat arr_shininess[5][1]={{0.0}, {4.0}, {16.0}, {32.0}, {100.0}};
	/*  draw sphere i
n first row, first column
 *  diffuse reflection only; no ambient or specular  
 */
	for (int a=0; a<5; a++)
	{
		for (int b=0; b<5; b++)
		{
			glPushMatrix();
			glTranslatef (-6.25 + b*2.5, 6.0-a*3.0, 0.0);
			a==0 ? glMaterialfv(GL_FRONT, GL_AMBIENT, &arr[b][0]) :glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient) ;
			a==1 ?glMaterialfv(GL_FRONT, GL_DIFFUSE, &arr[b][0]) : glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			a==2 ? glMaterialfv(GL_FRONT, GL_SPECULAR, &arr[b][0]) :glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			a==3? glMaterialfv(GL_FRONT, GL_SHININESS, &arr_shininess[b][0] ) :glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
			a==4? glMaterialfv(GL_FRONT, GL_EMISSION, &arr[b][0]) : glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glutSolidSphere(1.0, 16, 16);
			glPopMatrix();
		}
	}
	glFlush();

}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  
	glOrtho (-8.0, 6.0, -7.0, 7.0, -10.0, 10.0);
   
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 450);
    glutCreateWindow(argv[0]);
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}

