#include "../../include/OP/VertexArray.h"

namespace op
{
    // Constructors
    VertexArray::VertexArray()
    {

    }

    VertexArray::VertexArray(PrimitiveType type, unsigned count_vertices)
    {
        _primitive_type = type;

        resize(count_vertices);
    }

    // virtual
    void VertexArray::draw(RenderTarget& target) const
    {
        if (!_vertices.empty())
        {
            //target.draw(*this); // endless loop?

            Vector2i v = target.view;

            int width = target._width;
            int height = target._height;

        
            for(int i = 0; i < getVertexCount(); i++)
            {
                int x = static_cast<int> (_vertices[i].getPosition().x) - v.x;
                int y = static_cast<int> (_vertices[i].getPosition().y) - v.y;

                if( x >= 0 && x < height && y >= 0 && y < width)
                {
                    target.Screen[y + x * width].setChar(_vertices[i].getChar());
                    target.Screen[y + x * width].bgColor = _vertices[i].bgColor;
                    target.Screen[y + x * width].fgColor = _vertices[i].fgColor;
                }
            }
        }
    }

    // Functions
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

    //setters
    void VertexArray::setPrimitiveType(PrimitiveType type)
    {
        _primitive_type = type;
    }
    
    //getters
    PrimitiveType VertexArray::getPrimitiveType() const
    {
        return _primitive_type;
    }

    unsigned VertexArray::getVertexCount() const
    {
        return _vertices.size();
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
