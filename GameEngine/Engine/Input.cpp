#include "Input.h"

namespace Input
{

		LPDIRECTINPUT8   pDInput = nullptr;				//�|�C���^�Ȃ̂ł��ƂŃ����[�X
		LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;		//�L�[�f�o�C�X
		LPDIRECTINPUTDEVICE8 pMouseDevice = nullptr;	//�}�E�X�f�o�C�X
		BYTE keyState[256] = { 0 };						//������Ă邩�ǂ������肷��ϐ�
		BYTE prevKeyState[256] = { 0 };					//�O�t���[��������Ă����ǂ���
		XMVECTOR mousePosition;

		DIMOUSESTATE mouseState;
		DIMOUSESTATE prevMouseState;



	void Initialize(HWND hWnd)
	{
		//�Ƃ肠���������Ƃ�
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);

		//�L�[�{�[�h
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);					//�f�o�C�X�I�u�W�F�N�g�쐬
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);										//�f�o�C�X�̎�ގw��
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);	//�������x���ݒ�

		//�}�E�X
		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice, nullptr);
		pMouseDevice->SetDataFormat(&c_dfDIMouse);
		pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//�R���g���[���[
	}

	void Update()
	{
		memcpy(&prevKeyState, &keyState, sizeof(keyState));				//�O�t���[���̏�Ԃ��R�s�[
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);		//�L�[���ׂ�

		pMouseDevice->Acquire();
		memcpy(&prevMouseState, &mouseState, sizeof(mouseState));		//�O�t���[���̏�Ԃ��R�s�[
		pMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);	//�L�[���ׂ�
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsKeyDown(int keyCode)
	{
		if ((keyState[keyCode] & 0x80) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsKeyUp(int keyCode)
	{
		if (!(keyState[keyCode] & 0x80) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButton(int buttonCode)
	{
		if (mouseState.rgbButtons[buttonCode]  & 0x80)
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonDown(int buttonCode)
	{
		if ((mouseState.rgbButtons[buttonCode]  & 0x80)&&!(prevMouseState.rgbButtons[buttonCode]  & 0x80))
		{
			return true;
		}
		return false;
	}
	bool IsMouseButtonUp(int buttonCode)
	{
		if (!(mouseState.rgbButtons[buttonCode] & 0x80) && (prevMouseState.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
	}
}