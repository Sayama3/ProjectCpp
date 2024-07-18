//
// Created by ianpo on 18/07/2024.
//

#pragma once

#include <string>
#include <cstdint>

namespace PC {

	class Window {
	public:
		Window(std::string name, uint32_t width, uint32_t height);
		~Window();
		Window(const Window &) = delete;
		Window &operator=(const Window &) = delete;

	public:
		explicit operator bool() { return m_NativeWindow; }

	public:
		[[nodiscard]] bool ShouldClose() const;
		void Close();
		void SwapBuffer();
		[[nodiscard]] uint32_t GetWidth() const;
		[[nodiscard]] uint32_t GetHeight() const;

	public:
		template<typename T>
		[[nodiscard]] T *GetNative() { return reinterpret_cast<T *>(m_NativeWindow); }
		template<typename T>
		[[nodiscard]] const T *GetNative() const { return reinterpret_cast<T *>(m_NativeWindow); }
		[[nodiscard]] void *GetRawNative() { return m_NativeWindow; }
		[[nodiscard]] const void *GetRawNative() const { return m_NativeWindow; }

	private:
		std::string m_Name;
		uint32_t m_Width, m_Height;
		void *m_NativeWindow = nullptr;
	};
}