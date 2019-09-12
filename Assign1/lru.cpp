#include<iostream>
#include<vector>
#include<string>
#include <type_traits>


using namespace std;

using namespace std;
template <typename T>
class Deque{
    T *q;
    T *def;
    int qsize;
    int capacity;
    int fr;
    int rear;
    
    public:
    Deque(){
        q=0;
        qsize=0;
        capacity=0;
        fr=-1;
        rear=0;
        def=new T[1];
    }
    Deque(int n,T x){
        def=new T[1];
        qsize=n;
        capacity=n;
        rear=0;
        fr=0;
        q= new T[n];
        for(int i=0;i<n;i++)
        q[i]=x;
    }
    void init(int n,T x)
    {
        qsize=0;
        capacity=n;
        rear=0;
        fr=-1;
        q= new T[n];
        for(int i=0;i<n;i++)
        {
            q[i]=x;
        }
    }
    void print_q()
    {
        cout<<"--* ";
        if(fr==-1) return;
        if(fr<rear)
        for(int i=fr;i<rear;i++)
        {
            cout<<q[i]<<" ";
        }
        else
        {
            for(int i=fr;i<capacity;i++)
            {
                cout<<q[i]<<" ";
            }
            for(int i=0;i<rear;i++)
            {
                cout<<q[i]<<" ";
            }
        }
        cout<<" *--";
        cout<<"\n";
    }
    void print_plain()
    {
        for(int i=0;i<capacity;i++)
        cout<<q[i]<<" ";
    }
    void print_meta()
    {
        cout<<"Capacity: "<<capacity<<endl;
        cout<<"Size: "<<qsize<<endl;
        cout<<"Front: "<<fr<<endl;
        cout<<"Rear: "<<rear<<endl;
    }
    void alloc_mem(int ncap)
    {
        this->rearrange();
        T *newq=new T[ncap];
        if(ncap<=qsize)        //if shrinking
        {
            qsize=ncap;
            rear=0;
        }
        for(int i=0;i<qsize;i++)
        {
            newq[i]=q[i];
        }
        delete[] q;
        q=newq;
        this->capacity=ncap;
        rear=qsize;
    }
    void rearrange()
    {
        //cout<<fr<<" and "<<rear<<"\n";
        if(fr==-1) return;
        if(rear<=fr)
        {
            //cout<<"rearranging"<<"\n";
        T *nq=new T[capacity];
        for(int i=fr;i<capacity;i++)
        {
            nq[i-fr]=q[i];
        }
        for(int i=0;i<rear;i++)
        {
            nq[capacity-fr+i]=q[i];
        }
        delete[] q;
        q=nq; 
        
        }
        if(fr>0)
        {
            for(int i=fr;i<rear;i++)
            {
                q[i-fr]=q[i];
            }
        }
        fr=0;
        rear=qsize%capacity;
        
    }
    void push_back(T x)
    {
        if(fr==-1) fr=0;
        if(capacity==0)
        {
            alloc_mem(8);
        }
        
        if(rear==capacity)
        rear=0;
        
        if((qsize+1) > capacity)
        {
            this->alloc_mem(2*capacity);
            
          //  this->print_plain();
        }
        qsize++;
        q[rear++]=x;
        if(rear==capacity) rear=0;
    }
    
    void push_front(T x)
    {
        qsize++;
        if(capacity==0)
        {
            alloc_mem(8);
            fr=0; //non-empty queue
        }
        if(qsize > capacity)
        {
            this->alloc_mem(2*capacity);
        }
        if(fr==0)
        fr=capacity;

        q[--fr]=x;          
        
    }  

    void pop_front()
    {
        
        if(qsize==0)
        {
            //cout<<"Queue is EMPTY!";
            return;
        }
        qsize--;
        fr++;
        if(fr>=capacity)
        fr=0;
    }

    void pop_back()
    {
        
        if(qsize==0)
        {
           // cout<<"Queue is EMPTY!";
            return;
        }
        qsize--;
        rear--;
        if(rear<0)
        {
            rear=capacity-1;
        }   
    }
    T& front()
    {
        return q[fr];        //better not be -1!
    }
    T& back()
    {
        if(rear==0) return q[qsize-1];
        return q[rear-1];
    }
    int size()
    {
        return qsize;
    }
    void resize(int nsize)
    {
        alloc_mem(nsize);
        
        for(int i=qsize;i<nsize;i++)    
        q[i]= *def; 
        qsize=nsize;
        rear=0; 
    }
    T& operator[](int pos)
    {
        if((pos+fr)>=capacity)
        {
            int x=pos+fr-capacity;
            return q[x];
        }

     return q[pos+fr];
    }
    void insert(int pos,T data)
    {
        qsize++;
        this->rearrange(); 
        if(pos>qsize-2) return;
        
        if(qsize>capacity)
        {
            this->alloc_mem(capacity*2);
            
        }
        for(int i=qsize-1;i>pos;i--)
            {
                q[i]=q[i-1];
            }
        q[pos]=data;
        rear++;
        if(rear>=capacity) rear=0;
    }
    void erase(int pos)
    {       
        this->rearrange();
        if((qsize<=0)||(pos>=qsize)) return;

        for(int i=pos+1;i<qsize;i++)
        {
            q[i-1]=q[i];
        }
        qsize--;
        if(qsize==0) fr=-1;

        rear--;
        if(rear<0)
        {
            rear=capacity-1;
        } 
    }
    void clear()
    {
        delete[] q;
        q=0; 
        fr=-1;
        rear=0;
        qsize=0;
        capacity=0;
    }
};


template <class Tk,class Tv>

class LRU{
    int size;
    Deque< pair<Tk,Tv> > Dq;
    
    public:
    int pf;

    LRU(int n){
        size=n;
        pair<Tk,Tv> pair1;
        Dq.init(n,pair1);
        pf=0;
    }
    void printall()
    {
        for(int i=0;i<size;i++)
        {
            cout<<"Key "<<i<<" = "<<Dq[i].first<<"\t";
            cout<<"Value "<<i<<" = "<<Dq[i].second<<"\n";
        }
    }
    Tv* get(Tk key)
    {
        for(int i=0;i<size;i++)
        {
            if(Dq[i].first==key)
            {   
                pair<Tk,Tv> entry;
                entry.first=key;
                entry.second=Dq[i].second;
                Dq.erase(i);
                Dq.push_back(entry);
                return &Dq.back().second;
            }
        }
        //pf++;
        return NULL;
    }
    void set(Tk key,Tv value)
    {
        pair<Tk,Tv> entry;
        entry.first=key;
        entry.second=value;
        if(this->get(key)==NULL){
            if(Dq.size()==size)
            Dq.pop_front();

            pf++;
        }
        else{
            //logic to erase that element
            int i;
            for(i=0;i<Dq.size();i++)
            {  // cout<<"i is "<<i<<" "<<size<<endl;
                if(Dq[i].first==key)
                {
                    break;
                }
            }
            Dq.erase(i);
            // cout<<"After erase: ";
            // Dq.print_meta();            
        }
        //Dq.print_meta();
        Dq.push_back(entry);
        // cout<<"After Push: ";
        // Dq.print_meta();
    }
    
};


int main()
{ 
    int size,q;
    char ch;
    cin>>size;
    cin>>q;
    float k;
    string v;
    LRU<float,string> cache(size);
    while(q--)
    {
        cin>>ch;
        if(ch=='S')
        {
            cin>>k>>v;
            cache.set(k,v);
        }
        else if(ch=='G'){
            cin>>k;
            if(cache.get(k))
            {            
                cout<< *(cache.get(k))<<endl;
            }
            else
            {   
                cout<<-1<<endl; //doesn't exist
            }           
        }
        else if(ch=='P')
        {
            cache.printall();
        }
    }
    //cout<<"Page faults: "<<cache.pf<<endl;  
    return 0;
}