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

// AVL CLASS

class AvlTree{

    node *root;
    int size;

    int calc_size(node *nd)
    {
        if(!nd)
            return 0;
        else{
            nd->size= 1 + calc_size(nd->left) + calc_size(nd->right);
            return nd->size;
        }
    }

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
        if (nd == NULL) 
            return newnode(key);
     
        else if (key < nd->key)  
        {
            nd->left = insert_rec(nd->left, key);
        }
              
        else  
            nd->right = insert_rec(nd->right, key);  
      
        // update height of this node 
        setHeight(nd);
        //perform balancing
        if(nd==NULL) cout<<"whaaaa...";
        else
        nd=balanceAtNode(nd,key);
        
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
            cout << nd->key << " ";  
            preOrder(nd->left);  
            preOrder(nd->right);  
        }  
    }

   
/***************************************/

    public:


    AvlTree(){
        root=NULL;
    }

    void add(int key)
    {
        root=insert_rec(root,key);
    }

    int find_kth_largest(int k)
    {
        if(k<1 || k>size){
        cout<<"Input out of range";
        return -1;
        }
        else
        return find_k(root,k);
    }
    
    void setsize()
    {
        root->size=calc_size(root);
        this->size=root->size;
    }
    int getsize()
    {
        setsize();
        return this->size;
    }
   
    void printPreOrder()
    {
        preOrder(root);
    }
    
};


/*************************/


int main()  
{  

    AvlTree tree;
    
  
    //tree.add(32);
    //tree.setsize();
    int n,temp;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>temp;
        tree.add(temp);
    }

    double median=0.0;
    cout<<"\nMedian for given tree is ";
    int tsize=tree.getsize();
    if(tsize%2==0){
        median=tree.find_kth_largest(tsize/2)+tree.find_kth_largest(tsize/2+1);
        median/=2;
    }
    else
        median=tree.find_kth_largest(tsize/2+1);

     cout<<median<<endl;
   
    return 0;  
}  
