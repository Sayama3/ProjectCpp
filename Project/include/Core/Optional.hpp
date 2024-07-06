//
// Created by ianpo on 06/07/2024.
//

#pragma once

#include <memory>

template<typename T, T NullValue>
class Optional {
	template<typename ... Args>
	Optional(Args&& ... args) : m_Value(std::forward<Args>(args)...) {}
	~Optional() = default;

	[[nodiscard]] bool has_value() const noexcept {return m_Value != NullValue;}
	[[nodiscard]] T& value() {return m_Value;}
	[[nodiscard]] const T& value() const {return m_Value;}

	void reset() {m_Value = NullValue;}

	Optional& operator=(T&& other) {m_Value = other; return *this;}

	 operator bool() const noexcept {return has_value();}
private:
	T m_Value;
};
