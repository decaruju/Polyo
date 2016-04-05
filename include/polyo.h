#ifndef POLYO_H
#define POLYO_H
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include "bitmap_image.hpp"

class cell;

class polyo
{
    public:
        polyo(){_area=0;}
        polyo(const unsigned int h, const unsigned int v);
        polyo(const polyo& other){_cells = other._cells; _nonEmpty = other._nonEmpty; _size = other._size; _area = other._area;}
        void addCell(const cell cell);
        void setDegrees();
        bool hasCell(unsigned int i, unsigned int j);
        std::string toString();
        std::string toStringD();
        unsigned int getHSize(){return _size[0];}
        unsigned int getVSize(){return _size[1];}
        bool isConnected();
        bool isTree();
        bool isInscribed();
        unsigned int getArea(){return _area;}
        void cross();
        bitmap_image toBitmap();
        std::vector<cell> treeLiberties();

     private:
        std::vector<std::vector<cell>> _cells;
        std::vector<std::vector<bool>> _nonEmpty;
        std::array<unsigned int, 2> _size;
        bool findNeighbors(std::vector<std::vector<bool>>& visited, cell , std::vector<cell>& );
        unsigned int _area;
};

#endif // POLYO_H
