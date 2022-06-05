#version 330 core
layout (location = 0) in vec3 vPosition;

uniform mat4 mvp;

out vec4 vertexColor;

void main()
{
	gl_Position = mvp * vec4(vPosition, 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}