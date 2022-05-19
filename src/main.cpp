#include <iostream>
#include <memory>

#include "minji/ui/i_menu.h"
#include "minji/ui/cli_opt.h"
#include "minji/core/card.h"
#include "minji/core/answers/answer_factory.h"
#include "minji/core/answers/plain_answer.h"
#include "minji/core/deck.h"
#include "minji/core/card.h"
#include "minji/io/parse_markdown.h"
#include "minji/io/export_markdown.h"

namespace
{
    std::shared_ptr<minji::deck> get_deck()
    {
	auto d1 = std::make_shared<minji::deck>("deck1");
	d1->add(minji::card_builder::init(d1->name())
		.description("desc1")
		.front("question1")
		.back(minji::make_answer("plain1"))
		.build());
	d1->add(minji::card_builder::init(d1->name())
		.description("desc2")
		.front("ques2")
		.back(minji::make_answer("plain2"))
		.build());
	d1->add(minji::card_builder::init(d1->name())
		.description("desc3")
		.front("ques3")
		.back(minji::make_answer("plain3"))
		.build());
	d1->add(minji::card_builder::init(d1->name())
		.description("mult")
		.front("ques mult")
		.back(minji::make_answer({{"ans1", true}, {"ans2", false}}))
		.build());

	return d1;
    }

}

void test()
{
    io::export_markdown(::get_deck(), "new.md");
}

int main(int argc, char** argv)
{
    test();
    return 0;
    if (argc == 1)
	ui::i_menu({get_deck()});
    else
	ui::parse_argv(argc - 1, argv + 1);
}
