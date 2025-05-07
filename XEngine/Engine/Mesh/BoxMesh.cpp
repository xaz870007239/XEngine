#include "BoxMesh.h"

void CBoxMesh::Init()
{
	Super::Init();
}

void CBoxMesh::BuildMesh(const FMeshRenderData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);
}

void CBoxMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

CBoxMesh* CBoxMesh::CreateMesh()
{
	FMeshRenderData MeshRenderData;
	MeshRenderData.VertexData.push_back(FVector{ XMFLOAT3{0.f,0.f,0.f}, XMFLOAT4{Colors::White} });
	MeshRenderData.VertexData.push_back(FVector{ XMFLOAT3{0.f,1.f,0.f}, XMFLOAT4{Colors::AliceBlue} });
	MeshRenderData.VertexData.push_back(FVector{ XMFLOAT3{1.f,1.f,0.f}, XMFLOAT4{Colors::Aqua} });
	MeshRenderData.VertexData.push_back(FVector{ XMFLOAT3{1.f,0.f,0.f}, XMFLOAT4{Colors::Aquamarine} });
	MeshRenderData.VertexData.push_back(FVector{ XMFLOAT3{0.f,0.f,1.f}, XMFLOAT4{Colors::Red} });
	MeshRenderData.VertexData.push_back(FVector{ XMFLOAT3{0.f,1.f,1.f}, XMFLOAT4{Colors::Blue} });
	MeshRenderData.VertexData.push_back(FVector{ XMFLOAT3{1.f,1.f,1.f}, XMFLOAT4{Colors::Green} });
	MeshRenderData.VertexData.push_back(FVector{ XMFLOAT3{1.f,0.f,1.f}, XMFLOAT4{Colors::Gray} });
	
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
	MeshRenderData.IndexData.push_back(7);
	MeshRenderData.IndexData.push_back(6);

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
	MeshRenderData.IndexData.push_back(7);

	//up
	MeshRenderData.IndexData.push_back(1);
	MeshRenderData.IndexData.push_back(5);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(1);
	MeshRenderData.IndexData.push_back(6);
	MeshRenderData.IndexData.push_back(2);

	//down
	MeshRenderData.IndexData.push_back(4);
	MeshRenderData.IndexData.push_back(0);
	MeshRenderData.IndexData.push_back(3);
	MeshRenderData.IndexData.push_back(4);
	MeshRenderData.IndexData.push_back(3);
	MeshRenderData.IndexData.push_back(7);

	CBoxMesh* Result = new CBoxMesh();
	Result->BuildMesh(&MeshRenderData);
	Result->Init();
	return Result;
}
 
