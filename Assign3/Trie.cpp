#include</Users/mudit/stdc++.h>

using namespace std;
typedef long long int ll;
typedef vector<ll> vll;

typedef struct Trie{
Trie *child[2];
bool leaf;
} Trie;

Trie *newNode()
{
  Trie *node=new Trie;
  node->child[0]=NULL;
  node->child[1]=NULL;
  node->leaf=false;
  return node;  
}

void insert(Trie *root,ll x)
{
  Trie *node=root;
  ll cnt=0;
  bool index=0;
  for(ll i=43;i>=0;i--)
  {
  
    if(x&((ll)1<<i)){
      index=1;
      cout<<i<<" "<<x<<" "<<endl;
    }
    else 
      index=0;
    
    if(node->child[index]==NULL)
      node->child[index]=newNode();

    node=node->child[index];

  }
  node->leaf=true;
}

Trie* buildTrie(vll arr)
{
  Trie *root=newNode();

  for(ll i=0;i<arr.size();i++)
  {
    insert(root,arr[i]);
  }
  return root;
}

void search_result(Trie *root,ll x)
{  
  ll cnt=0,index,n_index;
  Trie *node=root;
  for(ll i=43;i>=0;i--)
  {
    if(x&((ll)1<<i))
      index=1;
    else
      index=0;
        
    n_index=!index;
    
    if(node->child[n_index]!=NULL && node->leaf==false)
    {
      cnt=cnt+pow(2,i) ;
      node=node->child[n_index];
    } 
    else 
    {
      node=node->child[index];
    }
  }
  cout<<cnt<<endl; 
}

int main()
{
  ll n,q,num;
  cin>>n;
  vll arr(n,0);
  //take input
  for(ll i=0;i<n;i++)
  cin>>arr[i];

  //build trie with this array
  Trie* root=buildTrie(arr);
  
  cin>>q;
  while(q--)
  {
    cin>>num;
    search_result(root,num);
  }
  return 0;
}