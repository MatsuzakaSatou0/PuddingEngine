#include <graphics/opengl/pgl_pipeline.hpp>
class Routine
{
public:
    int Initialize();
    void Update();
    void Exit();
    void LaunchTest();
private:
    PglPipeline* pipeline;
};