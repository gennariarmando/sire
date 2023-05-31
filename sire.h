#pragma once
#define SIRE_INCLUDE_DX9
//#define SIRE_INCLUDE_DX10
#define SIRE_INCLUDE_DX11
#define SIRE_INCLUDE_DX12
#define SIRE_INCLUDE_OPENGL

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

#ifdef SIRE_INCLUDE_OPENGL
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#endif

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
		SIRE_RENDERER_DX9,
		SIRE_RENDERER_DX10,
		SIRE_RENDERER_DX11,
		SIRE_RENDERER_DX12,
		SIRE_RENDERER_OPENGL,
		SIRE_RENDERER_VULKAN,
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

		struct tSirePtrsHolder {
			intptr_t* texture;
			intptr_t* surface;

			tSirePtrsHolder() {
				texture = nullptr;
				surface = nullptr;
			}

			~tSirePtrsHolder() {
				Release();
			}

			void Release() {
				switch (GetCurrentRenderer()) {
				case SIRE_RENDERER_DX9:
					Sire::Release((IDirect3DTexture9*)texture);
					Sire::Release((IDirect3DSurface9*)surface);
					break;
				case SIRE_RENDERER_DX11:
					Sire::Release((ID3D11ShaderResourceView*)texture);
					Sire::Release((ID3D11Texture2D*)surface);
					break;
				case SIRE_RENDERER_OPENGL:
					if (texture) {
						glDeleteTextures(1, (uint32_t*)texture);
						delete texture;
					}
					break;
				}

				texture = nullptr;
				surface = nullptr;
			}
		};
		std::unique_ptr<tSirePtrsHolder> ptrs;

		tSireTexture2D() {
			w = 0;
			h = 0;
			format = 0;
			ptrs = std::make_unique<tSirePtrsHolder>();
		}

		void Set(int32_t width, int32_t height, int32_t format, intptr_t* tex, intptr_t* surf) {
			this->w = width;
			this->h = height;
			this->format = format;
			this->ptrs->texture = tex;
			this->ptrs->surface = surf;
		}

		void Release() {
			delete this;
		}
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

		std::array<GLfloat, 16> ToFloatArray() {
			std::array<GLfloat, 16> out = {};

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

		SireRenderer() {
			initialised = false;
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
			if (!initialised || !dev)
				return false;

			D3DCAPS9 caps = {};
			HRESULT hr = dev->GetDeviceCaps(&caps);

			if (SUCCEEDED(hr)) {
				hr = dev->TestCooperativeLevel();
				return hr == D3D_OK;
			}

			return false;
		}

		void Init(intptr_t* d) override {
			if (initialised)
				return;

			dev = reinterpret_cast<IDirect3DDevice9*>(d);

			dev->CreateVertexBuffer(sizeof(tVertexLegacy) * 65536, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
				0, D3DPOOL_DEFAULT, &vb, nullptr);

			dev->CreateIndexBuffer(sizeof(tVertexLegacy) * 65536, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
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

			dev->DrawIndexedPrimitive(type, 0, 0, verticesLegacy.size(), 0, numIndices / 3);

			if (stateBlock) {
				stateBlock->Apply();
				Release(stateBlock);
				stateBlock = nullptr;
			}
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

		uint8_t* Lock(IDirect3DTexture9* texture) {
			D3DLOCKED_RECT out;
			texture->LockRect(0, &out, nullptr, 0);
			return (uint8_t*)out.pBits;
		}

		void Unlock(IDirect3DTexture9* texture) {
			texture->UnlockRect(0);
		}

		uint8_t* Lock(IDirect3DSurface9* surface) {
			D3DLOCKED_RECT out;
			surface->LockRect(&out, nullptr, 0);
			return (uint8_t*)out.pBits;
		}

		void Unlock(IDirect3DSurface9* surface) {
			surface->UnlockRect();
		}

		ID3DXBuffer* CompileShader(const std::string& str, const char* szEntrypoint, const char* szTarget) {
			ID3DXBuffer* out;
			ID3DXBuffer* outerr;
			HRESULT hr = D3DXCompileShader(str.c_str(), str.size(), NULL, NULL, szEntrypoint, szTarget, 0, &out, &outerr, NULL);
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
			if (!initialised || !swapchain || !dev || !devcon)
				return false;

			DXGI_SWAP_CHAIN_DESC desc;
			HRESULT hr = swapchain->GetDesc(&desc);

			return SUCCEEDED(hr) && desc.BufferCount > 0;
		}

		void Init(intptr_t* ptr) override {
			if (initialised)
				return;

			swapchain = reinterpret_cast<IDXGISwapChain*>(ptr);
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
			ID3DBlob* VS = CompileShader(hlslShader5_0, "VShader", "vs_5_0");
			ID3DBlob* PS = CompileShader(hlslShader5_0, "PShader", "ps_5_0");

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

			devcon->IASetInputLayout(inputLayout);

			auto renderTarget = GetRenderTarget();
			devcon->OMSetRenderTargets(1, &renderTarget, nullptr);

			devcon->VSSetShader(vertexShader, nullptr, 0);
			devcon->PSSetShader(pixelShader, nullptr, 0);

			devcon->VSSetConstantBuffers(0, 1, &pb);
			devcon->PSSetConstantBuffers(0, 1, &pb);

			// Set textures
			devcon->VSSetShaderResources(0, 1, &tex);
			devcon->VSSetShaderResources(1, 1, &mask);

			devcon->PSSetShaderResources(0, 1, &tex);
			devcon->PSSetShaderResources(1, 1, &mask);

			devcon->PSSetSamplers(0, 1, &ss);
			devcon->GSSetSamplers(0, 1, &ss);

			// Set index/vertex buffers
			UINT stride = sizeof(tVertex);
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
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
			devcon->IASetPrimitiveTopology(type);

			// Draw
			devcon->DrawIndexed(numIndices, 0, 0);

			Release(renderTarget);

			if (rasterizerState) {
				devcon->RSSetState(rasterizerState);
				Release(rasterizerState);
				depthStencilState = nullptr;
			}

			if (depthStencilState) {
				devcon->OMSetDepthStencilState(depthStencilState, stencilRef);
				Release(depthStencilState);
				depthStencilState = nullptr;
			}

			if (blendState) {
				devcon->OMSetBlendState(blendState, blendFactor, sampleMask);
				Release(blendState);
				blendState = nullptr;
			}
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

		void SetViewport(tSireViewport const& v) {
			D3D11_VIEWPORT vp = {};
			vp.TopLeftX = v.x;
			vp.TopLeftY = v.y;
			vp.Width = v.w;
			vp.Height = v.h;
			vp.MinDepth = v.mind;
			vp.MaxDepth = v.maxd;
			devcon->RSSetViewports(1, &vp);
		}

		void SetTexture(intptr_t* texture, intptr_t* textureMask) {
			cb.hasTex = texture ? true : false;
			cb.hasMask = textureMask ? true : false;

			tex = nullptr;
			mask = nullptr;

			if (texture)
				tex = reinterpret_cast<ID3D11ShaderResourceView*>(texture);

			if (textureMask)
				mask = reinterpret_cast<ID3D11ShaderResourceView*>(textureMask);
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
			ID3D11Texture2D* out;
			swapchain->GetBuffer(buffer, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&out));
			return out;
		}

		D3D11_TEXTURE2D_DESC GetDesc(ID3D11Texture2D* texture) {
			D3D11_TEXTURE2D_DESC out = {};
			texture->GetDesc(&out);
			return out;
		}

		uint8_t* Lock(ID3D11Texture2D* texture) {
			D3D11_MAPPED_SUBRESOURCE map;
			devcon->Map(texture, 0, D3D11_MAP_READ, 0, &map);
			return (uint8_t*)map.pData;
		}

		void Unlock(ID3D11Texture2D* texture) {
			devcon->Unmap(texture, 0);
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

		ID3D11VertexShader* CreateVertexShader(const void* buffer, uint32_t size) {
			ID3D11VertexShader* out = nullptr;
			dev->CreateVertexShader(buffer, size, NULL, &out);
			return out;
		}

		ID3D11PixelShader* CreatePixelShader(const void* buffer, uint32_t size) {
			ID3D11PixelShader* out = nullptr;
			dev->CreatePixelShader(buffer, size, NULL, &out);
			return out;
		}

		ID3D11InputLayout* CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>* layout, const void* buffer, uint32_t size) {
			ID3D11InputLayout* out = nullptr;
			dev->CreateInputLayout(layout->data(), layout->size(), buffer, size, &out);
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

			dev->CreateTexture2D(&desc, nullptr, &out);

			if (pixels) {
				D3D11_TEXTURE2D_DESC desc;
				out->GetDesc(&desc);
				devcon->UpdateSubresource(out, 0, nullptr, pixels, desc.Width * sizeof(UINT), 0);
			}

			return out;
		}

	};

	struct SireDirectX12 : SireRenderer {

	};

	struct SireOpenGL : SireRenderer {
		HDC con;
		HGLRC conres;
		uint32_t tex;
		uint32_t mask;

		SireOpenGL() : SireRenderer() {
			con = nullptr;
			conres = nullptr;
			tex = 0;
			mask = 0;
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
			initialised = true;
		}

		void Shutdown() override {
			if (!initialised)
				return;

			con = nullptr;
			tex = 0;
			mask = 0;

			if (conres) {
				wglDeleteContext(conres);
				conres = nullptr;
			}

			initialised = false;
		}

		void Begin() override {

		}

		void End() override {
			auto prevconres = wglGetCurrentContext();
			wglMakeCurrent(con, conres);

			glPushAttrib(GL_ALL_ATTRIB_BITS);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();

			glLoadIdentity();

			tConstBuff tempcb = cb;
			tempcb.matrix.Transpose();
			glLoadMatrixf(&tempcb.matrix.ToFloatArray()[0]);

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(3, GL_FLOAT, sizeof(tVertex), &vertices[0].pos);
			glColorPointer(4, GL_FLOAT, sizeof(tVertex), &vertices[0].col);
			glTexCoordPointer(2, GL_FLOAT, sizeof(tVertex), &vertices[0].uv0);
			glTexCoordPointer(2, GL_FLOAT, sizeof(tVertex), &vertices[0].uv1);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex);
			glBindTexture(GL_TEXTURE_2D, mask);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glEnable(GL_TEXTURE_2D);

			int32_t type = GL_POINTS;
			switch (primitiveType) {
			case SIRE_LINE:
				type = GL_LINES;
				break;
			case SIRE_POINT:
				type = GL_POINTS;
				break;
			case SIRE_TRIANGLE:
				type = GL_TRIANGLES;
				break;
			}

			glDrawElements(type, numIndices, GL_UNSIGNED_SHORT, &indices[0]);

			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);

			glPopMatrix();
			glPopAttrib();

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
			glDisable(GL_LIGHTING);
			glDisable(GL_COLOR_MATERIAL);
			glEnable(GL_SCISSOR_TEST);

			glPolygonMode(GL_FRONT_AND_BACK, SireFillMode(s.fillMode));
			glShadeModel(GL_SMOOTH);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}

		void SetViewport(tSireViewport const& v) override {
			glViewport(static_cast<int32_t>(v.x), static_cast<int32_t>(v.y), static_cast<int32_t>(v.w), static_cast<int32_t>(v.h));
		}

		void CopyResource(intptr_t* dst, intptr_t* src) override {

		}

		void SetTexture(intptr_t* texture, intptr_t* textureMask) override {
			tex = texture ? *texture : 0;
			mask = textureMask ? *textureMask : 0;
		}

		// End virtual override
		uint32_t SireFillMode(int8_t mode) {
			switch (mode) {
			case SIRE_FILL_WIREFRAME:
				return GL_LINE;
			case SIRE_FILL_SOLID:
				return GL_FILL;
			}
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
			//case SIRE_BLEND_BLEND_FACTOR:
			//	return GL_CONSTANT_COLOR;
			//case SIRE_BLEND_INV_BLEND_FACTOR:
			//	return GL_ONE_MINUS_CONSTANT_COLOR;
			//case SIRE_BLEND_SRC1_COLOR:
			//	return GL_SRC1_COLOR;
			//case SIRE_BLEND_INV_SRC1_COLOR:
			//	return GL_ONE_MINUS_SRC1_COLOR;
			//case SIRE_BLEND_SRC1_ALPHA:
			//	return GL_SRC1_ALPHA;
			//case SIRE_BLEND_INV_SRC1_ALPHA:
			//	return GL_ONE_MINUS_SRC1_ALPHA;
			}
		}

		tSireTexture2D GetBackBuffer(uint32_t buffer) {
			HDC hdc = wglGetCurrentDC();

			RECT windowRect;
			GetClientRect(WindowFromDC(hdc), &windowRect);

			tSireTexture2D out = {};
			out.w = windowRect.right - windowRect.left;
			out.h = windowRect.bottom - windowRect.top;

			return out;
		}

		uint32_t* CreateTexture(int32_t width, int32_t height, uint8_t* pixels) {
			uint32_t* out = new uint32_t;
			glGenTextures(1, out);
			glBindTexture(GL_TEXTURE_2D, *out);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			return out;
		}

		void CopyResources() {

		}
	};

	struct SireVulkan : SireRenderer {


	};


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

	static inline std::string hlslShader2_0 = R"(
	matrix proj;
	int hasTex;
	int hasMask;
	
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
	    
	    return c;
	}
	)";

	static inline std::string hlslShader5_0 = R"(
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
	static inline eSireRenderer const GetCurrentRenderer() {
		return currentRenderer;
	}

	template <typename T = SireRenderer>
	static inline T* const GetRenderers(eSireRenderer re) {
		return reinterpret_cast<T*>(renderers.at(re));
	}

	static inline bool IsRendererActive() {
		return GetRenderers(GetCurrentRenderer())->IsRendererActive();
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

			numIndices = indices.size();
		}

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

		tVertex v;
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

		return GetRenderers(GetCurrentRenderer())->SetRenderStates(shared.renderStates);
	}

	template <typename T>
	static inline void Init(eSireRenderer re, T* ptr) {
		if (currentRenderer != SIRE_RENDERER_NULL)
			return;

		if (!renderersInitialised) {
			if (!renderers.at(re)) {
				SireRenderer* renderer = nullptr;

				switch (re) {
				case SIRE_RENDERER_NULL:
					break;
				case SIRE_RENDERER_DX9:
					renderer = new SireDirectX9();
					break;
				case SIRE_RENDERER_DX10:
					renderer = new SireDirectX10();
					break;
				case SIRE_RENDERER_DX11:
					renderer = new SireDirectX11();
					break;
				case SIRE_RENDERER_DX12:
					renderer = new SireDirectX12();
					break;
				case SIRE_RENDERER_OPENGL:
					renderer = new SireOpenGL();
					break;
				case SIRE_RENDERER_VULKAN:
					renderer = new SireVulkan();
					break;
				}

				renderers.at(re) = renderer;
			}
			renderersInitialised = true;
		}

		currentRenderer = re;
		currentRendererMainPtr = (intptr_t*)ptr;

		return GetRenderers(GetCurrentRenderer())->Init(currentRendererMainPtr);
	}

	static inline void Shutdown() {
		if (currentRenderer == SIRE_RENDERER_NULL)
			return;

		GetRenderers(GetCurrentRenderer())->Shutdown();

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
	static inline void Release(T* res) {
		if (res) {
			res->Release();
			res = nullptr;
		}
	}

	static inline tSireTexture2D* GetBackBuffer(uint32_t buffer) {
		if (!IsRendererActive())
			return nullptr;

		tSireTexture2D* out = new tSireTexture2D();

		switch (GetCurrentRenderer()) {
		case SIRE_RENDERER_DX9: {
			auto result = GetRenderers<SireDirectX9>(GetCurrentRenderer())->GetBackBufferSurface(buffer);
			auto desc = GetRenderers<SireDirectX9>(GetCurrentRenderer())->GetDesc(result);
			out->Set(desc.Width, desc.Height, desc.Format, nullptr, reinterpret_cast<intptr_t*>(result));
		} break;
		case SIRE_RENDERER_DX10:
			break;
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
		case SIRE_RENDERER_DX12:
			break;
		case SIRE_RENDERER_OPENGL: {
			auto result = GetRenderers<SireOpenGL>(GetCurrentRenderer())->GetBackBuffer(buffer);
			out->Set(result.w, result.h, result.format, reinterpret_cast<intptr_t*>(result.ptrs->texture), reinterpret_cast<intptr_t*>(result.ptrs->texture));
		} break;
		}

		return out;
	}

	static inline tSireTexture2D* CreateTexture(int32_t width, int32_t height, uint8_t* pixels) {
		if (!IsRendererActive())
			return nullptr;

		tSireTexture2D* out = new tSireTexture2D();

		switch (GetCurrentRenderer()) {
		case SIRE_RENDERER_DX9: {
			IDirect3DSurface9* sout = nullptr;
			auto result = GetRenderers<SireDirectX9>(GetCurrentRenderer())->CreateTexture(width, height, pixels, &sout);

			if (result)
				out->Set(width, height, 0, reinterpret_cast<intptr_t*>(result), reinterpret_cast<intptr_t*>(sout));
		} break;
		case SIRE_RENDERER_DX10:
			break;
		case SIRE_RENDERER_DX11: {
			auto tex = GetRenderers<SireDirectX11>(GetCurrentRenderer())->CreateTexture(width, height, pixels);

			if (tex) {
				auto result = GetRenderers<SireDirectX11>(GetCurrentRenderer())->CreateShaderResourceView(tex);

				if (result)
					out->Set(width, height, 0, reinterpret_cast<intptr_t*>(result), reinterpret_cast<intptr_t*>(tex));
			}
		} break;
		case SIRE_RENDERER_DX12:
			break;
		case SIRE_RENDERER_OPENGL:
			auto result = GetRenderers<SireOpenGL>(GetCurrentRenderer())->CreateTexture(width, height, pixels);

			if (result)
				out->Set(width, height, 0, reinterpret_cast<intptr_t*>(result), reinterpret_cast<intptr_t*>(result));
			break;
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

	static inline void CopyResource(tSireTexture2D* dst, tSireTexture2D* src) {
		if (!IsRendererActive())
			return;

		dst->w = src->w;
		dst->h = src->h;
		dst->format = src->format;

		return GetRenderers(GetCurrentRenderer())->CopyResource(dst->ptrs->surface, src->ptrs->surface);
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

	static inline void SetTexture(tSireTexture2D* tex, tSireTexture2D* mask) {
		if (!IsRendererActive())
			return;

		intptr_t* tex0 = nullptr;
		intptr_t* tex1 = nullptr;

		if (tex)
			tex0 = tex->ptrs->texture;

		if (mask)
			tex1 = mask->ptrs->texture;

		return GetRenderers(GetCurrentRenderer())->SetTexture(tex0, tex1);
	}

	static inline void DrawRect(tSireFloat4 const& rect) {
		if (!IsRendererActive())
			return;

		Sire::Begin(SIRE_TRIANGLE);
		Sire::SetVertex2f(rect.x, rect.y);
		Sire::SetVertex2f(rect.z, rect.y);
		Sire::SetVertex2f(rect.z, rect.w);

		Sire::SetVertex2f(rect.x, rect.y);
		Sire::SetVertex2f(rect.z, rect.w);
		Sire::SetVertex2f(rect.x, rect.w);
		Sire::End();
	}
};
