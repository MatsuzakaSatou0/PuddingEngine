#pragma once
#include <gamefile_generated.h>

class GameFile
{
public:
    void SetFragmentShader(std::string shader_source);
    void SetVertexShader(std::string shader_source);
    void SaveFile();
    int LoadFile();
    char* GetFragmentShaderPtr();
    char* GetVertexShaderPtr();
private:
    std::string fragment_shader = "";
    std::string vertex_shader = "";
};