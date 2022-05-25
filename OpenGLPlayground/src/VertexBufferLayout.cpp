#include "VertexBufferLayout.h"
#include <iostream>

template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
	VertexBufferElement element = { GL_FLOAT, count, false };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	VertexBufferElement element = { GL_UNSIGNED_INT, count, false };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	VertexBufferElement element = { GL_UNSIGNED_BYTE, count, true };
	m_Elements.push_back(element);
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}