
#include <math.h>	
#include <stdio.h>
#include <stdlib.h>		
#include <GL/glut.h>
#include <time.h>	

double x1 = 1, y2 = 0, z1 = 0;

void myKeyboardFunc( unsigned char key, int x, int y ){
	switch ( key ) {

	case ' ':	
		x1 = 1.0/(rand()%100+1);
		y2 = 1.0/(rand()%100+1);
		z1 = 1.0/(rand()%100+1);
		glutPostRedisplay();
		break;

	case 27:
		exit(1);

	}
}

void display(void){

    glClear (GL_COLOR_BUFFER_BIT);
//  glShadeModel( GL_FLAT); //nema sjencanja linija i poligona
	glShadeModel( GL_SMOOTH);  //mjesanje boja
//	glPolygonMode ( GL_FRONT, GL_LINE );  //nema popunjavanja poligona
	glBegin( GL_TRIANGLES );

		glColor3f( x1, 0.1*y2, 0.5 );
		glVertex3f( 0.0, 0.0, 0.0 );
		
		glColor3f( 0.5,y2, 0.3*x1 );
		glVertex3f( 1.0, 0.0, 0.0 );		

		glColor3f( 0.9*x1, 0.5, z1 );		
		glVertex3f( 0.0, 1.0, 0.0 );

	glEnd ( );

    glFlush ();
}

void init (void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(3);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1, -1.0, 1, -1, 1);
}


int main(int argc, char** argv){

	srand( time(NULL) );
 
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (850, 850); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Trokutic");
    init ();
	glutKeyboardFunc( myKeyboardFunc );	
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}



