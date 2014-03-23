// fragment shader
#version 150

// this is how we receive the texture
uniform sampler2DRect tex0;
in vec2 varyingtexcoord;
out vec4 outputColor;

// this is coming from our C++ code
uniform float red;
uniform float green;
uniform float blue;
uniform float alpha;

void main()
{
    vec4 tmpColor = texture(tex0, varyingtexcoord);
    tmpColor.r = red;
    tmpColor.g = green;
    tmpColor.b = blue;
    tmpColor.a *= alpha;
    outputColor = tmpColor;
}