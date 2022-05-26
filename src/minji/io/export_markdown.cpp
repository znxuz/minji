#include "export_markdown.h"

namespace
{
    bool prompt_overwrite()
    {
	std::cout << "[confirm] file exists, overwrite? [y/n]\n";
	std::string input;
	utils::parse_input_return_empty(input, [](const std::string& s) {
		return !s.empty() && s != "y" && s != "n";
		});
	return input.empty() || input == "y";
    }
}

namespace io
{
    void export_markdown(const minji::deck* deck)
    {
	std::filesystem::path p = deck->name() + ".md";
	if (std::filesystem::exists(p) && !prompt_overwrite()) {
	    std::cerr << "[message] abort exporting\n";
	    return;
	}

	std::ofstream ofs(p, std::ios::trunc);
	for (size_t i = 0; i < deck->size(); ++i) {
	    const auto& crd = (*deck)[i];
	    ofs << crd;
	    if (i + 1 < deck->size())
		    ofs << '\n';
	}

	std::cout << "[message] written cards to " << p.c_str() << '\n';
    }
}
