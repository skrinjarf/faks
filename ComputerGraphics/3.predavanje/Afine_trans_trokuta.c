
/*
 * hello.c
 * Jednostavni OpenGL program za pocetak
 */
#include <math.h>		// za matematicke routine (npr. sqrt & trig).
#include <stdio.h>
#include <stdlib.h>		// Za izlaz
#include <GL/glut.h>	// OpenGL Graphics Utility Library

//#define M_PI 3.14159265358979323846f Ako nije definiran Pi u math lib-u, dekomentirati


float theta;
float l;
float r;

void koordinatni( void )
{
	glColor3f( 0.4, 0.4, 0.4 );

	glBegin( GL_LINES );
		glVertex2f( 0.0, 5.0 );
		glVertex2f( 0.0, -5.0 );
		glVertex2f( 5.0, 0.0 );
		glVertex2f( -5.0, 0.0 );
	glEnd();
}

void drawThreePoints( void )
{
  glBegin(GL_LINE_LOOP);
    glVertex2f(1.0, -1.0);
    glVertex2f(0.0, 1.0);
    glVertex2f(-1.0, -1.0);
  glEnd();
}

void display(void)
{
/* ocisti sve pixle  */
   glClear (GL_COLOR_BUFFER_BIT);

	glMatrixMode (GL_MODELVIEW);  // postavljanje matrice pogleda
	glLoadIdentity () ;           // M = jedinična matrica

	koordinatni();
	
	/*OVDJE SE POSTAVLJAJU PARAMETRI*/
	theta = 60.0;
	l = 2.0;
	r = 0.5;
	
	glBegin( GL_LINES );
		glVertex2f( 0.0, 0.0 );
		glVertex2f( l*cos( theta/180*M_PI ), l*sin( theta/180*M_PI ) );
	glEnd();

   glColor3f (1.0, 0.9, 0.0);

	glRotatef (theta, 0.0, 0.0, 1.0) ;         // M = M*Rθ
	glTranslatef(l,0, 0);      // M = M*T(l,0)
	glPushMatrix ();              // spremi matricu M na stog
	glTranslatef (0, r+1, 1);  // M = M*T(0,r+1)
	drawThreePoints ();
	glPopMatrix ();               // uzmi matricu sa stoga
	glRotatef (180.0, 0, 0, 1);      // M = M*R1800
	glTranslatef (0,r+1, 1);   // M = M*T(0,r+1)
	drawThreePoints ();

   glFlush ();
}

void init (void)
{
/* Odaberi pozadinsku boju 	*/
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* OpenGL je namijenjen za 3D, o projkecijam kasnije  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);
}

/*
 * Inicijalizacija
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Afine transformacije trokuta");
   init ();
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;   /* zahtijeva sintaksa, ali nece se nikad izvrsiti */
}
