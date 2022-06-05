#version 330 core
out vec4 FragColor;
  
in vec3 vertexWorldPosition;
in vec4 vertexColor;
in vec3 vertexNormal;

// Lights
uniform vec3 ambient;

// Temp light uniforms
uniform vec3 lightWorldPosition;
uniform vec4 lightDiffuseColor;

void main()
{
    vec3 normal = normalize(vertexNormal);
    vec3 lightDirection = normalize(lightWorldPosition - vertexWorldPosition);
    vec4 diffuse = max(dot(normal, lightDirection), 0.0) * lightDiffuseColor;
    FragColor = (vec4(ambient, 1.0) + diffuse) * vertexColor;
}