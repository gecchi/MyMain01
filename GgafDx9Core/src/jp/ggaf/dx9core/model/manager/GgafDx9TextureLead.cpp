#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9TextureLead::GgafDx9TextureLead(char* prm_idstr, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9)
	:GgafResourceLead<IDirect3DTexture9>(prm_idstr, prm_pIDirect3DTexture9) {
}

void GgafDx9TextureLead::processReleaseResource(IDirect3DTexture9* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}

