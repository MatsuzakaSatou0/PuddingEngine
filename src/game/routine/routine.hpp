#include <graphics/opengl/pgl_pipeline.hpp>
class Routine
{
public:
    void Initialize();
    void Update();
    void Exit();
    void LaunchTest();
private:
    PglPipeline* pipeline;
};