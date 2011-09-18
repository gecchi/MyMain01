#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TextureManager::GgafDx9TextureManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Texture> (prm_manager_name) {
}

GgafDx9Texture* GgafDx9TextureManager::processCreateResource(char* prm_idstr, void* prm_p) {
    GgafDx9Texture* pResourceTexture;
    pResourceTexture = NEW GgafDx9Texture(prm_idstr);
    TRACE3(" GgafDx9TextureManager::processCreateResource "<<prm_idstr<<" のテクスチャ生成しました。");
    return pResourceTexture;
}

void GgafDx9TextureManager::releaseAll() {
    _TRACE_("GgafDx9TextureManager::releaseAll() start-->");
    GgafResourceConnection<GgafDx9Texture>* pCurrent = _pFirstConnection;
    while (pCurrent) {
        pCurrent->use()->release();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_("GgafDx9TextureManager::releaseAll() end<--");
}

void GgafDx9TextureManager::restoreAll() {
    _TRACE_("GgafDx9TextureManager::restoreAll() start-->");
    GgafResourceConnection<GgafDx9Texture>* pCurrent = _pFirstConnection;
    while (pCurrent) {
        pCurrent->use()->restore();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_("GgafDx9TextureManager::restoreAll() end<--");
}

GgafResourceConnection<GgafDx9Texture>* GgafDx9TextureManager::processCreateConnection(char* prm_idstr, GgafDx9Texture* prm_pResource) {
    TRACE3(" GgafDx9TextureManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDx9TextureConnection* pConnection = NEW GgafDx9TextureConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9TextureManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}

