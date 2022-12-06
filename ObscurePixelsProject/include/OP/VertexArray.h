#pragma once

#include <vector>
#include "Vertex.h"
#include "Drawable.h"
#include "Utility.h"
#include "ConsoleHandler.h"

namespace op
{
    // Basic class to handle VertexArrays together (it's drawable to screen)
    class VertexArray : public Drawable
    {
        private:
        std::vector<Vertex> _vertices;
        PrimitiveType _primitive_type;

        // Inherited from Drawable
        private:
        virtual void draw(RenderTarget& target) const;

        public:
        // Constructors
        VertexArray();

        VertexArray(PrimitiveType type, unsigned count_vertices);

        // Main Functions
        void append(const Vertex& vertex);
        
        void resize(unsigned vertexCount);
        
        void clear();
    
        // operators (accessor / reader)
        Vertex& operator [](std::size_t index);
        
        const Vertex& operator [](std::size_t index) const;
    
        // Setters
        void setPrimitiveType(PrimitiveType type);
        
        // Getters
        PrimitiveType getPrimitiveType() const;
       
        unsigned getVertexCount() const;

        FloatRect getBounds() const;
       
    };
} // namespace op
