#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "group.hpp"
#include "render.hpp"
#include "light.hpp"
#include <memory>

std::unique_ptr<Group> xml_parser(const char*, struct window**, struct camera**, std::vector<std::unique_ptr<Light>>&);

#endif