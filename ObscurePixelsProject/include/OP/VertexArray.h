#pragma once

#include <vector>
#include "Vertex.h"
#include "Utility.h"

namespace op
{
    // Basic class to handle VertexArrays together (it's drawable to screen)
    class VertexArray
    {
        private:
        std::vector<Vertex> _vertices;
        PrimitiveType _primitive_type;

        public:
        // Constructors
        VertexArray();

        VertexArray(PrimitiveType type, unsigned count_vertices);

        // Main Functions
        void append(const Vertex& vertex);
        
        void resize(unsigned vertexCount);
        
        void clear();
    
        // Setters
        void setPrimitiveType(PrimitiveType type);
        
        // Getters
        PrimitiveType getPrimitiveType() const;
       
        unsigned getVertexCount() const;

        bool isEmpty() const;

        FloatRect getBounds() const;
       
        // operators (accessor / reader)
        Vertex& operator [](std::size_t index);
        
        const Vertex& operator [](std::size_t index) const;
    };
} // namespace op
