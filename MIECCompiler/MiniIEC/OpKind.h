#ifndef TOPKIND_H
#define TOPKIND_H

#include <unordered_map>
#include <map>

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