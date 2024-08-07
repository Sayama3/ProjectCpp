//
// Created by ianpo on 06/07/2024.
//

#pragma once

#include "Core/Logger.hpp"
#include <cstdint>

struct Buffer {
   inline Buffer() = default;
   inline ~Buffer() = default;
   Buffer(void*, uint64_t size);
   Buffer(uint64_t size);

   static Buffer Copy(const Buffer& other);

   void Allocate(uint64_t size);
   void Release();
   void Clear();

   template<typename T>
   T* As()
   {
      PC_ASSERT(Data, "Buffer is empty - has no initialized data.")
      PC_ASSERT(Size >= sizeof(T), "Buffer cannot be cast to {0} - insufficient size. Required size: {1}. Current size: {2}.", typeid(T).name(), sizeof(T), Size);
      return (T*)Data;
   }

   template<typename T>
   const T* As() const
   {
      PC_ASSERT(Data, "Buffer is empty - has no initialized data.")
      PC_ASSERT(Size >= sizeof(T), "Buffer cannot be cast to {0} - insufficient size. Required size: {1}. Current size: {2}.", typeid(T).name(), sizeof(T), Size);
      return (T*)Data;
   }

   template<typename T>
   T& At(uint64_t index)
   {
      PC_ASSERT(Data, "Buffer is empty - has no initialized data.")
      PC_ASSERT(Size >= (index+1) * sizeof(T), "Cannot access index {0} for type {1}. Buffer size: {2}. Required size: {3}.",
                      index,
                      typeid(T).name(),
                      Size,
                      (index+1) * sizeof(T));
      return ((T*)Data)[index];
   }

   template<typename T>
   const T& At(uint64_t index) const
   {
      PC_ASSERT(Data, "Buffer is empty - has no initialized data.");
      PC_ASSERT(Size >= (index+1) * sizeof(T), "Cannot access index {0} for type {1}. Buffer size: {2}. Required size: {3}.",
                      index,
                      typeid(T).name(),
                      Size,
                      (index+1) * sizeof(T));
      return ((T*)Data)[index];
   }

   uint8_t* Data = nullptr;
   uint64_t Size = 0;
};

struct ScopeBuffer {
   ScopeBuffer();
   ScopeBuffer(void*, uint64_t size);
   ScopeBuffer(uint64_t size);
   // Will take and clear the buffer given in parameters.
   ScopeBuffer(Buffer&& buffer);
   // Will take and clear the buffer given in parameters.
   ScopeBuffer(Buffer& buffer);

   // Will take and clear the buffer given in parameters.
   void Replace(Buffer&& buff);
   // Will take and clear the buffer given in parameters.
   void Replace(Buffer& buff);

   void Replace(void* ptr, uint64_t size);

   template<typename T>
   T* As()
   {
      return buffer.As<T>();
   }

   template<typename T>
   const T* As() const
   {
      return buffer.As<T>();
   }

   ~ScopeBuffer();
private:
   Buffer buffer;
};