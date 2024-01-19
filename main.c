#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "ponto.h"
#include "reta.h"

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
static int opcao = 0;  // Opção selecionada pelo usuário

/*
 * INICIALIZANDO VARIÁVEIS PARA PONTO, RETA E POLIGONO
 */
int statusObjeto = -1; // Indica se o objeto ainda está sendo desenhado (desenhando: 1; finalizado: -1)

int ponto = -1;        //
int reta = -1;         //

/*
 *
 */
int desenhandoReta = -1;
int desenhandoPoligono = -1;

/*
 * VARIÁVEIS DO MOUSE
 */
float largura = 400;   // Largura fixa da tela (metade dos pixels que formam a tela: eixo x)
float altura = 300;    // Altura fixa da tela (metade dos pixels que formam a tela: eixo y)
float mouseX;          // Posição do mouse no eixo x
float mouseY;          // Posição do mouse no eixo y
int statusMouse = 0;   // Indica se o mouse foi clicado ou não (não foi clicado: 0; clicado: 1)

///////////////////////////////////////////////////////////////////

/*
 * VARIÁVEIS DAS LISTAS DE OBJETOS PARA SEREM MANIPULADOS
 */
ListaPontos * listaPontos = NULL;
ListaRetas * listaRetas = NULL;

///////////////////////////////////////////////////////////////////

/*
 * LISTA DE FUNÇÕES
 */
int main(int argc, char ** argv);
void telaInicial();
void opcoesMenu();
void selecionarOpcao(int opcaoSelecionada);

void funcoesMouse(int botaoMouse, int statusMouse, int x, int y);
void arrastarMouse(int x, int y);

void funcoesTeclado(int tecla, int x, int y);
void gerenciarTeclado(unsigned char key, int x, int y);

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

    // Inicialização das variáveis das listas de objetos manipulados
    listaPontos = criarListaPontos();
    listaRetas = criarListaRetas();

    glClearColor(1.0, 1.0, 1.0, 0.0); // Cor do background
    glMatrixMode(GL_PROJECTION);
    glOrtho(-largura, largura, -altura, altura, -1.0f, 1.0f);

    glutMouseFunc(funcoesMouse);         //
    glutSpecialFunc(funcoesTeclado);     //
    glutDisplayFunc(telaInicial);        //
    glutKeyboardFunc(gerenciarTeclado);  // Função que é chamada quando um botão do teclado é pressionado
    glutMotionFunc(arrastarMouse);       // Função que é chamada quando um botão do mouse é mantido pressionado
    glutMainLoop();
    return 0;
}

/*
 * FUNÇÃO PARA CONFIGURAR A TELA INICIAL
 */
void telaInicial()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenhar elementos na tela
    desenharPontos(listaPontos);
    desenharRetas(reta, listaRetas);

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
    glutAddMenuEntry("Carregar", 8);
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
        // Reinicializa todas as variáveis para o valor inicial (valor que tem enquanto não estão sendo manipuladas)
        statusObjeto = -1;

        ponto = -1;
        reta = -1;

        statusMouse = 0;

        opcao = opcaoSelecionada;
        printf("Opcao selecionada: %d\n", opcao);
    }

    glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA DEFINIR O USO DO MOUSE PELO USUÁRIO
 */
void funcoesMouse(int botaoMouse, int statusMouse, int x, int y)
{
    // Localização atualizada do mouse
    mouseX = x - largura;  // Localização do eixo x (horizontal - largura)
    mouseY = altura - y;   // Localização do eixo y (vertical - altura)

    // Se o botão esquerdo do mouse foi pressionado
    if (botaoMouse == GLUT_LEFT_BUTTON && statusMouse == GLUT_DOWN) {
        printf("mouseX: %f, mouseY: %f\n", mouseX, mouseY);

        ////////// Opções Criar
        // Se a opção for 1 (Criar ponto)
        if (opcao == 1) {
            adicionarPonto(mouseX, mouseY, listaPontos);
            imprimirListaPontos(listaPontos);
        }
        // Se a opção for 2 (Criar segmento de reta)
        else if (opcao == 2) {
            statusObjeto = adicionarReta(mouseX, mouseY, statusObjeto, listaRetas);
            imprimirListaRetas(listaRetas);
        }
        // Se a opção for 3 (Criar polígono)
        else if (opcao == 3) {

        }

        ////////// Opção Selecionar
        // Se a opção for 4 (Selecionar ponto)
        else if (opcao == 4) {
            ponto = selecionarPonto(mouseX, mouseY, listaPontos);
            if (ponto != -1) { //se o mouse clicar em um ponto existente será imprimida a posição do ponto
                printf("-----mouseX: %f, mouseY: %f\n", mouseX, mouseY);
                printf("-----PX: %f, PY: %f\n", listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
                /*MatrizTransformacao * matrizTranslacao = criarMatrizTranslacao(
                        mouseX - listaPontos->pontos[ponto].x,
                        mouseY - listaPontos->pontos[ponto].y
                );
                transladarPonto(ponto, listaPontos, matrizTranslacao);*/
            }
        }
        // Se a opção for 5 (Selecionar segmento de reta)
        else if (opcao == 5) {

        }
        // Se a opção for 6 (Selecionar polígono)
        else if (opcao == 6) {

        }

        ////////// Opção Salvar objetos
        else if (opcao == 7) {
            salvarPontos(listaPontos);
            salvarRetas(listaRetas);
            // salvarPoligonos(listaPoligonos);
        }

        ////////// Opção Carregar objetos
        else if (opcao == 8) {
            carregarPontos();
            // carregarRetas(listaRetas);
            // carregarPoligonos(listaPoligonos);
        }

        ////////// Opção Cancelar
        else if (opcao == 0) {

        }
    }

    glutPostRedisplay();
}

/*
 * FUNÇÃO CHAMADA QUANDO O BOTÃO DO MOUSE É MANTIDO PRESSIONADO
 */
void arrastarMouse(int x, int y)
{
    mouseX = x - largura;
    mouseY = altura - y;

    // Se estiver na opção selecionar ponto e um ponto já estiver selecionado, mouse fica transladando o ponto
    if (opcao == 4 && ponto != -1) {
        MatrizTransformacao * matrizTranslacao = criarMatrizTranslacao(
            mouseX - listaPontos->pontos[ponto].x,
            mouseY - listaPontos->pontos[ponto].y
        );
        transladarPonto(ponto, listaPontos, matrizTranslacao);
    }

    glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA DEFINIR O USO DO TECLADO PELO USUÁRIO
 */
void funcoesTeclado(int tecla, int x, int y)
{
    // Opções Selecionar
    if (tecla == GLUT_KEY_F1) {
        if (opcao == 4 && ponto != -1) {
            if (excluirPonto(ponto, listaPontos)) {
                if (statusMouse != 0) statusMouse = 0;
                ponto = -1;
            }
        }
    }
}

/*
 * FUNÇÃO PARA USAR O TECLADO ASCII PARA APLICAR AS FUNÇÕES DE ROTACIONAR E ESCALAR
 */
void gerenciarTeclado(unsigned char key, int x, int y)
{
    switch (key) {
        // Rotaciona o ponto 45 graus apertando r caso esteja na opção de selecionar o ponto e um ponto esteja selecionado
        case 'R':
        case 'r':
            if (opcao == 4 && ponto != -1) {
                MatrizTransformacao * matrizRotacao = criarMatrizRotacao(45);
                rotacionarPonto(ponto, listaPontos, matrizRotacao);
            }
            break;

        // Esse vai ser o botão de escala
        case 'S':
        case 's':
                break;
    }

    glutPostRedisplay();
}
