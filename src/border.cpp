#include "border.h"
#include "polyo.h"
#include "cell.h"
using namespace std;

border::border(string rhs)
{
    _cont = true;
    _bord = rhs;
    _topIns = false;
    _bottomIns = false;
}

border::border(polyo rhs)
{
    string bord = "";
        for (int k(0); k<rhs.getHSize(); k++)
        {
            if (rhs.hasCell(k,0))
            {
                if (bord[bord.size()-1] == '0')
                    bord += "1";
                else if (bord[bord.size()-1] == '1')
                {
                    bord[bord.size()-1]='(';
                    bord += ")";
                }
                else if (bord[bord.size()-1] == ')')
                {
                    bord[bord.size()-1]='-';
                    bord += ")";
                }
                else
                    bord += "1";
            }
            else
                bord += "0";
        }
    _bord = bord;
    _cont = bord != string(rhs.getHSize(),'0');
}

void border::downgradeNextCPar(int i)
{
    while (i<_bord.size() - 1 && _bord[i] != ')')
    {
        i++;
        if (_bord[i] == '(')
        {
            while (_bord[i] == '-')
            {
                i++;
            }
            i++;
        }
    }
    _bord[i] = '-';
}
void border::downgradePreviousOPar(int i)
{
    while (i<_bord.size()-1 && _bord[i] != '(')
    {
        i--;
        if (_bord[i] == ')')
        {
            while (_bord[i] == '-')
            {
                i--;
            }
            i--;
        }
    }
    _bord[i] = '-';
}

void border::upgradePreviousDash(int i)
{
    while (i>0 && _bord[i]!= '-' && _bord[i]!= '(')
    {
        i--;
        if (i>0 && _bord[i] == ')')
        {
            i--;
            while (i>0 && _bord[i] == '-')
            {
                i--;
            }
            if (i>0)
                i--;
        }
    }
    if (_bord[i] == '-')
        _bord[i] = ')';
    else
        _bord[i] = '1';
}
void border::upgradeNextDash(int i)
{
    while (i<_bord.size()-1 && _bord[i]!= '-' && _bord[i]!= ')')
    {
        i++;
        if (i<_bord.size()-1 &&_bord[i] == '(')
        {
            i++;
            while (i<_bord.size()-1 &&_bord[i] == '-')
            {
                i++;
            }
            i++;
        }
    }
    if (_bord[i] == '-')
        _bord[i] = '(';
    else
        _bord[i] = '1';

}
void border::edgeTrue(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '1';
            return;
        break;

        case '1':
            _bord[i] = '1';
            return;
        break;

        case '(':
            _bord[i] = '(';
            return;
        break;

        case '-':
            //Impossible
            return;
        break;

        case ')':
            //Impossible
            return;
        break;
    }
}
void border::oParTrue(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '-';
            return;
        break;

        case '1':
            if (_bord[i-1] == '1')
                _bord[i-1] = '(';
            _bord[i] = '-';
            return;
        break;

        case '(':
            _bord[i] = '-';
            this->downgradeNextCPar(i);
            return;
        break;

        case '-':
            _bord[i] = '-';
            return;
        break;

        case ')':
            _bord[i] = ')';
            return;
        break;
    }
}
void border::cParTrue(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i-1] = '-';
            _bord[i] = ')';
            return;
        break;

        case '1':
            _bord[i-1] = '-';
            _bord[i] = ')';
            return;
        break;

        case '(':
            _bord[i-1] = '-';
            _bord[i] = '-';
            return;
        break;

        case '-':
            _bord[i] = '-';
            this->downgradePreviousOPar(i);
            return;
        break;

        case ')':
            _bord[i-1] = '-';
            _bord[i] = ')';
            return;
        break;
    }
}
void border::oneTrue(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i-1] = '(';
            _bord[i] = ')';
            return;
        break;

        case '1':
            _bord[i-1] = '(';
            _bord[i] = ')';
            return;
        break;

        case '(':
            _bord[i-1] = '(';
            _bord[i] = '-';
            return;
        break;

        case '-':
            _bord[i-1] = '-';
            _bord[i] = '-';
            return;
        break;

        case ')':
            _bord[i-1] = '-';
            _bord[i] = ')';
            return;
        break;
    }
}
void border::zeroTrue(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '1';
            return;
        break;

        case '1':
            _bord[i] = '1';
            return;
        break;

        case '(':
            _bord[i] = '(';
            return;
        break;

        case '-':
            _bord[i] = '-';
            return;
        break;

        case ')':
            _bord[i] = ')';
            return;
        break;
    }
}
void border::dashTrue(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '-';
            return;
        break;

        case '1':
            _bord[i] = '-';
            return;
        break;

        case '(':
            _bord[i] = '-';
            this->downgradeNextCPar(i);
            return;
        break;

        case '-':
            _bord[i] = '-';
            return;
        break;

        case ')':
            _bord[i] = ')';
            return;
        break;
    }
}
void border::oParFalse(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '0';
            return;
        break;

        case '1':
            _bord[i] = '0';
            _cont = false;
            return;
        break;

        case '(':
            //impossible
            return;
        break;

        case '-':
            _bord[i] = '0';
            return;
        break;

        case ')':
            _bord[i] = '0';
            this->upgradePreviousDash(i);
            return;
        break;
    }
}
void border::cParFalse(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '0';
            return;
        break;

        case '1':
            _bord[i] = '0';
            _cont = false;
            return;
        break;

        case '(':
            _bord[i] = '0';
            this->upgradeNextDash(i);
            return;
        break;

        case '-':
            _bord[i] = '0';
            return;
        break;

        case ')':
            _bord[i] = '0';
            this->upgradePreviousDash(i);
            return;
        break;
    }
}
void border::oneFalse(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '0';
            return;
        break;

        case '1':
            _bord[i] = '0';
            _cont = false;
            return;
        break;

        case '(':
            _bord[i] = '0';
            this->upgradeNextDash(i);
            return;
        break;

        case '-':
            _bord[i] = '0';
            return;
        break;

        case ')':
            _bord[i] = '0';
            this->upgradePreviousDash(i);
            return;
        break;
    }
}
void border::zeroFalse(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '0';
            return;
        break;

        case '1':
            _bord[i] = '0';
            _cont = false;
            return;
        break;

        case '(':
            _bord[i] = '0';
            this->upgradeNextDash(i);
            return;
        break;

        case '-':
            _bord[i] = '0';
            return;
        break;

        case ')':
            _bord[i] = '0';
            this->upgradePreviousDash(i);
            return;
        break;
    }
}
void border::dashFalse(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '0';
            return;
        break;

        case '1':
            _bord[i] = '0';
            _cont = false;
            return;
        break;

        case '(':
            _bord[i] = '0';
            this->upgradeNextDash(i);
            return;
        break;

        case '-':
            _bord[i] = '0';
            return;
        break;

        case ')':
            _bord[i] = '0';
            this->upgradePreviousDash(i);
            return;
        break;
    }
}

void border::edgeFalse(int i)
{
    switch (_bord[i])
    {
        case '0':
            _bord[i] = '0';
            return;
        break;

        case '1':
            _bord[i] = '0';
            _cont = false;
            return;
        break;

        case '(':
            _bord[i] = '0';
            this->upgradeNextDash(i);
            return;
        break;

        case '-':
            //Impossible
            return;
        break;

        case ')':
            //Impossible
            return;
        break;
    }
}

bool border::connex()
{
    int countPar = 0;
    int countOnes = 0;
    for (int i = 0; i< _bord.size(); i++)
    {
        if (_bord[i] == '1')
            countOnes++;
        if (_bord[i] == '(')
            countPar++;
    }
    return (countOnes + countPar == 1);
}
void border::change(int i ,bool add)
{
    if (i==0)
    {
        if (add)
            this->edgeTrue(i);
        else
            this->edgeFalse(i);
        return;
    }

    switch (_bord [i-1])
    {
    case '0':
        if (add)
            this->zeroTrue(i);
        else
            this->zeroFalse(i);
            return;
    break;

    case '1':
        if (add)
            this->oneTrue(i);
        else
            this->oneFalse(i);
            return;
    break;

    case '(':
        if (add)
            this->oParTrue(i);
        else
            this->cParFalse(i);
            return;
    break;

    case '-':
        if (add)
            this->dashTrue(i);
        else
            this->dashFalse(i);
            return;
    break;

    case ')':
        if (add)
            this->cParTrue(i);
        else
            this->cParFalse(i);
            return;
    break;
    }
}

unsigned int border::countConnexComponents()
{
    unsigned int rtn = 0;
    for (unsigned int i = 0; i<_bord.size(); i++)
    {
        if (_bord[i] == '(' || _bord[i] == '1')
        {
            rtn++;
        }
    }
    return rtn;
}

//keep inscription data
