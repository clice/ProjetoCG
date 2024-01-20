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
int chave = -1;        // Guarda a chave da lista para manipulação dos objetos (desenhando: > -1; finalizado: -1)
int statusObjeto = -1; // Indica se o objeto ainda está sendo desenhado (desenhando: 1; finalizado: -1)
int rot = 0;
int theta;

/*
 * VARIÁVEIS DAS DIMENSÕES DA TELA
 */
float largura = 400;   // Largura fixa da tela (metade dos pixels que formam a tela: eixo x)
float altura = 300;    // Altura fixa da tela (metade dos pixels que formam a tela: eixo y)

/*
 * VARIÁVEIS DO MOUSE
 */
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
void funcoesMovimento(int x, int y);
void funcoesTeclado(unsigned char key, int x, int y);

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
    glutMotionFunc(funcoesMovimento);    // Função que é chamada quando um botão do mouse é mantido pressionado
    glutKeyboardFunc(funcoesTeclado);    // Função que é chamada quando um botão do teclado é pressionado
    glutDisplayFunc(telaInicial);        //
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
    desenharRetas(listaRetas);

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
    glutAddMenuEntry("Salvar objetos", 7);
    glutAddMenuEntry("Carregar objetos", 8);
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
        chave = -1;
        statusMouse = 0;
        statusObjeto = -1;
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
        printf("mouseX: %.1f, mouseY: %.1f\n", mouseX, mouseY);

        ////////// Opções: Criar
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

        ////////// Opção: Selecionar
        // Se a opção for 4 (Selecionar ponto)
        else if (opcao == 4) {
            // Retorna a chave da lista onde o ponto que foi selecionado com o mouse está
            chave = selecionarPonto(mouseX, mouseY, listaPontos);
            printf("Chave selecionada: %d\n", chave);
        }
        // Se a opção for 5 (Selecionar segmento de reta)
        else if (opcao == 5) {
            // Retorna a chave da lista onde a reta que foi selecionada com o mouse está
            chave = selecionarReta(mouseX, mouseY, listaRetas);
            printf("Chave selecionada: %d\n", chave);
        }
        // Se a opção for 6 (Selecionar polígono)
        else if (opcao == 6) {
            // Retorna a chave da lista onde o polígono que foi selecionado com o mouse está
        }

        ////////// Opção: Salvar objetos
        else if (opcao == 7) {
            salvarListaPontos(listaPontos);
            salvarListaRetas(listaRetas);
            // salvarListaPoligonos(listaPoligonos);
        }

        ////////// Opção: Carregar objetos
        else if (opcao == 8) {
            carregarListaPontos();
            // carregarListaRetas(listaRetas);
            // carregarListaPoligonos(listaPoligonos);
        }
    }

    glutPostRedisplay();
}

/*
 * FUNÇÃO CHAMADA QUANDO O BOTÃO DO MOUSE É MANTIDO PRESSIONADO
 */
void funcoesMovimento(int x, int y)
{
    // Localização atualizada do mouse
    mouseX = x - largura;  // Localização do eixo x (horizontal - largura)
    mouseY = altura - y;   // Localização do eixo y (vertical - altura)

    ////////// Transladar ponto
    // Se estiver na opção "Selecionar" ponto e um ponto já estiver selecionado, o mouse fica transladando o ponto
    if (opcao == 4 && chave != -1) {
        // Realizar o cálculo da transformação para movimentar o ponto
        MatrizTransformacao * matrizTranslacaoPonto = criarMatrizTranslacao(
            mouseX - listaPontos->pontos[chave].x,
            mouseY - listaPontos->pontos[chave].y
        );

        // Realizar a translação do ponto selecionado
        transladarPonto(chave, listaPontos, matrizTranslacaoPonto);
    }

    ////////// Transladar reta
    // Se estivar na opção "Selecionar" reta e uma reta já estiver selecionada, o mouse fica transladando a reta
    else if (opcao == 5 && chave != -1) {
        // Realizar o cálculo da transformação para movimentar a reta
        MatrizTransformacao * matrizTranslacaoReta = criarMatrizTranslacao(
            mouseX - listaRetas->retas[chave].central.x,
            mouseY - listaRetas->retas[chave].central.y
        );

        // Realizar a translação da reta selecionada
        transladarReta(chave, listaRetas, matrizTranslacaoReta);
    }

    ////////// Transladar polígono
    // Se estiver na opção "Selecionar" polígono e um polígono já estiver selecionado, o mouse fica transladando o polígono
    else if (opcao == 6 && chave != -1) {

    }

    glutPostRedisplay();
}

/*
 * FUNÇÃO PARA USAR O TECLADO ASCII PARA APLICAR AS FUNÇÕES DE ROTACIONAR E ESCALAR
 */
void funcoesTeclado(unsigned char key, int x, int y)
{
    switch (key) {
        // Excluir objetos selecionados da tela (D - Delete)
        case 'D':
        case 'd':
            ////////// Excluir ponto
            // Se um ponto está na opção "Selecionar" e a chave contém um valor diferente de -1
            if (opcao == 4 && chave != -1) {
                if (excluirPonto(chave, listaPontos)) {
                    imprimirListaPontos(listaPontos);
                    chave = -1;
                }
            }

            ////////// Excluir reta
            // Se uma reta está na opção "Selecionar" e a chave contém um valor diferente de -1
            else if (opcao == 5 && chave != -1) {
                if (excluirReta(chave, listaRetas)) {
                    imprimirListaRetas(listaRetas);
                    chave = -1;
                }
            }

            ////////// Excluir polígono
            // Se um polígono está na opção "Selecionar" e a chave contém um valor diferente de -1
            else if (opcao == 6 && chave != -1) {

            }

            break;

        // Rotacionar objetos selecionados da tela (R - Rotate)
        // Rotaciona o ponto 45 graus apertando r caso esteja na opção de selecionar o ponto e um ponto esteja selecionado
        case 'R':
        case 'r':
            ////////// Rotacionar ponto
            // Se um ponto está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 4 && chave != -1) {
                MatrizTransformacao * matrizRotacao = criarMatrizRotacao(teta);
                rotacionarPonto(chave, listaPontos, matrizRotacao);
            }

            ////////// Rotacionar reta
            // Se uma reta está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 5 && chave != -1) {

            }

            ////////// Rotacionar polígono
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 6 && chave != -1) {

            }

            break;

        // Escalar objetos selecionados da tela (S - scale)
        case 'S':
        case 's':
            ////////// Escalar reta
            // Se uma reta está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 5 && chave != -1) {

            }

            ////////// Escalar polígono
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 6 && chave != -1) {

            }

            break;
    }

    glutPostRedisplay();
}
