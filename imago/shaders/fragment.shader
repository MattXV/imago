#version 330 core

layout(location = 0) out vec4 fragmentColor;

uniform vec4 u_Colour;

void main() 
{ 
	fragmentColor = u_Colour;
}