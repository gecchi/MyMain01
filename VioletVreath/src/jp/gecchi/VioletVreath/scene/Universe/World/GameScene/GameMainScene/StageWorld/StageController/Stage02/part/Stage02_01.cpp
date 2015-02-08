#include "Stage02_01.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage02PartController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02_01::Stage02_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,400,1000};
	_paFrame_NextEvent = new frame[4];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 4;
	orderActorToFactory(70000000, FormationGeria001, "FormationGeria001-1");
    // gen01 end
}

void Stage02_01::initialize() {

}

void Stage02_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 100: {
				FormationGeria001* pF = (FormationGeria001*)obtainActorFromFactory(70000000);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 400: {
				orderActorToFactory(70000002, FormationRis001, "FormationRis001-2");
				orderActorToFactory(70000003, FormationRis002, "FormationRis002-3");
				orderActorToFactory(70000004, FormationRis001, "FormationRis001-4");
				orderActorToFactory(70000005, FormationRis002, "FormationRis002-5");
				orderActorToFactory(70000006, FormationRis001, "FormationRis001-6");
				orderActorToFactory(70000007, FormationRis002, "FormationRis002-7");
				break;
			}
			case 1000: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-8");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(70000002)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(70000003)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(70000004)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(70000005)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(70000006)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(70000007)), 400);
				}
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 4-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    //シーン終了のイベントを通知
    if (getActiveFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventUpperTree(EVENT_STG02_01_WAS_BROKEN);
    }

}

Stage02_01::~Stage02_01() {

}
