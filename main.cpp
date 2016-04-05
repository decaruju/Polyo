#include <iostream>
#include "polyo.h"
#include "cell.h"
#include "generate.h"
#include "border.h"
using namespace std;
int counter(0);

int main()
{
    generateInscribedTreeToArea(-1,6,6,polyo(),counter,vector<vector<bool>>(),17);
    cout<<counter<<endl;
    return 0;
}
