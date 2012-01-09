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

// nth order besizer curve (general)
template<typename T>
T BezierCurve( T * points, int n, float t )
{
    T result;
    for(int dim = 0; dim < T::Dimension; ++dim)
    {
        //std::cout << "-------" << std::endl;
        //std::cout << pow(t,1) << std::endl;
        for(int i = 0; i <= n; ++i)
        {
            result[dim] += 
                  factorial(n) / (factorial(i)*factorial(n-i) )
                * pow(1-t,n-i)
                * pow(t,i)
                * points[i][dim];
        }
    }
    //cout << pow(0.5, 0) << endl;
    return result;
}

// Cubic besizer curve (specific)
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

void nurbsError(GLenum errorCode)
{
    const GLubyte *estring;
    estring = gluErrorString(errorCode);
    cout << "Nurbs Error: " << estring << endl;
    exit (0);
}

GLUnurbsObj* nurbsCurve;
GLfloat nurbsKnot[] = {1.0,2.0,3.0,4.0,5.0,6.,7.0,8.0,9.0,10.0};
GLuint nurbsKnotNb = 10;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);

    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 3; ++j)
            vecCtrlPoints[i][j] = ctrlpoints[i][j];
    }

    // 4th order bezier curve using legacy OpenGL facilities
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 5, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    // glu NURBS
    nurbsCurve = gluNewNurbsRenderer();
    assert( nurbsCurve );
	gluNurbsProperty(nurbsCurve, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
	gluNurbsProperty(nurbsCurve, GLU_U_STEP, 100);
    gluNurbsCallback(nurbsCurve, GLU_ERROR, (GLvoid (*)()) nurbsError);
    assert( glGetError() == GL_NO_ERROR );
}

void display(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity ();
    gluLookAt (0., 5., 1., 0., 5., 0., 0., 1., 0.);


    // opengl 4th order bezier curve
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++) 
         glEvalCoord1f((GLfloat) i/30.0);
    glEnd();


    // draw ctrl points as dots
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
      for (i = 0; i < 7; i++) 
         glVertex3fv(&ctrlpoints[i][0]);
    glEnd();

    // draw lines between ctrl points
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < 7; i++) 
    {
      glVertex3fv(&ctrlpoints[i][0]);
    }
    glEnd();

    // our generic bezier curve implementation
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < 42; ++i)
    {
        vec<3> p = BezierCurve(vecCtrlPoints, 6, (float)i/42.0 );
        glVertex3f(p[0],p[1],p[2]);
    }
    glEnd();

    // glu NURBS curve
    glGetError();
    glColor3f(0.0, 0.0, 1.0);
    gluBeginCurve(nurbsCurve);
    gluNurbsCurve(
        nurbsCurve, nurbsKnotNb, nurbsKnot, 3
        , &ctrlpoints[0][0], 4, GL_MAP1_VERTEX_3);
    gluEndCurve(nurbsCurve);
    assert( glGetError() == GL_NO_ERROR );


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
   gluDeleteNurbsRenderer(nurbsCurve);
   return 0;
}
