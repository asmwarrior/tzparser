/*
Copyright (c) 2008 Salomon BRYS

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


*/

#ifndef	AUTO_PTR_H__
#define	AUTO_PTR_H__

#include <iostream>

#include "win32_crtdbg.h"

template<typename T>
class AutoPtr
{
public:
	AutoPtr() : ptr(0), n(0), ptrDel(true) {}
	AutoPtr(T* p) : ptrDel(true) { set(p); }
	AutoPtr(T& p) : ptrDel(false) { set(&p); }
	AutoPtr(const AutoPtr& ap) { clone(ap); }
	virtual ~AutoPtr() { del(); }

	AutoPtr&	operator =   (const AutoPtr& ap) { del(); if (&ap != this) clone(ap); return *this; }
	AutoPtr&	operator =   (T* p) { del(); set(p); return *this; }
	T&			operator *   (void) const { return *ptr; }
	T*			operator ->  (void) const { return ptr;  }
	bool		operator ==  (const T* p) const { return (p == ptr); }
	bool		operator ==  (const AutoPtr& ap) const { return (ap.ptr == ptr); }
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

template<typename T, T def>
class	AutoInit
{
public:
	AutoInit() : val(def) {}

	T&			operator *  (void) { return val; }
	T*			operator -> (void) { return &val; }

private:
	T	val;
};

template<typename T>
class	AutoInitNull
{
public:
	AutoInitNull() : val(0) {}

	T&			operator *  (void) { return val; }
	T*			operator -> (void) { return &val; }

private:
	T	val;
};



#endif	// !AUTO_PTR_H__
