#ifndef TRANSF_HEADER
#define TRANSF_HEADER

#include "../common/point.hpp"
#include <vector>

class Transformation {

    public:
        virtual void transform(float) const = 0;
        virtual ~Transformation() {};
};

class TranslateStatic : public Transformation {

    private:
        float x;
        float y;
        float z;
    
    public:
        void transform(float) const override;
        TranslateStatic(float new_x, float new_y, float new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
        };
        ~TranslateStatic() override {};
};

class TranslateDynamic : public Transformation {

    private:
        float duration;
        bool align = false;         // Default value
        std::vector<Point> points;

    public:
        void transform(float) const override;
        TranslateDynamic(float time, std::vector<Point> p, bool isAlign) {
            duration = time * 1000;
            points = p;
            align = isAlign;
        }
        ~TranslateDynamic() override {};
};

class RotateStatic : public Transformation {

    private:
        float angle;
        float x;
        float y;
        float z;
    
    public:
        void transform(float) const override;
        RotateStatic(float new_angle, float new_x, float new_y, float new_z) {
            angle = new_angle;
            x = new_x;
            y = new_y;
            z = new_z;
        };
        ~RotateStatic() override {};
};

class RotateDynamic : public Transformation {

    private:
        float duration;
        float x;
        float y;
        float z;

    public:
        void transform(float) const override;
        RotateDynamic(float time, float new_x, float new_y, float new_z) {
        // Multiplicamos por 1000 porque o glutGet dá-nos o tempo em mili-segundos e tinhamos de estar sempre a dividir por 1000 (operação + custosa e que ocorria mais vezes)
            duration = time * 1000; 
            x = new_x;
            y = new_y;
            z = new_z;
        }
        ~RotateDynamic() override {};
};

class Scale : public Transformation {

    private:
        float x;
        float y;
        float z;
    
    public:
        void transform(float) const override;
        Scale(float new_x, float new_y, float new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
        };
        ~Scale() override {};
};

#endif