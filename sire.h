#pragma once
#define SIRE_INCLUDE_DX9
#define SIRE_INCLUDE_DX10
#define SIRE_INCLUDE_DX11
//#define SIRE_INCLUDE_DX12
//#define SIRE_INCLUDE_OPENGL
//#define SIRE_INCLUDE_VULKAN

#include <iostream>
#include <vector>
#include <array>

#ifdef SIRE_INCLUDE_DX9
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <DirectXMath.h>
#endif

#ifdef SIRE_INCLUDE_DX10
#include <d3d10_1.h>
#include <d3d10.h>
#include <dxgi.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d10_1.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#endif

#ifdef SIRE_INCLUDE_DX11
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#endif

#ifdef SIRE_INCLUDE_DX12
#include <d3d12.h>
#include <dxgi.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#endif

#ifdef SIRE_INCLUDE_OPENGL
#define SOGL_MAJOR_VERSION 4
#define SOGL_MINOR_VERSION 5
#define SOGL_OVR_multiview
#define SOGL_KHR_parallel_shader_compile
#define SOGL_IMPLEMENTATION_WIN32
#include "glad/include/glad/glad.h"
#include "glad/include/KHR/khrplatform.h"
#pragma comment(lib, "opengl32.lib")
#endif

#ifdef SIRE_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#pragma comment(lib, "vulkan-1.lib")
#endif

template <typename T>
class SirePtr {
public:
	SirePtr() : ptr(nullptr) {}

	SirePtr(T* p) : ptr(p) {}

	~SirePtr() {
		Reset();
	}

	SirePtr(const SirePtr<T>& other) = delete;

	SirePtr<T>& operator=(const SirePtr<T>& other) = delete;

	SirePtr(SirePtr<T>&& other) noexcept : ptr(nullptr) {
		*this = std::move(other);
	}

	SirePtr<T>& operator=(SirePtr<T>&& other) noexcept {
		if (this != &other) {
			Reset();
			ptr = std::move(other.ptr);
			other.ptr = nullptr;
		}
		return *this;
	}

	T* Get() const {
		return ptr.get();
	}

	T** GetAddressOf() {
		return ptr.get();
	}

	T* operator->() const {
		return ptr.get();
	}

	operator bool() const {
		return (ptr != nullptr);
	}

	void Reset() {
		Release();
		ptr.reset();
	}

	void Reset(T* p) {
		Release();
		ptr.reset(p);
	}

	void Release() {
		if (ptr) {
			ptr->Release();
			ptr = nullptr;
		}
	}

private:
	std::unique_ptr<T> ptr;
};

class Sire {
public:
	enum eSireProjection {
		SIRE_PROJ_NONE,
		SIRE_PROJ_ORTHOGRAPHIC,
		SIRE_PROJ_PERSPECTIVE,
	};

	enum eSireRenderState {
		SIRE_BLEND_ALPHATESTENABLE,
		SIRE_BLEND_SRCBLEND,
		SIRE_BLEND_DESTBLEND,
		SIRE_BLEND_BLENDOP,
		SIRE_BLEND_SRCBLENDALPHA,
		SIRE_BLEND_DESTBLENDALPHA,
		SIRE_BLEND_BLENDOPALPHA,
		SIRE_BLEND_WRITEMASK,
		SIRE_BLEND_CULLMODE,
		SIRE_BLEND_FILLMODE,
		SIRE_BLEND_STENCILENABLE,
		SIRE_BLEND_COLORWRITEENABLE,
	};

	enum eSireFillMode {
		SIRE_FILL_WIREFRAME = 2,
		SIRE_FILL_SOLID = 3
	};

	enum eSireCull {
		SIRE_CULL_NONE = 1,
		SIRE_CULL_FRONT = 2,
		SIRE_CULL_BACK = 3
	};

	enum eSireBlend {
		SIRE_BLEND_ZERO = 1,
		SIRE_BLEND_ONE = 2,
		SIRE_BLEND_SRC_COLOR = 3,
		SIRE_BLEND_INV_SRC_COLOR = 4,
		SIRE_BLEND_SRC_ALPHA = 5,
		SIRE_BLEND_INV_SRC_ALPHA = 6,
		SIRE_BLEND_DEST_ALPHA = 7,
		SIRE_BLEND_INV_DEST_ALPHA = 8,
		SIRE_BLEND_DEST_COLOR = 9,
		SIRE_BLEND_INV_DEST_COLOR = 10,
		SIRE_BLEND_SRC_ALPHA_SAT = 11,
		SIRE_BLEND_BLEND_FACTOR = 14,
		SIRE_BLEND_INV_BLEND_FACTOR = 15,
		SIRE_BLEND_SRC1_COLOR = 16,
		SIRE_BLEND_INV_SRC1_COLOR = 17,
		SIRE_BLEND_SRC1_ALPHA = 18,
		SIRE_BLEND_INV_SRC1_ALPHA = 19
	};

	enum eSireBlendOp {
		SIRE_BLEND_OP_ADD = 1,
		SIRE_BLEND_OP_SUBTRACT = 2,
		SIRE_BLEND_OP_REV_SUBTRACT = 3,
		SIRE_BLEND_OP_MIN = 4,
		SIRE_BLEND_OP_MAX = 5
	};

	enum eSireRenderer {
		SIRE_RENDERER_NULL = -1,
#ifdef SIRE_INCLUDE_DX9
		SIRE_RENDERER_DX9,
#endif
#ifdef SIRE_INCLUDE_DX10
		SIRE_RENDERER_DX10,
#endif
#ifdef SIRE_INCLUDE_DX11
		SIRE_RENDERER_DX11,
#endif
#ifdef SIRE_INCLUDE_DX12
		SIRE_RENDERER_DX12,
#endif
#ifdef SIRE_INCLUDE_OPENGL
		SIRE_RENDERER_OPENGL,
#endif
#ifdef SIRE_INCLUDE_VULKAN
		SIRE_RENDERER_VULKAN,
#endif
		SIRE_NUM_RENDERERS,
	};

	enum eSireColorWriteEnable {
		SIRE_COLOR_WRITE_ENABLE_RED = 1,
		SIRE_COLOR_WRITE_ENABLE_GREEN = 2,
		SIRE_COLOR_WRITE_ENABLE_BLUE = 4,
		SIRE_COLOR_WRITE_ENABLE_ALPHA = 8,
		SIRE_COLOR_WRITE_ENABLE_ALL = (((D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_GREEN) | D3D11_COLOR_WRITE_ENABLE_BLUE) | D3D11_COLOR_WRITE_ENABLE_ALPHA)
	};

	enum eSirePrimitiveType {
		SIRE_POINT,
		SIRE_LINE,
		SIRE_TRIANGLE,
	};

	struct tSireTexture2D {
		int32_t w;
		int32_t h;
		int32_t format;
		int32_t swapColors;

		struct tSirePtrsHolder {
			intptr_t* texture;
			intptr_t* surface;
			eSireRenderer owner;

			tSirePtrsHolder() {
				owner = GetCurrentRenderer();
				texture = nullptr;
				surface = nullptr;
			}

			~tSirePtrsHolder() {
				Release();
			}

			void Release() {
				if (GetCurrentRenderer() == owner) {
					switch (GetCurrentRenderer()) {
					case SIRE_RENDERER_DX9: {
						IDirect3DTexture9* tex = reinterpret_cast<IDirect3DTexture9*>(texture);
						IDirect3DSurface9* surf = reinterpret_cast<IDirect3DSurface9*>(surface);
						Sire::Release(tex);
						Sire::Release(surf);
					} break;
					case SIRE_RENDERER_DX10: {
						ID3D10ShaderResourceView* tex = reinterpret_cast<ID3D10ShaderResourceView*>(texture);
						ID3D10Texture2D* surf = reinterpret_cast<ID3D10Texture2D*>(surface);
						Sire::Release(tex);
						Sire::Release(surf);
					} break;
					case SIRE_RENDERER_DX11: {
						ID3D11ShaderResourceView* tex = reinterpret_cast<ID3D11ShaderResourceView*>(texture);
						ID3D11Texture2D* surf = reinterpret_cast<ID3D11Texture2D*>(surface);
						Sire::Release(tex);
						Sire::Release(surf);
					} break;
					}
				}

				texture = nullptr;
				surface = nullptr;
			}
		};
		tSirePtrsHolder ptrs;

		tSireTexture2D() {
			w = 0;
			h = 0;
			format = 0;
			swapColors = 0;
		}

		~tSireTexture2D() {

		}

		void Set(int32_t width, int32_t height, int32_t format, intptr_t* tex, intptr_t* surf) {
			this->w = width;
			this->h = height;
			this->format = format;
			this->ptrs.texture = tex;
			this->ptrs.surface = surf;
		}

		void Release() {

		}
	};

	struct tSireInt2 {
		int32_t x, y;
	};

	struct tSireFloat2 {
		float x, y;
	};

	struct tSireFloat3 {
		float x, y, z;
	};

	struct tSireFloat4 {
		float x, y, z, w;
	};

private:
	struct tRenderState {
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

	struct alignas(16) tSireMatrix {
		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};

			float m[4][4];
		};

		void Identity() {
			_11 = 1.0f;
			_12 = 0.0f;
			_13 = 0.0f;
			_14 = 0.0f;

			_21 = 0.0f;
			_22 = 1.0f;
			_23 = 0.0f;
			_24 = 0.0f;

			_31 = 0.0f;
			_32 = 0.0f;
			_33 = 1.0f;
			_34 = 0.0f;

			_41 = 0.0f;
			_42 = 0.0f;
			_43 = 0.0f;
			_44 = 1.0f;
		}

		void Orthographic(float x, float y, float width, float height, float nearPlane, float farPlane) {
			_11 = 2.0f / width;
			_12 = 0.0f;
			_13 = 0.0f;
			_14 = 0.0f;

			_21 = 0.0f;
			_22 = -2.0f / height;
			_23 = 0.0f;
			_24 = 0.0f;

			_31 = 0.0f;
			_32 = 0.0f;
			_33 = 1.0f / (farPlane - nearPlane);
			_34 = 0.0f;

			_41 = -(x + x + width) / width;
			_42 = (y + y + height) / height;
			_43 = -nearPlane / (farPlane - nearPlane);
			_44 = 1.0f;
		}

		void Perspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
			float f = tanf(fov * 0.5f);
			float invAspectRatio = 1.0f / aspectRatio;

			_11 = 1.0f / (f * invAspectRatio);
			_12 = 0.0f;
			_13 = 0.0f;
			_14 = 0.0f;

			_21 = 0.0f;
			_22 = 1.0f / f;
			_23 = 0.0f;
			_24 = 0.0f;

			_31 = 0.0f;
			_32 = 0.0f;
			_33 = farPlane / (farPlane - nearPlane);
			_34 = 1.0f;

			_41 = 0.0f;
			_42 = 0.0f;
			_43 = (-farPlane * nearPlane) / (farPlane - nearPlane);
			_44 = 0.0f;
		}

		void Transpose() {
			std::swap(_12, _21);
			std::swap(_13, _31);
			std::swap(_14, _41);

			std::swap(_23, _32);
			std::swap(_24, _42);

			std::swap(_34, _43);
		}

		D3DXMATRIX ToD3DXMATRIX() {
			D3DXMATRIX out = {};
			out._11 = _11;
			out._12 = _12;
			out._13 = _13;
			out._14 = _14;

			out._21 = _21;
			out._22 = _22;
			out._23 = _23;
			out._24 = _24;

			out._31 = _31;
			out._32 = _32;
			out._33 = _33;
			out._34 = _34;

			out._41 = _41;
			out._42 = _42;
			out._43 = _43;
			out._44 = _44;
			return out;
		}

		std::array<float, 16> ToFloatArray() {
			std::array<float, 16> out = {};

			out[0] = _11;
			out[1] = _21;
			out[2] = _31;
			out[3] = _41;

			out[4] = _12;
			out[5] = _22;
			out[6] = _32;
			out[7] = _42;

			out[8] = _13;
			out[9] = _23;
			out[10] = _33;
			out[11] = _43;

			out[12] = _14;
			out[13] = _24;
			out[14] = _34;
			out[15] = _44;

			return out;
		}
	};

	struct tConstBuff {
		tSireMatrix matrix;
		int32_t hasTex;
		int32_t hasMask;
		int32_t swapColors;
	};

	struct tVertex {
		tSireFloat3 pos;
		tSireFloat4 col;
		tSireFloat2 uv0;
		tSireFloat2 uv1;
	};

	struct tVertexLegacy {
		tSireFloat3 pos;
		uint32_t diff;
		tSireFloat2 uv0;
		tSireFloat2 uv1;
	};

	struct tSireViewport {
		float x;
		float y;
		float w;
		float h;
		float mind;
		float maxd;
	};

	struct tSireShared {
		tSireViewport viewport;
		float fov;
		float nearPlane;
		float farPlane;
		tRenderState renderStates;

		tSireShared() {
			viewport = { 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f };
			fov = 60.0f;
			nearPlane = 0.0f;
			farPlane = 1.0f;
			renderStates = { 0, SIRE_BLEND_SRC_ALPHA, SIRE_BLEND_INV_SRC_ALPHA, SIRE_BLEND_OP_ADD, SIRE_BLEND_ONE, SIRE_BLEND_ZERO, SIRE_BLEND_OP_ADD, SIRE_COLOR_WRITE_ENABLE_ALL, SIRE_CULL_NONE, SIRE_FILL_SOLID };
		}

		~tSireShared() {

		}
	};

	struct SireRenderer {
		bool initialised;
		HWND hWnd;

		virtual bool IsRendererActive() { return false; }
		virtual void Init(intptr_t* ptr) {}
		virtual void Shutdown() {}
		virtual void Begin() {}
		virtual void End() {}
		virtual void SetVertices(tVertex const& v) {}
		virtual void SetRenderStates(tRenderState const& s) {}
		virtual void SetViewport(tSireViewport const& v) {}
		virtual void CopyResource(intptr_t* dst, intptr_t* src) {}
		virtual void SetTexture(intptr_t* tex, intptr_t* mask) {}
		virtual HWND GetWindow() { return hWnd; }
		virtual uint8_t* Lock(void* ptr) { return nullptr; }
		virtual void Unlock(void* ptr) {}

		SireRenderer() {
			initialised = false;
			hWnd = nullptr;
		}

		bool operator==(const SireRenderer& other) const {
			return false;
		}
	};

	struct SireDirectX9 : SireRenderer {
		IDirect3DDevice9* dev;
		IDirect3DVertexBuffer9* vb;
		IDirect3DIndexBuffer9* ib;
		IDirect3DTexture9* tex;
		IDirect3DTexture9* mask;
		IDirect3DVertexDeclaration9* vertexDeclaration;
		IDirect3DPixelShader9* pixelShader;
		IDirect3DVertexShader9* vertexShader;
		ID3DXConstantTable* pct;
		ID3DXConstantTable* vct;
		IDirect3DPixelShader9* internalPixelShader;
		IDirect3DVertexShader9* internalVertexShader;
		std::vector<tVertexLegacy> verticesLegacy;
		IDirect3DStateBlock9* stateBlock;

		SireDirectX9() : SireRenderer() {
			dev = nullptr;
			vb = nullptr;
			ib = nullptr;
			tex = nullptr;
			mask = nullptr;
			vertexDeclaration = nullptr;
			pixelShader = nullptr;
			vertexShader = nullptr;
			pct = nullptr;
			vct = nullptr;
			internalPixelShader = nullptr;
			internalVertexShader = nullptr;
			verticesLegacy = {};
			stateBlock = nullptr;
		}

		// Start virtual override
		bool IsRendererActive() override {
			if (initialised && dev) {
				HRESULT hr = dev->TestCooperativeLevel();
				return SUCCEEDED(hr);
			}

			return false;
		}

		void Init(intptr_t* d) override {
			if (initialised)
				return;

			dev = reinterpret_cast<IDirect3DDevice9*>(d);

			IDirect3DSwapChain9* swapchain = nullptr;
			dev->GetSwapChain(0, &swapchain);

			D3DPRESENT_PARAMETERS presentParams;
			ZeroMemory(&presentParams, sizeof(presentParams));
			swapchain->GetPresentParameters(&presentParams);

			hWnd = presentParams.hDeviceWindow;

			dev->CreateVertexBuffer(sizeof(tVertexLegacy) * 65536, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
				0, D3DPOOL_DEFAULT, &vb, nullptr);

			dev->CreateIndexBuffer(sizeof(uint16_t) * 65536, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, nullptr);

			// Init shaders
			ID3DXBuffer* VS = CompileShader(hlslShader2_0, "VShader", "vs_2_0");
			ID3DXBuffer* PS = CompileShader(hlslShader2_0, "PShader", "ps_2_0");

			internalVertexShader = CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize());
			internalPixelShader = CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize());

			D3DXGetShaderConstantTable(static_cast<const DWORD*>(VS->GetBufferPointer()), &pct);
			D3DXGetShaderConstantTable(static_cast<const DWORD*>(PS->GetBufferPointer()), &vct);

			Release(VS);
			Release(PS);

			D3DVERTEXELEMENT9 vertexElements[] = {
				{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0, sizeof(float[3]), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
				{ 0, sizeof(float[3]) + sizeof(D3DCOLOR), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
				{ 0, sizeof(float[5]) + sizeof(D3DCOLOR), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
				D3DDECL_END()
			};

			dev->CreateVertexDeclaration(vertexElements, &vertexDeclaration);

			initialised = true;
		}

		void Shutdown() override {
			if (!initialised)
				return;

			Release(vb);
			Release(ib);
			Release(vertexDeclaration);
			Release(pct);
			Release(vct);

			tex = nullptr;
			mask = nullptr;
			dev = nullptr;

			initialised = false;
		}

		void Begin() override {
			verticesLegacy.clear();

			dev->CreateStateBlock(D3DSBT_ALL, &stateBlock);
			stateBlock->Capture();
		}

		void End() override {
			// Fallback to internal shaders if unset.
			if (!pixelShader && internalPixelShader)
				pixelShader = internalPixelShader;

			if (!vertexShader && internalVertexShader)
				vertexShader = internalVertexShader;

			void* out = nullptr;
			vb->Lock(0, 0, (void**)&out, 0);
			memcpy(out, verticesLegacy.data(), verticesLegacy.size() * sizeof(tVertexLegacy));
			vb->Unlock();

			ib->Lock(0, 0, (void**)&out, 0);
			memcpy(out, indices.data(), indices.size() * sizeof(uint16_t));
			ib->Unlock();

			tConstBuff tempcb = cb;
			D3DXMATRIX m = tempcb.matrix.ToD3DXMATRIX();
			pct->SetMatrix(dev, pct->GetConstantByName(NULL, "proj"), &m);
			pct->SetMatrix(dev, vct->GetConstantByName(NULL, "proj"), &m);

			pct->SetInt(dev, pct->GetConstantByName(NULL, "hasTex"), tempcb.hasTex);
			pct->SetInt(dev, vct->GetConstantByName(NULL, "hasTex"), tempcb.hasTex);

			pct->SetInt(dev, pct->GetConstantByName(NULL, "hasMask"), tempcb.hasMask);
			pct->SetInt(dev, vct->GetConstantByName(NULL, "hasMask"), tempcb.hasMask);

			pct->SetInt(dev, pct->GetConstantByName(NULL, "swapColors"), tempcb.swapColors);
			pct->SetInt(dev, vct->GetConstantByName(NULL, "swapColors"), tempcb.swapColors);

			auto renderTarget = GetRenderTarget();
			dev->SetRenderTarget(0, renderTarget);

			dev->SetVertexDeclaration(vertexDeclaration);

			dev->SetTexture(0, tex);
			dev->SetTexture(1, mask);

			dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
			dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

			dev->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			dev->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			dev->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
			dev->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

			dev->SetRenderState(D3DRS_WRAP0, 0);
			dev->SetRenderState(D3DRS_WRAP1, 0);

			dev->SetPixelShader(pixelShader);
			dev->SetVertexShader(vertexShader);

			dev->SetStreamSource(0, vb, 0, sizeof(tVertexLegacy));
			dev->SetIndices(ib);

			D3DPRIMITIVETYPE type = D3DPT_POINTLIST;
			switch (primitiveType) {
			case SIRE_LINE:
				type = D3DPT_LINELIST;
				break;
			case SIRE_POINT:
				type = D3DPT_POINTLIST;
				break;
			case SIRE_TRIANGLE:
				type = D3DPT_TRIANGLELIST;
				break;
			}

			dev->DrawIndexedPrimitive(type, 0, 0, static_cast<uint32_t>(verticesLegacy.size()), 0, numIndices / 3);

			stateBlock->Apply();
			Release(stateBlock);
		}
		
		void SetVertices(tVertex const& v) override {
			tVertexLegacy vl = {};

			vl.pos = v.pos;
			vl.diff = D3DCOLOR_ARGB(
				static_cast<uint32_t>(v.col.w * 255),
				static_cast<uint32_t>(v.col.x * 255),
				static_cast<uint32_t>(v.col.y * 255),
				static_cast<uint32_t>(v.col.z * 255)
			);
			vl.uv0 = v.uv0;
			vl.uv1 = v.uv1;

			verticesLegacy.push_back(vl);
		}

		void SetRenderStates(tRenderState const& s) override {
			// Set rasterizer state
			dev->SetRenderState(D3DRS_CULLMODE, s.cullMode);
			dev->SetRenderState(D3DRS_FILLMODE, s.fillMode);

			// Set blend state
			dev->SetRenderState(D3DRS_ALPHABLENDENABLE, s.blendEnable);
			dev->SetRenderState(D3DRS_SRCBLEND, s.srcBlend);
			dev->SetRenderState(D3DRS_DESTBLEND, s.dstBlend);
			dev->SetRenderState(D3DRS_BLENDOP, s.blendop);
			dev->SetRenderState(D3DRS_SRCBLENDALPHA, s.srcBlendAlpha);
			dev->SetRenderState(D3DRS_DESTBLENDALPHA, s.destBlendAlpha);
			dev->SetRenderState(D3DRS_BLENDOPALPHA, s.blendOpAlpha);
			dev->SetRenderState(D3DRS_COLORWRITEENABLE, s.sampleMask);
		}

		void SetViewport(tSireViewport const& v) {
			D3DVIEWPORT9 vp = {};
			vp.X = static_cast<DWORD>(v.x);
			vp.Y = static_cast<DWORD>(v.y);
			vp.Width = static_cast<DWORD>(v.w);
			vp.Height = static_cast<DWORD>(v.h);
			vp.MinZ = v.mind;
			vp.MaxZ = v.maxd;
			dev->SetViewport(&vp);
		}

		void SetTexture(intptr_t* texture, intptr_t* textureMask) override {
			cb.hasTex = texture ? true : false;
			cb.hasMask = textureMask ? true : false;

			tex = nullptr;
			mask = nullptr;

			if (texture)
				tex = reinterpret_cast<IDirect3DTexture9*>(texture);

			if (textureMask)
				mask = reinterpret_cast<IDirect3DTexture9*>(textureMask);
		}

		void CopyResource(intptr_t* dst, intptr_t* src) override {
			dev->StretchRect(reinterpret_cast<IDirect3DSurface9*>(src), nullptr, reinterpret_cast<IDirect3DSurface9*>(dst), nullptr, D3DTEXF_NONE);
		}

		uint8_t* Lock(void* ptr) override {
			D3DLOCKED_RECT out;
			reinterpret_cast<IDirect3DSurface9*>(ptr)->LockRect(&out, nullptr, 0);
			return (uint8_t*)out.pBits;
		}

		void Unlock(void* ptr) override {
			reinterpret_cast<IDirect3DSurface9*>(ptr)->UnlockRect();
		}

		// End virtual override

		IDirect3DSurface9* GetRenderTarget() {
			IDirect3DSurface9* out = nullptr;
			dev->GetRenderTarget(0, &out);
			return out;
		}

		IDirect3DSurface9* GetBackBufferSurface(uint32_t buffer) {
			IDirect3DSurface9* out = nullptr;
			dev->GetBackBuffer(0, buffer, D3DBACKBUFFER_TYPE_MONO, &out);
			return out;
		}

		D3DSURFACE_DESC GetDesc(IDirect3DSurface9* surface) {
			D3DSURFACE_DESC out = {};
			surface->GetDesc(&out);
			return out;
		}

		IDirect3DSurface9* GetSurfaceLevel(IDirect3DTexture9* texture, uint32_t level) {
			IDirect3DSurface9* out;
			texture->GetSurfaceLevel(level, &out);
			return out;
		}

		ID3DXBuffer* CompileShader(const std::string& str, const char* szEntrypoint, const char* szTarget) {
			ID3DXBuffer* out;
			ID3DXBuffer* outerr;
			HRESULT hr = D3DXCompileShader(str.c_str(), static_cast<uint32_t>(str.size()), NULL, NULL, szEntrypoint, szTarget, 0, &out, &outerr, NULL);
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

		IDirect3DVertexShader9* CreateVertexShader(const void* buffer, uint32_t size) {
			IDirect3DVertexShader9* pVertexShader = nullptr;
			dev->CreateVertexShader(static_cast<const DWORD*>(buffer), &pVertexShader);
			return pVertexShader;
		}

		IDirect3DPixelShader9* CreatePixelShader(const void* buffer, uint32_t size) {
			IDirect3DPixelShader9* pPixelShader = nullptr;
			dev->CreatePixelShader(static_cast<const DWORD*>(buffer), &pPixelShader);
			return pPixelShader;
		}

		const char* GetErrorString(HRESULT hr) {
			switch (hr) {
			case D3D_OK:
				return "D3D_OK: No error.";
			case D3DERR_NOTAVAILABLE:
				return "D3DERR_NOTAVAILABLE: This device does not support the queried technique or method.";
			case D3DERR_OUTOFVIDEOMEMORY:
				return "D3DERR_OUTOFVIDEOMEMORY: Out of video memory.";
			case D3DERR_INVALIDCALL:
				return "D3DERR_INVALIDCALL: The method call is invalid.";
			case D3DERR_DRIVERINTERNALERROR:
				return "D3DERR_DRIVERINTERNALERROR: Internal driver error.";
			case D3DERR_DEVICELOST:
				return "D3DERR_DEVICELOST: The device is lost and needs to be reset.";
			case D3DERR_INVALIDDEVICE:
				return "D3DERR_INVALIDDEVICE: The requested device type is not valid.";
			case D3DERR_MOREDATA:
				return "D3DERR_MOREDATA: There is more data available.";
			case D3DERR_NOTFOUND:
				return "D3DERR_NOTFOUND: The requested item was not found.";
			case D3DERR_DEVICEHUNG:
				return "D3DERR_DEVICEHUNG: The device is hung and needs to be reset.";
			case D3DERR_DEVICEREMOVED:
				return "D3DERR_DEVICEREMOVED: The device has been removed.";
			case D3DERR_DEVICENOTRESET:
				return "D3DERR_DEVICENOTRESET: The device has not been reset.";
			case D3DERR_WASSTILLDRAWING:
				return "D3DERR_WASSTILLDRAWING: The previous rendering operation is still in progress.";
			case D3DERR_UNSUPPORTEDALPHAARG:
				return "D3DERR_UNSUPPORTEDALPHAARG: The alpha blending argument is not supported.";
			case D3DERR_UNSUPPORTEDALPHAOPERATION:
				return "D3DERR_UNSUPPORTEDALPHAOPERATION: The alpha blending operation is not supported.";
			case D3DERR_UNSUPPORTEDCOLORARG:
				return "D3DERR_UNSUPPORTEDCOLORARG: The color blending argument is not supported.";
			case D3DERR_UNSUPPORTEDCOLOROPERATION:
				return "D3DERR_UNSUPPORTEDCOLOROPERATION: The color blending operation is not supported.";
			default:
				return "Unknown error.";
			}
		}

		IDirect3DSurface9* CreateSurface(uint32_t width, uint32_t height, uint8_t* pixels) {
			IDirect3DSurface9* out = nullptr;
			HRESULT hr = dev->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &out, nullptr);

			if (SUCCEEDED(hr)) {
				if (pixels) {
					uint8_t* texturePixels = Lock(out);
					std::memcpy(texturePixels, pixels, width * height * 4);
					Unlock(out);
				}
			}
			else {
				printf("%s", GetErrorString(hr));
			}

			return out;
		}

		IDirect3DTexture9* CreateTexture(uint32_t width, uint32_t height, uint8_t* pixels, IDirect3DSurface9** sout) {
			IDirect3DTexture9* out = nullptr;
			HRESULT hr = dev->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &out, nullptr);

			if (SUCCEEDED(hr)) {
				IDirect3DSurface9* surf = GetSurfaceLevel(out, 0);

				if (sout)
					*sout = surf;

				if (pixels) {
					IDirect3DSurface9* tempSurf = CreateSurface(width, height, pixels);
					CopyResource(reinterpret_cast<intptr_t*>(surf), reinterpret_cast<intptr_t*>(tempSurf));
					Release(tempSurf);
				}
			}
			else {
				printf("%s", GetErrorString(hr));
			}

			return out;
		}
	};

	struct SireDirectX10 : SireRenderer {
		IDXGISwapChain* swapchain;
		ID3D10Device* dev;
		ID3D10Buffer* vb;
		ID3D10Buffer* ib;
		ID3D10Buffer* pb;
		ID3D10SamplerState* ss;
		ID3D10InputLayout* inputLayout;
		ID3D10VertexShader* vertexShader;
		ID3D10PixelShader* pixelShader;
		ID3D10VertexShader* internalVertexShader;
		ID3D10PixelShader* internalPixelShader;
		ID3D10ShaderResourceView* tex;
		ID3D10ShaderResourceView* mask;
		ID3D10RasterizerState* rasterizerState;
		ID3D10DepthStencilState* depthStencilState;
		ID3D10BlendState* blendState;
		FLOAT blendFactor[4];
		UINT sampleMask;
		UINT stencilRef;

		// Start virtual override
		SireDirectX10() : SireRenderer() {
			swapchain = nullptr;
			dev = nullptr;
			vb = nullptr;
			ib = nullptr;
			pb = nullptr;
			ss = nullptr;
			inputLayout = nullptr;
			vertexShader = nullptr;
			pixelShader = nullptr;
			internalVertexShader = nullptr;
			internalPixelShader = nullptr;
			tex = nullptr;
			mask = nullptr;
			rasterizerState = nullptr;
			depthStencilState = nullptr;
			blendState = nullptr;
			blendFactor[0] = 0.0f;
			blendFactor[1] = 0.0f;
			blendFactor[2] = 0.0f;
			blendFactor[3] = 0.0f;
			sampleMask = 0;
			stencilRef = 0;
		}

		bool IsRendererActive() override {
			if (initialised && swapchain && dev) {
				HRESULT hr = dev->GetDeviceRemovedReason();
				return SUCCEEDED(hr);
			}

			return false;
		}

		void Init(intptr_t* ptr) override {
			if (initialised)
				return;

			swapchain = reinterpret_cast<IDXGISwapChain*>(ptr);
			HRESULT hResult = swapchain->GetDevice(__uuidof(ID3D11Device), (void**)&dev);

			if (FAILED(hResult))
				return;

			D3D10_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));

			bufferDesc.Usage = D3D10_USAGE_DYNAMIC;
			bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
			bufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
			bufferDesc.MiscFlags = 0;
			bufferDesc.ByteWidth = sizeof(tVertex) * 65536;

			// Vertex buffer
			dev->CreateBuffer(&bufferDesc, nullptr, &vb);

			// Index buffer
			bufferDesc.ByteWidth = sizeof(uint16_t) * 65536;
			bufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
			dev->CreateBuffer(&bufferDesc, nullptr, &ib);

			// Constant buffer
			bufferDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
			bufferDesc.ByteWidth = sizeof(tConstBuff);

			D3D10_SUBRESOURCE_DATA initData;
			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = &cb;
			dev->CreateBuffer(&bufferDesc, &initData, &pb);

			D3D10_SAMPLER_DESC samplerDesc;
			ZeroMemory(&samplerDesc, sizeof(samplerDesc));
			samplerDesc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D10_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D10_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D10_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D10_COMPARISON_NEVER;
			samplerDesc.BorderColor[0] = 0.0f;
			samplerDesc.BorderColor[1] = 0.0f;
			samplerDesc.BorderColor[2] = 0.0f;
			samplerDesc.BorderColor[3] = 0.0f;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
			dev->CreateSamplerState(&samplerDesc, &ss);

			// Init shaders
			ID3DBlob* VS = CompileShader(hlslShader5_0, "VShader", "vs_4_0");
			ID3DBlob* PS = CompileShader(hlslShader5_0, "PShader", "ps_4_0");

			internalVertexShader = CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize());
			internalPixelShader = CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize());

			// Init input layout
			std::vector<D3D10_INPUT_ELEMENT_DESC> layout = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D10_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			};

			inputLayout = CreateInputLayout(&layout, VS->GetBufferPointer(), VS->GetBufferSize());

			Release(VS);
			Release(PS);

			initialised = true;
		}

		void Shutdown() override {
			if (!initialised)
				return;

			Release(vb);
			Release(ib);
			Release(pb);
			Release(ss);
			Release(inputLayout);
			Release(internalVertexShader);
			Release(internalPixelShader);

			vertexShader = nullptr;
			pixelShader = nullptr;

			swapchain = nullptr;
			dev = nullptr;

			initialised = false;
		}

		void Begin() override {
			dev->RSGetState(&rasterizerState);
			dev->OMGetDepthStencilState(&depthStencilState, &stencilRef);
			dev->OMGetBlendState(&blendState, blendFactor, &sampleMask);
		}

		void End() override {
			// Fallback to internal shaders if unset.
			if (!pixelShader && internalPixelShader)
				pixelShader = internalPixelShader;

			if (!vertexShader && internalVertexShader)
				vertexShader = internalVertexShader;

			// Update index/vertex buffers
			void* out;
			vb->Map(D3D10_MAP_WRITE_DISCARD, 0, &out);
			memcpy(out, vertices.data(), vertices.size() * sizeof(tVertex));
			vb->Unmap();

			ib->Map(D3D10_MAP_WRITE_DISCARD, 0, &out);
			memcpy(out, indices.data(), numIndices * sizeof(uint16_t));
			ib->Unmap();

			// Update
			tConstBuff tempcb = cb;
			tempcb.matrix.Transpose();

			pb->Map(D3D10_MAP_WRITE_DISCARD, 0, &out);
			memcpy(out, &tempcb, sizeof(tempcb));
			pb->Unmap();

			dev->IASetInputLayout(inputLayout);

			auto renderTarget = GetRenderTarget();
			dev->OMSetRenderTargets(1, &renderTarget, nullptr);

			ID3D10VertexShader* prevVertexShader = nullptr;
			dev->VSGetShader(&prevVertexShader);
			dev->VSSetShader(vertexShader);

			ID3D10PixelShader* prevPixelShader = nullptr;
			dev->PSGetShader(&prevPixelShader);
			dev->PSSetShader(pixelShader);

			ID3D10Buffer* prevVertexConstantBuffer = nullptr;
			dev->VSGetConstantBuffers(0, 1, &prevVertexConstantBuffer);
			dev->VSSetConstantBuffers(0, 1, &pb);

			ID3D10Buffer* prevPixelConstantBuffer = nullptr;
			dev->PSGetConstantBuffers(0, 1, &prevPixelConstantBuffer);
			dev->PSSetConstantBuffers(0, 1, &pb);

			// Set textures
			ID3D10ShaderResourceView* prevVertexShaderResourceView0 = nullptr;
			dev->VSGetShaderResources(0, 1, &prevVertexShaderResourceView0);
			dev->VSSetShaderResources(0, 1, &tex);

			ID3D10ShaderResourceView* prevVertexShaderResourceView1 = nullptr;
			dev->VSGetShaderResources(1, 1, &prevVertexShaderResourceView1);
			dev->VSSetShaderResources(1, 1, &mask);

			ID3D10ShaderResourceView* prevPixelShaderResourceView0 = nullptr;
			dev->PSGetShaderResources(0, 1, &prevPixelShaderResourceView0);
			dev->PSSetShaderResources(0, 1, &tex);

			ID3D10ShaderResourceView* prevPixelShaderResourceView1 = nullptr;
			dev->PSGetShaderResources(1, 1, &prevPixelShaderResourceView1);
			dev->PSSetShaderResources(1, 1, &mask);

			ID3D10SamplerState* prevPixelSamplers = nullptr;
			dev->PSGetSamplers(0, 1, &prevPixelSamplers);
			dev->PSSetSamplers(0, 1, &ss);

			ID3D10SamplerState* prevVertexSamplers = nullptr;
			dev->GSGetSamplers(0, 1, &prevVertexSamplers);
			dev->GSSetSamplers(0, 1, &ss);

			// Set index/vertex buffers
			UINT stride = sizeof(tVertex);
			UINT offset = 0;

			UINT prevStride;
			UINT prevVertexOffset;
			ID3D10Buffer* prevVertexBuffers = nullptr;
			dev->IAGetVertexBuffers(0, 1, &prevVertexBuffers, &prevStride, &prevVertexOffset);
			dev->IASetVertexBuffers(0, 1, &vb, &stride, &offset);

			ID3D10Buffer* prevIndexBuffers = nullptr;
			DXGI_FORMAT prevFormat;
			UINT prevIndexOffset;
			dev->IAGetIndexBuffer(&prevIndexBuffers, &prevFormat, &prevIndexOffset);
			dev->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);

			D3D_PRIMITIVE_TOPOLOGY type = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
			switch (primitiveType) {
			case SIRE_LINE:
				type = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
				break;
			case SIRE_POINT:
				type = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
				break;
			case SIRE_TRIANGLE:
				type = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				break;
			}

			D3D_PRIMITIVE_TOPOLOGY prevType;
			dev->IAGetPrimitiveTopology(&prevType);
			dev->IASetPrimitiveTopology(type);

			// Draw
			dev->DrawIndexed(numIndices, 0, 0);

			// Restore shit
			dev->VSSetShader(prevVertexShader);
			Release(prevVertexShader);

			dev->PSSetShader(prevPixelShader);
			Release(prevPixelShader);

			dev->VSSetConstantBuffers(0, 1, &prevVertexConstantBuffer);
			Release(prevVertexConstantBuffer);

			dev->PSSetConstantBuffers(0, 1, &prevPixelConstantBuffer);
			Release(prevPixelConstantBuffer);

			dev->VSSetShaderResources(0, 1, &prevVertexShaderResourceView0);
			Release(prevVertexShaderResourceView0);

			dev->VSSetShaderResources(1, 1, &prevVertexShaderResourceView1);
			Release(prevVertexShaderResourceView1);

			dev->PSSetShaderResources(0, 1, &prevPixelShaderResourceView0);
			Release(prevPixelShaderResourceView0);

			dev->PSSetShaderResources(1, 1, &prevPixelShaderResourceView1);
			Release(prevPixelShaderResourceView1);

			dev->PSSetSamplers(0, 1, &prevPixelSamplers);
			Release(prevPixelSamplers);

			dev->GSSetSamplers(0, 1, &prevVertexSamplers);
			Release(prevVertexSamplers);

			dev->IASetVertexBuffers(0, 1, &prevVertexBuffers, &prevStride, &prevVertexOffset);
			Release(prevVertexBuffers);

			dev->IASetIndexBuffer(prevIndexBuffers, prevFormat, prevIndexOffset);
			Release(prevIndexBuffers);

			dev->IASetPrimitiveTopology(prevType);

			Release(renderTarget);

			if (rasterizerState) {
				dev->RSSetState(rasterizerState);
				Release(rasterizerState);
				depthStencilState = nullptr;
			}

			if (depthStencilState) {
				dev->OMSetDepthStencilState(depthStencilState, stencilRef);
				Release(depthStencilState);
				depthStencilState = nullptr;
			}

			if (blendState) {
				dev->OMSetBlendState(blendState, blendFactor, sampleMask);
				Release(blendState);
				blendState = nullptr;
			}
		}

		void SetVertices(tVertex const& v) override {

		}

		void SetRenderStates(tRenderState const& s) override {
			D3D10_RASTERIZER_DESC rasterizerDesc;
			ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
			rasterizerDesc.CullMode = (D3D10_CULL_MODE)s.cullMode;
			rasterizerDesc.FillMode = (D3D10_FILL_MODE)s.fillMode;
			ID3D10RasterizerState* rasterizerState = nullptr;
			dev->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
			dev->RSSetState(rasterizerState);
			Release(rasterizerState);

			D3D10_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(blendDesc));
			blendDesc.BlendEnable[0] = s.blendEnable;
			blendDesc.SrcBlend = (D3D10_BLEND)s.srcBlend;
			blendDesc.DestBlend = (D3D10_BLEND)s.dstBlend;
			blendDesc.BlendOp = (D3D10_BLEND_OP)s.blendop;
			blendDesc.SrcBlendAlpha = (D3D10_BLEND)s.srcBlendAlpha;
			blendDesc.DestBlendAlpha = (D3D10_BLEND)s.destBlendAlpha;
			blendDesc.BlendOpAlpha = (D3D10_BLEND_OP)s.blendOpAlpha;
			blendDesc.RenderTargetWriteMask[0] = s.renderTargetWriteMask;

			ID3D10BlendState* blendState = nullptr;
			dev->CreateBlendState(&blendDesc, &blendState);
			float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			dev->OMSetBlendState(blendState, blendFactor, s.sampleMask);
			blendState->Release();
		}

		void SetViewport(tSireViewport const& v) override {
			D3D10_VIEWPORT vp = {};
			vp.TopLeftX = v.x;
			vp.TopLeftY = v.y;
			vp.Width = v.w;
			vp.Height = v.h;
			vp.MinDepth = v.mind;
			vp.MaxDepth = v.maxd;
			dev->RSSetViewports(1, &vp);
		}

		void CopyResource(intptr_t* dst, intptr_t* src) override {
			dev->CopyResource(reinterpret_cast<ID3D10Resource*>(dst), reinterpret_cast<ID3D10Resource*>(src));
		}

		void SetTexture(intptr_t* texture, intptr_t* textureMask) override {
			cb.hasTex = texture ? true : false;
			cb.hasMask = textureMask ? true : false;

			tex = nullptr;
			mask = nullptr;

			if (texture)
				tex = reinterpret_cast<ID3D10ShaderResourceView*>(texture);

			if (textureMask)
				mask = reinterpret_cast<ID3D10ShaderResourceView*>(textureMask);
		}

		uint8_t* Lock(void* ptr) {
			D3D10_MAPPED_TEXTURE2D map;
			reinterpret_cast<ID3D10Texture2D*>(ptr)->Map(0, D3D10_MAP_READ, 0, &map);
			return (uint8_t*)map.pData;
		}

		void Unlock(void* ptr) {
			reinterpret_cast<ID3D10Texture2D*>(ptr)->Unmap(0);
		}

		// End virtual override	

		ID3D10RenderTargetView** GetRenderTargets() {
			ID3D10RenderTargetView* out[D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT] = {};
			dev->OMGetRenderTargets(D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT, out, nullptr);
			return out;
		}

		ID3D10RenderTargetView* GetRenderTarget() {
			ID3D10RenderTargetView* out = nullptr;
			dev->OMGetRenderTargets(1, &out, nullptr);
			return out;
		}

		ID3D10Texture2D* GetBackBuffer(uint32_t buffer) {
			ID3D10Texture2D* out = nullptr;
			swapchain->GetBuffer(buffer, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&out));
			return out;
		}

		D3D10_TEXTURE2D_DESC GetDesc(ID3D10Texture2D* texture) {
			D3D10_TEXTURE2D_DESC out = {};
			texture->GetDesc(&out);
			return out;
		}

		ID3D10RenderTargetView* CreateRenderTarget(ID3D10Texture2D* texture) {
			ID3D10RenderTargetView* out;
			dev->CreateRenderTargetView(texture, nullptr, &out);
			return out;
		}

		ID3DBlob* CompileShader(std::string const str, const char* szEntrypoint, const char* szTarget) {
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

		ID3D10VertexShader* CreateVertexShader(const void* buffer, size_t size) {
			ID3D10VertexShader* out = nullptr;
			dev->CreateVertexShader(buffer, size, &out);
			return out;
		}

		ID3D10PixelShader* CreatePixelShader(const void* buffer, size_t size) {
			ID3D10PixelShader* out = nullptr;
			dev->CreatePixelShader(buffer, size, &out);
			return out;
		}

		ID3D10InputLayout* CreateInputLayout(std::vector<D3D10_INPUT_ELEMENT_DESC>* layout, const void* buffer, size_t size) {
			ID3D10InputLayout* out = nullptr;
			dev->CreateInputLayout(layout->data(), static_cast<uint32_t>(layout->size()), buffer, size, &out);
			return out;
		}

		ID3D10ShaderResourceView* CreateShaderResourceView(ID3D10Texture2D* texture) {
			ID3D10ShaderResourceView* out = nullptr;
			dev->CreateShaderResourceView(texture, nullptr, &out);
			return out;
		}

		ID3D10BlendState* GetBlendState(float* blendFactor, uint32_t* sampleMask) {
			ID3D10BlendState* out;
			dev->OMGetBlendState(&out, blendFactor, sampleMask);
			return out;
		}

		D3D10_BLEND_DESC GetBlendDesc(ID3D10BlendState* blendState) {
			D3D10_BLEND_DESC out;
			blendState->GetDesc(&out);
			return out;
		}

		void SetBlendState(D3D10_BLEND_DESC* blendStateDesc, float* blendFactor, uint32_t sampleMask) {
			ID3D10BlendState* blendState = nullptr;
			dev->CreateBlendState(blendStateDesc, &blendState);
			dev->OMSetBlendState(blendState, blendFactor, sampleMask);
			Release(blendState);
		}

		void SetShaders(ID3D10VertexShader* v, ID3D10PixelShader* p) {
			vertexShader = v;
			pixelShader = p;
		}

		D3D10_VIEWPORT GetViewport() {
			uint32_t numViewport = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
			D3D10_VIEWPORT out[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

			dev->RSGetViewports(&numViewport, out);
			return out[0];
		}

		ID3D10Texture2D* CreateTexture(uint32_t width, uint32_t height, uint8_t* pixels) {
			ID3D10Texture2D* out = nullptr;
			D3D10_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.Usage = D3D10_USAGE_DEFAULT;
			desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;

			HRESULT hr = dev->CreateTexture2D(&desc, nullptr, &out);

			if (SUCCEEDED(hr)) {
				if (pixels) {
					D3D10_TEXTURE2D_DESC desc;
					out->GetDesc(&desc);
					dev->UpdateSubresource(out, 0, nullptr, pixels, desc.Width * sizeof(UINT), 0);
				}
			}

			return out;
		}
	};

	struct SireDirectX11 : SireRenderer {
		IDXGISwapChain* swapchain;
		ID3D11Device* dev;
		ID3D11DeviceContext* devcon;
		ID3D11Buffer* vb;
		ID3D11Buffer* ib;
		ID3D11Buffer* pb;
		ID3D11SamplerState* ss;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D11VertexShader* internalVertexShader;
		ID3D11PixelShader* internalPixelShader;
		ID3D11ShaderResourceView* tex;
		ID3D11ShaderResourceView* mask;
		ID3D11RasterizerState* rasterizerState;
		ID3D11DepthStencilState* depthStencilState;
		ID3D11BlendState* blendState;
		FLOAT blendFactor[4];
		UINT sampleMask;
		UINT stencilRef;

		SireDirectX11() : SireRenderer() {
			swapchain = nullptr;
			dev = nullptr;
			devcon = nullptr;
			vb = nullptr;
			ib = nullptr;
			pb = nullptr;
			ss = nullptr;
			inputLayout = nullptr;
			vertexShader = nullptr;
			pixelShader = nullptr;
			internalVertexShader = nullptr;
			internalPixelShader = nullptr;
			tex = nullptr;
			mask = nullptr;
			rasterizerState = nullptr;
			depthStencilState = nullptr;
			blendState = nullptr;
			blendFactor[0] = 0.0f;
			blendFactor[1] = 0.0f;
			blendFactor[2] = 0.0f;
			blendFactor[3] = 0.0f;
			sampleMask = 0;
			stencilRef = 0;
		}

		// Start virtual override
		bool IsRendererActive() override {
			if (initialised && swapchain && dev && devcon) {
				HRESULT hr = dev->GetDeviceRemovedReason();
				return SUCCEEDED(hr);
			}

			return false;
		}

		void Init(intptr_t* ptr) override {
			if (initialised)
				return;

			swapchain = reinterpret_cast<IDXGISwapChain*>(ptr);
			HRESULT hResult = swapchain->GetDevice(__uuidof(ID3D11Device), (void**)&dev);

			if (FAILED(hResult))
				return;

			dev->GetImmediateContext(&devcon);

			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
			swapchain->GetDesc(&swapChainDesc);

			hWnd = swapChainDesc.OutputWindow;

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
			ID3DBlob* VS = CompileShader(hlslShader5_0, "VShader", "vs_5_0");
			ID3DBlob* PS = CompileShader(hlslShader5_0, "PShader", "ps_5_0");

			internalVertexShader = CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize());
			internalPixelShader = CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize());

			// Init input layout
			std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			inputLayout = CreateInputLayout(&layout, VS->GetBufferPointer(), VS->GetBufferSize());

			Release(VS);
			Release(PS);

			initialised = true;
		}

		void Shutdown() override {
			if (!initialised)
				return;

			Release(vb);
			Release(ib);
			Release(pb);
			Release(ss);
			Release(inputLayout);
			Release(internalVertexShader);
			Release(internalPixelShader);

			vertexShader = nullptr;
			pixelShader = nullptr;

			swapchain = nullptr;
			dev = nullptr;
			devcon = nullptr;

			initialised = false;
		}

		void Begin() override {
			devcon->RSGetState(&rasterizerState);
			devcon->OMGetDepthStencilState(&depthStencilState, &stencilRef);
			devcon->OMGetBlendState(&blendState, blendFactor, &sampleMask);
		}

		void End() override {
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

			ZeroMemory(&mappedResource, sizeof(mappedResource));
			devcon->Map(ib, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy(mappedResource.pData, indices.data(), numIndices * sizeof(uint16_t));
			devcon->Unmap(ib, 0);

			// Update
			tConstBuff tempcb = cb;
			tempcb.matrix.Transpose();

			ZeroMemory(&mappedResource, sizeof(mappedResource));
			devcon->Map(pb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy(mappedResource.pData, &tempcb, sizeof(tempcb));
			devcon->Unmap(pb, 0);

			ID3D11InputLayout* prevInputLayout = nullptr;
			devcon->IAGetInputLayout(&prevInputLayout);
			devcon->IASetInputLayout(inputLayout);

			auto renderTarget = GetRenderTarget();
			devcon->OMSetRenderTargets(1, &renderTarget, nullptr);

			ID3D11VertexShader* prevVertexShader = nullptr;
			devcon->VSGetShader(&prevVertexShader, nullptr, 0);
			devcon->VSSetShader(vertexShader, nullptr, 0);

			ID3D11PixelShader* prevPixelShader = nullptr;
			devcon->PSGetShader(&prevPixelShader, nullptr, 0);
			devcon->PSSetShader(pixelShader, nullptr, 0);

			ID3D11Buffer* prevVertexConstantBuffer = nullptr;
			devcon->VSGetConstantBuffers(0, 1, &prevVertexConstantBuffer);
			devcon->VSSetConstantBuffers(0, 1, &pb);

			ID3D11Buffer* prevPixelConstantBuffer = nullptr;
			devcon->PSGetConstantBuffers(0, 1, &prevPixelConstantBuffer);
			devcon->PSSetConstantBuffers(0, 1, &pb);

			// Set textures
			ID3D11ShaderResourceView* prevVertexShaderResourceView0 = nullptr;
			devcon->VSGetShaderResources(0, 1, &prevVertexShaderResourceView0);
			devcon->VSSetShaderResources(0, 1, &tex);

			ID3D11ShaderResourceView* prevVertexShaderResourceView1 = nullptr;
			devcon->VSGetShaderResources(1, 1, &prevVertexShaderResourceView1);
			devcon->VSSetShaderResources(1, 1, &mask);

			ID3D11ShaderResourceView* prevPixelShaderResourceView0 = nullptr;
			devcon->PSGetShaderResources(0, 1, &prevPixelShaderResourceView0);
			devcon->PSSetShaderResources(0, 1, &tex);

			ID3D11ShaderResourceView* prevPixelShaderResourceView1 = nullptr;
			devcon->PSGetShaderResources(1, 1, &prevPixelShaderResourceView1);
			devcon->PSSetShaderResources(1, 1, &mask);

			ID3D11SamplerState* prevPixelSamplers = nullptr;
			devcon->PSGetSamplers(0, 1, &prevPixelSamplers);
			devcon->PSSetSamplers(0, 1, &ss);

			ID3D11SamplerState* prevVertexSamplers = nullptr;
			devcon->GSGetSamplers(0, 1, &prevVertexSamplers);
			devcon->GSSetSamplers(0, 1, &ss);

			// Set index/vertex buffers
			UINT stride = sizeof(tVertex);
			UINT offset = 0;

			UINT prevStride;
			UINT prevVertexOffset;
			ID3D11Buffer* prevVertexBuffers = nullptr;
			devcon->IAGetVertexBuffers(0, 1, &prevVertexBuffers, &prevStride, &prevVertexOffset);
			devcon->IASetVertexBuffers(0, 1, &vb, &stride, &offset);

			ID3D11Buffer* prevIndexBuffers = nullptr;
			DXGI_FORMAT prevFormat;
			UINT prevIndexOffset;
			devcon->IAGetIndexBuffer(&prevIndexBuffers, &prevFormat, &prevIndexOffset);
			devcon->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);

			D3D_PRIMITIVE_TOPOLOGY type = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
			switch (primitiveType) {
			case SIRE_LINE:
				type = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
				break;
			case SIRE_POINT:
				type = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
				break;
			case SIRE_TRIANGLE:
				type = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				break;
			}

			D3D_PRIMITIVE_TOPOLOGY prevType;
			devcon->IAGetPrimitiveTopology(&prevType);
			devcon->IASetPrimitiveTopology(type);

			// Draw
			devcon->DrawIndexed(numIndices, 0, 0);

			// Restore shit
			devcon->IASetInputLayout(prevInputLayout);
			Release(prevInputLayout);

			devcon->VSSetShader(prevVertexShader, nullptr, 0);
			Release(prevVertexShader);

			devcon->PSSetShader(prevPixelShader, nullptr, 0);
			Release(prevPixelShader);

			devcon->VSSetConstantBuffers(0, 1, &prevVertexConstantBuffer);
			Release(prevVertexConstantBuffer);

			devcon->PSSetConstantBuffers(0, 1, &prevPixelConstantBuffer);
			Release(prevPixelConstantBuffer);

			devcon->VSSetShaderResources(0, 1, &prevVertexShaderResourceView0);
			Release(prevVertexShaderResourceView0);

			devcon->VSSetShaderResources(1, 1, &prevVertexShaderResourceView1);
			Release(prevVertexShaderResourceView1);

			devcon->PSSetShaderResources(0, 1, &prevPixelShaderResourceView0);
			Release(prevPixelShaderResourceView0);

			devcon->PSSetShaderResources(1, 1, &prevPixelShaderResourceView1);
			Release(prevPixelShaderResourceView1);

			devcon->PSSetSamplers(0, 1, &prevPixelSamplers);
			Release(prevPixelSamplers);

			devcon->GSSetSamplers(0, 1, &prevVertexSamplers);
			Release(prevVertexSamplers);

			devcon->IASetVertexBuffers(0, 1, &prevVertexBuffers, &prevStride, &prevVertexOffset);
			Release(prevVertexBuffers);

			devcon->IASetIndexBuffer(prevIndexBuffers, prevFormat, prevIndexOffset);
			Release(prevIndexBuffers);

			devcon->IASetPrimitiveTopology(prevType);

			devcon->RSSetState(rasterizerState);
			Release(rasterizerState);

			devcon->OMSetDepthStencilState(depthStencilState, stencilRef);
			Release(depthStencilState);

			devcon->OMSetBlendState(blendState, blendFactor, sampleMask);
			Release(blendState);

			Release(renderTarget);
		}

		void SetRenderStates(tRenderState const& s) override {
			D3D11_RASTERIZER_DESC rasterizerDesc;
			ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
			rasterizerDesc.CullMode = (D3D11_CULL_MODE)s.cullMode;
			rasterizerDesc.FillMode = (D3D11_FILL_MODE)s.fillMode;
			ID3D11RasterizerState* rasterizerState = nullptr;
			dev->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
			devcon->RSSetState(rasterizerState);
			Release(rasterizerState);

			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(blendDesc));
			blendDesc.RenderTarget[0].BlendEnable = s.blendEnable;
			blendDesc.RenderTarget[0].SrcBlend = (D3D11_BLEND)s.srcBlend;
			blendDesc.RenderTarget[0].DestBlend = (D3D11_BLEND)s.dstBlend;
			blendDesc.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)s.blendop;
			blendDesc.RenderTarget[0].SrcBlendAlpha = (D3D11_BLEND)s.srcBlendAlpha;
			blendDesc.RenderTarget[0].DestBlendAlpha = (D3D11_BLEND)s.destBlendAlpha;
			blendDesc.RenderTarget[0].BlendOpAlpha = (D3D11_BLEND_OP)s.blendOpAlpha;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = s.renderTargetWriteMask;

			ID3D11BlendState* blendState = nullptr;
			dev->CreateBlendState(&blendDesc, &blendState);
			float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			devcon->OMSetBlendState(blendState, blendFactor, s.sampleMask);
			Release(blendState);
		}

		void CopyResource(intptr_t* dst, intptr_t* src) override {
			devcon->CopyResource(reinterpret_cast<ID3D11Resource*>(dst), reinterpret_cast<ID3D11Resource*>(src));
		}

		void SetViewport(tSireViewport const& v) override {
			D3D11_VIEWPORT vp = {};
			vp.TopLeftX = v.x;
			vp.TopLeftY = v.y;
			vp.Width = v.w;
			vp.Height = v.h;
			vp.MinDepth = v.mind;
			vp.MaxDepth = v.maxd;
			devcon->RSSetViewports(1, &vp);
		}

		void SetTexture(intptr_t* texture, intptr_t* textureMask) override {
			cb.hasTex = texture ? true : false;
			cb.hasMask = textureMask ? true : false;

			tex = nullptr;
			mask = nullptr;

			if (texture)
				tex = reinterpret_cast<ID3D11ShaderResourceView*>(texture);

			if (textureMask)
				mask = reinterpret_cast<ID3D11ShaderResourceView*>(textureMask);
		}


		uint8_t* Lock(void* ptr) override {
			D3D11_MAPPED_SUBRESOURCE map;
			devcon->Map(reinterpret_cast<ID3D11Texture2D*>(ptr), 0, D3D11_MAP_READ, 0, &map);
			return (uint8_t*)map.pData;
		}

		void Unlock(void* ptr) override {
			devcon->Unmap(reinterpret_cast<ID3D11Texture2D*>(ptr), 0);
		}

		// End virtual override

		ID3D11RenderTargetView** GetRenderTargets() {
			ID3D11RenderTargetView* out[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = {};
			devcon->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, out, nullptr);
			return out;
		}

		ID3D11RenderTargetView* GetRenderTarget() {
			ID3D11RenderTargetView* out = nullptr;
			devcon->OMGetRenderTargets(1, &out, nullptr);
			return out;
		}

		ID3D11Texture2D* GetBackBuffer(uint32_t buffer) {
			ID3D11Texture2D* out = nullptr;
			swapchain->GetBuffer(buffer, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&out));
			return out;
		}

		D3D11_TEXTURE2D_DESC GetDesc(ID3D11Texture2D* texture) {
			D3D11_TEXTURE2D_DESC out = {};
			texture->GetDesc(&out);
			return out;
		}

		ID3D11RenderTargetView* CreateRenderTarget(ID3D11Texture2D* texture) {
			ID3D11RenderTargetView* out;
			dev->CreateRenderTargetView(texture, nullptr, &out);
			return out;
		}

		ID3DBlob* CompileShader(std::string const str, const char* szEntrypoint, const char* szTarget) {
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

		ID3D11VertexShader* CreateVertexShader(const void* buffer, size_t size) {
			ID3D11VertexShader* out = nullptr;
			dev->CreateVertexShader(buffer, size, NULL, &out);
			return out;
		}

		ID3D11PixelShader* CreatePixelShader(const void* buffer, size_t size) {
			ID3D11PixelShader* out = nullptr;
			dev->CreatePixelShader(buffer, size, NULL, &out);
			return out;
		}

		ID3D11InputLayout* CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>* layout, const void* buffer, size_t size) {
			ID3D11InputLayout* out = nullptr;
			dev->CreateInputLayout(layout->data(), static_cast<uint32_t>(layout->size()), buffer, size, &out);
			return out;
		}

		ID3D11ShaderResourceView* CreateShaderResourceView(ID3D11Texture2D* texture) {
			ID3D11ShaderResourceView* out = nullptr;
			dev->CreateShaderResourceView(texture, nullptr, &out);
			return out;
		}

		ID3D11BlendState* GetBlendState(float* blendFactor, uint32_t* sampleMask) {
			ID3D11BlendState* out;
			devcon->OMGetBlendState(&out, blendFactor, sampleMask);
			return out;
		}

		D3D11_BLEND_DESC GetBlendDesc(ID3D11BlendState* blendState) {
			D3D11_BLEND_DESC out;
			blendState->GetDesc(&out);
			return out;
		}

		void SetBlendState(D3D11_BLEND_DESC* blendStateDesc, float* blendFactor, uint32_t sampleMask) {
			ID3D11BlendState* blendState = nullptr;
			dev->CreateBlendState(blendStateDesc, &blendState);
			devcon->OMSetBlendState(blendState, blendFactor, sampleMask);
			Release(blendState);
		}

		void SetShaders(ID3D11VertexShader* v, ID3D11PixelShader* p) {
			vertexShader = v;
			pixelShader = p;
		}

		D3D11_VIEWPORT GetViewport() {
			uint32_t numViewport = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
			D3D11_VIEWPORT out[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

			devcon->RSGetViewports(&numViewport, out);
			return out[0];
		}

		ID3D11Texture2D* CreateTexture(uint32_t width, uint32_t height, uint8_t* pixels) {
			ID3D11Texture2D* out = nullptr;
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

			HRESULT hr = dev->CreateTexture2D(&desc, nullptr, &out);

			if (SUCCEEDED(hr)) {
				if (pixels) {
					D3D11_TEXTURE2D_DESC desc;
					out->GetDesc(&desc);
					devcon->UpdateSubresource(out, 0, nullptr, pixels, desc.Width * sizeof(UINT), 0);
				}
			}

			return out;
		}

	};

#ifdef SIRE_INCLUDE_DX12
	struct SireDirectX12 : SireRenderer {
		IDXGISwapChain* swapchain;
		ID3D12Device* dev;
		ID3D12CommandQueue* commandQueue;
		ID3D12CommandAllocator* commandAllocator;
		ID3D12GraphicsCommandList* commandList;
		ID3D12DescriptorHeap* descriptorHeap;
		ID3D12Resource* vertexBuffer;
		ID3D12Resource* indexBuffer;
		ID3D12Resource* constantBuffer;
		ID3D12DescriptorHeap* samplerHeap;
		ID3D12RootSignature* rootSignature;
		ID3D12PipelineState* pipelineState;
		ID3D12ShaderReflection* vertexShader;
		ID3D12ShaderReflection* pixelShader;
		ID3D12ShaderReflection* internalVertexShader;
		ID3D12ShaderReflection* internalPixelShader;
		ID3D12Resource* tex;
		ID3D12Resource* mask;

		SireDirectX12() : SireRenderer() {
			swapchain = nullptr;
			dev = nullptr;
			commandQueue = nullptr;
			commandAllocator = nullptr;
			commandList = nullptr;
			descriptorHeap = nullptr;
			vertexBuffer = nullptr;
			indexBuffer = nullptr;
			constantBuffer = nullptr;
			samplerHeap = nullptr;
			rootSignature = nullptr;
			pipelineState = nullptr;
			vertexShader = nullptr;
			pixelShader = nullptr;
			internalVertexShader = nullptr;
			internalPixelShader = nullptr;
			tex = nullptr;
			mask = nullptr;
		}

		void Init(intptr_t* ptr) override {
			if (initialised)
				return;

			swapchain = reinterpret_cast<IDXGISwapChain*>(ptr);
			HRESULT hResult = swapchain->GetDevice(__uuidof(ID3D11Device), (void**)&dev);

			if (FAILED(hResult))
				return;

			dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&commandAllocator);

			if (!commandAllocator)
				return;

			dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, __uuidof(ID3D12GraphicsCommandList), (void**)&commandList);
			
			commandList->Close();

			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
			swapchain->GetDesc(&swapChainDesc);

			hWnd = swapChainDesc.OutputWindow;

			D3D12_RESOURCE_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));

			bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			bufferDesc.Alignment = 0;
			bufferDesc.Width = sizeof(tVertex) * 65536;
			bufferDesc.Height = 1;
			bufferDesc.DepthOrArraySize = 1;
			bufferDesc.MipLevels = 1;
			bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
			bufferDesc.SampleDesc.Count = 1;
			bufferDesc.SampleDesc.Quality = 0;
			bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

			D3D12_HEAP_PROPERTIES heapProp;
			ZeroMemory(&heapProp, sizeof(heapProp));
			heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;

			// Vertex buffer
			dev->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &bufferDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, __uuidof(ID3D12Resource), (void**)&vertexBuffer);

			// Index buffer
			bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			dev->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &bufferDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, __uuidof(ID3D12Resource), (void**)&indexBuffer);

			// Constant buffer
			bufferDesc.Width = sizeof(tConstBuff);
			dev->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &bufferDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, __uuidof(ID3D12Resource), (void**)&constantBuffer);

			D3D12_SAMPLER_DESC samplerDesc;
			ZeroMemory(&samplerDesc, sizeof(samplerDesc));
			samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			samplerDesc.BorderColor[0] = 0.0f;
			samplerDesc.BorderColor[1] = 0.0f;
			samplerDesc.BorderColor[2] = 0.0f;
			samplerDesc.BorderColor[3] = 0.0f;
			samplerDesc.MinLOD = 0.0f;
			samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;

			dev->CreateSampler(&samplerDesc, samplerHeap->GetCPUDescriptorHandleForHeapStart());

			// Init shaders
			ID3DBlob* VS = CompileShader(hlslShader5_0, "VShader", "vs_5_0");
			ID3DBlob* PS = CompileShader(hlslShader5_0, "PShader", "ps_5_0");

			internalVertexShader = CreateShaderReflection(VS->GetBufferPointer(), VS->GetBufferSize());
			internalPixelShader = CreateShaderReflection(PS->GetBufferPointer(), PS->GetBufferSize());

			D3D12_DESCRIPTOR_RANGE descriptorRange;
			descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			descriptorRange.NumDescriptors = 1;
			descriptorRange.BaseShaderRegister = 0;
			descriptorRange.RegisterSpace = 0;
			descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			D3D12_ROOT_PARAMETER rootParameters[1];
			rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;
			rootParameters[0].DescriptorTable.pDescriptorRanges = &descriptorRange;
			rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

			D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
			rootSignatureDesc.NumParameters = 1;
			rootSignatureDesc.pParameters = rootParameters;
			rootSignatureDesc.NumStaticSamplers = 0;
			rootSignatureDesc.pStaticSamplers = nullptr;
			rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

			ID3DBlob* signature;
			ID3DBlob* error;
			D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
			dev->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));

			initialised = true;
		}

		void Shutdown() override {
			if (!initialised)
				return;

			Release(vertexBuffer);
			Release(indexBuffer);
			Release(constantBuffer);
			Release(rootSignature);
			Release(internalVertexShader);
			Release(internalPixelShader);

			vertexShader = nullptr;
			pixelShader = nullptr;

			swapchain = nullptr;
			dev = nullptr;

			initialised = false;
		}

		void Begin() override {
			
		}

		void End() override {
			// Fallback to internal shaders if unset.
			if (!pixelShader && internalPixelShader)
				pixelShader = internalPixelShader;

			if (!vertexShader && internalVertexShader)
				vertexShader = internalVertexShader;

		}

		void SetRenderStates(tRenderState const& s) override {
			
		}

		void CopyResource(intptr_t* dst, intptr_t* src) override {

		}

		void SetViewport(tSireViewport const& v) override {

		}

		void SetTexture(intptr_t* texture, intptr_t* textureMask) override {
			cb.hasTex = texture ? true : false;
			cb.hasMask = textureMask ? true : false;

			texture = nullptr;
			textureMask = nullptr;

			if (texture)
				tex = reinterpret_cast<ID3D12Resource*>(texture);

			if (textureMask)
				mask = reinterpret_cast<ID3D12Resource*>(textureMask);
		}


		uint8_t* Lock(void* ptr) override {
			return nullptr;
		}

		void Unlock(void* ptr) override {

		}

		// End virtual override

		ID3DBlob* CompileShader(std::string const str, const char* szEntrypoint, const char* szTarget) {
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

		ID3D12ShaderReflection* CreateShaderReflection(const void* buffer, size_t size) {
			ID3D12ShaderReflection* out = nullptr;
			D3DReflect(buffer, size, IID_PPV_ARGS(&out));
			return out;
		}
	};

#endif

#ifdef SIRE_INCLUDE_OPENGL
	struct SireOpenGL : SireRenderer {
		HDC con;
		HGLRC conres;
		uint32_t tex;
		uint32_t mask;

		uint32_t vbo;
		uint32_t vao;

		uint32_t ibo;

		uint32_t vertexShader;
		uint32_t pixelShader;

		uint32_t shaderProgram;

		SireOpenGL() : SireRenderer() {
			con = nullptr;
			conres = nullptr;
			tex = 0;
			mask = 0;
			vbo = 0;
			vao = 0;
			ibo = 0;

			vertexShader = 0;
			pixelShader = 0;

			shaderProgram = 0;
		}

		// Start virtual override
		bool IsRendererActive() override {
			const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
			return con && conres && version;
		}

		void Init(intptr_t* ptr) override {
			if (initialised)
				return;

			con = reinterpret_cast<HDC>(ptr);
			conres = wglCreateContext(con);

			if (!gladLoadGL()) {
				std::cout << "Glad error" << std::endl;
			}

			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ibo);
			glGenVertexArrays(1, &vao);

			glBindVertexArray(vao);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(tVertex) * 65536, nullptr, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 65536, nullptr, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			uint32_t shader = glCreateShader(GL_VERTEX_SHADER);
			const char* shaderSource = glslShader3_3_0.c_str();
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, shader);
			glLinkProgram(shaderProgram);
			glDeleteShader(shader);

			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glUseProgram(0);

			initialised = true;
		}

		void Shutdown() override {
			if (!initialised)
				return;

			con = nullptr;

			if (conres) {
				wglDeleteContext(conres);
				conres = nullptr;
			}

			tex = 0;
			mask = 0;

			glDeleteProgram(shaderProgram);

			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);

			initialised = false;
		}

		void Begin() override {

		}

		void End() override {
			if (vertices.empty())
				throw std::runtime_error("Error End() method has been called before settings vertices.");

			auto prevconres = wglGetCurrentContext();
			wglMakeCurrent(con, conres);

			glBindVertexArray(vao);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(tVertex), vertices.data());

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(tVertex), (void*)offsetof(tVertex, pos));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(tVertex), (void*)offsetof(tVertex, col));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(tVertex), (void*)offsetof(tVertex, uv0));

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(tVertex), (void*)offsetof(tVertex, uv1));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, numIndices * sizeof(uint16_t), indices.data());

			glUseProgram(shaderProgram);

			tConstBuff tempcb = cb;
			tempcb.matrix.Transpose();
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "proj"), 1, GL_FALSE, &tempcb.matrix.ToFloatArray()[0]);
			glUniform1i(glGetUniformLocation(shaderProgram, "hasTex"), tempcb.hasTex);
			glUniform1i(glGetUniformLocation(shaderProgram, "hasMask"), tempcb.hasMask);
			glUniform1i(glGetUniformLocation(shaderProgram, "swapColors"), tempcb.swapColors);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex);
			glUniform1i(glGetUniformLocation(shaderProgram, "tex0"), 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mask);
			glUniform1i(glGetUniformLocation(shaderProgram, "mask0"), 1);

			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glUseProgram(0);

			wglMakeCurrent(con, prevconres);
		}

		void SetVertices(tVertex const& v) override {

		}

		void SetRenderStates(tRenderState const& s) override {
			if (s.blendEnable)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
			
			glBlendFunc(GL_SRC_ALPHA, SireToOpenGLBlendState(s.srcBlend));
			glBlendFunc(GL_DST_ALPHA, SireToOpenGLBlendState(s.dstBlend));

			glEnable(GL_CULL_FACE);
			glCullFace(SireToOpenGLCullMode(s.cullMode));

			glEnable(GL_DEPTH_TEST);
			glDisable(GL_STENCIL_TEST);
			glEnable(GL_SCISSOR_TEST);

			glPolygonMode(GL_FRONT_AND_BACK, SireFillMode(s.fillMode));
		}

		void SetViewport(tSireViewport const& v) override {
			glViewport(static_cast<int32_t>(v.x), static_cast<int32_t>(v.y), static_cast<int32_t>(v.w), static_cast<int32_t>(v.h));
		}

		void CopyResource(intptr_t* dst, intptr_t* src) override {

		}

		void SetTexture(intptr_t* texture, intptr_t* textureMask) override {
			tex = texture ? reinterpret_cast<tTexture2D*>(texture)->id : 0;
			mask = textureMask ? reinterpret_cast<tTexture2D*>(textureMask)->id : 0;
		}

		// End virtual override
		uint32_t SireFillMode(int8_t mode) {
			switch (mode) {
			case SIRE_FILL_WIREFRAME:
				return GL_LINE;
			case SIRE_FILL_SOLID:
				return GL_FILL;
			}

			return 0;
		}

		uint32_t SireToOpenGLCullMode(int8_t mode) {
			switch (mode) {
				case SIRE_CULL_NONE:
					glDisable(GL_CULL_FACE);
					return 0;
				case SIRE_CULL_FRONT:
					return GL_FRONT;
				case SIRE_CULL_BACK:
					return GL_BACK;
			}

			return 0;
		}

		uint32_t SireToOpenGLBlendState(int8_t blend) {
			switch (blend) {
			case SIRE_BLEND_ZERO:
				return GL_ZERO;
			case SIRE_BLEND_ONE:
				return GL_ONE;
			case SIRE_BLEND_SRC_COLOR:
				return GL_SRC_COLOR;
			case SIRE_BLEND_INV_SRC_COLOR:
				return GL_ONE_MINUS_SRC_COLOR;
			case SIRE_BLEND_SRC_ALPHA:
				return GL_SRC_ALPHA;
			case SIRE_BLEND_INV_SRC_ALPHA:
				return GL_ONE_MINUS_SRC_ALPHA;
			case SIRE_BLEND_DEST_ALPHA:
				return GL_DST_ALPHA;
			case SIRE_BLEND_INV_DEST_ALPHA:
				return GL_ONE_MINUS_DST_ALPHA;
			case SIRE_BLEND_DEST_COLOR:
				return GL_DST_COLOR;
			case SIRE_BLEND_INV_DEST_COLOR:
				return GL_ONE_MINUS_DST_COLOR;
			case SIRE_BLEND_SRC_ALPHA_SAT:
				return GL_SRC_ALPHA_SATURATE;
			}

			return 0;
		}

		tTexture2D* GetBackBuffer(uint32_t buffer) {
			int32_t w = 0;
			int32_t h = 0;
			
			HDC hdc = wglGetCurrentDC();
			HDC hMemoryDC = CreateCompatibleDC(hdc);
			
			RECT windowRect = {};
			GetClientRect(WindowFromDC(hdc), &windowRect);
			
			w = windowRect.right - windowRect.left;
			h = windowRect.bottom - windowRect.top;
			
			HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
			
			BitBlt(hMemoryDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			
			BITMAPINFO bitmapInfo = { 0 };
			bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bitmapInfo.bmiHeader.biWidth = w;
			bitmapInfo.bmiHeader.biHeight = -h;
			bitmapInfo.bmiHeader.biPlanes = 1;
			bitmapInfo.bmiHeader.biBitCount = 32;
			
			uint8_t* pixels = new unsigned char[w * h * 4];
			
			GetDIBits(hMemoryDC, hBitmap, 0, h, pixels, &bitmapInfo, DIB_RGB_COLORS);
			
			tTexture2D* out = CreateTexture(w, h, pixels);
			
			delete[] pixels;

			return out;
		}

		tTexture2D* CreateTexture(int32_t width, int32_t height, uint8_t* pixels) {
			tTexture2D* out = new tTexture2D();
			glGenTextures(1, &out->id);
			glBindTexture(GL_TEXTURE_2D, out->id);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			out->width = width;
			out->height = height;

			return out;
		}

		void CopyResources() {

		}
	};

#endif

#ifdef SIRE_INCLUDE_VULKAN
	struct SireVulkan : SireRenderer {
		SireVulkan() {

		}

		// Start virtual override

		bool IsRendererActive() override { 
			return false;
		}

		void Init(intptr_t* ptr) override {

		}

		void Shutdown() override {

		}

		void Begin() override {

		}

		void End() override {
		}

		void SetVertices(tVertex const& v) override {
		}

		void SetRenderStates(tRenderState const& s) override {

		}

		void SetViewport(tSireViewport const& v) override {

		}

		void CopyResource(intptr_t* dst, intptr_t* src) override {

		}

		void SetTexture(intptr_t* tex, intptr_t* mask) override {
		
		}

		// End virtual override	
	};

#endif

	static constexpr auto SIRE_NUM_MIN_VERTEX_INDEX = 4096;

	static inline tSireShared shared = {};

	static inline eSirePrimitiveType primitiveType = SIRE_TRIANGLE;
	static inline std::vector<tVertex> vertices = {};
	static inline tSireFloat4 color = {};
	static inline tSireFloat2 uv0 = {};
	static inline tSireFloat2 uv1 = {};

	static inline std::vector<uint16_t> indices = {};
	static inline uint32_t numIndices = 0;

	static inline std::array<SireRenderer*, SIRE_NUM_RENDERERS> renderers = {};
	static inline eSireRenderer currentRenderer = SIRE_RENDERER_NULL;
	static inline intptr_t* currentRendererMainPtr = nullptr;
	static inline bool renderersInitialised = false;

	static inline tConstBuff cb = { {}, false, false };

	static inline std::string glslShader3_3_0 = R"(
    #version 330 core

    layout(std140) uniform ConstantBuffer
    {
        mat4 proj;
        int hasTex;
        int hasMask;
		int swapColors;    
	};

    uniform sampler2D tex0;
    uniform sampler2D mask0;

    layout(location = 0) in vec4 position;
    layout(location = 1) in vec4 color;
    layout(location = 2) in vec2 uv0;
    layout(location = 3) in vec2 uv1;

    out vec4 FragColor;

    void main()
    {
        gl_Position = proj * position;
        FragColor = color;

        if (hasTex )
        {
            FragColor *= texture(tex0, uv0);
            FragColor.a = max(FragColor.a, color.a);
        }

        if (hasMask)
        {
            FragColor *= texture(mask0, uv1);
        }

		if (swapColors)
		{	
			float prev = FragColor.r;
			FragColor.r = FragColor.b;
			FragColor.b = prev;
		}
    }
	)";

	static inline std::string hlslShader2_0 = R"(
	matrix proj;
	int hasTex;
	int hasMask;
	int swapColors;
	
	sampler2D tex0 : register(s0);
	sampler2D mask0 : register(s1);
	
	struct VOut
	{
	    float4 position : POSITION;
	    float4 color : COLOR;
	    float2 uv0 : TEXCOORD0;
	    float2 uv1 : TEXCOORD1;
	};
	
	VOut VShader(float4 position : POSITION, float4 color : COLOR, float2 uv0 : TEXCOORD0, float2 uv1 : TEXCOORD1)
	{
	    VOut output;
	
	    output.position = mul(position, proj);
	    output.color = color;
	    output.uv0 = uv0;
	    output.uv1 = uv1;
	
	    return output;
	}
	
	float4 PShader(VOut input) : COLOR
	{
	    float4 c = input.color;

	    if (hasTex)
	    {   
	        c *= tex2D(tex0, input.uv0);
	        c.a = max(c.a, input.color.a);
	    }
	    
	    if (hasMask)
	    {
	        c *= tex2D(mask0, input.uv1);
	    }

		//if (swapColors)
		//{	
		//	float prev = c.r;
		//	c.r = c.b;
		//	c.b = prev;
		//}
	    
	    return c;
	}
	)";

	static inline std::string hlslShader4_0 = R"(
	cbuffer ConstantBuffer : register(b0)
	{
	    matrix proj;
	    int hasTex;
	    int hasMask;
		int swapColors;
	};
	
	Texture2D tex0 : register(t0);
	Texture2D mask0 : register(t1);
	SamplerState sampler0 : register(s0);
	
	struct VOut
	{
	    float4 position : POSITION;
	    float4 color : COLOR;
	    float2 uv0 : TEXCOORD0;
	    float2 uv1 : TEXCOORD1;
	};
	
	VOut VShader(float4 position : POSITION, float4 color : COLOR, float2 uv0 : TEXCOORD0, float2 uv1 : TEXCOORD1)
	{
	    VOut output;
	
	    output.position = mul(position, proj);
	    output.color = color;
	    output.uv0 = uv0;
	    output.uv1 = uv1;
	
	    return output;
	}
	
	float4 PShader(VOut input) : SV_Target
	{
	    float4 c = input.color;
	
	    if (hasTex)
	    {
	        c *= tex0.Sample(sampler0, input.uv0);
	        c.a = max(c.a, input.color.a);
	    }
	
	    if (hasMask)
	    {
	        c *= mask0.Sample(sampler0, input.uv1);
	    }

		if (swapColors)
		{	
			float prev = c.r;
			c.r = c.b;
			c.b = prev;
		}
	
	    return c;
	}
	)";


	static inline std::string hlslShader5_0 = R"(
	cbuffer ConstantBuffer : register(b0)
	{
	    matrix proj;
	    int hasTex;
	    int hasMask;
		int swapColors;
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
	
	    output.position = mul(position, proj);
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

		if (swapColors)
		{	
			float prev = c.r;
			c.r = c.b;
			c.b = prev;
		}
	    
	    return c;
	}
	)";

public:
	static inline eSireRenderer const GetCurrentRenderer() {
		return currentRenderer;
	}

	template <typename T = SireRenderer>
	static inline T* const GetRenderers(eSireRenderer re) {
		return reinterpret_cast<T*>(renderers.at(re));
	}

	static inline bool IsRendererActive() {
		return GetCurrentRenderer() != SIRE_RENDERER_NULL && GetRenderers(GetCurrentRenderer())->IsRendererActive();
	}

	static inline void Begin(eSirePrimitiveType type) {
		if (!IsRendererActive())
			return;

		primitiveType = type;
		vertices.clear();
		indices.clear();
		numIndices = 0;

		color = { 1.0f, 1.0f, 1.0f, 1.0f };
		uv0 = { 0.0f, 0.0f };
		uv1 = { 0.0f, 0.0f };

		return GetRenderers(GetCurrentRenderer())->Begin();
	}

	static inline void End() {
		if (!IsRendererActive())
			return;

		// Deduce indices automatically if unset.
		if (indices.empty()) {
			uint16_t i = 0;
			for (auto& it : vertices) {
				indices.push_back(i++);
			}

			numIndices = static_cast<uint32_t>(indices.size());
		}

		GetRenderers(GetCurrentRenderer())->SetRenderStates(shared.renderStates);
		return GetRenderers(GetCurrentRenderer())->End();
	}

	static inline void SetColor4f(float r, float g, float b, float a) {
		if (!IsRendererActive())
			return;

		color = { r, g, b, a };
	}

	static inline void SetColor3f(float r, float g, float b) {
		if (!IsRendererActive())
			return;

		SetColor4f(r, g, b, 1.0f);
	}

	static inline void SetTexCoords4f(float x1, float y1, float x2, float y2) {
		if (!IsRendererActive())
			return;

		uv0 = { x1, y1 };
		uv1 = { x2, y2 };
	}

	static inline void SetTexCoords2f(float x, float y) {
		if (!IsRendererActive())
			return;

		SetTexCoords4f(x, y, x, y);
	}

	static inline void SetVertex3f(float x, float y, float z) {
		if (!IsRendererActive())
			return;

		tVertex v = {};
		v.pos.x = x;
		v.pos.y = y;
		v.pos.z = z;
		v.col = color;
		v.uv0 = uv0;
		v.uv1 = uv1;

		vertices.push_back(v);

		return GetRenderers(GetCurrentRenderer())->SetVertices(v);
	}

	static inline void SetVertex2f(float x, float y) {
		if (!IsRendererActive())
			return;

		SetVertex3f(x, y, 0.0f);
	}

	static inline void SetIndex1i(uint16_t i) {
		if (!IsRendererActive())
			return;

		indices.push_back(i);
	}

	static inline void SetIndices(std::vector<uint16_t> const& i, int32_t n) {
		if (!IsRendererActive())
			return;

		indices = i;
		numIndices = n;
	}

	static inline void SetRenderState(eSireRenderState state, uint32_t value) {
		if (!IsRendererActive())
			return;

		switch (state) {
		case SIRE_BLEND_ALPHATESTENABLE:
			shared.renderStates.blendEnable = value;
			break;
		case SIRE_BLEND_SRCBLEND:
			shared.renderStates.srcBlend = value;
			break;
		case SIRE_BLEND_DESTBLEND:
			shared.renderStates.destBlendAlpha = value;
			break;
		case SIRE_BLEND_BLENDOP:
			shared.renderStates.blendop = value;
			break;
		case SIRE_BLEND_SRCBLENDALPHA:
			shared.renderStates.srcBlendAlpha = value;
			break;
		case SIRE_BLEND_DESTBLENDALPHA:
			shared.renderStates.destBlendAlpha = value;
			break;
		case SIRE_BLEND_BLENDOPALPHA:
			shared.renderStates.blendOpAlpha = value;
			break;
		case SIRE_BLEND_WRITEMASK:
			shared.renderStates.renderTargetWriteMask = value;
			break;
		case SIRE_BLEND_CULLMODE:
			shared.renderStates.cullMode = value;
			break;
		case SIRE_BLEND_FILLMODE:
			shared.renderStates.fillMode = value;
			break;
		case SIRE_BLEND_STENCILENABLE:
			shared.renderStates.stencilEnable = value;
			break;
		case SIRE_BLEND_COLORWRITEENABLE:
			shared.renderStates.sampleMask = value;
			break;
		}
	}

	template <typename T>
	static inline void Init(eSireRenderer re, T* ptr) {
		if (currentRenderer != SIRE_RENDERER_NULL)
			return;

		if (vertices.max_size() < SIRE_NUM_MIN_VERTEX_INDEX)
			vertices.reserve(SIRE_NUM_MIN_VERTEX_INDEX);

		if (indices.max_size() < SIRE_NUM_MIN_VERTEX_INDEX)
			indices.reserve(SIRE_NUM_MIN_VERTEX_INDEX);

		if (!renderersInitialised) {
			if (!renderers.at(re)) {
				SireRenderer* renderer = nullptr;

				switch (re) {
				case SIRE_RENDERER_NULL:
					break;
#ifdef SIRE_INCLUDE_DX9
				case SIRE_RENDERER_DX9:
					renderer = new SireDirectX9();
					break;
#endif
#ifdef SIRE_INCLUDE_DX10
				case SIRE_RENDERER_DX10:
					renderer = new SireDirectX10();
					break;
#endif
#ifdef SIRE_INCLUDE_DX11
				case SIRE_RENDERER_DX11:
					renderer = new SireDirectX11();
					break;
#endif
#ifdef SIRE_INCLUDE_DX12
				case SIRE_RENDERER_DX12:
					renderer = new SireDirectX12();
					break;
#endif
#ifdef SIRE_INCLUDE_OPENGL
				case SIRE_RENDERER_OPENGL:
					renderer = new SireOpenGL();
					break;
#endif
#ifdef SIRE_INCLUDE_VULKAN
				case SIRE_RENDERER_VULKAN:
					renderer = new SireVulkan();
					break;
#endif
				}

				renderers.at(re) = renderer;
			}
			renderersInitialised = true;
		}

		currentRenderer = re;
		currentRendererMainPtr = reinterpret_cast<intptr_t*>(ptr);

		GetRenderers(GetCurrentRenderer())->Init(currentRendererMainPtr);

		InitAfterRenderer();
	}

	static inline void InitAfterRenderer() {
		;;
	}

	static inline void Shutdown() {
		if (currentRenderer == SIRE_RENDERER_NULL)
			return;

		GetRenderers(GetCurrentRenderer())->Shutdown();

		vertices.clear();
		indices.clear();

		if (renderersInitialised) {
			for (auto& it : renderers) {
				if (it) {
					delete it;
					it = nullptr;
				}
			}

			renderersInitialised = false;
		}

		currentRenderer = SIRE_RENDERER_NULL;
		currentRendererMainPtr = nullptr;
	}

	template<typename T>
	static inline void Release(T*& res) {
		if (res) {
			res->Release();
			res = nullptr;
		}
	}

	static inline HWND GetHWND() {
		return GetRenderers(GetCurrentRenderer())->GetWindow();
	}

	static inline tSireInt2 GetWindowSize() {
		RECT windowRect;
		GetWindowRect(GetHWND(), &windowRect);

		tSireInt2 out;
		out.x = static_cast<int32_t>(windowRect.right - windowRect.left);
		out.y = static_cast<int32_t>(windowRect.bottom - windowRect.top);

		return out;
	}

	// These 2 works for old devices but process it's too slow to be used each frame.
	static inline void _GetClosestPowerOfTwoSize(uint32_t& width, uint32_t& height) {
		height = static_cast<uint32_t>(std::pow(2, std::ceil(std::log2(height))));
		width = height;
	}

	static inline std::vector<uint8_t> _ResizePixels(uint8_t* srcPixels, uint32_t srcWidth, uint32_t srcHeight, uint32_t dstWidth, uint32_t dstHeight) {
		float scaleX = static_cast<float>(dstWidth) / static_cast<float>(srcWidth);
		float scaleY = static_cast<float>(dstHeight) / static_cast<float>(srcHeight);

		std::vector<uint8_t> resizedPixels(dstWidth * dstHeight * 4, 0);

		for (int32_t y = 0; y < dstHeight; ++y) {
			for (int32_t x = 0; x < dstWidth; ++x) {
				int srcX = static_cast<int>(x / scaleX);
				int srcY = static_cast<int>(y / scaleY);
				int srcIndex = (srcY * srcWidth + srcX) * 4;
				int dstIndex = (y * dstWidth + x) * 4;

				if (srcX < srcWidth && srcY < srcHeight) {
					resizedPixels[dstIndex] = srcPixels[srcIndex];
					resizedPixels[dstIndex + 1] = srcPixels[srcIndex + 1];
					resizedPixels[dstIndex + 2] = srcPixels[srcIndex + 2];
					resizedPixels[dstIndex + 3] = srcPixels[srcIndex + 3];
				}
			}
		}

		return resizedPixels;
	}
	//
	
	// Use only if device has non power of 2 support.
	static inline SirePtr<tSireTexture2D> GetFakeBackBuffer(uint32_t buffer) {
		static std::vector<uint8_t> data;
		HWND wnd = GetHWND();
		auto windowSize = GetWindowSize();

		uint32_t fileSize = (windowSize.x * windowSize.y * 4);
		if (data.size() < fileSize) {
			data.resize(fileSize);
		}

		HDC dc = GetDC(GetHWND());
		HDC compdc = CreateCompatibleDC(dc);
	
		HBITMAP bmp = CreateCompatibleBitmap(dc, windowSize.x, windowSize.y);
		HBITMAP bmpOld = static_cast<HBITMAP>(SelectObject(compdc, bmp));
	
		BitBlt(compdc, 0, 0, windowSize.x, windowSize.y, dc, 0, 0, SRCCOPY);
		GetBitmapBits(bmp, fileSize, data.data());
	
		auto out = CreateTexture(windowSize.x, windowSize.y, data.data());
		out->swapColors = true;

		SelectObject(compdc, bmpOld);
		DeleteObject(bmp);
		DeleteDC(compdc);
		ReleaseDC(wnd, dc);
	
		return out;
	}

	static inline uint8_t* Lock(tSireTexture2D* surface) {
		return GetRenderers(GetCurrentRenderer())->Lock(surface->ptrs.surface);
	}

	static inline void Unlock(tSireTexture2D* surface) {
		GetRenderers(GetCurrentRenderer())->Unlock(surface->ptrs.surface);
	}

	static inline SirePtr<tSireTexture2D> GetBackBuffer(int32_t buffer) {
		if (!IsRendererActive())
			return nullptr;

		if (buffer == -1)
			return GetFakeBackBuffer(0);

		SirePtr<tSireTexture2D> out(new tSireTexture2D);

		switch (GetCurrentRenderer()) {
#ifdef SIRE_INCLUDE_DX9
		case SIRE_RENDERER_DX9: {
			auto result = GetRenderers<SireDirectX9>(GetCurrentRenderer())->GetBackBufferSurface(buffer);
			auto desc = GetRenderers<SireDirectX9>(GetCurrentRenderer())->GetDesc(result);
			out->Set(desc.Width, desc.Height, desc.Format, nullptr, reinterpret_cast<intptr_t*>(result));
		} break;
#endif
#ifdef SIRE_INCLUDE_DX10
		case SIRE_RENDERER_DX10: {
			auto tex = GetRenderers<SireDirectX10>(GetCurrentRenderer())->GetBackBuffer(buffer);

			if (tex) {
				auto result = GetRenderers<SireDirectX10>(GetCurrentRenderer())->CreateShaderResourceView(tex);
				auto desc = GetRenderers<SireDirectX10>(GetCurrentRenderer())->GetDesc(tex);

				if (tex) {
					out->Set(desc.Width, desc.Height, 0, reinterpret_cast<intptr_t*>(result), reinterpret_cast<intptr_t*>(tex));
				}
			}
		} break;
#endif
#ifdef SIRE_INCLUDE_DX11
		case SIRE_RENDERER_DX11: {
			auto tex = GetRenderers<SireDirectX11>(GetCurrentRenderer())->GetBackBuffer(buffer);

			if (tex) {
				auto result = GetRenderers<SireDirectX11>(GetCurrentRenderer())->CreateShaderResourceView(tex);
				auto desc = GetRenderers<SireDirectX11>(GetCurrentRenderer())->GetDesc(tex);

				if (tex) {
					out->Set(desc.Width, desc.Height, 0, reinterpret_cast<intptr_t*>(result), reinterpret_cast<intptr_t*>(tex));
				}
			}
		} break;
#endif
#ifdef SIRE_INCLUDE_DX12
		case SIRE_RENDERER_DX12: {
		} break;
#endif
#ifdef SIRE_INCLUDE_OPENGL
		case SIRE_RENDERER_OPENGL: {
		} break;
#endif
		}

		return out;
	}

	static inline SirePtr<tSireTexture2D> CreateTexture(int32_t width, int32_t height, uint8_t* pixels) {
		if (!IsRendererActive())
			return nullptr;

		SirePtr<tSireTexture2D> out(new tSireTexture2D);

		switch (GetCurrentRenderer()) {
#ifdef SIRE_INCLUDE_DX9
		case SIRE_RENDERER_DX9: {
			IDirect3DSurface9* sout = nullptr;
			auto result = GetRenderers<SireDirectX9>(GetCurrentRenderer())->CreateTexture(width, height, pixels, &sout);

			if (result)
				out->Set(width, height, 0, reinterpret_cast<intptr_t*>(result), reinterpret_cast<intptr_t*>(sout));
		} break;
#endif
#ifdef SIRE_INCLUDE_DX10
		case SIRE_RENDERER_DX10: {
			auto tex = GetRenderers<SireDirectX10>(GetCurrentRenderer())->CreateTexture(width, height, pixels);

			if (tex) {
				auto result = GetRenderers<SireDirectX10>(GetCurrentRenderer())->CreateShaderResourceView(tex);

				if (result)
					out->Set(width, height, 0, reinterpret_cast<intptr_t*>(result), reinterpret_cast<intptr_t*>(tex));
			}
		} break;
#endif
#ifdef SIRE_INCLUDE_DX11
		case SIRE_RENDERER_DX11: {
			auto tex = GetRenderers<SireDirectX11>(GetCurrentRenderer())->CreateTexture(width, height, pixels);

			if (tex) {
				auto result = GetRenderers<SireDirectX11>(GetCurrentRenderer())->CreateShaderResourceView(tex);

				if (result)
					out->Set(width, height, 0, reinterpret_cast<intptr_t*>(result), reinterpret_cast<intptr_t*>(tex));
			}
		} break;
#endif
#ifdef SIRE_INCLUDE_DX12
		case SIRE_RENDERER_DX12:
			break;
#endif
#ifdef SIRE_INCLUDE_OPENGL
		case SIRE_RENDERER_OPENGL: {
		} break;
#endif
		}

		return out;
	}

	static inline void SetViewport(float x, float y, float w, float h) {
		if (!IsRendererActive())
			return;

		shared.viewport.x = x;
		shared.viewport.y = y;
		shared.viewport.w = w;
		shared.viewport.h = h;

		return GetRenderers(GetCurrentRenderer())->SetViewport(shared.viewport);
	}

	static inline void CopyResource(SirePtr<tSireTexture2D> const& dst, SirePtr<tSireTexture2D> const& src) {
		if (!IsRendererActive())
			return;

		if (!src || !dst)
			return;

		dst->w = src->w;
		dst->h = src->h;
		dst->format = src->format;
		dst->swapColors = src->swapColors;

		return GetRenderers(GetCurrentRenderer())->CopyResource(dst->ptrs.surface, src->ptrs.surface);
	}

	static inline void SetProjectionMode(eSireProjection proj) {
		if (!IsRendererActive())
			return;

		switch (proj) {
		case SIRE_PROJ_NONE:
			cb.matrix.Identity();
			break;
		case SIRE_PROJ_ORTHOGRAPHIC:
			cb.matrix.Orthographic(shared.viewport.x, shared.viewport.y, shared.viewport.w, shared.viewport.h, shared.nearPlane, shared.farPlane);
			break;
		case SIRE_PROJ_PERSPECTIVE:
			cb.matrix.Perspective(shared.fov, shared.viewport.w / shared.viewport.h, shared.nearPlane, shared.farPlane);
			break;
		}
	}

	static inline void SetTexture(SirePtr<tSireTexture2D> const& tex, SirePtr<tSireTexture2D> const& mask) {
		if (!IsRendererActive())
			return;

		intptr_t* tex0 = nullptr;
		intptr_t* tex1 = nullptr;

		if (tex) {
			tex0 = tex->ptrs.texture;
			cb.swapColors = tex->swapColors;
		}

		if (mask)
			tex1 = mask->ptrs.texture;

		return GetRenderers(GetCurrentRenderer())->SetTexture(tex0, tex1);
	}

	static inline void DrawRect(tSireFloat4 const& rect) {
		if (!IsRendererActive())
			return;

		Sire::Begin(SIRE_TRIANGLE);
		Sire::SetTexCoords2f(0.0f, 0.0f);
		Sire::SetVertex2f(rect.x, rect.y);

		Sire::SetTexCoords2f(1.0f, 0.0f);
		Sire::SetVertex2f(rect.z, rect.y);

		Sire::SetTexCoords2f(1.0f, 1.0f);
		Sire::SetVertex2f(rect.z, rect.w);


		Sire::SetTexCoords2f(0.0f, 0.0f);
		Sire::SetVertex2f(rect.x, rect.y);

		Sire::SetTexCoords2f(1.0f, 1.0f);
		Sire::SetVertex2f(rect.z, rect.w);

		Sire::SetTexCoords2f(0.0f, 1.0f);
		Sire::SetVertex2f(rect.x, rect.w);

		Sire::End();
	}
};
