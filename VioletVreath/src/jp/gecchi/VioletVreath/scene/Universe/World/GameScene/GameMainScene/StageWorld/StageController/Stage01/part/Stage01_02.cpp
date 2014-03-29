#include "stdafx.h"
#include "Stage01_02.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4300,4500,4700,4900,5000,5100,6000,6100,7000,7100,8000,8100,8300,8600,9000,9100,9200,9500,10000};
    _paFrame_NextEvent = new frame[61];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 61;
    orderActorToFactory(40000000, EnemyEtis, "EnemyEtis-1");
    orderActorToFactory(40000001, EnemyEtis, "EnemyEtis-2");
    orderActorToFactory(40000002, EnemyEtis, "EnemyEtis-3");
    orderActorToFactory(40000003, EnemyEtis, "EnemyEtis-4");
    orderActorToFactory(40000004, EnemyEtis, "EnemyEtis-5");
    // gen01 end

    getBGMer()->useBgm(1);
    getBGMer()->set(0, "OGG_BGM_01_02");
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getBehaveingFrame()) {
            case 1: {
                break;
            }
            case 100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000000);
                getSceneDirector()->addSubGroup(pEtis);
                orderActorToFactory(40000025, VarietyRatislavia001, "VarietyRatislavia001-6");
                orderActorToFactory(40000043, FormationHalia, "FormationHalia-7");
                orderActorToFactory(40000054, FormationEbe001, "FormationEbe001-8");
                break;
            }
            case 200: {
                orderActorToFactory(40000005, EnemyEtis, "EnemyEtis-9");
                break;
            }
            case 300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000001);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 400: {
                orderActorToFactory(40000006, EnemyEtis, "EnemyEtis-10");
                break;
            }
            case 500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000002);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 600: {
                orderActorToFactory(40000007, EnemyEtis, "EnemyEtis-11");
                break;
            }
            case 700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000003);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 800: {
                orderActorToFactory(40000008, EnemyEtis, "EnemyEtis-12");
                break;
            }
            case 900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000004);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 1000: {
                orderActorToFactory(40000009, EnemyEtis, "EnemyEtis-13");
                VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(40000025);
                getSceneDirector()->addSubGroup(pRatislavia);
                FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000043);
                getSceneDirector()->addSubGroup(pF);
                FormationEbe001* pF14 = (FormationEbe001*)obtainActorFromFactory(40000054);
                getSceneDirector()->addSubGroup(pF14);
                break;
            }
            case 1100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000005);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 1200: {
                orderActorToFactory(40000010, EnemyEtis, "EnemyEtis-15");
                break;
            }
            case 1300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000006);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 1400: {
                orderActorToFactory(40000011, EnemyEtis, "EnemyEtis-16");
                orderActorToFactory(40000026, EnemyStraea, "EnemyStraea-17");
                break;
            }
            case 1500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000007);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 1600: {
                orderActorToFactory(40000012, EnemyEtis, "EnemyEtis-18");
                orderActorToFactory(40000027, FormationEmilia, "FormationEmilia-19");
                break;
            }
            case 1700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000008);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 1800: {
                orderActorToFactory(40000013, EnemyEtis, "EnemyEtis-20");
                orderActorToFactory(40000029, FormationAllas001a, "FormationAllas001a-21");
                orderActorToFactory(40000030, FormationAllas001b, "FormationAllas001b-22");
                orderActorToFactory(40000031, FormationAllas001c, "FormationAllas001c-23");
                orderActorToFactory(40000032, FormationAllas001d, "FormationAllas001d-24");
                orderActorToFactory(40000033, FormationAllas001a, "FormationAllas001a-25");
                orderActorToFactory(40000034, FormationAllas001d, "FormationAllas001d-26");
                orderActorToFactory(40000035, FormationAllas001b, "FormationAllas001b-27");
                orderActorToFactory(40000036, FormationAllas001c, "FormationAllas001c-28");
                orderActorToFactory(40000037, FormationAllas001a, "FormationAllas001a-29");
                orderActorToFactory(40000038, FormationAllas001d, "FormationAllas001d-30");
                orderActorToFactory(40000039, FormationAllas001b, "FormationAllas001b-31");
                orderActorToFactory(40000040, FormationAllas001c, "FormationAllas001c-32");
                break;
            }
            case 1900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000009);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 2000: {
                orderActorToFactory(40000014, EnemyEtis, "EnemyEtis-33");
                break;
            }
            case 2100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000010);
                getSceneDirector()->addSubGroup(pEtis);
                orderActorToFactory(40000041, FormationGeria001, "FormationGeria001-34");
                break;
            }
            case 2200: {
                orderActorToFactory(40000015, EnemyEtis, "EnemyEtis-35");
                break;
            }
            case 2300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000011);
                getSceneDirector()->addSubGroup(pEtis);
                EnemyStraea* pStraea2 = (EnemyStraea*)obtainActorFromFactory(40000026);
                getSceneDirector()->addSubGroup(pStraea2);
                pStraea2->_z = 1800000;
                pStraea2->_y = -100000;
                break;
            }
            case 2400: {
                orderActorToFactory(40000016, EnemyEtis, "EnemyEtis-36");
                break;
            }
            case 2500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000012);
                getSceneDirector()->addSubGroup(pEtis);
                FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(40000027);
                getSceneDirector()->addSubGroup(pFormationEmilia);
                break;
            }
            case 2600: {
                orderActorToFactory(40000017, EnemyEtis, "EnemyEtis-37");
                break;
            }
            case 2700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000013);
                getSceneDirector()->addSubGroup(pEtis);
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-38");
                ta->setMaxPerformFrame(2500);
                addSubLast(ta);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(40000029)), 400);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(40000030)), 400);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(40000031)), 400);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(40000032)), 400);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(40000033)), 1);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(40000034)), 400);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(40000035)), 1);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(40000036)), 400);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(40000037)), 1);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(40000038)), 1);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(40000039)), 1);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(40000040)), 400);
                }
                break;
            }
            case 2800: {
                orderActorToFactory(40000018, EnemyEtis, "EnemyEtis-39");
                break;
            }
            case 2900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000014);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 3000: {
                orderActorToFactory(40000019, EnemyEtis, "EnemyEtis-40");
                FormationGeria001* pF41 = (FormationGeria001*)obtainActorFromFactory(40000041);
                getSceneDirector()->addSubGroup(pF41);
                break;
            }
            case 3100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000015);
                getSceneDirector()->addSubGroup(pEtis);
                orderActorToFactory(40000042, VarietyRatislavia001, "VarietyRatislavia001-42");
                break;
            }
            case 3200: {
                orderActorToFactory(40000020, EnemyEtis, "EnemyEtis-43");
                break;
            }
            case 3300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000016);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 3400: {
                orderActorToFactory(40000021, EnemyEtis, "EnemyEtis-44");
                break;
            }
            case 3500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000017);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 3600: {
                orderActorToFactory(40000022, EnemyEtis, "EnemyEtis-45");
                break;
            }
            case 3700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000018);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 3800: {
                orderActorToFactory(40000023, EnemyEtis, "EnemyEtis-46");
                break;
            }
            case 3900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000019);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 4000: {
                orderActorToFactory(40000024, EnemyEtis, "EnemyEtis-47");
                VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(40000042);
                getSceneDirector()->addSubGroup(pRatislavia);
                break;
            }
            case 4100: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000020);
                getSceneDirector()->addSubGroup(pEtis);
                orderActorToFactory(40000044, FormationHalia, "FormationHalia-48");
                orderActorToFactory(40000055, EnemyEsperia, "EnemyEsperia-49");
                break;
            }
            case 4300: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000021);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 4500: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000022);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 4700: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000023);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 4900: {
                EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000024);
                getSceneDirector()->addSubGroup(pEtis);
                break;
            }
            case 5000: {
                FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000044);
                getSceneDirector()->addSubGroup(pF);
                EnemyEsperia* p50 = (EnemyEsperia*)obtainActorFromFactory(40000055);
                getSceneDirector()->addSubGroup(p50);
                break;
            }
            case 5100: {
                orderActorToFactory(40000056, EnemyEsperia, "EnemyEsperia-51");
                break;
            }
            case 6000: {
                EnemyEsperia* p52 = (EnemyEsperia*)obtainActorFromFactory(40000056);
                getSceneDirector()->addSubGroup(p52);
                break;
            }
            case 6100: {
                orderActorToFactory(40000057, EnemyEsperia, "EnemyEsperia-53");
                break;
            }
            case 7000: {
                EnemyEsperia* p54 = (EnemyEsperia*)obtainActorFromFactory(40000057);
                getSceneDirector()->addSubGroup(p54);
                break;
            }
            case 7100: {
                orderActorToFactory(40000058, EnemyEsperia, "EnemyEsperia-55");
                break;
            }
            case 8000: {
                EnemyEsperia* p56 = (EnemyEsperia*)obtainActorFromFactory(40000058);
                getSceneDirector()->addSubGroup(p56);
                break;
            }
            case 8100: {
                orderActorToFactory(40000045, FormationHalia, "FormationHalia-57");
                orderActorToFactory(40000059, EnemyEsperia, "EnemyEsperia-58");
                break;
            }
            case 8300: {
                orderActorToFactory(40000047, FormationRis002, "FormationRis002-59");
                orderActorToFactory(40000048, FormationRis001, "FormationRis001-60");
                orderActorToFactory(40000049, FormationRis001, "FormationRis001-61");
                orderActorToFactory(40000050, FormationRis002, "FormationRis002-62");
                orderActorToFactory(40000051, FormationRis001, "FormationRis001-63");
                orderActorToFactory(40000052, FormationRis002, "FormationRis002-64");
                break;
            }
            case 8600: {
                orderActorToFactory(40000053, EnemyIrce, "EnemyIrce-65");
                break;
            }
            case 9000: {
                FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000045);
                getSceneDirector()->addSubGroup(pF);
                EnemyEsperia* p66 = (EnemyEsperia*)obtainActorFromFactory(40000059);
                getSceneDirector()->addSubGroup(p66);
                break;
            }
            case 9100: {
                orderActorToFactory(40000060, EnemyEsperia, "EnemyEsperia-67");
                break;
            }
            case 9200: {
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-68");
                ta->setMaxPerformFrame(2000);
                addSubLast(ta);
                ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000047)), 400);
                ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000048)), 400);
                ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000049)), 400);
                ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000050)), 400);
                ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000051)), 400);
                ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000052)), 400);
                }
                break;
            }
            case 9500: {
                EnemyIrce* p69 = (EnemyIrce*)obtainActorFromFactory(40000053);
                getSceneDirector()->addSubGroup(p69);
                break;
            }
            case 10000: {
                EnemyEsperia* p70 = (EnemyEsperia*)obtainActorFromFactory(40000060);
                getSceneDirector()->addSubGroup(p70);
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 61-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end


    if (getBehaveingFrame() == 1 && P_GAME_SCENE->getProgress()->get() == GameScene::PROG_MAIN) {
        //兄弟シーンのBGMを全てフェードアウトし、自分のシーンBGMをフェードイン
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeout_stop_AllPartSceneBgm();
        getBGMer()->play_fadein(0);
    }
    if (getBehaveingFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        getBGMer()->fadeout_stop(0);
        throwEventUpperTree(EVENT_STG01_02_WAS_BROKEN);
    }
}

Stage01_02::~Stage01_02() {

}
