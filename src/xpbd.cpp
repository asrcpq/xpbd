#include <cstdlib>

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "cloth.cpp"
#include "ball.h"
#include "emode.h"

CApplication g_Application;
CCloth g_Cloth(2.0F, 2.0F, 20, 20);
CBall g_Ball(0.3F);

void render_string(std::string& str, int w, int h, int x0, int y0) {
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(x0, y0);
	int size = (int)str.size();
	for(int i = 0; i < size; ++i){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void init(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_CULL_FACE);

	GLfloat time = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	g_Application.SetTime(time);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LESS); 
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glPushMatrix();
	g_Cloth.Render();
	glPopMatrix();

	glPushMatrix();
	g_Ball.Render();
	glPopMatrix();

	glColor3d(1.0f, 1.0f, 1.0f);
	char debug[128];
	sprintf(debug, "ITERATION %d", g_Application.m_IterationNum);
	std::string iteration_text(debug);
	render_string(iteration_text, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 10, 20);
	sprintf(debug, "%s", MODE_STRING[g_Application.m_Mode]);
	std::string mode_text(debug);
	render_string(mode_text, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 10, 40);
	sprintf(debug, "TIME %d(ms)", g_Application.GetSolveTime());
	std::string time_text(debug);
	render_string(time_text, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 10, 60);

	glutSwapBuffers();
}

void reshape(int width, int height){
	static GLfloat lightPosition[4] = {0.0f,  2.5f,  5.5f, 1.0f};
	static GLfloat lightDiffuse[3]  = {1.0f,  1.0f,  1.0f      };
	static GLfloat lightAmbient[3]  = {0.25f, 0.25f, 0.25f     };
	static GLfloat lightSpecular[3] = {1.0f,  1.0f,  1.0f      };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)width / (double)height, 0.0001f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(4.0f, 0.0f, 3.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // pos, tgt, up

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

void idle(void){
	GLfloat time = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	GLfloat dt = time - g_Application.GetTime();

	dt = (dt > 0.033f) ? 0.033f : dt; // keep 30fps

	g_Ball.Update(dt);
	g_Cloth.Update(g_Application, dt, &g_Ball, g_Application.m_IterationNum);

	g_Application.SetTime(time);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
	(void)x;
	(void)y;
	switch(key){
		case 'q': exit(0); break;
	}
}

void special(int key, int x, int y){
	(void)x;
	(void)y;
	if (key == GLUT_KEY_UP) {
		g_Application.m_IterationNum++;
	}
	if (key == GLUT_KEY_DOWN) {
		if (g_Application.m_IterationNum > 1){
			g_Application.m_IterationNum--;
		}
	}
	if (key == GLUT_KEY_LEFT) {
		if (g_Application.m_Mode > eModePBD) {
			g_Application.m_OldMode = g_Application.m_Mode;
			g_Application.m_Mode--;
		}
	}
	if (key == GLUT_KEY_RIGHT) {
		if (g_Application.m_Mode < eModeMax - 1) {
			g_Application.m_OldMode = g_Application.m_Mode;
			g_Application.m_Mode++;
		}
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("XPBD");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glutMainLoop();
	return 0;
}
