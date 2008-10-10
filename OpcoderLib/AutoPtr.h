#ifndef	__SO_AUTO_PTR_H__
#define	__SO_AUTO_PTR_H__

namespace SoUtil
{
	template<typename T>
	class AutoPtr
	{
	public:
		AutoPtr() : ptr(0), n(0), ptrDel(true) {}
		AutoPtr(T* p) : ptrDel(true) { set(p); }
		AutoPtr(T& p) : ptrDel(false) { set(&p); }
		AutoPtr(const AutoPtr& ap) { clone(ap); }
		virtual ~AutoPtr() { del(); }

		AutoPtr&	operator =  (const AutoPtr& ap) { del(); if (&ap != this) clone(ap); return *this; }
		AutoPtr&	operator =  (T* p) { del(); set(p); return *this; }
		T&			operator *  (void) const { return *ptr; }
		T*			operator -> (void) const { return ptr;  }
		bool		operator == (const T* p) const { return (p == ptr); }
		bool		operator == (const AutoPtr& ap) const { return (ap.ptr == ptr); }
		operator T*  (void) { return ptr; }
		operator int (void) { return (int)ptr; }

		int			getCount(void) const { return *n; }
		T*			getPtr(void) const { return ptr; }

		void		set(T* p) { ptr = p; n = new int(1); }

		void		release(void) { ptrDel = false; };

	protected:
		void		clone(const AutoPtr& ap) { ptr = ap.ptr; n = ap.n; if (n) ++(*n); ptrDel = ap.ptrDel; }
		void		del(void) { if (n && --(*n) == 0) { if (ptrDel) delete ptr; delete n; } n = 0; ptr = 0; }

	private:
		T*			ptr;
		int*		n;
		bool		ptrDel;
	};
}

#endif	// !__SO_AUTO_PTR_H__
