//KEREM TUGRUL ENUNLU
#include <iostream>
#include <string>
#include <fstream>
#include "AVLSearchTree.h"
#include "Strutils.h"
#include "Hashtable.h"
#include <sstream>
#include <chrono>
#include "Randgen.h"
using namespace std;

RandGen r;

//OPERATOR OVERLOADS

bool operator < (const WordItem & lhs, const WordItem & rhs)
{
    return lhs.word < rhs.word;
}

bool operator <= (const WordItem & lhs, const WordItem & rhs)
{
    return lhs.word <= rhs.word;
}
bool operator > (const WordItem & lhs, const WordItem & rhs)
{
    return lhs.word > rhs.word;
}

bool operator == (const WordItem & lhs, const WordItem & rhs)
{
    return lhs.word > rhs.word;
}

void HashTableEditor(WordItem * & item, bool & check, string & docName)
{
    for(DocumentItem & document : item->vec)
    {
        if(document.documentName == docName)
        {
            document.count++;
            check = true;
            break;
        }
    }
    if(!check) // IF WORD IS IN HASHTABLE, BUT A NEW DOCUMENT ENTRY IS NEEDED
    {
        DocumentItem theDocument;

        theDocument.count = 1;
        theDocument.documentName = docName;

        item->vec.push_back(theDocument);
    }
}

void VectorEditor(WordItem * & item, bool & check, string & docName)
{
    for(DocumentItem & document : item->vec)
    {
        if(document.documentName == docName)
        {
            document.count++;
            check = true;
            break;
        }
    }
    if(!check) // IF WORD IS IN VECTOR, BUT A NEW DOCUMENT ENTRY IS NEEDED
    {
        DocumentItem theDocument;

        theDocument.count = 1;
        theDocument.documentName = docName;

        item->vec.push_back(theDocument);
    }
}

bool isWord(const string & s) //TO CHECK IF OUR ENTERED WORD IS INDEED A WORD
{
    for(int i = 0; i < s.length(); i++)
    {
        if(i == '0' || i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8' || i == '9')
        {
            return false;
        }
    }
    return true;
}

void correctedVersionOfString(string & word) //REMOVING NON-ALPHABETIC CHARACTERS
{
    for(char & a : word)
    {
        if(!isalpha(a))
        {
            a = ' ';
        }
    }
}

template <class Comparable>
void insertionSort(vector<Comparable*> & v)
{
    int j;

    for(int p = 1; p < v.size(); p++)
    {
        Comparable* tmp;
        tmp = v[p];

        for(j = p; j > 0 && *tmp < *v[j - 1]; j--)
        {
            v[j] = v[j - 1];
        }
        v[j] = tmp;
    }
}

inline int leftChild(int i)
{
    return 2 * i + 1;
}

template<class Comparable>
void percDown(vector<Comparable*> & v, int i, int n)
{
    int child;
    Comparable* tmp;

    for(tmp = v[i]; leftChild(i) < n; i = child)
    {
        child = leftChild(i);

        if(child != n-1 && *v[child] < *v[child+1])
        {
            child++;

            if(*v[child] > *tmp)
            {
                v[i] = v[child];
            }
            else
            {
                break;
            }
        }
    }
    v[i] = tmp;
}

template <class Comparable>
void heapSort(vector<Comparable*> & v)
{
    for(int i = v.size() / 2; i >= 0; i--)
    {
        percDown(v, i, v.size());
    }
    for(int j = v.size() - 1; j > 0; j--)
    {
        std::swap(v[0], v[j]);
        percDown(v, 0, j);
    }
}

template<class Comparable>
void merge(vector<Comparable*> & v, vector<Comparable*> & tmpArray, int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while(leftPos <= leftEnd && rightPos <= rightEnd)
    {
        if(*v[leftPos] <= *v[rightPos])
        {
            tmpArray[tmpPos++] = v[leftPos++];
        }
        else
        {
            tmpArray[tmpPos++] = v[rightPos++];
        }
    }

    while(leftPos <= leftEnd)
    {
        tmpArray[tmpPos++] = v[leftPos++];
    }

    while(rightPos <= rightEnd)
    {
        tmpArray[tmpPos++] = v[rightPos++];
    }

    for(int i = 0; i < numElements; i++, rightEnd--)
    {
        v[rightEnd] = tmpArray[rightEnd];
    }
}

template<class Comparable>
void mergeSort(vector<Comparable*> & v, vector<Comparable*> & tmpArray, int left, int right)
{
    if(left < right)
    {
        int center = (left + right) / 2;

        mergeSort(v, tmpArray, left, center);
        mergeSort(v, tmpArray, center + 1, right);

        merge(v, tmpArray, left, center + 1, right);
    }
}

template<class Comparable>
void mergeSort(vector<Comparable*> & v)
{
    vector<Comparable*> tmpArray(v.size());

    mergeSort(v, tmpArray, 0, v.size() - 1);
}

template<class Comparable*>
inline void swap(Comparable* & obj1, Comparable* & obj2)
{
    Comparable* tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

template<class Comparable>
Comparable* & median3(vector<Comparable*> & v, int left, int right)
{
    int center = (left + right) / 2;

    if(*v[center] < *v[left])
    {
        std::swap(v[left], v[center]);
    }
    if(*v[right] < *v[left])
    {
        std::swap(v[left], v[right]);
    }
    if(*v[right] < *v[center])
    {
        std::swap(v[center], v[right]);
    }

   std::swap(v[center], v[right - 1]);

    return v[right - 1];
}

template <class Comparable>
void insertionSort(vector<Comparable*> & v, int left, int right)
{
    for(int p = left + 1; p <= right; p++)
    {
        Comparable* tmp = v[p];
        int j;

        for(j = p; j > left && *tmp < *v[j - 1]; j--)
        {
            v[j] = v[j - 1];
        }

        v[j] = tmp;
    }
}

template <class Comparable>
void quickSort(vector<Comparable*> & v, int left, int right)
{
    if(left + 10 <= right)
    {
        Comparable* pivot = median3(v, left, right);

        int i = left, j = right - 1;

        for(;;)
        {
            while(*v[++i] < *pivot)
            {

            }
            while(*pivot < *v[--j])
            {

            }
            if(i < j)
            {
                std::swap(v[i], v[j]);
            }
            else
            {
                break;
            }
        }
        std::swap(v[i], v[right - 1]);

        quickSort(v, left, i-1);
        quickSort(v, i+1, right);
    }
    else
    {
        insertionSort(v, left, right);
    }
}

template<class Comparable>
void quickSort(vector<Comparable*> & v)
{
    quickSort(v, 0, v.size() - 1);
}

template<class Comparable>
void quickSortMedian(vector<Comparable*> & v)
{
    quickSort(v, (v.size() - 1) / 2, v.size() - 1);
}

template<class Comparable>
void quickSortRandom(vector<Comparable*> & v)
{
    int x = r.RandInt(0, v.size() - 1);

    quickSort(v, x, v.size() - 1);
}

WordItem* & binarySearch(vector<WordItem*> & v, string && key)
{
    int min = 0;
    int max = v.size() - 1;

    while(min <= max)
    {
        int mid = min + (max - min) / 2;

        if(v[mid]->word == key)
        {
            return v[mid];
        }
        else if(v[mid]->word < key)
        {
            min = mid + 1;
        }
        else
        {
            max = mid - 1;
        }
    }
    static WordItem* invalidItem;
    return invalidItem;
}

WordItem* & findWordInVector(string & word, vector<WordItem*> & v)
{
    for(WordItem* & obj : v)
    {
        if(obj->word == word)
        {
            return obj;
        }
    }
}

int main()
{
    vector<WordItem*> vecIS;
    vector<WordItem*> vecHS;
    vector<WordItem*> vecMS;
    vector<WordItem*> vecQS;

    vector<WordItem*> vecQSRand;
    vector<WordItem*> vecQSMed;

    AVLSearchTree<string, WordItem*> tree("");
    Hashtable<string, WordItem*> ht("", 53);

    vector<string> documentHolder;

    int amountOfFiles;
    ifstream input;
    string fileName;

    cout<<"Enter number of input files:";
    cin>>amountOfFiles;

    for(int x = 1; x <= amountOfFiles; x++)
    {
        cout<<"Enter "<<x<<". "<<"file name:";
        cin>>fileName;

        documentHolder.push_back(fileName);  //A DOCUMENT NAME HOLDER TO BE USED IN FURTHER OPERATIONS
    }

    for(int i = 1; i <= amountOfFiles; i++)
    {
        string s;

        string word;
        input.open(documentHolder[i-1]);

        while(getline(input, s))
        {
            correctedVersionOfString(s);

            istringstream st(s);

            while(st>>word)
            {
                if(!isWord(word))
                {
                    continue;
                }
                else
                {
                    word = LowerString(word);

                    if(tree.find(word) != word && ht.find(word) != word) //IF WORD DOESN'T EXIST IN TREE and IN HASHTABLE and VECTORS
                    {
                        WordItem * w = new WordItem;
                        DocumentItem d;

                        w->word = word;

                        d.count = 1;
                        d.documentName = documentHolder[i-1];

                        w->vec.push_back(d);
                        tree.insert(word, w);

                        WordItem * item = new WordItem;
                        DocumentItem docItem;

                        item->word = word;

                        docItem.count = 1;
                        docItem.documentName = documentHolder[i-1];

                        item->vec.push_back(docItem);
                        ht.insert(word, item);

                        WordItem* vecItem = new WordItem;
                        DocumentItem docVecItem;

                        vecItem->word = word;

                        docVecItem.count = 1;
                        docVecItem.documentName = documentHolder[i-1];

                        vecItem->vec.push_back(docVecItem);

                        vecIS.push_back(vecItem);
                        vecHS.push_back(vecItem);
                        vecMS.push_back(vecItem);
                        vecQS.push_back(vecItem);
                        vecQSMed.push_back(vecItem);
                        vecQSRand.push_back(vecItem);

                    }
                    else //IF WORD IS ALREADY IN TREE AND HASHTABLE AND VECTORS
                    {
                        WordItem * foundHashedWord;
                        WordItem * findWord;

                        WordItem *findVecIWord = findWordInVector(word, vecIS);
                        WordItem *findVecHWord = findWordInVector(word, vecHS);
                        WordItem *findVecMWord = findWordInVector(word, vecMS);
                        WordItem *findVecQWord = findWordInVector(word, vecQS);
                        WordItem *findVecQMedWord = findWordInVector(word, vecQSMed);
                        WordItem *findVecQRandWord = findWordInVector(word, vecQSRand);

                        foundHashedWord = ht.findWordInHashTable(word);
                        findWord = tree.findWordInTree(word, tree.getRoot());

                        bool findForTree = false;
                        bool findForHT = false;

                        bool findForVecI = false;
                        bool findForVecH = false;
                        bool findForVecM = false;
                        bool findForVecQ = false;
                        bool findForVecQRand = false;
                        bool findForVecQMed = false;

                        VectorEditor(findVecIWord, findForVecI, documentHolder[i-1]);
                        VectorEditor(findVecHWord, findForVecH, documentHolder[i-1]);
                        VectorEditor(findVecMWord, findForVecM, documentHolder[i-1]);
                        VectorEditor(findVecQWord, findForVecQ, documentHolder[i-1]);
                        VectorEditor(findVecQMedWord, findForVecQMed, documentHolder[i-1]);
                        VectorEditor(findVecQRandWord, findForVecQRand, documentHolder[i-1]);

                        HashTableEditor(foundHashedWord, findForHT, documentHolder[i-1]);

                        for(DocumentItem & document : findWord->vec)
                        {
                            if(document.documentName == documentHolder[i-1])
                            {
                                document.count++;
                                findForTree = true;
                                break;
                            }
                        }

                        if(!findForTree) // IF WORD IS IN TREE, BUT A NEW DOCUMENT ENTRY IS NEEDED
                        {
                            DocumentItem theDocument;

                            theDocument.count = 1;
                            theDocument.documentName = documentHolder[i-1];

                            findWord->vec.push_back(theDocument);
                        }
                    }
                    // SINCE WORDS AND THEIR RESPECTIVE INFO'S GET ADDED INTO OUR TREE AND HASHTABLE AND THE VECTORS AT THE SAME TIME,
                    // WE DO NOT HAVE TO CHECK FOR ALL THREE OF THEM. ONE WILL SUFFICE.
                }
            }
        }
        input.close();
    }

    cout<<"After preprocessing, the unique word count is "<<ht.getWordCount()
        <<". Current load ratio is "<<ht.getLoadFactor()<<endl;

    //SORTING TIMES

    int k = 100;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        insertionSort(vecIS);
    }
    auto endIS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        heapSort(vecHS);
    }
    auto endHS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        mergeSort(vecMS);
    }
    auto endMS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        quickSort(vecQS);
    }
    auto endQS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        quickSortMedian(vecQSMed);
    }
    auto endQSMed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        quickSortRandom(vecQSRand);
    }
    auto endQSRandom = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    string queriedWordsString;

    string secondWord;
    cin.ignore();

    cout << "Enter queried words in one line:";
    getline(cin, queriedWordsString);

    correctedVersionOfString(queriedWordsString);

    istringstream iss(queriedWordsString);

    int count = 0;
    vector<string> words;
    string theWord;

    while (iss >> theWord)
    {
        words.push_back(theWord);
        count++;
    }

    int count2 = 0;

    for(int i = 0; i < count; i++)
    {
        if(LowerString(words[i]) == tree.find(LowerString(words[i])))
        {
            count2++;
        }
    }

    start = std::chrono::high_resolution_clock::now();
    for (int I = 0; I < k; I++)
    {
        if(count != count2) //IF NOT ALL SEARCHED WORDS ARE IN THE TREE
        {
            if(I == 0)
            {
                cout<<"No document contains the given query"<<endl;
            }
        }

        else if(count == 1 && count2 == 1) //ONLY ONE WORD SEARCHED AND FOUND
        {
            WordItem * findWord = tree.findWordInTree(LowerString(words[0]), tree.getRoot());

            for(int a = 0; a < findWord->vec.size(); a++)
            {
                if(I == 0)
                {
                    cout<<"in Document "<<findWord->vec[a].documentName<<", "<<LowerString(theWord)<<" found "<<findWord->vec[a].count<<" times."<<endl;
                }
            }
        }

        else if(count > 1 && count2 > 1 && count == count2) //MORE THAN ONE WORD SEARCHED AND FOUND
        {
            int check = 0; //CHECK TO SEE IF EVERY SEARCHED WORD IS IN A PARTICULAR TXT FILE

            for(const string & d : documentHolder)
            {
                for(int i = 0; i < words.size(); i++)
                {
                    WordItem * findWord = tree.findWordInTree(LowerString(words[i]), tree.getRoot());

                    for (int j = 0; j < findWord->vec.size(); j++)
                    {
                        if (findWord->vec[j].documentName == d)
                        {
                            check++;
                        }
                    }
                }
                if(check == words.size())
                {
                    if(I == 0)
                    {
                        cout<<"in Document "<<d<<", "<<"";
                    }

                    for(int b = 0; b < words.size(); b++)
                    {
                        WordItem * findWord = tree.findWordInTree(LowerString(words[b]), tree.getRoot());

                        for(int c = 0; c < findWord->vec.size(); c++)
                        {
                            if(findWord->vec[c].documentName == d)
                            {
                                if(I == 0)
                                {
                                    cout<<LowerString(words[b])<<" found "<<findWord->vec[c].count<<" times"<<"";
                                }
                            }
                        }
                        if(b < words.size() - 1)
                        {
                            if(I == 0)
                            {
                                cout<<", "<<"";
                            }
                        }
                    }
                    if(I == 0)
                    {
                        cout<<"."<<endl;
                    }
                }
                check = false;
            }
        }
    }
    auto endBST = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    start = std::chrono::high_resolution_clock::now();
    for (int I = 0; I < k; I++)
    {
        if(count != count2) //IF NOT ALL SEARCHED WORDS ARE IN THE HASHTABLE
        {
            if(I == 0)
            {
                cout<<"No document contains the given query"<<endl;
            }
        }

        else if(count == 1 && count2 == 1) //ONLY ONE WORD SEARCHED AND FOUND
        {
            WordItem * findHashedWord = ht.findWordInHashTable(LowerString(words[0]));

            for(int a = 0; a < findHashedWord->vec.size(); a++)
            {
                if(I == 0)
                {
                    cout<<"in Document "<<findHashedWord->vec[a].documentName<<", "<<LowerString(theWord)<<" found "<<findHashedWord->vec[a].count<<" times."<<endl;
                }
            }
        }

        else if(count > 1 && count2 > 1 && count == count2) //MORE THAN ONE WORD SEARCHED AND FOUND
        {
            int check = 0; //CHECK TO SEE IF EVERY SEARCHED WORD IS IN A PARTICULAR TXT FILE

            for(const string & d : documentHolder)
            {
                for(int i = 0; i < words.size(); i++)
                {
                    WordItem * findHashedWord = ht.findWordInHashTable(LowerString(words[i]));

                    for (int j = 0; j < findHashedWord->vec.size(); j++)
                    {
                        if (findHashedWord->vec[j].documentName == d)
                        {
                            check++;
                        }
                    }
                }
                if(check == words.size())
                {
                    if(I == 0)
                    {
                        cout<<"in Document "<<d<<", "<<"";
                    }

                    for(int b = 0; b < words.size(); b++)
                    {
                        WordItem * findHashedWord = ht.findWordInHashTable(LowerString(words[b]));

                        for(int c = 0; c < findHashedWord->vec.size(); c++)
                        {
                            if(findHashedWord->vec[c].documentName == d)
                            {
                                if(I == 0)
                                {
                                    cout<<LowerString(words[b])<<" found "<<findHashedWord->vec[c].count<<" times"<<"";
                                }
                            }
                        }
                        if(b < words.size() - 1)
                        {
                            if(I == 0)
                            {
                                cout<<", "<<"";
                            }
                        }
                    }
                    if(I == 0)
                    {
                        cout<<"."<<endl;
                    }
                }
                check = false;
            }
        }
    }
    auto endHT = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    start = std::chrono::high_resolution_clock::now();
    for (int I = 0; I < k; I++)
    {
        if(count != count2) //IF NOT ALL SEARCHED WORDS ARE IN THE VECTOR
        {
            if(I == 0)
            {
                cout<<"No document contains the given query"<<endl;
            }
        }

        else if(count == 1 && count2 == 1) //ONLY ONE WORD SEARCHED AND FOUND
        {
            WordItem* findInVec = binarySearch(vecQS, LowerString(words[0]));

            for(int a = 0; a < findInVec->vec.size(); a++)
            {
                //counts were added as a whole, this gives the seperated amounts
                if(I == 0 && findInVec->vec[a].count % 2 == 0)
                {
                    cout<<"in Document "<<findInVec->vec[a].documentName<<", "<<LowerString(theWord)<<" found "<<(findInVec->vec[a].count/6)<<" times."<<endl;
                }
                else if(I == 0 && findInVec->vec[a].count % 2 != 0)
                {
                    cout<<"in Document "<<findInVec->vec[a].documentName<<", "<<LowerString(theWord)<<" found "<<(findInVec->vec[a].count/6)+1<<" times."<<endl;
                }
            }
        }

        else if(count > 1 && count2 > 1 && count == count2) //MORE THAN ONE WORD SEARCHED AND FOUND
        {
            int check = 0; //CHECK TO SEE IF EVERY SEARCHED WORD IS IN A PARTICULAR TXT FILE

            for(const string & d : documentHolder)
            {
                for(int i = 0; i < words.size(); i++)
                {
                    WordItem* findInVec = binarySearch(vecQS, LowerString(words[i]));

                    for (int j = 0; j < findInVec->vec.size(); j++)
                    {
                        if (findInVec->vec[j].documentName == d)
                        {
                            check++;
                        }
                    }
                }
                if(check == words.size())
                {
                    if(I == 0)
                    {
                        cout<<"in Document "<<d<<", "<<"";
                    }

                    for(int b = 0; b < words.size(); b++)
                    {
                        WordItem* findInVec = binarySearch(vecQS, LowerString(words[b]));

                        for(int c = 0; c < findInVec->vec.size(); c++)
                        {
                            if(findInVec->vec[c].documentName == d)
                            {
                                //counts were added as a whole, this gives the seperated amounts
                                if(I == 0 && findInVec->vec[c].count % 2 == 0)
                                {
                                    cout<<LowerString(words[b])<<" found "<<(findInVec->vec[c].count/6)<<" times"<<"";
                                }
                                else if(I == 0 && findInVec->vec[c].count % 2 != 0)
                                {
                                    cout<<LowerString(words[b])<<" found "<<(findInVec->vec[c].count/6)+1<<" times"<<"";
                                }
                            }
                        }
                        if(b < words.size() - 1)
                        {
                            if(I == 0)
                            {
                                cout<<", "<<"";
                            }
                        }
                    }
                    if(I == 0)
                    {
                        cout<<"."<<endl;
                    }
                }
                check = false;
            }
        }
    }
    auto endBS =  std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    //TIMING CALCULATIONS AND COMPARISONS

    cout << "\nBinary Search Tree Time: " << endBST.count() / k << "\n";
    cout << "Hash Table Time: " << endHT.count() / k << "\n";
    cout << "Binary Search Time: " << endBS.count() / k << "\n";

    cout <<"\nQuick Sort(median) Time: " << endQSMed.count() / k << "\n";
    cout <<"Quick Sort(random) Time: " << endQSRandom.count() / k << "\n";
    cout <<"Quick Sort(first) Time: " << endQS.count() / k << "\n";
    cout <<"Merge Sort Time: " << endMS.count() / k << "\n";
    cout <<"Heap Sort Time: " << endHS.count() / k << "\n";
    cout <<"Insertion Sort Time: " << endIS.count() / k << "\n";

    cout<<"\nSpeed Up BST/HST: "<< (1.0 * endBST.count()) / (1.0 * endHT.count()) << "\n";
    cout<<"Speed Up Merge Sort/Quick Sort(Median): "<< (1.0 * endMS.count()) / (1.0 * endQSMed.count()) << "\n";
    cout<<"Speed Up Heap Sort/Quick Sort(Median): "<< (1.0 * endHS.count()) / (1.0 * endQSMed.count()) << "\n";
    cout<<"Speed Up Insertion Sort/Quick Sort(Median): "<< (1.0 * endIS.count()) / (1.0 * endQSMed.count()) << "\n";

    if((1.0 * endBS.count()) >= (1.0 * endBST.count()))
    {
        cout<<"\nSpeed Up Binary Search / Binary Search Tree Time: "<<(1.0 * endBS.count()) / (1.0 * endBST.count()) << "\n";
    }
    else
    {
        cout<<"\nSpeed Up Binary Search Tree Time / Binary Search: "<< (1.0 * endBST.count()) / (1.0 * endBS.count())<< "\n";
    }
    if((1.0 * endBS.count()) >= (1.0 * endHT.count()))
    {
        cout<<"Speed Up Binary Search / Hash Table Time: "<< (1.0 * endBS.count()) / (1.0 * endHT.count())<< "\n";
    }
    else
    {
        cout<<"Speed Up Hash Table Time / Binary Search: "<< (1.0 * endHT.count()) / (1.0 * endBS.count())<< "\n";
    }

    return 0;
}