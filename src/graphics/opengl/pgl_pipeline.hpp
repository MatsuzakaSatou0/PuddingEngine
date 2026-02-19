#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <gamefile/gamefile.h>

class PglPipeline
{
public:
    PglPipeline();
    bool GetShaderError(GLuint);
    GLFWwindow* GetWindow();
    int Initialize();
    void Render();
    void End();
private:
    GameFile* gameFile;
    GLFWwindow* window;
    GLuint VAO,VBO;
    bool shaderError;

    //表示中のメニュー
    bool showShaderMenu;

    unsigned int shaderProgram;
    unsigned int fragmentShader;
    unsigned int vertexShader;
    bool show_demo_window = true;
};