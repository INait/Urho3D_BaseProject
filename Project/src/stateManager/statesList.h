#pragma once

#include "utility/simpleTypes.h"

namespace GameStates
{
	enum GameState : U32
	{
		START_MAIN_MENU,
		MENU_PROPERTIES,
		VIDEO_PROPERTIES,
		AUDIO_PROPERTIES,
		CONTROLS_PROPERTIES,
		Count
	};
};
