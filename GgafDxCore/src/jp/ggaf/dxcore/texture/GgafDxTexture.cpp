#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxTexture::GgafDxTexture(char* prm_texture_name) : GgafObject() {
    TRACE("GgafDxTexture::GgafDxTexture(" << prm_texture_name << ")");
    _texture_name = NEW char[51];
    strcpy(_texture_name, prm_texture_name);
    restore();
}

void GgafDxTexture::restore() {
    TRACE("GgafDxTexture::restore()");
    _pIDirect3DBaseTexture9 = NULL;
    _pD3DXIMAGE_INFO = NEW D3DXIMAGE_INFO();
    string texture_name = string(_texture_name);
    string texture_file_name = CFG_PROPERTY(DIR_TEXTURE) + texture_name;

    //�e�N�X�`���t�@�C������ "cubemap" or "CubeMap" or "Cubemap" ���܂܂�Ă���΁A���}�b�v�e�N�X�`���Ƃ݂Ȃ�
    if (texture_name.find("cubemap") == string::npos &&
        texture_name.find("CubeMap") == string::npos &&
        texture_name.find("Cubemap") == string::npos
    ) {
        //�ʏ�̂QD�e�N�X�`���̏ꍇ
        LPDIRECT3DTEXTURE9 pIDirect3DTexture9;
        HRESULT hr = D3DXCreateTextureFromFileEx(
                         GgafDxGod::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice,
                         texture_file_name.c_str(), // [in] LPCTSTR pSrcFile,
                         D3DX_DEFAULT,              // [in] UINT Widths,
                         D3DX_DEFAULT,              // [in] UINT Height,
                         D3DX_DEFAULT,              // [in] UINT MipLevels,  //D3DX_DEFAULT,
                         0,                         // [in] DWORD Usage,
                         D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
                         D3DPOOL_DEFAULT,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                         D3DX_FILTER_POINT,              // [in] DWORD Filter, D3DX_FILTER_POINT�Ń{���P�i�C. D3DX_FILTER_LINEAR
                         D3DX_DEFAULT,              // [in] DWORD MipFilter,
                         0,                         // [in] D3DCOLOR ColorKey,
                         _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO *pSrcInfo,
                         NULL,                      // [in] PALETTEENTRY *pPalette,
                         &pIDirect3DTexture9        // [out] LPDIRECT3DTEXTURE9* ppTexture
                    );
        if (hr != D3D_OK) {
            _TRACE_("GgafDxTextureManager::restore() D3DXCreateTextureFromFileEx���s�B�Ώ�="<<texture_name);
            //���s�p�e�N�X�`��"GgafDxIlligalTexture.png"��ݒ�
            string texture_file_name2 = CFG_PROPERTY(DIR_TEXTURE) + "GgafDxIlligalTexture.png";
            HRESULT hr2 = D3DXCreateTextureFromFileEx(
                             GgafDxGod::_pID3DDevice9, // [in] LPDIRECT3DDEVICE9 pDevice,
                             texture_file_name2.c_str(),// [in] LPCTSTR pSrcFile,
                             D3DX_DEFAULT,              // [in] UINT Width,
                             D3DX_DEFAULT,              // [in] UINT Height,
                             D3DX_DEFAULT,              // [in] UINT MipLevels,
                             0,                         // [in] DWORD Usage,
                             D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
                             D3DPOOL_DEFAULT,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                             D3DX_FILTER_POINT,         // [in] DWORD Filter, D3DX_FILTER_POINT�Ń{���P�i�C
                             D3DX_DEFAULT,              // [in] DWORD MipFilter,
                             0,                         // [in] D3DCOLOR ColorKey,
                             _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO *pSrcInfo,
                             NULL,                      // [in] PALETTEENTRY *pPalette,
                             &pIDirect3DTexture9        // [out] GgafDxTextureConnection* *ppTextureCon
                          );
            checkDxException(hr2, D3D_OK, "���x����GgafDxTextureManager::restore() D3DXCreateTextureFromFileEx���s�B�Ώ�="<<texture_name);
        }
        D3DSURFACE_DESC d3dsurface_desc;
        pIDirect3DTexture9->GetLevelDesc(0, &d3dsurface_desc);
        _tex_width = d3dsurface_desc.Width;
        _tex_height = d3dsurface_desc.Height;
        _pIDirect3DBaseTexture9 = pIDirect3DTexture9;
        Sleep(1); //�H��ɋC���g���B
    } else {
        //���}�b�v�e�N�X�`���̏ꍇ
        LPDIRECT3DCUBETEXTURE9 pIDirect3DCubeTexture9;
        HRESULT hr = D3DXCreateCubeTextureFromFileEx(
                            GgafDxGod::_pID3DDevice9,     // [in ] LPDIRECT3DDEVICE9 pDevice,
                            texture_file_name.c_str(),     // [in ] LPCTSTR pSrcFile,
                            D3DX_DEFAULT,                  // [in ] UINT Size,
                            D3DX_DEFAULT,                  // [in ] UINT MipLevels,
                            0,                             // [in ] DWORD Usage,
                            D3DFMT_UNKNOWN,                // [in ] D3DFORMAT Format,
                            D3DPOOL_DEFAULT,               // [in ] D3DPOOL Pool,
                            D3DX_FILTER_POINT,                  // [in ] DWORD Filter, D3DX_FILTER_POINT D3DX_FILTER_LINEAR
                            D3DX_DEFAULT,                  // [in ] DWORD MipFilter,
                            0,                             // [in ] D3DCOLOR ColorKey,
                            _pD3DXIMAGE_INFO,              // [out] D3DXIMAGE_INFO * pSrcInfo,
                            NULL,                          // [out] PALETTEENTRY * pPalette,
                            &pIDirect3DCubeTexture9        // [out] LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
                    );
        if (hr != D3D_OK) {
            _TRACE_("���x����GgafDxTextureManager::restore() D3DXCreateCubeTextureFromFileEx ���s�B�Ώ�="<<texture_name);
            //���s�p���}�b�v�e�N�X�`��"GgafDxIlligalCubeMapTexture.dds"��ݒ�
            string texture_file_name2 = CFG_PROPERTY(DIR_TEXTURE) + "GgafDxIlligalCubeMapTexture.dds";
            HRESULT hr2 = D3DXCreateCubeTextureFromFileEx(
                                    GgafDxGod::_pID3DDevice9,     // [in ] LPDIRECT3DDEVICE9 pDevice,
                                    texture_file_name2.c_str(),     // [in ] LPCTSTR pSrcFile,
                                    D3DX_DEFAULT,                  // [in ] UINT Size,
                                    D3DX_DEFAULT,                  // [in ] UINT MipLevels,
                                    0,                             // [in ] DWORD Usage,
                                    D3DFMT_UNKNOWN,                // [in ] D3DFORMAT Format,
                                    D3DPOOL_DEFAULT,               // [in ] D3DPOOL Pool,
                                    D3DX_FILTER_POINT,                  // [in ] DWORD Filter, D3DX_FILTER_POINT D3DX_FILTER_LINEAR
                                    D3DX_DEFAULT,                  // [in ] DWORD MipFilter,
                                    0,                             // [in ] D3DCOLOR ColorKey,
                                    _pD3DXIMAGE_INFO,              // [out] D3DXIMAGE_INFO * pSrcInfo,
                                    NULL,                          // [out] PALETTEENTRY * pPalette,
                                    &pIDirect3DCubeTexture9        // [out] LPDIRECT3DCUBETEXTURE9 * ppCubeTexture
                            );
            checkDxException(hr2, D3D_OK, "GgafDxTextureManager::restore() D3DXCreateTextureFromFileEx���s�B�Ώ�="<<texture_name);
        }

        D3DSURFACE_DESC d3dsurface_desc;
        pIDirect3DCubeTexture9->GetLevelDesc(0, &d3dsurface_desc);
        _tex_width = d3dsurface_desc.Width;
        _tex_height = d3dsurface_desc.Height;
        _pIDirect3DBaseTexture9 = pIDirect3DCubeTexture9;
    }

    //    //1px�������uv�̑傫�������߂�
    //     D3DSURFACE_DESC d3dsurface_desc;
    //     model_pTextureCon->view()->GetLevelDesc(0, &d3dsurface_desc);
    //     float pxU = 1.0 / d3dsurface_desc.Width; //�e�N�X�`���̕�(px)�Ŋ���
    //     float pxV = 1.0 / d3dsurface_desc.Height; //�e�N�X�`���̍���(px)�Ŋ���

    _TRACE_("GgafDxTextureManager::restore() "<<texture_name<<" �̃e�N�X�`���������܂����B");
}
void GgafDxTexture::release() {
    DELETE_IMPOSSIBLE_NULL(_pD3DXIMAGE_INFO);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DBaseTexture9);
}

GgafDxTexture::~GgafDxTexture() {
    TRACE3("GgafDxTexture::~GgafDxTexture() " << _texture_name << " start-->");
    release();
    DELETEARR_IMPOSSIBLE_NULL(_texture_name);
}
