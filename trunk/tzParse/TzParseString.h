/*
File created by Salomon BRYS : salomon . brys @ gmail . com
This file is under TzLicence which is a MPL / LGPL / GPL Licence
with some simple restrictions.
YOU MUST NOT USE THIS FILE FOR ANY COMERCIAL USE WITHOUT THE
PERMISSION OF IT'S AUTHOR.
*/


#ifndef	P_STRING_H__
#define	P_STRING_H__

#include "crtdbg.h"

#define	P_CONCAT2(a, b)												a b
#define	P_CONCAT3(a, b, c)											a b c
#define	P_CONCAT4(a, b, c, d)										a b c d
#define	P_CONCAT5(a, b, c, d, e)									a b c d e
#define	P_CONCAT6(a, b, c, d, e, f, g)								a b c d e f g
#define	P_CONCAT7(a, b, c, d, e, f, g, h)							a b c d e f g h
#define	P_CONCAT8(a, b, c, d, e, f, g, h, i)						a b c d e f g h i
#define	P_CONCAT9(a, b, c, d, e, f, g, h, i, j)						a b c d e f g h i j
#define	P_CONCAT10(a, b, c, d, e, f, g, h, i, j, k)					a b c d e f g h i j k
#define	P_CONCAT11(a, b, c, d, e, f, g, h, i, j, k, l)				a b c d e f g h i j k l
#define	P_CONCAT12(a, b, c, d, e, f, g, h, i, j, k, l, m)			a b c d e f g h i j k l m
#define	P_CONCAT13(a, b, c, d, e, f, g, h, i, j, k, l, m, n)		a b c d e f g h i j k l m n
#define	P_CONCAT14(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o)		a b c d e f g h i j k l m n o
#define	P_CONCAT15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)	a b c d e f g h i j k l m n o p

#define	P_HT		"\t"
#define	P_SP		" "
#define	P_LBLANKS	P_HT P_SP

#define	P_CR		"\r"
#define	P_LF		"\n"
#define	P_CRLF		P_CR P_LF
#define	P_NL		P_CRLF

#define	P_BLANKS	P_LBLANKS P_CRLF

#define	P_UPALPHA	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define	P_LOALPHA	"abcdefghijklmnopqrstuvwxyz"
#define	P_ALPHA		P_UPALPHA P_LOALPHA

#define	P_NUM		"0123456789"
#define	P_DIGIT		P_NUM

#define	P_ALPHANUM	P_ALPHA P_NUM

#define	P_CTL			"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"	\
					"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"	\
					"\x7F"

#define	P_TEXT		"\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"	\
					"\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F"	\
					"\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F"	\
					"\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F"	\
					"\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F"	\
					"\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E"

#define	P_CHAR		P_CTL P_TEXT

#define	P_HEX		"ABCDEF" P_NUM

#endif	// !P_STRING_H__
