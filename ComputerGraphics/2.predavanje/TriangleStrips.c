#include <stdio.h>
#include <stdlib.h>		
#include <GL/glut.h>
#include <GL/gl.h>

void display(void){

    glClear (GL_COLOR_BUFFER_BIT);
	glShadeModel( GL_FLAT); 

	glBegin( GL_TRIANGLE_STRIP );
	glColor3f(0,0,1);
	//prvi trokut
	glVertex2f(0,0);	
	glVertex2f(1,1);																									//	glColor3f( 0, 0.1, 0.5 );
	glVertex2f(0,2);																										//	glVertex3f( 0.0, 0.0, 0.0 );
	
	//drugi																										
	glColor3f(1,0,0);																									
	glVertex2f(1.5,1.5);	
	glVertex2f(2.0,2.0);

	//treci
	glColor3f(1,1,0);
	glVertex2f(2,1);
	
	glEnd ( );
	
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,0);
	glVertex2f(2,1);
	glVertex2f(1.5,1.5);
	glVertex2f(1.5,0.5);
	
	//cetvrti
	
	glColor3f(1,0.5,0.8);
	glVertex2f(1,1);
	
	//peti
	glColor3f(1,0.5,0);
	glVertex2f(1,0);
    glVertex2f(0.5,0.5);
    
    //sesti
    
    glColor3f(0,1,0);
    glVertex2f(0,0);		
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.2,1,1);
	glVertex2f(1,0);
	glVertex2f(2,0);
	glVertex2f(2,1);
	glEnd();
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
    glOrtho(0, 2, 0, 2, -1, 1);  //koordinatni sustav
}

int main(int argc, char** argv){
 
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (850, 850); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Tangram");
    init ();
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}
