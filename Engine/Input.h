#pragma once

#include <dInput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

namespace Input {
	// ������
	void Initialize(HWND hWnd);
	
	// �X�V
	void Update();

	// �����Ă��邩
	bool IsKey(int keyCode);

	// �����ꂽ��
	bool IsKeyDown(int keyCode);

	// �����ꂽ��
	bool IsKeyUp(int keyCode);

	// ���
	void Release();
};