#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxTextureManager::GgafDxTextureManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxTexture> (prm_manager_name) {
}

GgafDxTexture* GgafDxTextureManager::processCreateResource(char* prm_idstr, void* prm_p) {
    GgafDxTexture* pResourceTexture;
    pResourceTexture = NEW GgafDxTexture(prm_idstr);
    TRACE3(" GgafDxTextureManager::processCreateResource "<<prm_idstr<<" �̃e�N�X�`���������܂����B");
    return pResourceTexture;
}

void GgafDxTextureManager::releaseAll() {
    _TRACE_("GgafDxTextureManager::releaseAll() start-->");
    GgafResourceConnection<GgafDxTexture>* pCurrent = _pConnection_first;
    while (pCurrent) {
        pCurrent->peek()->release();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_("GgafDxTextureManager::releaseAll() end<--");
}

void GgafDxTextureManager::restoreAll() {
    _TRACE_("GgafDxTextureManager::restoreAll() start-->");
    GgafResourceConnection<GgafDxTexture>* pCurrent = _pConnection_first;
    while (pCurrent) {
        pCurrent->peek()->restore();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_("GgafDxTextureManager::restoreAll() end<--");
}

GgafResourceConnection<GgafDxTexture>* GgafDxTextureManager::processCreateConnection(char* prm_idstr, GgafDxTexture* prm_pResource) {
    TRACE3(" GgafDxTextureManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxTextureConnection* pConnection = NEW GgafDxTextureConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDxTextureManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}

