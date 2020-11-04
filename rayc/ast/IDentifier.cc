#include <pch.h>
#include "./ast.h"

namespace ray::ast {
	IDentifier::IDentifier(const std::string &name, IDentifierType type):
		name(make_unique<std::string>(name)),
		type(make_unique<IDentifierType>(type))
	{
	}
};