#pragma once


template<typename T>
class Use
{
public:

	Use() {
		m_empty = true;
	}
	Use(const Use& right) {
		m_value = right.m_value;
		m_empty = right.m_empty;
	}

	template<typename ...Args>
	Use(Args...args) :m_value(args...) {
		m_empty = false;
	}


	Use& operator = (const Use& right) {
		m_value = right.m_value;
		m_empty = right.m_empty;
		return *this;
	}

	Use& operator = (Use&& right) {
		m_value = std::move(right.m_value);
		m_empty = right.m_empty;
		return *this;
	}

	operator T()const noexcept {
		return m_value;
	}

	operator T* () {
		return &m_value;
	}

	T* operator -> () noexcept {
		return &m_value;
	}

	bool empty()const {
		return m_empty;
	}

private:
	T m_value;
	bool m_empty;
};