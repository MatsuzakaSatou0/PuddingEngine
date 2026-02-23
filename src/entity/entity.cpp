#include <entity/entity.hpp>

Entity::Entity(glm::vec3 _position)
{
    position = _position;
}
void Entity::SetVertices(std::vector<glm::vec3> _verticies)
{
    vertices = _verticies;
}
void Entity::SetNormals(std::vector<glm::vec3> vec)
{
    normals = vec;
}
void Entity::SetIndices(std::vector<int> vec)
{
    indices = vec;
}
void Entity::SetPosition(glm::vec3 vec)
{
    position = vec;
}
std::vector<glm::vec3> Entity::GetNormals()
{
    return normals;
}
std::vector<glm::vec3> Entity::GetVertices()
{
    return vertices;
}
std::vector<int> Entity::GetIndices()
{
    return indices;
}
glm::vec3 Entity::GetPosition()
{
    return position;
}
void Entity::SetName(std::string _name)
{
    name = _name;
}
std::string Entity::GetName()
{
    return name;
}