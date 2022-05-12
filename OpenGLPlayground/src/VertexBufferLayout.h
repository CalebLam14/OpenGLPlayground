#pragma once

#include <vector>
#include <GL/glew.h>
#include <type_traits>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:             return 4;
		case GL_UNSIGNED_INT:	   return 4;
		case GL_UNSIGNED_BYTE:	   return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(true);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};

template<> inline
void VertexBufferLayout::Push<float>(unsigned int count)
{
	VertexBufferElement element = { GL_FLOAT, count, false };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<> inline
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	VertexBufferElement element = { GL_UNSIGNED_INT, count, false };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<> inline
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	VertexBufferElement element = { GL_UNSIGNED_BYTE, count, true };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
