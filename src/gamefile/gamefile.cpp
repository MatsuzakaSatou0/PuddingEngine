#include <fstream>
#include <iostream>
#include <logger.hpp>
#include <parser/gltf_parser.hpp>
#include "gamefile.h"
#include "gamefile_generated.h"
#include "config.h"
void GameFile::SetFragmentShader(std::string shader_source)
{
    fragment_shader.reserve(shader_source.size());
    fragment_shader = shader_source;
    return;
}
void GameFile::SetVertexShader(std::string shader_source)
{
    vertex_shader.reserve(shader_source.size());
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
    Log("Seek pos to 0.");

    std::vector<char> buffer_pointer(size);
    
    file.read(buffer_pointer.data(), size);

    //ゲームのデータ読み込み
    Log("Load Data with FlatBuffer");
    auto gamefile = gamefile::GetGameFile(buffer_pointer.data());
    Log("FlatBuffer Done");
    //バージョンチェック
    if(gamefile->version() != SAVE_VERSION)
    {
        Log("Game files are out of date. Please update your core to the appropriate build.");
        //バージョンが違う場合に、危険なためデバッグモード以外では強制停止。
        if(debugMode)
        {
            Log("The software is in debug mode so the shutdown routine was forcibly exited.");
            Log("The save data update will be performed.");
        }else{
            //離脱ルーチン
            return 1;
        }
    }
    //シェダーのデータ読み込み
    if(gamefile->fragment_shader() != nullptr){
        fragment_shader = gamefile->fragment_shader()->shader()->str();
    }else{
        Log("The fragment shader in the game data was unknown.");
    }

    if(gamefile->vertex_shader() != nullptr){
        vertex_shader = gamefile->vertex_shader()->shader()->str();
    }else{
        Log("The vertex shader in the game data was unknown.");
    }
    //エンティティーデータがあるバージョンかどうか
    if(gamefile->entities() != nullptr){
        //エンティティーのデータ読み込み
        for(auto ent : *gamefile->entities()){
            //entityのメモリはここで消して。
            Entity entity = Entity(glm::vec3(ent->position()->x(),ent->position()->y(),ent->position()->z()));
            
            std::vector<glm::vec3> vercities = {};
            std::vector<glm::vec3> normals = {};
            std::vector<int> indicies = {};
            for(auto ent_vertex : *ent->mesh()->vertex())
            {
                auto vertex = glm::vec3(ent_vertex->x(),ent_vertex->y(),ent_vertex->z());
                vercities.push_back(vertex);
            }
            for(auto ent_normal : *ent->mesh()->normal())
            {
                auto normal = glm::vec3(ent_normal->x(),ent_normal->y(),ent_normal->z());
                normals.push_back(normal);
            }
            for(auto ent_index : *ent->mesh()->indices())
            {
                indicies.push_back(ent_index);
            }
            entity.SetVertices(vercities);
            entity.SetIndices(indicies);
            entity.SetNormals(normals);
            entities.push_back(entity);
        }
    }else{
        //エンティティーデータがないバージョンの場合
        Log("The entities in the game data was unknown.");
    }

    Log("SaveData Load Done");
    return 0;
}
void GameFile::SaveFile()
{
    flatbuffers::FlatBufferBuilder builder(1024);
    //ゲームファイルの設定
    auto name = builder.CreateString("GameFile");
    Log("Saving shader");
    //シェダーの保存
    auto fragmentShaderFile = gamefile::CreateTextFileDirect(builder,GetInstance().fragment_shader.data());
    auto vertexShaderFile = gamefile::CreateTextFileDirect(builder,GetInstance().vertex_shader.data());
    
    /*
    table GameFile{
        vertex_shader:TextFile;
        fragment_shader:TextFile;
        entities:[Entity];
    }
    */
    std::vector<flatbuffers::Offset<gamefile::Entity>> entities_save = {};
    Log("Saving entities");
    //エンティティ取得
    for(auto ent : GetInstance().entities)
    {
        auto vertices_offset = builder.CreateVectorOfStructs(
            reinterpret_cast<const gamefile::Vec3*>(ent.GetVertices().data()), 
            ent.GetVertices().size()
        );
        auto normals_offset = builder.CreateVectorOfStructs(
            reinterpret_cast<const gamefile::Vec3*>(ent.GetNormals().data()), 
            ent.GetNormals().size()
        );
        auto indices_offset = builder.CreateVector(
            ent.GetIndices().data(), 
            ent.GetIndices().size()
        );
        auto g =gamefile::Vec3(ent.GetPosition().x,ent.GetPosition().y,ent.GetPosition().z);
        auto mesh_save = gamefile::CreateMesh(builder,vertices_offset,normals_offset,indices_offset);
        auto entity_save = gamefile::CreateEntity(builder,&g,mesh_save);
        entities_save.push_back(entity_save);
    }
    
    auto finalGameData = gamefile::CreateGameFile(
        builder,
        SAVE_VERSION,
        vertexShaderFile,
        fragmentShaderFile,
        builder.CreateVector(entities_save));

    //書き込み
    builder.Finish(finalGameData);

    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize();

    std::ofstream ofile("game_data.bin", std::ios::binary);

    ofile.write(reinterpret_cast<char*>(buf), size);
    ofile.close();
    return;
}
char* GameFile::GetFragmentShaderPtr()
{
    //割り当て自動化
    GetInstance().fragment_shader.reserve(GetInstance().fragment_shader.size()+4);
    return GetInstance().fragment_shader.data();
}
char* GameFile::GetVertexShaderPtr()
{
    //割り当て自動化
    GetInstance().vertex_shader.reserve(GetInstance().vertex_shader.size()+4);
    return GetInstance().vertex_shader.data();
}
std::vector<Entity>& GameFile::GetEntitiesMut()
{
    return entities;
}
std::vector<Entity> GameFile::GetEntities()
{
    return entities;
}
void GameFile::AddEntity(Entity entity)
{
    entities.push_back(entity);
}