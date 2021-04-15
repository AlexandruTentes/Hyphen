#include "../../../lib/GraphicEngine/Material/Light.h"

namespace Hyphen
{
    Light::Light()
    {
        init_position.set(8.0f, 8.0f, 0.0f);
        init_direction.set(0.0f, -2.0f, 0.0f);
        init_color.set(255.0f, 255.0f, 255.0f);
        //init_ambient.set(color->sub(256).mul(-init_ambient_strength));
        //init_diffuse.set(color->sub(256).mul(-1));
        init_ambient.set(0.5f, 0.5f, 0.5f);
        init_diffuse.set(0.5f, 0.5f, 0.5f);
        init_specular.set(1.0f, 1.0f, 1.0f);
    }
}