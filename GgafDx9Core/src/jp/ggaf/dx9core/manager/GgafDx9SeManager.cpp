#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SeManager::GgafDx9SeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Se> (prm_manager_name) {
}

GgafDx9Se* GgafDx9SeManager::processCreateResource(char* prm_idstr) {
    // prm_idstr = "1/laser" �̏ꍇ�A���f���}�l�[�W���[�̃L�[�ɂ�"1/laser"�œo�^��
    // �ǂݍ���wave�t�@�C����"laser.wav"�Ƃ���B
    // ����́A����wave�𕡐��`�����l���Ŗ炵�����ꍇ���A�ŏ��̐��l��ω�����΁A����������
    // �m�ۂ����Ǝ����Ӗ�����B

    GgafDx9Se* pResource = NULL;
    char idstr[129];
    strcpy(idstr, prm_idstr);
    char* pT = strtok(idstr, "/" );
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        pResource = NEW GgafDx9Se(prm_idstr);
    } else {
        pResource = NEW GgafDx9Se(pT);
    }

    return pResource;
}

GgafResourceConnection<GgafDx9Se>* GgafDx9SeManager::processCreateConnection(char* prm_idstr, GgafDx9Se* prm_pResource) {
    TRACE3(" GgafDx9SeManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDx9SeConnection* pConnection = NEW GgafDx9SeConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9SeManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}
