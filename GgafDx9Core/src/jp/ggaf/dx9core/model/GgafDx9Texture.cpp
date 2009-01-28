#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Texture::GgafDx9Texture(string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9)
	:GgafResource<IDirect3DTexture9>(prm_texture_file_name) {
    _TRACE_("GgafDx9Texture::GgafDx9Texture(" <<  _texture_file_name << ")");
    _pResource = prm_pIDirect3DTexture9;
}

void GgafDx9Texture::releaseResourceProcess() {
	_TRACE_("GgafDx9Texture::release() " <<  _texture_file_name << " start-->");
	RELEASE_IMPOSSIBLE_NULL(_pIDirect3DTexture9);
	_TRACE_("GgafDx9Texture::release() " <<  _texture_file_name << " <--end");
}

GgafDx9Texture::~GgafDx9Texture() {
	_TRACE_("GgafDx9Texture::~GgafDx9Texture() " <<  _texture_file_name << " start-->");
	_TRACE_("GgafDx9Texture::~GgafDx9Texture() " <<  _texture_file_name << " <--end");
}

