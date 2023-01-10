#pragma once
#include<vector>
#include<string>

namespace ImageManager
{
	/// <summary>
	/// �摜���[�h
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <returns>�摜�ԍ�</returns>
	int Load(std::string fileName);
	
	/// <summary>
	/// �摜�`��
	/// </summary>
	/// <param name="imageHandle">�摜�ԍ�</param>
	void Draw(int imageHandle);
	
	/// <summary>
	/// �摜�̐؂蔲���͈̓��Z�b�g
	/// </summary>
	/// <param name="imageHandle">�摜�ԍ�</param>
	void ResetRect(int imageHandle);
	
	/// <summary>
	/// �摜�̐؂蔲���͈͐ݒ�
	/// </summary>
	/// <param name="imageHandle">�摜�ԍ�</param>
	/// <param name="top">��</param>
	/// <param name="bottom">��</param>
	/// <param name="left">��</param>
	/// <param name="right">�E</param>
	void SetRect(int imageHandle,int top,int bottom,int left,int right);
};

