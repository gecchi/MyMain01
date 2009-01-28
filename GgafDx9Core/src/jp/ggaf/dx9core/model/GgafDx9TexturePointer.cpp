#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9TexturePointer::GgafDx9TexturePointer(string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9)
	:GgafResourcePointer<IDirect3DTexture9>(prm_texture_file_name, prm_pIDirect3DTexture9) {
    _TRACE_("GgafDx9TexturePointer::GgafDx9TexturePointer(" <<  _texture_file_name << ")");
}
GgafDx9TexturePointer::~GgafDx9TexturePointer() {
	_TRACE_("GgafDx9TexturePointer::~GgafDx9TexturePointer() " <<  _texture_file_name << " start-->");
	_TRACE_("GgafDx9TexturePointer::~GgafDx9TexturePointer() " <<  _texture_file_name << " <--end");
}

