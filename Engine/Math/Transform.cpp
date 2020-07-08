#include "pch.h"
#include "Transform.h"

namespace bleh
{
    std::istream& operator>>(std::istream& stream, Transform& transform)
    {
        stream >> transform.position;
        stream >> transform.scale;
        stream >> transform.angle;

        return stream;
    }
}

