#pragma once

namespace op
{
    // ConsoleHandler will change name in future propably
    class ConsoleHandler;
    typedef ConsoleHandler RenderTarget;

    // Class of Drawable objects (method draw)
    class Drawable
    {
        public:
        virtual ~Drawable() {}

        protected:
        friend class ConsoleHandler;
        virtual void draw(RenderTarget& target) const = 0;

    };
    
} // namespace op