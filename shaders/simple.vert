#version 450

layout(binding = 0) uniform UBO {
    mat4 M;
    mat4 V;
    mat4 P;
} ubo;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = ubo.P * ubo.V * ubo.M * vec4(position, 1.0);
    fragColor = color;
}
