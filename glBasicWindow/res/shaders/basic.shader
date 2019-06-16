#ShaderTypeInfo: vertex
#version 330 core
in layout(location=0) vec2 pos;
void main()
{
    gl_Position = vec4(pos, 0.0, 1.0);
}

#ShaderTypeInfo: fragment
#version 330 core
out vec4 result;
void main()
{
    result = vec4(0.3, 0.2, 0.8, 1.0);
}