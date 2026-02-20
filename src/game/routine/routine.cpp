#include "routine.hpp"
#include <logger.hpp>
//初期化
int Routine::Initialize()
{
    pipeline = new PglPipeline();
    if(pipeline->Initialize() == 1)
    {
        return 1;
    }
    return 0;
}

void Routine::Exit(){
    glfwTerminate();
}
void Routine::Update()
{
    //ウィンドウが終了すべきか
    while (!glfwWindowShouldClose(pipeline->GetWindow())) {
        //Esc押されたら閉じる。
        if (glfwGetKey(pipeline->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(pipeline->GetWindow(), true);
        pipeline->Render();
    }
    pipeline->End();
}

void Routine::LaunchTest()
{
    Log("Testing...");
    pipeline = new PglPipeline();
    pipeline->Initialize();
    pipeline->Render();
    pipeline->End();
    Log("Done...");
}