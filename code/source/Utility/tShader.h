#pragma once

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

class tShader
{
public:
    enum Type
    {
        kInvalid,
        kVertexShader,
        kFragmentShader,
    };

protected:
    GLuint      mShaderID;
    Type        mType;
    std::string mSource;
    bool        mShouldDelete;

protected:
    void CreateGLShader(const tShader::Type &newType, const std::string &newSource);
    void DestroyGLShader();
    
public:
    tShader(const Type& newType, const std::string& newSource);
    tShader(const tShader& original);
    ~tShader();

    bool compileStatus() const;
    std::string getInfoLog() const;

    friend class tProgram;
};

