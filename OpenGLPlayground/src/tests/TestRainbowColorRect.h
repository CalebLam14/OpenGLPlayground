#pragma once
#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

namespace test {
	class TestRainbowColorRect : public Test
	{
	public:
		TestRainbowColorRect();
		~TestRainbowColorRect();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		void HSVAToRGBA(float h, float s, float v, float a, float rgbaArray[4]);
		glm::vec3 m_Translation;
		float m_Hue;
		float m_Period;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
	};
}


