#pragma once

#include "Buffer.h"

namespace FallingSandEngine
{
	//virtual interface
	class VertexArray
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)  = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)  = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();

	};

	//could make a Index Array class here
}