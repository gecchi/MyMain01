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

    if (GgafUtil::strcmp_ascii("Shot001", prm_idstr) == 0) {
        pResource = NEW ActorDispatcher("DP_Shot001");
        pGAMESCENE->getLordActor()->addSubGroup(KIND_ENEMY_SHOT_GU, pResource);
        Shot001* pShot001;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot001 = NEW Shot001("Shot001");
            pShot001->inactivateImmediately();
            pResource->addSubLast(pShot001);
        }
    }
    return pResource;
}

GgafResourceConnection<ActorDispatcher>* DispatcherManager::processCreateConnection(char* prm_idstr, ActorDispatcher* prm_pResource) {
    TRACE3(" DispatcherManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    DispatcherConnection* pConnection = NEW DispatcherConnection(prm_idstr, prm_pResource);
    TRACE3(" DispatcherManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
