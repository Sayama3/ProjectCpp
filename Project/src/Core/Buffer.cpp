//
// Created by ianpo on 06/07/2024.
//

#include "Core/Buffer.hpp"
#include <cstdlib>
#include <cstring>

Buffer::Buffer(void * data, uint64_t size) : Data((uint8_t*)data), Size(size)
{
}

Buffer::Buffer(uint64_t size)
{
   Allocate(size);
}

void Buffer::Allocate(uint64_t size)
{
   Release();

   Data = (uint8_t*)malloc(size);
   Size = size;
}

void Buffer::Release()
{
   free(Data);
   Data = nullptr;
   Size = 0;
}


void Buffer::Clear()
{
   Data = nullptr;
   Size = 0;
}

Buffer Buffer::Copy(const Buffer & other)
{
   Buffer buff(other.Size);
   memcpy(buff.Data, other.Data, other.Size);
   return buff;
}

ScopeBuffer::ScopeBuffer()
{
}

ScopeBuffer::ScopeBuffer(void* ptr, uint64_t size) : buffer(ptr, size)
{

}
ScopeBuffer::ScopeBuffer(uint64_t size) : buffer(size)
{

}

ScopeBuffer::ScopeBuffer(Buffer&& buffer) : buffer(buffer)
{
   buffer.Clear();
}

ScopeBuffer::ScopeBuffer(Buffer& buffer) : buffer(buffer)
{
   buffer.Clear();
}

void ScopeBuffer::Replace(Buffer&& buff)
{
   buffer.Release();
   buffer = buff;
   buff.Clear();
}

void ScopeBuffer::Replace(Buffer& buff)
{
   buffer.Release();
   buffer = buff;
   buff.Clear();
}


void ScopeBuffer::Replace(void* ptr, uint64_t size)
{
   buffer.Release();
   buffer.Data = static_cast<uint8_t *>(ptr);
   buffer.Size = size;
}

ScopeBuffer::~ScopeBuffer()
{
   buffer.Release();
}
