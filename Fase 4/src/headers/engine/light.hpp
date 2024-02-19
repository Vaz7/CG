#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "../common/point.hpp"

class Light {

    private:
        // Podemos dar a opção de mudar a cor da luz (atribuir valores default caso nada seja dito)

    public:
        virtual void turn_on(int) const = 0;
        virtual ~Light() {};
        static inline int l_number = 0;
};

class PointLight : public Light {

    private:
        Point pos;

    public:
        PointLight(Point); 
        void turn_on(int) const override;
        ~PointLight() override {};
};

class DirectionalLight : public Light {

    private:
        Point dir;

    public:
        DirectionalLight(Point);
        void turn_on(int) const override;
        ~DirectionalLight() override {};
};

class SpotLight : public Light {

    private:
        Point pos;
        Point dir;
        size_t cutoff;

    public:
        SpotLight(Point, Point, size_t);
        void turn_on(int) const override;
        ~SpotLight() override {};
};

#endif