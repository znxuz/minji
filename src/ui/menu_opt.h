#pragma once

#include <algorithm>
#include <array>
#include <iostream>

namespace menu
{
  enum class opt
  {
    practice = 'p', add_card = 'a', remove_card = 'r', change_card = 'c', list_card = 'l',
    add_deck = 'A', remove_deck = 'R', change_deck = 'C', list_deck = 'L', exit = 'e'
  };

  static constexpr std::array<opt, 10> opts
  {
      opt::practice, opt::add_card, opt::remove_card, opt::change_card, opt::list_card,
      opt::add_deck, opt::remove_deck, opt::change_deck, opt::list_deck, opt::exit
  };

  inline std::istream& operator>>(std::istream& is, opt& opt)
  {
    char in;
    is >> in;

    opt = static_cast<menu::opt>(in);
    if (std::find(begin(opts), end(opts), opt) == opts.end())
      is.setstate(std::ios::failbit);

    return is;
  }

  inline std::ostream& operator<<(std::ostream& os, const opt& opt)
  {
    switch (opt) {
	case opt::practice:
	    return (os << "(p)ractice");
      case opt::add_card:
        return (os << "(a)dd card");
      case opt::remove_card:
        return (os << "(r)emove card");
      case opt::change_card:
        return (os << "(c)hange card");
      case opt::list_card:
        return (os << "(l)ist card");
      case opt::add_deck:
        return (os << "(A)dd deck");
      case opt::remove_deck:
        return (os << "(R)emove deck");
      case opt::change_deck:
        return (os << "(C)hange deck");
      case opt::list_deck:
        return (os << "(L)ist deck");
      case opt::exit:
        return (os << "(e)xit");
    }
  }

}
