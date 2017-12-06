#include "Stage01_01.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,500,1900,2400,2500,2900,3000,3400,3500,3900,4000,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6400,6500,6900,7000,7400,7500,7900,8000,8400,8500,8900,9000,9400,9500,10000};
    _paFrame_NextEvent = new frame[43];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 43;

    orderActorToFactory(20000001, FormationAllas001a, "FormationAllas001a-20000001");
    orderActorToFactory(20000002, FormationAllas001b, "FormationAllas001b-20000002");
    orderActorToFactory(20000003, FormationAllas001c, "FormationAllas001c-20000003");
    orderActorToFactory(20000004, FormationAllas001d, "FormationAllas001d-20000004");
    orderActorToFactory(20000005, FormationAllas001a, "FormationAllas001a-20000005");
    orderActorToFactory(20000006, FormationAllas001d, "FormationAllas001d-20000006");
    orderActorToFactory(20000007, FormationAllas001b, "FormationAllas001b-20000007");
    orderActorToFactory(20000008, FormationAllas001c, "FormationAllas001c-20000008");
    orderActorToFactory(20000009, FormationAllas001a, "FormationAllas001a-20000009");
    orderActorToFactory(20000010, FormationAllas001d, "FormationAllas001d-20000010");
    orderActorToFactory(20000011, FormationAllas001b, "FormationAllas001b-20000011");
    orderActorToFactory(20000012, FormationAllas001c, "FormationAllas001c-20000012");
    // gen01 end

    getConductor()->ready(0, "OGG_BGM_01_01");

}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getBehaveingFrame()) {
            case 1: {
                break;
            }
            case 500: {
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-1");
                ta->setMaxPerformFrame(2000);
                addSubLast(ta);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(20000001)), 400);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(20000002)), 400);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(20000003)), 400);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(20000004)), 400);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(20000005)), 1);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(20000006)), 400);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(20000007)), 1);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(20000008)), 400);
                ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(20000009)), 1);
                ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(20000010)), 1);
                ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(20000011)), 1);
                ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(20000012)), 400);
                }
                break;
            }
            case 1900: {
                orderActorToFactory(20000013, FormationUnomia001a, "FormationUnomia001a-20000013");
                orderActorToFactory(20000017, VarietyRatislavia001, "VarietyRatislavia001-20000017");
                orderActorToFactory(20000019, FormationAppho001a, "FormationAppho001a-20000019");
                break;
            }
            case 2400: {
                orderActorToFactory(20000015, FormationUnomia001b, "FormationUnomia001b-20000015");
                orderActorToFactory(20000018, VarietyRatislavia002, "VarietyRatislavia002-20000018");
                orderActorToFactory(20000027, FormationAppho001b, "FormationAppho001b-20000027");
                break;
            }
            case 2500: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000013));
                VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(20000017);
                bringSceneMediator()->addSubGroup(pRatislavia);
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000019));
                break;
            }
            case 2900: {
                orderActorToFactory(20000020, FormationAppho001a, "FormationAppho001a-20000020");
                break;
            }
            case 3000: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000015));
                VarietyRatislavia002* pRatislavia = (VarietyRatislavia002*)obtainActorFromFactory(20000018);
                bringSceneMediator()->addSubGroup(pRatislavia);
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000027));
                break;
            }
            case 3400: {
                orderActorToFactory(20000028, FormationAppho001b, "FormationAppho001b-20000028");
                break;
            }
            case 3500: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000020));
                break;
            }
            case 3900: {
                orderActorToFactory(20000021, FormationAppho001a, "FormationAppho001a-20000021");
                break;
            }
            case 4000: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000028));
                break;
            }
            case 4400: {
                orderActorToFactory(20000029, FormationAppho001b, "FormationAppho001b-20000029");
                orderActorToFactory(20000035, FormationDelheid001, "FormationDelheid001-20000035");
                break;
            }
            case 4500: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000021));
                orderActorToFactory(20000036, FormationDelheid001, "FormationDelheid001-20000036");
                break;
            }
            case 4600: {
                orderActorToFactory(20000037, FormationDelheid001, "FormationDelheid001-20000037");
                break;
            }
            case 4700: {
                orderActorToFactory(20000038, FormationDelheid001, "FormationDelheid001-20000038");
                break;
            }
            case 4800: {
                orderActorToFactory(20000039, FormationDelheid001, "FormationDelheid001-20000039");
                break;
            }
            case 4900: {
                orderActorToFactory(20000022, FormationAppho001a, "FormationAppho001a-20000022");
                orderActorToFactory(20000040, FormationDelheid001, "FormationDelheid001-20000040");
                break;
            }
            case 5000: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000029));
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000035);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(0), D_ANG(-40), D_ANG(0));
                orderActorToFactory(20000041, FormationDelheid001, "FormationDelheid001-20000041");
                break;
            }
            case 5100: {
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000036);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(0), D_ANG(-30), D_ANG(0));
                orderActorToFactory(20000042, FormationDelheid001, "FormationDelheid001-20000042");
                break;
            }
            case 5200: {
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000037);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(0), D_ANG(-20), D_ANG(0));
                orderActorToFactory(20000043, FormationDelheid001, "FormationDelheid001-20000043");
                break;
            }
            case 5300: {
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000038);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(0), D_ANG(-10), D_ANG(0));
                break;
            }
            case 5400: {
                orderActorToFactory(20000030, FormationAppho001b, "FormationAppho001b-20000030");
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000039);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C(   0), PX_C(500), D_ANG(0), D_ANG(  0), D_ANG(0));
                break;
            }
            case 5500: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000022));
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000040);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(0), D_ANG( 10), D_ANG(0));
                break;
            }
            case 5600: {
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000041);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(0), D_ANG( 20), D_ANG(0));
                break;
            }
            case 5700: {
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000042);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(0), D_ANG( 30), D_ANG(0));
                break;
            }
            case 5800: {
                FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000043);
                bringSceneMediator()->addSubGroup(pF);
                pF->setPosition(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(0), D_ANG( 40), D_ANG(0));
                break;
            }
            case 5900: {
                orderActorToFactory(20000014, FormationUnomia001a, "FormationUnomia001a-20000014");
                orderActorToFactory(20000023, FormationAppho001a, "FormationAppho001a-20000023");
                break;
            }
            case 6000: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000030));
                break;
            }
            case 6400: {
                orderActorToFactory(20000016, FormationUnomia001b, "FormationUnomia001b-20000016");
                orderActorToFactory(20000031, FormationAppho001b, "FormationAppho001b-20000031");
                break;
            }
            case 6500: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000014));
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000023));
                break;
            }
            case 6900: {
                orderActorToFactory(20000024, FormationAppho001a, "FormationAppho001a-20000024");
                break;
            }
            case 7000: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000016));
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000031));
                break;
            }
            case 7400: {
                orderActorToFactory(20000032, FormationAppho001b, "FormationAppho001b-20000032");
                break;
            }
            case 7500: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000024));
                break;
            }
            case 7900: {
                orderActorToFactory(20000025, FormationAppho001a, "FormationAppho001a-20000025");
                break;
            }
            case 8000: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000032));
                break;
            }
            case 8400: {
                orderActorToFactory(20000033, FormationAppho001b, "FormationAppho001b-20000033");
                break;
            }
            case 8500: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000025));
                break;
            }
            case 8900: {
                orderActorToFactory(20000026, FormationAppho001a, "FormationAppho001a-20000026");
                break;
            }
            case 9000: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000033));
                break;
            }
            case 9400: {
                orderActorToFactory(20000034, FormationAppho001b, "FormationAppho001b-20000034");
                break;
            }
            case 9500: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000026));
                break;
            }
            case 10000: {
                bringSceneMediator()->addSubGroup(obtainActorFromFactory(20000034));
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 43-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end


    if (getBehaveingFrame() == 1 && pGAME_SCENE->getProgress()->get() == GameScene::PROG_MAIN) {
        //兄弟シーンのBGMを全てフェードアウトし、自分のシーンBGMをフェードイン
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeoutBgmTree(300);
        getConductor()->performFromTheBegining(0);
    }
    if (getBehaveingFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        getConductor()->fadeoutStop(0, 120);
        //シーン終了のイベントを通知
        throwEventUpperTree(EVENT_STG01_01_WAS_BROKEN);
    }
}

Stage01_01::~Stage01_01() {

}
