#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9TextureConnection::GgafDx9TextureConnection(char* prm_idstr, IDirect3DTexture9* prm_pIDirect3DTexture9)
	:GgafResourceConnection<IDirect3DTexture9>(prm_idstr, prm_pIDirect3DTexture9) {
    TRACE3("GgafDx9TextureConnection：コンストラクタ prm_idstr="<<prm_idstr);
}

void GgafDx9TextureConnection::processReleaseResource(IDirect3DTexture9* prm_pResource) {
    TRACE3("GgafDx9TextureConnection::processReleaseResource _idstr="<<_idstr<<" 開始");
    _pManager->dump();
	RELEASE_IMPOSSIBLE_NULL(prm_pResource);
    TRACE3("GgafDx9TextureConnection::processReleaseResource _idstr="<<_idstr<<" 完了");
}

GgafDx9TextureConnection::~GgafDx9TextureConnection() {
    TRACE3("GgafDx9TextureConnection：デストラクタ prm_idstr="<<_idstr);
}
