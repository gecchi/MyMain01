#include "Stage01_01.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,500,1600,2500,2600,3500,3600,4500,4600,5500,5600,6500,6600,7500,7600,8500,8600,9500};
	_paFrame_NextEvent = new frame[18];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 18;
	
	orderActorToFactory(20000001, FormationAllas001a, "FormationAllas001a-1");
	orderActorToFactory(20000002, FormationAllas001b, "FormationAllas001b-2");
	orderActorToFactory(20000003, FormationAllas001c, "FormationAllas001c-3");
	orderActorToFactory(20000004, FormationAllas001d, "FormationAllas001d-4");
	orderActorToFactory(20000005, FormationAllas001a, "FormationAllas001a-5");
	orderActorToFactory(20000006, FormationAllas001d, "FormationAllas001d-6");
	orderActorToFactory(20000007, FormationAllas001b, "FormationAllas001b-7");
	orderActorToFactory(20000008, FormationAllas001c, "FormationAllas001c-8");
	orderActorToFactory(20000009, FormationAllas001a, "FormationAllas001a-9");
	orderActorToFactory(20000010, FormationAllas001d, "FormationAllas001d-10");
	orderActorToFactory(20000011, FormationAllas001b, "FormationAllas001b-11");
	orderActorToFactory(20000012, FormationAllas001c, "FormationAllas001c-12");
    // gen01 end

    getBGMer()->ready(0, "OGG_BGM_01_01");

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
			case 1600: {
				orderActorToFactory(20000013, FormationUnomia001a, "FormationUnomia001a-14");
				orderActorToFactory(20000021, VarietyRatislavia001, "VarietyRatislavia001-15");
				orderActorToFactory(20000022, FormationAppho001a, "FormationAppho001a-16");
				break;
			}
			case 2500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000013);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(20000021);
				getSceneDirector()->addSubGroup(pRatislavia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(20000022);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 2600: {
				orderActorToFactory(20000014, FormationUnomia001a, "FormationUnomia001a-17");
				orderActorToFactory(20000023, FormationAppho001a, "FormationAppho001a-18");
				break;
			}
			case 3500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000014);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(20000023);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 3600: {
				orderActorToFactory(20000015, FormationUnomia001a, "FormationUnomia001a-19");
				orderActorToFactory(20000024, FormationAppho001a, "FormationAppho001a-20");
				break;
			}
			case 4500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000015);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(20000024);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 4600: {
				orderActorToFactory(20000016, FormationUnomia001a, "FormationUnomia001a-21");
				orderActorToFactory(20000025, FormationAppho001a, "FormationAppho001a-22");
				break;
			}
			case 5500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000016);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(20000025);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 5600: {
				orderActorToFactory(20000017, FormationUnomia001a, "FormationUnomia001a-23");
				orderActorToFactory(20000026, FormationAppho001a, "FormationAppho001a-24");
				break;
			}
			case 6500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000017);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(20000026);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 6600: {
				orderActorToFactory(20000018, FormationUnomia001a, "FormationUnomia001a-25");
				orderActorToFactory(20000027, FormationAppho001a, "FormationAppho001a-26");
				break;
			}
			case 7500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000018);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(20000027);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 7600: {
				orderActorToFactory(20000019, FormationUnomia001a, "FormationUnomia001a-27");
				orderActorToFactory(20000028, FormationAppho001a, "FormationAppho001a-28");
				break;
			}
			case 8500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000019);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(20000028);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 8600: {
				orderActorToFactory(20000020, FormationUnomia001a, "FormationUnomia001a-29");
				orderActorToFactory(20000029, FormationAppho001a, "FormationAppho001a-30");
				break;
			}
			case 9500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000020);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pF = (FormationAppho001a*)obtainActorFromFactory(20000029);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 18-1 ? _cnt_event+1 : _cnt_event);
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
        //シーン終了のイベントを通知
        throwEventUpperTree(EVENT_STG01_01_WAS_BROKEN);
    }
}

Stage01_01::~Stage01_01() {

}
