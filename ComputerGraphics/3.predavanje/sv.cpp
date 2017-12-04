#include <iostream>
#include <GL/glut.h>
using namespace std;

GLint Width = 1000, Height = 1000;
// These three variables control the animation's state and speed.
static float broj = 0.0;
static float AnimateIncrement = 24.0;  // Time step for animation (hours)
static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;

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

static void Key_up(void)
{
    AnimateIncrement *= 2.0;			// Double the animation time step
}

static void Key_down(void)
{
    AnimateIncrement /= 2.0;			// Halve the animation time step
	
}

static void mySpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key ) {
	case GLUT_KEY_UP:		
		Key_up();
		break;
	case GLUT_KEY_DOWN:
		Key_down();
		break;
	}
}

static void Key_r(void)
{
	if ( singleStep ) {			// If ending single step mode
		singleStep = GL_FALSE;
		spinMode = GL_TRUE;		// Restart animation
	}
	else {
		spinMode = !spinMode;	// Toggle animation on and off.
	}
}

static void Key_s(void)
{
	singleStep = GL_TRUE;
	spinMode = GL_TRUE;
}

static void KeyPressFunc( unsigned char Key, int x, int y )
{
	switch ( Key ) {
	case 'R':
	case 'r':
		Key_r();
		break;
	case 's':
	case 'S':
		Key_s();
		break;
	}
}



void drawScene(void)
{
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0, 0, 0, 1);
	glColor3f(1.0, 1.0, 0.0);
	
    if (spinMode) {
        broj += AnimateIncrement/24.0;
        broj = broj - ((int)(broj/365))*365;
		}

	glLoadIdentity();	
	
	glTranslatef( Width/2, Height/2, 0.0 );
	
	glRotatef( 90, -1.0, 0.0, 0.0 );		//prodizanje da se lijepo vidi kako se vrti
 	
	glRotatef( 360.0*broj/365.0, 0.0, 0.0, 1.0 ); 
	glRotatef( 20, 0.0, 1.0, 0.0 );			//oscilacija nagiba osi

	glutWireSphere( 150, 14, 15 );

	glColor3f(1.0, 1.0, 1.0);
	glBegin( GL_LINES );
		glVertex3f( 0.0,0.0,200.0  );
		glVertex3f( 0.0,0.0,-200.0  );		
        glEnd ();

	
	if ( singleStep ) {
		spinMode = GL_FALSE;
	}
	

	glFlush();
   	 glutSwapBuffers();

	glutPostRedisplay();	


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
	glutInitWindowSize( Width, Height  );
	glutCreateWindow( "SimpleDraw" );


	initRendering();

	glutKeyboardFunc( KeyPressFunc );		
	glutSpecialFunc( mySpecialKeyFunc );	

	glutReshapeFunc( resizeWindow );

	glutDisplayFunc( drawScene );
	glutMainLoop(  );

	return(0);	
}
