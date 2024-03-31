#include "Table.hpp"


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


Table::~Table()
{
   Tab.clear();
   Save.clear();
};
