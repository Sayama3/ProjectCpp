//
// Created by ianpo on 20/07/2023.
//

#pragma once

#include "Core/Macros.hpp"
#include "Core/Logger.hpp"
#include "Core/SmartPointers.hpp"
#include "Renderer/Buffer.hpp"

namespace PC {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

        inline const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
    private:
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
        uint32_t m_RendererID;
    };

} // Core
