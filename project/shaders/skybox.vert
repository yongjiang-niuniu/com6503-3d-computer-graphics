#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    
    // 关键技巧：把 Z 设为 W，这样透视除法后 Z=1.0 (最大深度)
    // 确保天空永远在所有物体后面
    gl_Position = pos.xyww;
}