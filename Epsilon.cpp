#include<bits/stdc++.h>
#define N 100
#define M 27
using namespace std;

int main()
{
    int n,m,a,b,c,nr,nrf;
    ifstream fin("epsilon.in");
    ofstream fout("epsilon.out");
    fin>>n>>m>>nr;
    unordered_set<int> inchidere[n];
    vector<int> v[n][m];
    unordered_set<int> sol[n][m];
    int inc;
    bool sfarsit[n]={0},inceput[n]={0};

    for(int i=0;i<nr;++i)
    {
        fin>>a>>b>>c;
        //matricea tranzitiilor
        //din starea a cu b ajung in starea c
        //in fisierul de citire am b ca un numar
        //daca b este egal cu 0, am o tranzitie lambda
        v[a][b].push_back(c);
        if(b)
            sol[a][b].insert(c);
    }

    //citesc starea initiala
    fin>>inc;
    inceput[inc]=1;
    //citesc starile finale
    fin>>nrf;
    for(int i=0;i<nrf;++i)
    {
        int j;
        fin>>j;
        sfarsit[j]=1;

    }

    //determin inchiderea la epsilon pentru fiecare stare
    for(int i=0;i<n;++i)
    {
        queue<int> q;
        bool viz[n];
        memset(viz,0,sizeof(viz));
        //viz-ul il folosesc pentru cazul in care ar aparea un ciclu de lambda
        q.push(i);
        viz[i]=1;
        inchidere[i].insert(i);
        while(!q.empty())
        {
            int curr=q.front();
            q.pop();
            for(int j=0;j<v[curr][0].size();++j)
            {
                int es=v[curr][0][j];
                if(!viz[es]){
                    viz[es]=1;
                    q.push(es);
                    inchidere[i].insert(es);
                }

            }
        }

    }

    /*for(int i=0;i<n;i++)
    {
        cout<<"inchiderea-epsilon a lui "<<i<<": ";
        for(int j:inchidere[i])
            cout<<j<<' ';
        cout<<endl;
    }*/

    for(int i=0;i<n;++i)
    {
        for(int it:inchidere[i])
        if(it!=i)
        {
            for(int j=1;j<m;j++)
        {
            //ma duc pe toate tranzitiile din v2 si le copiez in v1
            for(int k=0;k<v[it][j].size();++k)
            {
                int nod=v[it][j][k];
                //cout<<i<<' '<<nod<<endl;
                for(auto it2:inchidere[nod])
                {
                    sol[i][j].insert(it2);
                }

            }

        }
            if(inceput[i])
                inceput[it]=1;
            if(sfarsit[it])
                sfarsit[i]=1;
        }
    }

    //afisez tranzitiile

    for(int i=0;i<n;i++)
    {   //fout<<i<<": ";
        for(int j=0;j<m;j++)
        {   //fout<<j<<": ";
            for(int k:sol[i][j])
                fout<<i<<' '<<j<<' '<<k<<'\n';
        }
    }

    //afisez starile initiale
    for(int i=0;i<n;i++)
        if(inceput[i])
        fout<<i<<' ';
    fout<<endl;

    //afisez starile finale
    for(int i=0;i<n;i++)
        if(sfarsit[i])
        fout<<i<<' ';
    fout<<endl;

    fin.close();
}
