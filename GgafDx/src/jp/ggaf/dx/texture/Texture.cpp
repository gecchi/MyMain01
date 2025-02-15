#include "jp/ggaf/dx/texture/Texture.h"

#include <Shlwapi.h>
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/Caretaker.h"


using namespace GgafDx;

Texture::Texture(const char* prm_texture_name) : GgafCore::Object() {
    int len = strlen(prm_texture_name);
    _texture_name = NEW char[len+1];
    strcpy(_texture_name, prm_texture_name);
    _texture_file_name = "";
    restore();
}

std::string Texture::getTextureFilePath(std::string prm_file) {
    std::string texture_file2 = CONFIG::DIR_TEXTURE[2] + "/" + prm_file;
    UTIL::strReplace(texture_file2, "//", "/");
    if (PathFileExists(texture_file2.c_str()) ) {
        _TRACE_("Texture::getTextureFilePath() texture_file2.c_str()="<<texture_file2.c_str());
        return texture_file2;
    } else {
        std::string texture_file1 = CONFIG::DIR_TEXTURE[1] + "/" + prm_file;
        UTIL::strReplace(texture_file1, "//", "/");
        if (PathFileExists(texture_file1.c_str()) ) {
            _TRACE_("Texture::getTextureFilePath() texture_file1.c_str()="<<texture_file1.c_str());
            return texture_file1;
        } else {
            std::string texture_file0 = CONFIG::DIR_TEXTURE[0] + "/" + prm_file;
            UTIL::strReplace(texture_file0, "//", "/");
            if (PathFileExists(texture_file0.c_str()) ) {
                _TRACE_("Texture::getTextureFilePath() texture_file0.c_str()="<<texture_file0.c_str());
                return texture_file0;
            } else {
                std::string texture_file = "./" + prm_file;
                UTIL::strReplace(texture_file, "//", "/");
                if (PathFileExists(texture_file.c_str()) ) {
                    _TRACE_("Texture::getTextureFilePath() texture_file.c_str()="<<texture_file.c_str());
                    return texture_file;
                } else {
                    _TRACE_("【警告】Texture::getTextureFilePath テクスチャファイルが見つかりません。prm_file="<<prm_file<<"\n"<<
                            "texture_file2="<<texture_file2<<"\n"
                            "texture_file1="<<texture_file1<<"\n"
                            "texture_file0="<<texture_file0<<"\n"
                            "texture_file="<<texture_file);
                    return "";
                }
            }
        }
    }
}

void Texture::restore() {
    _pIDirect3DBaseTexture9 = nullptr;
    _pD3DXIMAGE_INFO = NEW D3DXIMAGE_INFO;
    std::string texture_name = std::string(_texture_name);
    if (_texture_file_name == "") {
        _texture_file_name = Texture::getTextureFilePath(texture_name);
    }

    //テクスチャファイル名に "cubemap" or "CubeMap" or "Cubemap" が含まれていれば、環境マップテクスチャとみなす
    if (texture_name.find("cubemap") == std::string::npos &&
        texture_name.find("CubeMap") == std::string::npos &&
        texture_name.find("Cubemap") == std::string::npos
    ) {
        _TRACE_("Texture::restore() texture_name="<<texture_name<<" は、通常の2Dテクスチャとみなします（ファイル名に CubeMap が含まれ無い為）");
        //通常の2Dテクスチャの場合
        LPDIRECT3DTEXTURE9 pIDirect3DTexture9;
        HRESULT hr = D3DXCreateTextureFromFileEx(
                         pCARETAKER->_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice,
                         _texture_file_name.c_str(), // [in] LPCTSTR pSrcFile,
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
            _TRACE_("【警告】D3DXCreateTextureFromFileEx失敗の為、[IlligalTexture.dds]を設定。texture_name="<<texture_name<<" _texture_file_name="<<_texture_file_name);
            //失敗用テクスチャ"IlligalTexture.dds"を設定
            texture_name = getTextureFilePath(CONFIG::ILLIGAL_TEXTURE);
            HRESULT hr2 = D3DXCreateTextureFromFileEx(
                             pCARETAKER->_pID3DDevice9,   // [in] LPDIRECT3DDEVICE9 pDevice,
                             texture_name.c_str(), // [in] LPCTSTR pSrcFile,
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
                             &pIDirect3DTexture9         // [out] TextureConnection* *ppTextureConnection
                          );
            checkDxException(hr2, D3D_OK, "【警告】TextureManager::restore() D3DXCreateTextureFromFileEx失敗。対象="<<texture_name);
        }
        D3DSURFACE_DESC d3dsurface_desc;
        pIDirect3DTexture9->GetLevelDesc(0, &d3dsurface_desc);
        _tex_width = d3dsurface_desc.Width;
        _tex_height = d3dsurface_desc.Height;
        _pIDirect3DBaseTexture9 = pIDirect3DTexture9;
        Sleep(1); //愛に気を使う。
    } else {
        _TRACE_("Texture::restore() texture_name="<<texture_name<<" は、環境マップテクスチャとみなします（ファイル名に CubeMap が含まれる為）");
        //環境マップテクスチャの場合
        LPDIRECT3DCUBETEXTURE9 pIDirect3DCubeTexture9;
        HRESULT hr = D3DXCreateCubeTextureFromFileEx(
                            pCARETAKER->_pID3DDevice9,  // [in ] LPDIRECT3DDEVICE9 pDevice,
                            _texture_file_name.c_str(), // [in ] LPCTSTR pSrcFile,
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
            _TRACE_("【警告】D3DXCreateCubeTextureFromFileEx 失敗の為[IlligalTexture.dds]を設定。texture_name="<<texture_name<<" _texture_file_name="<<_texture_file_name);
            //失敗用環境マップテクスチャ"IlligalCubeMapTexture.dds"を設定
            texture_name = getTextureFilePath(CONFIG::ILLIGAL_CUBEMAP_TEXTURE);
            HRESULT hr2 = D3DXCreateCubeTextureFromFileEx(
                                    pCARETAKER->_pID3DDevice9,   // [in ] LPDIRECT3DDEVICE9 pDevice,
                                    texture_name.c_str(), // [in ] LPCTSTR pSrcFile,
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
            checkDxException(hr2, D3D_OK, "D3DXCreateTextureFromFileEx失敗。対象="<<texture_name);
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

    _TRACE_("Texture::restore() "<<texture_name<<"("<<_tex_width<<"x"<<_tex_height<<") のテクスチャ生成しました。 _texture_file_name=" << _texture_file_name<<" this="<<this);
}
void Texture::release() {
    GGAF_DELETE(_pD3DXIMAGE_INFO);
    GGAF_RELEASE(_pIDirect3DBaseTexture9);
}

Texture::~Texture() {
    _TRACE4_("Texture::~Texture("<<_texture_name<<") Adr:"<<this);
    Texture::release();
    GGAF_DELETEARR(_texture_name);
}

