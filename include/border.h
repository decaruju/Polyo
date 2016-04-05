#ifndef BORDER_H
#define BORDER_H
#include <string>
class polyo;
class border
{
    public:
        border(std::string );
        border(polyo rhs);
        void change(int, bool);
        std::string getBord(){return _bord;}
        bool stop(){return !_cont;}
        bool connex();
        void oParTrue(int i);
        void cParTrue(int i);
        void oneTrue(int i);
        void zeroTrue(int i);
        void dashTrue(int i);
        void edgeTrue(int i);
        void oParFalse(int i);
        void cParFalse(int i);
        void oneFalse(int i);
        void zeroFalse(int i);
        void dashFalse(int i);
        void edgeFalse(int i);
        void downgradeNextCPar(int i);
        void downgradePreviousOPar(int i);
        void upgradePreviousDash(int i);
        void upgradeNextDash(int i);
        unsigned int countConnexComponents();
        bool isInscribed(){return _topIns && _bottomIns;}
        void setTopIns(){_topIns = true;}
        void setBottomIns(){_bottomIns = true;}
    private:
        std::string _bord;
        bool _cont;
        bool _topIns;
        bool _bottomIns;
};

#endif // BORDER_H
