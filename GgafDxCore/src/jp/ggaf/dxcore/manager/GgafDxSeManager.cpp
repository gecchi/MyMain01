#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeManager::GgafDxSeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxSe> (prm_manager_name) {
}

GgafDxSe* GgafDxSeManager::processCreateResource(char* prm_idstr, void* prm_p) {
    // prm_idstr = "1/laser" �̏ꍇ�A���f���}�l�[�W���[�̃L�[�ɂ�"1/laser"�œo�^��
    // �ǂݍ���wave�t�@�C����"laser.wav"�Ƃ���B
    // ����́A����wave�𕡐��`�����l���Ŗ炵�����ꍇ���A�ŏ��̐��l��ω�����΁A����������
    // �m�ۂ����Ǝ����Ӗ�����B

    GgafDxSe* pResource = NULL;
    char idstr[129];
    strcpy(idstr, prm_idstr);
    char* pT = strtok(idstr, "/" );
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        pResource = NEW GgafDxSe(prm_idstr);
    } else {
        pResource = NEW GgafDxSe(pT);
    }

    return pResource;
}

GgafResourceConnection<GgafDxSe>* GgafDxSeManager::processCreateConnection(char* prm_idstr, GgafDxSe* prm_pResource) {
    TRACE3(" GgafDxSeManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxSeConnection* pConnection = NEW GgafDxSeConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDxSeManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}
