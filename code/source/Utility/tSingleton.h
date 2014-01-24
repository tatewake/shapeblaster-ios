#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

template<typename T>
class tSingleton
{
public:
    tSingleton() { }

    static T* getInstance()
    {
        static T mInstance;
        return &mInstance;
    }
};

