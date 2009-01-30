#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9TextureConnection::GgafDx9TextureConnection(char* prm_idstr, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9)
	:GgafResourceConnection<IDirect3DTexture9>(prm_idstr, prm_pIDirect3DTexture9) {
}

void GgafDx9TextureConnection::processReleaseResource(IDirect3DTexture9* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}

