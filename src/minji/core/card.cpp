#include "card.h"

namespace minji
{
    card::card(const card& c) : description_(c.description_),
    front_(c.front_), back_(c.back().clone()), deck_name_(c.deck_name_)
    {}

    card& card::operator=(const card& c)
    {
	card cpy = c;
	using std::swap;
	swap(this->description_, cpy.description_);
	swap(this->front_, cpy.front_);
	swap(this->back_, cpy.back_);
	swap(this->deck_name_, cpy.deck_name_);

	return *this;
    }

    std::string& card::description()
    {
        return description_;
    }

    const std::string& card::description() const
    {
        return const_cast<card*>(this)->description();
    }

    std::string& card::front()
    {
        return front_;
    }

    const std::string& card::front() const
    {
        return const_cast<card*>(this)->front();
    }

    answer& card::back()
    {
        return *back_;
    }

    const answer& card::back() const
    {
        return const_cast<card*>(this)->back();
    }

    void card::show(std::ostream& os, answer::reveal reveal) const
    {
	os << this->to_string(reveal);
    }

    bool card::operator==(const card& c) const
    {
        return this == &c ||
            (this->front_ == c.front_ &&
             this->back_ == c.back_ &&
             this->deck_name_ == c.deck_name_);
    }

    std::ostream& operator<<(std::ostream& os, const card& c)
    {
        return (os << c.to_string(answer::reveal::yes));
    }

    card::card(std::string description, std::string front,
	    std::unique_ptr<answer>&& ans, std::string deck_name) noexcept :
	description_(std::move(description)),
	front_(std::move(front)),
	back_(std::move(ans)),
	deck_name_(std::move(deck_name))
    {}

    std::string card::to_string(answer::reveal reveal) const
    {
	std::stringstream ss;
	ss << "# " << this->description() << "\n\n"
                "> " << this->front() << "\n\n" <<
		this->back().output(reveal) << '\n';

	return ss.str();
    }
}

namespace minji
{
    card_builder::card_builder(std::string deck_name) : deck_name_(deck_name)
    {}

    card_builder card_builder::init(std::string deck_name)
    {
	return card_builder(std::move(deck_name));
    }

    card_builder& card_builder::description(std::string description)
    {
	description_ = std::move(description);
	return *this;
    }

    card_builder& card_builder::front(std::string front)
    {
	front_ = std::move(front);
	return *this;
    }

    card_builder& card_builder::back(std::unique_ptr<answer>&& ans)
    {
	ans_ = std::move(ans);
	return *this;
    }

    card card_builder::build()
    {
	return card(std::move(description_), std::move(front_),
		std::move(ans_), std::move(deck_name_));
    }
}
