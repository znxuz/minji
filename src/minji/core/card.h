#pragma once

#include <iostream>
#include <memory>
#include <sstream>

#include "answers/answer.h"

namespace minji
{
    class card final
    {
        public:
	    card(const card&);
	    card& operator=(const card&);
	    card(card&&) = default;
	    card& operator=(card&&) = default;
	    ~card() = default;

            std::string& description();
            const std::string& description() const;
            std::string& front();
            const std::string& front() const;
            answer& back();
            const answer& back() const;
	    void show(std::ostream&, answer::reveal) const;
            bool operator==(const card& c) const;

	    friend std::ostream& operator<<(std::ostream&, const minji::card&);
            friend class card_builder;

        private:
            card(std::string description, std::string front,
                    std::unique_ptr<answer>&& ans,
		    std::string deck_name) noexcept;
            std::string description_;
            std::string front_;
            std::unique_ptr<answer> back_;
            std::string deck_name_;

	    std::string to_string(answer::reveal) const;
    };

    std::ostream& operator<<(std::ostream&, const minji::card&);

    class card_builder final
    {
        public:
            static card_builder init(std::string deck_name);

            card_builder& description(std::string);
            card_builder& front(std::string);
            card_builder& back(std::unique_ptr<answer>&& ans);
            minji::card build();

        private:
            explicit card_builder(std::string deck_name);
	    std::string deck_name_;
            std::string description_;
            std::string front_;
            std::unique_ptr<answer> ans_;
    };
}
