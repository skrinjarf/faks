
// Header za dots.c

void myKeyboardFunc( unsigned char key, int x, int y );
void myMouseFunc( int button, int state, int x, int y );
void rotatefunkcija();

void displayLines(void);
void removeFirstPoint();
void removeLastPoint();
void addNewPoint( float x, float y );

void initRendering();
void resizeWindow(int w, int h);



