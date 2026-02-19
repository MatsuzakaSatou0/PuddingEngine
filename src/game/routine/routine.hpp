#include <graphics/opengl/pgl_pipeline.hpp>
class Routine
{
public:
    void Initialize();
    void Update();
    void Exit();
private:
    PglPipeline* pipeline;
};