#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

#include "Shlwapi.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxTexture::GgafDxTexture(const char* prm_texture_name) : GgafObject() {
    _texture_name = NEW char[51];
    strcpy(_texture_name, prm_texture_name);
    restore();
}

std::string GgafDxTexture::getTextureFileName(std::string prm_file) {
    std::string texture_file = PROPERTY::DIR_TEXTURE[2] + "/" + prm_file;
    UTIL::strReplace(texture_file, "//", "/");
    if (PathFileExists(texture_file.c_str()) ) {
        return texture_file; //ユーザースキンに存在すればそれを優先
    } else {
        texture_file = PROPERTY::DIR_TEXTURE[1] + "/" + prm_file;
        UTIL::strReplace(texture_file, "//", "/");
        if (PathFileExists(texture_file.c_str()) ) {
            return texture_file;
        } else {
            texture_file = PROPERTY::DIR_TEXTURE[0] + "/" + prm_file;
            UTIL::strReplace(texture_file, "//", "/");
            if (PathFileExists(texture_file.c_str()) ) {
                return texture_file;
            } else {
                _TRACE_("＜警告＞GgafDxTexture::getTextureFileName テクスチャファイルが見つかりません。texture_file="<<texture_file);
                return texture_file;
            }
        }
    }
}

void GgafDxTexture::restore() {
    _pIDirect3DBaseTexture9 = nullptr;
    _pD3DXIMAGE_INFO = NEW D3DXIMAGE_INFO;
    std::string texture_name = std::string(_texture_name);
    std::string texture_file_name = getTextureFileName(texture_name);

    //テクスチャファイル名に "cubemap" or "CubeMap" or "Cubemap" が含まれていれば、環境マップテクスチャとみなす
    if (texture_name.find("cubemap") == std::string::npos &&
        texture_name.find("CubeMap") == std::string::npos &&
        texture_name.find("Cubemap") == std::string::npos
    ) {
        //通常の２Dテクスチャの場合
        LPDIRECT3DTEXTURE9 pIDirect3DTexture9;
        HRESULT hr = D3DXCreateTextureFromFileEx(
                         GgafDxGod::_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice,
                         texture_file_name.c_str(), // [in] LPCTSTR pSrcFile,
                         D3DX_DEFAULT,              // [in] UINT Widths,
                         D3DX_DEFAULT,              // [in] UINT Height,
                         D3DX_DEFAULT,              // [in] UINT MipLevels,  //D3DX_DEFAULT,
                         0,                         // [in] DWORD Usage,
                         D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
                         D3DPOOL_DEFAULT,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                         D3DX_FILTER_POINT,         // [in] DWORD Filter, D3DX_FILTER_POINTでボヤケナイ. D3DX_FILTER_LINEAR
                         D3DX_DEFAULT,              // [in] DWORD MipFilter,
                         0,                         // [in] D3DCOLOR ColorKey,
                         _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO *pSrcInfo,
                         nullptr,                   // [in] PALETTEENTRY *pPalette,
                         &pIDirect3DTexture9        // [out] LPDIRECT3DTEXTURE9* ppTexture
                    );
        if (hr != D3D_OK) {
            _TRACE_("GgafDxTextureManager::restore() D3DXCreateTextureFromFileEx失敗。対象="<<texture_file_name);
            //失敗用テクスチャ"GgafDxIlligalTexture.dds"を設定
            std::string texture_file_name2 = getTextureFileName(PROPERTY::ILLIGAL_TEXTURE);
            HRESULT hr2 = D3DXCreateTextureFromFileEx(
                             GgafDxGod::_pID3DDevice9,   // [in] LPDIRECT3DDEVICE9 pDevice,
                             texture_file_name2.c_str(), // [in] LPCTSTR pSrcFile,
                             D3DX_DEFAULT,               // [in] UINT Width,
                             D3DX_DEFAULT,               // [in] UINT Height,
                             D3DX_DEFAULT,               // [in] UINT MipLevels,
                             0,                          // [in] DWORD Usage,
                             D3DFMT_UNKNOWN,             // [in] D3DFORMAT Format,
                             D3DPOOL_DEFAULT,            // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                             D3DX_FILTER_POINT,          // [in] DWORD Filter, D3DX_FILTER_POINTでボヤケナイ
                             D3DX_DEFAULT,               // [in] DWORD MipFilter,
                             0,                          // [in] D3DCOLOR ColorKey,
                             _pD3DXIMAGE_INFO,           // [out] D3DXIMAGE_INFO *pSrcInfo,
                             nullptr,                    // [in] PALETTEENTRY *pPalette,
                             &pIDirect3DTexture9         // [out] GgafDxTextureConnection* *ppTextureConnection
                          );
            checkDxException(hr2, D3D_OK, "＜警告＞GgafDxTextureManager::restore() D3DXCreateTextureFromFileEx失敗。対象="<<texture_file_name2);
        }
        D3DSURFACE_DESC d3dsurface_desc;
        pIDirect3DTexture9->GetLevelDesc(0, &d3dsurface_desc);
        _tex_width = d3dsurface_desc.Width;
        _tex_height = d3dsurface_desc.Height;
        _pIDirect3DBaseTexture9 = pIDirect3DTexture9;
        Sleep(1); //工場に気を使う。
    } else {
        //環境マップテクスチャの場合
        LPDIRECT3DCUBETEXTURE9 pIDirect3DCubeTexture9;
        HRESULT hr = D3DXCreateCubeTextureFromFileEx(
                            GgafDxGod::_pID3DDevice9,  // [in ] LPDIRECT3DDEVICE9 pDevice,
                            texture_file_name.c_str(), // [in ] LPCTSTR pSrcFile,
                            D3DX_DEFAULT,              // [in ] UINT Size,
                            D3DX_DEFAULT,              // [in ] UINT MipLevels,
                            0,                         // [in ] DWORD Usage,
                            D3DFMT_UNKNOWN,            // [in ] D3DFORMAT Format,
                            D3DPOOL_DEFAULT,           // [in ] D3DPOOL Pool,
                            D3DX_FILTER_POINT,         // [in ] DWORD Filter, D3DX_FILTER_POINT D3DX_FILTER_LINEAR
                            D3DX_DEFAULT,              // [in ] DWORD MipFilter,
                            0,                         // [in ] D3DCOLOR ColorKey,
                            _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO * pSrcInfo,
                            nullptr,                   // [out] PALETTEENTRY * pPalette,
                            &pIDirect3DCubeTexture9    // [out] LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
                    );
        if (hr != D3D_OK) {
            _TRACE_("＜警告＞GgafDxTextureManager::restore() D3DXCreateCubeTextureFromFileEx 失敗。対象="<<texture_name);
            //失敗用環境マップテクスチャ"GgafDxIlligalCubeMapTexture.dds"を設定
            std::string texture_file_name2 = getTextureFileName(PROPERTY::ILLIGAL_CUBEMAP_TEXTURE);
            HRESULT hr2 = D3DXCreateCubeTextureFromFileEx(
                                    GgafDxGod::_pID3DDevice9,   // [in ] LPDIRECT3DDEVICE9 pDevice,
                                    texture_file_name2.c_str(), // [in ] LPCTSTR pSrcFile,
                                    D3DX_DEFAULT,               // [in ] UINT Size,
                                    D3DX_DEFAULT,               // [in ] UINT MipLevels,
                                    0,                          // [in ] DWORD Usage,
                                    D3DFMT_UNKNOWN,             // [in ] D3DFORMAT Format,
                                    D3DPOOL_DEFAULT,            // [in ] D3DPOOL Pool,
                                    D3DX_FILTER_POINT,          // [in ] DWORD Filter, D3DX_FILTER_POINT D3DX_FILTER_LINEAR
                                    D3DX_DEFAULT,               // [in ] DWORD MipFilter,
                                    0,                          // [in ] D3DCOLOR ColorKey,
                                    _pD3DXIMAGE_INFO,           // [out] D3DXIMAGE_INFO * pSrcInfo,
                                    nullptr,                    // [out] PALETTEENTRY * pPalette,
                                    &pIDirect3DCubeTexture9     // [out] LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
                            );
            checkDxException(hr2, D3D_OK, "GgafDxTextureManager::restore() D3DXCreateTextureFromFileEx失敗。対象="<<texture_name);
        }

        D3DSURFACE_DESC d3dsurface_desc;
        pIDirect3DCubeTexture9->GetLevelDesc(0, &d3dsurface_desc);
        _tex_width = d3dsurface_desc.Width;
        _tex_height = d3dsurface_desc.Height;
        _pIDirect3DBaseTexture9 = pIDirect3DCubeTexture9;
    }

    //    //1pxあたりのuvの大きさを求める
    //     D3DSURFACE_DESC d3dsurface_desc;
    //     model_pTextureConnection->view()->GetLevelDesc(0, &d3dsurface_desc);
    //     float pxU = 1.0 / d3dsurface_desc.Width; //テクスチャの幅(px)で割る
    //     float pxV = 1.0 / d3dsurface_desc.Height; //テクスチャの高さ(px)で割る

    _TRACE_("GgafDxTextureManager::restore() "<<texture_name<<" のテクスチャ生成しました。this="<<this);
}
void GgafDxTexture::release() {
    GGAF_DELETE(_pD3DXIMAGE_INFO);
    GGAF_RELEASE(_pIDirect3DBaseTexture9);
}

GgafDxTexture::~GgafDxTexture() {
    _TRACE_("GgafDxTexture::~GgafDxTexture() " << _texture_name );
    GgafDxTexture::release();
    GGAF_DELETEARR(_texture_name);
}

