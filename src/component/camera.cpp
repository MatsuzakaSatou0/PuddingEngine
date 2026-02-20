#include <component/camera.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::GetViewMat(){
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}
glm::mat4 Camera::GetProjectionMat()
{
    glm::mat4 projection = glm::perspective(fov, aspect, nearPlane, farPlane);
    return projection;
}