#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "ponto.h"

///////////////////////////////////////////////////////////////////

/*
 * VARIÁVEIS DE TELA
 */
static int tela;
static int menuPrincipal;
static int menuCriarObjetos;
static int menuSelecionarObjetos;

/*
 * VALOR RECEBIDO PELO USUÁRIO PARA OPÇÃO
 */
static int opcao = 0;

/*
 * INICIALIZANDO VARIÁVEIS PARA PONTO, RETA E POLIGONO
 */
int aux = -1;
int ponto = -1;
int reta = -1;
int poligono = -1;

/*
 *
 */
int desenhandoReta = -1;
int desenhandoPoligono = -1;

/*
 * VARIÁVEIS DO MOUSE
 */
float largura = 400;
float altura = 300;
float mouseX;
float mouseY;
int estadoMouse = 0;

///////////////////////////////////////////////////////////////////

ListaPontos * listaPontos = NULL;

///////////////////////////////////////////////////////////////////

/*
 * LISTA DE FUNÇÕES
 */
int main(int argc, char ** argv);
void desenharTela();
void telaInicial();
void opcoesMenu();
void selecionarOpcao(int opcaoSelecionada);
void funcoesMouse(int botaoMouse, int estadoMouse, int x, int y);
void funcoesTeclado(int tecla, int x, int y);

/*
 * FUNÇÃO PARA INICIAR O SISTEMA
 */
int main (int argc, char ** argv)
{
    // Inicializando o OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    tela = glutCreateWindow("Paint - Computacao Grafica");

    // Mostrar menu
    opcoesMenu();

    //
    listaPontos = criarListaPontos();

    glClearColor(1.0, 1.0, 1.0, 0.0); // Cor do background
    glMatrixMode(GL_PROJECTION);
    glOrtho(-largura, largura, -altura, altura, -1.0f, 1.0f);

    glutMouseFunc(funcoesMouse);
    glutSpecialFunc(funcoesTeclado);
    glutDisplayFunc(telaInicial);
    glutMainLoop();
    return 0;
}

/*
 * FUNÇÃO PARA DEFINIR AS OPÇÕES DO MENU
 */
void desenharTela()
{
    // glColor3f(0.0, 0.0, 0.0);
    // glBegin(GL_LINES);
    // glVertex2i(-400, 0);
    // glVertex2i(400, 0);
    // glVertex2i(0, -300);
    // glVertex2i(0, 300);
    // glEnd();
}

/*
 * FUNÇÃO PARA CONFIGURAR A TELA INICIAL
 */
void telaInicial()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicializando os desenhos da tela
    desenharTela();
    desenharPontos(ponto, listaPontos);

    glutSwapBuffers();
}

/*
 * FUNÇÃO PARA DEFINIR AS OPÇÕES DO MENU
 */
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
    glutAddMenuEntry("Salvar", 7);
    glutAddMenuEntry("Cancelar", 0);
    glutAddMenuEntry("Sair", -1);

    // Utilizar o botão direito do mouse para acionar o menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*
 * FUNÇÃO PARA SELECIONAR A OPCAO INDICADA PELO USUÁRIO
 */
void selecionarOpcao(int opcaoSelecionada)
{
    // Se o usuário escolheu "Sair" encerra e finaliza a tela
    if (opcaoSelecionada == -1) {
        glutDestroyWindow(tela);
        exit(0);
    }
    // Caso o usuário tenha selecionado alguma outra opção
    else {
        opcao = opcaoSelecionada;
        printf("Opcao selecionada: %d\n", opcao);
        estadoMouse = 0;
        ponto = -1;
    }

    glutPostRedisplay();
}

/*
 * FUNÇÃO PARA DEFINIR O USO DO MOUSE PELO USUÁRIO
 */
void funcoesMouse(int botaoMouse, int estadoMouse, int x, int y)
{
    printf("x: %d, y: %d\n", x, y);
    printf("largura: %f, altura: %f\n", largura, altura);

    // Localização atualizada do mouse
    mouseX = x - largura;  // Localização do eixo x (horizontal - largura)
    mouseY = altura - y;   // Localização do eixo y (vertical - altura)

    printf("mouseX: %f, mouseY: %f\n", mouseX, mouseY);

    // Se o botão esquerdo do mouse foi pressionado
    if (botaoMouse == GLUT_LEFT_BUTTON && estadoMouse == GLUT_DOWN) {
        ////////// Opções Criar
        // Se a opção for 1 (Criar ponto)
        if (opcao == 1) { 
            adicionarPonto(mouseX, mouseY, listaPontos);
        }
        // Se a opção for 2 (Criar segmento de reta)
        else if (opcao == 2) {

        }
        // Se a opção for 3 (Criar polígono)
        else if (opcao == 3) {

        }

        ////////// Opção Selecionar
        // Se a opção for 4 (Selecionar ponto)
        else if (opcao == 4) {
            ponto = selecionarPonto(listaPontos, mouseX, mouseY, aux);
            printf("-----mouseX: %f, mouseY: %f\n", mouseX, mouseY);
            MatrizTransformacao * matrizTranslacao = criarMatrizTranslacao(
                    mouseX - listaPontos->pontos[ponto].x,
                    mouseY - listaPontos->pontos[ponto].y
                );
            transladarPonto(ponto, listaPontos, matrizTranslacao);
        }
        // Se a opção for 5 (Selecionar segmento de reta)
        else if (opcao == 5) {

        }
        // Se a opção for 6 (Selecionar polígono)
        else if (opcao == 6) {

        }

        ////////// Opção Salvar
        else if (opcao == 7) {
             salvarPontos(listaPontos);
        }

        ////////// Opção Cancelar
        else if (opcao == 0) {

        }
    }

    glutPostRedisplay();
}

/*
 * FUNÇÃO PARA DEFINIR O USO DO TECLADO PELO USUÁRIO
 */
void funcoesTeclado(int tecla, int x, int y)
{
    printf("Tecla: %d\n", tecla);
    printf("x: %d, y: %d\n", x, y);
    printf("ponto: %d\n", ponto);

    // Opções Selecionar
    if (tecla == GLUT_KEY_F1) {
        if (opcao == 4 && ponto != -1) {
            if (removerPonto(ponto, listaPontos)) {
                if (estadoMouse != 0) estadoMouse = 0;
                ponto = -1;
            }
        }
    }
}
