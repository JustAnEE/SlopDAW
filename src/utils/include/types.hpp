#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

#define REAL ((ULONG)(0))
#define IMAG ((ULONG)(1))


// !TODO: Use fixed bit width integer types.
typedef unsigned int ULONG;
typedef unsigned short USHORT;
typedef unsigned char UCHAR;
typedef int LONG;
typedef short SHORT;
typedef char CHAR;

typedef bool BOOL;
#define TRUE (BOOL(1))
#define FALSE (BOOL(0))

typedef float FLOAT;
typedef double DOUBLE;

typedef std::string STRING;


#endif 
