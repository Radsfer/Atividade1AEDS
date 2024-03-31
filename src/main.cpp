#include <iostream>
#include "Table.hpp"

int main (){
    int rounds;

    std::cout<<"Digite a quantidade de rodadas: ";
    std::cin>>rounds;
    
    Table Game=Table();

    //Geração automática, para alterar o tamanhado da matriz altere
    //o valor em setSizeTable, se não o tamanho automático será de 5X5
    // Game.setSizeTable(10);
     Game.setFirstTableTest();
    
    //Recebe a matriz via input
   // Game.getFirsTableFromInput();

    Game.runGame(rounds);
        





    return 0;
}
