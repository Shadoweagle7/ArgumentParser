#ifndef SE7_ARGUMENT_PARSER
#define SE7_ARGUMENT_PARSER

#include <map>
#include <string>
#include <vector>
#include <initializer_list>
#include <stdexcept>

namespace SE7 {
	class duplicate_argument : public std::runtime_error {
	public:
		duplicate_argument(const std::string &arg) : std::runtime_error("Duplicate argument " + arg) {}
	};

	class argument_parser {
	private:
		std::map<std::string, std::vector<std::string>> args;
	public:
		void add(std::string arg, std::initializer_list<std::string> i_list_values) {
			if (auto [it, success] = this->args.insert({ arg, i_list_values }); !success) {

			}
		}
	};
}

#endif // !SE7_ARGUMENT_PARSER
