#include "cell.h"
#include "polyo.h"

cell::cell()
{

}

cell::cell(unsigned int h, unsigned int v)
{
    _position[0] = h;
    _position[1] = v;
}

bool cell::operator==(cell cell)
{
    return (this->getHPosition() == cell.getHPosition() && this->getVPosition() == cell.getVPosition());
}

void cell::setDegree(polyo polyo)
{
    unsigned int rtn = 0;
    if (_position[0] < polyo.getHSize()-1 && polyo.hasCell(_position[0]+1,_position[1]))
        rtn++;
    if (_position[0] > 0 && polyo.hasCell(_position[0]-1,_position[1]))
        rtn++;
    if (_position[1] < polyo.getVSize()-1 && polyo.hasCell(_position[0],_position[1]+1))
        rtn++;
    if (_position[1] > 0 && polyo.hasCell(_position[0],_position[1]-1))
        rtn++;
    _degree = rtn;
}

std::string cell::toString()
{
    std::string rtn = "";
    rtn += "(";
    rtn += std::to_string(_position[0]);
    rtn += ",";
    rtn += std::to_string(_position[1]);
    rtn += ")";
    return rtn;
}
