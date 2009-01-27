#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

string GgafDx9Texture::_id_lastdraw = "";

GgafDx9Texture::GgafDx9Texture(string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9) : GgafObject() {
    _TRACE_("GgafDx9Texture::GgafDx9Texture(" <<  _texture_file_name << ")");
    _texture_file_name = prm_texture_file_name;
	_pIDirect3DTexture9 = prm_pIDirect3DTexture9;
	_pTexture_Next = NULL;
	_iRefModelNum = 0;
}

void GgafDx9Texture::release() {
	RELEASE_IMPOSSIBLE_NULL(_pIDirect3DTexture9);
}

GgafDx9Texture::~GgafDx9Texture() {
	_TRACE_("GgafDx9Texture::~GgafDx9Texture() " <<  _texture_file_name << " start-->");
	_TRACE_("GgafDx9Texture::~GgafDx9Texture() " <<  _texture_file_name << " <--end");
}

