#include <string>
#include <fstream>
#include <iostream>
#include <logger.hpp>
#include "gamefile.h"
#include "gamefile_generated.h"
//0x55555580b360
void GameFile::SetFragmentShader(std::string shader_source)
{
    fragment_shader = shader_source;
    return;
}
void GameFile::SetVertexShader(std::string shader_source)
{
    vertex_shader = shader_source;
    return;
}
int GameFile::LoadFile()
{
    Log("Creating a pudding file.");
    std::ifstream file("game_data.bin", std::ios::binary | std::ios::ate);
    Log("Loading game data...");
    if (!file) {
        Log("No game data found.");
        return 1;
    }
    std::streamsize size = file.tellg();
    if(size == -1)
    {
        return 1;
    }
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer_pointer(size);

    file.read(buffer_pointer.data(), size);

    auto gamefile = gamefile::GetGameFile(buffer_pointer.data());

    fragment_shader = gamefile->fragment_shader()->shader()->str();

    vertex_shader = gamefile->vertex_shader()->shader()->str();
    return 0;
}
void GameFile::SaveFile()
{
    flatbuffers::FlatBufferBuilder builder(1024);

    auto name = builder.CreateString("GameFile");

    auto fragmentShaderFile = gamefile::CreateTextFileDirect(builder,fragment_shader.data());
    auto vertexShaderFile = gamefile::CreateTextFileDirect(builder,vertex_shader.data());
    auto mloc = gamefile::CreateGameFile(builder,vertexShaderFile,fragmentShaderFile);

    builder.Finish(mloc);

    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize();

    std::ofstream ofile("game_data.bin", std::ios::binary);

    ofile.write(reinterpret_cast<char*>(buf), size);
    ofile.close();
    return;
}
char* GameFile::GetFragmentShaderPtr()
{
    fragment_shader += "\0";
    return fragment_shader.data();
}
char* GameFile::GetVertexShaderPtr()
{
    fragment_shader += "\0";
    return vertex_shader.data();
}