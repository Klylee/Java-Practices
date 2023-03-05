#shader vertex
#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
out vec4 o_color;
void main()
{
    gl_Position = position;
    o_color = color;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 fragment_color;
in vec4 o_color;
void main()
{
    fragment_color = o_color;
};
