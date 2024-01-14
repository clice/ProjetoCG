#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// LISTA DE FUNÇÕES
void opcoesMenu(void);
void selecionarOpcao(int opcao);
void telaInicial(void);

// VARIÁVEIS DE TELA
static int tela;
static int menuPrincipal;
static int menuCriarObjetos;
static int menuSelecionarObjetos;

// Valor recebido da opção pelo usuário
static int opcao = 0;

int ponto = -1;
int reta = -1;
int poligono = -1;

int estado = 0;
int desenhandoReta = -1;
int desenhandoPoligono = -1;

// Variáveis das dimensões
float largura;
float altura;

// FUNÇÃO PARA DEFINIR AS OPÇÕES DO MENU
void opcoesMenu()
{
    // Opção de criar ponto, segmento de reta ou poligono
    menuCriarObjetos = glutCreateMenu(selecionarOpcao);
    glutAddMenuEntry("Ponto", 1);
    glutAddMenuEntry("Segmento de Reta", 2);
    glutAddMenuEntry("Poligono", 3);

    // Opção de selecionar um ponto, segmento de reta ou poligono
    menuSelecionarObjetos = glutCreateMenu(selecionarOpcao);
    glutAddMenuEntry("Ponto", 4);
    glutAddMenuEntry("Segmento de Reta", 5);
    glutAddMenuEntry("Poligono", 6);

    // Menu principal para mostrar opções
    menuPrincipal = glutCreateMenu(selecionarOpcao);
    glutAddSubMenu("Criar", menuCriarObjetos);
    glutAddSubMenu("Selecionar", menuSelecionarObjetos);
    glutAddMenuEntry("Cancelar", 0);
    glutAddMenuEntry("Sair", -1);

    // Utilizar o botão direito do mouse para acionar o menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// FUNÇÃO PARA SELECIONAR OPÇÃO DO MENU
void selecionarOpcao(int opcaoSelecionada)
{
    // Se o usuário escolheu "Sair" encerra e finaliza a tela
    if (opcaoSelecionada == -1) {
        glutDestroyWindow(tela);
        exit(0);
    }
    // Caso o usuário tenha selecionado alguma outra opção
    else {
        printf("Opcao selecionada: %d\n", opcaoSelecionada);
        opcao = opcaoSelecionada;
        ponto = -1;
        reta = -1;
        poligono = -1;
        estado = 0;
        desenhandoReta = -1;
        desenhandoPoligono = -1;
    }

    glutPostRedisplay();
}

// FUNÇÃO PARA CONFIGURAR A TELA INICIAL
void telaInicial()
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
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    tela = glutCreateWindow("Paint - Computacao Grafica");

    // Mostrar menu
    opcoesMenu();

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-largura, largura, -altura, altura, -1.0f, 1.0f);

    glutDisplayFunc(telaInicial);
    glutMainLoop();
    return 0;
}
