#ifndef CS300_HW4_HASHTABLE_H
#define CS300_HW4_HASHTABLE_H
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

int hashIt(const string & key, int tableSize)
{
    int hashVal = 0;

    for(int i = 0; i < key.length(); i++)
    {
        hashVal = 37 * hashVal + key[i];
    }

    hashVal %= tableSize;

    if(hashVal < 0)
    {
        hashVal += tableSize;
    }
    return hashVal;
}

struct DocumentItem
{
    string documentName;
    int count;
};

struct WordItem
{
    string word;
    vector<DocumentItem> vec;
};

template<class Key, class Value>
class Hashtable
{
private:
    enum EntryType{ACTIVE, EMPTY, DELETED};

    struct HashEntry
    {
        Key element;
        Value data;
        EntryType info;

        HashEntry(const Key & theElement = Key(), const Value & theValue = Value(), EntryType i = EMPTY):element(theElement), data(theValue), info(i)
        {}
    };
    vector<HashEntry> array;
    int currentSize;
    const Key ITEM_NOT_FOUND;

    bool isPrime(int n)
    {
        if(n == 2 || n == 3)
        {
            return true;
        }
        if(n == 1 || n % 2 == 0)
        {
            return false;
        }
        for(int i = 3; i * i <= n; i+=2)
        {
            if(n % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    int nextPrime(int n)
    {
        if(n % 2 == 0)
        {
            n++;
        }
        for(; !isPrime(n); n+=2)
        {
            ;
        }
        return n;
    }

    bool isActive(int currentPos)const
    {
        if(array[currentPos].info == ACTIVE)
        {
            return true;
        }
        return false;
    }

    int findPos(const Key & x)const
    {
        int collisionNum = 0;
        int currentPos = hashIt(x, array.size());

        while (array[currentPos].info != EMPTY && array[currentPos].element != x)
        {
            currentPos += pow(++collisionNum, 2);

            if(currentPos >= array.size())
            {
                currentPos = currentPos % array.size();
            }
        }
        return currentPos;
    }

    void rehash()
    {
        int prevTableSize = array.size();

        vector<HashEntry> oldArray = array;

        array.resize(nextPrime(2 * oldArray.size()));

        int newTableSize = array.size();

        for(int i = 0; i < array.size(); i++)
        {
            array[i].info = EMPTY;
        }

        currentSize = 0;

        for(int i = 0; i < oldArray.size(); i++)
        {
            if(oldArray[i].info == ACTIVE)
            {
                insert(oldArray[i].element, oldArray[i].data);
            }
        }
        /*
        cout<<"rehashed..."<<endl;
        cout<<"previous table size:"<<prevTableSize<<", new table size: "<<newTableSize
            <<", current unique word count "<<currentSize<<", current load factor: "<< this->getLoadFactor()<<endl;*/
    }

public:
    Hashtable(const Key & notFound, int size):ITEM_NOT_FOUND(notFound), array(nextPrime(size))
    {
        this->makeEmpty();
    }

    void makeEmpty()
    {
        for(int i = 0; i < array.size(); i++)
        {
            array[i].info = EMPTY;
        }
        currentSize = 0;
    }

    void remove(const Key & x)
    {
        int curPos = findPos(x);
        if(isActive(curPos))
        {
            array[curPos].info = DELETED;
        }
    }

    const Key & find(const Key & x)const
    {
        int curPos = findPos(x);
        if(isActive(curPos))
        {
            return array[curPos].element;
        }
        return ITEM_NOT_FOUND;
    }

    void insert(const Key & x, const Value & y)
    {
        int curPos = findPos(x);
        if(isActive(curPos))
        {
            return;
        }
        array[curPos] = HashEntry(x, y, ACTIVE);

        if(++currentSize >= array.size() * 0.6)
        {
            rehash();
        }
    }


    Value findWordInHashTable(const Key & word)
    {
        int curPos = findPos(word);

        if(isActive(curPos))
        {
            return array[curPos].data;
        }
    }

    double getLoadFactor()
    {
        double loadFactor;
        loadFactor = 1.0 * currentSize/array.size();
        return loadFactor;
    }

    int getWordCount()
    {
       return currentSize;
    }
};

#endif