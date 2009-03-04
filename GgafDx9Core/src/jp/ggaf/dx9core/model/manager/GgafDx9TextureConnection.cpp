#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9TextureConnection::GgafDx9TextureConnection(char* prm_idstr, IDirect3DTexture9* prm_pIDirect3DTexture9)
	:GgafResourceConnection<IDirect3DTexture9>(prm_idstr, prm_pIDirect3DTexture9) {
    TRACE("GgafDx9TextureConnection�F�R���X�g���N�^ prm_idstr="<<prm_idstr);
}

void GgafDx9TextureConnection::processReleaseResource(IDirect3DTexture9* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}

GgafDx9TextureConnection::~GgafDx9TextureConnection() {
    TRACE("GgafDx9TextureConnection�F�f�X�g���N�^ prm_idstr="<<_idstr);
}
