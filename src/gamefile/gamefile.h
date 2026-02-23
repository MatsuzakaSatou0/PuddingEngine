#pragma once
#include <vector>
#include <entity/entity.hpp>
#include <gamefile_generated.h>
#include <string>

class GameFile
{
public:
    //シングルトン
    static GameFile& GetInstance() {
        static GameFile instance;
        return instance;
    }
    GameFile(const GameFile&) = delete;
    GameFile& operator=(const GameFile&) = delete;
    GameFile(GameFile&&) = delete;
    GameFile& operator=(GameFile&&) = delete;

    void SetFragmentShader(std::string shader_source);
    void SetVertexShader(std::string shader_source);
    void SaveFile();
    int LoadFile();
    char* GetFragmentShaderPtr();
    char* GetVertexShaderPtr();
    std::vector<Entity> GetEntities();
    void AddEntity(Entity entity);
private:
    GameFile() {
    }
    ~GameFile() = default;
    std::string fragment_shader = "";
    std::string vertex_shader = "";
    std::vector<Entity> entities;
};