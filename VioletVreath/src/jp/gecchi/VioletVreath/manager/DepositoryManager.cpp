#include "stdafx.h"
#include "DepositoryManager.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryConnection.h"

#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DepositoryManager::DepositoryManager(const char* prm_manager_name) :
    GgafResourceManager<GgafActorDepository> (prm_manager_name) {
}

GgafActorDepository* DepositoryManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    GgafActorDepository* pResource = nullptr;

    if (UTIL::strcmp_ascii("Shot001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot001Stock");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW Shot001("Shot001"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource); //最後にaddSubGroupすべし（さもないと直ぐに削除対象になる）

    } else if (UTIL::strcmp_ascii("Shot002", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot002Stock");
        for (int i = 0; i < 100; i++) { //ストック100個
            pResource->addSubLast(NEW Shot002("Shot002"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("Shot003", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot003Stock");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW Shot003("Shot003"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    } else if (UTIL::strcmp_ascii("Shot004Blue", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004BlueStock");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW Shot004Blue("Shot004Blue"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("Shot004Yellow", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_Shot004YellowStock");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EffRefraction001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_EffRefraction001");
        for (int i = 0; i < 100; i++) {
            pResource->addSubLast(NEW EffectLaserRefraction001("EffRefraction001"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyStraeaLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyStraeaLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            std::string name1 = "LaserChipDepository["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name2 = "EnemyStraeaLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->addSubLast(NEW EnemyStraeaLaserChip001(name2.c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyStraeaLaserChip002DepoStore", prm_idstr) == 0) {
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

                pLaserChipDepo->addSubLast(pChip);
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyStraeaLaserChip003DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyStraeaLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 30; nLaser++) {
            std::string name1 = "LaserChipDepository["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name2 = "EnemyStraeaLaserChip003["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->addSubLast(NEW EnemyStraeaLaserChip003(name2.c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyStraeaLaserChip004DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyStraeaLaserChip004DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 30; nLaser++) {
            std::string name1 = "LaserChipDepository["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name2 = "EnemyStraeaLaserChip004["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->addSubLast(NEW EnemyStraeaLaserChip004(name2.c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyUnomia4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("EnemyUnomiaDepo");
        for (int i = 0; i < 800; i++) {
            pResource->addSubLast(NEW EnemyUnomia("Unomia"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("Emilia", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Emilia");
        for (int i = 0; i < 200; i++) {
            pResource->addSubLast(NEW EnemyEmilia("EnemyEmilia"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EmiliaFragment", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_EmiliaFragment");
        for (int i = 0; i < 200; i++) {
            pResource->addSubLast(NEW EnemyEmiliaFragment("EMF"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EmiliaFragment2", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_EmiliaFragment2");
        for (int i = 0; i < 300; i++) {
            pResource->addSubLast(NEW EnemyEmiliaFragment2("EMF2"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EmiliaFragment3", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_EmiliaFragment3");
        for (int i = 0; i < 400; i++) {
            pResource->addSubLast(NEW EnemyEmiliaFragment3("EMF3"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyEbe4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Deop_Ebe");
        for (int i = 0; i < RF_FormationEbe_Num(2.0); i++) {
            pResource->addSubLast(NEW EnemyEbe("EnemyEmilia"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyEsperiaLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyEsperiaLaserChip0014DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < RF_EnemyEsperia_ShotWay(1.0)*8; nLaser++) {
            std::string name1 = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                std::string name2 = "EnemyEsperiaLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->addSubLast(NEW EnemyEsperiaLaserChip001(name2.c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("Talante", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_TalanteStock");
        for (int i = 0; i < 2000; i++) {
            std::string name = "EnemyTalante("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyTalante(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyEmusLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyEmusLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 20; nLaser++) { //２０本
            std::string name1 = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 100; nChip++) {
                std::string name2 = "EnemyEmusLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                pLaserChipDepo->addSubLast(NEW EnemyEmusLaserChip001(name2.c_str()));
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyHisbeLaserChip001DepoStore", prm_idstr) == 0) {
        pResource = NEW GgafActorDepositoryStore("EnemyEmusLaserChip001DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 3; nLaser++) { //２本
            std::string name2 = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name2.c_str());
            for (int nChip = 0; nChip < 300; nChip++) {
                std::string name3 = "EnemyHisbeLaserChip001["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                EnemyHisbeLaserChip001* pChip = NEW EnemyHisbeLaserChip001(name3.c_str());
                pChip->_is_fix_begin_pos = false;
                pLaserChipDepo->addSubLast(pChip);
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyHisbeLaserChip002DepoStore", prm_idstr) == 0) {
        GgafActorDepository* pDepoEffect = NEW GgafActorDepository("HisbeLaser");
        EffectLaserRefraction001* pEffect;
        for (int i = 0; i < 200; i++) {
            std::string name = "EffectLaserRefraction001["+XTOS(i)+"]";
            pEffect = NEW EffectLaserRefraction001(name.c_str());
            pDepoEffect->addSubLast(pEffect);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepoEffect);

        pResource = NEW GgafActorDepositoryStore("EnemyEmusLaserChip002DepoStore");
        LaserChipDepository* pLaserChipDepo;
        for (int nLaser = 0; nLaser < 40; nLaser++) { //4本
            std::string name1 = "LaserChipDepo["+XTOS(nLaser)+"]";
            pLaserChipDepo = NEW LaserChipDepository(name1.c_str());
            for (int nChip = 0; nChip < 200; nChip++) {
                std::string name2 = "EnemyHisbeLaserChip002["+XTOS(nLaser)+"]["+XTOS(nChip)+"]";
                EnemyHisbeLaserChip002* pChip = NEW EnemyHisbeLaserChip002(name2.c_str());
                int num_refraction = pChip->pKurokoLeader_->getPointNum();
                pChip->config(num_refraction, 1, 1, false, pDepoEffect);
                pLaserChipDepo->addSubLast(pChip);
                Sleep(1);
            }
            pResource->addSubLast(pLaserChipDepo);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("AntiopeP", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AntiopeP");
        for (int i = 0; i < 120; i++) {
            std::string name = "AntiopeP("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyAntiopeP(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("AntiopeN", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_AntiopeN");
        for (int i = 0; i < 120; i++) {
            std::string name = "AntiopeN("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyAntiopeP(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyDelheid4Formation", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_DelheidStock");
        for (int i = 0; i < 300; i++) {
            std::string name = "EnemyDelheid("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyDelheid(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("EnemyDelheidShot", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_DelheidShotStock");
        for (int i = 0; i < 400; i++) {
            pResource->addSubLast(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("RingShot", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("MgrDepo_DelheidShotStock");
        for (int i = 0; i < 400; i++) {
            pResource->addSubLast(NEW Shot004Yellow("Shot004Yellow"));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);

    } else if (UTIL::strcmp_ascii("GlajaLance001", prm_idstr) == 0) {
        pResource = NEW GgafActorDepository("Depo_EnemyGlajaLance001");
        for (int i = 0; i < 40; i++) {
            std::string name = "GlajaLance001("+XTOS(i)+")";
            pResource->addSubLast(NEW EnemyGlajaLance001(name.c_str()));
            Sleep(1);
        }
        P_COMMON_SCENE->getSceneDirector()->addSubGroup(pResource);
    }

    if (pResource == nullptr) {
        throwGgafCriticalException("DepositoryManager::processCreateResource("<<prm_idstr<<") 想定外のIDです。Depositoryが作成できません。");
    }
    return pResource;
}

GgafResourceConnection<GgafActorDepository>* DepositoryManager::processCreateConnection(char* prm_idstr, GgafActorDepository* prm_pResource) {
    TRACE3(" DepositoryManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    DepositoryConnection* pConne = NEW DepositoryConnection(prm_idstr, prm_pResource);
    TRACE3(" DepositoryManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}
