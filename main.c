#include <GL/glut.h>
#include <stdio.h>
//   |************************************|
//   |||||||_ATIVIDADE BONUS 2_CG_|||||||||
//   |************************************|
//   | Aluno: Higor Luiz Farinha Celante  |
//   | R.A.: 1602870                      |
//   |************************************|


//   |***********************************************|
//   | Executando:                                   |
//   |"gcc bonus2.c -o executavel -lGL -lglut -lGLU" |
//   |***********************************************|


// Variavel global de rotacao
static GLfloat spin = 0.0;


// Metodo de inicializacao
int init(void);
// Metodo de display
void display(void);
// Metodo criador das viewports
void init_Viewports(int xvmin, int yvmin, int vn);
// Inicializacao da camera
void init_Camera(float x0, float y0, float z0, float vx, float vy, float vz, int vn);
// Metodo que rotaciona o objeto
void spin_Objeto(void);


int init(void){

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.72, -1.5, 1.5);
}

void init_Viewports(int xvmin, int yvmin, int vn){
    glViewport(xvmin, yvmin, 400, 400);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(vn == 5){
        gluPerspective(70, 1.0, 1.0, 50);
    } else {
        glOrtho(-3, 3, -3, 3, 1, 50); // xvmin, xvmax, xwmin, ywmax, near, far
    }
}



void init_Camera(float x0, float y0, float z0, float vx, float vy, float vz, int vn){

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( x0,  y0,  z0,
              0.0, 0.0, 0.0,
               vx,  vy,  vz);

    float sizeTeaPoat = 2.0;

    if(vn == 4){
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float rotation_A = spin;
        int rotation_B = rotation_A;
        int angle = rotation_B % 365;

        glRotatef(spin, 0.0, 0.0, 1.0);
        glRotatef(angle, 1.0, 0.0, 0.0);
        sizeTeaPoat = 0.6;
    }

    glutWireTeapot(sizeTeaPoat);
}

void spin_Objeto(void){
   spin = spin + 0.4;
   if (spin > 360.0)
      spin = 0;

   glutPostRedisplay();
}

void createViewPort(){

    init_Viewports(000, 400, 1);
    init_Camera(0.0, 1.0, 0.0, 0.0, 0.0, -1.0, 1);

    init_Viewports(400, 400, 2);
    init_Camera(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);

    init_Viewports(000, 000, 3);
    init_Camera(0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 3);

    init_Viewports(400, 000, 4);
    init_Camera(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 4);
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f);
    createViewPort();

    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(800, 800);           // tamanho da janela
    glutInitWindowPosition(200, 200);       // posicao da janela 
    glutCreateWindow("Atividade bonus 2");  // criacao da janela
    glutIdleFunc(spin_Objeto);              // rotacao do objeto
    glutDisplayFunc(display);               // metodo display
    init();                                 // meotodo de inicializacao
    glutMainLoop();                         // metodo de loop da main da lib glut
    return 0;
}
