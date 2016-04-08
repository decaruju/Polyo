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

void growGenerate(polyo pol, int& counter, vector<vector<bool>> canGrow, bool tree, bool inscribed, bool toArea, unsigned int n, unsigned int h, unsigned int v)
{
    if (pol.getArea() == 0)
    {
        if (!inscribed)
        {
            h = 2*n+2;
            v = n;
            pol = polyo(h,v);
            counter = 0;
            canGrow = vector<vector<bool>>(h,vector<bool>(v,true));

            pol.addCell(cell(n+1,0));
            canGrow[n+1][0] = false;
            growGenerate(pol,counter,canGrow,tree,inscribed,toArea,n,h,v);
            return;
        }
        else
        {
            counter = 0;
            canGrow = vector<vector<bool>>(h,vector<bool>(v,true));
            pol = polyo(h,v);
            for (unsigned int k = 0; k < h; k++)
            {
                if (k>0)
                    canGrow[k-1][0] = false;
                canGrow[k][0] = false;
                polyo tempPol(pol);
                tempPol.addCell(cell(k,0));
                growGenerate(tempPol,counter,canGrow,tree,inscribed,toArea,n,h,v);
            }
            return;
        }
    }
    if (toArea)
    {
        if (pol.getArea() == n)
        {
            if (inscribed)
            {
                if (pol.isInscribed())
                {
                    cout<<pol.getArea()<<endl;
                    cout<<pol.toString()<<endl;
                    counter++;
                }
            }
            else
            {
                cout<<pol.toString()<<endl;
                counter++;
            }
            return;
        }
    }
    else
    {
        if (inscribed)
        {
            if (pol.isInscribed())
            {
                cout<<pol.toString()<<endl;
                counter++;
                return;
            }
        }
    }
    vector<cell> liberties(pol.liberties(tree,inscribed));
    unsigned int celli, cellj;
    for (unsigned int k = 0; k < liberties.size(); k++)
    {
        celli = liberties[k].getHPosition();
        cellj = liberties[k].getVPosition();
        if (canGrow[celli][cellj])
        {
            polyo tempPol(pol);
            tempPol.addCell(liberties[k]);
            canGrow[celli][cellj] = false;
            growGenerate(tempPol,counter,canGrow,tree,inscribed,toArea,n,h,v);
        }
    }
}

void generateSnake (polyo pol, int& counter, bool toArea, bool inscribed, int n, int h, int v, int i, int j, int k, int l)
{
    if (pol.getArea() == 0)
    {
        if (inscribed)
        {
            if (!toArea)
                n = h*v;
            pol = polyo(h,v);
            counter = 0;
            for (int a = 0 ; a<h; a++)
            {
                for (int b = 0 ; b < v; b++)
                {
                    polyo tempPol(pol);
                    tempPol.addCell(cell(a,b));
                    generateSnake(tempPol,counter,toArea,inscribed,n,h,v,a,b,a,b);
                }
            }
        }
        else if (toArea)
        {
            h = 2*n+2;
            v = 2*n+2;
            pol = polyo(h,v);
            counter = 0;
            pol.addCell(cell(n,n));
            generateSnake(pol,counter,toArea,inscribed,n,h,v,n,n,n,n);
        }
        return;
    }
    if (toArea)
    {
        if (pol.getArea() == n && (j<l|| (j==l && i<k)))
        {
            if (inscribed)
            {
                if (pol.isInscribed())
                {
                    cout<<pol.toString()<<endl;
                    counter++;
                    return;
                }
            }
            else if ((i<k|| (i==k && j<l)))
            {
                cout<<pol.toString()<<endl;
                counter++;
                return;
            }
        }
        if (pol.getArea() == n)
            return;
    }
    else
    {
        if (inscribed)
        {
            if (pol.isInscribed() && (i<k|| (i==k && j<l)))
            {
                cout<<pol.toString()<<endl;
                counter++;
                return;
            }
        }
        else
            return;
    }
    if (i<h-1 && !pol.hasCell(i+1,j) && !pol.hasCell(i+2,j) && !pol.hasCell(i+1,j+1) && !pol.hasCell(i+1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i+1,j));
        generateSnake(tempPol,counter,toArea,inscribed,n,h,v,i+1,j,k,l);
    }
    if (i>0 && !pol.hasCell(i-1,j) && !pol.hasCell(i-2,j) && !pol.hasCell(i-1,j+1) && !pol.hasCell(i-1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i-1,j));
        generateSnake(tempPol,counter,toArea,inscribed,n,h,v,i-1,j,k,l);
    }
    if (j<v-1 && !pol.hasCell(i,j+1) && !pol.hasCell(i,j+2) && !pol.hasCell(i+1,j+1) && !pol.hasCell(i-1,j+1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i,j+1));
        generateSnake(tempPol,counter,toArea,inscribed,n,h,v,i,j+1,k,l);
    }
    if (j>0 && !pol.hasCell(i,j-1) && !pol.hasCell(i,j-2) && !pol.hasCell(i+1,j-1) && !pol.hasCell(i-1,j-1))
    {
        polyo tempPol(pol);
        tempPol.addCell(cell(i,j-1));
        generateSnake(tempPol,counter,toArea,inscribed,n,h,v,i,j-1,k,l);
    }
}
