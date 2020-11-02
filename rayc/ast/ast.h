#pragma once
#include <pch.h>
namespace ray::ast {
	struct ASTBase {
		virtual ~ASTBase(){}
	};
};

#include "./interfaces/interfaces.hpp"
#include "./expressions/expressions.hpp"