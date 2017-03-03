#version 450 core

vec2 pos[4] = vec2[4](vec2(-1, -1), vec2(-1, 1), vec2(1, -1), vec2(1, 1));

layout(location = 0) out vec2 clipSpace;

void main() {
    gl_Position = vec4(pos[gl_VertexID], 1.0, 1.0);
    clipSpace = gl_Position.xy;
}
