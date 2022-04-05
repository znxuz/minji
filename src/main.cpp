#include <iostream>

#include "ui/simple_menu.h"
#include "minji/card_back.h"
#include "minji/card.h"

int main(int argc, char** argv)
{
	const minji::card c("this is the front of the card", minji::card_back());
	c.print();
}
