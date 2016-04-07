#ifndef CELL_H
#define CELL_H
#include <array>
#include <vector>
#include <string>

class polyo;

class cell
{
    public:
        cell();
        cell(unsigned int h, unsigned int v);
        cell(const cell& other){_position = other._position; _degree = other._degree;}
        unsigned int getHPosition() {return _position[0];}
        unsigned int getVPosition() {return _position[1];}
        void setDegree(polyo polyo);
        unsigned int getDegree(){return _degree;}
        bool operator==(cell);
        std::string toString();

    private:
        std::array<int,2> _position;
        unsigned int _degree;
};

#endif // CELL_H
