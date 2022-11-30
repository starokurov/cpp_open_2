#pragma once

#include <iostream>
#include <vector>

template<typename T>
struct MyVector {
	explicit MyVector(const std::initializer_list<T>& values)
		: m_data(values)
	{}

	MyVector(const MyVector& other)
		: m_data{other.m_data}
	{}

	MyVector(MyVector&& other) noexcept	
		: m_data{std::move(other.m_data)}
	{}
	
	MyVector& operator=(const MyVector& rhs) {
		m_data = rhs.m_data;
		return *this;
	}

	MyVector& operator=(MyVector&& rhs) noexcept {
		m_data = std::move(rhs.m_data);
		return *this;
	}

	const T& operator[](size_t index) const {
		return m_data[index];
	}

	T& operator[](size_t index) {
		return m_data[index];
	}

	size_t size() const {
		return m_data.size();
	}

private:
	std::vector<T> m_data;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& values) {
	for (size_t i = 0; i < values.size(); ++i) {
		os << values[i] << ' ';
	}
	return os;
}