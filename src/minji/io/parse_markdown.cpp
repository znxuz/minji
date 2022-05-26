#include "parse_markdown.h"

namespace
{
    struct card_component_mark
    {
	bool description = false;
	bool front = false;
	bool back = false;

	bool all_checked()
	{
	    return description && front && back;
	}

	void clear()
	{
	    description = front = back = false;
	}

	bool check(char c)
	{
	    switch (c) {
		case '#':
		    return (description = !description);
		case '>':
		    return (front = !front);
		default:
		    return (back = !back);
	    }
	}
    };

    bool section_end_reached(std::ifstream& ifs)
    {
	return ifs.peek() == std::char_traits<char>::eof() ||
	    ifs.peek() == '\n';
    }

    std::string parse_description(std::ifstream& ifs)
    {
	std::string description;
	std::getline(ifs, description);
	while (description.front() == '#' || description.front() == ' ')
	    description.erase(description.begin());

	return description;
    }

    std::string parse_front(std::ifstream& ifs)
    {
	std::string line;
	std::string front;
	while (!section_end_reached(ifs)) {
	    std::getline(ifs, line);
	    if (line.front() == '>')
		while (line.front() == '>' || line.front() == ' ')
		    line.erase(line.begin());
	    front += std::move(line);
	}

	return front;
    }

    std::unique_ptr<minji::answer> parse_multi(std::ifstream& ifs)
    {
	static std::regex answer_head("-\\s*\\[[X|O]\\]\\s*");
	static std::regex correct_answer("\\[[oO]\\]");

	std::vector<std::pair<std::string, bool>> choices;
	std::string answer;
	std::smatch matched;
	bool is_correct;
	while (!section_end_reached(ifs)) {
	    std::string line;
	    std::getline(ifs, line);

	    if (std::regex_search(line, matched, answer_head)) {
		if (!answer.empty())
		    choices.push_back(std::pair(std::move(answer), is_correct));

		answer = std::regex_replace(line, answer_head, "");
		is_correct = std::regex_search(line, correct_answer);
	    } else {
		answer += std::move(line);
	    }
	}
	if (!answer.empty())
	    choices.push_back(std::pair(std::move(answer), is_correct));

	return minji::make_answer(choices);
    }

    std::unique_ptr<minji::answer> parse_plain(std::ifstream& ifs)
    {
	std::string answer;
	std::string line;
	while (!section_end_reached(ifs)) {
	    std::getline(ifs, line);
	    answer += std::move(line);
	}

	return minji::make_answer(answer);
    }

    std::unique_ptr<minji::answer> parse_back(std::ifstream& ifs)
    {
	if (ifs.peek() == '-')
	    return parse_multi(ifs);
	return parse_plain(ifs);
    }

    void debug(const char* fname)
    {
	std::ifstream ifs(fname);
	std::string line;
	while (std::getline(ifs, line)) {
	    std::cout << line << '\n';
	}
    }
}

namespace io
{
    std::shared_ptr<minji::deck> parse_markdown(const std::filesystem::path& p,
	    const std::string& deck_name)
    {
	auto deck = std::make_shared<minji::deck>(deck_name);
	auto crd_builder = minji::card_builder::init(deck_name);
	card_component_mark mark = card_component_mark();
	std::ifstream ifs(p);
	while (!ifs.eof() || mark.all_checked()) {
	    if (mark.all_checked()) {
		deck->add(crd_builder.build());
		crd_builder = minji::card_builder::init(deck_name);
		mark.clear();
		continue;
	    }
	    if (ifs.peek() == '\n') {
		ifs.get();
		continue;
	    }

	    char start = static_cast<char>(ifs.peek());
	    if (!mark.check(start))
		throw parse_error("error parsing markdown file");

	    if (start == '#')
		crd_builder.description(parse_description(ifs));
	    else if (start == '>')
		crd_builder.front(parse_front(ifs));
	    else
		crd_builder.back(parse_back(ifs));
	}

	return deck;
    }
}
