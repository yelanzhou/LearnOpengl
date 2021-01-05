#include "Light.h"

Light::Light()
    :_cutterOff(glm::cos(glm::radians(12.5)))
    ,_outerCutterOff(glm::cos(glm::radians(17.5)))
    ,_lightType(LightType::Point)
{
}

Light::~Light()
{
}

void Light::setPosition(glm::vec3 pos)
{
    _pos = pos;
}

void Light::setDirection(glm::vec3 dir)
{
    _dir = dir;
}

void Light::setLightType(LightType type)
{
    _lightType = type;
}

void Light::setAmbientColor(glm::vec4 color)
{
    _ambientColor = color;
}

void Light::setDiffuseColor(glm::vec4 color)
{
    _diffuseColor = color;
}

void Light::setSpecularColor(glm::vec4 color)
{
    _specularColor = color;
}

void Light::setAttenuationConstant(float val)
{
    _attenuationConstant = val;
}

void Light::setAttenuationLinear(float val)
{
    _attenuationLinear = val;
}

void Light::setAttenuationQuadartic(float val)
{
    _attenuationQuadartic = val;
}

void Light::setCutterOff(float val)
{
    _cutterOff = val;
}

void Light::setOuterCutterOff(float val)
{
    _outerCutterOff = val;
}

glm::vec3 Light::getPosition()
{
    return _pos;
}

glm::vec3 Light::getDirection()
{
    return _dir;
}

Light::LightType Light::getLightType()
{
    return _lightType;
}

glm::vec4 Light::getAmbientColor()
{
    return _ambientColor;
}

glm::vec4 Light::getDiffuseColor()
{
    return _diffuseColor;
}

glm::vec4 Light::getSpecularColor()
{
    return _specularColor;
}

float Light::getAttenuationConstant()
{
    return _attenuationConstant;
}

float Light::getAttenuationLinear()
{
    return _attenuationLinear;
}

float Light::getAttenuationQuadartic()
{
    return _attenuationQuadartic;
}

float Light::getCutterOff()
{
    return _cutterOff;
}

float Light::getOuterCutterOff()
{
    return _outerCutterOff;
}
