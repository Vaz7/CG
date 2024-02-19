#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <memory>
#include "group.hpp"
#include "render.hpp"

std::unique_ptr<Group> xml_parser(const char*, struct window**, struct camera**);

#endif