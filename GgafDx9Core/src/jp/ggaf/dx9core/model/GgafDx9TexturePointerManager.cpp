#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TexturePointerManager::GgafDx9TexturePointerManager(string prm_name) : GgafResourcePointerManager<IDirect3DTexture9>(prm_name) {
}

IDirect3DTexture9* GgafDx9TexturePointerManager::processCreateResource(std::string prm_resource_idstr) {
	string texture_file_name = GGAFDX9_PROPERTY(DIR_TEXTURE) + string(prm_resource_idstr);
	LPDIRECT3DTEXTURE9 pIDirect3DTexture9_New;
	HRESULT hr = D3DXCreateTextureFromFileEx(
			GgafDx9God::_pID3DDevice9,   // [in] LPDIRECT3DDEVICE9 pDevice,
			texture_file_name.c_str(),    // [in] LPCTSTR pSrcFile,
			D3DX_DEFAULT,                // [in] UINT Width,
			D3DX_DEFAULT,                // [in] UINT Height,
			D3DX_DEFAULT,                // [in] UINT MipLevels,
			0,                           // [in] DWORD Usage,
			D3DFMT_UNKNOWN,              // [in] D3DFORMAT Format,
			D3DPOOL_MANAGED,             // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
			D3DX_DEFAULT,                // [in] DWORD Filter,
			D3DX_DEFAULT,                // [in] DWORD MipFilter,
			0,                           // [in] D3DCOLOR ColorKey,
			NULL,                        // [in] D3DXIMAGE_INFO *pSrcInfo,
			NULL,                        // [in] PALETTEENTRY *pPalette,
			&pIDirect3DTexture9_New                // [out] GgafDx9TexturePointer* *ppTexture
		 );
	if(hr != D3D_OK) {
		throw_GgafDx9CriticalException("[GgafDx9TexturePointerManager::createResource] D3DXCreateTextureFromFileExé∏îsÅBëŒè€="<<prm_resource_idstr, hr);
	}
	return pIDirect3DTexture9_New;
}

GgafResourcePointer<IDirect3DTexture9>* GgafDx9TexturePointerManager::createResourcePointer(std::string prm_resource_idstr, IDirect3DTexture9* prm_pResource) {
	GgafDx9TexturePointer* p = NEW GgafDx9TexturePointer(prm_resource_idstr, prm_pResource);
	return p;
}

void GgafDx9TexturePointerManager::processReleaseResource(IDirect3DTexture9* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}



GgafDx9TexturePointerManager::~GgafDx9TexturePointerManager(){};
