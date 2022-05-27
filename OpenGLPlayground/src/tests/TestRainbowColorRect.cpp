#include "TestRainbowColorRect.h"

#include <math.h>

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {
    TestRainbowColorRect::TestRainbowColorRect()
        : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_Translation(480, 270, 0), m_Hue(0.0f), m_Period(2.0f)
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
        m_Shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	}

    TestRainbowColorRect::~TestRainbowColorRect()
	{
	}

	void TestRainbowColorRect::OnUpdate(float deltaTime)
	{
        m_Period = fmax(m_Period, 0.0f);
        if (m_Period > 0.0f)
            m_Hue += deltaTime / m_Period * 360.0f;
        m_Hue = fmod(m_Hue, 360.0f);
	}

	void TestRainbowColorRect::OnRender()
	{
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
            glm::mat4 mvp = m_Proj * m_View * model;
            float color[4];
            HSVAToRGBA(m_Hue, 1.0f, 1.0f, 1.0f, color);
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
	}

	void TestRainbowColorRect::OnImGuiRender()
	{
        ImGui::SliderFloat2("Translation", &m_Translation.x, 0.0f, 960.0f);
        ImGui::InputFloat("Color Cycle Period (s)", &m_Period);
        ImGui::DragFloat("Color Cycle Period (s)", &m_Period, 0.005f, 0.0f, FLT_MAX, "%.3f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Text("NOTE: Setting Color Cycle Period to 0.0s stops the rainbow animation.");
        ImGui::Text("Hue (deg.): %d", (unsigned int)m_Hue);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

    void TestRainbowColorRect::HSVAToRGBA(float h, float s, float v, float a, float rgbaArray[4])
    {
        float r, g, b; // 0.0-1.0

        int   hi = (int)(h / 60.0f) % 6;
        float f = (h / 60.0f) - hi;
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));

        switch (hi) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
        default: r = g = b = 0.0f;   break;
        }

        rgbaArray[0] = r;
        rgbaArray[1] = g;
        rgbaArray[2] = b;
        rgbaArray[3] = a;
    }
}