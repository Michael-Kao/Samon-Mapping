#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 aColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
    aColor = vec3(0.5, 0.5, 0.5);
    if(aPos.z > 0.9)
        aColor = vec3(1.0, 0.0, 0.0);
    else if(aPos.z < 0.1)
        aColor = vec3(0.0, 0.0, 1.0);
}