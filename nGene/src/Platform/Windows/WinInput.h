#pragma once

#include "nGene/Input.h"

namespace nGene {
	class WinInput: public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		/*virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;*/
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}

