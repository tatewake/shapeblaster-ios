#include "Utility/package.h"

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

tProgram::tProgram(const tShader& newVertShader, const tShader& newFragShader)
: mProgramID(0)
{
    assert(newVertShader.mType == tShader::kVertexShader);
    assert(newFragShader.mType == tShader::kFragmentShader);

    if (newVertShader.compileStatus() && newFragShader.compileStatus())
    {
        mProgramID = glCreateProgram();

        if (mProgramID)
        {
            glAttachShader(mProgramID, newVertShader.mShaderID);
            glAttachShader(mProgramID, newFragShader.mShaderID);
            glLinkProgram(mProgramID);
        }
    }
}

tProgram::~tProgram()
{
    if (mProgramID)
    {
        glDeleteProgram(mProgramID);
    }
}

bool tProgram::linkStatus() const
{
    if (mProgramID)
    {
        GLint linked;

        glGetProgramiv(mProgramID, GL_LINK_STATUS, &linked);

        return (linked == GL_TRUE);
    }
    return false;
}

bool tProgram::validate() const
{
    GLint validated;
    glValidateProgram(mProgramID);
    glGetProgramiv(mProgramID, GL_VALIDATE_STATUS, &validated);

    return (validated == GL_TRUE);
}

std::string tProgram::getInfoLog() const
{
    std::string result;
    GLint  infoLogLength;

    glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        GLchar* infoLog = new GLchar[infoLogLength];
        if (infoLog)
        {
            glGetProgramInfoLog(mProgramID, infoLogLength, &infoLogLength, infoLog);
            result = (char*)infoLog;
        }
        delete[] infoLog;
    }

    return result;
}
