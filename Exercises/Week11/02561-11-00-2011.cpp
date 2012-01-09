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

// glu NURBS curve
GLUnurbsObj* nurbsCurve;


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
T BezierCurve( T * points, int order, float t )
{
    int n = order-1;
    T result;
    for(int dim = 0; dim < T::Dimension; ++dim)
    {
        for(int i = 0; i <= n; ++i)
        {
            result[dim] += 
                  factorial(n) / (factorial(i)*factorial(n-i) )
                * pow(1-t,n-i)
                * pow(t,i)
                * points[i][dim];
        }
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


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);

    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 3; ++j)
            vecCtrlPoints[i][j] = ctrlpoints[i][j];
    }
    
    // glu NURBS
    nurbsCurve = gluNewNurbsRenderer();
    assert( nurbsCurve );
	gluNurbsProperty(nurbsCurve, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
	gluNurbsProperty(nurbsCurve, GLU_U_STEP, 100);
    gluNurbsCallback(nurbsCurve, GLU_ERROR, (GLvoid (*)()) nurbsError);
    assert( glGetError() == GL_NO_ERROR );
}

void DisplayNURBSCurve(GLUnurbsObj* curve, GLfloat* knots, GLuint nbKnots )
{
    assert( glGetError() == GL_NO_ERROR );
    gluBeginCurve(nurbsCurve);
    gluNurbsCurve(
        curve, nbKnots, knots
        , 3, &ctrlpoints[0][0]
        , 4, GL_MAP1_VERTEX_3);
    gluEndCurve(nurbsCurve);
    assert( glGetError() == GL_NO_ERROR );
}

void DisplayGenericBezierCurve( vec<3>* points, int order )
{
    // our generic bezier curve implementation
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < 42; ++i)
    {
        vec<3> p = BezierCurve(points, order, (float)i/42.0 );
        glVertex3f(p[0],p[1],p[2]);
    }
    glEnd();
}

void display(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity ();
    gluLookAt (0., 5., 1., 0., 5., 0., 0., 1., 0.);

/*
    // opengl 4th order (cubic) bezier curve
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++) 
         glEvalCoord1f((GLfloat) i/30.0);
    glEnd();
*/

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
/*
    glColor3f(1.0, 0.0, 0.0);
    DisplayGenericBezierCurve(vecCtrlPoints, 7);
    DisplayGenericBezierCurve(vecCtrlPoints, 6);
    DisplayGenericBezierCurve(vecCtrlPoints, 5);
    DisplayGenericBezierCurve(vecCtrlPoints, 4);
    DisplayGenericBezierCurve(vecCtrlPoints, 3);
*/


    GLfloat nurbsKnot1[] = {  0.0, 0.0, 0.0, 0.0
                            , 0.1, 0.5, 0.9
                            , 1.0, 1.0, 1.0, 1.0 };
    GLfloat nurbsKnot2[] = {  0.0, 0.0, 0.0, 0.0
                            , 0.25, 0.5, 0.75
                            , 1.0, 1.0, 1.0, 1.0 };
    GLfloat nurbsKnot3[] = {  0.0, 0.0, 0.0, 0.0
                            , 0.4, 0.5, 0.6
                            , 1.0, 1.0, 1.0, 1.0 };
    // the following knot vector is equivalent to a cubic bezier curve
    GLfloat nurbsKnot4[] = {  0.0, 0.0, 0.0, 0.0
                            , 0.5, 0.5, 0.5
                            , 1.0, 1.0, 1.0, 1.0 };

    // uniform
    GLfloat nurbsKnotUniform[] = {  0.0, 0.1, 0.2, 0.3
                            , 0.4, 0.5, 0.6
                            , 0.7, 0.8, 0.9, 1.0 };

    // non uniform with different knob vectors
    glColor3f(0.0, 0.0, 1.0);
    DisplayNURBSCurve(nurbsCurve, nurbsKnot1, 11 );
    DisplayNURBSCurve(nurbsCurve, nurbsKnot2, 11 );
    DisplayNURBSCurve(nurbsCurve, nurbsKnot3, 11 );
    DisplayNURBSCurve(nurbsCurve, nurbsKnot4, 11 );

    // uniform b spline (knots are uniformly growing)
    glColor3f(0.6, 0.0, 0.6);
    DisplayNURBSCurve(nurbsCurve, nurbsKnotUniform, 11 );

    
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
