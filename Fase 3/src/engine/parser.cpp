#include "../tinyxml/tinyxml.h"
#include "../headers/engine/group.hpp"
#include "../headers/engine/render.hpp"
#include <string>
#include <iostream>
#include <math.h>
#include <memory>

// TODO: Atualizar documentação da função "xml_parser"

/**
 * @brief Função responsável pelo parsing dos atributos da janela 
 * 
 * @param node Nodo com os atributos da janela
 */
void parse_window(TiXmlNode* node, struct window** w) {

    for (auto att = node->ToElement()->FirstAttribute(); att != NULL; att = att->Next()) {
        std::string name = att->Name();

        if (name == "width") {
            (*w)->w_width = std::stoi(att->Value());
        }
        else if (name == "height") {
            (*w)->w_height = std::stoi(att->Value());
        }
    }
}

/**
 * @brief Função responsável pelo parsing dos elementos da câmera 
 * 
 * @param node Nodo com os elementos da câmera
 */
void parse_camera(TiXmlNode* node, struct camera** cam) {

    // Ciclo que percorre todos os elementos da câmera e recolhe os respetivos atributos
    for (auto att = node->FirstChild(); att != NULL; att = att->NextSibling()) {
        std::string name = att->Value();

        if (name == "position") {
            (*cam)->pos_x = std::stof(att->ToElement()->Attribute("x"));
            (*cam)->pos_y = std::stof(att->ToElement()->Attribute("y"));
            (*cam)->pos_z = std::stof(att->ToElement()->Attribute("z"));
            (*cam)->c_radius = sqrt((*cam)->pos_x*(*cam)->pos_x + (*cam)->pos_y*(*cam)->pos_y + (*cam)->pos_z*(*cam)->pos_z);
        }
        else if (name == "lookAt") {
            (*cam)->look_x = std::stof(att->ToElement()->Attribute("x"));
            (*cam)->look_y = std::stof(att->ToElement()->Attribute("y"));
            (*cam)->look_z = std::stof(att->ToElement()->Attribute("z"));
        }
        else if (name == "up") {
            (*cam)->up_x = std::stof(att->ToElement()->Attribute("x"));
            (*cam)->up_y = std::stof(att->ToElement()->Attribute("y"));
            (*cam)->up_z = std::stof(att->ToElement()->Attribute("z"));
        }
        else if (name == "projection") {
            (*cam)->fov = std::stof(att->ToElement()->Attribute("fov"));
            (*cam)->near = std::stof(att->ToElement()->Attribute("near"));
            (*cam)->far = std::stof(att->ToElement()->Attribute("far"));
        }
    }
}

/**
 * @brief Função que faz o parsing de ficheiros XML recorrendo à biblioteca tinyxml 
 * 
 * @param filename Nome do ficheiro a ser alvo de parsing
 * @param scene Apontador para a cena principal do ficheiro xml 
 */
std::unique_ptr<Group> xml_parser(const char* filename, struct window** w, struct camera** cam) {

    TiXmlDocument doc(filename);
    std::unique_ptr<Group> scene;

    if (doc.LoadFile()) {
        TiXmlElement* proot = doc.FirstChildElement("world");

        // Caso o primeiro elemento não seja "world" é gerada uma mensagem de erro
        if (!proot) {
            std::cout << "Invalid format detected! Please make sure to provide a config file that follows the specified norms!" << std::endl;
            return nullptr;
        }

        // Ciclo que percorre todos os elementos dentro da tag "world" e realiza a ação adequada
        for (auto elem = proot->FirstChild(); elem != NULL; elem = elem->NextSibling()) {
            std::string name = elem->Value();
            if (name == "window") {
                parse_window(elem, w);
            }
            else if (name == "camera") {
                parse_camera(elem, cam);
            }
            else if (name == "group") {
                scene = std::make_unique<Group>(elem);
            }
        }
    }
    else {
        std::cout << "Failed to load file " + std::string(filename) << std::endl;
        return nullptr;
    }

    return scene;
}