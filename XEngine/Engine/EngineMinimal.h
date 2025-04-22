#include "../3dparty/simple_library/public/simple_library.h"
#include "../Engine/Config/EngineRenderConfig.h"
#include "EngineDebug/EngineLog/EngineLog.h"
#include "EngineDebug/EngineDebug.h"
#include <vector>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include <wrl.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

#include "Rendering/DirectX12/d3dx12.h"
#include "Core/Engine.h"

using namespace Microsoft::WRL;
using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

extern class FEngine* Engine;
