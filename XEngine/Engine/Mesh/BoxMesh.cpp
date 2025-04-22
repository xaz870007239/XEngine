#include "BoxMesh.h"

void BoxMesh::Init()
{
	Super::Init();
}

void BoxMesh::BuildMesh(const FMeshRenderData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);
}

void BoxMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

BoxMesh* BoxMesh::CreateMesh()
{
	FMeshRenderData MeshRenderData;
	MeshRenderData.PosData.push_back(FVector{ XMFLOAT3{0.f,0.f,0.f}, XMFLOAT4{Colors::White} });
	MeshRenderData.PosData.push_back(FVector{ XMFLOAT3{0.f,1.f,0.f}, XMFLOAT4{Colors::White} });
	MeshRenderData.PosData.push_back(FVector{ XMFLOAT3{1.f,1.f,0.f}, XMFLOAT4{Colors::White} });
	MeshRenderData.PosData.push_back(FVector{ XMFLOAT3{1.f,0.f,0.f}, XMFLOAT4{Colors::White} });
	MeshRenderData.PosData.push_back(FVector{ XMFLOAT3{0.f,0.f,1.f}, XMFLOAT4{Colors::White} });
	MeshRenderData.PosData.push_back(FVector{ XMFLOAT3{0.f,1.f,1.f}, XMFLOAT4{Colors::White} });
	MeshRenderData.PosData.push_back(FVector{ XMFLOAT3{1.f,1.f,1.f}, XMFLOAT4{Colors::White} });
	MeshRenderData.PosData.push_back(FVector{ XMFLOAT3{1.f,0.f,1.f}, XMFLOAT4{Colors::White} });
	
	//front
	MeshRenderData.IndexData.push_back(0);
	MeshRenderData.IndexData.push_back(1);
	MeshRenderData.IndexData.push_back(2);
	MeshRenderData.IndexData.push_back(0);
	MeshRenderData.IndexData.push_back(2);
	MeshRenderData.IndexData.push_back(3);

	//back
	MeshRenderData.IndexData.push_back(4);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(5);
	MeshRenderData.IndexData.push_back(4);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(7);

	//left
	MeshRenderData.IndexData.push_back(4);
	MeshRenderData.IndexData.push_back(5);
	MeshRenderData.IndexData.push_back(1);
	MeshRenderData.IndexData.push_back(4);
	MeshRenderData.IndexData.push_back(1);
	MeshRenderData.IndexData.push_back(0);

	//right
	MeshRenderData.IndexData.push_back(3);
	MeshRenderData.IndexData.push_back(2);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(3);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(0);

	//up
	MeshRenderData.IndexData.push_back(1);
	MeshRenderData.IndexData.push_back(5);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(1);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(0);

	//down
	MeshRenderData.IndexData.push_back(4);
	MeshRenderData.IndexData.push_back(0);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(4);
	MeshRenderData.IndexData.push_back(3);
	MeshRenderData.IndexData.push_back(0);

	BoxMesh* Result = new BoxMesh();
	Result->BuildMesh(&MeshRenderData);
	Result->Init();
	return Result;
}
 
