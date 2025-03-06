#ifndef Vec2D_H
    #define Vec2D_H

class Vec2D{
    private:
        double x;
        double y;
    public:
        Vec2D(double a, double b);
        void set_x(double a);
        void set_y(double b);
        double get_x();
        double get_y();
        Vec2D operator+(Vec2D v);
        Vec2D operator-(Vec2D v);
        Vec2D operator*(double u);
        double length();
};


#endif