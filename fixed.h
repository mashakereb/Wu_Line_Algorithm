// fixed.h
#pragma once

#define fixed int


inline fixed intToFixed(int value) {
	return (value << 16);
}

inline int fixedToInt(fixed value) {
	if (value < 0) return ((value >> 16) - 1);
	else return (value >> 16);
}


//writes the ratio (a / b) in the format of a fixed-point numbers
inline fixed fracToFixed(int a, int b) {
	return (a << 16) / b;
}

inline float  fractionalPart(fixed a) {

	int  p = a - intToFixed(fixedToInt(a));
	int s = 1 << 16;
	float d = p;
	//if (d / s) throw new int;
	return d / s;
}