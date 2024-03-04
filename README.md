# Computação Gráfica

**Equipe:** 
 - Alexandre Marques Cabral
 - Clice Bezerra Brito Romão

## Construção de um "Paint"

### Instruções para execução do projeto

Com o OpenGL instalado, é possível utilizar tanto o Code::Blocks como o WSL (Windows Subsystem for Linux) instalado no Windows para a compilação do projeto.

#### 1. Code::Blocks

É necessário primeiramente fazer algumas alterções no compilador do programa para que seja possível compilar o OpenGL. Fazendo as alterações corretamente, a execução do programa ocorre como outros projetos usando o Codë::Blocks são executados e testados.

#### 2. WSL (Windows Subsystem for Linux)

Para a utilização do WSL, podesse compilar o projeto utilizando o comando:
```bash
g++ main.c matriz.c ponto.c reta.c poligono.c -o main -lglut -lGLU -lGL
```

Para rodar o projeto, utilizasse o comando:
```bash
./main
```

OBS: Lembrando que esses comandos devem ser executados dentro da pasta do projeto.

Também é possível utilizar o Code::Blocks para a compilar e testar o projeto, porém configurações são necessárias para compilação e a utilização do OpenGL.

### Instruções para uso do programa

#### 1. Utilização do menu 

É necessário clicar no botão direito do mouse para ativar o menu e escolher uma das opções disponíveis.

#### 2. Criação de pontos, segmentos de reta e polígonos

É necessário escolher a opção 'Criar' > 'Ponto' ou 'Segmento de Reta' ou 'Polígono' para a criação dos objetos. No caso dos pontos, depois de escolhida a opção, basta clicar com o botão esquerdo do mouse no local onde deseja adicionar um ponto e ele aparecerá no local desejado. Já para o segmento de reta, dois cliques no botão esquerdo são necessários, onde a reta deverá iniciar e terminar, respectivamente. Para o polígono, é necessário um clique a mais e depois clicar na tecla 'F' do teclado.

#### 3. Seleção de pontos, segmentos de reta e polígonos

É necessário escolher a opção 'Selecionar' > 'Ponto', ou 'Segmento de Reta', ou 'Polígono' para a seleção dos objetos. Após esse passo, basta clicar em cima do objeto desejado e já é possível realizar as manipulações dos mesmos individualmente, dependendo do tipo de objeto escolhido.

#### 4. Transladar pontos, segmentos de reta e polígonos

É necessário escolher a opção 'Selecionar' > 'Ponto', ou 'Segmento de Reta', ou 'Polígono' para a seleção dos objetos. Após esse passo, basta utilizar o mouse, clicando em cima do objeto correspondente ao tipo de objeto escolhido, ou seja, escolhendo 'Ponto' é possível somente transladar pontos, 'Segmento de Reta' somente se translada os segmentos de reta e para os polígonos escolhe a opção 'Polígono'.

#### 5. Rotacionar pontos, segmentos de reta e polígonos

É necessário escolher a opção 'Selecionar' > 'Ponto', ou 'Segmento de Reta', ou 'Polígono' para a seleção dos objetos. Após esse passo, basta clicar em cima do objeto desejado. Depois há duas opções de rotação que podem ser realizadas. Usando 'A' para rotacionar os objetos em sentido anti-horário ou 'C' para rotacionar os objetos em sentido horário.

#### 6. Escalar segmentos de reta e polígonos

É necessário escolher a opção 'Selecionar' > 'Segmento de Reta', ou 'Polígono' para a seleção dos objetos. Após esse passo, basta clicar em cima do objeto desejado. Depois há duas opções de escalonamento que pondem ser realizadas. Usando 'B' para aumentar os objetos, tornando-os maiores que o original ou 'S' para diminuir os objetos, tornando-os menores que o original. OBS: Não é possível escalar pontos, isso por conta da natureza do ponto, ele tem um tamanho uníco.

#### 7. Refletir pontos, segmentos de reta e polígonos

É necessário escolher a opção 'Selecionar' > 'Ponto', ou 'Segmento de Reta', ou 'Polígono' para a seleção dos objetos. Após esse passo, basta clicar em cima do objeto desejado. Depois há três opções de reflexão que podem ser realizadas. Usando 'O' para refletir os objetos em referência a origem, no caso (0, 0), ou usando 'X' para refletir os objetos em referência ao eixo X, ou ainda usando 'Y' para refletir os objetos em referência ao eixo Y.

#### 8. Cisalhar polígonos

É necessário escolher a opção 'Selecionar' > 'Polígono' para a seleção dos objetos. Após esse passo, basta clicar em cima do objeto desejado. Depois há duas opções de cisalhamento que podem ser realizadas. Usando 'M' para cisalhar os objetos em referência ao eixo X ou usando 'N' para cisalhar os objetos em referência ao eixo Y. OBS: Não é possível cisalhar pontos ou segmentos de reta, isso por conta da natureza desses objetos, ele tem uma estrutura única.

#### 9. Salvar objetos da tela

É necessário escolher a opção 'Salvar objetos'. Após esse passo, todos os objetos, tanto pontos, segmentos de reta e polígonos, caso tenham esses tipos de objeto desenhados na tela, as coordenadas dos mesmos serão salvas em um arquivo .txt, um para cada tipo de objeto (ponto, segmento de reta e poligono), onde terá a quantidade de cada objeto para poder realizar as iterações necessárias par buscar os dados. No caso do arquivo para os polígonos, além de salvar a quantidade de polígonos criados, também é salvo a quantidade de lados que cada polígono possui, também para o mesmo propósito da quantidade de objetos, realizar as iterações.

#### 10. Carregar objetos a partir de arquivos

É necessário escolher a opção 'Carregar objetos'. Após esse passo, todos os objetos, tanto pontos, segmentos de reta e polígonos, caso tenham sido salvos em arquivos com os nomes referentes respectivamente, 'ponto.txt', 'reta.txt' e 'poligono.txt', os dados serão resgatados, através de iterações com base nos dados salvos, após realizar essas iterações necessárias, os objetos serão carregados na tela.
