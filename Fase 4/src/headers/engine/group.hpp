#ifndef GROUP_HEADER
#define GROUP_HEADER

#include "model.hpp"
#include "../../tinyxml/tinyxml.h"
#include "transformations.hpp"
#include <memory>

class Group {

    private:
       std::vector<Model> models;
       std::vector<std::unique_ptr<Transformation>> transformations;
       std::vector<Group> subgroups;

    public:
        Group(TiXmlNode*);
        void draw(float);
};

#endif