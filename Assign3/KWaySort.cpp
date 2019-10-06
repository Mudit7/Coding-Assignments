#include</Users/mudit/stdc++.h>

using namespace std;
typedef long long int ll;
typedef vector<int> vi;

class MinHeap{

    private:
    int size;
    vector<int> arr;
    public:
    MinHeap(int k)
    {
        size=k;
        arr.resize(k);
    }
    int extractMin()
    {
        return 0;    
    }

    void heapify(int node)
    {

    }
    void insert(int x)
    {
        arr.push_back(x);
        size++;
    }
    int replaceMin(int newval)
    {
        int minElement=arr[0];
        arr[0]=newval;
        heapify(0);

        return minElement;
    }
    int getSize()
    {
        return size;
    }

};

ll getFileSize(string filename)
{
    ll size=0;

    return size;
}

vi getKthChunk(string fname,int k,int size)
{
    vi chunk(size,0);
    int offset=k*size;
    //fseek(offset) then read then rewind

    return chunk;
}
void mergeKSortedFile(string fname,int k,int chunkSize)
{
    //perform k way sort and store it in a new output file
    
}

void storeInFiles(vi chunk,int i)
{

}

int main(int argc,char* argv[])
{
    
    int k=5;
    //cin>>k;
    MinHeap heap(k);
    string input_file=argv[1];
    string output_file=argv[2];
    int filesize=1000;
    ll chunkSize=getFileSize(input_file)/k;    
    vi unsorted_chunk(chunkSize,0);
    vi sorted_chunk(chunkSize,0);
    //create a new file to store k number of sorted chunks
    //fread data=chunksize
    FILE *fin=fopen(argv[1],"r");
    FILE *fout=fopen(argv[2],"w");
    //FILE f2=fopen("temp_output_file_name","rb");
    for(int i=0;i<k;i++)
    {
        //store in ith file
        unsorted_chunk = getKthChunk(input_file,i,chunkSize);
        sort(unsorted_chunk.begin(),unsorted_chunk.end()); 
        sorted_chunk=unsorted_chunk; // and stores in sorted_chunk
        storeInFiles(sorted_chunk,i);
    }
    mergeKSortedFile(output_file,k,chunkSize);

    return 0;
}

