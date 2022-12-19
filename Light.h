#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <wrl.h>
#include "DirectXCommon.h"
class Light
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	struct ConstBufferData {
		XMVECTOR lightv;		//ライトへの方向を表すベクトル
		XMFLOAT3 lightcolor;	//ライトの色
	};
private:
	static ID3D12Device* device;
public:
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device);
	


	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns></returns>
	static Light* Create();
private:
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	ConstBufferData* constMap;
	//ライト光線方向(単位ベクトル)
	XMVECTOR lightdir = { 1,0,0,0 };
	//ライトの色
	XMFLOAT3 lightcolor = { 1,1,1 };
	//ダーティフラグ
	bool dirty = false;
public:
	void Initialize();
	void TransferConstBuffer();
	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightdir">ライト方向</param>
	void SetLightDir(const DirectX::XMVECTOR& lightdir);
	/// <summary>
	/// ライトの色をセット
	/// </summary>
	/// <param name="lightcolor">ライト色</param>
	void SetLightColor(const XMFLOAT3& lightcolor);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);
};

