#include "polyo.h"
#include "cell.h"


using namespace std;

polyo::polyo(const unsigned int h, const unsigned int v)
{
    _cells = vector<vector<cell>>(h,vector<cell>(v));
    _cellVector = vector<cell>();
    _nonEmpty = vector<vector<bool>>(h,vector<bool>(v,false));
    _size[0] = h;
    _size[1] = v;
    _area = 0;
}

void polyo::setDegrees()
{
    for (unsigned int i(0); i< _size[0]; i++)
    {
        for (unsigned int j(0); j< _size[1]; j++)
        {
            _cells[i][j].setDegree(*this);
        }
    }
}

void polyo::addCell(cell cellToAdd)
{
    unsigned int h = cellToAdd.getHPosition();
    unsigned int v = cellToAdd.getVPosition();
    if (h<_size[0] && v<_size[1])
    {
        if (!_nonEmpty[h][v] )
            _cells[h][v] = cellToAdd;

        _nonEmpty[h][v] = true;
        _cellVector.push_back(cell(h,v));
    }
    _area++;
}

string polyo::toString()
{
    string rtn;
    for (unsigned int i(0); i< _size[0]; i++)
    {
        for (unsigned int j(0); j< _size[1]; j++)
        {
            if (_nonEmpty[i][j])
                rtn += "X";
            else
                rtn += "-";
        }
        rtn += "\n";
    }
    return rtn;
}
bitmap_image polyo::toBitmap()
{
    bitmap_image rtn(_size[0],_size[1]);
    for (unsigned int i(0); i< _size[0]; i++)
    {
        for (unsigned int j(0); j< _size[1]; j++)
        {
            if (_nonEmpty[i][j])
                rtn.set_pixel(i,j,0,0,0);
            else
                rtn.set_pixel(i,j,255,255,255);
        }
    }
    return rtn;
}

string polyo::toStringD()
{
    string rtn;
    for (unsigned int i(0); i< _size[0]; i++)
    {
        for (unsigned int j(0); j< _size[1]; j++)
        {
            if (_nonEmpty[i][j])
                rtn += to_string(_cells[i][j].getDegree());
            else
                rtn += "O";
        }
        rtn += "\n";
    }
    return rtn;
}
bool polyo::isConnected()
{
    bool rtn(true);
    bool cont(true);
    for (unsigned int i(0); i< _size[0] && cont; i++)
    {
        for (unsigned int j(0); j<_size[1] && cont;  j++)
        {
            if (_nonEmpty[i][j])
            {
                cell cellToVisit;
                vector<vector<bool>> visited = vector<vector<bool>>(_size[0],vector<bool>(_size[1],false));
                vector<cell> toVisit = {_cells[i][j]};
                visited[i][j]=true;
                while (toVisit.size()>0)
                {
                    cellToVisit = toVisit.back();
                    toVisit.pop_back();
                    this->findNeighbors(visited, cellToVisit , toVisit);
                }

                for (unsigned int i(0); i<_size[0]; i++)
                {
                    for (unsigned int j(0); j<_size[1]; j++)
                    {
                        if (visited[i][j] != _nonEmpty[i][j])
                            rtn = false;
                    }
                }
                cont=false;
            }
        }
    }
    return rtn;
}

bool polyo::findNeighbors(vector<vector<bool>>& visited, cell cellA , vector<cell>& toVisit)
{
    bool rtn = false;
    unsigned int h = cellA.getHPosition();
    unsigned int v = cellA.getVPosition();
    if (h>0 && !visited[h-1][v] && _nonEmpty[h-1][v])
    {
        rtn = true;
        toVisit.push_back(cell(h-1,v));
        visited[h-1][v]=true;
    }
    if (h<_size[0]-1 && !visited[h+1][v] && _nonEmpty[h+1][v])
    {
        rtn = true;
        toVisit.push_back(cell(h+1,v));
        visited[h+1][v]=true;
    }

    if (v>0 && !visited[h][v-1] && _nonEmpty[h][v-1])
    {
        rtn = true;
        toVisit.push_back(cell(h,v-1));
        visited[h][v-1] = true;
    }
    if (v<_size[1]-1 && !visited[h][v+1] && _nonEmpty[h][v+1])
    {
        rtn = true;
        toVisit.push_back(cell(h,v+1));
        visited[h][v+1] = true;
    }
    return rtn;
}

bool polyo::isInscribed()
{
    if (_area==0)
        return false;
    bool rtn(true);
    bool temprtn(false);
    unsigned int i(0);
    for(i=0; i<_size[0]; i++)
    {
        if (_nonEmpty[i][0])
            temprtn = true;
    }
    rtn = rtn && temprtn;
    temprtn = false;
    for(i=0; i<_size[0]; i++)
    {
        if (_nonEmpty[i][_size[1]-1])
            temprtn = true;
    }
    rtn = rtn && temprtn;
    temprtn = false;
    for(i=0; i<_size[1]; i++)
    {
        if (_nonEmpty[0][i])
            temprtn = true;
    }
    rtn = rtn && temprtn;
    temprtn = false;
    for(i=0; i<_size[1]; i++)
    {
        if (_nonEmpty[_size[0]-1][i])
            temprtn = true;
    }
    rtn = rtn && temprtn;
    temprtn = false;
    return rtn;
}

bool polyo::hasCell(unsigned int i, unsigned int j)
{
    if (i<_size[0] && j<_size[1])
        return _nonEmpty[i][j];
    return false;
}

void polyo::cross()
{
    array<unsigned int, 2> tempSize({_size[0]*2+1,_size[1]*2+1});
    vector<vector<cell>> tempCells = vector<vector<cell>>(tempSize[0],vector<cell>(tempSize[1]));
    vector<vector<bool>> tempNonEmpty = vector<vector<bool>>(tempSize[0],vector<bool>(tempSize[1],false));
    unsigned int tempArea = _area*4+1;
    for (unsigned int i(0); i<_size[0]; i++)
    {
        for (unsigned int j(0); j<_size[1]; j++)
        {
            if (_nonEmpty[i][j])
            {
                tempNonEmpty[2*i][2*j+1] = true;
                tempNonEmpty[2*i+1][2*j+1] = true;
                tempNonEmpty[2*i+2][2*j+1] = true;
                tempNonEmpty[2*i+1][2*j] = true;
                tempNonEmpty[2*i+1][2*j+2] = true;
                tempCells[2*i][2*j+1] = cell(2*i,2*j+1);
                tempCells[2*i+1][2*j+1] = cell(2*i+1,2*j+1);
                tempCells[2*i+2][2*j+1] = cell(2*i+2,2*j+1);
                tempCells[2*i+1][2*j] = cell(2*i+1,2*j);
                tempCells[2*i+1][2*j+2] = cell(2*i+1,2*j+2);

            }
        }
    }
    _cells = tempCells;
    _area = tempArea;
    _nonEmpty = tempNonEmpty;
    _size = tempSize;
}

vector<cell> polyo::liberties(bool tree, bool inscribed)
{
    vector<cell> rtn(0);
    unsigned int degree;
    for (unsigned int i = 0; i< _size[0]; i++)
    {
        for (unsigned int j = 0; j < _size[1]; j++)
        {
            degree = 0;
            if (i<_size[0]-1 && _nonEmpty[i+1][j])
                degree++;
            if (i>0 && _nonEmpty[i-1][j])
                degree++;
            if (j<_size[1]-1 && _nonEmpty[i][j+1])
                degree++;
            if (j>0 && _nonEmpty[i][j-1])
                degree++;

            if (!inscribed)
            {
                if (j>0 || (j==0 && i>_size[1]))
                {
                    if (tree)
                    {
                        if (degree == 1)
                            rtn.push_back(cell(i,j));
                    }
                    else if (degree > 0 )
                        rtn.push_back(cell(i,j));
                }
            }
            else
            {
                if (tree)
                {
                    if (degree == 1)
                        rtn.push_back(cell(i,j));
                }
                else if (degree > 0)
                    rtn.push_back(cell(i,j));
            }
        }
    }
    return rtn;
}
