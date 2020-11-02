#include <pch.h>

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
		this->set_locale();
		//TODO:此处执行编译过程
		for (auto &arg : args) {
		}


		return 0;
	}

	void Application::set_locale() {
		setlocale(LC_ALL, "");
		std::locale global;
		std::cout.imbue(std::locale(global.name() + ".UTF8"));
		std::cerr.imbue(std::locale(global.name() + ".UTF8"));
		std::clog.imbue(std::locale(global.name() + ".UTF8"));
	}
};