#pragma once
#include "Test.h"

namespace test {
	class TestSimpleRect : public Test
	{
	public:
		TestSimpleRect();
		~TestSimpleRect();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_RectColor[4];
	};
}


