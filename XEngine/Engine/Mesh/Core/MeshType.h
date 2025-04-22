#pragma once

#include "../../Math/XMath.h"

struct FVector
{
	FVector(const XMFLOAT3& InVec, const XMFLOAT4& InColor)
		: VectorData(InVec),ColorData(InColor){}

	XMFLOAT3 VectorData;
	XMFLOAT4 ColorData;
};

struct FMeshRenderData
{
	vector<FVector> VertexData;
	vector<uint16_t> IndexData;
};
