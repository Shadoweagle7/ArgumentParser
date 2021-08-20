#ifndef SE7_ARGUMENT_PARSER
#define SE7_ARGUMENT_PARSER

#include <stdexcept>
#include <string>
#include <string_view>
#include <map>
#include <initializer_list>
#include <vector>
#include <utility>
#include <array>
#include <tuple>

namespace SE7 {
	class argument_parser_exception : public std::runtime_error {
	public:
		argument_parser_exception(const std::string &message) : std::runtime_error(message) {}
	};

	class duplicate_argument : public argument_parser_exception {
	public:
		duplicate_argument(const std::string &flag) : 
			argument_parser_exception("Duplicate argument " + flag) {}
	};

	class unknown_argument : public argument_parser_exception {
	public:
		unknown_argument(const std::string &flag) :
			argument_parser_exception("Unknown argument " + flag) {}
	};

	class too_many_arguments : public argument_parser_exception {
	public:
		too_many_arguments(const std::string &flag) :
			argument_parser_exception("Too many arguments for flag " + flag) {}
	};

	class not_enough_arguments : public argument_parser_exception {
	public:
		not_enough_arguments(const std::string &flag) :
			argument_parser_exception("Not enough arguments for flag " + flag) {
		}
	};

	class argument {
	private:
		std::string m_str;
	public:
		argument() {}

		void set_value(std::string_view p_str) {
			this->m_str = p_str;
		}

		std::string_view get_value() const {
			return this->m_str;
		}

		bool no_value() const {
			return this->m_str.empty();
		}

		operator std::string_view() const {
			return this->get_value();
		}
	};

	template<class T>
	concept arguable = std::same_as<T, argument>;

	class argument_parser {
	private:
		std::map<std::string, std::vector<argument>> m_msa;
	public:
		argument_parser(
			std::initializer_list<std::pair<const std::string, std::vector<argument>>> p_i_list_psa
		) {
			this->m_msa = p_i_list_psa;
		}

		std::map<std::string, std::vector<argument>>::iterator begin() {
			return this->m_msa.begin();
		}

		std::map<std::string, std::vector<argument>>::iterator end() {
			return this->m_msa.end();
		}

		std::vector<argument> &operator[](const std::string &key) {
			return this->m_msa[key];
		}

		void parse(int argc, const char *argv[]) {
			int i = 0;

			for (; i < argc; i++) {
				try {
					std::vector<argument> &v_a = this->m_msa.at(argv[i]);

					size_t j = 0;

					for (; j < v_a.size(); j++) {
						if (i + j + 1 == argc) {
							throw not_enough_arguments(argv[i]);
						}

						v_a[j].set_value(argv[i + j + 1]);
					}

					i += j;
				} catch (const std::out_of_range &e_oor) {
					throw unknown_argument(argv[i]);
				} catch (const not_enough_arguments &e_tma) {
					throw e_tma;
				}
			}
		}

		template<size_t N>
		void parse(std::string (&args)[N]) {
			size_t i = 0;

			for (; i < N; i++) {
				try {
					std::vector<argument> &v_a = this->m_msa.at(args[i]);

					size_t j = 0;

					for (; j < v_a.size(); j++) {
						if (i + j + 1 == N) {
							throw not_enough_arguments(args[i]);
						}

						v_a[j].set_value(args[i + j + 1]);
					}

					i += j;
				} catch (const std::out_of_range &e_oor) {
					throw unknown_argument(args[i]);
				} catch (const not_enough_arguments &e_tma) {
					throw e_tma;
				}
			}
		}

		template<size_t N>
		void parse(std::array<std::string, N> args) {
			size_t i = 0;

			for (; i < N; i++) {
				try {
					std::vector<argument> &v_a = this->m_msa.at(args[i]);

					size_t j = 0;

					for (; j < v_a.size(); j++) {
						if (i + j + 1 == N) {
							throw not_enough_arguments(args[i]);
						}

						v_a[j].set_value(args[i + j + 1]);
					}

					i += j;
				} catch (const std::out_of_range &e_oor) {
					throw unknown_argument(args[i]);
				} catch (const not_enough_arguments &e_tma) {
					throw e_tma;
				}
			}
		}

		void parse(std::vector<std::string> args) {
			size_t i = 0;

			for (; i < args.size(); i++) {
				try {
					std::vector<argument> &v_a = this->m_msa.at(args[i]);

					size_t j = 0;

					for (; j < v_a.size(); j++) {
						if (i + j + 1 == args.size()) {
							throw not_enough_arguments(args[i]);
						}

						v_a[j].set_value(args[i + j + 1]);
					}

					i += j;
				} catch (const std::out_of_range &e_oor) {
					throw unknown_argument(args[i]);
				} catch (const not_enough_arguments &e_tma) {
					throw e_tma;
				}
			}
		}
	};
}

#endif // !SE7_ARGUMENT_PARSER
