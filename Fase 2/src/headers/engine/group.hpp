#ifndef GROUP_HEADER
#define GROUP_HEADER

#include "../../tinyxml/tinyxml.h"
#include "model.hpp"
#include "transformations.hpp"
#include <memory>
#include <vector>

class Group {

    private:
       std::vector<Model> models;
       std::vector<std::unique_ptr<Transformation>> transformations;
       std::vector<Group> subgroups;

    public:
        Group(TiXmlNode*);
        void draw();
};

#endif