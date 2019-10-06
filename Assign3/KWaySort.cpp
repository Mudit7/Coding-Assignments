#include</Users/mudit/stdc++.h>
#include <sys/stat.h>

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
    struct stat stat_buff;
    int rc = stat(filename.c_str(), &stat_buff);
    return rc == 0 ? stat_buff.st_size : -1;
}

vi getKthChunk(string fname,int k,int size)
{
    vi chunk(size,0);
    int offset=k*size;
    //fseek(offset) then read then rewind
    FILE *f=fopen(fname.c_str(),"r");
    int i=0;
    while(i<size){
    fread(&chunk[i],4,1,f);
    i++;
    }
    fclose(f);
    return chunk;
}
void mergeKSortedFile(string fname,int k,int chunkSize)
{
    //perform k way sort and store it in a new output file
    
}

void storeInFiles(vi chunk,int k)
{
    FILE *f=fopen(to_string(k).c_str(),"w");
    for(int i=0;i<chunk.size();i++)
    fprintf(f,"%d",chunk[i]);
    fclose(f);
}

int main(int argc,char* argv[])
{
    
    int k=5;
    //cin>>k;
    MinHeap heap(k);
    string input_file=argv[1];
    string output_file=argv[2];
    //int filesize=1000;
    ll chunkSize=getFileSize(input_file)/k;    
    vi unsorted_chunk(chunkSize,0);
    vi sorted_chunk(chunkSize,0);
    //create a new file to store k number of sorted chunks
    //fread data=chunksize
    //FILE f2=fopen("temp_output_file_name","rb");
    //cout<<chunkSize;
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

