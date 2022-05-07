#pragma once

#include <iostream>
#include <memory>

#include "answer.h"

namespace minji
{
    class deck;
    class card_builder;

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

            bool operator==(const card& c) const;
            friend class card_builder;

        private:
            card(std::string description, std::string front,
                    std::unique_ptr<answer>&& ans, std::string cty) noexcept;
            std::string _description;
            std::string _front;
            std::unique_ptr<answer> _back;
            std::string _deck_name;
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
            card_builder(std::string deck_name);
	    std::string _deck_name;
            std::string _description;
            std::string _front;
            std::unique_ptr<answer> _ans;
    };
}
