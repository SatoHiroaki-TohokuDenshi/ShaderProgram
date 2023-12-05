#pragma once

#include <dInput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

namespace Input {
	// ‰Šú‰»
	void Initialize(HWND hWnd);
	
	// XV
	void Update();

	// ‰Ÿ‚µ‚Ä‚¢‚é‚©
	bool IsKey(int keyCode);

	// ‰Ÿ‚³‚ê‚½‚©
	bool IsKeyDown(int keyCode);

	// —£‚³‚ê‚½‚©
	bool IsKeyUp(int keyCode);

	// ‰ğ•ú
	void Release();
};