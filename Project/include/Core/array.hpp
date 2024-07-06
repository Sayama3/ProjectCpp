//
// Created by ianpo on 03/03/2024.
//

#pragma once

#include <cinttypes>
#include <stdexcept>

namespace vxm {

	template<typename T, typename sizeT, sizeT Capacity>
	class array {
	public:
		array() = default;
		~array() = default;
		array(sizeT size);
		array(sizeT size, T defaultValue);

		T& operator[](sizeT index);
		const T& operator[](sizeT index) const;

		T& at(sizeT index);
		const T& at(sizeT index) const;

		inline sizeT size() const {return count;}
		inline sizeT capacity() const {return Capacity;}

		void push_back(const T& value);
		T pop_back();

		void resize(sizeT size);
		void resize(sizeT size, T defaultValue);

		void clear();



		T* data();
	private:
		T buffer[Capacity];
		sizeT count = 0;
	};
	template<typename T, typename sizeT, sizeT Capacity>
	array<T, sizeT, Capacity>::array(sizeT size) : count(size)
	{
		if (size > Capacity) {
			throw std::out_of_range("Size is greater than the capacity of the array.");
		}
	}

	template<typename T, typename sizeT, sizeT Capacity>
	array<T, sizeT, Capacity>::array(sizeT size, T defaultValue) : count(size)
	{
		if (size > Capacity) {
			throw std::out_of_range("Size is greater than the capacity of the array.");
		}

		for (int i = 0; i < count; ++i) {
			buffer[i] = defaultValue;
		}
	}

	template<typename T, typename sizeT, sizeT Capacity>
	const T &array<T, sizeT, Capacity>::operator[](sizeT index) const {
		return buffer[index];
	}

	template<typename T, typename sizeT, sizeT Capacity>
	T &array<T, sizeT, Capacity>::operator[](sizeT index) {
		return buffer[index];
	}

	template<typename T, typename sizeT, sizeT Capacity>
	const T &array<T, sizeT, Capacity>::at(sizeT index) const {
		if(index > count)
		{
			throw std::out_of_range("Index is not in the bounds of the array.");
		}
		return  buffer[index];
	}

	template<typename T, typename sizeT, sizeT Capacity>
	T &array<T, sizeT, Capacity>::at(sizeT index) {
		if(index > count)
		{
			throw std::out_of_range("Index is not in the bounds of the array.");
		}
		return  buffer[index];
	}

	template<typename T, typename sizeT, sizeT Capacity>
	void array<T, sizeT, Capacity>::push_back(const T &value)
	{
		if (count >= Capacity) {
			throw std::out_of_range("Array is already at maximum capacity.");
		}
		buffer[count++] = value;
	}

	template<typename T, typename sizeT, sizeT Capacity>
	T array<T, sizeT, Capacity>::pop_back() {
		if (count == 0) {
			throw std::out_of_range("Array is empty.");
		}
		T value = buffer[--count];
		return value;
	}

	template<typename T, typename sizeT, sizeT Capacity>
	void array<T, sizeT, Capacity>::resize(sizeT size) {
		if (size > Capacity) {
			throw std::out_of_range("New size is greater than the capacity of the array.");
		}
		count = size;
	}

	template<typename T, typename sizeT, sizeT Capacity>
	void array<T, sizeT, Capacity>::resize(sizeT size, T defaultValue) {
		if (size > Capacity) {
			throw std::out_of_range("New size is greater than the capacity of the array.");
		}

		for (sizeT i = count; i < size; i++) {
			buffer[i] = defaultValue;
		}

		count = size;
	}

	template<typename T, typename sizeT, sizeT Capacity>
	void array<T, sizeT, Capacity>::clear() {
		count = 0;
	}

	template<typename T, typename sizeT, sizeT Capacity>
	T *array<T, sizeT, Capacity>::data() {
		return buffer;
	}


	typedef array<uint8_t, uint8_t, 4> pxArray;
} // vxm
