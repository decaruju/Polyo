#include "generate.h"
#include "polyo.h"
#include "cell.h"
#include "border.h"

using namespace std;
void countOnly(int n, int h, int v, int& counter, border b, int i, int j, int m)
{
    if (m == 0)
        b = border(string(h,'0'));

    if (b.stop())
        return;

    if (i==h-1)
    {
        if (j==v-1)
        {
            if (b.getBord()!= string(h,'0') && b.countConnexComponents() == 1 && m == n)
            {
                counter++;
                if (counter%10000 == 0)
                {
                    cout<<counter<<endl;
                }
            }
            return;
        }
        i=0;
        j++;
    }
    else
        i++;

    border tempBord(b.getBord());

    b.change(i,false);
    tempBord.change(i,true);
    if (i==0)
        tempBord.setTopIns();
    else if (i==v-1)
        tempBord.setBottomIns();
    countOnly(n,h,v,counter,tempBord,i,j,m+1);
    countOnly(n,h,v,counter,b,i,j,m);
}

void generateByArea(int n, int h, int v, int& counter, polyo pol, border b ,int i, int j)
{
    if (pol.getArea() == 0)
    {
        pol = polyo(h,v);
    }
    if (i==h-1 && j==0)
    {
        b = border(pol);
        if (b.getBord() == string(h,'0'))
            return;
    }

    if (b.stop())
    {
        return;
    }
    if (i==h-1)
    {
        if (j==v-1)
        {
            if (b.getBord()!= string(h,'0') && b.countConnexComponents() == 1 && pol.getArea() == n)
            {
                cout<<pol.toString()<<endl;
                cout<<b.getBord()<<endl;
                counter++;
                cout<<counter<<endl;
            }
            return;
        }
        i=0;
        j++;
    }
    else
        i++;
    if (n-pol.getArea()>h-i+(h)*(v-j-1))
        return;

    if (n-pol.getArea()<v-j-1)
        return;



    border tempBord(b.getBord());
    polyo temppol(pol);

    b.change(i,false);
    tempBord.change(i,true);

    pol.addCell(cell(i,j));

    generateByArea(n,h,v,counter,pol,tempBord,i,j);
    generateByArea(n,h,v,counter,temppol,b,i,j);


}

void generateNoConstraint(int i, int j, int h, int v, polyo pol, int& counter)
{
    if (i==h-1)
    {
        if (j==v-1)
        {
            if (pol.isInscribed() && pol.isConnected())
            {
                cout<<pol.toString()<<endl;
                counter++;
            }
            return;
        }
        i=0;
        j++;
    }
    else
        i++;

    generateNoConstraint(i,j,h,v,pol,counter);
    pol.addCell(cell(i,j));
    generateNoConstraint(i,j,h,v,pol,counter);
}

void generateTree(int i, int h, int v, polyo pol, int& counter, vector<vector<bool>> canGrow)
{
    if (i==-1)
    {
        canGrow = vector<vector<bool>>(h,vector<bool>(v,true));
        for (int k(0); k<h; k++)
        {
            if (k>0)
            {
                canGrow[k-1][0]=false;
            }
            polyo tempPol(h,v);
            tempPol.addCell(cell(k,0));
            generateTree(0,h,v,tempPol,counter,canGrow);
        }
        return;
    }

    vector<cell> liberties(pol.treeLiberties());

    for (int k(0); k<liberties.size(); k++)
    {
        if (canGrow[liberties[k].getHPosition()][liberties[k].getVPosition()])
        {
            polyo tempPol(pol);
            canGrow[liberties[k].getHPosition()][liberties[k].getVPosition()] = false;
            tempPol.addCell(liberties[k]);
            generateTree(i,h,v,tempPol,counter,canGrow);
        }
    }
    if (pol.isInscribed())
    {
        cout<<pol.toString()<<endl;
        counter++;
    }

}
void generateTreeToArea(int i, int h, int v, polyo pol, int& counter, vector<vector<bool>> canGrow,int n)
{
    if (i==-1)
    {
        canGrow = vector<vector<bool>>(h,vector<bool>(v,true));
        for (int k(0); k<h; k++)
        {
            if (k>0)
            {
                canGrow[k-1][0]=false;
            }
            polyo tempPol(h,v);
            tempPol.addCell(cell(k,0));
            generateTreeToArea(0,h,v,tempPol,counter,canGrow,n);
        }
        return;
    }
    if (pol.getArea() > n)
        return;
    vector<cell> liberties(pol.treeLiberties());

    for (int k(0); k<liberties.size(); k++)
    {
        if (canGrow[liberties[k].getHPosition()][liberties[k].getVPosition()])
        {
            polyo tempPol(pol);
            canGrow[liberties[k].getHPosition()][liberties[k].getVPosition()] = false;
            tempPol.addCell(liberties[k]);
            generateTreeToArea(i,h,v,tempPol,counter,canGrow,n);
        }
    }
    if (pol.isInscribed() && pol.getArea() == n)
    {
        cout<<pol.toString()<<endl;
        counter++;
    }
}
void generateInscribedSnake(int i, int j, int h, int v, polyo pol, int& counter, bool toArea, unsigned int n)
{
    if (i==-1)
    {
        pol = polyo(h,v);
        for (unsigned int k(0); k<h; k++)
        {
            for (unsigned int l(0); l<v; l++)
            {
                polyo tempPol(pol);
                tempPol.addCell(cell(k,l));
                generateInscribedSnake(k,l,h,v,tempPol,counter,toArea,n);
                cout<<k<<endl;
                cout<<l<<endl;
            }
        }
        return;
    }
    if (toArea&&pol.getArea()>n)
    {
        return;
    }
    if (pol.isInscribed())
    {
        if (toArea)
        {
            if(pol.getArea() == n)
            {
                cout<<pol.toString()<<endl;
                counter++;
            }
        }
        else
        {
            cout<<pol.toString()<<endl;
            counter++;
        }

    }
    if (i<h-1 && !pol.hasCell(i+1,j) && !pol.hasCell(i+2,j) && !pol.hasCell(i+1,j+1) && !pol.hasCell(i+1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i+1,j));
        generateInscribedSnake(i+1,j,h,v,tempPol,counter,toArea,n);
    }
    if (i>0 && !pol.hasCell(i-1,j) && !pol.hasCell(i-2,j) && !pol.hasCell(i-1,j+1) && !pol.hasCell(i-1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i-1,j));
        generateInscribedSnake(i-1,j,h,v,tempPol,counter,toArea,n);
    }
    if (j<v-1 && !pol.hasCell(i,j+1) && !pol.hasCell(i,j+2) && !pol.hasCell(i+1,j+1) && !pol.hasCell(i-1,j+1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i,j+1));
        generateInscribedSnake(i,j+1,h,v,tempPol,counter,toArea,n);
    }
    if (j>0 && !pol.hasCell(i,j-1) && !pol.hasCell(i,j-2) && !pol.hasCell(i+1,j-1) && !pol.hasCell(i-1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i,j-1));
        generateInscribedSnake(i,j-1,h,v,tempPol,counter,toArea,n);
    }

}

void generateSnake(int i, int j, polyo pol, int& counter, unsigned int n)
{
    if (i==-1)
    {
                polyo tempPol(2*n+2,2*n+2);
                tempPol.addCell(cell(n,n));
                generateSnake(n,n,tempPol,counter,n);
                return;
    }

    if(pol.getArea() == n)
    {
        cout<<pol.toString()<<endl;
        counter++;
        return;
    }

    if (!pol.hasCell(i+1,j) && !pol.hasCell(i+2,j) && !pol.hasCell(i+1,j+1) && !pol.hasCell(i+1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i+1,j));
        generateSnake(i+1,j,tempPol,counter,n);
    }
    if (!pol.hasCell(i-1,j) && !pol.hasCell(i-2,j) && !pol.hasCell(i-1,j+1) && !pol.hasCell(i-1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i-1,j));
        generateSnake(i-1,j,tempPol,counter,n);
    }
    if (!pol.hasCell(i,j+1) && !pol.hasCell(i,j+2) && !pol.hasCell(i+1,j+1) && !pol.hasCell(i-1,j+1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i,j+1));
        generateSnake(i,j+1,tempPol,counter,n);
    }
    if (!pol.hasCell(i,j-1) && !pol.hasCell(i,j-2) && !pol.hasCell(i+1,j-1) && !pol.hasCell(i-1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i,j-1));
        generateSnake(i,j-1,tempPol,counter,n);
    }

}

