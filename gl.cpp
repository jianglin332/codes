#include <GL/glut.h>
#include <cmath>
void myDisp()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	for (double i = -10; i <= 10; i += 0.1)
		glVertex2d(i, i * i);
	glEnd();
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("First OpenGL Program");
	glutReshapeFunc(&reshape);
	glutDisplayFunc(&myDisp);
	glutMainLoop();
	return 0;
}
