#include <iostream>
#include <map>

#include "generator/Classes.hpp"

using std::cout;

static std::map<std::array<int, 3>, int> ordermap_;

QuartetSet GenerateInitialQuartetTargets(std::array<int, 4> amlst, bool initial)
{
    int flag = (initial ? QUARTET_INITIAL : 0);

    QuartetSet qs;
    int nam1 = ((amlst[0] + 1) * (amlst[0] + 2)) / 2;
    int nam2 = ((amlst[1] + 1) * (amlst[1] + 2)) / 2;
    int nam3 = ((amlst[2] + 1) * (amlst[2] + 2)) / 2;
    int nam4 = ((amlst[3] + 1) * (amlst[3] + 2)) / 2;

    Gaussian cur1 = Gaussian{amlst[0], 0, 0};
    for(int i = 0; i < nam1; i++)
    {
        Gaussian cur2 = Gaussian{amlst[1], 0, 0};
        for(int j = 0; j < nam2; j++)
        {
            Doublet bra{DoubletType::BRA, cur1, cur2};
            Gaussian cur3 = Gaussian{amlst[2], 0, 0};
            for(int k = 0; k < nam3; k++)
            {
                Gaussian cur4 = Gaussian{amlst[3], 0, 0};
                for(int l = 0; l < nam4; l++)
                {
                    Doublet ket{DoubletType::KET, cur3, cur4};
                    qs.insert(Quartet{bra, ket, 0, flag});
                    cur4.Iterate();
                } 

                cur3.Iterate();
            }

            cur2.Iterate(); 
        }       
                
        cur1.Iterate();
    }
                
    return qs;
}

DoubletSet GenerateInitialDoubletTargets(std::array<int, 2> amlst, DoubletType type, bool initial)
{
    int flag = (initial ? DOUBLET_INITIAL : 0);

    DoubletSet ds;
    int nam1 = ((amlst[0] + 1) * (amlst[0] + 2)) / 2;
    int nam2 = ((amlst[1] + 1) * (amlst[1] + 2)) / 2;

    Gaussian cur1 = Gaussian{amlst[0], 0, 0};
    for(int i = 0; i < nam1; i++)
    {
        Gaussian cur2 = Gaussian{amlst[1], 0, 0};
        for(int j = 0; j < nam2; j++)
        {
            ds.insert(Doublet{type, cur1, cur2, flag});
            cur2.Iterate();
        }
        cur1.Iterate();
    }
                
    return ds;
}



void PruneRight(QuartetSet & qs, DoubletType type)
{
    QuartetSet qsnew;

    for(auto & it : qs)
    {
        if(it.get(type).right.am() != 0)
            qsnew.insert(it);
    }

    qs = qsnew; 
}



void PrintQuartetSet(const QuartetSet & q, const std::string & title)
{
    cout << title << ": " << q.size() << "\n";
    for(auto & it : q)
        cout << "    " << it << "       ->      " << it.code_var() << "\n";
    cout << "\n";
}




void PrintQuartetSet_Arr(const QuartetSet & q, const std::string & title)
{
    cout << title << ": " << q.size() << "\n";
    for(auto & it : q)
        cout << "    " << it << "       ->      " << it.array_var() << "\n";
    cout << "\n";
}


int GaussianOrder(const std::array<int, 3> & ijk)
{
    if(!ordermap_.size())
    {
        // generate the order map
        for(int i = 0; i < 20; i++)
        {
            int n = 0;
            Gaussian g{i, 0, 0};
            ordermap_[g.ijk] = n++;
            
            while(g.Iterate())
                ordermap_[g.ijk] = n++;
        }
    }

    return ordermap_.at(ijk);
}