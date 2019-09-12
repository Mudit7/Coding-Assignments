#include "/Users/mudit/stdc++.h"
using namespace std; 

typedef struct node  
{  
    int key; 
    int height;  
    int size;
    node *left;  
    node *right;  
} node;
class AvlTree{

    node *root;
    int size;

    // int calc_size(node *nd)
    // {
    //     if(!nd)
    //         return 0;
    //     else{
    //         nd->size= 1 + calc_size(nd->left) + calc_size(nd->right);
    //         return nd->size;
    //     }
    // }

    void setHeight(node* &nd)  
    {  
        int lheight=getHeight(nd->left);
        int rheight=getHeight(nd->right);
        nd->height= (lheight>rheight)?lheight:rheight;
        nd->height++; //for counting the root itself
        //cout<<endl<<"height::"<<nd->key<<"->"<<nd->height<<endl;
        if(nd->key==66 && nd->height==4) 
        {
            //preOrder(nd->right);
            //cout<<"really:"<<getHeight(nd->right->right)<<endl;
        }
    }
    int getHeight(node *nd)  
    {  
        if (nd == NULL)
            return 0;  
        return nd->height;  
    }
    node *rightRotate(node *grand_parent)  
    {   
        node *child=NULL;
        node *parent=NULL;
        if(grand_parent->left)
            parent=grand_parent->left;
        if(parent)
        {
            child=parent->right;

            //rotate right   
            parent->right=grand_parent;
            grand_parent->left=child;

            // Update heights  
            setHeight(grand_parent); 
            setHeight(parent); 
            grand_parent->size-=parent->size;
            parent->size+=grand_parent->size;
        }
            
        else
        {
            return grand_parent;
        }
        
        // Return new root  
        return parent;  
    }

    node *leftRotate(node *grand_parent)  
    {  
        node *child=NULL;
        node *parent=NULL;

        if(grand_parent->right)
            parent=grand_parent->right;
        if(parent)
        {
            child=parent->left;

            //rotate right   
            parent->left=grand_parent;
            grand_parent->right=child;

            // Update heights  
            setHeight(grand_parent); 
            setHeight(parent); 

            //update sizes

            grand_parent->size-=parent->size;
            parent->size+=grand_parent->size;


        }
        else
        {
            return grand_parent;
        }
        // Return new root  
        return parent;  
    }
    node* newnode(int key)  
    {  
        node* node = new struct node(); 
        node->key = key;  
        node->left = NULL;  
        node->right = NULL;  
        node->height = 1;
        node->size=1;
        return node;
    }
    int getBalance(node *nd)  
    {
        if (!nd)
            return 0;
        if(nd->key==11){
            //cout<<"left:"<<getHeight(nd->left)<<"right:"<<getHeight(nd->right)<<endl;
            //cout<<"\n";
            //preOrder(nd->right);
            //cout<<endl;
        }
        int bal=getHeight(nd->left);
        bal-=getHeight(nd->right);
        return bal;  
    }
    node* balanceAtNode(node *nd,int key)
    {
        // check if its balanced
        int balance = getBalance(nd);  
        //if(key==32) cout<<"nd->key,balance:"<<nd->key<<","<<balance<<endl;
        // If not then 4 cases
        // L-L Case  
        if (balance>1 && nd->left){
            //L-L
            if(key<nd->left->key)
            {
                return rightRotate(nd);
            }
            //L-R
            if (key>nd->left->key)
            {  
                //covert to L-L
                nd->left = leftRotate(nd->left);
                return rightRotate(nd);  
            }
        }
        
        else if(balance<-1 && nd->right){ 
            if(key>nd->right->key)
            {
                return leftRotate(nd);  
            }
            if(key<nd->right->key)
            {
                //convert to R-R
                nd->right = rightRotate(nd->right);  

                return leftRotate(nd);  
            }
        }
        else{
            //the tree is already balanced
            return nd;
        }

        return nd;
    }

    node* get_inorder_succ(node *nd)
    {
        node* temp=nd;

        if(nd==NULL) return nd;
        
        else if(nd->right==NULL) return nd;

        else if(nd->right->left==NULL) return nd->right;

        temp=temp->right;

        while(temp->left!=NULL)
        temp=temp->left;

        return temp;        
    }

    node* insert_rec(node* nd, int key)  
    {  
        //if tree is empty on nd
        if (nd == NULL) {
            size++;
            return newnode(key);
        }
     
        else if (key < nd->key)  
        {
            nd->left = insert_rec(nd->left, key);
            nd->size++;
        }
              
        else { 
            nd->right = insert_rec(nd->right, key);  
            nd->size++;
        }
        // update height of this node 
        setHeight(nd);
        //perform balancing
        if(nd==NULL) cout<<"whaaaa...";
        else
        nd=balanceAtNode(nd,key);
        
        return nd;
    }

    node* delete_rec(node* nd,int key)
    {
        if(nd==NULL)
        return nd;

        else if(nd->key > key)
        nd->left= delete_rec(nd->left,key);

        else if(nd->key < key)
        nd->right= delete_rec(nd->right,key);

        else{// if equal
            //no child case
            if((nd->left==NULL)&&(nd->right==NULL))
            {
                free(nd);
                nd=NULL;
                //calc_size(nd);
                return NULL;
            }
            //if only right child exists
            else if(nd->left==NULL)
            {
                node *temp=nd->right;
                *nd=*temp;
                free(temp);
            }
            //if only left child exists
            else if(nd->right==NULL)
            {
                node *temp=nd->left;
                *nd=*temp;
                free(temp);
            }
            else{//one with 2 child (tough guy)
                //get inorder successor
                node* temp=get_inorder_succ(nd);
                if(temp){
                nd->key= temp->key;  
                nd->right= delete_rec(nd->right,temp->key);
                }
                
            }

        }
        if(nd==NULL) return nd;
        //update heights
        setHeight(nd);
        //perform balancing
        nd=balanceAtNode(nd,key); 
        //calc_size(nd);
        return nd;
    }

    int find_k (node *nd,int nth_lar)
    {    
        //if its either a leaf or only with a left child and we are looking for largest in the (sub)tree
        //if(nd==NULL)  cout<<"GAL "<<nth_lar<<endl;
        if((nd)&&(nd->right==NULL)&&(nth_lar==1))
            return nd->key;

        //go till the point where it still remains the nth largest element
        while((nd->right)&&(nd->right->size>=nth_lar))
        {       
            nd=nd->right;
            if((nd->right==NULL)&&(nth_lar==1))
                return nd->key;
        }
        //if nd is the one!
        if(( nd->right)&&(nd->right->size==(nth_lar-1)))
                return nd->key;

        int rsize= (nd->right)?nd->right->size:0;
    
        return find_k(nd->left,nth_lar-rsize-1);
    }

    void preOrder(node *nd)  
    {  
        if(nd != NULL)  
        {  
            cout << nd->size << " ";  
            preOrder(nd->left);  
            preOrder(nd->right);  
        }  
    }

    //mode = 0 for -ve difference, mode = 1 for positive
    int findMinDiff(int key,int mode) 
    {   
        node *temp=root;
        int minDiff;
        switch(mode)
        {
            case 0:
            {
                minDiff=root->key-key;
                break;
            }
            case 1:
            {
                minDiff=__INT_MAX__;
                break;
            }
            case -1:
            {
                minDiff=-1*__INT_MAX__;
            }
        }
        while(temp!=NULL)
        {
            if(temp->left && key<temp->key)
            {
                temp=temp->left;
            }   
            else if(temp->right && key>temp->key)
            {
                temp=temp->right;
            }
            
            else if(key==temp->key){
                return 0;
                break;
            }
            else{ //leaf
                if(abs(minDiff)>abs(temp->key - key))
                    minDiff=temp->key-key;

                return minDiff;
            }
            if(mode==0){
                if(abs(minDiff)>abs(temp->key-key))
                minDiff=temp->key - key;
                if((abs(minDiff)==abs(temp->key-key)) && (temp->key<key))
                {
                    minDiff=temp->key - key;
                }
            }
            if((mode==-1)&&(temp->key<=key)) //for upper bound
            {
                if(temp->key - key > minDiff)
                minDiff=temp->key-key;
            }
            if((mode==1)&&(temp->key >= key)) //for lower bound
            {
                if((temp->key - key)<minDiff){
                minDiff=temp->key-key;
                }
            }
        }
        return minDiff;
    }
    int countZeroToN(node* nd,int key)
    {
        if(nd==NULL) return 0;
        else if(nd->key > key)
            return countZeroToN(nd->left,key);
        else if(nd->key <key)
        {
            if(nd->left)
            return 1 + nd->left->size +countZeroToN(nd->right,key);
            else
            return 1 +countZeroToN(nd->right,key);
        }
            
        else{   //found element
            if(nd->left)
                return 1+nd->left->size;
            else
                return 1;
            
        }
    }
    int countBetweenElements(int e1,int e2)
    {
        //this->setsize();

        // for calculating no. of elements between 0 and e1 and e2
        int c1=countZeroToN(root,e1);
        int c2=countZeroToN(root,e2);
        //result should be numbers between them , so..
        return c2-c1+1;
    }
    

/***************************************/

    public:


    AvlTree(){
        root=NULL;
        size=0;
    }

    void add(int key)
    {
        root=insert_rec(root,key);
    }
    
    void remove(int key)
    {
        if(root==NULL) cout<<"Error";

        if(checkIfExists(key))
        root=delete_rec(root,key);
        else
        {
            cout<<"Element Not Found!";
        }
        
    }

    int find_kth_largest(int k)
    {
        if(k<1 || k>size){
        cout<<"Input out of range"<<size;
        return -1;
        }
        else
        return find_k(root,k);
    }
    
    int getsize()
    {
        //setsize();
        return this->size;
    }
   
    void printPreOrder()
    {
        preOrder(root);
    }
    
    bool checkIfExists(int key)
    {
        int minDiff=findMinDiff(key,0);
        if(minDiff==0)  
            return true;
        else
            return false;      
    }
    int getClosest(int val)
    {
        int diff= findMinDiff(val,0);      //via absolute difference  
        return val+diff;
    }

    int countInRange(int low,int high)
    {
        int diff1= findMinDiff(low ,1);       //lower bound
        int diff2= findMinDiff(high,-1);      //upper bound
        int val1=low+diff1;
        int val2=high+diff2;
        return countBetweenElements(val1,val2);
    }
};

class Ordered_Set{
    AvlTree tree;

    public:
    void insert(int x)
    {
        if(tree.checkIfExists(x))
        tree.add(x);
        else
        {
            cout<<"Duplicate element, not adding";
        }
    }
    void remove(int x)
    {
        tree.remove(x);
    }
    bool checkIfExists(int key)
    {
        return tree.checkIfExists(key);
    }
    int getClosest(int val)
    {
        return tree.getClosest(val);
    }
    int find_kth_largest(int k)
    {
        return tree.find_kth_largest(k);
    }
    int countInRange(int low,int high)
    {
        return tree.countInRange(low,high);
    }

};


int main()
{
    Ordered_Set set;


    return 0;
}