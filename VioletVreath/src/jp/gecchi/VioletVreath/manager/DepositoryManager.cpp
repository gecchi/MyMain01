#include "DepositoryManager.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryConnection.h"

#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DepositoryManager::DepositoryManager(const char* prm_manager_name) :
    GgafResourceManager<GgafActorDepository> (prm_manager_name) {
}

GgafActorDepository* DepositoryManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    GgafActorDepository* pResource = nullptr;

    if (strcmp("Shot001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot001Stock");
        for (int i = 0; i < 100; i++) {
            pResource->put(NEW Shot001("Shot001"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource); //最後にappendGroupChildすべし（さもないと直ぐに削除対象になる）

    } else if (strcmp("Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot002Stock");
        for (int i = 0; i < 100; i++) { //ストック100個
            pResource->put(NEW Shot002("Shot002"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot003Stock");
        for (int i = 0; i < 100; i++) {
            pResource->put(NEW Shot003("Shot003"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);
    } else if (strcmp("Shot004Blue", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004BlueStock");
        for (int i = 0; i < 100; i++) {
            pResource->put(NEW Shot004Blue("Shot004Blue"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("Shot004Yellow", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004YellowStock");
        for (int i = 0; i < 100; i++) {
            pResource->put(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EffRefraction001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_EffRefraction001");
        for (int i = 0; i < 100; i++) {
            pResource->put(NEW EffectLaserRefraction001("EffRefraction001"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyStraeaLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyStraeaLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            std::string name1 = "LaserChipDepository["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name2 = "EnemyStraeaLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->put(NEW EnemyStraeaLaserChip001(name2.c_str()));
                Sleep(1);
            }
            pResource->put(pLaserChipDepo);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyStraeaLaserChip002DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyStraeaLaserChip002DepoStore");
        LaserChipDepository* pLaserChipDepo;
        EnemyStraeaLaserChip002* pChip;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            std::string name1 = "LaserChipDepository["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name2 = "EnemyStraeaLaserChip002["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pChip = NEW EnemyStraeaLaserChip002(name2.c_str());
                pChip->config(30, 20, 8, true, nullptr);

                pLaserChipDepo->put(pChip);
                Sleep(1);
            }
            pResource->put(pLaserChipDepo);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyStraeaLaserChip003DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyStraeaLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 30; nLaser++) {
            std::string name1 = "LaserChipDepository["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name2 = "EnemyStraeaLaserChip003["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->put(NEW EnemyStraeaLaserChip003(name2.c_str()));
                Sleep(1);
            }
            pResource->put(pLaserChipDepo);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyStraeaLaserChip004DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyStraeaLaserChip004DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 50; nLaser++) {
            std::string name1 = "LaserChipDepository["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 40; nChip++) {
                std::string name2 = "EnemyStraeaLaserChip004["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->put(NEW EnemyStraeaLaserChip004(name2.c_str()));
                Sleep(1);
            }
            pResource->put(pLaserChipDepo);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("Emilia", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Emilia");
        for (int i = 0; i < 200; i++) {
            pResource->put(NEW EnemyEmilia("EnemyEmilia"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EmiliaFragment", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_EmiliaFragment");
        for (int i = 0; i < 200; i++) {
            pResource->put(NEW EnemyEmiliaFragment("EMF"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EmiliaFragment2", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_EmiliaFragment2");
        for (int i = 0; i < 300; i++) {
            pResource->put(NEW EnemyEmiliaFragment2("EMF2"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EmiliaFragment3", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_EmiliaFragment3");
        for (int i = 0; i < 400; i++) {
            pResource->put(NEW EnemyEmiliaFragment3("EMF3"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyEbe4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Ebe");
        for (int i = 0; i < RF_FormationEbe_Num(2.0); i++) {
            pResource->put(NEW EnemyEbe("EnemyEmilia"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyEsperiaLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyEsperiaLaserChip0014DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < RF_EnemyEsperia_ShotWay(1.0)*5; nLaser++) {
            std::string name1 = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name2 = "EnemyEsperiaLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->put(NEW EnemyEsperiaLaserChip001(name2.c_str()));
                Sleep(1);
            }
            pResource->put(pLaserChipDepo);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("Talante", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_TalanteStock");
        for (int i = 0; i < 2000; i++) {
            std::string name = "EnemyTalante("+XTOS(i)+")";
            pResource->put(NEW EnemyTalante(name.c_str()));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyEmusLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyEmusLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 20; nLaser++) { //２０本
            std::string name1 = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 100; nChip++) {
                std::string name2 = "EnemyEmusLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->put(NEW EnemyEmusLaserChip001(name2.c_str()));
                Sleep(1);
            }
            pResource->put(pLaserChipDepo);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyHisbeLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyEmusLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 3; nLaser++) { //２本
            std::string name2 = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name2.c_str());
            for (int nChip = 0; nChip < 300; nChip++) {
                std::string name3 = "EnemyHisbeLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                EnemyHisbeLaserChip001* pChip = NEW EnemyHisbeLaserChip001(name3.c_str());
                pChip->_is_fix_begin_pos = false;
                pLaserChipDepo->put(pChip);
                Sleep(1);
            }
            pResource->put(pLaserChipDepo);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyHisbeLaserChip002DepoStore", prm_idstr) == 0) {
        GgafActorDepository* pDepoEffect = NEW GgafActorDepository("HisbeLaser");
        EffectLaserRefraction001* pEffect;
        for (int i = 0; i < 300; i++) {
            std::string name = "EffectLaserRefraction001["+XTOS(i)+"]";
            pEffect = NEW EffectLaserRefraction001(name.c_str());
            pDepoEffect->put(pEffect);
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pDepoEffect);

        pResource = NEW GgafActorDepositoryStore("EnemyHisbeLaserChip002DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 8; nLaser++) { //4本
            std::string name1 = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 200; nChip++) {
                std::string name2 = "EnemyHisbeLaserChip002["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                EnemyHisbeLaserChip002* pChip = NEW EnemyHisbeLaserChip002(name2.c_str());
                int num_refraction = pChip->pKurokoLeader_->getPointNum();
                pChip->config(num_refraction, 1, 1, false, pDepoEffect);
                pLaserChipDepo->put(pChip);
                Sleep(1);
            }
            pResource->put(pLaserChipDepo);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("AntiopeP", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AntiopeP");
        for (int i = 0; i < 120; i++) {
            std::string name = "AntiopeP("+XTOS(i)+")";
            pResource->put(NEW EnemyAntiopeP(name.c_str()));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("AntiopeN", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AntiopeN");
        for (int i = 0; i < 120; i++) {
            std::string name = "AntiopeN("+XTOS(i)+")";
            pResource->put(NEW EnemyAntiopeN(name.c_str()));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyDelheid4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_DelheidStock");
        for (int i = 0; i < 300; i++) {
            std::string name = "EnemyDelheid("+XTOS(i)+")";
            pResource->put(NEW EnemyDelheid(name.c_str()));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("EnemyDelheidShot", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_DelheidShotStock");
        for (int i = 0; i < 400; i++) {
            pResource->put(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("RingShot", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_DelheidShotStock");
        for (int i = 0; i < 400; i++) {
            pResource->put(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);

    } else if (strcmp("GlajaLance001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_EnemyGlajaLance001");
        for (int i = 0; i < 40; i++) {
            std::string name = "GlajaLance001("+XTOS(i)+")";
            pResource->put(NEW EnemyGlajaLance001(name.c_str()));
            Sleep(1);
        }
        pCOMMON_SCENE->bringSceneMediator()->appendGroupChild(pResource);
    }

    if (pResource == nullptr) {
        throwGgafCriticalException("想定外のIDです。Depositoryが作成できません。");
    }
    return pResource;
}

GgafResourceConnection<GgafActorDepository>* DepositoryManager::processCreateConnection(const char* prm_idstr, GgafActorDepository* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    DepositoryConnection* pConne = NEW DepositoryConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}
