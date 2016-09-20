#version 330

in vec2 UV;

out vec4 color;

uniform sampler2D myTextureSampler;
uniform vec4 m_Color = vec4(1.0, 1.0, 1.0, 1.0);

void main() {
	color = texture( myTextureSampler, UV ) * m_Color;
}