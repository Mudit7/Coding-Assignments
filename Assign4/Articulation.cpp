#include "/Users/mudit/stdc++.h"

using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int> > vvi;

vvi adj;
vb visited,res;
vi dfsTreeParent,d_time,low;
int curtime;

void findAP(int x)
{
    curtime++;
    visited[x]=1;
    int cnt=0;  //cnt of children
    d_time[x]=curtime;
    low[x]=curtime;
    for(auto i:adj[x])
    {
        if(visited[i]==0)
        {
            dfsTreeParent[i]=x;
            cnt++;
            findAP(i);
            low[x]=min(low[i],low[x]);
            if(dfsTreeParent[i]==-1 && cnt>=2)
            {
                res[x]=1;
                continue;
            }
            else
            {
                if (dfsTreeParent[x]!=-1 && low[i] >= d_time[x])
                {
                    res[x]=1;
                    
                }
            }
            
        }
        //back edge case 1
        else if(dfsTreeParent[x]!=i)
        {
            low[x]=min(low[x],d_time[i]);
        }
    }

}


int main()
{
    int n,m,edge,x,y;
    curtime=0;
    cout<<"Enter n(vertices)\n";
    cin>>n;
    visited.resize(n,0);
    res.resize(n,0);
    d_time.resize(n,0);
    low.resize(n,0);
    dfsTreeParent.resize(n,-1);
    adj.resize(n);
    cout<<"Enter m(edges)\n";
    cin>>m;
    cout<<"Enter edges 1 by 1\n";
    for(int i=0;i<m;i++)
    {
        cin>>x>>y;
        if(x<n && y<n){
        adj[x].push_back(y);
        adj[y].push_back(x);
        }
        else{
            cout<<"Invalid\n";
            i--;
        }
    }

    for(int x=0;x<n;x++)
    {
        if(visited[x]==0)
        {
            findAP(x);
        }
    }

    for(int i=0;i<n;i++)
    {
        if(res[i])
        {
            cout<<"Articulation Point found at "<<i<<" node"<<endl;
        }
    }
    cout<<endl;
    return 0;
}