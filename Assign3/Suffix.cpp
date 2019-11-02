#include "/Users/mudit/stdc++.h"

using namespace std;
int sufxRank[20][100000];
typedef struct str_s{
    int index;
    int rank1;
    int rank2;
} str_s;

int compare(str_s a, str_s b) 
{ 
return (a.rank1 == b.rank1)? (a.rank2 < b.rank2): 
    (a.rank1 < b.rank1); 
} 

int main()
{
    int n;
    string s;
    cin>>n;
    cin>>s;
    int len=s.size();
    string s1=s;
    s.append(s1);
    vector<str_s> sarr;
    for(int i = 0; i < n; ++i)
        sufxRank[0][i] = s[i];

    for(int i=0;i<len;i++)
    {
        str_s strnode;
        strnode.index=i;
        sarr.push_back(strnode); 
    }
    //int stp=1;
    for(int cnt = 1, stp = 1; cnt < n; cnt *= 2, ++stp) {
        for(int i = 0; i < n; ++i) {
            sarr[i].rank1 = sufxRank[stp - 1][i];
            sarr[i].rank2 = i + cnt < n ? sufxRank[stp - 1][i + cnt] : -1;
            sarr[i].index = i;
        }

        sort(sarr.begin(), sarr.end(), compare);

        sufxRank[stp][sarr[0].index]=0;
        int cur=0;
        for(int i=1;i<n;++i) {
            if(sarr[i - 1].rank1 != sarr[i].rank1 || sarr[i - 1].rank2 != sarr[i].rank2)
                cur++;

            sufxRank[stp][sarr[i].index] = cur;
        }
        stp++;
    }
 
   for(int i=0;i<sarr.size();i++)
        cout<<sarr[i].index<<" "<<sarr[i].rank2<<endl;
    return 0;
}