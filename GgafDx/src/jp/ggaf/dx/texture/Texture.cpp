#include "jp/ggaf/dx/texture/Texture.h"

#include <Shlwapi.h>
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/God.h"


using namespace GgafDx;

Texture::Texture(const char* prm_texture_name) : GgafCore::Object() {
    int len = strlen(prm_texture_name);
    _texture_name = NEW char[len+1];
    strcpy(_texture_name, prm_texture_name);
    restore();
}

std::string Texture::getTextureFilePath(std::string prm_file) {
    std::string texture_file = CONFIG::DIR_TEXTURE[2] + "/" + prm_file;
    UTIL::strReplace(texture_file, "//", "/");
    if (PathFileExists(texture_file.c_str()) ) {
        return texture_file;
    } else {
        texture_file = CONFIG::DIR_TEXTURE[1] + "/" + prm_file;
        UTIL::strReplace(texture_file, "//", "/");
        if (PathFileExists(texture_file.c_str()) ) {
            return texture_file;
        } else {
            texture_file = CONFIG::DIR_TEXTURE[0] + "/" + prm_file;
            UTIL::strReplace(texture_file, "//", "/");
            if (PathFileExists(texture_file.c_str()) ) {
                return texture_file;
            } else {
                _TRACE_("�y�x���zTexture::getTextureFilePath �e�N�X�`���t�@�C����������܂���Btexture_file="<<texture_file);
                return texture_file;
            }
        }
    }
}

void Texture::restore() {
    _pIDirect3DBaseTexture9 = nullptr;
    _pD3DXIMAGE_INFO = NEW D3DXIMAGE_INFO;
    std::string texture_name = std::string(_texture_name);
    std::string texture_file_name = Texture::getTextureFilePath(texture_name);

    //�e�N�X�`���t�@�C������ "cubemap" or "CubeMap" or "Cubemap" ���܂܂�Ă���΁A���}�b�v�e�N�X�`���Ƃ݂Ȃ�
    if (texture_name.find("cubemap") == std::string::npos &&
        texture_name.find("CubeMap") == std::string::npos &&
        texture_name.find("Cubemap") == std::string::npos
    ) {
        _TRACE_("Texture::restore() texture_name="<<texture_name<<" �́A�ʏ�̂QD�e�N�X�`���Ƃ݂Ȃ��܂��i�t�@�C������ CubeMap ���܂܂ꖳ���ׁj");
        //�ʏ�̂QD�e�N�X�`���̏ꍇ
        LPDIRECT3DTEXTURE9 pIDirect3DTexture9;
        HRESULT hr = D3DXCreateTextureFromFileEx(
                         God::_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice,
                         texture_file_name.c_str(), // [in] LPCTSTR pSrcFile,
                         D3DX_DEFAULT,              // [in] UINT Widths,
                         D3DX_DEFAULT,              // [in] UINT Height,
                         D3DX_DEFAULT,              // [in] UINT MipLevels,  //D3DX_DEFAULT,
                         0,                         // [in] DWORD Usage,
                         D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
                         D3DPOOL_DEFAULT,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                         D3DX_FILTER_POINT,         // [in] DWORD Filter, D3DX_FILTER_POINT�Ń{���P�i�C. D3DX_FILTER_LINEAR
                         D3DX_DEFAULT,              // [in] DWORD MipFilter,
                         0,                         // [in] D3DCOLOR ColorKey,
                         _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO *pSrcInfo,
                         nullptr,                   // [in] PALETTEENTRY *pPalette,
                         &pIDirect3DTexture9        // [out] LPDIRECT3DTEXTURE9* ppTexture
                    );
        if (hr != D3D_OK) {
            _TRACE_("D3DXCreateTextureFromFileEx���s�B�Ώ�="<<texture_file_name);
            //���s�p�e�N�X�`��"IlligalTexture.dds"��ݒ�
            std::string texture_file_name2 = getTextureFilePath(CONFIG::ILLIGAL_TEXTURE);
            HRESULT hr2 = D3DXCreateTextureFromFileEx(
                             God::_pID3DDevice9,   // [in] LPDIRECT3DDEVICE9 pDevice,
                             texture_file_name2.c_str(), // [in] LPCTSTR pSrcFile,
                             D3DX_DEFAULT,               // [in] UINT Width,
                             D3DX_DEFAULT,               // [in] UINT Height,
                             D3DX_DEFAULT,               // [in] UINT MipLevels,
                             0,                          // [in] DWORD Usage,
                             D3DFMT_UNKNOWN,             // [in] D3DFORMAT Format,
                             D3DPOOL_DEFAULT,            // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
                             D3DX_FILTER_POINT,          // [in] DWORD Filter, D3DX_FILTER_POINT�Ń{���P�i�C
                             D3DX_DEFAULT,               // [in] DWORD MipFilter,
                             0,                          // [in] D3DCOLOR ColorKey,
                             _pD3DXIMAGE_INFO,           // [out] D3DXIMAGE_INFO *pSrcInfo,
                             nullptr,                    // [in] PALETTEENTRY *pPalette,
                             &pIDirect3DTexture9         // [out] TextureConnection* *ppTextureConnection
                          );
            checkDxException(hr2, D3D_OK, "�y�x���zTextureManager::restore() D3DXCreateTextureFromFileEx���s�B�Ώ�="<<texture_file_name2);
        }
        D3DSURFACE_DESC d3dsurface_desc;
        pIDirect3DTexture9->GetLevelDesc(0, &d3dsurface_desc);
        _tex_width = d3dsurface_desc.Width;
        _tex_height = d3dsurface_desc.Height;
        _pIDirect3DBaseTexture9 = pIDirect3DTexture9;
        Sleep(1); //���ɋC���g���B
    } else {
        _TRACE_("Texture::restore() texture_name="<<texture_name<<" �́A���}�b�v�e�N�X�`���Ƃ݂Ȃ��܂��i�t�@�C������ CubeMap ���܂܂��ׁj");
        //���}�b�v�e�N�X�`���̏ꍇ
        LPDIRECT3DCUBETEXTURE9 pIDirect3DCubeTexture9;
        HRESULT hr = D3DXCreateCubeTextureFromFileEx(
                            God::_pID3DDevice9,  // [in ] LPDIRECT3DDEVICE9 pDevice,
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
            _TRACE_("�y�x���zTextureManager::restore() D3DXCreateCubeTextureFromFileEx ���s�B�Ώ�="<<texture_name);
            //���s�p���}�b�v�e�N�X�`��"IlligalCubeMapTexture.dds"��ݒ�
            std::string texture_file_name2 = getTextureFilePath(CONFIG::ILLIGAL_CUBEMAP_TEXTURE);
            HRESULT hr2 = D3DXCreateCubeTextureFromFileEx(
                                    God::_pID3DDevice9,   // [in ] LPDIRECT3DDEVICE9 pDevice,
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
            checkDxException(hr2, D3D_OK, "D3DXCreateTextureFromFileEx���s�B�Ώ�="<<texture_name);
        }

        D3DSURFACE_DESC d3dsurface_desc;
        pIDirect3DCubeTexture9->GetLevelDesc(0, &d3dsurface_desc);
        _tex_width = d3dsurface_desc.Width;
        _tex_height = d3dsurface_desc.Height;
        _pIDirect3DBaseTexture9 = pIDirect3DCubeTexture9;
    }

    //    //1px�������uv�̑傫�������߂�
    //     D3DSURFACE_DESC d3dsurface_desc;
    //     model_pTextureConnection->view()->GetLevelDesc(0, &d3dsurface_desc);
    //     float pxU = 1.0 / d3dsurface_desc.Width; //�e�N�X�`���̕�(px)�Ŋ���
    //     float pxV = 1.0 / d3dsurface_desc.Height; //�e�N�X�`���̍���(px)�Ŋ���

    _TRACE_(""<<texture_name<<" �̃e�N�X�`���������܂����Bthis="<<this);
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

