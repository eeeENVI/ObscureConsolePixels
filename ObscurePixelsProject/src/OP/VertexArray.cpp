#include "../../include/OP/VertexArray.h"

namespace op
{
    // Constructors
    VertexArray::VertexArray(){}

    VertexArray::VertexArray(PrimitiveType type, unsigned count_vertices)
    {
        _primitive_type = type;

        resize(count_vertices);
    }

    // Main Functions
    void VertexArray::append(const Vertex& vertex)
    {
        _vertices.push_back(vertex);
    }

    void VertexArray::resize(unsigned vertexCount)
    {
        Vertex v;

        _vertices.resize(vertexCount, v);
    }

    void VertexArray::clear()
    {
        _vertices.clear();
    }

    // Setters
    void VertexArray::setPrimitiveType(PrimitiveType type)
    {
        _primitive_type = type;
    }
    
    // Getters
    PrimitiveType VertexArray::getPrimitiveType() const
    {
        return _primitive_type;
    }

    unsigned VertexArray::getVertexCount() const
    {
        return _vertices.size();
    }

    bool VertexArray::isEmpty() const
    {
        return _vertices.empty();
    }

    // Returns bounds of Vertex array
    FloatRect VertexArray::getBounds() const
    {
        if(!_vertices.empty())
        {
            float left   = _vertices[0].getPosition().x;
            float top    = _vertices[0].getPosition().y;
            float right  = _vertices[0].getPosition().x;
            float bottom = _vertices[0].getPosition().y;

            for (std::size_t i = 1; i < _vertices.size(); ++i)
            {
                Vector2i position = _vertices[i].getPosition();

                // Update left and right
                if (position.x < left)
                    left = position.x;
                else if (position.x > right)
                    right = position.x;

                // Update top and bottom
                if (position.y < top)
                    top = position.y;
                else if (position.y > bottom)
                    bottom = position.y;
            }

            return FloatRect({left, top}, {right - left, bottom - top});
        }
        else
        {
            return FloatRect();
        }
    }

    // operators (accessor / reader)
    Vertex& VertexArray::operator [](std::size_t index)
    {
        return _vertices[index];
    }

    const Vertex& VertexArray::operator [](std::size_t index) const
    {
        return _vertices[index];
    }

} // namespace op
