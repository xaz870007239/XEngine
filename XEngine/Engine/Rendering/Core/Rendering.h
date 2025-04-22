#pragma once

#include "../../EngineMinimal.h"

class FRenderingInterface
{
public:
	friend class FWinEngine;

	FRenderingInterface();
	~FRenderingInterface();

	virtual void Init();
	virtual void Draw(float DeltaTime);

	bool operator==(const FRenderingInterface& Other)
	{
		return guid_equal(&Other.GUID, &GUID);
	}

	simple_c_guid GetGUID() const { return GUID; }

	ComPtr<ID3D12Device> GetDXDevice() const;
	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;

	ComPtr<ID3D12Resource> ConstructDefaultBuffer(ComPtr<ID3D12Resource>& OutTmpBuffer, const void* InData, UINT64 InDataSize);

protected:
	static vector<FRenderingInterface*> RenderingInterfaces;
	simple_c_guid GUID;
};