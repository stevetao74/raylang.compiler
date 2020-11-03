#include <pch.h>
#include <parser/ray-parser.tab.h>
extern FILE *yyin, *yyout;
namespace {
	class Application {
	public:
		int main(const std::vector<std::string> &args);
		void set_locale();
	private:

	};
};

int main(int argc, char *argv[]) {
	std::vector<std::string> args(argv, argv + argc);
	Application app;
	return app.main(args);
}

namespace {

	int Application::main(const std::vector<std::string> &args) {
		using Parser =  yy::parser;
		this->set_locale();
		Parser parser;
		yyin = stdin;
		//TODO:此处执行编译过程
		for (auto &arg : args) {
			
		}
		parser.parse();

		return 0;
	}

	void Application::set_locale() {
		try {
			setlocale(LC_ALL, "");
			auto utf = std::locale("");
			std::cout.imbue(utf);
			std::cerr.imbue(utf);
			std::clog.imbue(utf);
		}
		catch (std::exception e) {
			std::cerr << "Warning:"<< e.what() << std::endl;
		}
	}
};