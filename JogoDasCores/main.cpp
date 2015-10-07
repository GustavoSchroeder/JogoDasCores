using namespace std;

#include "stdafx.h"
#include <windows.h>		// Must have for Windows platform builds
#include <GL/gl.h>
#include <GL/glu.h>
#include <freeglut_std.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <cmath>

#include "retangulo.h"

const int X = 32;
const int Y = 32;
retangulo ret[X][Y];
int rPrimeira;
int gPrimeira;
int bPrimeira;
int percentual = 8;
int pontos = 0;
int tentativas = 0;
int maxTentativas = 32;



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	//glRotatef(spin, 0.0, 0.0, 1.0);
	//gluOrtho2D(-25.0, -25.0, 25.0, 25.0);
	glPopMatrix();
	glutSwapBuffers();

	int largura = 2;
	int altura = 2;
	for (int i = 0; i < X; i++){
		for (int j = 0; j < Y; j++){
			float r = ret[i][j].getRed() / 256;
			float g = ret[i][j].getGreen() / 256;
			float b = ret[i][j].getBlue() / 256;
			bool v = ret[i][j].isVisivel();
			if (v == true){
				glColor3f(r, g, b);
			}
			else{
				glColor3f(1, 1, 1);
			}
			
			glBegin(GL_POLYGON);
				glVertex2f(-34 + largura, 34 - altura);
				glVertex2f(-32 + largura, 34 - altura);
				glVertex2f(-32 + largura, 32 - altura);
				glVertex2f(-34 + largura, 32 - altura);
			glEnd();
			glColor3f(0.0f, 0.0f, .0f);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-34 + largura, 34 - altura);
				glVertex2f(-32 + largura, 34 - altura);
				glVertex2f(-32 + largura, 32 - altura);
				glVertex2f(-34 + largura, 32 - altura);
			glEnd();
			largura += 2;
			if (j == Y-1){
				largura = 2;
				altura += 2;
			}
		}
	}
	glFlush();
}

void verificaCores(int x, int y){

	int iT = y / 18.75;
	int jT = x / 25;
	if (ret[iT][jT].isVisivel() == true) {
		printf("Posicao do array: ret[%d][%d]\n", iT, jT);

		rPrimeira = ret[iT][jT].getRed();
		gPrimeira = ret[iT][jT].getGreen();
		bPrimeira = ret[iT][jT].getBlue();

		for (int i = 0; i < X; i++){
			for (int j = 0; j < Y; j++){
				int rSegunda = ret[i][j].getRed();
				int gSegunda = ret[i][j].getGreen();
				int bSegunda = ret[i][j].getBlue();

				double raiz = (rPrimeira - rSegunda) * (rPrimeira - rSegunda);
				raiz += (gPrimeira - gSegunda) * (gPrimeira - gSegunda);
				raiz += (bPrimeira - bSegunda) * (bPrimeira - bSegunda);

				raiz = sqrt(raiz);

				double distancia = (percentual * 441.67) / 100;

				if (raiz < distancia){
					ret[i][j].setVisivel(false);
					pontos += 1;
				}
			}
		}
		glutPostRedisplay();
	}
	else{
		printf("Retangulo clicado nao esta visivel!");
		tentativas -= 1;
	}
}


void mouse(int button, int state, int x, int y){
	if (button == 0 && state == 0 && tentativas < maxTentativas){
		verificaCores(x, y);
		tentativas += 1;
		printf("Pontos: %d\n", pontos);
	}
	
}


///////////////////////////////////////////////////////////
// Setup the rendering state
void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLoadIdentity();
	gluOrtho2D(-32.0, 32.0, -32.0, 32.0);
	glShadeModel(GL_FLAT);

	
	srand((unsigned)time(NULL));
	for (int i = 0; i < X; i++){
		for (int j = 0; j < Y; j++){
			int r = rand() % 256 + 0;
			int g = rand() % 256 + 0;
			int b = rand() % 256 + 0;
			ret[i][j].iniciaRetangulo(true, r, g, b);
		}
	}
}
///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	int id = glutCreateWindow("Jogo das Cores");

	// definição de funções de call-back
	glutDisplayFunc(display);
	//glutReshapeFunc(ChangeSize);
	glutMouseFunc(mouse);

	// inicializações e definições constantes
	init();

	// inicio do pipe-line OpenGL
	glutMainLoop();

	return 0;
}