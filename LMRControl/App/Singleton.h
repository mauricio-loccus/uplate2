#ifndef LMESINGLETON_H
#define LMESINGLETON_H

#include <boost/smart_ptr.hpp>
#include <assert.h>

template <class T>
class SingletonPattern
{
	public:
		static T* instance()
		{
			if (!m_pInstance.get())
				m_pInstance.reset(new T());

			assert(m_pInstance.get() != NULL);

			return m_pInstance.get();
		}

		template<typename P> static T* instance(P *p)
		{
			if (!m_pInstance.get())
				m_pInstance.reset(new T(p));

			assert(m_pInstance.get() != NULL);

			return m_pInstance.get();
		}

	private:
		SingletonPattern() {}
		~SingletonPattern() {}

	private:
		static boost::shared_ptr<T> m_pInstance;

		SingletonPattern(SingletonPattern const&) {}
		SingletonPattern& operator = (SingletonPattern const&) {};
};

#include "Singleton.inl"

#endif // SINGLETONPATTERN_H


