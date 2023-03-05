#pragma once
#include "Item.h"

class ItemBuffer
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

	unsigned int count;


	void SetVertexBuffer(const void* data, unsigned int size);

	void SetIndexBuffer(const unsigned int* data, unsigned int count);

	void BindVertexBuffer();

	void BindIndexBuffer();

	void UnbindVertexBuffer();

	void UnbindIndexBuffer();

	void SetVertexBufferLayout(VertexBufferLayout vblayout);

public:
	ItemBuffer() :vao(0), vbo(0), ibo(0) {}

	void SetBuffer(const Item &item);

	void BindBuffer();

	void UnbindBuffer();

	void drawBuffer();
};

