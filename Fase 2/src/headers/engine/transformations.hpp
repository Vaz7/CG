#ifndef TRANSF_HEADER
#define TRANSF_HEADER

class Transformation {

    public:
        virtual void transform() const = 0;
        virtual ~Transformation() {};
};

class Translate : public Transformation {

    private:
        float x;
        float y;
        float z;
    
    public:
        void transform() const override;
        Translate(float new_x, float new_y, float new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
        };
        ~Translate() override {};
};

class Rotate : public Transformation {

    private:
        float angle;
        float x;
        float y;
        float z;
    
    public:
        void transform() const override;
        Rotate(float new_angle, float new_x, float new_y, float new_z) {
            angle = new_angle;
            x = new_x;
            y = new_y;
            z = new_z;
        };
        ~Rotate() override {};
};

class Scale : public Transformation {

    private:
        float x;
        float y;
        float z;
    
    public:
        void transform() const override;
        Scale(float new_x, float new_y, float new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
        };
        ~Scale() override {};
};

#endif