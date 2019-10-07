#include</Users/mudit/stdc++.h>
#include <sys/stat.h>

using namespace std;
typedef long long int ll;
typedef vector<int> vi;

typedef struct node
{
    int value;
    int fi;
}node;

class MinHeap{

    private:
    int size;
    vector<node> arr;
    public:
    MinHeap(int k)
    {
        size=0;
        //arr.resize(k);
    }
    int extractMin()
    {
        size--;
        arr[0]=arr[size];
        heapify(0);

        return 0;    
    }
    void heapify(int node)
    {
        int child_1 = 2*node+1;
        int child_2 = 2*node+2;
        int min_child;
        if(child_1<size && child_2<size){
        
            if(arr[child_1].value<arr[child_2].value){
                min_child=2*node+1;
            }
            else{
                min_child=2*node+2;   
            }
    
            if (arr[min_child].value > 0) { 
                
                if (arr[node].value > arr[min_child].value) { 
                    swap(arr[node], arr[min_child]); 
                
                    heapify(min_child); 
                } 
            }
        } 
    }
    void buildHeap()
    {
        for (int i = size/2; i >= 0; i--) {
        heapify(i);
        } 
    }
    void insert(int x,int fileIndex)
    {
        node newnode;
        newnode.fi=fileIndex;
        newnode.value=x;
        arr.push_back(newnode);
        size++;
    }
    node replaceMin(int newval,int newindex)
    {
        node oldElement=arr[0];
        arr[0].value=newval;
        arr[0].fi=newindex;
        heapify(0);

        return oldElement;
    }
    int getSize()
    {
        
        return arr.size();
    }
    int getMin()
    {
        return arr[0].value;
    }
    node getMinNode()
    {
       
        return arr[0]; 
    }

};

ll getFileSize(string filename)
{
    ll size=0;
 
    FILE *f=fopen(filename.c_str(),"r");
    ll count=0;
    while(!feof(f))
    {
        
        int temp;
        fscanf(f,"%d ",&temp);
        count++; 
    }
    fclose(f);
    return count;
}

vi getKthChunk(FILE *f,int k,int size)
{
    vi chunk(size,0);
    
    int i=0;
    while(size>0){
    //fread(&chunk[i],4,1,f);
    fscanf(f,"%d ",&chunk[i]);
    i++;
    size--;
    }
    return chunk;
}
void mergeKSortedFile(string fname,int k)
{
    FILE *fout=fopen(fname.c_str(),"w");
    FILE* fin[k]; 
    for(int i=0;i<k;i++)
    {   
        string filename=to_string(i); 
        fin[i] = fopen(filename.c_str(), "r"); 
    }  
  

    MinHeap heap(k);

    for(int i=0;i<k;i++)
    { 
       
        int nxtel;
        if (fscanf(fin[i], "%d ", &nxtel) == 1)
        {
            heap.insert(nxtel,i);
          
        } 
        else
        {
            cout<<"error: ";
            perror("fscanf");
            break;
        }
        
    } 

    heap.buildHeap();
  
    int q=0;
    while (heap.getMin()!=INT_MAX)// && q<1000) 
    { 
       // q++;
        node minNode=heap.getMinNode();
        
        fprintf(fout, "%d ", heap.getMin()); 
        int nxtminval;

        if (fscanf(fin[minNode.fi], "%d ", &nxtminval) != 1 ) 
        { 
            nxtminval = INT_MAX; 
        }  
        heap.replaceMin(nxtminval,minNode.fi); 
    }
    
    for(int i=0;i<k;i++)
        fclose(fin[i]); 
  
    fclose(fout);  
    
}

void storeInFiles(vi chunk,int k)
{
    FILE *f=fopen(to_string(k).c_str(),"w");
    for(int i=0;i<chunk.size();i++)
        fprintf(f,"%d ",chunk[i]);
    fclose(f);
}

// ./a.out inputfilename outputfilename
int main(int argc,char* argv[])
{
    ll chunkSize=1000;
    int k;
    //cin>>k;
    MinHeap heap(k);
    string input_file=argv[1];
    string output_file=argv[2];
    //int filesize=1000;
    ll filesize=getFileSize(input_file);
    if(filesize<pow(10,3))
        chunkSize=filesize;
    if(filesize>pow(10,6))
        chunkSize=pow(10,5);
    if(filesize>pow(10,9))
        chunkSize=pow(10,8);

    k=filesize/chunkSize;
    //ll chunkSize=filesize/k;  
    
    vi unsorted_chunk(chunkSize,0);
    vi sorted_chunk(chunkSize,0);
    ll rem=filesize%chunkSize;
    if(rem>0)
        k++;
        
    FILE *f2=fopen(input_file.c_str(),"r");
    for(int i=0;i<k;i++)
    {
        //store in ith file
        if(i<(k-1))
            unsorted_chunk = getKthChunk(f2,i,chunkSize);
        else
           { 
               unsorted_chunk = getKthChunk(f2,i,rem);
               unsorted_chunk.resize(rem);
           }
        
        
        sort(unsorted_chunk.begin(),unsorted_chunk.end());
        
        storeInFiles(unsorted_chunk,i);
    }
    mergeKSortedFile(output_file,k);


    return 0;
}

