#include "Compression.h"



Compression::Compression(string filename)
{
    this->filename = filename;
}
void Compression::CreateSortedList()
{
    ifstream inFS;
    inFS.open(filename);
    if (!inFS)
    {
        cout << "Error opening file" << endl;
        return;
    }
    string currString;
    while (inFS >> currString)
    {
        everySingleWordLol.push_back(currString);
        frequencyHeap.enqueue(currString);
        frequencyHeap.highest();
    }

    inFS.close();
}
void Compression::MakeAccessible()
{
    int counter = 0;
    while (frequencyHeap.getSize() != 0)
    {
        counter += 1;
        frequencyHeap.highest()->setCode(counter);
        accessibleList.push_back(frequencyHeap.highest());
        frequencyHeap.dequeue();
    }

}
void Compression::HashItUp()
{
    CreateSortedList();
    MakeAccessible();
    HashTable hashywashy(accessibleList.size());

    pair<string, int>* encoder = hashywashy.encode(accessibleList);
    pair<int, string>* decoder = hashywashy.decode(accessibleList);


    ofstream outFS;
    if (!outFS)
    {
        cout << "Error opening file" << endl;
        return;
    }
    outFS.open("coded.txt");

    for (unsigned int i = 0; i < everySingleWordLol.size(); i++)
    {
        for (unsigned int j = 0; j < hashywashy.getSize(); j++)
        {
            if (everySingleWordLol.at(i) == encoder[j].first)
            {
                outFS << encoder[j].second;
                break;
            }
            
        }
        if (i < everySingleWordLol.size() - 1)
        {
            outFS << ' ';
        }
    }

    outFS.close();

    outFS.open("decodermap.txt");
    for (unsigned int i = 0; i < hashywashy.getSize(); i++)
    {
        outFS << decoder[i].first << ' ' << decoder[i].second;
        if (i < hashywashy.getSize() - 1)
        {
            outFS << endl;
        }
    }

    outFS.close();
}

void Compression::UnhashItUp()
{
    HashTable hashywashy(accessibleList.size());
    pair<int, string>* decoder = hashywashy.decode(accessibleList);

    ifstream inFS;
    inFS.open("coded.txt");
    if (!inFS)
    {
        cout << "Error opening file" << endl;
        return;
    }
    int currInt;
    while (inFS >> currInt)
    {
        code.push_back(currInt);
    }
    inFS.close();

    ofstream outFS;
    if (!outFS)
    {
        cout << "Error opening file" << endl;
        return;
    }
    outFS.open("decoded.txt");
    
    for (unsigned int i = 0; i < everySingleWordLol.size(); i++)
    {
        for (unsigned int j = 0; j < hashywashy.getSize(); j++)
        {
            if (code.at(i) == decoder[j].first)
            {
                outFS << '(' << code.at(i) << ')' << decoder[j].second;
                break;
            }

        }
        if (i < code.size() - 1)
        {
            outFS << ' ';
        }
    }
}