/*
 * SimpleDraw.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h> 
#include "SimpleDraw.h"

// Varijable koje kontroliraju trenutni nacin crtanja
int CurrentMode = 0;
const int NumModes = 5;

// Dimenzije pravokutnika od interesa za gledanje
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

// glutKeyboardFunc za sve normalne ascii znakove s tipkovnice
// koriste se samo blank i esc
void myKeyboardFunc( unsigned char key, int x, int y )    //trenutni x i y polozaj misa
{
	switch ( key ) {

	case ' ':									//  blank
		// povecaj trenutni nacin i poruka OS-u za iscrtavanje
		CurrentMode = (CurrentMode+1)%NumModes;
		glutPostRedisplay();					//zahtjev glutu da ponovno crta display
		break;

	case 27:									// "27" Escape 
		exit(1);

	}
}


/*
 * drawScene() animacija i obnavljanje prozora
*/
void drawScene(void)
{
	// Ocisti prozor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //GL_DEPTH_BUFFER_BIT je buffer za dubinu

	// Boja za crtanje je bijela
	glColor3f( 1.0, 1.0, 1.0 );		

	switch (CurrentMode)
	{

	case 0:
		// Nacrtaj tri tocke
		glBegin(GL_POINTS);
		glVertex2f( 1.0, 1.0 );
		glVertex2f( 2.0, 1.0 );
		glVertex2f( 2.0, 2.0 );
		glEnd();
		break;

	case 1:
	case 2:
	case 3:
		if ( CurrentMode==1 ) {
			// Crtaj linije u GL_LINES 
			glBegin( GL_LINES );
		}
		else if ( CurrentMode==2 ) {
			// Crtaj linije u  GL_LINE_STRIP 
			glBegin( GL_LINE_STRIP );
		}
		else {
			// Crtaj linije u GL_LINE_LOOP 
			glBegin( GL_LINE_LOOP );
		}
		glVertex2f( 0.5, 1.0 );
		glVertex2f( 2.0, 2.0 );
		glVertex2f( 1.8, 2.6 );
		glVertex2f( 0.7, 2.2 );
		glVertex2f( 1.6, 1.2 );
		glVertex2f( 1.0, 0.5 );
		glEnd();
		break;

	case 4:			// Preklapajuci trokuti
		glBegin( GL_TRIANGLES );
		glColor3f( 1.0, 0.0, 0.0 );
		glVertex3f( 0.3, 1.0, 0.5 );
		glVertex3f( 2.7, 0.85, 0.0 );
		glVertex3f( 2.7, 1.15, 0.0 );

		glColor3f( 0.0, 1.0, 0.0 );
		glVertex3f(2.53, 0.71, 0.5 );
		glVertex3f(1.46, 2.86, 0.0 );
		glVertex3f(1.2, 2.71, 0.0 );

		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f(1.667, 2.79, 0.5);
		glVertex3f(0.337, 0.786, 0.0);
		glVertex3f(0.597, 0.636, 0.0);
		glEnd();
	}

	// Forsiraj rendering; obicno ne treba
	glFlush();

}

// Inicijalizacija OpenGL renderinga
void initRendering()
{

	glEnable ( GL_DEPTH_TEST );                  //u trenutku projekcije nema z komponente pa dubina odreduje da nebude najblizi onaj koji je zadnji naljepljen nego onaj koji je po z-u najblizi.

	

	
	glPointSize(8);								//debljina tocaka
	glLineWidth(5);								//debljina linija	

// Okrugle tocke i antialijasiranje (ovisno o implementaciji)
	
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Okrugle a ne cetvrtaste tocke
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialijasiranje
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

// poziva se kod promjene velicine prozora
//		w, h - sirina i visina prozora u pixelima
void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	// Definicija podrucja gledanja
	glViewport( 0, 0, w, h );	// Cijeli prozor

	// Matrica projkecije je ortografska
	// min i max vrijednosti za x i y koje su unutra prozora
	// problem je u skaliranju slike , koje treba biti kao i skaliranje prozora
	w = (w==0) ? 1 : w;
	h = (h==0) ? 1 : h;
	if ( (Xmax-Xmin)/w < (Ymax-Ymin)/h ) {             //xmin, xmax i isto za y su stare vrijednosti     uvjet je horizontalno sirenje
		scale = ((Ymax-Ymin)/h)/((Xmax-Xmin)/w);
		center = (Xmax+Xmin)/2;							//novi centar
		windowXmin = center - (center-Xmin)*scale;
		windowXmax = center + (Xmax-center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax-Xmin)/w)/((Ymax-Ymin)/h);
		center = (Ymax+Ymin)/2;
		windowYmin = center - (center-Ymin)*scale;
		windowYmax = center + (Ymax-center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}
	
	// kad znamo dimanzije
	// mozemo odrediti i projekciju
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( windowXmin, windowXmax, windowYmin, windowYmax, -1, 1 );				//nove velicine koordinatnog sustava su izracunate dimenzije a z mi se ne mjenja

}


// Glavni program
// Inicijalizacija OpenGl-a, callback procedura i sl.
int main( int argc, char** argv )
{
	glutInit(&argc,argv);

	// Nema animacije, pa je  single buffering OK. 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

	// Window position (gornji lijevi kut), i dimenzije (sirina i visina)
	glutInitWindowPosition( 20, 60 );
	glutInitWindowSize( 360, 360 );
	glutCreateWindow( "SimpleDraw - blank za nastavak" );

	// Initialize OpenGL as we like it..
	initRendering();

	// Callback funkcije za tipkovnicu
	glutKeyboardFunc( myKeyboardFunc );		// Normalni  ascii znakovi
	// glutSpecialFunc( mySpecialKeyFunc );		// Specijalni ascii znakovi

	// Callback funkcije za promjenu velicine prozora
	glutReshapeFunc( resizeWindow );

	// Background processing
	// glutIdleFunc( myIdleFunction );

	// Pozovi kad prozor trba iscrtavanje
	glutDisplayFunc( drawScene );

	fprintf(stdout, "Space za nastavak; escape za kraj.\n");
	
	// Beskonacna petlja za procesiranje dogadjaja
	glutMainLoop(  );

	return(0);	// Zahtijeva sintaksa, ali se do nje nikad ne dodje
}
