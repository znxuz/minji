#include <iostream>
#include <memory>

#include "ui/i_menu.h"
#include "minji/card.h"
#include "minji/plain_answer.h"
#include "minji/answer_factory.h"
#include "minji/deck.h"
#include "minji/card.h"

std::vector<std::shared_ptr<minji::deck>> get_decks()
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


    return {std::move(d1)};
}

int main(int argc, char** argv)
{
    i_menu(get_decks());
}
