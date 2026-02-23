#include <config.h>

#include <parser/gltf_parser.hpp>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imconfig.h"
#include "imgui.h"
#include "pgl_pipeline.hpp"

#include <graphics/settings.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include <component/camera.hpp>

#include <gamefile/gamefile.h>

#include <logger.hpp>

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

void APIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, 
    GLsizei length, const GLchar* message, const void* userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
    (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}
void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error [" << error << "]: " << description << std::endl;
}

PglPipeline::PglPipeline()
{

}
GLFWwindow* PglPipeline::GetWindow()
{
    return window;
}

void PglPipeline::End()
{
    Log("Destroying the pipeline...");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void PglPipeline::Render()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    #ifdef DEBUG
    //シェーダーが正しく読み込めなかったら
    if(shaderError)
    {
        //シェーダーの失敗の表示
        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
        flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoResize;
        ImGui::SetNextWindowSize(ImVec2(300, 150));
        ImGui::Begin("ShaderNotFound",NULL,flags);
        ImGui::Text("An error occurred while compiling the shader.");
        //リセット用のボタン
        if (ImGui::Button("Reset the shader.")) {
            std::string str1(fragmentShaderSource);
            gameFile->SetFragmentShader(str1);
            std::string str2(vertexShaderSource);
            gameFile->SetVertexShader(str2);
        }
        ImGui::End();
    }
    //シェーダーの設定画面
    if(showShaderMenu){
        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("ShaderSetting",NULL,flags);
        ImGui::InputTextMultiline("VertexShader", gameFile->GetVertexShaderPtr(), 512,ImVec2(300,100));
        ImGui::InputTextMultiline("FragmentShader", gameFile->GetFragmentShaderPtr(), 512,ImVec2(300,100));
        ImGui::End();
    }

    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    //セーブ状態
    ImGui::Begin("SaveMenu",NULL,flags);
    if (ImGui::Button("Save Game")) {
        gameFile->SaveFile();

    }
    ImGui::End();
    
    //メインメニュー
    ImGui::Begin("MainMenu",NULL,flags);
    ImGui::Text("Pudding");
    ImGui::Checkbox("ShaderMenu",&showShaderMenu);
    ImGui::End();

    //エンティティーメニュー
    ImGui::Begin("Entities");
    //インデックス。staticで初期化。
    static int selected_idx = 0;
    //最大256で割り当て
    std::vector<const char*> items(256);
    const char* item_current = items[selected_idx];
    
    int name_count = 0;
    //メッシュ読み込み
    for(auto entity : GameFile::GetInstance().GetEntities())
    {
        if(name_count > 256)
        {
            return;
        }
        items.push_back(entity.GetName().c_str());
        name_count++;
    }
    //エンティティ
    ImGui::Begin("EntityTool",NULL,flags);
    if(ImGui::Button("New Entity"))
    {
        Entity entity = Entity(glm::vec3(0,0,0));
        GameFile::GetInstance().AddEntity(entity);
    }
    ImGui::End();
    //エンティティリスト
    if (ImGui::BeginTable("EntityList", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY))
    {
        ImGui::TableSetupColumn("NAME", ImGuiTableColumnFlags_WidthFixed, 40.0f);
        ImGui::TableSetupColumn("EDITOR", ImGuiTableColumnFlags_WidthFixed, 40.0f);
        ImGui::TableHeadersRow();
        int i = 0;
        for (auto entity : GameFile::GetInstance().GetEntities())
        {
            ImGui::TableNextRow();
            
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(entity.GetName().data());
            ImGui::TableSetColumnIndex(1);
            ImGui::PushID(i);
            if(ImGui::Button("OPEN"))
            {

            }
            ImGui::PopID();
            i++;
        }
        ImGui::EndTable();
    }
    ImGui::Text(debugResult.data());
    ImGui::End();

    #endif

    //ImGui描画
    ImGui::Render();
    
    //背景の色設定
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    //背景を初期化
    glClear(GL_COLOR_BUFFER_BIT);
        
    //頂点データ
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    //頂点配列データを割り当て
    glBindVertexArray(VAO);
    //頂点バッファデータを割り当て
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Camera camera = Camera();
    glm::mat4 view = camera.GetViewMat();
    
    glm::mat4 projection = camera.GetProjectionMat();
    
    glm::mat4 model = glm::mat4(1.0f);

    if(!shaderError)
    {
        glUseProgram(shaderProgram); 
        //シェダーに値転送
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc  = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(projection));
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //フレームバッファをスワップ
    glfwSwapBuffers(window);

    //glfwのイベントを送る。
    glfwPollEvents();

}
bool PglPipeline::GetShaderError(GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        return false;
    }
    return true;
}
int PglPipeline::Initialize()
{
    //エラー用コールバック
    glfwSetErrorCallback(error_callback);
    
    Log("Initializing pipeline...");
    if(GameFile::GetInstance().LoadFile() == 1)
    {
        return 1;
    }
    Log("Game file loading completed");
    
    //初期化、できなければ返す
    if (!glfwInit())
    {
        Log("glfw initialization failed");
        return 1;
    }

    //OpenGLのバージョンを選択　3.3
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    Log("GLSL");
    Log(glsl_version);
    Log("VERSION");
    //ウィンドウ作成
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learn OpenGL", NULL, NULL);

    //ウィンドウがなければ終了。
    if (!window) {
        glfwTerminate();
        Log("Window creation failed");
        return 1;
    }

    //winowにコンテキスト作成
    glfwMakeContextCurrent(window);

    //GLを読み込み
    if (!gladLoadGL(glfwGetProcAddress)) {
        Log("Load GL(glad) failed");
        return 1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugMessageCallback, 0);

    //シェダーの処理
    Log("Processing Shaders");
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* ptr1 = gameFile->GetVertexShaderPtr();
    glShaderSource(vertexShader, 1, &ptr1, NULL);
    glCompileShader(vertexShader);

    shaderError = false;

    if(!GetShaderError(vertexShader))
    {
        shaderError = true;
        Log("The shader error flag was turned on.(vertex)");
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* ptr2 = gameFile->GetFragmentShaderPtr();
    glShaderSource(fragmentShader, 1, &ptr2, NULL);
    glCompileShader(fragmentShader);
    
    if(!GetShaderError(fragmentShader))
    {
        shaderError = true;
        Log("The shader error flag was turned on.(fragment)");
    }
    if(shaderError == false){
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
    }

    //3.0からの、割り当てのもの。
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    Log("Initializing ImGUI");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   

    ImGui::StyleColorsDark();
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init(glsl_version);
    return 0;
}