/* 02561-11-00.cpp 	
 */

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <assert.h>

using namespace std;

GLfloat ctrlpoints [7][3] = {
	{-10.,0.,0.},
	{-10.,5.,0.},
	{-5.,5.,0.},
	{0.,10.,0.},
	{5.,5.,0.},
	{10.,5.,0.},
	{10.,0.,0.}};


float factorial(int n)
{
    float res = 1.0;
    for(int i = 1; i <= n; ++i ) res *= (float)i;
    //cout << n <<"! = "<< res << endl;
    return res;
}

template<int N>
struct vec
{
    vec()
    {
        for(int i = 0; i < N; ++i)
            values[i] = 0.0;
    }
    static const int Dimension = N;
    float values[N];
    float& operator[](int n)
    {
        return values[n];
    }
};

vec<3> vecCtrlPoints [7];

template<typename T>
T BezierCurve( T * points, int n, float t )
{
    T result;
    for(int dim = 0; dim < T::Dimension; ++dim)
    {
        std::cout << "-------" << std::endl;
        std::cout << pow(t,1) << std::endl;
        for(int i = 0; i <= n; ++i)
        {
            result[dim] += 
                  factorial(n) / (factorial(i)*factorial(n-i) )
                * pow(1-t,n-i)
                * pow(t,i)
                * points[i][dim];
        }
    }
    cout << pow(0.5, 0) << endl;
    return result;
}

template<typename T>
T CubicBezierCurve( T* points, float t )
{
    T result;
    for(int dim = 0; dim < T::Dimension; ++dim)
    {
        result[dim] = pow(1-t,3) * points[0][dim] 
            + 3*pow(1-t,2)*t*points[1][dim] 
            + 3*(1-t)*pow(t,2)*points[2][dim] 
            + pow(t,3)*points[3][dim];
    }
    return result;
}

void init(void)
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glShadeModel(GL_FLAT);

    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 3; ++j)
            vecCtrlPoints[i][j] = ctrlpoints[i][j];
    }
/*
   theNurb = gluNewNurbsRenderer ();
    
	gluNurbsProperty (theNurb, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
	gluNurbsProperty (theNurb, GLU_U_STEP, 100);
*/


}

void display(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);
  
	glLoadIdentity ();
	gluLookAt (0., 5., 1., 0., 5., 0., 0., 1., 0.);



/* The following code displays the control points as dots and line strip. */
   glPointSize(5.0);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 7; i++) 
         glVertex3fv(&ctrlpoints[i][0]);
   glEnd();


glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_STRIP);
    for (i = 0; i < 7; i++) 
    {
      glVertex3fv(&ctrlpoints[i][0]);
    }
glEnd();

    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < 42; ++i)
    {
        vec<3> p = BezierCurve(vecCtrlPoints, 4, (float)i/42.0 );
        //vec<3> p = CubicBezierCurve(vecCtrlPoints, (float)i/42.0 );
        glVertex3f(p[0],p[1],p[2]);
        assert( (float)i/42.0 <= 1.0 );
    }
    glEnd();

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      gluOrtho2D (-12.0, 12.0, -12.0*(GLfloat)h/(GLfloat)w, 
               12.0*(GLfloat)h/(GLfloat)w);
   else
      gluOrtho2D(-12.0*(GLfloat)w/(GLfloat)h, 
               12.0*(GLfloat)w/(GLfloat)h, -12.0, 12.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}
