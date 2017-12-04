#include <iostream>
#include <GL/glut.h>

using namespace std;



void initRendering()
{
	glEnable( GL_DEPTH_TEST );
	glPointSize(8);
	glLineWidth(1);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Okrugle a ne cetvrtaste tocke
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialijasiranje

}

void resizeWindow(GLint w, GLint h)
{
  Width = w;
  Height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, 0, h, -500, 500);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


int main( int argc, char** argv )
{
	glutInit(&argc,argv);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );


	glutInitWindowPosition( 20, 60 );
	glutInitWindowSize( 200, 200  );
	glutCreateWindow( "Zrcaljenje" );


	initRendering();

	glutReshapeFunc( resizeWindow );

	glutDisplayFunc( drawScene );
	glutMainLoop(  );

	return(0);	
