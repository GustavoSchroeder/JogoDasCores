using namespace std;

#include "stdafx.h"
#include <windows.h>		
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
int red, green, blue;  
int percentual = 8;
int pontuacao = 0;
int tentativas = 0;
int maxTentativas = 32;



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glPopMatrix();
	glutSwapBuffers();

	int width = 2;
	int height = 2;
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
				glVertex2f(-34 + width, 34 - height);
				glVertex2f(-32 + width, 34 - height);
				glVertex2f(-32 + width, 32 - height);
				glVertex2f(-34 + width, 32 - height);
			glEnd();
			glColor3f(0.0f, 0.0f, .0f);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-34 + width, 34 - height);
				glVertex2f(-32 + width, 34 - height);
				glVertex2f(-32 + width, 32 - height);
				glVertex2f(-34 + width, 32 - height);
			glEnd();
			width += 2;
			if (j == Y-1){
				width = 2;
				height += 2;
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

		red = ret[iT][jT].getRed();
		green = ret[iT][jT].getGreen();
		blue = ret[iT][jT].getBlue();

		for (int i = 0; i < X; i++){
			for (int j = 0; j < Y; j++){
				int redS = ret[i][j].getRed();
				int greenS = ret[i][j].getGreen();
				int blueS = ret[i][j].getBlue();

				double raiz = (red - redS) * (red - redS);
				raiz += (green - greenS) * (green - greenS);
				raiz += (blue - blueS) * (blue - blueS);

				raiz = sqrt(raiz);

				double distancia = (percentual * 441.67) / 100;

				if (raiz < distancia){
					ret[i][j].setVisivel(false);
					pontuacao += 1;
				}
			}
		}
		glutPostRedisplay();
	}
	else{
		printf("Errou!");
		tentativas -= 1;
	}
}


void mouse(int button, int state, int x, int y){
	if (button == 0 && state == 0 && tentativas < maxTentativas){
		verificaCores(x, y);
		tentativas += 1;
		printf("pontuacao: %d\n", pontuacao);
	}
	
}

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
