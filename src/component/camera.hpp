#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
    glm::mat4 GetViewMat();
    glm::mat4 GetProjectionMat();
private:
    glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
    float fov = glm::radians(45.0f);
    float aspect = 800.0f / 600.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
};