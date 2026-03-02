#include <gamefile/gamefile.h>
#include <glm/glm.hpp>
#include <entity/entity.hpp>
class GltfParser
{
public:
    bool LoadGLTF(std::string& log,Entity& entity);
private:
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;
};