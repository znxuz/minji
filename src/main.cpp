#include <iostream>
#include <memory>

#include "ui/simple_menu.h"
#include "minji/card.h"
#include "minji/plain_answer.h"

int main(int argc, char** argv)
{
	std::unique_ptr<minji::answer> ptr = std::make_unique<minji::plain_answer>("plain answer back");
	const minji::card c("this is the front of the card", std::move(ptr));

	std::cout << c;
}
