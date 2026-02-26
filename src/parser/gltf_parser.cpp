
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION

#include <string>
#include "gltf_parser.hpp"

bool GltfParser::LoadGLTF(std::string& log,Entity& entity){
    flatbuffers::FlatBufferBuilder builder(1024);
    std::string filename = "input.gltf";
    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
    if(!ret)
    {
        log += "file not found\n";
        log += err;
        return false;
    }
    const tinygltf::Scene& scene = model.scenes[model.defaultScene];
    log += "---SCENE---\n";
    log += scene.name;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<int> indices;
    for(tinygltf::Node node : model.nodes)
    {
        if (node.mesh < 0) continue;
        for(auto bufferView : model.bufferViews)
        {
            log += "---BUFFER_VIEW---\n";
            log += bufferView.name;
        }
        for(tinygltf::Primitive primitive:model.meshes[node.mesh].primitives)
        {
            tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];
            for (auto &attrib : primitive.attributes) {
                tinygltf::Accessor accessor_one = model.accessors[attrib.second];
                int byteStride = accessor_one.ByteStride(model.bufferViews[accessor_one.bufferView]);
                const tinygltf::Buffer &buffer = model.buffers[model.bufferViews[accessor_one.bufferView].buffer];

                const float *positions = reinterpret_cast<const float *>(
                    &buffer.data[model.bufferViews[accessor_one.bufferView].byteOffset + accessor_one.byteOffset]
                );

                int size = 1;
                if (accessor_one.type != TINYGLTF_TYPE_SCALAR) {
                    size = accessor_one.type;
                }
                
                for (size_t v = 0; v < accessor_one.count; ++v) {
                    //ポジション
                    if(attrib.first == "POSITION"){
                        float x = positions[v * 3 + 0];
                        float y = positions[v * 3 + 1];
                        float z = positions[v * 3 + 2];
                        log += "P";
                        log += std::to_string(x);
                        log += " ";
                        log += std::to_string(y);
                        log += " ";
                        log += std::to_string(z);
                        log += " ";
                        log += "\n";
                        vertices.push_back(glm::vec3(x,y,z));
                    }
                    if(attrib.first == "NORMAL"){
                        float x = positions[v * 3 + 0];
                        float y = positions[v * 3 + 1];
                        float z = positions[v * 3 + 2];
                        log += "N";
                        log += std::to_string(x);
                        log += " ";
                        log += std::to_string(y);
                        log += " ";
                        log += std::to_string(z);
                        log += " ";
                        log += "\n";
                        normals.push_back(glm::vec3(x,y,z));
                    }
                }
            }
            if (primitive.indices > -1) {
                const tinygltf::Accessor &indexAccessor = model.accessors[primitive.indices];
                const tinygltf::Buffer &buffer = model.buffers[model.bufferViews[indexAccessor.bufferView].buffer];
                const unsigned char* basePtr = &buffer.data[model.bufferViews[indexAccessor.bufferView].byteOffset + indexAccessor.byteOffset];

                for (size_t v = 0; v < indexAccessor.count; ++v) {
                    uint32_t idx = 0;

                    if (indexAccessor.componentType == 5123) { //UNSIGNED_SHORT
                        const uint16_t* buf = reinterpret_cast<const uint16_t*>(basePtr);
                        idx = buf[v];
                    } 
                    else if (indexAccessor.componentType == 5125) { //UNSIGNED_INT
                        const uint32_t* buf = reinterpret_cast<const uint32_t*>(basePtr);
                        idx = buf[v];
                    }
                    else if (indexAccessor.componentType == 5121) { //UNSIGNED_BYTE
                        idx = basePtr[v];
                    }
                    log += "ID";
                    log += std::to_string(idx);
                    log += "\n";
                    indices.push_back(idx);
                }
                log += " ";
            }
        }
    }
    entity.SetVertices(vertices);
    entity.SetIndices(indices);
    entity.SetNormals(normals);
    return true;
}