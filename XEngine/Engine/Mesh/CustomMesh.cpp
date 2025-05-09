#include "CustomMesh.h"

void CCustomMesh::Init()
{
	Super::Init();
}

void CCustomMesh::BuildMesh(const FMeshRenderData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);
}

void CCustomMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

CCustomMesh* CCustomMesh::CreateMesh(const string& InPath)
{
	FMeshRenderData MeshData;

	{
		unsigned int FileSize = get_file_size_by_filename(InPath.c_str());
		char* Buffer = new char[FileSize + 1];
		memset(Buffer, 0, FileSize + 1);
		get_file_buf(InPath.c_str(), Buffer);

		if (!LoadObjFromBuffer(Buffer, FileSize, MeshData))
		{
			XLog_Error("LoadObjFromBuffer failed!");
		}

		delete Buffer;
	}

	CCustomMesh* CustomMesh = new CCustomMesh();
	CustomMesh->BuildMesh(&MeshData);
	CustomMesh->Init();
	return CustomMesh;
}

bool CCustomMesh::LoadObjFromBuffer(char* InBuff, uint32_t InBuffSize, FMeshRenderData& RenderData)
{
	if (InBuffSize > 0)
	{
		stringstream BuffStream{InBuff};
		char TmpLine[256] = { 0 };
		string Tmp{};
		//while (!BuffStream.eof())
		for ( ;!BuffStream.eof(); )
		{
			memset(TmpLine, 0, 256);
			BuffStream.getline(TmpLine, 256);
			
			if (strlen(TmpLine) < 0)
			{
				continue;
			}

			if (TmpLine[0] == 'v')
			{
				stringstream LineStream{ TmpLine };
				if (TmpLine[1] == 'n')
				{
					
				}
				else if (TmpLine[1] == 't')
				{
				
				}
				else
				{
					RenderData.VertexData.push_back(FVector{XMFLOAT3{}, XMFLOAT4{Colors::White}});

					int TopIndex = RenderData.VertexData.size() - 1;
					XMFLOAT3& Float3InPos = RenderData.VertexData[TopIndex].VectorData;

					LineStream >> Tmp;
					LineStream >> Float3InPos.x;
					LineStream >> Float3InPos.y;
					LineStream >> Float3InPos.z;
				}
			}
			else if (TmpLine[0] == 'f')
			{
				stringstream LineStream{ TmpLine };
				LineStream >> Tmp;
				
				char SaveLineString[256] = { 0 };
				char TmpBuff[256] = { 0 };
				for (size_t i = 0; i < 3; ++i)
				{
					memset(SaveLineString, 0, 256);
					LineStream >> SaveLineString;

					int StringPosA = find_string(SaveLineString, "/", 0);
					memset(TmpBuff, 0, 256);
					char* VPosIndex = string_mid(SaveLineString, TmpBuff, 0, StringPosA);

					RenderData.IndexData.push_back(atoi(VPosIndex));

					int StringPosB = find_string(SaveLineString, "/", StringPosA + 1);
					memset(TmpBuff, 0, 256);
					char* TexcoordIndex = string_mid(SaveLineString, TmpBuff, StringPosA + 1, StringPosB - (StringPosA + 1));

					memset(TmpBuff, 0, 256);
					char* NomrmalIndex = string_mid(SaveLineString, TmpBuff, StringPosB + 1, strlen(SaveLineString));
				}
			}
		}
	}

	return false;
}
