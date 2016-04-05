#include <iostream>
#include "polyo.h"
#include "cell.h"
#include "generate.h"
#include "border.h"
using namespace std;
int counter(0);

int main()
{
    countOnly(15,3,10,counter,border(""));
    cout<<counter<<endl;
    return 0;
}
