#include "/Users/mudit/stdc++.h"
#include <chrono>

using namespace std;
typedef vector<int> vi;


int partition(vi &arr,int low,int high)
{
    
    
    int pivot=high; 
    int small=low;
    cout<<"piv:"<<pivot<<endl;
    for(int i=low;i<high;i++)
    {
        if((arr[i]<=arr[pivot]))
        {
           
            swap(arr[i],arr[small]);
            small++;
        }
       
    }
    swap(arr[small],arr[pivot]);

    return small;
}

int findNthSmallest(vi &arr,int k,int low,int high)
{
    int res=INT_MAX;
    if(k>=0 && k<=high-low){
        int pivot=rand()%(high-low+1) + low;   
        swap(arr[high],arr[pivot]);
        int p=partition(arr,low,high);
        if(p-low==k)
            return arr[p];
        else
        {
            if(p-low<=k)
            {
                res= findNthSmallest(arr,k-p+low-1,p+1,high);
            }
            else
            {
                res= findNthSmallest(arr,k,low,p-1);
            }       
        }
    }
   
    
    return res;
}

int main()
{
    int n,k;
    time_t now;
    time_t then;
    double sec=0.0;
    cout<<"Enter the Number of Integers:";
    cin>>n;
    cout<<"Enter the value of k:";
    cin>>k;
    vi arr(n,0);
    vi arr2(n,0);
    srand(time(0));
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    arr2=arr;
    
    auto start = chrono::high_resolution_clock::now();   
    int res= findNthSmallest(arr,k-1,0,n-1);
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 

    

    //sec=difftime(then,now);
    cout<<"After my sort: "<<res<<endl;
    cout <<"time= "<< duration.count() << endl; 

    start = chrono::high_resolution_clock::now();
    nth_element(&arr2[0], &arr2[0] + k-1, &arr2[0] + n-1);
    stop = chrono::high_resolution_clock::now();

    cout<<"After standard sort: "<<arr[k-1]<<endl;
    duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    cout <<"time= "<< duration.count() << endl;
    return 0;
}
