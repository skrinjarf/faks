
/*
 * hello.c
 * Jednostavni OpenGL program za pocetak
 */
#include <math.h>		// za matematicke routine (npr. sqrt & trig).
#include <stdio.h>
#include <stdlib.h>		// Za izlaz
#include <GL/glut.h>	// OpenGL Graphics Utility Library

void drawThreePoints ()  // konstrukcija trokuta
{
  glBegin(GL_LINE_LOOP);
    glVertex2f(1.0, -1.0);
    glVertex2f(0.0, 1.0);
    glVertex2f(-1.0, -1.0);
  glEnd();
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glColor3f (1.0, 1.0, 1.0);
  glBegin(GL_LINES); // nacrtaj koordinatni sistem
    glVertex2f(-5.0, 0.0);
    glVertex2f(5.0, 0.0);
    glVertex2f(0.0, -5.0);
    glVertex2f(0.0, 5.0);
  glEnd();
  glColor3f (1.0, 0., 0.);
  drawThreePoints ();  // nacrtaj trokut, promijeni matricu modela (translacijom i rotacijom)
  glColor3f(0,1,0);
  glTranslatef (1.0, 3.0, 0.0);             
  glRotatef(-90.0, 0.0, 0.0, 1.0); 
  drawThreePoints ();  // nacrtaj ponovo trokut s novom matricom modela
  glFlush(); 
}
 

void init (void) 
{

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glPointSize(6);
   glLineWidth(4);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Rotacija trokuta!");
   init ();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;   
}
