// From https://learnopengl.com/#!Getting-started/Textures

#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 objectColor;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(objectColor, 1.0);
}
