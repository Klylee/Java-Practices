#pragma once
#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct VertexElementLayout {
    unsigned int count; //refer to size
    unsigned int type;
    unsigned char normalized;
};
struct VertexBufferLayout {
    std::vector<VertexElementLayout> elements;
    unsigned int stride;

    VertexBufferLayout() : stride(0) {}
    ~VertexBufferLayout() {
        //std::cout << "destroy vertex buffer layout" <<std::endl;
    }

    void operator=(const VertexBufferLayout& ly)
    {
        this->stride = ly.stride;
        for (unsigned int i = 0; i < ly.elements.size(); i++)
        {
            this->elements.push_back(ly.elements[i]);
        }
    }

    template<typename> void push(unsigned int count)
    {
        return;
    }
    template<> void push<float>(unsigned int count)
    {
        stride += count * sizeof(float);
        elements.push_back({ count, GL_FLOAT, GL_FALSE });
    }
    template<> void push<unsigned int>(unsigned int count)
    {
        stride += count * sizeof(unsigned int);
        elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
    }
    template<> void push<int>(unsigned int count)
    {
        stride += count * sizeof(int);
        elements.push_back({ count, GL_INT, GL_FALSE });
    }
};

class Item
{
    unsigned int vertexes_count;
    float* vertex_position;

    unsigned int indices_count;
    unsigned int* indices;

    VertexBufferLayout layout;

public:
    friend class ItemBuffer;
    Item() : vertex_position(nullptr), indices(nullptr) {}

    Item(const unsigned int ver_count, const float* vertex_pos, const unsigned int ind_count, const unsigned int* indices,
        const VertexBufferLayout& layout);
    
    ~Item();

    void operator=(const Item& it);
    void showDetail() const;
};

