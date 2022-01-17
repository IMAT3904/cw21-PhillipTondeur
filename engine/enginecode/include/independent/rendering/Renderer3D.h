/**\file Renderer3D.h*/
#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "rendering/vertexArray.h"
#include "rendering/shader.h"
#include "rendering/texture.h"
#include "rendering/shaderDataType.h"
#include "RenderAPI.h"

namespace Engine
{
	using SceneWideUniforms = std::unordered_map < const char*, std::pair<ShaderDataType, void*>>;
	
	/**\class Material
	**\ brief Hold a shader and the unifrom data associated with the shader
	*/
	class Material
	{
	public:
		Material(const std::shared_ptr<Shader>& shader) :
			m_shader(shader), m_flags(0), m_texture(nullptr), m_tint(glm::vec4(0.f))
		{}
		
		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const glm::vec4& tint) :
			m_shader(shader), m_texture(texture), m_tint(tint)
		{
			setFlag(flag_texture | flag_tint);
		}

		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) :
			m_shader(shader), m_texture(texture), m_tint(glm::vec4(0.f))
		{
			setFlag(flag_texture );
		}

		Material(const std::shared_ptr<Shader>& shader,const glm::vec4& tint) :
			m_shader(shader),m_texture(nullptr), m_tint(tint)
		{
			setFlag(flag_tint);
		}

		inline std::shared_ptr<Shader> getShader() const { return m_shader; } //!< Reference to Getting the shader
		inline std::shared_ptr<Texture> getTexture() const { return m_texture; } //!< getting the texture
		inline glm::uvec4 getTint() const { return m_tint; } //!< getting the tint
		bool isFlagSet(uint32_t flag) const { return m_flags & flag; } //!< want to know if the flags are set

		void setTexture(const std::shared_ptr<Texture>& texture) { m_texture = texture; }
		void setTint(const glm::vec4& tint) { m_tint = tint; }
		constexpr static uint32_t flag_texture = 1 << 0; //!< 000000001
		constexpr static uint32_t flag_tint = 1 << 1; //!< 000000010
	private:
		uint32_t m_flags = 0; //!< Bitfield representation of the shader settings
		std::shared_ptr<Shader> m_shader; //!< the materials shader
		std::shared_ptr<Texture> m_texture; //!< The texture to be applied to the material
		glm::vec4 m_tint;//!< Colour tinit to be applied to the geometry
		void setFlag(uint32_t flag) 
		{
			m_flags = m_flags | flag;
		}
	};
	/**\class Renderer3D
	**\ brief a class which renders 3D geometry instantly (non-batched)
	*/
	class Renderer3D
	{
	public:
		static void init();//!< Init the render 
		static void begin(const SceneWideUniforms& sceneWideUniforms);//!< begin a new 3D Scene
		static void submit(const std::shared_ptr<VertexArray>& geometry,const std::shared_ptr<Material>& material, const glm::mat4& model); //!< Submit the piece of geometry to be rendered 
		static void end(); //!< End the current 3D Scene
	private:
		struct InternalData
		{
			SceneWideUniforms SceneWideUniforms; //!< Replace with UBO at some point 
			std::shared_ptr<Texture> defaultTexture; //!< Empty white texture
			glm::vec4 defaultTint;
		};

		static std::shared_ptr<InternalData> s_data; //!< Data Internal to the renderer 
	};
}