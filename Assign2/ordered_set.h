#include "avl.h"

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