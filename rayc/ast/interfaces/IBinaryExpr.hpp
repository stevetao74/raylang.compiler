#pragma once
namespace ray::ast {
	struct IBinaryExpr :IInterfaceBase {
		enum class OperatorType {
			_add = '+',
			_sub = '-',
			_mul = '*',
			_div = '/',
			_mod = '%',
		};
	};
};