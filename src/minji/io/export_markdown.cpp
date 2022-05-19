#include "export_markdown.h"

namespace
{
    constexpr static std::string_view md_separator = "\n---\n\n";

    bool prompt_overwrite()
    {
	std::cout << "[confirm] file exists, overwrite? [y/n]\n";
	std::string input;
	utils::parse_input_allow_empty(input, [](const std::string& s) {
		return !s.empty() && s != "y" && s != "n";
		});
	return input.empty() || input == "y";
    }
}

namespace io
{
    void export_markdown(const std::weak_ptr<minji::deck> deck,
	    const std::string_view fname)
    {
	if (std::filesystem::exists(fname.data()) && !prompt_overwrite()) {
	    std::cerr << "[message] abort exporting\n";
	    return;
	}

	std::ofstream ofs(fname.data(), std::ios::trunc);
	for (size_t i = 0; i < deck.lock()->size(); ++i) {
	    const auto& crd = (*deck.lock())[i];
	    ofs << crd;
	    if (i + 1 < deck.lock()->size())
		    ofs << md_separator;
	}

	std::cout << "[message] written cards to " << fname << '\n';
    }
}
