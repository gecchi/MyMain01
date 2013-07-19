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
	
	orderActorToFactory(30000001, FormationAllas001a, "FormationAllas001a-1");
	orderActorToFactory(30000002, FormationAllas001b, "FormationAllas001b-2");
	orderActorToFactory(30000003, FormationAllas001c, "FormationAllas001c-3");
	orderActorToFactory(30000004, FormationAllas001d, "FormationAllas001d-4");
	orderActorToFactory(30000005, FormationAllas001a, "FormationAllas001a-5");
	orderActorToFactory(30000006, FormationAllas001d, "FormationAllas001d-6");
	orderActorToFactory(30000007, FormationAllas001b, "FormationAllas001b-7");
	orderActorToFactory(30000008, FormationAllas001c, "FormationAllas001c-8");
	orderActorToFactory(30000009, FormationAllas001a, "FormationAllas001a-9");
	orderActorToFactory(30000010, FormationAllas001d, "FormationAllas001d-10");
	orderActorToFactory(30000011, FormationAllas001b, "FormationAllas001b-11");
	orderActorToFactory(30000012, FormationAllas001c, "FormationAllas001c-12");
    // gen01 end
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
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-13");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(30000001)), 400);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(30000002)), 400);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(30000003)), 400);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(30000004)), 400);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(30000005)), 1);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(30000006)), 400);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(30000007)), 1);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(30000008)), 400);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(30000009)), 1);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(30000010)), 1);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(30000011)), 1);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(30000012)), 400);
				}
				break;
			}
			case 1600: {
				orderActorToFactory(30000013, FormationUnomia001a, "FormationUnomia001a-14");
				orderActorToFactory(30000029, VarietyRatislavia001, "VarietyRatislavia001-15");
				orderActorToFactory(30000031, FormationAppho001a, "FormationAppho001a-16");
				break;
			}
			case 2100: {
				orderActorToFactory(30000021, FormationUnomia001b, "FormationUnomia001b-17");
				orderActorToFactory(30000030, VarietyRatislavia002, "VarietyRatislavia002-18");
				orderActorToFactory(30000039, FormationAppho001b, "FormationAppho001b-19");
				break;
			}
			case 2500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(30000013);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(30000029);
				getSceneDirector()->addSubGroup(pRatislavia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(30000031);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 2600: {
				orderActorToFactory(30000014, FormationUnomia001a, "FormationUnomia001a-20");
				orderActorToFactory(30000032, FormationAppho001a, "FormationAppho001a-21");
				break;
			}
			case 3000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(30000021);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				VarietyRatislavia002* pRatislavia = (VarietyRatislavia002*)obtainActorFromFactory(30000030);
				getSceneDirector()->addSubGroup(pRatislavia);
				FormationAppho001b* pF = (FormationAppho001b*)obtainActorFromFactory(30000039);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 3100: {
				orderActorToFactory(30000022, FormationUnomia001b, "FormationUnomia001b-22");
				orderActorToFactory(30000040, FormationAppho001b, "FormationAppho001b-23");
				break;
			}
			case 3500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(30000014);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(30000032);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 3600: {
				orderActorToFactory(30000015, FormationUnomia001a, "FormationUnomia001a-24");
				orderActorToFactory(30000033, FormationAppho001a, "FormationAppho001a-25");
				break;
			}
			case 4000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(30000022);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001b* pF = (FormationAppho001b*)obtainActorFromFactory(30000040);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 4100: {
				orderActorToFactory(30000023, FormationUnomia001b, "FormationUnomia001b-26");
				orderActorToFactory(30000041, FormationAppho001b, "FormationAppho001b-27");
				break;
			}
			case 4500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(30000015);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(30000033);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 4600: {
				orderActorToFactory(30000016, FormationUnomia001a, "FormationUnomia001a-28");
				orderActorToFactory(30000034, FormationAppho001a, "FormationAppho001a-29");
				break;
			}
			case 5000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(30000023);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001b* pF = (FormationAppho001b*)obtainActorFromFactory(30000041);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 5100: {
				orderActorToFactory(30000024, FormationUnomia001b, "FormationUnomia001b-30");
				orderActorToFactory(30000042, FormationAppho001b, "FormationAppho001b-31");
				break;
			}
			case 5500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(30000016);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(30000034);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 5600: {
				orderActorToFactory(30000017, FormationUnomia001a, "FormationUnomia001a-32");
				orderActorToFactory(30000035, FormationAppho001a, "FormationAppho001a-33");
				break;
			}
			case 6000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(30000024);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001b* pF = (FormationAppho001b*)obtainActorFromFactory(30000042);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 6100: {
				orderActorToFactory(30000025, FormationUnomia001b, "FormationUnomia001b-34");
				orderActorToFactory(30000043, FormationAppho001b, "FormationAppho001b-35");
				break;
			}
			case 6500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(30000017);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(30000035);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 6600: {
				orderActorToFactory(30000018, FormationUnomia001a, "FormationUnomia001a-36");
				orderActorToFactory(30000036, FormationAppho001a, "FormationAppho001a-37");
				break;
			}
			case 7000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(30000025);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001b* pF = (FormationAppho001b*)obtainActorFromFactory(30000043);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 7100: {
				orderActorToFactory(30000026, FormationUnomia001b, "FormationUnomia001b-38");
				orderActorToFactory(30000044, FormationAppho001b, "FormationAppho001b-39");
				break;
			}
			case 7500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(30000018);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(30000036);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 7600: {
				orderActorToFactory(30000019, FormationUnomia001a, "FormationUnomia001a-40");
				orderActorToFactory(30000037, FormationAppho001a, "FormationAppho001a-41");
				break;
			}
			case 8000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(30000026);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001b* pF = (FormationAppho001b*)obtainActorFromFactory(30000044);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 8100: {
				orderActorToFactory(30000027, FormationUnomia001b, "FormationUnomia001b-42");
				orderActorToFactory(30000045, FormationAppho001b, "FormationAppho001b-43");
				break;
			}
			case 8500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(30000019);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(30000037);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 8600: {
				orderActorToFactory(30000020, FormationUnomia001a, "FormationUnomia001a-44");
				orderActorToFactory(30000038, FormationAppho001a, "FormationAppho001a-45");
				break;
			}
			case 9000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(30000027);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001b* pF = (FormationAppho001b*)obtainActorFromFactory(30000045);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 9100: {
				orderActorToFactory(30000028, FormationUnomia001b, "FormationUnomia001b-46");
				orderActorToFactory(30000046, FormationAppho001b, "FormationAppho001b-47");
				break;
			}
			case 9500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(30000020);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(30000038);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 10000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(30000028);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001b* pF = (FormationAppho001b*)obtainActorFromFactory(30000046);
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
