#include "../headers/common/point.hpp"
#include "../headers/engine/transformations.hpp"
#include "../headers/engine/group.hpp"
#include "../headers/engine/model.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// TODO: Mudar as funções que usam Transform* para usar std::unique_ptr<Transform> para ter gestão de memória automática
// No mesmo sentido tenho de mudar os return's Transform* para std::make_unique<subclass_constructor> não esquecer de fazer std::move quando fizer push_back para não copiar o objeto!
// adicionar virtual ~Transformation() {} (destrutor) e ~subclass_type() = default; nas restantes subclasses 

const std::string _3D_path = "../3DFiles/";   // string com o path relativo para a pasta com os ficheiros .3d

void parse_color(TiXmlNode* node, GLfloat* param) {

    float r = param[0];
    float g = param[1];
    float b = param[2];

    for (auto rgb = node->ToElement()->FirstAttribute(); rgb != NULL; rgb = rgb->Next()) {
        std::string name = rgb->Name();

        if (name == "R") r = std::stof(rgb->Value()) / 255.0;
        else if (name == "G") g = std::stof(rgb->Value()) / 255.0;
        else if (name == "B") b = std::stof(rgb->Value()) / 255.0;
    }

    param[0] = r;
    param[1] = g;
    param[2] = b;
}

/**
 * @brief Função responsável pelo parsing dos modelos 
 * 
 * @param node Nodo com os elementos dos modelos
 * @return std::vector<Model> Vetor com todos os modelos contidos em node
 */
std::vector<Model> parse_model(TiXmlNode* node) {
    
    std::vector<Model> temp; // vetor temporário que armazena os modelos

    for (auto model = node->FirstChildElement("model"); model != NULL; model = model->NextSiblingElement()) {
        std::string name = _3D_path + model->Attribute("file");
        
        bool textured = false, colored = false;
        std::string tex_file;
        GLfloat diffusive[4] = {200 / 255.0, 200 / 255.0, 200 / 255.0, 1.0}, ambient[4] = {50 / 255.0, 50 / 255.0, 50 / 255.0, 1.0};
        GLfloat specular[4] = {0.0f, 0.0f, 0.0f, 1.0}, emissive[4] = {0.0f, 0.0f, 0.0f, 1.0};
        GLfloat shininess = 0.0f;

        for (auto child = model->FirstChild(); child != NULL; child = child->NextSibling()) {
            std::string c_name = child->Value();
            if (c_name == "color") {
                for (auto color = child->ToElement()->FirstChild(); color != NULL; color = color->NextSibling()) {
                    colored = true;
                    std::string color_type = color->Value();

                    if (color_type == "diffuse") parse_color(color, diffusive);
                    else if (color_type == "ambient") parse_color(color, ambient);
                    else if (color_type == "specular") parse_color(color, specular);
                    else if (color_type == "emissive") parse_color(color, emissive);
                    else if (color_type == "shininess") shininess = std::stof(color->ToElement()->Attribute("value"));
                }
            }
            else if (c_name == "texture") {
                textured = true;
                tex_file = child->ToElement()->Attribute("file");
            }
        }

        if (!textured && !colored) { 
            Model m(name);
            temp.push_back(std::move(m)); // Para não criar uma cópia desnecessária do objeto 
        }
        else if (!textured && colored) {
            Model m(name, diffusive, ambient, specular, emissive, shininess);
            temp.push_back(std::move(m)); // Para não criar uma cópia desnecessária do objeto 
        }
        else {
            Model m(name, diffusive, ambient, specular, emissive, shininess, tex_file);
            temp.push_back(std::move(m));
        }
    } 
    
    return temp;
}

std::vector<Point> parse_points(TiXmlNode* node) {

    std::vector<Point> result;
    float x = 0, y = 0, z = 0;

    for (auto elem = node->FirstChild(); elem != NULL; elem = elem->NextSibling()) {
        std::string name = elem->Value();
        
        if (name == "point") {
            x = std::stof(elem->ToElement()->Attribute("x"));
            y = std::stof(elem->ToElement()->Attribute("y"));
            z = std::stof(elem->ToElement()->Attribute("z"));
            
            result.push_back(Point(x, y, z));
        }
    }

    return result;
}

/**
 * @brief Função responsável pelo parsing da operação de translação 
 * 
 * @param node Nodo como os atributos da translação
 * @return Transformation* Apontador para o super tipo abstrato Transformation
 */
std::unique_ptr<Transformation> parse_translate(TiXmlNode* node) {

    float x = 0, y = 0, z = 0, time;
    bool timed = false, align = false;

    for (auto att = node->ToElement()->FirstAttribute(); att != NULL; att = att->Next()) {
        std::string name = att->Name();

        if (name == "x") {
            x = std::stof(att->Value());
        }
        else if (name == "y") {
            y = std::stof(att->Value());
        }
        else if (name == "z") {
            z = std::stof(att->Value());
        }
        else if (name == "time") {
            time = std::stof(att->Value());
            timed = true;
        }
        else if (name == "align") {
            std::istringstream(att->Value()) >> std::boolalpha >> align;
        }
    }

    if (timed) {
        std::vector<Point> points = parse_points(node);
        return std::make_unique<TranslateDynamic>(time, points, align);
    }

    return std::make_unique<TranslateStatic>(x, y, z);
}

/**
 * @brief Função responsável pelo parsing da operação de rotação 
 * 
 * @param node Nodo com os atributos da rotação
 * @return Transformation* Apontador para o super tipo abstrato Transformation
 */
std::unique_ptr<Transformation> parse_rotate(TiXmlNode* node) {

    float angle = 0, x = 0, y = 0, z = 0, time = 0;
    bool timed = false;

    for (auto att = node->ToElement()->FirstAttribute(); att != NULL; att = att->Next()) {
        std::string name = att->Name();

        if (name == "angle") {
            angle = std::stof(att->Value());
        }
        else if (name == "x") {
            x = std::stof(att->Value());
        }
        else if (name == "y") {
            y = std::stof(att->Value());
        }
        else if (name == "z") {
            z = std::stof(att->Value());
        }
        else if (name == "time") {
            time = std::stof(att->Value());
            timed = true;
        }
    }

    if(timed) {
        return std::make_unique<RotateDynamic>(time, x, y, z);
    } 

    return std::make_unique<RotateStatic>(angle, x, y, z);
}

/**
 * @brief Função responsável pelo parsing da operação de escala 
 * 
 * @param node Nodo com os atributos da escala
 * @return Transformation* Apontador para o super tipo abstrato Transformation 
 */
std::unique_ptr<Transformation> parse_scale(TiXmlNode* node) {

    float x = 0, y = 0, z = 0;

    for (auto att = node->ToElement()->FirstAttribute(); att != NULL; att = att->Next()) {
        std::string name = att->Name();

        if (name == "x") {
            x = std::stof(att->Value());
        }
        else if (name == "y") {
            y = std::stof(att->Value());
        }
        else if (name == "z") {
            z = std::stof(att->Value());
        }
    }

    return std::make_unique<Scale>(x, y, z);
}

/**
 * @brief Função responsável pelo parsing das transformações disponíveis 
 * 
 * @param node Nodo com todos os elementos das transformações
 * @return std::vector<std::unique_ptr<Transformation>> Vetor com todas as transformações contidas em node
 */
std::vector<std::unique_ptr<Transformation>> parse_transformations(TiXmlNode* node) {

    std::vector<std::unique_ptr<Transformation>> temp; // Vetor temporário que armazena as transformações

    for (auto elem = node->FirstChild(); elem != NULL; elem = elem->NextSibling()) {
        std::string name = elem->Value();
        
        if (name == "translate") {
            temp.push_back(parse_translate(elem));
        }
        else if (name == "rotate") {
            temp.push_back(parse_rotate(elem));
        }
        else if (name == "scale") {
            temp.push_back(parse_scale(elem));
        }
    }

    return temp;
}

Group::Group(TiXmlNode* node) {

    // Ciclo que percorre todos os elementos de um dado <group>
    for(auto elem = node->FirstChild(); elem != NULL; elem = elem->NextSibling()) {
        std::string name = elem->Value();

        if (name == "models") {
            models = parse_model(elem);
        }
        if (name == "transform") {
            transformations = parse_transformations(elem);
        }
        else if (name == "group") {
            Group group(elem);
            subgroups.push_back(std::move(group)); // em vez de copiar o objeto group para dentro do vector usamos o move para alterar o apontador (canibalismo)
        }
    }
}

/**
 * @brief Função que desenha os elementos de uma dado grupo 
 * 
 */
void Group::draw(float time_elapsed) {

    glPushMatrix();
    // Primeiramente realizamos todas as transformações do grupo
    for (const auto& transformation : transformations) {
        transformation->transform(time_elapsed);
    }
    
    // Após termos realizado as transformações podemos gerar os modelos com a certeza de que estes estarão nas posições desejadas
    for (auto model : models) {
        model.draw();
    }

    // Repetimos o processo recursivamente para todos os subgrupos do <group> atual
    // NOTE: tive de trocar o for each loop para um for loop normal porque estava a dar um erro e não percebi o porquê
    for (int i = 0; i < subgroups.size(); i++) {
        subgroups[i].draw(time_elapsed);
    }
    glPopMatrix();
}