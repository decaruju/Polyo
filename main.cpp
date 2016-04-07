#include <iostream>
#include "polyo.h"
#include "cell.h"
#include "generate.h"
#include "border.h"
using namespace std;
int counter(0);

int main()
{
    growGenerate(polyo(),counter,vector<vector<bool>>(),false,false,true,50);
    cout<<counter<<endl;
    return 0;
}
