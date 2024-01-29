#ifndef CS300_HW3_AVLSEARCHTREE_H
#define CS300_HW3_AVLSEARCHTREE_H
#include <string>
#include <vector>
using namespace std;

//THIS CLASS IMPLEMENTATION BEARS THE SAME NAME AS THE CLASS USED IN HW2 AND HW3 FOR SYNTACTIC PURPOSES. I DID NOT WANT TO MODIFY OR CHANGE THE CONSTRUCTORS AND THE IMPLEMENTATIONS OF CERTAIN FUNCTIONS TO EASE MY WORK.
//THIS CLASS IS ACTUALLY A BST CLASS SINCE THE ROTATION IMPLEMENTATIONS HAVE BEEN REMOVED OR COMMENTED OUT.

template <class Key, class Value>
class AVLSearchTree
{
private:
    struct AvlNode
    {
        Key element;
        Value data;

        AvlNode * left;
        AvlNode * right;
        int height;

        AvlNode(const Key & theElement, const Value & item):element(theElement), height(0), left(nullptr), right(nullptr), data(item)
        {}

        AvlNode(const Key & theElement):element(theElement), height(0), left(nullptr), right(nullptr), data(nullptr)
        {}
    };
    AvlNode * root;
    const Key ITEM_NOT_FOUND;

    void insert(const Key & x, const Value & y, AvlNode * & t) const
    {
        if(t == NULL)
        {
            t = new AvlNode(x, y);
        }
        else if(x < t->element)
        {
            insert(x, y, t->left);
        }
        else if(x > t->element)
        {
            insert(x, y, t->right);
        }
        else
        {
            ; // DO NOTHING
        }

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    void makeEmpty(AvlNode * & t)const
    {
        if(t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }

    int max(int lhs, int rhs) const
    {
        if(lhs > rhs)
        {
            return lhs;
        }
        else
        {
            return rhs;
        }
    }

    const Key & elementAt(AvlNode * t)const
    {
        if(t == NULL)
        {
            return ITEM_NOT_FOUND;
        }
        else
        {
            return t->element;
        }
    }

    AvlNode * find(const Key & x, AvlNode * t)const
    {
        while(t != NULL)
        {
            if(x < t->element)
            {
                t = t->left;
            }
            else if(x > t->element)
            {
                t = t->right;
            }
            else
            {
                return t;
            }
        }
        return NULL;
    }

    AvlNode * findMin(AvlNode * t)const
    {
        if(t == NULL)
        {
            return NULL;
        }
        if(t->left == NULL)
        {
            return t;
        }
        return findMin(t->left);
    }

    AvlNode * findMax(AvlNode * t)const
    {
        if(t == NULL)
        {
            return NULL;
        }
        if(t->right == NULL)
        {
            return t;
        }
        return findMax(t->right);
    }

    void remove(const Key & x, const Value & y, AvlNode * & t)const
    {
        if(t == NULL)
        {
            return;
        }
        else if(x < t->element)
        {
            remove(x, y, t->left);
        }
        else if(x > t->element)
        {
            remove(x, y, t->right);
        }
        else if(t->left != NULL && t->right != NULL)
        {
            t->element = findMin(t->right)->element;

            remove(t->element, y, t->right);
        }
        else
        {
            AvlNode * oldNode = t;

            if(t->left != NULL)
            {
                t = t->left;
            }
            else
            {
                t = t->right;
            }
            delete oldNode;
        }
    }

public:
    AVLSearchTree(const Key & notFound):ITEM_NOT_FOUND(notFound), root(NULL)
    {}

    ~AVLSearchTree()
    {
        makeEmpty();
    }

    const Key & find(const Key & x) const
    {
        return elementAt(find(x, root));
    }

    const Key & findMin()const
    {
        return elementAt(findMin(root));
    }

    const Key & findMax()const
    {
        return elementAt(findMax(root));
    }

    int height(AvlNode * n) const
    {
        if(n == nullptr)
        {
            return -1;
        }
        else
        {
            return n->height;
        }
    }

    void insert(const Key & x, const Value & y)
    {
        insert(x, y, root);
    }

    void remove(const Key & x, const Value & y)
    {
        remove(x, y, root);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    Value findWordInTree(const Key & word, AvlNode * t)
    {
        if(t == NULL || t->element == word)
        {
            if(t != NULL && t->element == word)
            {
                return t->data;
            }
            else
            {
                return NULL;
            }
        }
        else if(word < t->element)
        {
            return findWordInTree(word, t->left);
        }
        else
        {
            return findWordInTree(word, t->right);
        }
    }

    AvlNode * getRoot()
    {
        return root;
    }
};
#endif