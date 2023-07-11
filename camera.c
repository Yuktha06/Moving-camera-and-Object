#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<stdarg.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
GLUquadric *quadCyl;
int windowWidth;
 // Rotate the scene about the Y axis
GLfloat yrot;
 // Location of the target and camera objects, respectively
float target[3], camera[3];
#define DELTA 0.25f
#define TIMER 33
void *font = GLUT_STROKE_ROMAN;
void *fonts[] = {GLUT_STROKE_ROMAN};
static float xrot;
int value,val,valu,v;
void polygon();
int theObject = -1;
char *objectNames[10] ={"Sphere","Octahedron","Tetrahedron","Icosahedron"};
void setup()
{
 glClearColor(.4, .5, .6, .0);
}
void output(GLfloat x, GLfloat y, char *format,...)
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
22
{
va_list args;
 char buffer[500], *p;
if(theObject>=0)
 {
 va_start(args, format);
 vsprintf(buffer, format, args);
 va_end(args);
 glPushMatrix();
 glTranslatef(x, y, 0);
 for (p = buffer; *p; p++)
 glutStrokeCharacter(font, *p);
 glPopMatrix();
 }
}
void text()
{
 glColor3f(1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
glPushMatrix();
 glLoadIdentity();
 gluOrtho2D(0, 3000, 0, 3000);
 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
 glLoadIdentity();
 glColor3f(.0,.0,1.0);
 output(1800,2800, "%s",objectNames[theObject]);
 glPopMatrix();
 glMatrixMode(GL_PROJECTION);
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
23
 glPopMatrix();
 glMatrixMode(GL_MODELVIEW);
 glPopAttrib();
}
void Colors()
{
 switch(val)
 {
 case 3:
 glColor3f(1.0,.5,.0);
break;
 case 4:
 glColor3f(1.0,.0,0.0);
break;
 case 5:
 glColor3f(0.0,.0,1.0);
break;
case 6:
 glColor3f(.5,.0,.5);
break;
 case 7:
 glColor3f(1.0,.0,0.5);
break;
 default: glColor3f(.6, .3, .5);
break;
}
}
void col(int p)
{
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
24
val=p;
}
void drawScene (GLenum order)
{
 GLfloat pos[4] = {-2.5, 5., 2.2, 1.};
 glLightfv (GL_LIGHT1, GL_POSITION, pos);
glPushMatrix();
glEnable (GL_CULL_FACE);
glCullFace (GL_BACK);
glFrontFace (order);
 text();
/* Draw the polygon */
 glRotatef(xrot, 1.,1., 1.);
Colors();
 glPushMatrix ();
 glPopMatrix ();
polygon();
glPopMatrix();
}
void sphere()
{
 theObject=0;
 glutSolidSphere(0.5,28,12);
}
void oct()
{
theObject=1;
glutSolidOctahedron();
}
Department of CS&E, BIT 2022
-23
Movable Camera And Object 1BI2
1CS416
25
void tet() {
theObject = 2;
glutSolidTetrahedron();
}
void ico() {
theObject = 3;
glutSolidIcosahedron();
}
void polygon() {
if(value==14)

{
 sphere();

}
if(value==15)
oct();
if(value==16)
tet();
if(value==17) {
ico();
}
}
void pol(int p) {
value=p;
}
void main_menu(int valu)
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
26
{
value=valu;
 if (value == 0)
 exit(0);
}
static void key (unsigned char key, int x, int y)
{
 int nv=value,cv=val;
if(key=='o' && nv>=14 && nv<=17) value++;
if(key=='o' && nv==17) value=14;
if(key=='c' && cv>=3 && cv<=7) val++;
if(key=='c' && cv==7) val=3;
if(key=='r' && v<16) v++;
if(key=='k' &&v>=1) v--;
if(key=='q') target[0] -= DELTA;
 if(key=='Q') target[0] += DELTA;
 if(key=='w') target[1] -= DELTA;
 if(key=='W') target[1] += DELTA;
 if(key=='e') target[2] -= DELTA;
 if(key=='E') target[2] += DELTA;
 if(key=='a') camera[0] -= DELTA;
 if(key=='A') camera[0] += DELTA;
 if(key=='s') camera[1] -= DELTA;
 if(key=='S') camera[1] += DELTA;
 if(key=='d') camera[2] -= DELTA;
 if(key=='D') camera[2] += DELTA;
 glutPostRedisplay ();
}
static void cross(float dst[3],float srcA[3],float srcB[3])
{
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
27
 dst[0] = srcA[1]*srcB[2] - srcA[2]*srcB[1];
 dst[1] = srcA[2]*srcB[0] - srcA[0]*srcB[2];
 dst[2] = srcA[0]*srcB[1] - srcA[1]*srcB[0];
}
static void normalize (float vec[3])
{
 const float squaredLen = vec[0]*vec[0] + vec[1]*vec[1]
 + vec[2]*vec[2];
 const float invLen = 1.f / (float) sqrt (squaredLen);
 vec[0] *= invLen;
 vec[1] *= invLen;
 vec[2] *= invLen;
}
static void scale (float v[3], float s)
{
 v[0] *= s;
 v[1] *= s;
 v[2] *= s;
}
 glMatrixMode (GL_MODELVIEW)
glPushMatrix();
multLookAt (orig[0], orig[1],orig[2],
 at[0],at[1],at[2],up[0], up[1], up[2]);
glPopMatrix();
static void multLookAt (float eyex, float eyey, float eyez,
 float atx, float aty, float atz,
 float upx, float upy, float upz)
{
 float m[16];
 float *xaxis = &m[0],
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
28
 *up = &m[4],
 *at = &m[8];
at[0] = atx-eyex;
at[1] = aty-eyey;
at[2] = atz-eyez;
normalize (at);
up[0] = upx;
up[1] = upy;
up[2] = upz;
cross (xaxis, at, up);
normalize (xaxis);
cross (up, xaxis, at);
scale (at, -1.f);
m[3] = 0.f; // xaxis is m[0..2]
m[7] = 0.f; // up is m[4..6]
 m[11]= 0.f; // -at is m[8..10]
 m[12]= eyex;
m[13]= eyey;
 m[14]= eyez;
 m[15]= 1.f;
glMultMatrixf (m);
}
static void display( void )
{
 glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity ();
glTranslatef (0., -1., -5.);
glRotatef (yrot, 0., 1., 0.);
 glPushMatrix ();
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
29
 glTranslatef (target[0], target[1], target[2]);
 glPopMatrix ();
 glPushMatrix ();
 multLookAt (camera[0], camera[1], camera[2],
 target[0], target[1], target[2],
 0., 1., 0.);
 glRotatef (-90., 1., 0., 0.);
 glColor3f (0.2, .2, .2);
 glutSolidCube(.45);
 glRotatef (-90., 1., 0., 0.);
 glColor3f (1., .6, .4);
 gluCylinder (quadCyl, .20, 0., 0.6, 8, 2);
 glPopMatrix ();
 glutSwapBuffers();
}
void selectFont(int newfont)
{
font = fonts[newfont];
 glutPostRedisplay();
}
void reshape(int w, int h)
{
 windowWidth=w;
 glViewport (0, 0, w, h);
 glMatrixMode (GL_PROJECTION);
 glLoadIdentity ();
 gluPerspective (50., (float)w/(float)h, 1., 20.);
}
static void timer (int value)
{
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
30
 xrot +=v;
 if (xrot > 360.f) xrot -= 360.f;
 glutPostRedisplay ();
 glutTimerFunc (TIMER, timer, 0);
}
static void motion (int x, int y)
{
 yrot = (float)x*360.f/(float)windowWidth - 180.f;
 glutPostRedisplay ();
}
static void init ()
{
int s1,s2,s3;
 xrot = 1.;
 target[0] = target[1] = target[2] = 1.25f;
 camera[0] = camera[1] = camera[2] = 0.f;
 yrot = 0.f;
 glEnable (GL_DEPTH_TEST);
 {
 GLfloat pos[4] = {3., 5., 2., 1.};
 GLfloat white[4] = {1., 1., 1., 1.};
 GLfloat black[4] = {0., 0., 0., 0.};
 glEnable (GL_LIGHTING);
 glEnable (GL_LIGHT1);
 glLightfv (GL_LIGHT1, GL_POSITION, pos);
 glLightfv (GL_LIGHT1, GL_DIFFUSE, white);
 glLightfv (GL_LIGHT1, GL_SPECULAR, white);
 glEnable (GL_COLOR_MATERIAL);
 glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 glMaterialfv (GL_FRONT, GL_SPECULAR, white);
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
31
glMaterialf (GL_FRONT, GL_SHININESS, 20.);
 }
 quadCyl = gluNewQuadric ();
 glutDisplayFunc (display);
 glutReshapeFunc (reshape);
 glutMotionFunc (motion);
 glutKeyboardFunc (key);
 glutTimerFunc (TIMER, timer, 0);
s1=glutCreateMenu(pol);
glutAddMenuEntry("Sphere",14);
 glutAddMenuEntry("Octahedron", 15);
glutAddMenuEntry("Tetrahedron",16);
glutAddMenuEntry("Icosahedron",17);
s2= glutCreateMenu(col);
 glutAddMenuEntry("orange", 3);
 glutAddMenuEntry("red", 4);
 glutAddMenuEntry("Blue",5);
 glutAddMenuEntry("purple",6);
 glutAddMenuEntry("pink",7);
s3=glutCreateMenu(selectFont);
 glutAddMenuEntry("Roman",0);
 glutCreateMenu(main_menu);
 glutAddSubMenu("Object",s1);
glutAddSubMenu("Colors",s2);
glutAddMenuEntry("Quit", 0);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void main(int argc, char** argv)
{
 glutInit (&argc,argv);
Department of CS&E, BIT 2022-23
Movable Camera And Object 1BI21CS416
32
 glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
 glutInitWindowSize (windowWidth=300,300);
 glutInitWindowPosition (0,0);
 glutCreateWindow ("MOVABLE CAMERA AND OBJECT");
setup();
 init ();
 printf ("Left mouse button rotates the scene.\n");
 printf ("Move the target object:\n");
 printf ("\tq/Q\talong the X axis;\n");
 printf ("\tw/W\talong the Y axis;\n");
 printf ("\te/E\talong the Z axis.\n");
 printf ("Move the camera object:\n");
 printf ("\ta/A\talong the X axis;\n");
 printf ("\ts/S\talong the Y axis;\n");
 printf ("\td/D\talong the Z axis.\n");
 printf ("Any other key exits.\n");
 glutMainLoop ();
}
