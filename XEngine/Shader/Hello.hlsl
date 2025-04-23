cbuffer ConstBuffer : register(b0)
{
    float4x4 World;
}

struct MeshVertex
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct MeshVertexOut
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

MeshVertexOut VS_Main(MeshVertex MV)
{
    MeshVertexOut Out;
     
    Out.Position = mul(float4(MV.Position, 1.0f), World);
    Out.Color = MV.Color;

    return Out;
}

float4 PS_Main(MeshVertexOut PS) : SV_TARGET
{
    return PS.Color;
}
