/* pick.c    */

/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */

/* demonstrates picking used selection mode */

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <GL/glut.h>

#include <iostream>
#include <math.h>

//size of selection buffer
#define BUFSIZE 64

enum component_type
{
    capacitor,
    resistor,
    transistor
};

//#include <cmath>
struct component_t
{
    component_t(int t=0, int x=0, int y=0) : type(t), tx(x), ty(y), rx(0), sx(15), sy(15) {}

    int type;        //type of component
    int tx, ty;        //translation
    int rx;            //rotation in degrees
    float sx, sy;    //scale
};

struct wire_t
{
	wire_t(int start_x=0, int start_y=0, int end_x=10, int end_y=0): start_x(start_x), end_x(end_x), start_y(start_y), end_y(end_y) {}
	
	int start_x, start_y, end_x, end_y;
};

static int width, height;
static bool ctrl_down = false;
static bool alt_down = false;
static bool shift_down = false;

static int mx = 0; //mouse position x
static int my = 0; //mouse position y
static float zoom=1.0;
static int translation_x=0;
static int translation_y=0;
//list with current components
static std::vector<component_t> components;
static std::vector<wire_t> wires;

//index of select components in above list, -1 means nothing is selected
static int selected = -1;
static int w_selected = -1;
static int type=0; // clue what is selected, component or wire
void draw_wire(const wire_t & w)
{
	glBegin(GL_LINES);
	glVertex3f(w.start_x, w.start_y, -1.0);
	glVertex3f(w.end_x, w.end_y, -1.0);
	glEnd();
}
void draw_capacitor(void)
{
    
    glBegin(GL_LINES);
    glVertex2f(-1, 0.);
    glVertex2f(-0.1, 0.);
    glVertex2f(-0.1, -1.);
    glVertex2f(-0.1, 1.);
    glVertex2f(1, 0.);
    glVertex2f(0.1, 0.);
    glVertex2f(0.1, -1.);
    glVertex2f(0.1, 1.);
    glEnd();
    //TODO: draw capacitor symbol
}

void draw_resistor(void)
{
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-1, 0.);
    glVertex2f(-0.8, 0.);
    glVertex2f(-0.5, 1.);
    glVertex2f(-0.2, -1.);
    glVertex2f(0.1, 1.);
    glVertex2f(0.4, -1.);
    glVertex2f(0.7,0.);
    glVertex2f(1.0, 0.);
    glEnd();
    //TODO: draw resistor symbol
}

void draw_transistor(void)
{
    glBegin(GL_LINE_LOOP);
    float r=0.8;
    for(int a=0; a<30; a++)
    {
        glVertex2f(r*cos(a/30.0*2*3.14), r*sin(a/30.0*2*3.14));
    }

    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.);
    glVertex2f(-0.2, 0.);
    glVertex2f(0.1, 1.);
    glVertex2f(0.1, 0.3);
    glVertex2f(0.1, -1.);
    glVertex2f(0.1, -0.3);

    glVertex2f(-0.2, -0.5);
    glVertex2f(-0.2, 0.5);

    glVertex2f(0.1, 0.3);
    glVertex2f(-0.2, 0.2);
    glVertex2f(0.1, -0.3);
    glVertex2f(-0.2, -0.2);

    glEnd();
    //TODO: draw transistor symbol
}

void draw_components(GLenum mode)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(zoom, zoom, 1);
	glTranslatef(translation_x, translation_y, 0.0);
    //loop over components and draw them. Mode is either GL_RENDER or GL_SELECT
	for(size_t i=0; i<wires.size(); i++)
	{
		const wire_t & w = wires[i];
		if(selected==i && type==1) glColor3f(1,0,0);
		else glColor3f(0,0,0);
		//glPushMatrix();
		glLoadName(i);
		draw_wire(w);
		//glPopMatrix();
	}
	if(mode==GL_SELECT) glPushName(1);
    for (size_t i=0; i<components.size(); i++)
    {
        
        const component_t& c = components[i];

        //draw selected component in different color
        if (selected == i && type==0)
            glColor3f(1,0,0);
        else
            glColor3f(0,0,0);

        glPushMatrix();
        //glLoadIdentity();
        glTranslatef(c.tx, c.ty, 0.);
        glScalef(c.sx, c.sy, 0.);
        glRotatef(c.rx, 0., 0., 1.);
		if (mode==GL_SELECT) glLoadName((GLuint)(i));
        if ( c.type == resistor) draw_resistor();
        else if(c.type==capacitor) draw_capacitor();
        else draw_transistor();
        glPopMatrix();
        //TODO: draw components using their individual translation, rotation,
        //      and scale.
    }
}
void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint ii, jj, names, *ptr;

   printf ("hits = %d\n", hits);
   ptr = (GLuint *) buffer; 
   for (i = 0; i < hits; i++) {	/*  for each hit  */
      names = *ptr;
	  printf("names: %i ...", names);
	  ptr++;
	  printf("z min= %d\n", *ptr);
	  ptr+=2;

      for (j = 0; j < names; j++) { /*  for each name */
         printf("j: %i typ :%i | ", j,  components[*ptr].type);
         ptr++;
      }
      printf ("\n");
   }
}
int get_id(int hits, GLuint buffer[], int &type)
{
	
	GLuint *ptr = (GLuint *) buffer;
	if(*ptr == 2) 
	{
		type=0; // component
		ptr++;
	}
	else type=1; // wire
	ptr+=3;
    if (hits == 0) return -1;
	else return *ptr;
	
    //TODO: grab name from the select buffer and return it

   // return 42;
}
void drawCursor(int x, int y)
{

	//std::cout<<"drawing "<<x<<" "<<y<<std::endl;
        glPushMatrix();
        glLoadIdentity();
        glColor3f(0.0, 0.5, 0.7);
        glBegin(GL_QUADS);
            glVertex2f(x-1, y-1);
            glVertex2f(x-1, y+1);
            glVertex2f(x+1, y+1);
            glVertex2f(x+1, y-1);
        glEnd();
        glPopMatrix();
       
}
void mouse(int button, int state, int x, int y)
{
    ctrl_down = (glutGetModifiers() & GLUT_ACTIVE_CTRL) != 0;
    alt_down = (glutGetModifiers() & GLUT_ACTIVE_ALT) != 0;
    shift_down = (glutGetModifiers() & GLUT_ACTIVE_SHIFT) != 0;
	int cx=x;
	int cy=y;
    x = x - width/2;
    y = (height-y-1) - height/2;
    mx=x;
    my=y;
	//glutPostRedisplay();
	//std::cout<<mx <<" "<< my<<std::endl;
	
	GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];    
	
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		glGetIntegerv (GL_VIEWPORT, viewport);

		glSelectBuffer (BUFSIZE, selectBuf);
		(void) glRenderMode(GL_SELECT);	
		glInitNames();
		glPushName(0);

		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();
		glLoadIdentity ();
		//std::cout<<"window coordinates: "<<cx<< " "<<viewport[3]-cy<<std::endl;
		//std::cout<<"w/2  h/2: "<<width/2<< " "<<height/2<<std::endl;
		//std::cout<<"viewport"<<viewport[0]<< " "<<viewport[1]<< " "<<viewport[2]<< " "<<viewport[3]<< " "<<std::endl;
		gluPickMatrix ((GLdouble) cx, (GLdouble) (viewport[3] - cy), 16.0, 16.0, viewport);// it is using window coordinates!
		gluOrtho2D (-width/2, width/2, -height/2, height/2);
		draw_components(GL_SELECT);


		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush();
		//glutSwapBuffers ();
		hits = glRenderMode (GL_RENDER);
		processHits(hits, selectBuf);
		selected= get_id(hits, selectBuf, type);
		std::cout<<"Selected: "<<selected<<std::endl;
		//glutPostRedisplay();
	}
	
	if (selected!=-1)
    {
		std::cout<<"Wybrany: "<<selected<<std::endl;
        if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
		{
			if(ctrl_down)
			{
				if (type==0)	components.erase(components.begin()+selected);
				else wires.erase(wires.begin()+selected);
			}
			selected = -1;
			glutPostRedisplay();
			return;
		}

		
    }
	
		glutPostRedisplay();
    //TODO: Draw components with the 'select' render mode.
    //      Use gluPickMatrix to restrict drawing to a 16x16 pixels area near
    //      cursor (x,y).
    
    //glutPostRedisplay();
	
} 


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
  
	draw_components(GL_RENDER);  
	drawCursor(mx,my);
	glFlush();
    //glutSwapBuffers();
}

/*  processHits prints out the contents of the 
 *  selection array.
 */



void reshape(int w, int h)
{
    glClearColor(1.f,1.f,1.f,0.f);
    glColor3f(0.f, 0.f, 0.f);
    glLineWidth(2.f);

    width = w; height = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, w/2, -h/2, h/2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
	  case '=':
		  //std::cout<<"zoom"<<std::endl;
		  zoom*=2;
		  break;
	  case '-':
		  zoom/=2;
		  break;
	  case 'w':
		  translation_y-=10;
		  break;
	  case 's':
		  translation_y+=10;
		  break;
	  case 'd':
		  translation_y-=10;
		  break;
	  case 'a':
		  translation_y+=10;
		  break;
	  default:
		  std::cout<<"key "<< key <<std::endl;
		  break;
		 
   }
   glutPostRedisplay();
}
void motion(int x, int y)
{

    x = x - width/2;
    y = (height-y-1) - height/2;

    //TODO: This function is called when the mouse is moved.
    //      Handle translation, rotation and scaling of the
    //      selected component here.
	if(selected<0) return;
	if(type==1)
	{
		wire_t & w=wires[selected];
		if((w.start_x-x)*(w.start_x-x) +(w.start_y-y)*(w.start_y-y) < (w.end_x-x)*(w.end_x-x) +(w.end_y-y)*(w.end_y-y))
		{
			w.start_x=x;
			w.start_y=y;
		}
		else
		{
			w.end_x=x;
			w.end_y=y;
		}
		glutPostRedisplay();
		return;
	}
	component_t & c=components[selected];
	
	if(shift_down)
	{	
		c.rx=(y - c.ty);
	}
	else if(alt_down)
	{
		c.sx=(x-c.tx)+15.;
		c.sy=(y-c.ty)+15.;
	}
	else
	{
		c.tx=x;
		c.ty=y;
	}
	
    //save mouse position for later
    //mx = x; my = y;    

    glutPostRedisplay();
}
void menu(int c)
{
	if(c==3) wires.push_back(wire_t(mx, my, mx+20, my));
    else components.push_back(component_t(c,mx,my));
    glutPostRedisplay();
}
/* Main Loop */
int main(int argc, char** argv)
{
  //add some default components
    //components.push_back(component_t(capacitor, 0, 0));
    components.push_back(component_t(resistor, 0, 0));
    //components.push_back(component_t(transistor, 256, 0));

    //setup glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutCreateMenu(menu);
    glutAddMenuEntry("New capacitor..",0); 
    glutAddMenuEntry("New resistor..",1); 
    glutAddMenuEntry("New transistor",2); 
	glutAddMenuEntry("New wire",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON); 
    glutReshapeFunc(reshape);
    glutDisplayFunc(display); 
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0; 
}
