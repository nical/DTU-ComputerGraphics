
/*	02501-03-02.cpp (= OGLPG Example 8.1 material.c)
 * This program demonstrates the use of the GL lighting model.
 * Several objects are drawn using different material characteristics.
 * A single light source illuminates the objects.
 */

#include <stdlib.h>
#include <GL/glut.h>

#define SLICES 128

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
    /*GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};*/

    GLfloat shininess[] = {
      0.0, 25.0, 50.0, 75.0, 100.0
    };

    GLfloat emission[][4] = {
      {0.0, 0.0, 0.0, 1.0},
      {1.0, 0.0, 0.0, 1.0},
      {0.0, 1.0, 0.0, 1.0},
      {0.0, 0.0, 1.0, 1.0},
      {0.5, 0.5, 0.5, 0.5}
    };

    GLfloat ambient[][4] = {
      {0.0, 0.0, 0.0, 1.0},
      {1.0, 0.0, 0.0, 1.0},
      {0.0, 1.0, 0.0, 1.0},
      {0.0, 0.0, 1.0, 1.0},
      {0.5, 0.5, 0.5, 0.5}
    };
    
    GLfloat diffuse[][4] = {
      {0.0, 0.0, 0.0, 1.0},
      {1.0, 0.0, 0.0, 1.0},
      {0.0, 1.0, 0.0, 1.0},
      {0.0, 0.0, 1.0, 1.0},
      {0.5, 0.5, 0.5, 0.5}
    };
    
    GLfloat specular[][4] = {
      {0.0, 0.0, 0.0, 1.0},
      {1.0, 0.0, 0.0, 1.0},
      {0.0, 1.0, 0.0, 1.0},
      {0.0, 0.0, 1.0, 1.0},
      {0.5, 0.5, 0.5, 0.5}
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint i, j;

    for (i = 0; i < 5; i++){
      

        glPushMatrix();
        glTranslatef (-3.75, (2 - i) * 3.0, 0.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[i]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[4]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess[0]);
        glMaterialfv(GL_FRONT, GL_EMISSION, emission[0]);
        glutSolidSphere(1.0, SLICES, SLICES);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef (-1.25, (2 - i) * 3.0, 0.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[i]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess[0]);
        glMaterialfv(GL_FRONT, GL_EMISSION, emission[0]);
        glutSolidSphere(1.0, SLICES, SLICES);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef (1.25, (2 - i) * 3.0, 0.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[4]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular[i]);
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess[0]);
        glMaterialfv(GL_FRONT, GL_EMISSION, emission[0]);
        glutSolidSphere(1.0, SLICES, SLICES);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef (3.75, (2 - i) * 3.0, 0.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[4]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular[4]);
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess[i]);
        glMaterialfv(GL_FRONT, GL_EMISSION, emission[0]);
        glutSolidSphere(1.0, SLICES, SLICES);
        glPopMatrix();     
        
        glPushMatrix();
        glTranslatef (6.25, (2 - i) * 3.0, 0.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[4]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess[0]);
        glMaterialfv(GL_FRONT, GL_EMISSION, emission[i]);
        glutSolidSphere(1.0, SLICES, SLICES);
        glPopMatrix();
    }
    glFlush();
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= (h * 2))
	glOrtho (-6.0, 8.0, -3.0*((GLfloat)h*2)/(GLfloat)w, 
	    4.0*((GLfloat)h*2)/(GLfloat)w, -10.0, 10.0);
    else
	glOrtho (-6.0*(GLfloat)w/((GLfloat)h*2), 
	    8.0*(GLfloat)w/((GLfloat)h*2), -3.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
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

