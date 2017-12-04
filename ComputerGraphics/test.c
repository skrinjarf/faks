#include <stdio.h>


int main(void)
{
  printf("hello world\n");
  glBegin(triangles);
  glVertex2f(1,1);
  glVertex2f(2,1);
  glVertex2f(1,2);
  glEnd;
  return 0;
}
