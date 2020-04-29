#include<bits/stdc++.h>
#define N 100
#define M 26
using namespace std;

class DFA{
int n,m,nr,nrf,inc;
int a[N][M];
int t[N][M]; //retine graful transpus
bool sfarsit[N];
bool marked[N]; //pentru nodurile inaccesibile si cele moarte(din care nu se poate ajunge intr-o stare finala)

public:
    DFA(){
    }

    void elimination();
    void minimizing();

    friend istream& operator>>(istream&,DFA&);
    friend void minimizat(vector< vector<int> >& ,const DFA&);
};




void DFA::elimination()
{
    bool viz[n];
    memset(viz,0,sizeof(viz));
    viz[inc]=1;
    stack<int> s;
    s.push(inc);
    while(!s.empty())
    {
        int x=s.top();
        s.pop();
        if(!viz[x])
            viz[x]=1;
        for(int i=0;i<m;++i)
            if(a[x][i])
                if(!viz[a[x][i]])
                    s.push(a[x][i]);

    }
    for(int i=0;i<n;++i)
        if(!viz[i])
            marked[i]=1;

    queue<int> q;
    memset(viz,0,sizeof(viz));
    for(int i=0;i<n;++i)
        if(sfarsit[i])
        {viz[i]=1;
        q.push(i);
        }
        while(!q.empty())
        {
            int x=q.front();
            q.pop();

            for(int j=0;j<m;++j)
                if(t[x][j]!=-1)
                    if(!viz[t[x][j]])
                        {   //cout<<x<<' '<<t[x][j]<<endl;
                            viz[t[x][j]]=1;
                            q.push(t[x][j]);
                        }

        }
        for(int j=0;j<n;++j)
            if(!viz[j])
                marked[j]=1;

        /*for(int j=0;j<n;j++)
            cout<<marked[j];
        cout<<endl;*/

    for(int i=0;i<n;++i)
        if(marked[i])
    {
        for(int j=0;j<m;++j)
            a[i][j]=-1;
        for(int j=0;j<m;++j)
            if(t[i][j])
        {
            a[t[i][j]][j]=-1;
        }

    }

}

int get_index(int x, vector< vector<int> >& v)
{
    for(int i=0;i<v.size();++i)
        for(int j=0;j<v[i].size();++j)
            if(v[i][j]==x)
                return i;

}

ofstream fout("minimizare.out");

void minimizat(vector< vector<int> >& v,const DFA& d)
{
    vector<int> finale;
    for(int i=0;i<v.size();++i)
    {
        //trebuie marcate si starile finale
        for(int j=0;j<v[i].size();++j)
            if(d.sfarsit[v[i][j]])
                {
                    finale.emplace_back(i);
                    break;
                }
        for(int l=0;l<d.m;++l)
        {
            int x=d.a[v[i][0]][l];
            fout<<i<<' '<<l<<' '<<get_index(x,v)<<endl;
        }

    }
    fout<<"Starile finale sunt: ";
    for(int i: finale)
        fout<<i<<' ';
    fout<<endl;

}

istream& operator>>(istream& in, DFA& d)
{
    memset(d.a,-1,sizeof(d.a));
    memset(d.t,-1,sizeof(d.t));
    int x,y,z;
    in>>d.n>>d.m>>d.nr;
    for(int i=0;i<d.nr;i++){
        in>>x>>y>>z;
        d.a[x][y]=z;
        d.t[z][y]=x;
    }
    in>>d.inc;
    in>>d.nrf;
    for(int i=0;i<d.nr;i++)
        d.sfarsit[i]=0;
    for(int i=0;i<d.nrf;i++)
    {
        in>>x;
        d.sfarsit[x]=1;
    }
    for(int i=0;i<d.nr;i++)
        d.marked[i]=0;

}


void afisare(vector< vector<int> >& v)
{
    for(int i=0;i<v.size();++i){
        for(int j=0;j<v[i].size();++j)

        cout<<v[i][j]<<' ';
    cout<<endl;
    }
}


void DFA::minimizing()
{
    //seturile de partitie
    vector< vector<int> > ps[2];
    vector<int> f[2];
    for(int i=0;i<n;i++)
        if(!marked[i])
        f[sfarsit[i]].push_back(i);
    ps[1].reserve(2);
    ps[1].emplace_back(f[0]);
    ps[1].emplace_back(f[1]);

    while(true)
    {
        //construiesc alternativ in ps[1] noul set de partitii(de clase de echivalenta)
        //ps[0] va fi ps[1]
        ps[0]=ps[1];
        for(int i=0;i<ps[0].size();++i){
            for(int j=0;j<ps[1][i].size();++j)
            {
                //cout<<get_index(ps[0][i][j],ps[0])<<' ';
                //pentru fiecare nod(stare a dfa-ului) le compar cu toate pentru a afla daca se vor afla in subseturi
                //diferite la urmatoarea partitionare
                int k;
                for(k=0;k<j;++k)
                {
                    bool ok=1;
                    int x=ps[1][i][j];
                    int y=ps[1][i][k];

                    for(int t=0;t<m && ok;++t)
                    {
                        if(a[x][t]==a[y][t])
                            continue;
                        if(get_index(a[x][t],ps[1])!=get_index(a[y][t],ps[1]))
                            ok=0;
                        //cout<<x<<' '<<y<<' '<<t<<' '<<get_index(a[x][t],ps[1])<<' '<<get_index(a[y][t],ps[1])<<endl;
                    }
                    if(!ok)
                        break;
                }
                    if(k==j)
                        continue;
                    //trebuie mutat in alt subset sau creat un nou subset ce-l continue doar pe ps[0][i][j]
                    bool adaugat=0;
                    for(int k=ps[0].size();k<ps[1].size();++k)
                    {
                            int l;
                        for(l=0;l<ps[1][k].size();++l)
                    {
                        int x=ps[1][i][j];
                        int y=ps[1][k][l];
                        bool ok2=1;
                        for(int t=0;t<m && ok2;++t)
                        {
                        if(a[x][t]==a[y][t])
                            continue;
                        if(get_index(a[x][t],ps[1])!=get_index(a[y][t],ps[1]))
                            ok2=0;
                        }
                        if(!ok2)
                            break;

                    }
                    if(l==ps[1][k].size()){
                        ps[1][k].emplace_back(ps[1][i][j]);
                        ps[1][i].erase(ps[1][i].begin()+j);
                        ps[0][i].erase(ps[0][i].begin()+j);
                        adaugat=1;
                        }

                }
                if(adaugat)
                    continue;
                vector<int> aux;
                aux.push_back(ps[1][i][j]);
                ps[1].emplace_back(aux);
                ps[1][i].erase(ps[1][i].begin()+j);
                ps[0][i].erase(ps[0][i].begin()+j);

            }
        }
    	if(ps[0] == ps[1])
            break;

    }

    fout<<"Numarul starilor dupa minimizare:"<<ps[0].size()<<endl;
    //cout<<ps[0].size();
    //afisare(ps[0]);
    minimizat(ps[0],*this);


}


int main()
{
    DFA d;
    ifstream fin("minimizare.in");
    fin>>d;
    d.elimination();
    d.minimizing();
    fin.close();
    fout.close();
}
