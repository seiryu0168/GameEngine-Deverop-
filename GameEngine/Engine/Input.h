#pragma once

#include <dInput.h>
#include"Direct3D.h"
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")
#include"SAFE_DELETE_RELEASE.h"

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	//�L�[�{�[�h
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);

	//�}�E�X
	bool IsMouseButton(int buttonCode);
	bool IsMouseButtonDown(int buttonCode);
	bool IsMouseButtonUp(int buttonCode);

	XMVECTOR GetMousePosition();
	void SetMousePosition(int x, int y);
	void Release();
};