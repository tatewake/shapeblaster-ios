uniform mediump mat4 mMVP;

varying mediump vec2 texCoords;
varying mediump vec4 colors;

attribute mediump vec2 mVerts;
attribute mediump vec2 mTexCoords;
attribute mediump vec4 mColors;

void main()
{
	gl_Position = mMVP * vec4(mVerts, 0.0, 1.0);

    texCoords = vec2(mTexCoords.x, mTexCoords.y);
    colors = mColors;
}

