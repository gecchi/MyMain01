#include "jp/ggaf/dx/manager/TextureManager.h"

#include "jp/ggaf/dx/manager/TextureConnection.h"


using namespace GgafDx;

TextureManager::TextureManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<Texture> (prm_manager_name) {
}

Texture* TextureManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    Texture* pResourceTexture;
    pResourceTexture = NEW Texture(prm_idstr);
    _TRACE3_("prm_idstr="<<prm_idstr<<" のテクスチャ生成しました。");
    return pResourceTexture;
}

void TextureManager::releaseAll() {
    _TRACE_(FUNC_NAME<<" start-->");
    GgafCore::ResourceConnection<Texture>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->release();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_(FUNC_NAME<<" end<--");
}

void TextureManager::restoreAll() {
    _TRACE_(FUNC_NAME<<" start-->");
    GgafCore::ResourceConnection<Texture>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->restore();
        pCurrent = pCurrent->getNext();
    }
    _TRACE_(FUNC_NAME<<" end<--");
}

GgafCore::ResourceConnection<Texture>* TextureManager::processCreateConnection(const char* prm_idstr, Texture* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    TextureConnection* pConne = NEW TextureConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}

