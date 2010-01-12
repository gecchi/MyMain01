#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DispatcherManager::DispatcherManager(const char* prm_manager_name) :
    GgafResourceManager<ActorDispatcher> (prm_manager_name) {
}

ActorDispatcher* DispatcherManager::processCreateResource(char* prm_idstr) {
    ActorDispatcher* pResource = NULL;

    if (GgafUtil::strcmp_ascii("DpCon_Shot001", prm_idstr) == 0) {
        pResource = NEW ActorDispatcher("DP_Shot001");
        Shot001* pShot001;
        for (int i = 0; i < 100; i++) { //�X�g�b�N100��
            pShot001 = NEW Shot001("Shot001");
            pShot001->inactivateImmediately();
            pResource->addSubLast(pShot001);
        }
        pCOMMONSCENE->getLordActor()->addSubGroup(KIND_ENEMY_SHOT_NOMAL, pResource); //�Ō��addSubGroup���ׂ��i�����Ȃ��ƒ����ɍ폜�ΏۂɂȂ�j
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot002", prm_idstr) == 0) {
        pResource = NEW ActorDispatcher("DP_Shot002");
        Shot002* pShot002;
        for (int i = 0; i < 100; i++) { //�X�g�b�N100��
            pShot002 = NEW Shot002("Shot002");
            pShot002->inactivateImmediately();
            pResource->addSubLast(pShot002);
        }
        pCOMMONSCENE->getLordActor()->addSubGroup(KIND_ENEMY_SHOT_GU, pResource);
    }

    return pResource;
}

GgafResourceConnection<ActorDispatcher>* DispatcherManager::processCreateConnection(char* prm_idstr, ActorDispatcher* prm_pResource) {
    TRACE3(" DispatcherManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    DispatcherConnection* pConnection = NEW DispatcherConnection(prm_idstr, prm_pResource);
    TRACE3(" DispatcherManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}
