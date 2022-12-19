#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <wrl.h>
#include "DirectXCommon.h"
class Light
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	struct ConstBufferData {
		XMVECTOR lightv;		//���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightcolor;	//���C�g�̐F
	};
private:
	static ID3D12Device* device;
public:
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* device);
	


	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns></returns>
	static Light* Create();
private:
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	ConstBufferData* constMap;
	//���C�g��������(�P�ʃx�N�g��)
	XMVECTOR lightdir = { 1,0,0,0 };
	//���C�g�̐F
	XMFLOAT3 lightcolor = { 1,1,1 };
	//�_�[�e�B�t���O
	bool dirty = false;
public:
	void Initialize();
	void TransferConstBuffer();
	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightdir">���C�g����</param>
	void SetLightDir(const DirectX::XMVECTOR& lightdir);
	/// <summary>
	/// ���C�g�̐F���Z�b�g
	/// </summary>
	/// <param name="lightcolor">���C�g�F</param>
	void SetLightColor(const XMFLOAT3& lightcolor);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);
};

