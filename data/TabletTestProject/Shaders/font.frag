#version 150

uniform sampler2D s_texture;
uniform vec4 color;

in vec2 texCoord;
out vec4 fragColor;

void main()
{
	//fragColor = vec4(abs(texCoord.x), abs(texCoord.y), 0, 1);
	if (texCoord.x < 0 || texCoord.x > 1 || texCoord.y < 0 || texCoord.y > 1)
		discard;
	
	vec4 tex = texture2D(s_texture, texCoord) * color;
	if(tex.a < 0.01)
		discard;
	fragColor = tex;
	//fragColor = vec4(0,0,1,1);
}
