#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

#include <set>

class tProgram
{
protected:
    GLuint              mProgramID;

public:
    tProgram(const tShader& newVertShader, const tShader& newFragShader);
    ~tProgram();

    bool linkStatus() const;
    bool validate() const;
    
    std::string getInfoLog() const;

    friend class tSpriteBatch;
};

