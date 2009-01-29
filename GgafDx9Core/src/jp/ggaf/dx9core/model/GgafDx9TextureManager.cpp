#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TextureManager::GgafDx9TextureManager(string prm_name)
    : GgafResourceManager<IDirect3DTexture9>(prm_name) {
}

IDirect3DTexture9* GgafDx9TextureManager::processCreateResource(std::string prm_resource_idstr) {
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
			&pIDirect3DTexture9_New                // [out] GgafDx9TextureConnection* *ppTexture
		 );
	if(hr != D3D_OK) {
		throw_GgafDx9CriticalException("[GgafDx9TextureManager::createResource] D3DXCreateTextureFromFileExé∏îsÅBëŒè€="<<prm_resource_idstr, hr);
	}
	return pIDirect3DTexture9_New;
}

GgafResourceConnection<IDirect3DTexture9>* GgafDx9TextureManager::processCreateConnection(std::string prm_resource_idstr, IDirect3DTexture9* prm_pResource) {
	_TRACE_(" GgafDx9TextureManager::processCreateConnection "<<prm_resource_idstr<<" Çê∂ê¨ÇµÇ‹ÇµÇΩÅB");
	GgafDx9TextureConnection* p = NEW GgafDx9TextureConnection(prm_resource_idstr, prm_pResource);
	return p;
}



GgafDx9TextureManager::~GgafDx9TextureManager(){};
