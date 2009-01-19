#ifndef	__SO_AUTO_PTR_H__
#define	__SO_AUTO_PTR_H__

namespace SoUtil
{
	template<typename R, typename V>
	class SelfArithmeticOpOverload
	{
	public:
		template<typename C>
		R&	operator += (const C a) { getV() += a; return *this; }
		template<typename C>
		R&	operator -= (const C a) { getV() -= a; return *this; }
		template<typename C>
		R&	operator *= (const C a) { getV() *= a; return *this; }
		template<typename C>
		R&	operator /= (const C a) { getV() /= a; return *this; }
		template<typename C>
		R&	operator %= (const C a) { getV() %= a; return *this; }

		R&	operator ++ (void) { ++getV(); return *this; }
		R&	operator -- (void) { --getV(); return *this; }

	protected:
		virtual V&	getV() = 0;
	};

	template<typename V>
	class ArithmeticOpOverload
	{
		template<typename C>
		V	operator + (const C a) const { return getV() + a; }
		template<typename C>
		V	operator - (const C a) const { return getV() - a; }
		template<typename C>
		V	operator * (const C a) const { return getV() * a; }
		template<typename C>
		V	operator / (const C a) const { return getV() / a; }
		template<typename C>
		V	operator % (const C a) const { return getV() % a; }

	protected:
		virtual V const &	getV() const = 0;
	};

	template<typename V>
	class ComparisonOpOverload
	{
	public:
		template<typename C>
		bool	operator == (const C& v) const { return (getV() == v); }
		template<typename C>
		bool	operator <  (const C& v) const { return (getV() < v); }
		template<typename C>
		bool	operator >  (const C& v) const { return (getV() > v); }
		template<typename C>
		bool	operator >= (const C& v) const { return (getV() >= v); }

	protected:
		virtual V const &	getV() const = 0;
	};

	template<typename T>
	class AutoPtr : public SelfArithmeticOpOverload<AutoPtr<T>, T*>, public ArithmeticOpOverload<T*>, public ComparisonOpOverload<T*>
	{
	public:
		AutoPtr() : ptr(0), n(0), ptrDel(true) {}
		AutoPtr(T* p) : ptrDel(true) { set(p); }
		AutoPtr(T& p) : ptrDel(false) { set(&p); }
		AutoPtr(const AutoPtr& ap) { clone(ap); }
		virtual ~AutoPtr() { del(); }

		AutoPtr<T>&	operator =  (const AutoPtr& ap) { del(); if (&ap != this) clone(ap); return *this; }
		AutoPtr<T>&	operator =  (T* p) { del(); set(p); return *this; }
// !!! This line has been especially removed for this project !!!
//		T&			operator *  (void) const { return *ptr; }
		T*			operator -> (void) const { return ptr;  }

		operator T*  (void) { return ptr; }
		operator int (void) { return (int)ptr; }

		int			getCount(void) const { return *n; }
		T*			getPtr(void) const { return ptr; }

		void		set(T* p) { ptr = p; n = new int(1); }

		void		release(void) { ptrDel = false; };

	protected:
		void		clone(const AutoPtr& ap) { ptr = ap.ptr; n = ap.n; if (n) ++(*n); ptrDel = ap.ptrDel; }
		void		del(void) { if (n && --(*n) == 0) { if (ptrDel) delete ptr; delete n; } n = 0; ptr = 0; }

		T*&			getV()       { return ptr; }
		T* const &	getV() const { return ptr; }

	private:
		T*			ptr;
		int*		n;
		bool		ptrDel;
	};
}

#endif	// !__SO_AUTO_PTR_H__
