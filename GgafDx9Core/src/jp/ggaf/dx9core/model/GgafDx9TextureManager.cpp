#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Texture* GgafDx9TextureManager::_pTexture_First = NULL;

GgafDx9Texture* GgafDx9TextureManager::find(string prm_texture_file_name) {
	GgafDx9Texture* pTexture_Current = _pTexture_First;
	while (pTexture_Current != NULL) {
		if (pTexture_Current->_texture_file_name == prm_texture_file_name) {
			return pTexture_Current;
		}
		pTexture_Current = pTexture_Current -> _pTexture_Next;
	}
	return NULL;
}

void GgafDx9TextureManager::add(GgafDx9Texture* prm_pTexture_New) {
	if (_pTexture_First == NULL) {
		_pTexture_First = prm_pTexture_New;
		return;
	} else {
		GgafDx9Texture* pTexture_Current = _pTexture_First;
		while (pTexture_Current -> _pTexture_Next != NULL) {
			pTexture_Current = pTexture_Current -> _pTexture_Next;
		}
		pTexture_Current -> _pTexture_Next = prm_pTexture_New;
		return;
	}
}
void GgafDx9TextureManager::remove(GgafDx9Texture* prm_pTexture) {
	if (prm_pTexture == NULL) {
		_TRACE_("GgafDx9TextureManager::remove 引数 prm_pTexture は NULLです");
		return;
	}
	static GgafDx9Texture* pTexture_Current;
	static GgafDx9Texture* pTexture_Prev;
	pTexture_Current = _pTexture_First;
	pTexture_Prev    = NULL;
	while (pTexture_Current != NULL) {
		if (pTexture_Current == prm_pTexture) { //発見
			_TRACE_("GgafDx9TextureManager::remove["<<pTexture_Current->_texture_file_name<<"]");
			if (prm_pTexture->_pTexture_Next == NULL) {
				//末尾だった
				if (pTexture_Prev == NULL) {
					//末尾で先頭だった（＝最後の一つ）
					_pTexture_First = NULL;
				} else {
					//末尾で先頭でなかった
					pTexture_Prev->_pTexture_Next = NULL;
				}
			} else {
				//末尾でない
				if (pTexture_Prev == NULL) {
					//先頭だった
					_pTexture_First = pTexture_Current->_pTexture_Next; //先頭を次にずらす
				} else {
					//末尾でも先頭でもない（中間）
					pTexture_Prev->_pTexture_Next = pTexture_Current->_pTexture_Next; //両隣を繋げる
				}
			}
			//ハイそれではさようなら
			pTexture_Current->release();
			DELETE_IMPOSSIBLE_NULL(pTexture_Current);
			return;
		}
		pTexture_Prev = pTexture_Current;
		pTexture_Current = pTexture_Current -> _pTexture_Next;
	}
	_TRACE_("GgafDx9TextureManager::remove prm_pTexture["<<pTexture_Current->_texture_file_name<<"]は既にありません。意図しとっと？");
}
void GgafDx9TextureManager::release() {
	//保持しているGgafDx9Textureインスタンスを解放
	GgafDx9Texture* pTexture_Current = _pTexture_First;
	if (_pTexture_First == NULL) {
		_TRACE_("GgafDx9TextureManager::clear() 解放するテクスチャはありませんでした。意図どうりですか？");
	} else {
		while (pTexture_Current != NULL) {
			GgafDx9Texture* pTexture_tmp = pTexture_Current -> _pTexture_Next;
			if (pTexture_tmp == NULL) {
				pTexture_tmp->release();
				DELETE_IMPOSSIBLE_NULL(pTexture_tmp);
				pTexture_Current = NULL;
				break;
			} else {
				pTexture_tmp->release();
				DELETE_IMPOSSIBLE_NULL(pTexture_tmp);
				pTexture_Current = pTexture_tmp;
			}
		}
	}
}

GgafDx9Texture* GgafDx9TextureManager::obtain(string prm_texture_file_name) {
	GgafDx9Texture* pTexture = GgafDx9TextureManager::find(prm_texture_file_name);
	//未生成ならば生成
	if (pTexture == NULL) {
		string texture_file_name = GGAFDX9_PROPERTY(DIR_TEXTURE) + string(prm_texture_file_name);
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
				&pIDirect3DTexture9_New                // [out] GgafDx9Texture* *ppTexture
			 );
		if(hr != D3D_OK) {
			throw_GgafDx9CriticalException("[GgafDx9MeshModelManager::load] D3DXCreateTextureFromFile失敗。対象="<<prm_texture_file_name, hr);
		}
		pTexture = NEW GgafDx9Texture(prm_texture_file_name, pIDirect3DTexture9_New);
		//GgafDx9Texture* pTexture_New = GgafDx9Sound::createTexture(prm_texture_file_name);
		GgafDx9TextureManager::add(pTexture);
		pTexture->_iRefModelNum = 1;
		return pTexture;
	} else {
		pTexture->_iRefModelNum++;
		return pTexture;
	}
}

