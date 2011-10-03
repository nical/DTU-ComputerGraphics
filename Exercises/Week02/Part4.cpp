/*Appendix 3  -  02561-01-03-2011-a3
*  Tea pot
*
*
*/

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define M_PI       3.14159265358979323846
int width = 500;
int height = 500;

float aileronLeft = 0., aileronRight = 0.;
float roll=0.;
void drawRectangle(float x, float y){
	glBegin(GL_POLYGON);
		glVertex2f (0.,0.);
		glVertex2f (0.,y);
		glVertex2f (x ,y);
		glVertex2f (x,0.);
	glEnd ();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
}
void drawCircle(float r, int points, GLenum type=GL_TRIANGLE_FAN)
{
	glBegin(type);
	if(type==GL_TRIANGLE_FAN) glVertex3f(0.,0., 0.);
	float arg;
	
	for(float a=0; a<points; a++){
		arg=float(a/points*2*M_PI);
		glVertex3f(r*cos(arg), r*sin(arg), 0.);
	}
	glVertex3f(r, 0., 0.);
	glEnd();
	
}

void drawBox(float a, float b, float c)
{
	//glPushMatrix();
	//glLoadIdentity();
	
	
	glBegin(GL_QUADS);
	glVertex3f(0.,0.,0.);
	glVertex3f(a,0.,0.);
	glVertex3f(a,b,0.);
	glVertex3f(0.,b,0.);

	glVertex3f(0.,0.,c);
	glVertex3f(a,0.,c);
	glVertex3f(a,b,c);
	glVertex3f(0.,b,c);

	glVertex3f(a, 0., 0.);
	glVertex3f(a,b,0.);
	glVertex3f(a,b,c);
	glVertex3f(a,0,c);

	glVertex3f(0.,0.,0.);
	glVertex3f(a, 0., 0.);
	glVertex3f(a, 0., c);
	glVertex3f(0., 0., c);
	
	glVertex3f(0.,b,0.);
	glVertex3f(a, b, 0.);
	glVertex3f(a, b, c);
	glVertex3f(0., b, c);

	glVertex3f(0.,0.,0.);
	glVertex3f(0., b, 0.);
	glVertex3f(0., b, c);
	glVertex3f(0., 0., c);
	glEnd();
	//glPopMatrix();
}

void drawSmile(float size)
{
	glBegin(GL_LINES);
	glVertex2f(-size/2, size/2);
	glVertex2f(-size/2, -size/2);
	glVertex2f(size/2, size/2);
	glVertex2f(size/2, -size/2);
	glEnd();
	glBegin(GL_LINE_STRIP);
	
	for(float a=-M_PI/10; a>-3/2*M_PI; a=a-M_PI/10){
	
		glVertex3f(2*size*cos(a), 2*size*sin(a), 0.);
	}
	glEnd();
}


void display() {

	float Bx=200., By=30., Bz=30.;
	float Wx=30., Wy=100., Wz=15.;
	float Sx=20., Sy=5., Sz=40.;
	float Hx=20., Hy=35., Hz=5.;
	float Ax=10., Ay=50., Az=5.;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
	
	
    glColor3f(1.0, 0.0, 1.0);
  glPushMatrix();
  glLoadIdentity();
  glRotatef(roll, 1., 0., 0.);
  //glTranslatef(0., 0., 0.);
  drawBox(Bx, By, Bz);

  glColor3f(1.,1.,1.);
  glTranslatef((Bx-Wx)/2., -Wy, (Bz-Wz)/2);
  drawBox(Wx, Wy, Wz);
  glLoadIdentity();
  glRotatef(roll, 1., 0., 0.);
  glTranslatef((Bx-Wx)/2., By, (Bz-Wz)/2);
  drawBox(Wx, Wy, Wz);
  
  glColor3f(1., 1., 0.);
  glLoadIdentity();
  glRotatef(roll, 1., 0., 0.);
  glTranslatef(0.,(By-Sy)/2, Bz);
  drawBox(Sx, Sy, Sz);

  glLoadIdentity();
  glRotatef(roll, 1., 0., 0.);
  glTranslatef(0.,-Hy, (Bz-Hz)/2);
  glColor3f(0.,1.,0.);
  drawBox(Hx, Hy, Hz);
  glTranslatef(0.,By+Hy, 0.);
  drawBox(Hx, Hy, Hz);

  //ailerons
  
  glLoadIdentity();
  glRotatef(roll, 1., 0., 0.);
  glColor3f(0., 0., 1.);
  
  glTranslatef((Bx-Wx)/2, -(Wy+Ay)/2, (Bz-Az)/2);
  glRotatef(aileronLeft, 0., 1., 0.);
  drawBox(-Ax, Ay, Az);
  
  glLoadIdentity();
  glRotatef(roll, 1., 0., 0.);
  glTranslatef((Bx-Wx)/2, By+(Wy-Ay)/2, (Bz-Az)/2);
  glRotatef(aileronRight, 0., 1., 0.);
  
  drawBox(-Ax, Ay, Az);
 
  //end ailerons
  glPopMatrix();
  glFlush();
}


void reshape(int w, int h)  {         

  width = w;
  height = h;

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  glOrtho(-width/2, width/2, -height/2, height/2, -1000, 1000 );
  //glFrustum(-width/2, width/2, -height/2, height/2, -1000, 1000 );
  //glRotatef(45., 1., 0., 0.);
  glViewport(0, 0, width, height);  
  gluLookAt(0.,0., 200., 0., 0., -1., 0., 1., 0.);
}
//***********************************/
//needed for mouse rotation
int pos_x=0;
int pos_y=0;
int buttonPressed=0;
void mouse(int button, int state, int x, int y)
{
	//button: 0- left, 2-right
	//state: 0 - clicked, 1-released
	if(state==0){
		pos_x=x;
		pos_y=y;
		buttonPressed=button;
	}
	
}

void keyboard(unsigned char key, int x, int y)
{
	//std::cout<<(int)key<<std::endl;
	if(key=='q' && aileronLeft<60.) aileronLeft++;
	else if(key=='Q' && aileronLeft>-60.) aileronLeft--;
	else if(key=='a' && aileronRight<60.) aileronRight++;
	else if(key=='A' && aileronRight>-60.) aileronRight--;
	else if(key==27) exit(0);
	display();
}

void mouseMove(int x, int y)
{
	int divider=1;
	
	if(buttonPressed==0)
	{		
		glMatrixMode(GL_PROJECTION);
		glRotatef((x-pos_x)/divider, 0., 1., 0.);
		glRotatef((y-pos_y)/divider, 1., 0., 0.);
		display();
	}
	else if(buttonPressed==2)
	{
		glMatrixMode(GL_PROJECTION);
		glRotatef((x-pos_x)/divider, 0., 0., 1.);
		//glRotatef((y-pos_y)/10, 1., 0., 0.);
		display();
	}
	pos_x=x;
	pos_y=y;
	//std::cout<<x-pos_x<<std::endl;
}
//*******************************************************/
void refresh(int value)
{
	//std::cout<<"a"<<std::endl;
	float divider=8.;
	roll+=(aileronLeft-aileronRight)/divider;
	glutTimerFunc(40, refresh, 0);
	display();
}

int main (int argc, char **argv){

  glutInit (&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);    
  
  glutCreateWindow("Airplane!");  
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMove);
  glutKeyboardFunc(keyboard);
  
  glutTimerFunc(40, refresh, 0);
  
 // glutShowWindow();   
  glutMainLoop();
  

  return 0;
}
