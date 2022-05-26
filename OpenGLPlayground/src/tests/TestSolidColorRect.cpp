#include "TestSolidColorRect.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {
	TestSolidColorRect::TestSolidColorRect()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Translation(480, 270, 0), m_RectColor{ 1.0f, 1.0f, 0.0f, 1.0f }
	{
        float points[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f,
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(points, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("res/shaders/basic_color.shader");
        m_Shader->Bind();

        /* Provide u_Color uniform */
        m_Shader->SetUniform4f("u_Color", m_RectColor[0], m_RectColor[1], m_RectColor[2], m_RectColor[3]);
	}

	TestSolidColorRect::~TestSolidColorRect()
	{
	}

	void TestSolidColorRect::OnUpdate(float deltaTime)
	{
	}

	void TestSolidColorRect::OnRender()
	{
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", m_RectColor[0], m_RectColor[1], m_RectColor[2], m_RectColor[3]);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
	}

	void TestSolidColorRect::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation A", &m_Translation.x, 0.0f, 960.0f);
        ImGui::ColorEdit4("Color", m_RectColor);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}