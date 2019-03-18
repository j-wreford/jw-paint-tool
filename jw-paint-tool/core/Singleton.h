#pragma once

//
// Singleton
//
// A template base class to provide singleton implementation to 
// derived classes.
//
// Derived classes will need to declair Singleton<T> as a friend so that it may
// instantiate it using its private constructor.
//

namespace paint_tool {

	template <class T>
	class Singleton {
	public:

		static inline T *getInstance();
		static inline void destroyInstance();

	protected:

		Singleton();
		virtual ~Singleton();

	private:

		static T *instance;
	};

	template<class T>
	T *Singleton<T>::instance = nullptr;

	template <class T>
	Singleton<T>::Singleton() {
		//
	}

	template <class T>
	Singleton<T>::~Singleton() {
		//
	}

	template <class T>
	T* Singleton<T>::getInstance() {

		if (instance == nullptr)
			instance = new T();

		return instance;
	}

	template <class T>
	void Singleton<T>::destroyInstance() {

		if (instance == nullptr)
			return;

		instance->~T();
		delete instance;
	}
}
