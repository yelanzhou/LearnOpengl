#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
    enum class LightType
    {
       Point,
       Direction,
       Spot,
    };

    Light();
    ~Light();

    void setPosition(glm::vec3 pos);
    void setDirection(glm::vec3 dir);
    void setLightType(LightType type);
    void setAmbientColor(glm::vec4 color);
    void setDiffuseColor(glm::vec4 color);
    void setSpecularColor(glm::vec4 color);
    void setAttenuationConstant(float val);
    void setAttenuationLinear(float val);
    void setAttenuationQuadartic(float val);
    void setCutterOff(float val);
    void setOuterCutterOff(float val);

    glm::vec3 getPosition();
    glm::vec3 getDirection();
    LightType getLightType();
    glm::vec4 getAmbientColor();
    glm::vec4 getDiffuseColor();
    glm::vec4 getSpecularColor();
    float getAttenuationConstant();
    float getAttenuationLinear();
    float getAttenuationQuadartic();

    //用点积表示
    float getCutterOff();
    float getOuterCutterOff();

private:

    LightType _lightType = LightType::Point;

    glm::vec3  _pos;
    glm::vec3  _dir;
    glm::vec4 _diffuseColor = glm::vec4(0.8,0.8,0.8,1);
    glm::vec4 _ambientColor = glm::vec4(0.05,0.05,0.05,1);
    glm::vec4 _specularColor = glm::vec4(1.0,1.0,1.0,1.0);

    float     _attenuationConstant = 1.0f;
    float     _attenuationLinear = 1.09f;
    float     _attenuationQuadartic = 0.032f;
    float    _cutterOff;
    float    _outerCutterOff;
};