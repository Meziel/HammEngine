#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

out vec4 vertexWorldPosition;
out vec4 vertexColor;
out vec3 vertexNormal;

void main()
{
	vertexWorldPosition = model * vec4(vPosition, 1.0);
	gl_Position = projection * view * model * vec4(vPosition, 1.0);
    // Use normal matrix to convert normal vector to world space
	vertexNormal = mat3(transpose(inverse(model))) * vNormal;
	vertexColor = color; // set the output variable to a dark-red color
}