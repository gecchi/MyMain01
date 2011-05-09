#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Texture::GgafDx9Texture(char* prm_texture_name) : GgafObject() {
    TRACE("GgafDx9Texture::GgafDx9Texture(" << prm_texture_name << ")");
    _pIDirect3DBaseTexture9 = NULL;
    _pD3DXIMAGE_INFO = NEW D3DXIMAGE_INFO();

    _texture_name = NEW char[51];
    strcpy(_texture_name, prm_texture_name);
    string texture_name = string(_texture_name);
    string texture_file_name = PROPERTY(DIR_TEXTURE) + texture_name;

    //テクスチャファイル名に "cubemap" 或いは "CubeMap" が含まれていれば、環境マップテクスチャとみなす
    if (texture_name.find("cubemap") == string::npos && texture_name.find("CubeMap") == string::npos) {
        //通常の２Dテクスチャの場合
        LPDIRECT3DTEXTURE9 pIDirect3DTexture9;
        HRESULT hr = D3DXCreateTextureFromFileEx(
                         GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice,
                         texture_file_name.c_str(), // [in] LPCTSTR pSrcFile,
                         D3DX_DEFAULT,              // [in] UINT Width,
                         D3DX_DEFAULT,              // [in] UINT Height,
                         0,                         // [in] UINT MipLevels,  //D3DX_DEFAULT,
                         0,                         // [in] DWORD Usage,
                         D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
                         D3DPOOL_DEFAULT,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                         D3DX_DEFAULT,              // [in] DWORD Filter, D3DX_FILTER_POINTでボヤケナイ. D3DX_FILTER_LINEAR
                         D3DX_DEFAULT,              // [in] DWORD MipFilter,
                         0,                         // [in] D3DCOLOR ColorKey,
                         _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO *pSrcInfo,
                         NULL,                      // [in] PALETTEENTRY *pPalette,
                         &pIDirect3DTexture9        // [out] LPDIRECT3DTEXTURE9* ppTexture
                    );
        if (hr != D3D_OK) {
            _TRACE_("[GgafDx9TextureManager::createResource] D3DXCreateTextureFromFileEx失敗。対象="<<prm_texture_name);
            //失敗用テクスチャ"GgafDx9IlligalTexture.png"を設定
            string texture_file_name2 = PROPERTY(DIR_TEXTURE) + "GgafDx9IlligalTexture.png";
            HRESULT hr2 = D3DXCreateTextureFromFileEx(
                             GgafDx9God::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice,
                             texture_file_name2.c_str(),// [in] LPCTSTR pSrcFile,
                             D3DX_DEFAULT,              // [in] UINT Width,
                             D3DX_DEFAULT,              // [in] UINT Height,
                             D3DX_DEFAULT,              // [in] UINT MipLevels,
                             0,                         // [in] DWORD Usage,
                             D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
                             D3DPOOL_DEFAULT,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                             D3DX_FILTER_POINT,         // [in] DWORD Filter, D3DX_FILTER_POINTでボヤケナイ
                             D3DX_DEFAULT,              // [in] DWORD MipFilter,
                             0,                         // [in] D3DCOLOR ColorKey,
                             _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO *pSrcInfo,
                             NULL,                      // [in] PALETTEENTRY *pPalette,
                             &pIDirect3DTexture9        // [out] GgafDx9TextureConnection* *ppTextureCon
                          );
            checkDxException(hr2, D3D_OK, "[GgafDx9TextureManager::createResource] D3DXCreateTextureFromFileEx失敗。対象="<<prm_texture_name);
        }
        _pIDirect3DBaseTexture9 = pIDirect3DTexture9;
        Sleep(1); //工場に気を使う。
    } else {
        //環境マップテクスチャの場合
        LPDIRECT3DCUBETEXTURE9 pIDirect3DCubeTexture9;
        HRESULT hr = D3DXCreateCubeTextureFromFileEx(
                            GgafDx9God::_pID3DDevice9,     // [in ] LPDIRECT3DDEVICE9 pDevice,
                            texture_file_name.c_str(),     // [in ] LPCTSTR pSrcFile,
                            D3DX_DEFAULT,                  // [in ] UINT Size,
                            D3DX_DEFAULT,                  // [in ] UINT MipLevels,
                            0,                             // [in ] DWORD Usage,
                            D3DFMT_UNKNOWN,                // [in ] D3DFORMAT Format,
                            D3DPOOL_DEFAULT,               // [in ] D3DPOOL Pool,
                            D3DX_DEFAULT,                  // [in ] DWORD Filter,
                            D3DX_DEFAULT,                  // [in ] DWORD MipFilter,
                            0,                             // [in ] D3DCOLOR ColorKey,
                            _pD3DXIMAGE_INFO,              // [out] D3DXIMAGE_INFO * pSrcInfo,
                            NULL,                          // [out] PALETTEENTRY * pPalette,
                            &pIDirect3DCubeTexture9        // [out] LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
                    );
        checkDxException(hr, D3D_OK, "[GgafDx9TextureManager::createResource] D3DXCreateCubeTextureFromFileEx。対象="<<prm_texture_name);
        _pIDirect3DBaseTexture9 = pIDirect3DCubeTexture9;
        Sleep(1); //工場に気を使う。
    }
    TRACE3(" GgafDx9TextureManager::processCreateResource "<<prm_idstr<<" のテクスチャ生成しました。");
}

GgafDx9Texture::~GgafDx9Texture() {
    TRACE3("GgafDx9Texture::~GgafDx9Texture() " << _texture_name << " start-->");
    DELETEARR_IMPOSSIBLE_NULL(_texture_name);
    DELETE_IMPOSSIBLE_NULL(_pD3DXIMAGE_INFO);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DBaseTexture9);
}

