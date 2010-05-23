#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DispatcherManager::DispatcherManager(const char* prm_manager_name) :
    GgafResourceManager<GgafActorDispatcher> (prm_manager_name) {
}

GgafActorDispatcher* DispatcherManager::processCreateResource(char* prm_idstr) {
    GgafActorDispatcher* pResource = NULL;

    if (GgafUtil::strcmp_ascii("DpCon_Shot001", prm_idstr) == 0) {
        pResource = NEW GgafActorDispatcher("DP_Shot001_Stock");
        Shot001* pShot001;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot001 = NEW Shot001("Shot001");
            pShot001->inactivateImmediately();
            pResource->addSubLast(pShot001);
        }
        pCOMMONSCENE->getLordActor()->addSubGroup(pResource); //最後にaddSubGroupすべし（さもないと直ぐに削除対象になる）
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorDispatcher("DP_Shot002_Stock");
        Shot002* pShot002;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot002 = NEW Shot002("Shot002");
            pShot002->inactivateImmediately();
            pResource->addSubLast(pShot002);
        }
        pCOMMONSCENE->getLordActor()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorDispatcher("DP_Shot003_Stock");
        Shot003* pShot003;
        for (int i = 0; i < 300; i++) {
            pShot003 = NEW Shot003("Shot003");
            pShot003->inactivateImmediately();
            pResource->addSubLast(pShot003);
        }
        pCOMMONSCENE->getLordActor()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot004", prm_idstr) == 0) {
        pResource = NEW GgafActorDispatcher("DP_Shot004_Stock");
        Shot004* pShot004;
        for (int i = 0; i < 600; i++) {
            pShot004 = NEW Shot004("Shot004");
            pShot004->inactivateImmediately();
            pResource->addSubLast(pShot004);
        }
        pCOMMONSCENE->getLordActor()->addSubGroup(pResource);
    }

    return pResource;
}

GgafResourceConnection<GgafActorDispatcher>* DispatcherManager::processCreateConnection(char* prm_idstr, GgafActorDispatcher* prm_pResource) {
    TRACE3(" DispatcherManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    DispatcherConnection* pConnection = NEW DispatcherConnection(prm_idstr, prm_pResource);
    TRACE3(" DispatcherManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
