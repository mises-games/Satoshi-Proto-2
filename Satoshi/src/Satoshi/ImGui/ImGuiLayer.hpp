#ifndef IM_GUI_LAYER_HPP
#define IM_GUI_LAYER_HPP

#include <Satoshi/Core/Layer.hpp>

namespace Satoshi {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		virtual void Begin() {}
		virtual void End() {}

		static ImGuiLayer* CreateImGuiLayer();
	private:
		float m_Time = 0.0f;
	};

}

#endif // !1
