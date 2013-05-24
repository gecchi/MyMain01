#include "stdafx.h"
#include "Stage01_01.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,500,1600,2100,2500,2600,3000,3100,3500,3600,4000,4100,4500,4600,5000,5100,5500,5600,6000,6100,6500,6600,7000,7100,7500,7600,8000,8100,8500,8600,9000,9100,9500,10000};
    _paFrame_NextEvent = new frame[34];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 34;

    orderActorToFactory(30000001, FormationPallas001a, "FormationPallas001a-1");
    orderActorToFactory(30000002, FormationPallas001b, "FormationPallas001b-2");
    orderActorToFactory(30000003, FormationPallas001c, "FormationPallas001c-3");
    orderActorToFactory(30000004, FormationPallas001d, "FormationPallas001d-4");
    orderActorToFactory(30000005, FormationPallas001a, "FormationPallas001a-5");
    orderActorToFactory(30000006, FormationPallas001d, "FormationPallas001d-6");
    orderActorToFactory(30000007, FormationPallas001b, "FormationPallas001b-7");
    orderActorToFactory(30000008, FormationPallas001c, "FormationPallas001c-8");
    orderActorToFactory(30000009, FormationPallas001a, "FormationPallas001a-9");
    orderActorToFactory(30000010, FormationPallas001d, "FormationPallas001d-10");
    orderActorToFactory(30000011, FormationPallas001b, "FormationPallas001b-11");
    orderActorToFactory(30000012, FormationPallas001c, "FormationPallas001c-12");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getActiveFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getActiveFrame()) {
            case 1: {
                break;
            }
            case 500: {
                {
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-13");
                ta->setMaxPerformFrame(2000);
                addSubLast(ta);
                ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000001)), 400);
                ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000002)), 400);
                ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000003)), 400);
                ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000004)), 400);
                ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000005)), 1);
                ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000006)), 400);
                ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000007)), 1);
                ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000008)), 400);
                ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000009)), 1);
                ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000010)), 1);
                ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000011)), 1);
                ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000012)), 400);
                }
                break;
            }
            case 1600: {
                orderActorToFactory(30000013, FormationEunomia001a, "FormationEunomia001a-14");
                orderActorToFactory(30000029, VarietySylvia001, "VarietySylvia001-15");
                orderActorToFactory(30000031, FormationSappho001a, "FormationSappho001a-16");
                break;
            }
            case 2100: {
                orderActorToFactory(30000021, FormationEunomia001b, "FormationEunomia001b-17");
                orderActorToFactory(30000030, VarietySylvia002, "VarietySylvia002-18");
                orderActorToFactory(30000039, FormationSappho001b, "FormationSappho001b-19");
                break;
            }
            case 2500: {
                FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000013);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                VarietySylvia001* pSylvia = (VarietySylvia001*)obtainActorFromFactory(30000029);
                getSceneDirector()->addSubGroup(pSylvia);
                FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(30000031);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 2600: {
                orderActorToFactory(30000014, FormationEunomia001a, "FormationEunomia001a-20");
                orderActorToFactory(30000032, FormationSappho001a, "FormationSappho001a-21");
                break;
            }
            case 3000: {
                FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000021);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                VarietySylvia002* pSylvia = (VarietySylvia002*)obtainActorFromFactory(30000030);
                getSceneDirector()->addSubGroup(pSylvia);
                FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(30000039);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 3100: {
                orderActorToFactory(30000022, FormationEunomia001b, "FormationEunomia001b-22");
                orderActorToFactory(30000040, FormationSappho001b, "FormationSappho001b-23");
                break;
            }
            case 3500: {
                FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000014);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(30000032);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 3600: {
                orderActorToFactory(30000015, FormationEunomia001a, "FormationEunomia001a-24");
                orderActorToFactory(30000033, FormationSappho001a, "FormationSappho001a-25");
                break;
            }
            case 4000: {
                FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000022);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(30000040);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 4100: {
                orderActorToFactory(30000023, FormationEunomia001b, "FormationEunomia001b-26");
                orderActorToFactory(30000041, FormationSappho001b, "FormationSappho001b-27");
                break;
            }
            case 4500: {
                FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000015);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(30000033);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 4600: {
                orderActorToFactory(30000016, FormationEunomia001a, "FormationEunomia001a-28");
                orderActorToFactory(30000034, FormationSappho001a, "FormationSappho001a-29");
                break;
            }
            case 5000: {
                FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000023);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(30000041);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 5100: {
                orderActorToFactory(30000024, FormationEunomia001b, "FormationEunomia001b-30");
                orderActorToFactory(30000042, FormationSappho001b, "FormationSappho001b-31");
                break;
            }
            case 5500: {
                FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000016);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(30000034);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 5600: {
                orderActorToFactory(30000017, FormationEunomia001a, "FormationEunomia001a-32");
                orderActorToFactory(30000035, FormationSappho001a, "FormationSappho001a-33");
                break;
            }
            case 6000: {
                FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000024);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(30000042);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 6100: {
                orderActorToFactory(30000025, FormationEunomia001b, "FormationEunomia001b-34");
                orderActorToFactory(30000043, FormationSappho001b, "FormationSappho001b-35");
                break;
            }
            case 6500: {
                FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000017);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(30000035);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 6600: {
                orderActorToFactory(30000018, FormationEunomia001a, "FormationEunomia001a-36");
                orderActorToFactory(30000036, FormationSappho001a, "FormationSappho001a-37");
                break;
            }
            case 7000: {
                FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000025);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(30000043);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 7100: {
                orderActorToFactory(30000026, FormationEunomia001b, "FormationEunomia001b-38");
                orderActorToFactory(30000044, FormationSappho001b, "FormationSappho001b-39");
                break;
            }
            case 7500: {
                FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000018);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(30000036);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 7600: {
                orderActorToFactory(30000019, FormationEunomia001a, "FormationEunomia001a-40");
                orderActorToFactory(30000037, FormationSappho001a, "FormationSappho001a-41");
                break;
            }
            case 8000: {
                FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000026);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(30000044);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 8100: {
                orderActorToFactory(30000027, FormationEunomia001b, "FormationEunomia001b-42");
                orderActorToFactory(30000045, FormationSappho001b, "FormationSappho001b-43");
                break;
            }
            case 8500: {
                FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000019);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(30000037);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 8600: {
                orderActorToFactory(30000020, FormationEunomia001a, "FormationEunomia001a-44");
                orderActorToFactory(30000038, FormationSappho001a, "FormationSappho001a-45");
                break;
            }
            case 9000: {
                FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000027);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(30000045);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 9100: {
                orderActorToFactory(30000028, FormationEunomia001b, "FormationEunomia001b-46");
                orderActorToFactory(30000046, FormationSappho001b, "FormationSappho001b-47");
                break;
            }
            case 9500: {
                FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000020);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(30000038);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            case 10000: {
                FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000028);
                getSceneDirector()->addSubGroup(pFormationEunomia);
                FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(30000046);
                getSceneDirector()->addSubGroup(pF);
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 34-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end

    //シーン終了のイベントを通知
    if (getActiveFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventUpperTree(EVENT_STG01_01_WAS_BROKEN);
    }
}

Stage01_01::~Stage01_01() {

}
