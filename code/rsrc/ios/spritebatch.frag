varying mediump vec2 texCoords;
varying mediump vec4 colors;
uniform sampler2D tex;

void main()
{
	gl_FragColor = texture2D(tex, texCoords) * colors;
}

