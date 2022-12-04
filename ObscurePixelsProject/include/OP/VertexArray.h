#pragma once

#include <vector>
#include "Vertex.h"
#include "Drawable.h"
#include "PrimitiveType.h"
#include "ConsoleHandler.h"

namespace op
{
    class VertexArray : public Drawable
    {
        private:
        std::vector<Vertex> _vertices;
        PrimitiveType _primitive_type;

        private:
        virtual void draw(RenderTarget& target) const;

        public:
        // Constructors
        VertexArray();

        VertexArray(PrimitiveType type, unsigned count_vertices);

        // Functions
        void append(const Vertex& vertex);
        
        void resize(unsigned vertexCount);
        
        void clear();
    
        // operators (accessor / reader)
        Vertex& operator [](std::size_t index);
        
        const Vertex& operator [](std::size_t index) const;
    
        //setters
        void setPrimitiveType(PrimitiveType type);
        
        //getters
        PrimitiveType getPrimitiveType() const;
       
        unsigned getVertexCount() const;
       
    };
} // namespace op
