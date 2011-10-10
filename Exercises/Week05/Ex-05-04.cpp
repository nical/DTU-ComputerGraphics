/*  02561-05-03.cpp
 *
 *  checker.c  = oglpg9.1
 *  This program texture maps a checkerboard image onto
 *  two rectangles.  This program clamps the texture, if
 *  the texture coordinates fall outside 0.0 and 1.0.
 */
#include <GL/glut.h>

/*	Create checkerboard texture	*/
#define	checkImageWidth 64
#define	checkImageHeight 64
GLubyte checkImage[checkImageWidth][checkImageHeight][3];

void makeCheckImage(void)
{
    int i, j, c;
    
    for (i = 0; i < checkImageWidth; i++) {
	for (j = 0; j < checkImageHeight; j++) {
	    c = ((((i&0x8)==0)^((j&0x8))==0))*255;
	    checkImage[i][j][0] = (GLubyte) c;
	    checkImage[i][j][1] = (GLubyte) c;
	    checkImage[i][j][2] = (GLubyte) c;
	}
    }
}

void myinit(void)
{    
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth, 
	    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 
	    &checkImage[0][0][0]);
    
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, checkImageWidth, checkImageHeight,
    GL_RGB, GL_UNSIGNED_BYTE, &checkImage[0][0][0] ); 

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    double polygon[][3] = {
      0, 0, 0,
      10, 0, 0,
      10, 6, 0,
      5, 10, 0,
      0, 6, 0
    };

    double text[][2] = {
      0, 0,
      10, 0,
      10, 6,
      5, 10,
      0, 6
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POLYGON);
      glTexCoord2dv(text[0]); glVertex3dv(polygon[0]);
      glTexCoord2dv(text[1]); glVertex3dv(polygon[1]);
      glTexCoord2dv(text[2]); glVertex3dv(polygon[2]);
      glTexCoord2dv(text[3]); glVertex3dv(polygon[3]);
      glTexCoord2dv(text[4]); glVertex3dv(polygon[4]);
    glEnd();
    glutSwapBuffers();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0*(GLfloat)w/(GLfloat)h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-5.0, -5.0, -20);
}

int
main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("checker");
    myinit();
    glutReshapeFunc (myReshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
