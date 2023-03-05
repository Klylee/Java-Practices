#include "pch.h"
#include "ItemBuffer.h"

void ItemBuffer::SetVertexBuffer(const void* data, unsigned int size)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); 
}

void ItemBuffer::SetIndexBuffer(const unsigned int* data, unsigned int count)
{
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void ItemBuffer::BindVertexBuffer()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void ItemBuffer::BindIndexBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void ItemBuffer::UnbindVertexBuffer()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ItemBuffer::UnbindIndexBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ItemBuffer::SetVertexBufferLayout(VertexBufferLayout vblayout)
{
    unsigned int offset = 0;
    std::vector<VertexElementLayout> elements = vblayout.elements;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        //don't forget to call enable before set vertex attribute pointer
        glEnableVertexAttribArray(i);
        //tell the structure of the given data
        //std::cout << i << " " << elements[i].count << " " << vblayout.stride << " " << offset << std::endl;
        glVertexAttribPointer(i, elements[i].count, elements[i].type,
            elements[i].normalized, vblayout.stride, (const void*)(offset * sizeof(float)));
        offset += elements[i].count;
    }
}

void ItemBuffer::SetBuffer(const Item &item)
{
    count = item.indices_count;
    SetVertexBuffer(item.vertex_position, item.vertexes_count * sizeof(float));
    SetIndexBuffer(item.indices, item.indices_count);
    SetVertexBufferLayout(item.layout);
}

void ItemBuffer::BindBuffer()
{
    BindVertexBuffer();
    BindIndexBuffer();
}

void ItemBuffer::UnbindBuffer()
{
    UnbindVertexBuffer();
    UnbindIndexBuffer();
}

void ItemBuffer::drawBuffer()
{
    BindBuffer();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}
