#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

// 材质贴图
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

// ============ 灯光参数 ============
uniform vec3 lightPos;      
uniform vec3 lightColor;    
uniform bool lightOn;       

uniform vec3 spotPos;       
uniform vec3 spotDir;       
uniform float spotCutOff;   
uniform bool spotOn;        

uniform vec3 viewPos;

// 🌟 新增：由 main.cpp 控制的“发光模式”开关
uniform bool isLightSource; 

void main()
{
    // 🌟 如果是光源物体（灯泡），直接输出最亮的纯白，不进行后续光照计算
    if(isLightSource) {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0); 
        return; 
    }

    // ============ 下面是常规物体的光照计算 ============
    vec3 texDiff = texture(diffuseMap, TexCoord).rgb;
    vec3 texSpec = texture(specularMap, TexCoord).rgb;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0);

    // 1. 通用光
    if(lightOn) {
        vec3 ambient = 0.1 * texDiff;
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor * texDiff;
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = spec * lightColor * texSpec;
        result += (ambient + diffuse + specular);
    } else {
        result += 0.05 * texDiff; 
    }

    // 2. 聚光灯
    if(spotOn) {
        vec3 sLightDir = normalize(spotPos - FragPos);
        float theta = dot(sLightDir, normalize(-spotDir));
        if(theta > spotCutOff) {       
            float diff = max(dot(norm, sLightDir), 0.0);
            vec3 diffuse = diff * vec3(1.0, 1.0, 0.8) * texDiff; 
            vec3 reflectDir = reflect(-sLightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
            vec3 specular = spec * vec3(1.0, 1.0, 0.8) * texSpec;
            result += (diffuse + specular) * 1.5; 
        }
    }

    FragColor = vec4(result, 1.0);
}