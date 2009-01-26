#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

LPDIRECT3DTEXTURE9 GgafDx9TextureManager::_pTexture_First = NULL;

LPDIRECT3DTEXTURE9 GgafDx9TextureManager::find(string prm_texture_file_name) {
	LPDIRECT3DTEXTURE9 pTexture_Current = _pTexture_First;
	while (pTexture_Current != NULL) {
		if (pTexture_Current->_texture_name == prm_texture_file_name) {
			return pTexture_Current;
		}
		pTexture_Current = pTexture_Current -> _pTexture_Next;
	}
	return NULL;
}

void GgafDx9TextureManager::add(LPDIRECT3DTEXTURE9 prm_pTexture_New) {
	if (_pTexture_First == NULL) {
		_pTexture_First = prm_pTexture_New;
		return;
	} else {
		LPDIRECT3DTEXTURE9 pTexture_Current = _pTexture_First;
		while (pTexture_Current -> _pTexture_Next != NULL) {
			pTexture_Current = pTexture_Current -> _pTexture_Next;
		}
		pTexture_Current -> _pTexture_Next = prm_pTexture_New;
		return;
	}
}

void GgafDx9TextureManager::clear() {
	//保持しているGgafDx9Textureインスタンスを解放
	LPDIRECT3DTEXTURE9 pTexture_Current = _pTexture_First;
	while (pTexture_Current != NULL) {
		LPDIRECT3DTEXTURE9 pTexture_tmp = pTexture_Current -> _pTexture_Next;
		if (pTexture_tmp == NULL) {
			RELEASE_POSSIBLE_NULL(pTexture_Current);
			pTexture_Current = NULL;
			break;
		} else {
			RELEASE_POSSIBLE_NULL(pTexture_Current);
			pTexture_Current = pTexture_tmp;
		}
	}
}

LPDIRECT3DTEXTURE9 GgafDx9TextureManager::get(string prm_texture_file_name) {
	LPDIRECT3DTEXTURE9 pTexture = GgafDx9TextureManager::find(prm_texture_file_name);
	//未生成ならば生成
	if (pTexture == NULL) {
		string texture_file_name = GGAFDX9_PROPERTY(DIR_TEXTURE) + string(paD3DMaterial9_tmp[i].pTextureFilename);
		LPDIRECT3DTEXTURE9 pTexture_New;
		hr = D3DXCreateTextureFromFileEx(
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
				&pTexture_New                // [out] LPDIRECT3DTEXTURE9 *ppTexture
			 );
		if(hr != D3D_OK) {
			throw_GgafDx9CriticalException("[GgafDx9MeshModelManager::load] D3DXCreateTextureFromFile失敗。対象="<<xfile_name, hr);
		}

		//LPDIRECT3DTEXTURE9 pTexture_New = GgafDx9Sound::createTexture(prm_texture_file_name);
		GgafDx9TextureManager::add(pTexture_New);
		return pTexture_New;
	} else {
		return pTexture;
	}
}

