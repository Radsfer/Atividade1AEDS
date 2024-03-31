# Atividade 1 - Aquecimento
A proposta do programa é receber uma matriz quadrada de um arquivo no formato MPS(Mathematical Programming System) de tamanho mínimo 5 por 5 e que fosse atualizada a cada rodada conforme as regras.
## Objetivos:
- Descobrir como funciona a formatação MPS.
- Manipular os dados e inseri-los em um formato de matriz em C++.
- Manipular as matrizes do programa de forma eficiente a seguir as regras do jogo.
## Arquivo MPS

Com a ajuda da documentação no site da [IBM](https://www.ibm.com/docs/pt-br/icos/20.1.0?topic=standard-records-in-mps-format) e do ChatGPT consegui a seguinte suposição de como seria um arquivo do tipo MPS que gera uma matriz quadrada.

```mps
NAME       Rodada 0
ROWS       Integer
COLUMNS
    i11      int 0
    i12      int 1
    i13      int 0
    i14      int 0
    i15      int 1
    i21      int 0
    i22      int 0
    i23      int 1
    i24      int 1
    i25      int 0
    i31      int 1
    i32      int 1
    i33      int 1
    i34      int 1
    i35      int 1
    i41      int 1
    i42      int 1
    i43      int 0
    i44      int 0
    i45      int 0
    i51      int 0
    i52      int 1
    i53      int 1
    i54      int 0
    i55      int 0
RHS        RHS1
    RHS1     1
BOUNDS
    UP BOUND1  i11 1
    UP BOUND2  i12 1
    UP BOUND3  i13 1
    UP BOUND4  i14 1
    UP BOUND5  i15 1
    UP BOUND6  i21 1
    UP BOUND7  i22 1
    UP BOUND8  i23 1
    UP BOUND9  i24 1
    UP BOUND10  i25 1
    UP BOUND11  i31 1
    UP BOUND12  i32 1
    UP BOUND13  i33 1
    UP BOUND14  i34 1
    UP BOUND15  i35 1
    UP BOUND16  i41 1
    UP BOUND17  i42 1
    UP BOUND18  i43 1
    UP BOUND19  i44 1
    UP BOUND20  i45 1
    UP BOUND21  i51 1
    UP BOUND22  i52 1
    UP BOUND23  i53 1
    UP BOUND24  i54 1
    UP BOUND25  i55 1
ENDATA
```
A matriz em questão foi usada no arquivo input para testes, e como pode ser visto, o importante para o programa é que o valor desejado é o número ao final de cada linha entre COLUMS e RHS que representam respectivamente o valor dentro da célula.
## O Programa
### Abordagem para criação do programa
Primeiro foi feita uma análise das regras do jogo antes e foi seguido a abordagem de utilizar 2 matrizes como recomendado na documentação da atividade. Partindo disso, primeiro foi feito uma versão do programa com uma função que gera uma matriz seguindo as proporções pedidas, onde era uma fração de 2 para 1 em relação a quantidade de números 0 para quantidade de números 1. Em seguida um método para mostrar os dados presentes na matriz principal e um segundo método para copiar os dados da matriz principal para uma matriz secundária.
Depois disso foi planejado a forma como seria escrita do arquivo, seguindo o exemplo mostrado anteriormente. E feita a função de forma a salvar a matriz secundária pois as regras seriam aplicadas apenas na matriz principal. 
Em seguida foram feitas duas funções. Uma que consiste em fazer a contagem de vizinhos e guardar essa contagem dentro da própria célula na matriz principal e a outra seria apenas uma função de aplicação da regra que analisa o valor presente na célula respectiva na matriz secundária em relação a quantidade de vizinhos anotada na célula de mesma posição na matriz primária.
Então para o jogo foi feita uma função simples que recebe a quantidade de rodadas mantendo em loop utilizando as funções anteriormente descritas até serem realizadas todas as rodadas.
Assim que foi confirmado o funcionamento do código foi feita a função de leitura do arquivo. Que consiste em pegar os números presentes ao final de cada linha entra as palavras COLUMNS e RHS.
Até o presente momento o código funciona perfeitamente para os casos de teste.
### Bibliotecas utilizadas
```cpp 
#include <iostream>	
#include <string>
#include <fstream>
#include <cstddef>
#include <vector>
#include <cmath>
#include <sys/stat.h>
```
1. <b>iostream</b>
	 Biblioteca necessária padrão de entrada e saída para o código.
2. <b>string</b>
	Foi utilizada para manipulação de strings devido a escrita padrão do arquivo tipo MPS.
3. <b>fstream</b>
	Necessária para a devida manipulação de arquivos.
4. <b>cstddef</b>
	Foi usada em conjunto com a biblioteca string pois tem funções úteis para manipulação de ponteiros em string que me ajudaram a coletar os dados do arquivo MPS.
5. <b>vector</b>
	Escolhi fazer as matrizes em vector devido a facilidade das funções presentes da biblioteca para inserção de dados, também pelo fato de não ter que me preocupar com alocação e desalocação de espaço para matrizes durante o código.
6. <b>cmath</b>
	Utilizada unica e exclusivamente por conta da função sqrt().
1. <b>sys/stat.h</b>
	Foi usada unica e exclusivamente para garantir a permissão de criação e escrita do arquivo MPS como requisitado em documentação.
### Funcionamento e funções
O programa em si contem 3 arquivos. Sendo o main.cpp para execução do programa, Table.hpp como o header do objeto Table onde em seu Table.cpp estão todas as funções que estão sendo executadas na main e internamente chamadas dentro dos métodos do próprio objeto.

#### main.cpp
Na main temos apenas uma solicitação ao usuário para quantidade de rodadas e a criação do objeto do tipo Table chamado de Game que servira para chamada dos métodos.
Sendo que antes de compilar pode-se ser feita a alteração para decidir se vai utilizar a chamada do método que pede pelo arquivo input.mps presente na pasta datasets do projeto, ou se deseja gerar uma matriz quadrada preenchida de forma aleatória usando o setSizeTable(int num).
```cpp
    int rounds;

    std::cout<<"Digite a quantidade de rodadas: ";
    std::cin>>rounds;
    
    Table Game=Table();

    //Geração automática, para alterar o tamanhado da matriz altere
    //o valor em setSizeTable, se não o tamanho automático será de 5X5
    // Game.setSizeTable(10);
    // Game.setFirstTableTest();
    
    //Recebe a matriz via input
    Game.getFirsTableFromInput();

    Game.runGame(rounds);
```
#### Table/.hpp/.cpp
Para facilitar a análise do código vou explicar de forma direta o funcionamento de cada método chamado e o motivo da escolha.
O objeto contem 3 atributos privados, sendo o size para o tamanho da matriz NxN e as matrizes feitas com vector de Tab e Save, sendo Tab a matriz primária e Save a matriz secundária.
 ```cpp
 private:
 int size;
 std::vector<std::vector <int>>Tab;
 std::vector<std::vector <int>>Save;
```
O construtor é vazio pois como foi pedido em documentação a matriz tem que ter um tamanho minimo de 5x5, então caso for decidido utilizar o método de criação de matriz aleatória com um tamanho diferente, é necessário alterar o atributo size, por isso o método setSizeTable. Quanto ao método getTable foi um método para auxiliar durante a criação do programa verificando se a criação da matriz funcionava como esperado.
 ```cpp
 Table::Table()
{
    this->size=5;
};
void Table::setSizeTable(int size)
{
  this->size=size;  
};
std::vector<std::vector<int>> Table::getTable() const
{
    return Tab;
};

```
O método setFirstTableTest funciona de forma a primeiro preencher as células da matriz Tab com valor zero no tamanho size determinado, e em seguida pra seguir a proporção desejada de números 0 para números 1, é calculado de acordo com a quantidade total de células e em seguida a quantidade de 0 é decidida pela metade do total (lembrando que se não for um número inteiro o resultado vai descartar a parte decimal) e a quantidade de números 1 é calculada como o total menos a quantidade de 0.
Então o loop while começa até que a quantidade de números 1 desejada seja colocada dentro da matriz, para as casas serem preenchidas de forma aleatória as coordenadas são decididas pela função rand, mas para evitar de preencher uma célula que já tenha recebido o número 1 foi colocada a condição if que verifica se o valor daquela célula é zero (por conta da matriz ter sido preenchida inicialmente com números 0).
 ```cpp
void Table::setFirstTableTest()
{
    std::cout << "Criando tabela Teste ... " << std::endl;

    for (int i = 0; i < size; i++)
    {
        std::vector<int> line;
        for (int j = 0; j < size; j++)
        {
            line.push_back(0);
        }
        Tab.push_back(line);
    }

    int total = size * size;
    int zeroQty = total / 2;
    int oneQty = total - zeroQty;

    
    while (oneQty > 0)
    {
        int i = rand() % size;
        int j = rand() % size;

        if (Tab[i][j] == 0)
        {
            Tab[i][j] = 1;
            oneQty--;
        }
    }

    std::cout << "Tabela criada! " << std::endl;
};

 ```
A função que recebe de input os valores da matriz não recebe nenhuma variável porque a pasta e onde o input.mps esta localizado foi decidido previamente na documentação do exercício. Então partindo do caminho é criado a instancia de input para a leitura do arquivo na variável file.
Primeiro a condição onde verifica se o arquivo ta aberto e depois começa a avaliação. Como foi falado anteriormente no formato do arquivo tipo MPS só é interessante os dados presentes no final de cada linha entre as palavras COLUMNS e RHS, então pra começar a procurar primeiro eu uso a função getline para pegar a linha por linha do arquivo e verifico se a palavra COLUMNS está naquela string usando a função find que se não encontrar a subs string COLUMNS retorna que não está presente naquela string. Por isso a comparação de diferente de npos (no position).
Achado a palavra COLUMNS sigo para segunda verificação que é caso a palavra RHS esteja presente. Porque não me interessa os dados depois de RHS, então se achar a palavra termina o loop.
A variável pos tem o formato size_t por conta do retorno do método find_last_of, que nesse caso, retorna a posição de memória do ultimo espaço presente na linha (por conta que o dado desejado está sempre depois de um espaço ao final da linha).  Em seguida a variável lastNumber vai receber a substring que ta na posição pos+1. Convertida em inteiro na variável num e colocada em posição no vetor auxiliar.
E por fim é calculado o valor equivalente ao N de uma matriz que por ser quadrada seria equivalente a raiz do tamanho do vetor auxiliar:
$$NxN=\sqrt{N^{2}}$$
Assim que o tamanho de size é redefinido. Um vetor auxiliar lineTable é preenchido de acordo com os dados que devem ir em cada linha usando a propriedade de matriz onde quadrada onde:
$$(ROW*N)+COL=Cell$$
Sendo cell a posição sequencial da célula. Assim a linha é preenchida o vetor é inserido na matriz principal Tab e em seguida é limpo para ser preenchido novamente.
```cpp
 void Table::getFirsTableFromInput()
{
    std::string filepath = "datasets/input.mps";
    std::ifstream file(filepath);
    std::vector<int> aux;
    
    if(file.is_open())
    {
    std::string line;
    bool start=false;
    while (std::getline(file,line)) 
    {
        if(!start)
        {
            if(line.find("COLUMNS")!= std::string::npos)
            {
                start=true;
            }
            continue;
        }

        if (line.find("RHS") != std::string::npos)
        {
            break;
        }

        size_t pos = line.find_last_of(" ");
        std::string lastNumber = line.substr(pos + 1);
        int num = std::stoi(lastNumber);
        aux.push_back(num);
    }
    
    file.close();
    
    int square=aux.size();
    square=std::sqrt(square);

    size=square;

    std::vector<int>lineTable;
   
    for (int i=0; i<size;i++)
    {
        for (int j=0; j<size; j++)
        {
            int cell=aux[(i*size)+j];
            lineTable.push_back(cell);
        }
        Tab.push_back(lineTable);
        lineTable.clear();
    }




    std::cout<<"Input lido com sucesso!"<<std::endl;

    }else
    {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }

};
```
A função que salva a matriz secundária como foi decido e mencionado anteriormente recebe apenas a entrada de um numero inteiro que receberia a quantidade de rodadas para facilitar a leitura do arquivo depois da execução do programa.
O caminho e nome do arquivo já foi decidido previamente em documentação da atividade então foi criada uma instancia de output stream na variável file para manipulação de arquivo, onde é primeiro verificado se o arquivo foi aberto.
Em seguida a escrita do arquivo segue o padrão pre-estabelecido utilizando de dois loops for para a escrita das posições da célula seguindo o atributo size.
Como adendo devido a erros anteriores de funcionamento do programa foi adicionado a função chmod que primeiro recebe o filepath convertido para um ponteiro de char e em seguida combina as permissões de escrita de usuário, grupo e outros usuários. Para dar a devida permisão ao programa de escrever e criar o arquivo gerações se necessário. Também foi alterado o script make mas isso será visto futuramente.
 ```cpp
 void Table::saveTable(int rounds)
{

    std::string filepath = "datasets/geracoes.mps"; 
    std::ofstream file(filepath, std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return;
    }

    file << "NAME       Rodada "<<rounds<<"\n";
    file << "ROWS       Integer\n";
    file << "COLUMNS\n";

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            file << "    i" << i + 1 << j + 1 << "      int " << Save[i][j]<<"\n";
        }
    }
    file << "RHS        RHS1\n";
    file << "    RHS1     1\n";
    file << "BOUNDS\n";

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            file <<"    UP BOUND" << i * size + j + 1 << "  i" << i + 1 << j + 1 << " 1\n";
        }
    }
    
    file << "ENDATA\n";
    file.close();
    chmod(filepath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    std::cout << "Matriz salva com sucesso" << std::endl;
};

```
Função simples que serve apenas pra ajudar a visualização do estado da matriz durante a execução do programa. Iterando sobre cada item.
 ```cpp
void Table::showTable()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << "|" << Tab[i][j];
        }
        std::cout << "|" << std::endl;
    }
};
```
Como foi comentado na secção de abordagem. Essa função serve apenas para salvar uma cópia da matriz principal na matriz secundária, devido a decisão de fazer as alterações na matriz principal e manter e salvar os dados com o auxilio da matriz secundária.
 ```cpp
void Table::copyTable()
{
    Save.clear();

    for (int i = 0; i < size; ++i)
    {
        std::vector<int> line;

        for (int j = 0; j < size; ++j)
        {
            int aux = Tab[i][j];
            line.push_back(aux);
        }

        Save.push_back(line);
    }
};
```
Função simples que recebe o valor inteiro da célula e a quantidade de vizinhos para aplicar as regras do jogo. Retornando 0 em casos onde a célula valha 1 e sua quantidade de vizinhos seja maior que 2 e menor do 3 vizinhos. E caso a célula não valha 1 verifica se possuí uma quantidade de vizinhos igual a 3, retorna 1, se não, retorna 0.
 ```cpp
 int Table:: applyRules(int cell, int liveNeighbors)
{
    if (cell == 1)
    {
        if (liveNeighbors < 2 || liveNeighbors > 3)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (liveNeighbors == 3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};
```
Essa função faz a contagem de vizinhos e os salva dentro da própria matriz principal Tab. A ideia é utilizar os vetores movesX e movesY para realizar um movimento circular em torno da célula e salvar a quantidade de vizinhos dentro da prórpria célula. Os 2 primeiros loops for servem para iterar sobre as linhas e colunas da matriz e o terceiro loop for serve apenar para realizar o movimento circular entorno da célula, levando em conta os limites da matriz.
Em seguida o valor somado é coloca na respectiva posição da matriz Tab antes do segundo loop terminar. E assim segue sucessivamente até passar por todas as células da matriz Tab.
 ```cpp
 
void Table::countNeighbors()
{
    int movesX[]={1,0,-1,-1,0,0,1,1};
    int movesY[]={0,1,0,0,-1,-1,0,0};
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) 
        {
            int neighbors=0;
            for (int k=0; k<8; k++)
            {
                int newX = i + movesX[k];
                int newY = j + movesY[k];
                if (newX >= 0 && newX < size && newY >= 0 && newY < size)
                {
                    neighbors += Save[newX][newY];
                }
            }
            this->Tab[i][j]=neighbors;
        }
    }
    
};
```
A função  que faz o funcionamento do jogo vai receber a quantidade de rodadas externamente. A decisão do uso de um loop while ao invés de um loop for ou um loop do-while foi meramente arbitrária, sendo que tirando caso do-while que forçaria pelo menos uma iteração e foi desconsiderado no momento de escrita do código pois em caso de ser necessário fazer apenas 1 rodada poderia causar erros. O loop for supriria também de forma adequada, mas como a ideia era de uma condição para gerar uma rodada do jogo, decidi que o loop while seria melhor semanticamente. 
Primeiro o loop verifica se a quantidade de rounds é maior que 0. Depois a variável showRounds serve como marcação, sendo 0 para o estado inicial da matriz. Em seguida a tabela principal é mostrada, depois feita a cópia para a tabela secundária e feita a contagem de vizinhos na matriz principal.
Em sequência é iterado sobre os valores das tabelas primária e secundária, e feita a aplicação da regra retornando o valor em aux. Lembrando que o estado original da matriz principal está na matriz Save por isso é ela que fica no valor de célula e a matriz Tab nesse momento do código tem como valor em suas células a quantidade de vinhos que a respectiva célula tem. Em seguida a célula na posição avaliada recebe o valor retornado pela função de regra do jogo. 
Após a atualização da tabela principal, é salvo a tabela secundária antes do próximo loop. Assim seguindo até a ultima rodada onde é copiado e salvo a ultima iteração da tabela.
 ```cpp
 void Table::runGame(int rounds)
{
   int showRounds=0;
    while(rounds>0)
     {
        std::cout<<"Rodada: "<<showRounds<<std::endl; 
        showTable();
        copyTable();
        countNeighbors();
        for (int i=0; i<size;i++)
        {
            for (int j=0;j<size;j++)
            {
                int save= Save[i][j];
                int tab= Tab[i][j];
                int aux=applyRules(save,tab);               
                Tab[i][j]=aux;
            }
        }
        saveTable(showRounds);
        showRounds++;
        rounds--;
      }

    std::cout<<"Rodada: "<< showRounds <<std::endl; 
    showTable();
    copyTable();
    saveTable(showRounds);

};

```
Por fim por é feito a limpeza das matrizes no destrutor do objeto para garantir que não exista nenhum vazamento de memória.
 ```cpp
 Table::~Table()
{
   Tab.clear();
   Save.clear();
};
```

### Alterações no arquivo make
No arquivo de script do make foi adicionado apenas 2 alterações. 
Sendo na parte de clean:
```bashsrc
	rm -f $(TARGET_DIR)/geracoes.mps
```
Para a exclusão do arquivo geracoes.mps de compilações passadas. Então caso vá alterar o tipo de execução do programa entre gerar aleatoriamente ou gerar com input, separar em um arquivo a parte para fazer a comparação!
E na execução do app com o run:
```bashsrc
	mkdir -p $(TARGET_DIR)
	chmod +w $(TARGET_DIR)
```
Para corrigir o erro onde não conseguia criar/escrever em um arquivo de geracoes.mps como foi mencionado anteriormente na parte de funcionamento do código.
## Execução do programa
Primeiro, se quiser alterar a forma de funcionamento do programa, sendo recebendo por input ou gerando automaticamente a matriz, faça as devidas alterações no arquivo main.cpp.
Para compilação e execução digite no terminal:
```bashsrc
	make clean
	make
	make run
```
## Testes realizados
Aproveitando de um feliz acidente com a geração automática de matriz, para o caso mínimo de uma matriz 5x5 o teste realizado contou com o fato da função rand() ser pseudo aleatória. Foi gerado uma matriz com 0 rodadas e renomeei para o arquivo input.mps para teste a versão que recebe do arquivo.
[Imagem 1](/imgs/matrizNaoTaoAleatoria.png)
Sendo assim foi avaliado as condições de funcionamento minima requisitadas pela documentação da atividade. E para comparação de funcionamento, vi os resultados gerados tanto pela matriz gerada "aleatóriamente" com a de matriz passada via input, e em 10 rodadas as duas apresentaram o mesmo comportamento.

[Imagem 2](imgs/setimaRodadaMorte.png)
Onde a partir de 8 rodada todas as células morrem. Que ao ser avaliado de acordo com as regras do programa seguiu perfeitamente o comportamento esperado.

#### Possíveis erros.
Até o momento, como os testes foram realizados para o valor minimo requisitado de matriz pode ser que o algoritmo utilizado para contagem e geração de matrizes seja passível de algum problema de gestão de memória ao aumentar a escala de rodadas e de matrizes. 
Outro erro seria que a suposição de formatação do arquivo tipo MPS esteja errada, então nesse caso geraria algum problema na leitura da matriz do jogo.

## Agradecimento e considerações finais
A atividade proposta foi um excelente aquecimento para as atividades a seguir do semestre, servindo para rever conceitos de acesso de memória e conhecer alguns conceitos novos sobre o script bash presente em make. E agradeço ao professor [Dr Michel](https://github.com/mpiress/) pelo projeto proposto.
## Contato
Qualquer dúvida sobre o funcionamento do código pode pode entrar em contato via o email:
rafael.ferreira11.98@gmail.com

## Sobre

Rafael Adolfo Silva Ferreira
Formado em Engenharia Química - UNIFORMG.
Cursando atualmente Engenharia da Computação - CEFETMG - Campus Divinópolis.
