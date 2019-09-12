#include<iostream>
#include<vector>
#include<string>

using namespace std;
typedef vector<int> vi;

class BigInt{

    public:
    vi b;

    //utils
    void set_with_vect(vi v)
    {
        b.resize(v.size());
        for(int i=0;i<v.size();i++)
        {
            b[i]=v[i];
        }
    }
    
    void set_with_str(string s) 
    {
        for(int i=0;i<s.length();i++)
        {
            if((s[i]<'0')|(s[i]>'9')){
                perror("Not a number");
                exit(-1);
            }
        }
        b.resize(s.length());
        for(int i=b.size()-1;i>=0;i--)
        {
            b[i]=s[b.size()-1-i]-'0';
        }
    }
    vi get_vect()
    {
        return b;
    }
    string get_str()
    {
        string s;
        for(int i=b.size()-1;i>=0;i--)
        {
            s.push_back(b[i]+'0');
        }
        return s;
    }
    void print_vect()
    {
        for(int i=b.size()-1;i>=0;i--)
        {
            cout<<b[i];
        }
        cout<<"\n";
    }
    void trunc()
    {
        int i=b.size()-1;
        while(b[i]==0)
        {
            b.erase(b.begin()+i);
            i--;
        }
        if(b.size()==0)
        b.push_back(0);
    }

    // arithmetic ops

    bool equals(BigInt C)
    {
        C.trunc();
        vi C_v=C.get_vect();
        
        if(b.size()!=C_v.size())
            return false;
        for(int i=0;i<b.size();i++)
        {
            if(b[i]!=C_v[i]) return false;
        }
        return true;
    }
    bool neqz()
    {
        cout<<"\t"<<b.size()<<"\t";
        for(int i=0;i<b.size();i++)
        {
            
            if(b[i]!=0) 
            return true;
        }
        return false;
    }
    BigInt add(BigInt C)
    {
        BigInt A;
        vi C_v=C.get_vect();
        int len_C=C_v.size();
        int len_B=b.size();
        int big_len= (len_C>len_B)?len_C:len_B;
        big_len++;
        vi res_v(big_len,0);
        C_v.resize(big_len,0);
        b.resize(big_len,0);
        for(int i=0;i<big_len;i++)
        {
            if((C_v[i]+b[i])>9){
                res_v[i]+= (C_v[i]+b[i]-10);   //carry
                res_v[i+1]++;
            }
            else
            res_v[i]+=C_v[i]+b[i];
        }
        A.set_with_vect(res_v);
        return A;
    }
    BigInt sub(BigInt C)
    {
        BigInt A;
        vi C_v=C.get_vect();
        vi B_v=b;
        int len_C=C_v.size();
        int len_B=b.size();
        int big_len= (len_C>len_B)?len_C:len_B;
        vi res_v(big_len,0);
        C_v.resize(big_len,0);
        B_v.resize(big_len,0);
        for(int i=0;i<big_len;i++)
        {   if(B_v[i]==-1)
            {
                B_v[i]=9;
                B_v[i+1]--;
            }
            if((B_v[i]-C_v[i])<0){
                res_v[i] += (B_v[i]-C_v[i]+10);   //carry
                B_v[i+1]--;
            }
            else
            res_v[i] = B_v[i] - C_v[i];
        }
    
        A.set_with_vect(res_v);
        A.trunc();
        
        return A;
    }
    BigInt mul(BigInt C)
    {
        BigInt A;
        vi C_v=C.get_vect();
        vi B_v=b;
        int len_C=C_v.size();
        int len_B=B_v.size();
        vi temp;
        BigInt temp_b;
        if(len_B>len_C)
        {
            B_v.swap(C_v);
            swap(len_B,len_C);
        }
        int carry=0;
        for(int i=0;i<len_B;i++)
        {
            temp=C_v;
            vector<int>::iterator it=temp.begin();
            for(int k=0;k<i;k++)
                it=temp.insert(it,0);

            carry=0;
            for(int j=i;j<temp.size();j++)
            {
                temp[j]=temp[j]*B_v[i]+carry;
                if(temp[j]>9){
                    carry=temp[j]/10;
                    temp[j]=temp[j]-carry*10;
                }              
                else {  carry=0;  }
            }
            if(carry)
            {
                temp.push_back(carry);
            }

            temp_b.set_with_vect(temp);
            
            A=A.add(temp_b);
        }
        A.trunc();
        return A;
    }

    BigInt exp(BigInt C)
    {
        BigInt A;
        vi t;
        t.push_back(1);
        A.set_with_vect(t);
        vi C_v=C.get_vect();
        vi B_v=b;
        BigInt B;
        B.set_with_vect(B_v);
        while(C_v.size()>0)
        {
            if(C_v[0]%2)
                A=A.mul(B);
            B=B.mul(B);
            C_v[0]=C_v[0]/2;
            if(C_v[0]==0)
            C_v.erase(C_v.begin());
        }
        A.trunc();
        return A;
    }

    BigInt max(BigInt C)
    {
        C.trunc();
        vi C_v=C.get_vect();
        if(b.size()>C_v.size()) return *this;
        else if(b.size()<C_v.size()) return C;
        else{
            int i=b.size()-1;
            
            while(b[i]==C_v[i])
            {
                i--;
            }
            if(b[i]>C_v[i])
            return *this;
            else
            return C;
        }
    }
    BigInt min(BigInt C)
    {
        C.trunc();
        vi C_v=C.get_vect();
        if(b.size()<C_v.size()) return *this;
        else if(b.size()>C_v.size()) return C;
        else{
            int i=b.size()-1;
            
            while(b[i]==C_v[i])
            {
                i--;
            }
            if(b[i]<C_v[i])
            return *this;
            else
            return C;
        }
    }

    BigInt gcd(BigInt C)
    {
        BigInt A;
        BigInt B;
        B.set_with_vect(b);
        A=B.max(C);
        B=B.min(C);

        while(!A.equals(B))
        {
            BigInt temp=B.max(A);
            B=B.min(A);
            A=temp.sub(B);
        }
        A.trunc();
        return A;
    }

    BigInt facto()
    {
        BigInt A;
        BigInt B;
        BigInt one;
        one.set_with_str("1");
        BigInt zero;
        zero.set_with_str("0");

        B.set_with_vect(b);
        B.trunc();
        A.set_with_str("1");
        while(B.neqz())
        {
            A=A.mul(B);
            B=B.sub(one);
        }
        return A;
    }

};