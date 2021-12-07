/** \file bufferLayout.h */
#pragma once

#include "shaderDataType.h"
#include <vector>

namespace Engine
{
	/**\ 
	\class VertexBufferElement
	 A class which holds data about a single element in a vertex buffer layout
	 */
	class VertexBufferElement
	{
	public:
		ShaderDataType m_dataType; //!< Data Type 
		uint32_t m_size; //!< Size of the Element
		uint16_t m_offset; //!< Offset of the Element
		bool m_normalised; //!< is it Normalised?

		VertexBufferElement() {} //!< Default Constructor 
		VertexBufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType),
			m_size(SDT::size(dataType)),
			m_offset(0),
			m_normalised(normalised)
		{} //!< Constructor with parameters 
	};

	/**\
	\class UniformElement
	 A class which holds data about a single element in a uniform buffer layout
	 */
	class UniformBufferElement
	{
	public:
		const char* m_name;
		ShaderDataType m_dataType; //!< Data Type 
		uint32_t m_size; //!< Size of the Element
		uint16_t m_offset; //!< Offset of the Element

		UniformBufferElement() {} //!< Default Constructor 
		UniformBufferElement(const char * name, ShaderDataType dataType) :
			m_name(name),
			m_dataType(dataType),
			m_size(SDT::std140alignment(dataType)),
			m_offset(0)
	
		{} //!< Constructor with parameters 
	};


	/**\
	\class BufferLayout
	 Abstraction of the notion of a buffer layout 
	 */
	template <class G>
	class BufferLayout
	{
	public:
		BufferLayout<G>() {};
		BufferLayout<G>(const std::initializer_list<G>& element) : m_elements(element) { calcStrideAndOffset(); }
		inline uint32_t getStride() const { return m_stride; }
		void addElement(G element);
		inline typename std::vector<G>::iterator begin() { return m_elements.begin(); }
		inline typename std::vector<G>::iterator end() { return m_elements.end(); }
		inline typename std::vector<G>::const_iterator begin() const { return m_elements.begin(); }
		inline  typename std::vector<G>::const_iterator end() const { return m_elements.end(); }
		

	private:
		std::vector<G> m_elements; //!< Buffer elements 
		uint32_t m_stride; //!< width is bytes of a buffer line 
		void calcStrideAndOffset(); //!< Caluclate stride and offset based on elements 
	};

	template <class G>
	void BufferLayout<G>::addElement(G element)
	{
		m_elements.push_back(element);
		calcStrideAndOffset();
	}

	template <class G>
	void BufferLayout<G>::calcStrideAndOffset()
	{
		uint32_t l_offset = 0;

		for (auto& element : m_elements)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		}

		m_stride = l_offset;
	}

	using VertexBufferLayout = BufferLayout<VertexBufferElement>;
	using UniformBufferLayout = BufferLayout<UniformBufferElement>;
	/*void BufferLayout::addElement(BufferElement element)
	{
		m_elements.push_back(element);
		calcStrideAndOffset();
	}
	
	void BufferLayout::calcStrideAndOffset()
	{
		uint32_t l_offset = 0;

		for (auto& element : m_elements)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		}

		m_stride = l_offset;
	}*/
}
