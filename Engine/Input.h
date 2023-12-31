#pragma once

#include <dInput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

namespace Input {
	// 初期化
	void Initialize(HWND hWnd);
	
	// 更新
	void Update();

	// 押しているか
	bool IsKey(int keyCode);

	// 押されたか
	bool IsKeyDown(int keyCode);

	// 離されたか
	bool IsKeyUp(int keyCode);

	// 解放
	void Release();
};