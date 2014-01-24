#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

template<class T>
class tOptional
{
protected:
    T    mValue;
    bool mEngaged;

public:
    tOptional() : mEngaged(false)                       { }
    tOptional(const T& a) : mValue(a), mEngaged(true)   { }

    const T& operator*() const  { assert(mEngaged); return mValue; }
    T& operator*()              { assert(mEngaged); return mValue; }

    const T* operator->() const { assert(mEngaged); return &mValue; }
    T* operator->()             { assert(mEngaged); return &mValue; }

    operator bool() const       { return mEngaged; }
};

