#pragma once

#include "bufferLayout.h"
#include <cstdint>

namespace Engine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		static VertexBuffer* create(void* vertices, uint32_t size, const BufferLayout layout);

		virtual inline uint32_t getID() const = 0;
		virtual const BufferLayout& getLayout() const = 0;

		virtual void edit(void* vertices, uint32_t size, int32_t offset) = 0;
	private:

	};
}