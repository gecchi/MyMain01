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
    _TRACE3_(" GgafDxTextureManager::processCreateResource "<<prm_idstr<<" �̃e�N�X�`���������܂����B");
    return pResourceTexture;
}

void GgafDxTextureManager::releaseAll() {
    _TRACE_("GgafDxTextureManager::releaseAll() start-->");
    GgafResourceConnection<GgafDxTexture>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->release();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_("GgafDxTextureManager::releaseAll() end<--");
}

void GgafDxTextureManager::restoreAll() {
    _TRACE_("GgafDxTextureManager::restoreAll() start-->");
    GgafResourceConnection<GgafDxTexture>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->restore();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_("GgafDxTextureManager::restoreAll() end<--");
}

GgafResourceConnection<GgafDxTexture>* GgafDxTextureManager::processCreateConnection(const char* prm_idstr, GgafDxTexture* prm_pResource) {
    _TRACE3_(" GgafDxTextureManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxTextureConnection* pConne = NEW GgafDxTextureConnection(prm_idstr, prm_pResource);
    _TRACE3_(" GgafDxTextureManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}

