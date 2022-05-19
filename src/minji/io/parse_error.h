#pragma once

#include <stdexcept>
#include <string>

namespace io
{
    class parse_error : public std::runtime_error
    {
    public:
	parse_error(const std::string& msg) : std::runtime_error(msg)
	{}
    };
}
