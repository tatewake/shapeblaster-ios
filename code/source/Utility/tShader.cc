#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

void tShader::CreateGLShader(const tShader::Type &newType, const std::string &newSource)
{
    const char* newSourcePtr = newSource.c_str();
    
    static GLenum glShaderTypes[] =
    {
        GL_VERTEX_SHADER,
        GL_VERTEX_SHADER,
        GL_FRAGMENT_SHADER,
    };
    
    mShaderID = glCreateShader(glShaderTypes[newType]);
    
    glShaderSource(mShaderID, 1, &newSourcePtr, NULL);
}

void tShader::DestroyGLShader()
{
    if (mShaderID)
    {
        glDeleteShader(mShaderID);
    }
}

tShader::tShader(const Type& newType, const std::string& newSource)
: mShaderID(0), mType(newType), mSource(newSource), mShouldDelete(true)
{
    assert(newType != kInvalid);

    CreateGLShader(newType, newSource);
    
    if (mShaderID)  //Not fixed function
    {
        glCompileShader(mShaderID);

        if (compileStatus() == false)
        {
            printf("***Compile error: %s\n", getInfoLog().c_str());
        }
    }
}

tShader::tShader(const tShader& original)
: mShaderID(original.mShaderID), mType(original.mType), mSource(original.mSource),
    mShouldDelete(false)    //we're the copy now.
{
}


tShader::~tShader()
{
    if (mShouldDelete)
    {
        DestroyGLShader();
    }
}

bool tShader::compileStatus() const
{
    if (mShaderID)  //Not fixed function
    {
        GLint compileStatus;

        glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &compileStatus);

        return (compileStatus == GL_TRUE);
    }

    return false;
}

std::string tShader::getInfoLog() const
{
    std::string result;
    GLint  infoLogLength;

    glGetShaderiv(mShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        GLchar* infoLog = new GLchar[infoLogLength];
        if (infoLog)
        {
            glGetShaderInfoLog(mShaderID, infoLogLength, &infoLogLength, infoLog);
            result = (char*)infoLog;
        }
        delete[] infoLog;
    }

    return result;
}

