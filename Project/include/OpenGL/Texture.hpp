//
// Created by ianpo on 06/07/2024.
//

#pragma once

#include <optional>
#include "Image.hpp"
#include "Core/Buffer.hpp"
#include "OpenGL/TextureSpecification.hpp"



class Texture {
public:
   Texture();
   Texture(const TextureSpecification& spec);
   Texture(const TextureSpecification& spec, Buffer image);
   ~Texture();

   Texture(const Texture&) = delete;
   Texture& operator=(const Texture&) = delete;

   Texture(Texture&&) noexcept;
   Texture& operator=(Texture&&) noexcept;
public:
   [[nodiscard]] virtual uint32_t GetWidth() const;
   [[nodiscard]] virtual uint32_t GetHeight() const;
   [[nodiscard]] virtual uint32_t GetChannels() const;

   void SetData(Buffer data);

   void Bind(uint32_t slot = 0) const;
   void Unbind() const;

   [[nodiscard]] virtual uint32_t GetRenderID() const;
private:
	void CreateTexture();
private:
   TextureSpecification m_Specification{};
   uint32_t m_RenderID{0};
   mutable std::optional<uint32_t> m_Slot{std::nullopt};
};
