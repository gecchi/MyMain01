#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TextureManager::GgafDx9TextureManager(const char* prm_manager_name) :
    GgafResourceManager<IDirect3DTexture9> (prm_manager_name) {
}

IDirect3DTexture9* GgafDx9TextureManager::processCreateResource(char* prm_idstr) {

    string texture_file_name = GGAFDX9_PROPERTY(DIR_TEXTURE) + string(prm_idstr);
    LPDIRECT3DTEXTURE9 pResourceTexture;
    HRESULT hr = D3DXCreateTextureFromFileEx(
                     GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice,
                     texture_file_name.c_str(), // [in] LPCTSTR pSrcFile,
                     D3DX_DEFAULT,              // [in] UINT Width,
                     D3DX_DEFAULT,              // [in] UINT Height,
                     D3DX_DEFAULT,              // [in] UINT MipLevels,
                     0,                         // [in] DWORD Usage,
                     D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
                     D3DPOOL_MANAGED,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                     D3DX_FILTER_POINT,         // [in] DWORD Filter, D3DX_FILTER_POINTでボヤケナイ
                     D3DX_DEFAULT,              // [in] DWORD MipFilter,
                     0,                         // [in] D3DCOLOR ColorKey,
                     NULL,                      // [in] D3DXIMAGE_INFO *pSrcInfo,
                     NULL,                      // [in] PALETTEENTRY *pPalette,
                     &pResourceTexture    // [out] GgafDx9TextureConnection* *ppTextureCon
                );
    if (hr != D3D_OK) {
        _TRACE_("[GgafDx9TextureManager::createResource] D3DXCreateTextureFromFileEx失敗。対象="<<prm_idstr);
        //失敗用テクスチャを設定
        string texture_file_name2 = GGAFDX9_PROPERTY(DIR_TEXTURE) + "GgafDx9IlligalTexture.png";
        HRESULT hr2 = D3DXCreateTextureFromFileEx(
                         GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice,
                         texture_file_name2.c_str(),// [in] LPCTSTR pSrcFile,
                         D3DX_DEFAULT,              // [in] UINT Width,
                         D3DX_DEFAULT,              // [in] UINT Height,
                         D3DX_DEFAULT,              // [in] UINT MipLevels,
                         0,                         // [in] DWORD Usage,
                         D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
                         D3DPOOL_MANAGED,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                         D3DX_FILTER_POINT,         // [in] DWORD Filter, D3DX_FILTER_POINTでボヤケナイ
                         D3DX_DEFAULT,              // [in] DWORD MipFilter,
                         0,                         // [in] D3DCOLOR ColorKey,
                         NULL,                      // [in] D3DXIMAGE_INFO *pSrcInfo,
                         NULL,                      // [in] PALETTEENTRY *pPalette,
                         &pResourceTexture    // [out] GgafDx9TextureConnection* *ppTextureCon
                      );
        mightDx9Exception(hr2, D3D_OK, "[GgafDx9TextureManager::createResource] D3DXCreateTextureFromFileEx失敗。対象="<<prm_idstr);
    }

    Sleep(2); //工場に気を使う。
    TRACE3(" GgafDx9TextureManager::processCreateResource "<<prm_idstr<<" のテクスチャ生成しました。");
    return pResourceTexture;
}

GgafResourceConnection<IDirect3DTexture9>* GgafDx9TextureManager::processCreateConnection(char* prm_idstr, IDirect3DTexture9* prm_pResource) {
    TRACE3(" GgafDx9TextureManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDx9TextureConnection* pConnection = NEW GgafDx9TextureConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9TextureManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}

