#pragma once
#include <pch.h>
namespace ray::ast {
	struct ASTBase {
		virtual ~ASTBase(){}
	};
};
#include "IDentifier.hpp"
#include "./interfaces/interfaces.hpp"
#include "./expressions/expressions.hpp"
