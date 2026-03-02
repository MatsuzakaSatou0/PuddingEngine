#include <entity/entity.hpp>
#include <format>
#include "imgui.h"
#include <parser/gltf_parser.hpp>

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
void Entity::RenderEditor()
{
    if(isEditorOpen)
    {
        GltfParser gltfParser = GltfParser();
        ImGui::Begin("MeshEditor");
        if(ImGui::Button("Close"))
        {
            CloseEditor();
        }
        if(ImGui::Button("LoadMesh"))
        {
            gltfParser.LoadGLTF(gltfLog,*this);
        }
        ImGui::Text("mesh info");
        int mesh_size = GetVertices().size() + GetNormals().size() + GetIndices().size();
        std::string mesh_size_str = std::format("SIZE:{}",mesh_size);
        ImGui::Text(mesh_size_str.data());
        ImGui::Text(gltfLog.data());
        ImGui::End();
    }
}
void Entity::OpenEditor()
{
    isEditorOpen = true;
}
void Entity::CloseEditor()
{
    isEditorOpen = false;
}
void Entity::SetImage(tinygltf::Image _image)
{
    image = _image;
}