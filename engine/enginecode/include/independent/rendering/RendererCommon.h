/**\file rendererCommon.h*/

#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>

#include "rendering/vertexArray.h"
#include "rendering/shader.h"
#include "rendering/texture.h"

#include "rendering/shaderDataType.h"
namespace Engine
{
	using SceneWideUniforms = std::unordered_map < const char*, std::pair<ShaderDataType, void*>>;
}