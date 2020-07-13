#include "pch.h"
#include "Transform.h"

namespace bleh
{
    std::istream& operator>>(std::istream& stream, Transform& transform)
    {
        stream >> transform.position;

        std::string line;

        std::getline(stream, line);
        transform.scale = stof(line);

        std::getline(stream, line);
        transform.angle = stof(line);

        return stream;
    }
}

