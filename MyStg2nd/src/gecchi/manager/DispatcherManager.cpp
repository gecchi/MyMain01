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
        P_COMMON_SCENE->getLordActor()->addSubGroup(pResource); //最後にaddSubGroupすべし（さもないと直ぐに削除対象になる）
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorDispatcher("DP_Shot002_Stock");
        Shot002* pShot002;
        for (int i = 0; i < 100; i++) { //ストック100個
            pShot002 = NEW Shot002("Shot002");
            pShot002->inactivateImmediately();
            pResource->addSubLast(pShot002);
        }
        P_COMMON_SCENE->getLordActor()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorDispatcher("DP_Shot003_Stock");
        Shot003* pShot003;
        for (int i = 0; i < 300; i++) {
            pShot003 = NEW Shot003("Shot003");
            pShot003->inactivateImmediately();
            pResource->addSubLast(pShot003);
            if (i % 20 == 0) { Sleep(1); }
        }
        P_COMMON_SCENE->getLordActor()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_Shot004", prm_idstr) == 0) {
        pResource = NEW GgafActorDispatcher("DP_Shot004_Stock");
        Shot004* pShot004;
        for (int i = 0; i < 2500; i++) {
            pShot004 = NEW Shot004("Shot004");
            pShot004->inactivateImmediately();
            pResource->addSubLast(pShot004);
            if (i % 20 == 0) { Sleep(1); }
        }
        P_COMMON_SCENE->getLordActor()->addSubGroup(pResource);
    }

    if (GgafUtil::strcmp_ascii("DpCon_EffRefraction001", prm_idstr) == 0) {
        pResource = NEW GgafActorDispatcher("DP_EffRefraction001");
        EffectLaserRefraction001* p;
        for (int i = 0; i < 100; i++) {
            p = NEW EffectLaserRefraction001("Shot004");
            p->inactivateImmediately();
            pResource->addSubLast(p);
        }
        P_COMMON_SCENE->getLordActor()->addSubGroup(pResource);
    }

    //敵カーブレーザー01未使用。こぴぺのために残す
	/*
    if (GgafUtil::strcmp_ascii("DpCon_EneCurveLaser001Dp", prm_idstr) == 0) {
        pResource = NEW LaserChipDispatcherDispatcher("DPDP_EneCurveLaser001");
        LaserChipDispatcher* pLaserChipDispatcher;
        EnemyCurveLaserChip001* pChip;
        for (int set = 0; set < 20; set++) {
            stringstream name;
            name <<  "EneCurveLaser001Dp["<<set<<"]";
            pLaserChipDispatcher = NEW LaserChipDispatcher(name.str().c_str());
            for (int n = 0; n < 50; n++) {
                stringstream name;
                name <<  "EneCurveLaser001["<<set<<"]["<<n<<"]";
                pChip = NEW EnemyCurveLaserChip001(name.str().c_str());
                pChip->inactivateImmediately();
                pLaserChipDispatcher->addSubLast(pChip);
                if (n % 20 == 0) { Sleep(1); }
            }
            pLaserChipDispatcher->inactivateImmediately();
            pResource->addSubLast(pLaserChipDispatcher);

        }
        P_COMMON_SCENE->getLordActor()->addSubGroup(pResource);
    }
*/

    if (pResource == NULL) {
        throwGgafCriticalException("DispatcherManager::processCreateResource("<<prm_idstr<<") 想定外のIDです。Dispatcherが作成できません。");
    } else {
        return pResource;
    }
}

GgafResourceConnection<GgafActorDispatcher>* DispatcherManager::processCreateConnection(char* prm_idstr, GgafActorDispatcher* prm_pResource) {
    TRACE3(" DispatcherManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    DispatcherConnection* pConnection = NEW DispatcherConnection(prm_idstr, prm_pResource);
    TRACE3(" DispatcherManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
