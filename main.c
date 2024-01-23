#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "poligono.h"

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
ListaPoligonos * listaPoligonos = NULL;

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
    listaPoligonos = criarListaPoligonos();

    glClearColor(1.0, 1.0, 1.0, 0.0); // Cor do background
    glMatrixMode(GL_PROJECTION);
    glOrtho(-largura, largura, -altura, altura, -1.0f, 1.0f);

    glutMouseFunc(funcoesMouse);         // Chamadas quando um botão do mouse é acionado
    glutMotionFunc(funcoesMovimento);    // Chamadas quando o mouse é movimentado
    glutKeyboardFunc(funcoesTeclado);    // Chamadas quando o teclado ASCII é acionado
    glutDisplayFunc(telaInicial);        // Para mostrar elementos na tela rederizando os objetos
    glutMainLoop();

    // Liberando espaço da memória ocupado pelas listas de objetos
    liberarListaPontos(listaPontos);
    liberarListaRetas(listaRetas);
    liberarListaPoligonos(listaPoligonos);

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
    desenharPoligonos(listaPoligonos);

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

    // Transladar objetos selecionados da tela
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
            statusObjeto = adicionarPoligono(mouseX, mouseY, statusObjeto, listaPoligonos);
            imprimirListaPoligonos(listaPoligonos);
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
            chave = selecionarPoligono(mouseX, mouseY, listaPoligonos);
            printf("Chave selecionada: %d\n", chave);
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
    float translacaoX, translacaoY;

    // Localização atualizada do mouse
    mouseX = x - largura;  // Localização do eixo x (horizontal - largura)
    mouseY = altura - y;   // Localização do eixo y (vertical - altura)

    ////////// Transladar ponto
    // Se estiver na opção "Selecionar" ponto e um ponto já estiver selecionado, o mouse fica transladando o ponto
    if (opcao == 4 && chave != -1) {
        // Realizar o cálculo para saber o valor da translação realizada
        translacaoX = mouseX - listaPontos->pontos[chave].x;
        translacaoY = mouseY - listaPontos->pontos[chave].y;

        // Criar a matriz da translação realizada
        Matriz3Por3 * matrizTranslacaoPonto = criarMatrizTranslacao(translacaoX, translacaoY);

        // Realizar a translação do ponto selecionado
        transladarPonto(chave, listaPontos, matrizTranslacaoPonto);
    }

    ////////// Transladar reta
    // Se estivar na opção "Selecionar" reta e uma reta já estiver selecionada, o mouse fica transladando a reta
    else if (opcao == 5 && chave != -1) {
        // Realizar o cálculo para saber o valor da translação realizada
        translacaoX = mouseX - listaRetas->retas[chave].central.x;
        translacaoY = mouseY - listaRetas->retas[chave].central.y;

        // Criar a matriz da translação realizada
        Matriz3Por3 * matrizTranslacaoReta = criarMatrizTranslacao(translacaoX, translacaoY);

        // Realizar a translação da reta selecionada
        transladarReta(chave, listaRetas, matrizTranslacaoReta);
    }

    ////////// Transladar polígono
    // Se estiver na opção "Selecionar" polígono e um polígono já estiver selecionado, o mouse fica transladando o polígono
    else if (opcao == 6 && chave != -1) {
        // Realizar o cálculo para saber o valor da translação realizada
        translacaoX = mouseX - listaPoligonos->poligonos[chave].centroide.x;
        translacaoY = mouseY - listaPoligonos->poligonos[chave].centroide.y;

        // Criar a matriz da translação realizada
        Matriz3Por3 * matrizTranslacaoPoligono = criarMatrizTranslacao(translacaoX, translacaoY);

        // Realizar a translação do polígono selecionado
        transladarPoligono(chave, listaPoligonos, matrizTranslacaoPoligono);
    }

    glutPostRedisplay();
}

/*
 * FUNÇÃO PARA USAR O TECLADO ASCII PARA APLICAR AS FUNÇÕES DE ROTACIONAR E ESCALAR
 */
void funcoesTeclado(unsigned char key, int x, int y)
{
    float corte = 0.5;
    float angulo = 45.0;
    float escala = 1.05;

    // Localização atualizada do mouse
    mouseX = x - largura;  // Localização do eixo x (horizontal - largura)
    mouseY = altura - y;   // Localização do eixo y (vertical - altura)

    switch (key) {
        // Rotacionar objetos selecionados da tela no sentido anti-horário (A - Anti-clockwise)
        // Rotaciona o ponto 45 graus apertando "R" caso esteja na opção de selecionar o ponto e um ponto esteja selecionado
        case 'A':
        case 'a':
            ////////// Rotacionar ponto no sentido anti-horário
            // Se um ponto está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 4 && chave != -1) {
                // Criar a matriz da rotação realizada passando o ângulo
                Matriz3Por3 * matrizRotacaoPonto = criarMatrizRotacao(angulo);

                // Realizar a rotação do ponto selecionado
                rotacionarPonto(chave, listaPontos, matrizRotacaoPonto);
            }

            ////////// Rotacionar reta no sentido anti-horário
            // Se uma reta está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 5 && chave != -1) {
                // Criar a matriz da rotação realizada passando o ângulo
                Matriz3Por3 * matrizRotacaoReta = criarMatrizRotacao(angulo);

                // Realizar a rotação da reta selecionada
                rotacionarReta(chave, listaRetas, matrizRotacaoReta);
            }

            ////////// Rotacionar polígono no sentido anti-horário
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 6 && chave != -1) {
                // Criar a matriz da rotação realizada passando o ângulo
                Matriz3Por3 * matrizRotacaoPoligono = criarMatrizRotacao(angulo);

                // Realizar a rotação do polígono selecionado
                rotacionarPoligono(chave, listaPoligonos, matrizRotacaoPoligono);
            }

            break;

        // Aumentar objetos selecionados da tela (B - Big)
        case 'B':
        case 'b':            
            ////////// Aumentar reta
            // Se uma reta está na opção "Selecionar" e a chave contém um valor diferente de -1
            if (opcao == 5 && chave != -1) {
                // Criar a matriz da escalar realizada para aumentar a reta
                Matriz3Por3 * matrizEscalarAumentaReta = criarMatrizEscalar(escala);

                // Realizar o aumento da escala da reta selecionada
                escalarReta(chave, listaRetas, matrizEscalarAumentaReta);
            }

            ////////// Aumentar polígono
            // Se um polígono está na opção "Selecionar" e a chave contém um valor diferente de -1
            else if (opcao == 6 && chave != -1) {
                // Criar a matriz da escalar realizada para aumentar o polígono
                Matriz3Por3 * matrizEscalarAumentaPoligono = criarMatrizEscalar(escala);

                // Realizar aumento da escala do polígono selecionado
                escalarPoligono(chave, listaPoligonos, matrizEscalarAumentaPoligono);
            }

            break;

        // Rotacionar objetos selecionados da tela no sentido horário (C - Clockwise)
        // Rotaciona o ponto 45 graus apertando "C" caso esteja na opção de selecionar o ponto e um ponto esteja selecionado
        case 'C':
        case 'c':
            ////////// Rotacionar ponto no sentido horário
            // Se um ponto está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 4 && chave != -1) {
                // Criar a matriz da rotação inversa realizada passando o ângulo
                Matriz3Por3 * matrizRotacaoInversaPonto = criarMatrizRotacaoInversa(angulo);

                // Realizar a rotação inversa do ponto selecionado
                rotacionarPonto(chave, listaPontos, matrizRotacaoInversaPonto);
            }

            ////////// Rotacionar reta no sentido horário
            // Se uma reta está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 5 && chave != -1) {
                // Criar a matriz da rotação inversa realizada passando o ângulo
                Matriz3Por3 * matrizRotacaoInversaReta = criarMatrizRotacaoInversa(angulo);

                // Realizar a rotação inversa da reta selecionada
                rotacionarReta(chave, listaRetas, matrizRotacaoInversaReta);
            }

            ////////// Rotacionar polígono no sentido horário
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 6 && chave != -1) {
                // Criar a matriz da rotação inversa realizada passando o ângulo
                Matriz3Por3 * matrizRotacaoInversaPoligono = criarMatrizRotacaoInversa(angulo);

                // Realizar a rotação inversa do polígono selecionado
                rotacionarPoligono(chave, listaPoligonos, matrizRotacaoInversaPoligono);
            }

            break;

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
                if (excluirPoligono(chave, listaPoligonos)) {
                    imprimirListaPoligonos(listaPoligonos);
                    chave = -1;
                }
            }

            break;

        // Finalizar o polígono (F - Finish)
        case 'F':
        case 'f':
            if (opcao == 3 && statusObjeto == 1) {
                // Status do objeto para finalização
                statusObjeto = 2;

                // Adicionar o último ponto do polígono para finalizá-lo
                statusObjeto = adicionarPoligono(mouseX, mouseY, statusObjeto, listaPoligonos);

                // finalizarPoligono(statusObjeto, listaPoligonos);
                imprimirListaPoligonos(listaPoligonos);

                // Mudar status do objeto para ele ser finalizado
                statusObjeto = -1;
            }

            break;        

        // Cisalhar objetos com relação ao eixo X
        case 'M':
        case 'm':
            ////////// Cisalhar polígono com relação ao eixo X
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 6 && chave != -1) {
                // Criar a matriz do cisalhamento
                Matriz3Por3 * matrizCisalhamentoEixoXPoligono = criarMatrizCisalhamentoEixoX(corte);

                // Realizar o cisalhamento com relação ao eixo X
                cisalharPoligono(chave, listaPoligonos, matrizCisalhamentoEixoXPoligono);
            }
            
            break;

        // Cisalhar objetos com relação ao eixo Y
        case 'N':
        case 'n':
            ////////// Cisalhar polígono com relação ao eixo Y
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 6 && chave != -1) {
                // Criar a matriz do cisalhamento
                Matriz3Por3 * matrizCisalhamentoEixoYPoligono = criarMatrizCisalhamentoEixoY(corte);

                // Realizar o cisalhamento com relação ao eixo Y
                cisalharPoligono(chave, listaPoligonos, matrizCisalhamentoEixoYPoligono);
            }
            
            break;

        // Refletir objetos com relação a origem
        case 'O':
        case 'o':
            ////////// Refletir ponto com relação a origem
            // Se um ponto está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 4 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoOrigemPonto = criarMatrizReflexaoOrigem();

                // Realizar a reflexão com a origem
                refletirPonto(chave, listaPontos, matrizReflexaoOrigemPonto);
            }

            ////////// Refletir reta com relação a origem
            // Se uma reta está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 5 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoOrigemReta = criarMatrizReflexaoOrigem();

                // Realizar a reflexão com a origem
                refletirReta(chave, listaRetas, matrizReflexaoOrigemReta);
            }

            ////////// Refletir polígono com relação a origem
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 6 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoOrigemPoligono = criarMatrizReflexaoOrigem();

                // Realizar a reflexão com a origem
                refletirPoligono(chave, listaPoligonos, matrizReflexaoOrigemPoligono);
            }
            break;
            
        // Diminuir objetos selecionados da tela (S - small)
        case 'S':
        case 's':
            ////////// Diminuir reta
            // Se uma reta está na opção "Selecionar" e a chave contém um valor diferente de -1
            if (opcao == 5 && chave != -1) {
                // Criar a matriz da escalar realizada para diminuir a reta
                Matriz3Por3 * matrizEscalarDiminuirReta = criarMatrizEscalarInversa(escala);

                // Realizar a diminuição da escala da reta selecionada
                escalarReta(chave, listaRetas, matrizEscalarDiminuirReta);
            }

            ////////// Diminuir polígono
            // Se um polígono está na opção "Selecionar" e a chave contém um valor diferente de -1
            else if (opcao == 6 && chave != -1) {
                // Criar a matriz da escalar realizada para diminuir o polígono
                Matriz3Por3 * matrizEscalarDiminuirPoligono = criarMatrizEscalarInversa(escala);

                // Realizar a diminuição da escala do polígono selecionado
                escalarPoligono(chave, listaPoligonos, matrizEscalarDiminuirPoligono);
            }

            break;

        // Transladar inversamente os objetos selecionados da tela em relação ao mouse(T - Translate)
        case 'T':
        case 't':
            float translacaoX, translacaoY;

            ////////// Transladar inversamente o ponto
            // Se estiver na opção "Selecionar" ponto e um ponto já estiver selecionado
            if (opcao == 4 && chave != -1) {
                // Realizar o cálculo para saber o valor da translação inversa realizada
                translacaoX = mouseX - listaPontos->pontos[chave].x;
                translacaoY = mouseY - listaPontos->pontos[chave].y;

                // Criar a matriz da translação inversa realizada
                Matriz3Por3 * matrizTranslacaoInversaPonto = criarMatrizTranslacaoInversa(translacaoX, translacaoY);

                // Realizar a translação inversa do ponto selecionado
                transladarPonto(chave, listaPontos, matrizTranslacaoInversaPonto);
            }

            ////////// Transladar inversamente a reta
            // Se estivar na opção "Selecionar" reta e uma reta já estiver selecionada
            else if (opcao == 5 && chave != -1) {
                // Realizar o cálculo para saber o valor da translação inversa realizada
                translacaoX = mouseX - listaRetas->retas[chave].central.x;
                translacaoY = mouseY - listaRetas->retas[chave].central.y;

                // Criar a matriz da translação inversa realizada
                Matriz3Por3 * matrizTranslacaoInversaReta = criarMatrizTranslacaoInversa(translacaoX, translacaoY);

                // Realizar a translação inversa da reta selecionada
                transladarReta(chave, listaRetas, matrizTranslacaoInversaReta);
            }

            ////////// Transladar inversamente o polígono
            // Se estiver na opção "Selecionar" polígono e um polígono já estiver selecionado
            else if (opcao == 6 && chave != -1) {
                // Realizar o cálculo para saber o valor da translação inversa realizada
                translacaoX = mouseX - listaPoligonos->poligonos[chave].centroide.x;
                translacaoY = mouseY - listaPoligonos->poligonos[chave].centroide.y;

                // Criar a matriz da translação inversa realizada
                Matriz3Por3 * matrizTranslacaoInversaPoligono = criarMatrizTranslacaoInversa(translacaoX, translacaoY);

                // Realizar a translação inversa do polígono selecionado
                transladarPoligono(chave, listaPoligonos, matrizTranslacaoInversaPoligono);
            }

            break;

        // Refletir objetos com relação ao eixo X
        case 'X':
        case 'x':
            ////////// Refletir ponto com relação ao eixo X
            // Se um ponto está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 4 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoEixoXPonto = criarMatrizReflexaoEixoX();

                // Realizar a reflexão com relação ao eixo X
                refletirPonto(chave, listaPontos, matrizReflexaoEixoXPonto);
            }

            ////////// Refletir reta com relação a origem
            // Se uma reta está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 5 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoEixoXReta = criarMatrizReflexaoEixoX();

                // Realizar a reflexão com relação ao eixo X
                refletirReta(chave, listaRetas, matrizReflexaoEixoXReta);
            }

            ////////// Refletir polígono com relação a origem
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 6 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoEixoXPoligono = criarMatrizReflexaoEixoX();

                // Realizar a reflexão com relação ao eixo X
                refletirPoligono(chave, listaPoligonos, matrizReflexaoEixoXPoligono);
            }
            
            break;

        // Refletir objetos com relação ao eixo Y
        case 'Y':
        case 'y':
            ////////// Refletir ponto com relação ao eixo Y
            // Se um ponto está na opção "Selecionar" e a chave conter um valor diferente de -1
            if (opcao == 4 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoEixoYPonto = criarMatrizReflexaoEixoY();

                // Realizar a reflexão com relação ao eixo Y do ponto selecionado
                refletirPonto(chave, listaPontos, matrizReflexaoEixoYPonto);
            }

            ////////// Refletir reta com relação a origem
            // Se uma reta está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 5 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoEixoYReta = criarMatrizReflexaoEixoY();

                // Realizar a reflexão com relação ao eixo X
                refletirReta(chave, listaRetas, matrizReflexaoEixoYReta);
            }

            ////////// Refletir polígono com relação a origem
            // Se um polígono está na opção "Selecionar" e a chave conter um valor diferente de -1
            else if (opcao == 6 && chave != -1) {
                // Criar a matriz da reflexão
                Matriz3Por3 * matrizReflexaoEixoYPoligono = criarMatrizReflexaoEixoY();

                // Realizar a reflexão com relação ao eixo X
                refletirPoligono(chave, listaPoligonos, matrizReflexaoEixoYPoligono);
            }
            
            break;
    }

    glutPostRedisplay();
}
