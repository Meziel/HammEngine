#version 330 core
out vec4 FragColor;
  
in vec4 vertexWorldPosition;
in vec4 vertexColor;
in vec3 vertexNormal;

uniform vec3 ambient;

void main()
{
    FragColor = vec4(0.5, 0.0, 0.0, 1.0); //vec4(ambient, 1.0) * vertexColor;
}