
#include <GL/glut.h>

void display(void)
{
/* clear all pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   glColor3f (0.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3i (0,0,0);				//netransformirana kucica
      glVertex3i (30,0,0);
      glVertex3i (30,30,0);
      glVertex3i (15,45,0);
      glVertex3i (0,30,0);
   glEnd();
   
   glTranslated(40,30,0);
   glRotated(90,0,0,1);
   glScalef(0.3,0.3,1);
   glTranslated(-15,-24,0);			//rtransformacije od ovdje na gore
   glColor3f (1.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3i (0,0,0);
      glVertex3i (30,0,0);
      glVertex3i (30,30,0);
      glVertex3i (15,45,0);
      glVertex3i (0,30,0);
   glEnd();

/* don't wait!  
 * start processing buffered OpenGL routines 
 */
   glFlush ();
}

void init (void) 
{
/* select clearing color    */
   glClearColor (1.0, 1.0, 1.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 50.0, 0.0, 50.0, -1.0, 1.0);
}

/* 
 * Declare initial window size, position, and display mode

 * (single buffer and RGBA).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("kucica");
   init ();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
