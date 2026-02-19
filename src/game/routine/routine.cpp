//ルーチン
#include "routine.hpp"

//初期化
void Routine::Initialize()
{
    pipeline = new PglPipeline();
    pipeline->Initialize();
}
//

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
    