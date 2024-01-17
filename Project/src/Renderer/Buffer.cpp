//
// Created by ianpo on 20/07/2023.
//

#include "Renderer/Buffer.hpp"
#include "glad/glad.h"
namespace PC {

    VertexBuffer::VertexBuffer(uint32_t size, const void* vertices) {
        // PC_PROFILE_FUNCTION();
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        // TODO: abstract the GL_STATIC_DRAW to have it as a param.
        glBufferData(GL_ARRAY_BUFFER, (long)size, vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Bind() const {
        // PC_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const {
        // PC_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBuffer::~VertexBuffer() {
        // PC_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }

    IndexBuffer::IndexBuffer(uint32_t count, const uint32_t *indices) : m_Count(count) {
        // PC_PROFILE_FUNCTION();
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        // TODO: abstract the GL_STATIC_DRAW to have it as a param.
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Bind() const {
        // PC_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::Unbind() const {
        // PC_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    IndexBuffer::~IndexBuffer() {
        // PC_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }
} // VoxymoreCore