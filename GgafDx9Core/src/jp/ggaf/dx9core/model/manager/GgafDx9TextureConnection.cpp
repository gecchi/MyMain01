#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9TextureConnection::GgafDx9TextureConnection(char* prm_idstr, IDirect3DTexture9* prm_pIDirect3DTexture9)
	:GgafResourceConnection<IDirect3DTexture9>(prm_idstr, prm_pIDirect3DTexture9) {
    _TRACE_("GgafDx9TextureConnection：コンストラクタ prm_idstr="<<prm_idstr);
}

void GgafDx9TextureConnection::processReleaseResource(IDirect3DTexture9* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}

GgafDx9TextureConnection::~GgafDx9TextureConnection() {
    _TRACE_("GgafDx9TextureConnection：デストラクタ prm_idstr="<<_idstr);
}
