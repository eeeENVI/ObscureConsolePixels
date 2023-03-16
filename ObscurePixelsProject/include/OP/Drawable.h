#pragma once

namespace op
{
    // ConsoleHandler will change name in future propably and RenderTarget will be new Class
    class ConsoleHandler;

    // Class of Drawable objects (method draw) to create ur own custom shapes and how to draw them
    class Drawable
    {
        public:
        virtual ~Drawable() {}

        protected:
        friend class ConsoleHandler;
        virtual void draw(ConsoleHandler& target) const = 0;

    };
    
} // namespace op