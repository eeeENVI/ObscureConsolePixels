#pragma once

namespace op
{
    // IN DEV
    enum PrimitiveType
    {
        Points,
        Lines,
        LineStrip
    };

    // To getBounds of an object
    struct FloatRect
    {
        float left;
        float top;
        float right;
        float bottom;

        FloatRect(float left, float top, float right, float bottom)
        {
            this->left = left;
            this->top = top;
            this->right = right;
            this->bottom =bottom;
        }

        FloatRect(Vector2f v1,Vector2f v2)
        {
            this->left = v1.getPosition().x;
            this->top = v1.getPosition().y;

            this->right = v2.getPosition().x;
            this->bottom = v2.getPosition().y;
        }

        FloatRect()
        {
            left = 0.0f;
            top = 0.0f;
            right = 0.0f;
            bottom = 0.0f;
        }
    };


} // namespace op
