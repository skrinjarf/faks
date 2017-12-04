/*
 * Dots.c
 *
 *     Crta segmente koji spajaju tocke unesene misem
 *
 *
 * 
 *   Lijevi klik za unos kontrolne tocke (najvise 64)
 *	  "f" micanje prve tocke
 *	  "l" micanje zadnje tocke
 *	 "escape" za izlaz
 */

#include "dots.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define MaxNumPts 64
float PointArray[MaxNumPts][2];
int NumPts = 0;

// Window size in pixels
int WindowHeight;
int WindowWidth;


void rotatefunkcija()
{ glRotated(10,0,0,1);
}

void myKeyboardFunc (unsigned char key, int x, int y)
{
	switch (key) {
	case 'f':
		removeFirstPoint();
		glutPostRedisplay();
		break;
	case 'l':
		removeLastPoint();
		glutPostRedisplay();
		break;
	case 27:			// Escape key
		exit(0);
		break;
	case 'r':
		rotatefunkcija();
		glutPostRedisplay();
		break;
	}
}


void removeFirstPoint() {
	int i;
	if ( NumPts>0 ) {
		// Makni prvu tocku, i pomakni slijedece
		NumPts--;
		for ( i=0; i<NumPts; i++ ) {
			PointArray[i][0] = PointArray[i+1][0];
			PointArray[i][1] = PointArray[i+1][1];
		}
	}
}

// Lijevi klik za kontrolnu tocku
void myMouseFunc( int button, int state, int x, int y ) {
	if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ) {
		float xPos = ((float)x)/((float)(WindowWidth-1));
		float yPos = ((float)y)/((float)(WindowHeight-1));

		yPos = 1.0f-yPos;	   //pocetni yPos je bio od ishodista u gornjem lijevom kutu pa je y naopaka, pa ovo moram da zarotiram		

		addNewPoint( xPos, yPos );
		glutPostRedisplay();
	}
}

// Nova tocka na kraj liste
// Makni prvu ako ih je previse
void removeLastPoint() {
	if ( NumPts>0 ) {
		NumPts--;
	}
}

// Nova tocka na kraj liste
// Makni prvu ako ih je previse
void addNewPoint( float x, float y ) {
	if ( NumPts>=MaxNumPts ) {
		removeFirstPoint();
	}
	PointArray[NumPts][0] = x;
	PointArray[NumPts][1] = y;
	NumPts++;
}

void displayLines(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the line segments
	glColor3f(1.0f, 0.0f, 0.8f);			// Crvenkasto ruzicaste linije
	if ( NumPts>1 ) {
		glBegin( GL_LINE_STRIP );
		for ( i=0; i<NumPts; i++ ) {
		   glVertex2f( PointArray[i][0], PointArray[i][1] );
		}
		glEnd();
	}

	// Onda nacrtaj interpoliranu tocku
	glColor3f( 0.0f, 0.0f, 0.0f);			// u crnom
	glBegin( GL_POINTS );
	for ( i=0; i<NumPts; i++ ) {
	   glVertex2f( PointArray[i][0], PointArray[i][1] );
	}
	glEnd();

	glFlush();
}

void initRendering() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	// Velike tocke i siroke linije
	glPointSize(8);
	glLineWidth(5);

	// Okrugle tocke i antialijasiranje, ovisno o implementaciji
	
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Okrugle a ne cetvrtaste tocke
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialijasiranje
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void resizeWindow(int w, int h)
{
	WindowHeight = (h>1) ? h : 2;
	WindowWidth = (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  // Uvijek se gleda [0,1]x[0,1].
	glMatrixMode(GL_MODELVIEW);  		 
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB ); 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initRendering();

	glutDisplayFunc(displayLines);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(myKeyboardFunc);
	glutMouseFunc(myMouseFunc);
	glutMainLoop();

	return 0;					// Nikad se ne ivrsi, zahtijeva ANSI C
}
