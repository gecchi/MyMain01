#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9ModelLead::GgafDx9ModelLead(char* prm_idstr, LPDIRECT3DTEXTURE9 prm_pIDirect3DModel9)
	:GgafResourceLead<IDirect3DModel9>(prm_idstr, prm_pIDirect3DModel9) {
}

void GgafDx9ModelLead::processReleaseResource(IDirect3DModel9* prm_pResource) {
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
}

