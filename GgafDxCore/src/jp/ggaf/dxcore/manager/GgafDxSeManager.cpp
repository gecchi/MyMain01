#include "jp/ggaf/dxcore/manager/GgafDxSeManager.h"

#include <cstring>
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSeManager::GgafDxSeManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxSe> (prm_manager_name) {
}

GgafDxSe* GgafDxSeManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    // prm_idstr = "1/laser" �̏ꍇ�A���f���}�l�[�W���[�̃L�[�ɂ�"1/laser"�œo�^����邱�ƂɂȂ�B
    // �������A�ǂݍ���wave�t�@�C����"laser.wav"�Ƃ���B
    // ����́A����wave�𕡐��`�����l���Ŗ炵�����ꍇ���A�ŏ��̐��l��ω�����΁A����������
    // �m�ۂ����Ǝ����Ӗ�����B

    GgafDxSe* pResource = nullptr;
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, "/", 1); //�ŏ��̃X���b�V���ŕ���
    if (names.size() == 2) {
        pResource = NEW GgafDxSe(names[1].c_str());
    } else {
        pResource = NEW GgafDxSe(names[0].c_str());
    }
    return pResource;
}

void GgafDxSeManager::updateVolume() {
    while (_is_connecting_resource) {
        Sleep(1);
    }
    GgafDxSeConnection* pConne = (GgafDxSeConnection*)_pConn_first;
    while (pConne) {
        pConne->peek()->setVolume(GGAF_MAX_VOLUME);
        while (_is_connecting_resource) { //�ȈՔr��
            Sleep(1);
        }
        pConne = (GgafDxSeConnection*)(pConne->getNext());
    }
}

GgafResourceConnection<GgafDxSe>* GgafDxSeManager::processCreateConnection(const char* prm_idstr, GgafDxSe* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxSeConnection* pConne = NEW GgafDxSeConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}
