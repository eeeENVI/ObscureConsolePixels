#pragma once

namespace op
{
    // Class to handle 2d vector math
    template <class T>
    class Vector2
    {
        public:
        T x;
        T y;

        // Constructors
        // Default
        Vector2() = default;

        // Full
        Vector2(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        Vector2(const Vector2<T>& v)
        {
            this->x = v.x;
            this->y = v.y;
        }
       
        // Setters  
        void setPosition(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        // Getters
        Vector2<T> getPosition()
        {
            return *this;
        }

        // Operators
        Vector2<T> operator+(const Vector2<T>& right)
        {
            return Vector2<T>(x + right.x,y + right.y);
        }

        Vector2<T> operator+=(const Vector2<T>& right)
        {
            return *this + right;
        }

        Vector2<T> operator-(const Vector2<T>& right)
        {
            return Vector2<T>(x - right.x,y - right.y);
        }

        Vector2<T> operator-=(const Vector2<T>& right)
        {
            return *this - right;
        }

        const Vector2<T> operator*(T right)
        {
            return Vector2<T>(x * right, y * right);
        }

        const Vector2<T> operator*=(T right)
        {
            return *this * right;
        }

        bool operator==(const Vector2<T>& right)
        {
            return (x == right.x && right.y == y);
        }

        bool operator!=(const Vector2<T>& right)
        {
            return (x != right.x || right.y != y);
        }

    };

    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
    typedef Vector2<unsigned> Vector2u;

} // namespace op
