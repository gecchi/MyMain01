#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxTextureManager::GgafDxTextureManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxTexture> (prm_manager_name) {
}

GgafDxTexture* GgafDxTextureManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    GgafDxTexture* pResourceTexture;
    pResourceTexture = NEW GgafDxTexture(prm_idstr);
    _DTRACE3_(" GgafDxTextureManager::processCreateResource "<<prm_idstr<<" のテクスチャ生成しました。");
    return pResourceTexture;
}

void GgafDxTextureManager::releaseAll() {
    _DTRACE_("GgafDxTextureManager::releaseAll() start-->");
    GgafResourceConnection<GgafDxTexture>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->release();
        pCurrent = pCurrent->getNext();
    }
    _DTRACE_("GgafDxTextureManager::releaseAll() end<--");
}

void GgafDxTextureManager::restoreAll() {
    _DTRACE_("GgafDxTextureManager::restoreAll() start-->");
    GgafResourceConnection<GgafDxTexture>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->restore();
        pCurrent = pCurrent->getNext();
    }
    _DTRACE_("GgafDxTextureManager::restoreAll() end<--");
}

GgafResourceConnection<GgafDxTexture>* GgafDxTextureManager::processCreateConnection(char* prm_idstr, GgafDxTexture* prm_pResource) {
    _DTRACE3_(" GgafDxTextureManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDxTextureConnection* pConne = NEW GgafDxTextureConnection(prm_idstr, prm_pResource);
    _DTRACE3_(" GgafDxTextureManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}

