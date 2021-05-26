#ifndef DEMO_LAYER_HPP
#define DEMO_LAYER_HPP

#include <Satoshi/Satoshi.hpp>

class DemoLayer : public Satoshi::Layer
{
public:
	virtual void OnAttach() override{}
	virtual void OnDetach() override{}
	virtual void OnUpdate() override{}
	virtual void OnImGuiRender() override
	{
		ImGui::ShowDemoWindow(&m_Show);
	}
	virtual void OnEvent(Satoshi::Event& event) override{}
private:
	bool m_Show = true;
};

#endif
