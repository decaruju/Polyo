#ifndef GENERATE_H
#define GENERATE_H
#include <vector>

class polyo;
class cell;
class border;

void generateByArea(int n, int h, int v, int&, polyo pol, border b,int i=-1, int j=0);
void generateNoConstraint(int i, int j, int h, int v, polyo pol, int&);
void generateTree(int i, int h, int v, polyo pol, int& counter, std::vector<std::vector<bool>> noGrow);
void generateInscribedSnake(int i, int j, int h, int v, polyo pol, int&, bool, unsigned int);
void generateSnake(int i, int j, polyo pol, int& counter, unsigned int n);
void growGenerate(polyo pol, int& counter, std::vector<std::vector<bool>> canGrow, bool tree, bool inscribed, bool toArea, unsigned int n ,unsigned int h = 0, unsigned int v = 0);
void countOnly(int n, int h, int v, int& counter, border b, int i = -1, int j=0, int m =0);
#endif // GENERATE_H
