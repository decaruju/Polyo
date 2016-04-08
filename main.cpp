#include <iostream>
#include "polyo.h"
#include "cell.h"
#include "generate.h"
#include "border.h"
using namespace std;
int counter(0);

int main()
{
    generateSnake(polyo(),counter,false,true,0,5,10);
    cout<<counter<<endl;
    return 0;
}
