//
// Created by ianpo on 06/07/2024.
//

#include "OpenGL/Texture.hpp"
#include "Core/Profiler.hpp"
#include <glad/glad.h>

class TexSpecHelper
{
private:
	TextureSpecification& spec;

public:
	TexSpecHelper(TextureSpecification& specification) : spec(specification) {}
	~TexSpecHelper() = default;

	[[nodiscard]] GLenum GetInternalFormat() const
	{
		PC_PROFILE_FUNCTION();
		switch (spec.pixelFormat) {
			case RED:
			{
				switch (spec.pixelType) {
					case PX_8: return GL_R8;
					case PX_16: return GL_R16;

					case PX_8UI: return GL_R8UI;
					case PX_16UI: return GL_R16UI;
					case PX_32UI: return GL_R32UI;

					case PX_8I: return GL_R8I;
					case PX_16I: return GL_R16I;
					case PX_32I: return GL_R32I;

					case PX_16F: return GL_R16F;
					case PX_32F: return GL_R32F;
				}
			}
			case RG:
			{
				switch (spec.pixelType) {
					case PX_8: return GL_RG8;
					case PX_16: return GL_RG16;

					case PX_8UI: return GL_RG8UI;
					case PX_16UI: return GL_RG16UI;
					case PX_32UI: return GL_RG32UI;

					case PX_8I: return GL_RG8I;
					case PX_16I: return GL_RG16I;
					case PX_32I: return GL_RG32I;

					case PX_16F: return GL_RG16F;
					case PX_32F: return GL_RG32F;
				}
			}
			case RGB:
			{
				switch (spec.pixelType) {
					case PX_8: return GL_RGB8;
					case PX_16: return GL_RGB16;

					case PX_8UI: return GL_RGB8UI;
					case PX_16UI: return GL_RGB16UI;
					case PX_32UI: return GL_RGB32UI;

					case PX_8I: return GL_RGB8I;
					case PX_16I: return GL_RGB16I;
					case PX_32I: return GL_RGB32I;

					case PX_16F: return GL_RGB16F;
					case PX_32F: return GL_RGB32F;
				}
			}
			case RGBA:
			{
				switch (spec.pixelType) {
					case PX_8: return GL_RGBA8;
					case PX_16: return GL_RGBA16;

					case PX_8UI: return GL_RGBA8UI;
					case PX_16UI: return GL_RGBA16UI;
					case PX_32UI: return GL_RGBA32UI;

					case PX_8I: return GL_RGBA8I;
					case PX_16I: return GL_RGBA16I;
					case PX_32I: return GL_RGBA32I;

					case PX_16F: return GL_RGBA16F;
					case PX_32F: return GL_RGBA32F;
				}
			}
		}

		PC_WARNING("No valid internal format found. Defaulting to GL_R8.");
		return GL_R8;
	}

	[[nodiscard]] GLenum GetFormat() const
	{
		PC_PROFILE_FUNCTION();
		switch (spec.pixelFormat) {
			case RED: return GL_RED;
			case RG: return GL_RG;
			case RGB: return GL_RGB;
			case RGBA: return GL_RGBA;
		}

		PC_ERROR("The pixel format {0} do not exist... Returning RGBA", (int)spec.pixelFormat);
		return GL_RGBA;
	}

	[[nodiscard]] GLenum GetType() const
	{
		PC_PROFILE_FUNCTION();
		switch (spec.pixelType) {
			case PX_8: return GL_UNSIGNED_BYTE;
			case PX_16: return GL_UNSIGNED_SHORT;
			case PX_8UI: return GL_UNSIGNED_BYTE;
			case PX_16UI: return GL_UNSIGNED_SHORT;
			case PX_32UI: return GL_UNSIGNED_INT;
			case PX_8I: return GL_BYTE;
			case PX_16I: return GL_SHORT;
			case PX_32I: return GL_INT;
			case PX_16F: return GL_HALF_FLOAT;
			case PX_32F: return GL_FLOAT;
		}

		PC_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
		return GL_UNSIGNED_BYTE;
	}

	[[nodiscard]] std::string_view GetTypeToString() const
	{
		PC_PROFILE_FUNCTION();
		switch (spec.pixelType) {
			case PX_8: return "PX_8";
			case PX_16: return "PX_16";
			case PX_8UI: return "PX_8UI";
			case PX_16UI: return "PX_16UI";
			case PX_32UI: return "PX_32UI";
			case PX_8I: return "PX_8I";
			case PX_16I: return "PX_16I";
			case PX_32I: return "PX_32I";
			case PX_16F: return "PX_16F";
			case PX_32F: return "PX_32F";
		}

		PC_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
		return "Unknown";
	}

	[[nodiscard]] uint32_t GetPixelSize() const {
		PC_PROFILE_FUNCTION();
		switch (spec.pixelType) {
			case PX_8:
			case PX_8UI:
			case PX_8I:
				return 1U;
			case PX_16:
			case PX_16UI:
			case PX_16I:
			case PX_16F:
				return 2U;
			case PX_32UI:
			case PX_32I:
			case PX_32F:
				return 4U;
		}

		PC_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
		return 1U;
	}

	[[nodiscard]] GLint GetMagFilter() const
	{
		PC_PROFILE_FUNCTION();
		switch (spec.filterMag) {

			case Nearest: return GL_NEAREST;
			case Linear: return GL_LINEAR;
		}
		PC_WARNING("No value found for MagFilter, defaulting to 'Linear'.");
		return GL_LINEAR;
	}

	[[nodiscard]] GLint GetMinFilter() const
	{
		PC_PROFILE_FUNCTION();
		switch (spec.filterMin) {

			case Nearest: return GL_NEAREST;
			case Linear: return GL_LINEAR;
		}
		PC_WARNING("No value found for MinFilter, defaulting to 'Linear'.");
		return GL_LINEAR;
	}

	[[nodiscard]] GLint GetWrapS() const
	{
		PC_PROFILE_FUNCTION();
		switch (spec.wrapperS) {
			case Repeat: return GL_REPEAT;
			case ClampToEdge: return GL_CLAMP_TO_EDGE;
			case MirroredRepeat: return GL_MIRRORED_REPEAT;
		}
		PC_WARNING("No value found for WrapS, defaulting to 'Repeat'.");
		return GL_REPEAT;
	}

	[[nodiscard]] GLint GetWrapT() const
	{
		PC_PROFILE_FUNCTION();
		switch (spec.wrapperT) {
			case Repeat: return GL_REPEAT;
			case ClampToEdge: return GL_CLAMP_TO_EDGE;
			case MirroredRepeat: return GL_MIRRORED_REPEAT;
		}
		PC_WARNING("No value found for WrapT, defaulting to 'Repeat'.");
		return GL_REPEAT;
	}
};

Texture::Texture() {
	CreateTexture();
}

Texture::Texture(const TextureSpecification &spec) : m_Specification(spec) {
	CreateTexture();
}

Texture::Texture(const TextureSpecification &spec, Buffer image) : m_Specification(spec) {
	CreateTexture();
	SetData(image);
}

Texture::~Texture() {
	if(m_Slot) {
		Unbind();
	}

	if (m_RenderID) {
		glDeleteTextures(1, &m_RenderID);
		m_RenderID = 0;
	}
}

Texture::Texture(Texture && other) noexcept : m_Specification(other.m_Specification), m_RenderID(other.m_RenderID), m_Slot(other.m_Slot)
{
	other.m_Specification = {};
	other.m_RenderID = 0;
	other.m_Slot = std::nullopt;
}

Texture &Texture::operator=(Texture && other) noexcept {
	std::swap(m_Specification, other.m_Specification);
	std::swap(m_RenderID, other.m_RenderID);
	std::swap(m_Slot, other.m_Slot);
	return *this;
}

uint32_t Texture::GetWidth() const {
	return 0;
}

uint32_t Texture::GetHeight() const {
	return 0;
}

uint32_t Texture::GetChannels() const {
	return 0;
}

void Texture::Bind(uint32_t slot) const {
	glBindTextureUnit(slot, m_RenderID);
	m_Slot = slot;
}

void Texture::Unbind() const {
	if(m_Slot.has_value()) {
		glBindTextureUnit(m_Slot.value(), 0);
		m_Slot = std::nullopt;
	}
}

uint32_t Texture::GetRenderID() const {
	return m_RenderID;
}

void Texture::CreateTexture() {
	TexSpecHelper helper(m_Specification);


	int width = static_cast<GLsizei>(m_Specification.width);
	int height = static_cast<GLsizei>(m_Specification.height);
	int channels = static_cast<GLsizei>(m_Specification.channels);

	PC_CHECK(m_Specification.channels > 0 && m_Specification.channels < 5, "The number of channel {0} is not handle at the moment.", m_Specification.channels);

	GLenum internalFormat = helper.GetInternalFormat();

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
	glTextureStorage2D(m_RenderID, 1, internalFormat, width, height);

	//TODO: Add parameter on the Texture API to be able to change this type of parameters.
	glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, helper.GetMinFilter());
	glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, helper.GetMagFilter());
	glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_S, helper.GetWrapS());
	glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_T, helper.GetWrapT());
}

void Texture::SetData(Buffer data) {

	PC_PROFILE_FUNCTION();
	TexSpecHelper helper(m_Specification);
	GLenum dataFormat = helper.GetFormat();
	GLenum pixelType = helper.GetType();

	int width = static_cast<GLsizei>(m_Specification.width);
	int height = static_cast<GLsizei>(m_Specification.height);
	int channels = static_cast<GLsizei>(m_Specification.channels);

	PC_ASSERT(width * height * channels * helper.GetPixelSize() == data.Size, "The size of the image ({0}) is different from the information of the texture (width: {1}, height: {2}, channel: {3}, pixelType: '{4}')", data.Size, width, height, channels, helper.GetTypeToString());
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTextureSubImage2D(m_RenderID, 0, 0, 0, width, height, dataFormat, pixelType, data.Data);
	if(m_Specification.generateMipMaps) {
		glGenerateTextureMipmap(m_RenderID);
	}
}