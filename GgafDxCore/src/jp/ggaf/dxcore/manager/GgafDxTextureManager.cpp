#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxTextureManager::GgafDxTextureManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxTexture> (prm_manager_name) {
}

GgafDxTexture* GgafDxTextureManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    GgafDxTexture* pResourceTexture;
    pResourceTexture = NEW GgafDxTexture(prm_idstr);
    _TRACE3_("prm_idstr="<<prm_idstr<<" のテクスチャ生成しました。");
    return pResourceTexture;
}

void GgafDxTextureManager::releaseAll() {
    _TRACE_("start-->");
    GgafResourceConnection<GgafDxTexture>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->release();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_("end<--");
}

void GgafDxTextureManager::restoreAll() {
    _TRACE_("start-->");
    GgafResourceConnection<GgafDxTexture>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->restore();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_("end<--");
}

GgafResourceConnection<GgafDxTexture>* GgafDxTextureManager::processCreateConnection(const char* prm_idstr, GgafDxTexture* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    GgafDxTextureConnection* pConne = NEW GgafDxTextureConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}

