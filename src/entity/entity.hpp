#include <glm/glm.hpp>
class Entity
{
public:
    Entity(glm::vec3 _position);
private:
    glm::vec3 position =glm::vec3(0.0f, 0.0f, 0.0f);
};