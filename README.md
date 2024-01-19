# Computação Gráfica

**Equipe:** Alexandre Marques Cabral e Clice Bezerra Brito Romão

## Construção de um "Paint"

### Instruções para execução do projeto

Com o OpenGL instalado, é possível utilizar tanto o Code::Blocks como o WSL (Windows Subsystem for Linux) instalado no Windows para a compilação do projeto.

#### Code::Blocks



#### WSL (Windows Subsystem for Linux)

Para a utilização do WSL, podesse compilar o projeto utilizando o comando:
```bash
g++ main.c -o main -lglut -lGLU -lGL
```

Para rodar o projeto, utilizasse o comando:
```bash
./main
```

2. Também é possível utilizar o Code::Blocks para a compilar e testar o projeto, porém configurações são necessárias para compilação e a utilização do OpenGL.

### Instruções para uso do programa

#### 1. Utilização do menu 

É necessário clicar no botão direito do mouse para ativar o menu e escolher uma das opções disponíveis.

#### 2. Criação de pontos, retas e polígonos

É necessário escolher a opção Criar > Ponto ou Segmento de Reta ou Polígono para a criação dos objetos. No caso dos pontos, depois de escolhida a opção, basta clicar com o botão esquerdo do mouse no local onde deseja adicionar um ponto e ele aparecerá no local desejado. Já para o segmento de reta, dois clique no botão esquerdo são necessários, onde a reta deverá iniciar e terminar, respectivamente. 

#### 3. Seleção de pontos, retas e polígonos

É necessário escolher a opção Selecionar > Ponto, ou Segmento de Reta, ou Polígono para a seleção dos objetos. Após esse passo, basta clicar em cima do objeto desejado e já é possível realizar as manipulações dos mesmos individualmente.

#### 4. Salvar objetos da tela



#### 5. Carregar objetos a partir de arquivos