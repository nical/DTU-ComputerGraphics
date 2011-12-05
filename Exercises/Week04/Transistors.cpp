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

#define BUFSIZE 64
#define PI 3,14159265

using namespace std;

enum { NOTHING, WIRE, CIRCUIT };

enum circuit_selected_type
{
    CAPACITOR,
    RESISTOR,
    TRANSISTOR
};

struct Circuit
{
    Circuit(int t=0, int x=0, int y=0)
    : type(t), x(x), y(y), rot(0), scale(15) {}

    int type;
    int x;
    int y;
    int rot;         
    float scale;
};

struct Wire
{
	Wire(int x1=0, int y1=0, int x2=10, int y2=0)
    : x1(x1), x2(x2), y1(y1), y2(y2) {}
	
	int x1;
    int y1;
    int x2;
    int y2;

    void draw()
    {
        glBegin(GL_LINES);
        glVertex3f(x1, y1, -1.0);
        glVertex3f(x2, y2, -1.0);
        glEnd();
    }
};

static int width, height;

static std::vector<Circuit> circuits;
static std::vector<Wire> wires;
static int selected = -1;
static int selected_type = 0;
static int add_elt = NOTHING;
static int next_circuit;

static int motion_wait = 0;

static int scroll_x=0;
static int scroll_y=0;
static int mouse_x = 0;
static int mouse_y = 0;
static float zoom = 1.0;




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
}

void draw_circuits(GLenum mode)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(zoom, zoom, 1);
	glTranslatef(scroll_x, scroll_y, 0.0);

    for(int i=0; i<wires.size(); ++i)
	{
        //cout << "w" << i << "/"<< wires.size() << endl;
		if(selected==i && selected_type==1) glColor3f(0.0,1.0,0.0);
		else glColor3f(0.0,0.0,0.0);
		glLoadName(i);
		wires[i].draw();
	}
	if(mode==GL_SELECT) glPushName(1);
    for (int i=0; i<circuits.size(); ++i)
    {
        //cout << "c" << i << "/" << circuits.size()<< endl;
        const Circuit& c = circuits[i];

        // different color for selected circuit
        if (selected == i && selected_type==0)
            glColor3f(0.0,1.0,0.0);
        else
            glColor3f(0.0,0.0,0.0);

        glPushMatrix();

        glTranslatef(c.x, c.y, 0.);
        glScalef(c.scale, c.scale, 0.);
        glRotatef(c.rot, 0., 0., 1.);
		if (mode==GL_SELECT) glLoadName((GLuint)(i));

        if ( c.type == RESISTOR) draw_resistor();
        else if (c.type==CAPACITOR) draw_capacitor();
        else if (c.type==TRANSISTOR) draw_transistor();
        else cout << "wrong type!" <<endl;

        glPopMatrix();
    }
}

void erase_circuit( int idx )
{

    cout << "selected type = " << selected_type << endl;
    if (selected_type == 0)
    {
        if ( idx >= 0 && idx < circuits.size() );
        {
            circuits[idx] = circuits[circuits.size()-1];
            circuits.resize( circuits.size() -1 );
        }
        selected = -1;
        return;
    }
    else if ( idx >= 0 && idx < wires.size() )
    {
        wires[idx] = wires[wires.size()-1];
        wires.resize( wires.size() -1 );
    }
    selected = -1;
    
}

void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint ii, jj, names, *ptr;

   printf ("hits = %d\n", hits);
   ptr = (GLuint *) buffer; 
   for (i = 0; i < hits; i++) {
      names = *ptr;
	  printf("names: %i ...", names);
	  ptr++;
	  printf("z min= %d\n", *ptr);
	  ptr+=2;

      for (j = 0; j < names; j++) {
         printf("j: %i yp :%i | ", j,  circuits[*ptr].type);
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
		type=0; // circuit
		ptr++;
	}
	else type=1; // wire
	ptr+=3;
    if (hits == 0) return -1;
	else return *ptr;
}
void draw_cursor(int x, int y)
{
        glPushMatrix();
        glLoadIdentity();
        glColor3f(0.8, 0.9, 0.95);
        glBegin(GL_LINES);
            glVertex2f(-width*0.5, y); glVertex2f(width*0.5, y);
            
            glVertex2f(x, -height*0.5); glVertex2f(x, height*0.5);
        glEnd();
        glPopMatrix();
       
}
void mouse(int button, int state, int x, int y)
{
	int cx=x;
	int cy=y;
    x = x - width/2;
    y = (height-y-1) - height/2;
    mouse_x=x;
    mouse_y=y;

    // insert elements in the scene 
    if ( add_elt == WIRE )
    {
        wires.push_back( Wire(x,y,x+50.0,y ) );
        add_elt = NOTHING;
    }
    else if ( add_elt == CIRCUIT )
    {
        circuits.push_back( Circuit( next_circuit, x, y ) );
        add_elt = NOTHING;
    }

    GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{

		glGetIntegerv (GL_VIEWPORT, viewport);

		glSelectBuffer (BUFSIZE, selectBuf);
		(void) glRenderMode(GL_SELECT);	
		glInitNames();
		glPushName(0);

		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();
		glLoadIdentity ();
		gluPickMatrix ((GLdouble) cx, (GLdouble) (viewport[3] - cy), 16.0, 16.0, viewport);
		gluOrtho2D (-width/2, width/2, -height/2, height/2);
		draw_circuits(GL_SELECT);


		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush();
		hits = glRenderMode (GL_RENDER);
		processHits(hits, selectBuf);
        int temp = get_id(hits, selectBuf, selected_type); 
		if(temp != -1 || selected_type == 1) selected = temp;
	}
	
	
	glutPostRedisplay();
} 


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
	draw_cursor(mouse_x,mouse_y);  
	draw_circuits(GL_RENDER);  
	glFlush();
}

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

void zoomIn()
{
    zoom *= 1.5;
}

void zoomOut()
{
    zoom /= 1.5;
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
	  case 'w':
		  scroll_y-=10;
		  break;
	  case 's':
		  scroll_y+=10;
		  break;
	  case 'd':
		  scroll_y-=10;
		  break;
	  case 'a':
		  scroll_y+=10;
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

	if(selected <0 ) return;
    
	if (selected_type==1)
	{
        if(selected >= wires.size() ) return;
		Wire & w=wires[selected];
		if((w.x1-x)*(w.x1-x) +(w.y1-y)*(w.y1-y) < (w.x2-x)*(w.x2-x) +(w.y2-y)*(w.y2-y))
		{
			w.x1=x;
			w.y1=y;
		}
		else
		{
			w.x2=x;
			w.y2=y;
		}
		glutPostRedisplay();
		return;
	}

    if ( motion_wait <= 0 )
    {
        circuits[selected].x=x;
        circuits[selected].y=y;
    }
    
    glutPostRedisplay();
}

void scale_up( int idx )
{
    if( idx < 0 ) return;
    if( idx >= circuits.size() ) return;
    
    circuits[idx].scale *= 1.5;
}

void scale_down( int idx )
{
    if( idx < 0 ) return;
    if( idx >= circuits.size() ) return;
    
    circuits[idx].scale /= 1.5;
}

void rotate_cw( int idx )
{
    if( idx < 0 ) return;
    if( idx >= circuits.size() ) return;
    
    circuits[idx].rot -= 45.0;
}

void rotate_ccw( int idx )
{
    if( idx < 0 ) return;
    if( idx >= circuits.size() ) return;
    
    circuits[idx].rot -= 45.0;
}

void menu(int c)
{
    cout << "selected= " << selected << endl;

    switch ( c )
    {
        case 3: { add_elt = WIRE; break; }
        case 4: { zoomIn(); break; }
        case 5: { zoomOut(); break; }
        case 6: { erase_circuit( selected ); break; }
        case 7: { rotate_cw(selected); break; }
        case 8: { rotate_cw(selected); break; }
        case 9: { scale_up(selected); break; }
        case 10:{ scale_down(selected); break; }
        default:{
            add_elt = CIRCUIT;
            next_circuit = c;
            break;
        }
    }

    motion_wait = 20;// to avoid moving things when selecting menu items
     
    glutPostRedisplay();
}


void timer_function(int)
{
    if (motion_wait > 0) --motion_wait;
    glutTimerFunc(100,timer_function,0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutCreateMenu(menu);
    glutAddMenuEntry("New capacitor..",CAPACITOR); 
    glutAddMenuEntry("New resistor..",RESISTOR); 
    glutAddMenuEntry("New transistor",TRANSISTOR); 
	glutAddMenuEntry("New wire",3);
	glutAddMenuEntry("Zoom in",4);
	glutAddMenuEntry("Zoom out",5);
	glutAddMenuEntry("Erase",6);
	glutAddMenuEntry("Rotate cw",7);
	glutAddMenuEntry("Rotate ccw",8);
	glutAddMenuEntry("Scale up",9);
	glutAddMenuEntry("Scale down",10);
    glutAttachMenu(GLUT_RIGHT_BUTTON); 
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(100,timer_function,0);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0; 
}
