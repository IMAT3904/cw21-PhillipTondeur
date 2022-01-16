/*\file indexBuffer.h*/

#pragma once

#include <cstdint>

namespace Engine
{

	/* \class IndexBuffer
	* API agnostic index buffer
	*/
	class IndexBuffer 
	{
	public:
		virtual ~IndexBuffer() = default;
		virtual inline uint32_t getID() const = 0;
		virtual inline uint32_t getCount() const = 0;

		static IndexBuffer* create(uint32_t* indices, uint32_t count);
		
	};
	
}