#ifndef TOPKIND_H
#define TOPKIND_H

#include <unordered_map>
#include <map>

/**
* <summary> Enum for the possible operators of the three address code. </summary>
*/
enum class OpKind 
	{
		Add,
		Subtract,
		Multiply,
		Divide,
		IsEqual,
		IsLessEqual,
		IsGreaterEqual,
		IsNotEqual,
		IsLess,
		IsGreater,
		Assign,
		Jump,
		IfFalseJump,
		Print,
		Exit
	};

#endif