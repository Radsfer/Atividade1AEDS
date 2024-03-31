#ifndef __TABLE_H__
#define __TABLE_H__

#include <iostream>	
#include <string>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <cmath>
#include <vector>
#include <sys/stat.h>

class Table 
{
private:
 int size;
 std::vector<std::vector <int>>Tab;
 std::vector<std::vector <int>>Save;

public:
    Table();
    void setSizeTable(int size);
    int getSizeTable();
    void countNeighbors();
    void getFirsTableFromInput();
    void setFirstTableTest();
    void saveTable(int rounds);
    void showTable();
    std::vector<std::vector <int>> getTable() const;
    void copyTable();
    int applyRules(int cell, int liveNeighbors);
    void runGame(int rounds);
    ~Table();
};

#endif
