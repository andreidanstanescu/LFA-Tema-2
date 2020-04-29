#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m,a,b,c,nr,nrf;
    ifstream fin("nfa.in");
    ofstream fout("nfa.out");
    fin>>n>>m>>nr;
    vector<int> v[n][m];
    int dfa[n][m]; //matricea de adiacenta pentru dfa-ul rezultat
    int inc;
    bool sfarsit[n]={0};
    for(int i=0;i<nr;++i)
    {
        fin>>a>>b>>c;
        //matricea tranzitiilor
        //din starea a cu b ajung in starea c
        //in fisierul de citire am b ca un numar
        v[a][b].push_back(c);
    }

    //citesc starea initiala
    fin>>inc;
    //citesc starile finale
    fin>>nrf;
    for(int i=0;i<nrf;++i)
    {
        int j;
        fin>>j;
        sfarsit[j]=1;

    }
    queue<int> q;
    q.push(0);

    vector< set<int> > sol;
    int ns=1;  //numar stari din dfa
    set<int> s;
    s.insert(inc);
    sol.push_back(s);

    while(!q.empty())
    {
        int nod=q.front();
        q.pop();

        for(int i=0;i<m;i++)
        {
            set<int> sc; //starile curente, ce trebuie adaugate in coada
            for(int j:sol[nod])
                  for(int k:v[j][i])
                {
                    sc.insert(k);
                    //cout<<k<<' ';
                }
        //verific daca a mai aparut setul curent
        //for(int j:sc)
            //cout<<j<<' ';
        //cout<<endl;
        bool gasit=0;
        int j;
        for(j=0;j<ns && !gasit;++j)
            if(sol[j]==sc)
                {
                    gasit=1;
                    //break;
                }
        //cout<<(sol[0]==sc)<<endl;
        if(!gasit)
        {
            sol.push_back(sc);
            q.push(ns);
            dfa[nod][i]=ns;
            ++ns;
        }
        else
            dfa[nod][i]=j-1;

        }

    }

    fout<<"Numarul de stari:"<<ns<<endl;
    fout<<"Starile sunt:\n";
    for(int i=0;i<ns;i++)
    {   fout<<'{';
        for(int j:sol[i])
    fout<<j<<' ';
    fout<<'}'<<endl;
    }

    fout<<"Matricea de adiacenta pentru DFA:\n";
    for(int i=0; i<ns; i++) {
			for(int j=0; j<m; j++) {
                fout << "{";
                for(int k:sol[i])
                        fout << k;
                fout << "} ";
				fout<<j<<" {";
				for(int k:sol[dfa[i][j]]) {
					fout<<k;
				}
				fout<<"}"<<endl;
			}
		}
    fout<<"Starile finale sunt:\n";
    for(int i=0;i<ns;i++)
    {
        bool ok=0;
        for(int j:sol[i])
            if(sfarsit[j])
        {
            ok=1;
            break;
        }
        if(ok)
        {
            fout<<"{";
            for(int j:sol[i])
                fout<<j<<' ';
            fout<<"}";
            fout<<endl;
        }
    }
    /*for(int i=0;i<ns;i++)
        {
            for(int j=0;j<m;j++)
            {
                //set<int> s1(sol[i]);
                if(dfa[i][j])
                {cout<<i<<' '<<j<<' '<<dfa[i][j]<<endl;
                //s1.insert(dfa[i][j]);
                }
            for(int k=0;k<sol[i].size();++k)
                for(int t:v[k][j])
                    if(!s1.count(t))
                {cout<<i<<' '<<j<<' '<<t<<endl;
                s1.insert(t);
                }
            }

        }*/
    fin.close();
    fout.close();

}
