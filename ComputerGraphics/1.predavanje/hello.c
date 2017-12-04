
/*
 * hello.c
 * Jednostavni OpenGL program za pocetak
 */
#include <math.h>		// za matematicke routine (npr. sqrt & trig).
#include <stdio.h>
#include <stdlib.h>		// Za izlaz
#include <GL/glut.h>	// OpenGL Graphics Utility Library

void display(void)
{
/* ocisti sve pixle  */
   glClear (GL_COLOR_BUFFER_BIT);

/* nacrtaj bijeli poligon sa zadanim vrhovima   (kvadrat)
 * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
 */
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.75, 0.75, 0.0);
      glVertex3f (0.25, 0.75, 0.0);
   glEnd();

/* Ne cekaj nego odmah prikazi medjuspremnik (buffer) 
 */
   glFlush ();
}

void init (void) 
{
/* Odaberi pozadinsku boju 	*/
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* OpenGL je namijenjen za 3D, o projkecijam kasnije  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);   				//definira kvadar [0,1]x[0,1]x[-1,1] to je vidljivi koordinatni sustav po x po y i po z za svaki su 2 parametra
}

/* 
 * Inicijalizacija 
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);		//GLUT_SINGLE daje da lie radimo sa jendim ili dva buffera, i GLUT_RGB odabire tip boje, moze bit standardni rgba ili neki indexni koji se danas ne koristi
   glutInitWindowSize (250, 250); 						//velicina prozora u pixelima
   glutInitWindowPosition (100, 100);   				//pozicija gornjeg desnog kuta
   glutCreateWindow ("hello OpenGl world");				//ime prozora
   init ();												//poziva fju inicijalizacije
   glutDisplayFunc(display); 
   glutMainLoop();										//beskonacna petlja
   return 0;   /* zahtijeva sintaksa, ali nece se nikad izvrsiti */
}
