#pragma once

#include "../CompiledHeaders.h"

//===== Check if the OS is Linux =====//
#ifdef LINUX

#define LINUX_H_

#include "../WindowAPI.h"
#include "../WindowManager.h"

namespace WindowAPI
{
	class Linux : public Window
	{

	};
}

#endif // LINUX