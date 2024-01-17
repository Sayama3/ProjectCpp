//
// Created by ianpo on 20/07/2023.
//

#pragma once

#include "Core/Macros.hpp"
#include "Core/Logger.hpp"
#include "Renderer/Shader.hpp"

namespace PC {
	struct BufferElement{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		inline BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		inline uint32_t GetComponentCount() const
		{
			// PC_PROFILE_FUNCTION();
			return GetShaderDataTypeCount(Type);
		}
	};

	class BufferLayout {
	public:
		inline BufferLayout() : m_Elements(), m_Stride(0) {}
		inline BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements), m_Stride(0) {
			CalculateOffsetAndStride();
		}

		inline std::vector<BufferElement>::const_iterator begin() const { return GetElements().begin();}
		inline std::vector<BufferElement>::const_iterator end() const { return GetElements().end();}

		inline const std::vector<BufferElement>& GetElements() const {return m_Elements;}
		inline uint32_t GetStride() const { return m_Stride; }

	private:
		inline void CalculateOffsetAndStride() {
			// PC_PROFILE_FUNCTION();
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element:m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};
	
    class VertexBuffer {
        public:
        VertexBuffer(uint32_t size, const void* vertices);
        ~VertexBuffer();
        void Bind() const;
        void Unbind() const;

        inline void SetLayout(const BufferLayout& layout) {m_Layout = layout;}
        inline const BufferLayout& GetLayout() const {return m_Layout;}

        VertexBuffer(const VertexBuffer &) = delete;
        VertexBuffer &operator=(const VertexBuffer &) = delete;

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };
    class IndexBuffer {
    public:
        IndexBuffer(uint32_t count, const uint32_t* indices);
        ~IndexBuffer();
        void Bind() const;
        void Unbind() const;
        inline uint32_t GetCount() const { return m_Count; }
        IndexBuffer(const IndexBuffer &) = delete;
        IndexBuffer &operator=(const IndexBuffer &) = delete;
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };

} // VoxymoreCore
