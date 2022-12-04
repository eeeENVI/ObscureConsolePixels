#pragma once

namespace op
{
    class ConsoleHandler;
    typedef ConsoleHandler RenderTarget;

    class Drawable
    {
        public:
        virtual ~Drawable() {}

        protected:
        friend class ConsoleHandler;
        virtual void draw(RenderTarget& target) const = 0;

    };
    
} // namespace op