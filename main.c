#include <GL/glut.h>
#include <windows.h>

typedef struct{
    float x;
    float y;
    int h;
}Ponto;

typedef struct{
    Ponto a;
    Ponto b;
}Reta;

void rotacionar(Ponto p, int teta){
    float matrizR[3][3];
    matrizR[0][2] = 0; matrizR[1][2] = 0; matrizR[2][2] = 1; matrizR[2][0] = 0; matrizR[2][1] = 0;
}
void transladar(Ponto p, float tx, float ty){
    float matrizT[3][3];
    matrizT[0][0] = 1; matrizT[1][1] = 1; matrizT[2][2] = 1; matrizT[2][0] = 0; matrizT[2][1] = 0;
    matrizT[0][2] = tx; matrizT[1][2] = ty; matrizT[0][1] = 0; matrizT[1][0] = 0;
}
void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.0, 0.5);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}

void init(void);
void createMenu(void);
void menu(int value);

static int win;
static int mainmenu;
static int criar;
static int selecionar;
static int val = 0;

int tolerancia = 5;
int ponto = -1;
int reta = -1;
int poligono = -1;

int estado = 0;
int desenhandoReta = -1;
int desenhandoPoligono = -1;

float theta = 0.05;
float scale = 1.05;
float border = 1.03;

float Width = 300;
float Height = 300;
float mousex, mousey;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-Width, Width, -Height, Height, -1.0f, 1.0f);
}

void mostrarMenu()
{
    criar = glutCreateMenu(menu);
    glutAddMenuEntry("Ponto", 1);
    glutAddMenuEntry("Reta", 2);
    glutAddMenuEntry("Poligono", 3);

    selecionar = glutCreateMenu(menu);
    glutAddMenuEntry("Ponto", 4);
    glutAddMenuEntry("Reta", 5);
    glutAddMenuEntry("Poligono", 6);

    mainmenu = glutCreateMenu(menu);
    glutAddSubMenu("Criar", criar);
    glutAddSubMenu("Selecionar", selecionar);
    glutAddMenuEntry("Cancelar", 0);
    glutAddMenuEntry("Sair", -1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int value)
{
    if (value == -1) {
        glutDestroyWindow(win);
        exit(0);
    } else {
        val = value;
        ponto = -1;
        reta = -1;
        poligono = -1;
        estado = 0;
        desenhandoReta = -1;
        desenhandoPoligono = -1;
    }

    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // desenhaPlano();
    // desenhaPoligonos(Poligonos, poligono, borda);
    // desenhaRetas(Retas, reta);
    // desenhaPontos(Pontos, ponto);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    // Inicializando o OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    win = glutCreateWindow("Paint - Computação Gráfica");

    // Mostrar menu
    mostrarMenu();

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
