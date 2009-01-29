#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9TextureConnection::GgafDx9TextureConnection(string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9)
	:GgafResourceConnection<IDirect3DTexture9>(prm_texture_file_name, prm_pIDirect3DTexture9) {
    _TRACE_("GgafDx9TextureConnection::GgafDx9TextureConnection(" <<  _resource_idstr << ")");
}

void GgafDx9TextureConnection::processReleaseResource(IDirect3DTexture9* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}


GgafDx9TextureConnection::~GgafDx9TextureConnection() {
	_TRACE_("GgafDx9TextureConnection::~GgafDx9TextureConnection() " <<  _resource_idstr << " start-->");
	_TRACE_("GgafDx9TextureConnection::~GgafDx9TextureConnection() " <<  _resource_idstr << " <--end");
}

