#pragma once

namespace Aspen
{
	class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach()		 {  };
		virtual void OnDetach()		 {  };

		virtual void OnUpdate()		 {  };

		virtual void OnRender()		 {  };
	};
}