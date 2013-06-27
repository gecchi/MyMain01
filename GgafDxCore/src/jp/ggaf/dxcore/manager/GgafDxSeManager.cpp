#include "stdafx.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeManager.h"

#include <cstring>
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeManager::GgafDxSeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxSe> (prm_manager_name) {
}

GgafDxSe* GgafDxSeManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    // prm_idstr = "1/laser" �̏ꍇ�A���f���}�l�[�W���[�̃L�[�ɂ�"1/laser"�œo�^��
    // �ǂݍ���wave�t�@�C����"laser.wav"�Ƃ���B
    // ����́A����wave�𕡐��`�����l���Ŗ炵�����ꍇ���A�ŏ��̐��l��ω�����΁A����������
    // �m�ۂ����Ǝ����Ӗ�����B

    GgafDxSe* pResource = nullptr;
    char idstr[129];
    strcpy(idstr, prm_idstr);
    char* pT = strtok(idstr, "/" );
    pT = strtok(nullptr, "/");
    if (pT == nullptr) {
        pResource = NEW GgafDxSe(prm_idstr);
    } else {
        pResource = NEW GgafDxSe(pT);
    }

    return pResource;
}

void GgafDxSeManager::updateVolume() {
    while(_is_connecting_resource) {
        Sleep(1);
    }
    GgafDxSeConnection* pConne = (GgafDxSeConnection*)_pConn_first;
    while (pConne) {
        pConne->peek()->setVolume(GGAF_MAX_VOLUME);
        while(_is_connecting_resource) { //�ȈՔr��
            Sleep(1);
        }
        pConne = (GgafDxSeConnection*)(pConne->getNext());
    }
}

GgafResourceConnection<GgafDxSe>* GgafDxSeManager::processCreateConnection(char* prm_idstr, GgafDxSe* prm_pResource) {
    TRACE3(" GgafDxSeManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxSeConnection* pConne = NEW GgafDxSeConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDxSeManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}
