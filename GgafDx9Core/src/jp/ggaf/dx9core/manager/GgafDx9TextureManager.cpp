#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9TextureManager::GgafDx9TextureManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Texture> (prm_manager_name) {
}

GgafDx9Texture* GgafDx9TextureManager::processCreateResource(char* prm_idstr) {
    GgafDx9Texture* pResourceTexture;
    pResourceTexture = NEW GgafDx9Texture(prm_idstr);
    TRACE3(" GgafDx9TextureManager::processCreateResource "<<prm_idstr<<" �̃e�N�X�`���������܂����B");
    return pResourceTexture;
}

GgafResourceConnection<GgafDx9Texture>* GgafDx9TextureManager::processCreateConnection(char* prm_idstr, GgafDx9Texture* prm_pResource) {
    TRACE3(" GgafDx9TextureManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDx9TextureConnection* pConnection = NEW GgafDx9TextureConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9TextureManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}

