#include <iostream>
#include <GL/glut.h>
using namespace std;

GLint Width = 500, Height = 500;
GLint broj=0;

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
	broj=1;
}

static void Key_down(void)
{
    broj=0;	

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



void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			

	glClearColor(0, 0, 0, 1);


	glLoadIdentity(); 	
	
	glPushMatrix();
	if( !broj ){
	glTranslatef( 1.0, 3.0, 0.0 );
	glRotatef(-90.0, 0.0, 0.0, 1.0);	
	}		

	glColor3f(1.0, 1.0, 0.0);

        glBegin( GL_TRIANGLES );
            glVertex3f( 0.0,1.0,0.0  );
            glVertex3f( -1.0,-1.0,0.0  );
            glVertex3f( 1.0 ,-1.0 ,0.0   );
        glEnd ( );

	glPopMatrix();

	glColor3f(1.0, 0.0, 0.0);

        glBegin( GL_LINES );
            	glVertex3f( -5.0,0.0,1.0  );
 	    	glVertex3f( 5.0,0.0,1.0  );
		glVertex3f( 0.0,-5.0,1.0  );
		glVertex3f( 0.0,5.0,1.0  );		
        glEnd ( );


	glFlush();
   	glutSwapBuffers();
   	glutPostRedisplay();	// Automatsko iscrtavanje


}


void resizeWindow(GLint w, GLint h)
{
  Width = w;
  Height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( -6, 6, -6, 6, -1, 1 );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main( int argc, char** argv )
{
	glutInit(&argc,argv);

	// double buffering (nije bas bitno) 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Window position
	glutInitWindowPosition( 20, 60 );
	glutInitWindowSize( Width, Height  );
	glutCreateWindow( "SimpleDraw" );

	// Initialize OpenGL 
	initRendering();

	//glutKeyboardFunc( myKeyboardFunc );	// Normalni  ascii znakovi
	glutSpecialFunc( mySpecialKeyFunc );	// Specijalni ascii znakovi
	// glutMouseFunc(Mouse);

	glutReshapeFunc( resizeWindow );
	//glutIdleFunc( myIdleFunction );
	glutDisplayFunc( drawScene );
	glutMainLoop(  );

	return(0);	// Zahtijeva sintaksa, ali se do nje nikad ne dodje
}
