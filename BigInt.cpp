#include<iostream>
#include<vector>
#include<string>
#include "BigInt.h"
using namespace std;
typedef long long int ll; 
typedef vector<int> vi;

int main()
{
   ll q;
   int k=0;
   cin>>q;
   BigInt res;
   string a,b;
   while(q--)
   {
       cin>>k;
       switch(k)
       {
           case 1:{
               cin>>a>>b;
               BigInt A,B;
               A.set_with_str(a);
               B.set_with_str(b);
               res=A.exp(B);
               res.print_vect();
               break;
           }
           case 2:{
               cin>>a>>b;
               BigInt A,B;
               A.set_with_str(a);
               B.set_with_str(b);
               res=A.gcd(B);
               res.print_vect();
               break;
           }
           case 3:{
               cin>>a;
               BigInt A;
               A.set_with_str(a);
               res=A.facto();
               res.print_vect();
               break;
           }
           default:
           cout<<"INVALID";
       }
   }
    return 0;
}