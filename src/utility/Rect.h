#ifndef INCLUDE_RECT_H
#define INCLUDE_RECT_H
namespace WalrusRPG
{
    namespace Utils
    {
        class Rect
        {
          public:
            signed x, y;
            unsigned width, height;
            // We don't need a source file for two inline functions.
            Rect(signed x_, signed y_, unsigned width_, unsigned height_)
                : x(x_), y(y_), width(width_), height(height_){};
            Rect(signed x_, signed y_) : Rect(x_, y_, 0, 0){};
            Rect() : Rect(0, 0, 0, 0){};
        };
    }
}
#endif
