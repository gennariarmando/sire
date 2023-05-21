#pragma once
 //#define SIRE_INCLUDE_DX9
 //#define SIRE_INCLUDE_DX10
#define SIRE_INCLUDE_DX11
//#define SIRE_INCLUDE_DX12
//#define SIRE_INCLUDE_OPENGL
//#define SIRE_INCLUDE_VULKAN

#include <iostream>
#include <vector>

#if SIRE_INCLUDE_DX9
#include <d3d9.h>
#include <DirectXMath.h>
#endif

#ifdef SIRE_INCLUDE_DX10
#include <d3d10.h>
#include <dxgi.h>
#include <DirectXMath.h>
#endif

#ifdef SIRE_INCLUDE_DX11
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3dcompiler.lib")
#endif

#ifdef SIRE_INCLUDE_DX12
#include <d3d12.h>
#include <dxgi.h>
#include <DirectXMath.h>
#endif

class Sire {
public:
	inline enum eSireProjection {
		ORTHOGRAPHIC,
		PERSPECTIVE,
	};

	inline enum eRenderState {
		D3DRS_ALPHATESTENABLE,
		D3DRS_SRCBLEND,
		D3DRS_DESTBLEND,
		D3DRS_BLENDOP,
		D3DRS_SRCBLENDALPHA,
		D3DRS_DESTBLENDALPHA,
		D3DRS_BLENDOPALPHA,
		D3DRS_WRITEMASK,
		D3DRS_CULLMODE,
		D3DRS_FILLMODE,
		D3DRS_STENCILENABLE,
		D3DRS_COLORWRITEENABLE,
	};

	enum eSireRenderAPI {
		SIRE_NULL,
		SIRE_DX9,
		SIRE_DX10,
		SIRE_DX11,
		SIRE_DX12,
		SIRE_OPENGL,
	};

	struct tSireTexture2D {
		int32_t w;
		int32_t h;
		int32_t format;
		uint8_t* pixels;
		int32_t* ptr;

		tSireTexture2D() {
			w = 0;
			h = 0;
			format = 0;
			pixels = nullptr;
		}

		~tSireTexture2D() {
			if (pixels) {
				delete[] pixels;
			}
		}

		void Release() {
			delete this;
		}
	};

private:
	inline struct tRenderState {
		uint8_t blendEnable;
		uint8_t srcBlend;
		uint8_t dstBlend;
		uint8_t blendop;
		uint8_t srcBlendAlpha;
		uint8_t destBlendAlpha;
		uint8_t blendOpAlpha;
		uint8_t renderTargetWriteMask;
		uint8_t cullMode;
		uint8_t fillMode;
		uint8_t stencilEnable;
		uint32_t sampleMask;
	};

	static inline tRenderState states = {
		0,
		D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_OP_ADD,
		D3D11_COLOR_WRITE_ENABLE_ALL,
		D3D11_CULL_NONE,
		D3D11_FILL_SOLID
	};

	static inline eSireRenderAPI currentAPI = SIRE_NULL;

	inline struct tConstBuff {
		DirectX::XMMATRIX matrix;
		int32_t hasTex;
		int32_t hasMask;
	};

	inline struct tVertex {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 col;
		DirectX::XMFLOAT2 uv0;
		DirectX::XMFLOAT2 uv1;
	};

	struct tSireViewport {
		float x;
		float y;
		float w;
		float h;
		float maxd;
		float mind;
	};

	struct tSireShared {
		tSireViewport viewport;
		float fov;
		float nearPlane;
		float farPlane;

		tSireShared() {
			viewport = { 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f };
			fov = 60.0f;
			nearPlane = 0.1f;
			farPlane = 100.0f;
		}

		~tSireShared() {

		}
	};

	struct SireDirectX11 {
		static inline IDXGISwapChain* swapchain = nullptr;
		static inline ID3D11Device* dev = nullptr;
		static inline ID3D11DeviceContext* devcon = nullptr;

		static inline ID3D11Buffer* vb = nullptr;
		static inline ID3D11Buffer* ib = nullptr;

		static inline tConstBuff cb = { {}, false, false };
		static inline ID3D11Buffer* pb = nullptr;

		static inline ID3D11SamplerState* ss = nullptr;

		static inline ID3D11InputLayout* inputLayout = nullptr;

		static inline ID3D11VertexShader* vertexShader = nullptr;
		static inline ID3D11PixelShader* pixelShader = nullptr;

		static inline ID3D11VertexShader* internalVertexShader = nullptr;
		static inline ID3D11PixelShader* internalPixelShader = nullptr;

		static inline ID3D11ShaderResourceView* shaderResourceView0 = nullptr;
		static inline ID3D11ShaderResourceView* shaderResourceView1 = nullptr;

		static inline ID3D11RenderTargetView** GetRenderTargets() {
			ID3D11RenderTargetView* out[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = {};
			devcon->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, out, nullptr);
			return out;
		}

		static inline ID3D11RenderTargetView* GetRenderTarget() {
			ID3D11RenderTargetView* out = nullptr;
			devcon->OMGetRenderTargets(1, &out, nullptr);
			return out;
		}

		static inline ID3D11Texture2D* GetBackBuffer(uint32_t buffer) {
			ID3D11Texture2D* out;
			swapchain->GetBuffer(buffer, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&out));
			return out;
		}

		static inline D3D11_TEXTURE2D_DESC GetDesc(ID3D11Texture2D* texture) {
			D3D11_TEXTURE2D_DESC out = {};
			texture->GetDesc(&out);
			return out;
		}

		static inline D3D11_MAPPED_SUBRESOURCE map = {};

		static inline uint8_t* BeginMap(ID3D11Texture2D* texture, uint32_t* rowPixels) {
			devcon->Flush();
			devcon->Map(texture, 0, D3D11_MAP_READ, 0, &map);
			*rowPixels = map.RowPitch;
			return (uint8_t*)map.pData;
		}

		static inline void EndMap(ID3D11Texture2D* texture) {
			devcon->Unmap(texture, 0);
		}

		static inline ID3D11RenderTargetView* CreateRenderTarget(ID3D11Texture2D* texture) {
			ID3D11RenderTargetView* out;
			dev->CreateRenderTargetView(texture, nullptr, &out);
			return out;
		}

		static inline ID3DBlob* CompileShader(std::string const str, const char* szEntrypoint, const char* szTarget) {
			ID3DBlob* out = nullptr;
			ID3DBlob* outerr = nullptr;

			auto hr = D3DCompile(str.c_str(), str.length(), 0, nullptr, nullptr, szEntrypoint, szTarget, D3DCOMPILE_ENABLE_STRICTNESS, 0, &out, &outerr);
			if (FAILED(hr)) {
				if (outerr) {
					char szError[256]{ 0 };
					memcpy(szError, outerr->GetBufferPointer(), outerr->GetBufferSize());
					MessageBoxA(nullptr, szError, "Error", MB_OK);
				}
				return outerr;
			}
			return out;
		}

		static inline ID3D11VertexShader* CreateVertexShader(const void* buffer, uint32_t size) {
			ID3D11VertexShader* out = nullptr;
			dev->CreateVertexShader(buffer, size, NULL, &out);
			return out;
		}

		static inline ID3D11PixelShader* CreatePixelShader(const void* buffer, uint32_t size) {
			ID3D11PixelShader* out = nullptr;
			dev->CreatePixelShader(buffer, size, NULL, &out);
			return out;
		}

		static inline ID3D11InputLayout* CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>* layout, const void* buffer, uint32_t size) {
			ID3D11InputLayout* out = nullptr;
			dev->CreateInputLayout(layout->data(), layout->size(), buffer, size, &out);
			return out;
		}

		static inline ID3D11ShaderResourceView* CreateShaderResourceView(ID3D11Texture2D* texture) {
			ID3D11ShaderResourceView* out = nullptr;
			dev->CreateShaderResourceView(texture, nullptr, &out);
			return out;
		}

		static inline ID3D11Device* GetDev() {
			return dev;
		}

		static inline ID3D11DeviceContext* GetDevCon() {
			return devcon;
		}

		static inline void CopyResource(ID3D11Resource* dst, ID3D11Resource* src) {
			devcon->CopyResource(dst, src);
		}

		static inline void CopySubresourceRegion(ID3D11Resource* dst, ID3D11Resource* src, uint32_t i) {
			devcon->CopySubresourceRegion(dst, i, 0, 0, 0, src, 0, nullptr);
		}

		static void SetRenderState() {
			D3D11_RASTERIZER_DESC rasterizerDesc;
			ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
			rasterizerDesc.CullMode = (D3D11_CULL_MODE)states.cullMode;
			rasterizerDesc.FillMode = (D3D11_FILL_MODE)states.fillMode;
			ID3D11RasterizerState* rasterizerState = nullptr;
			dev->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
			devcon->RSSetState(rasterizerState);
			rasterizerState->Release();

			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(blendDesc));
			blendDesc.RenderTarget[0].BlendEnable = states.blendEnable;
			blendDesc.RenderTarget[0].SrcBlend = (D3D11_BLEND)states.srcBlend;
			blendDesc.RenderTarget[0].DestBlend = (D3D11_BLEND)states.dstBlend;
			blendDesc.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)states.blendop;
			blendDesc.RenderTarget[0].SrcBlendAlpha = (D3D11_BLEND)states.srcBlendAlpha;
			blendDesc.RenderTarget[0].DestBlendAlpha = (D3D11_BLEND)states.destBlendAlpha;
			blendDesc.RenderTarget[0].BlendOpAlpha = (D3D11_BLEND_OP)states.blendOpAlpha;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = states.renderTargetWriteMask;

			ID3D11BlendState* blendState = nullptr;
			dev->CreateBlendState(&blendDesc, &blendState);
			float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			devcon->OMSetBlendState(blendState, blendFactor, states.sampleMask);
			blendState->Release();
		}

		static inline ID3D11BlendState* GetBlendState(float* blendFactor, uint32_t* sampleMask) {
			ID3D11BlendState* out;
			devcon->OMGetBlendState(&out, blendFactor, sampleMask);
			return out;
		}

		static inline D3D11_BLEND_DESC GetBlendDesc(ID3D11BlendState* blendState) {
			D3D11_BLEND_DESC out;
			blendState->GetDesc(&out);
			return out;
		}

		static inline void SetBlendState(D3D11_BLEND_DESC* blendStateDesc, float* blendFactor, uint32_t sampleMask) {
			ID3D11BlendState* blendState = nullptr;
			dev->CreateBlendState(blendStateDesc, &blendState);
			devcon->OMSetBlendState(blendState, blendFactor, sampleMask);
			blendState->Release();
		}

		static inline void SetInputLayout(ID3D11InputLayout* l) {
			devcon->IASetInputLayout(l);
		}

		static inline void SetRenderTarget(ID3D11RenderTargetView* t) {
			devcon->OMSetRenderTargets(1, &t, nullptr);
		}

		static inline void SetShaders(ID3D11VertexShader* v, ID3D11PixelShader* p) {
			vertexShader = v;
			pixelShader = p;
		}

		static inline void SetProjectionMode(eSireProjection p) {
			switch (p) {
			case ORTHOGRAPHIC:
				cb.matrix = DirectX::XMMatrixOrthographicOffCenterLH(0, shared.viewport.w, shared.viewport.h, 0, shared.nearPlane, shared.farPlane);
				break;
			case PERSPECTIVE:
				cb.matrix = DirectX::XMMatrixPerspectiveFovLH(shared.fov, shared.viewport.w / shared.viewport.h, shared.nearPlane, shared.farPlane);
				break;
			}
		}

		static inline D3D11_VIEWPORT GetViewPort() {
			uint32_t numViewport = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
			D3D11_VIEWPORT out[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

			devcon->RSGetViewports(&numViewport, out);
			return out[0];
		}

		static inline void SetViewport(tSireViewport viewport) {
			D3D11_VIEWPORT vp = {};
			vp.TopLeftX = viewport.x;
			vp.TopLeftY = viewport.y;
			vp.Width = viewport.w;
			vp.Height = viewport.h;
			vp.MinDepth = viewport.mind;
			vp.MaxDepth = viewport.maxd;
			devcon->RSSetViewports(1, &vp);
		}

		static inline void SetTexture(ID3D11Texture2D* texture, ID3D11Texture2D* textureMask) {
			cb.hasTex = texture ? true : false;
			cb.hasMask = textureMask ? true : false;

			shaderResourceView0 = CreateShaderResourceView(texture);
			shaderResourceView1 = CreateShaderResourceView(textureMask);
		}

		static inline ID3D11Texture2D* CreateTexture(uint32_t width, uint32_t height, uint8_t* pixels) {
			ID3D11Texture2D* texture = nullptr;
			D3D11_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;

			dev->CreateTexture2D(&desc, nullptr, &texture);

			if (pixels)
				UpdateTexture(texture, pixels);

			return texture;
		}

		static inline void UpdateTexture(ID3D11Texture2D* texture, uint8_t* pixels) {
			D3D11_TEXTURE2D_DESC desc;
			texture->GetDesc(&desc);
			devcon->UpdateSubresource(texture, 0, nullptr, pixels, desc.Width * sizeof(UINT), 0);
		}

		static inline void Update() {
			// Deduce indices automatically if unset.
			if (indices.empty()) {
				uint16_t i = 0;
				for (auto& it : vertices)
				{
					indices.push_back(i++);
				}

				numIndices = indices.size();
			}

			// Fallback to internal shaders if unset.
			if (!pixelShader && internalPixelShader)
				pixelShader = internalPixelShader;

			if (!vertexShader && internalVertexShader)
				vertexShader = internalVertexShader;

			// Update index/vertex buffers
			D3D11_MAPPED_SUBRESOURCE mappedResource;
			devcon->Map(vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy(mappedResource.pData, vertices.data(), vertices.size() * sizeof(tVertex));
			devcon->Unmap(vb, 0);

			devcon->Map(ib, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy(mappedResource.pData, indices.data(), numIndices * sizeof(uint16_t));
			devcon->Unmap(ib, 0);

			// Update 
			cb.matrix = DirectX::XMMatrixTranspose(cb.matrix);

			devcon->Map(pb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy(mappedResource.pData, &cb, sizeof(cb));
			devcon->Unmap(pb, 0);
		}

		static inline void Render() {
			auto renderTarget = GetRenderTarget();

			SetInputLayout(inputLayout);
			SetRenderTarget(renderTarget);

			devcon->VSSetShader(vertexShader, nullptr, 0);
			devcon->PSSetShader(pixelShader, nullptr, 0);

			devcon->VSSetConstantBuffers(0, 1, &pb);
			devcon->PSSetConstantBuffers(0, 1, &pb);

			// Set textures
			devcon->VSSetShaderResources(0, 1, &shaderResourceView0);
			devcon->VSSetShaderResources(0, 1, &shaderResourceView1);

			devcon->PSSetShaderResources(0, 1, &shaderResourceView0);
			devcon->PSSetShaderResources(1, 1, &shaderResourceView1);
			devcon->PSSetSamplers(0, 1, &ss);
			devcon->GSSetSamplers(0, 1, &ss);

			// Set index/vertex buffers
			UINT stride = sizeof(tVertex);
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
			devcon->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);
			devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// Draw
			devcon->DrawIndexed(numIndices, 0, 0);

			Release(renderTarget);
			Release(shaderResourceView0);
			Release(shaderResourceView1);
		}

		static inline void Init(IDXGISwapChain* sc) {
			swapchain = sc;
			HRESULT hResult = swapchain->GetDevice(__uuidof(ID3D11Device), (void**)&dev);

			if (FAILED(hResult))
				return;

			dev->GetImmediateContext(&devcon);

			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));

			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.MiscFlags = 0;
			bufferDesc.ByteWidth = sizeof(tVertex) * 65536;

			// Vertex buffer
			dev->CreateBuffer(&bufferDesc, nullptr, &vb);

			// Index buffer
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			dev->CreateBuffer(&bufferDesc, nullptr, &ib);

			// Constant buffer
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.ByteWidth = sizeof(tConstBuff);

			D3D11_SUBRESOURCE_DATA initData;
			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = &cb;
			dev->CreateBuffer(&bufferDesc, &initData, &pb);

			D3D11_SAMPLER_DESC samplerDesc;
			ZeroMemory(&samplerDesc, sizeof(samplerDesc));
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			samplerDesc.BorderColor[0] = 0.0f;
			samplerDesc.BorderColor[1] = 0.0f;
			samplerDesc.BorderColor[2] = 0.0f;
			samplerDesc.BorderColor[3] = 0.0f;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
			dev->CreateSamplerState(&samplerDesc, &ss);

			// Init shaders
			ID3DBlob* VS = CompileShader(hlslShader, "VShader", "vs_5_0");
			ID3DBlob* PS = CompileShader(hlslShader, "PShader", "ps_5_0");

			internalVertexShader = CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize());
			internalPixelShader = CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize());

			// Init input layout
			std::vector<D3D11_INPUT_ELEMENT_DESC> layout =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			inputLayout = CreateInputLayout(&layout, VS->GetBufferPointer(), VS->GetBufferSize());

			Release(VS);
			Release(PS);
		}

		static inline void Shutdown() {
			Release(vb);
			Release(ib);
			Release(pb);
			Release(ss);
			Release(inputLayout);
			//Release(internalVertexShader);
			//Release(internalPixelShader);
			//Release(shaderResourceView0);
			//Release(shaderResourceView1);

			swapchain = nullptr;
			dev = nullptr;
			devcon = nullptr;
		}
	};

	static inline tSireShared shared = {};

	static inline std::vector<tVertex> vertices = {};
	static inline DirectX::XMFLOAT4 color = {};
	static inline DirectX::XMFLOAT2 uv0 = {};
	static inline DirectX::XMFLOAT2 uv1 = {};

	static inline std::vector<uint16_t> indices = {};
	static inline uint32_t numIndices;

	static inline std::string hlslShader = R"(
	cbuffer ConstantBuffer : register(b0)
	{
	    matrix projection;
	    int hasTex;
	    int hasMask;
	};
	
	Texture2D tex0 : register(t0);
	Texture2D mask0 : register(t1);
	SamplerState sampler0 : register(s0);
	
	struct VOut
	{
	    float4 position : SV_POSITION;
	    float4 color : COLOR;
	    float2 uv0 : TEXCOORD0;
	    float2 uv1 : TEXCOORD1;
	};
	
	VOut VShader(float4 position : POSITION, float4 color : COLOR, float2 uv0 : TEXCOORD0, float2 uv1 : TEXCOORD1)
	{
	    VOut output;
	
	    output.position = mul(position, projection);
	    output.color = color;
	    output.uv0 = uv0;
	    output.uv1 = uv1;
	
	    return output;
	}
	
	float4 PShader(float4 position : SV_POSITION, float4 color : COLOR, float2 uv0 : TEXCOORD0, float2 uv1 : TEXCOORD1) : SV_TARGET
	{
	    float4 c = color;
	
	    if (hasTex)
	    {   
	        c *= tex0.Sample(sampler0, uv0);
	        c.a = max(c.a, color.a);
	    }
	    
	    if (hasMask)
	    {
	        c *= mask0.Sample(sampler0, uv1);
	    }
	    
	    return c;
	}
	)";

public:
	static inline void Begin() {
		vertices.clear();
		indices.clear();
		numIndices = 0;

		color = { 1.0f, 1.0f, 1.0f, 1.0f };
		uv0 = { 0.0f, 0.0f };
		uv1 = { 0.0f, 0.0f };
	}

	static inline void End() {
		switch (currentAPI) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11:
			SireDirectX11::Update();
			SireDirectX11::Render();
			break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}
	}

	static inline void SetColor4f(float r, float g, float b, float a) {
		color = { r, g, b, a };
	}

	static inline void SetColor3f(float r, float g, float b) {
		SetColor4f(r, g, b, 1.0f);
	}

	static inline void SetTexCoords4f(float x1, float y1, float x2, float y2) {
		uv0 = { x1, y1 };
		uv1 = { x2, y2 };
	}

	static inline void SetTexCoords2f(float x, float y) {
		SetTexCoords4f(x, y, x, y);
	}

	static inline void SetVertex3f(float x, float y, float z) {
		tVertex v;
		v.pos.x = x;
		v.pos.y = y;
		v.pos.z = z;
		v.col = color;
		v.uv0 = uv0;
		v.uv1 = uv1;

		vertices.push_back(v);
	}

	static inline void SetVertex2f(float x, float y) {
		SetVertex3f(x, y, 0.0f);
	}

	static inline void SetIndex1i(uint16_t i) {
		indices.push_back(i);
	}

	static inline void SetIndices(std::vector<uint16_t> const& i, int32_t n) {
		indices = i;
		numIndices = n;
	}

	static inline void SetRenderState(eRenderState state, uint32_t value) {
		switch (state) {
		case D3DRS_ALPHATESTENABLE:
			states.blendEnable = value;
			break;
		case D3DRS_SRCBLEND:
			states.srcBlend = value;
			break;
		case D3DRS_DESTBLEND:
			states.destBlendAlpha = value;
			break;
		case D3DRS_BLENDOP:
			states.blendop = value;
			break;
		case D3DRS_SRCBLENDALPHA:
			states.srcBlendAlpha = value;
			break;
		case D3DRS_DESTBLENDALPHA:
			states.destBlendAlpha = value;
			break;
		case D3DRS_BLENDOPALPHA:
			states.blendOpAlpha = value;
			break;
		case D3DRS_WRITEMASK:
			states.renderTargetWriteMask = value;
			break;
		case D3DRS_CULLMODE:
			states.cullMode = value;
			break;
		case D3DRS_FILLMODE:
			states.fillMode = value;
			break;
		case D3DRS_STENCILENABLE:
			states.stencilEnable = value;
			break;
		case D3DRS_COLORWRITEENABLE:
			states.sampleMask = value;
			break;
		}

		switch (currentAPI) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11:
			SireDirectX11::SetRenderState();
			break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}
	}

	template <typename T>
	static inline void Init(eSireRenderAPI rapi, T* sc) {
		switch (rapi) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11:
			SireDirectX11::Init(reinterpret_cast<IDXGISwapChain*>(sc));
			break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}	

		currentAPI = rapi;
	}

	static inline void Shutdown(eSireRenderAPI rapi) {
		switch (rapi) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11:
			SireDirectX11::Shutdown();
			break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}

		currentAPI = SIRE_NULL;
	}

	template<typename T>
	static inline void Release(T res) {
		if (res) {
			res->Release();
			res = nullptr;
		}
	}

	static inline tSireTexture2D* GetBackBuffer(uint32_t buffer) {
		tSireTexture2D* out = new tSireTexture2D();

		switch (currentAPI) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11: {
			auto result = SireDirectX11::GetBackBuffer(buffer);
			auto desc = SireDirectX11::GetDesc(result);
			out->w = desc.Width;
			out->h = desc.Height;
			out->format = desc.Format;

			uint32_t pixelSize = 0;
			if (desc.Format == DXGI_FORMAT_R8G8B8A8_UNORM || desc.Format == DXGI_FORMAT_B8G8R8A8_UNORM) {
				pixelSize = 4;

				out->pixels = new uint8_t[desc.Width * desc.Height * pixelSize];

				uint32_t rowPitch = 0;
				uint8_t* pixels = SireDirectX11::BeginMap(result, &rowPitch);

				if (pixels) {
					memcpy(out->pixels, pixels, desc.Width * desc.Height * pixelSize);

				}
				else {
					assert("No pixels in the backbuffer");
				}

				SireDirectX11::EndMap(result);

				out->ptr = (int32_t*)result;
			}

			Release(result);
		} break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}

		return out;
	}

	static inline void SetViewport(float x, float y, float w, float h) {
		shared.viewport = { x, y, w, h, 0.0f, 1.0f };

		switch (currentAPI) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11:
			SireDirectX11::SetViewport(shared.viewport);
			break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}
	}

	static inline tSireTexture2D* CreateTexture(int32_t width, int32_t height, uint8_t* pixels) {
		tSireTexture2D* out = new tSireTexture2D();

		switch (currentAPI) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11: {
			auto result = SireDirectX11::CreateTexture(width, height, pixels);
			out->w = width;
			out->h = height;
			out->format = 0;
			out->pixels = new uint8_t[width * height * 4];
			out->ptr = (int32_t*)result;

			if (pixels)
				memcpy(out->pixels, pixels, width * height * 4);
		} break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}

		return out;
	}

	static inline void CopyResource(tSireTexture2D* dst, tSireTexture2D* src) {
		dst->w = src->w;
		dst->h = src->h;
		dst->format = src->format;

		const int32_t imageSize = src->w * src->h * 4;
		if (!dst->pixels) {
			dst->pixels = new uint8_t[imageSize];
		}

		memcpy(dst->pixels, src->pixels, imageSize);

		switch (currentAPI) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11:
			SireDirectX11::CopyResource((ID3D11Texture2D*)dst->ptr, (ID3D11Texture2D*)src->ptr);
			break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}
	}

	static inline void SetProjectionMode(eSireProjection proj) {
		switch (currentAPI) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11:
			SireDirectX11::SetProjectionMode(proj);
			break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}
	}

	static inline void SetTexture(tSireTexture2D* tex, tSireTexture2D* mask) {
		switch (currentAPI) {
		case SIRE_DX9:
			break;
		case SIRE_DX10:
			break;
		case SIRE_DX11:
			SireDirectX11::SetTexture((ID3D11Texture2D*)tex->ptr, (ID3D11Texture2D*)mask->ptr);
			break;
		case SIRE_DX12:
			break;
		case SIRE_OPENGL:
			break;
		}
	}
};
