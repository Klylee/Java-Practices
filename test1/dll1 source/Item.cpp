#include "pch.h"
#include "Item.h"

Item::Item(const unsigned int ver_count, const float* vertex_pos, const unsigned int ind_count, const unsigned int* indices,
    const VertexBufferLayout& layout) :
    vertexes_count(ver_count), indices_count(ind_count), vertex_position(NULL), indices(NULL)
{
    vertex_position = new float[ver_count];
    for (unsigned int i = 0; i < ver_count; i++)
        vertex_position[i] = vertex_pos[i];

    this->indices = new unsigned int[ind_count];
    for (unsigned int i = 0; i < ind_count; i++)
        this->indices[i] = indices[i];

    this->layout = layout;
}

Item::~Item()
{
    if (vertex_position)
        delete vertex_position;
    if (indices)
        delete indices;
}

void Item::operator=(const Item& it)
{
    this->vertexes_count = it.vertexes_count;
    this->indices_count = it.indices_count;
    this->layout = it.layout;

    this->vertex_position = new float[this->vertexes_count];
    for (unsigned int i = 0; i < this->vertexes_count; i++)
        vertex_position[i] = it.vertex_position[i];

    this->indices = new unsigned int[this->indices_count];
    for (unsigned int i = 0; i < this->indices_count; i++)
        this->indices[i] = it.indices[i];
}

void Item::showDetail() const
{
    for (unsigned int i = 0; i < vertexes_count; i++)
        std::cout << vertex_position[i] << " ";
    std::cout << std::endl;
    for (unsigned int i = 0; i < indices_count; i++)
        std::cout << indices[i] << " ";

    std::cout << layout.stride << std::endl;
}
