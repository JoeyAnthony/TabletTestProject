#version 330

#include "common.glsl"


uniform sampler2D s_texture;
uniform sampler2D s_normalmap;
uniform sampler2D s_specularmap;
uniform vec4 diffuseColor;
uniform float textureFactor;
uniform float shinyness;


in vec2 texCoord;


in vec4 position;
out vec4 fragColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;


void main()
{
	vec4 tex = texture2D(s_texture, texCoord);
	if(tex.a < 0.01)
		discard;
	fragColor.rgb = tex.rgb;
	fragColor.a = tex.a;
}
