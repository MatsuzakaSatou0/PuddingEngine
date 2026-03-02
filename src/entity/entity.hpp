#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "tiny_gltf.h"

class Entity
{
public:
    Entity(glm::vec3 _position);
    void SetNormals(std::vector<glm::vec3> vec);
    void SetVertices(std::vector<glm::vec3> vec);
    void SetIndices(std::vector<int> vec);
    void SetPosition(glm::vec3 vec);
    std::vector<glm::vec3> GetNormals();
    std::vector<glm::vec3> GetVertices();
    std::vector<int> GetIndices();
    glm::vec3 GetPosition();
    void SetName(std::string name);
    std::string GetName();
    void RenderEditor();
    void OpenEditor();
    void CloseEditor();
    void SetImage(tinygltf::Image image);
    void GetImage();
private:
    tinygltf::Image image;
    std::string gltfLog;
    bool isEditorOpen = false;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> vertices;
    std::vector<int> indices;
    glm::vec3 position =glm::vec3(0.0f, 0.0f, 0.0f);
    std::string name = "ENT";
};