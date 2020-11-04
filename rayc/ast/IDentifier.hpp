#pragma once
namespace ray::ast {
	enum struct IDentifierType  {
		_function,
		_var,
		_const,
		_class
	};
	struct IDentifier:ASTBase 
	{
		unique_ptr<std::string> name;
		unique_ptr<IDentifierType> type;
		IDentifier(const std::string &name, IDentifierType type);
		virtual ~IDentifier(){
			name.release();
			type.release();
		}
	};
};