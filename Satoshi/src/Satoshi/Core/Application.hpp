#ifndef APPLICATION_HPP
#define APPLICATION_HPP

namespace Satoshi
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		inline static Application& GetInstance() { return *s_Instance; }
	private:
		static Application* s_Instance;
	};
}

#endif