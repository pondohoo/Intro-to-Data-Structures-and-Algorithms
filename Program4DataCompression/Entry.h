#ifndef __ENTRY_H__
#define __ENTRY_H__

#include<string>
using namespace std;

class Entry
{
private:
    string token;
    int frequency;
    int code;
public:
    Entry(const string& token) : token(token)
    {
        frequency = 1;
        code = 1;
    }

    //accessors
    int getFrequency()
    {
        return frequency;
    }
    string getToken()
    {
        return token;
    }
    int getCode()
    {
        return code;
    }

    //setters
    void addFrequency()
    {
        frequency += 1;
    }
    void setCode(int newCode)
    {
        code = newCode;
    }

};
#endif