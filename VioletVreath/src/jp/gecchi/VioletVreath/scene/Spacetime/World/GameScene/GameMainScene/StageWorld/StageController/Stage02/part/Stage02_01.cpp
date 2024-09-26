#include "Stage02_01.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/ggaf/lib/scene/RotateFormationScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage02PartController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

using namespace GgafLib;
using namespace VioletVreath;

Stage02_01::Stage02_01(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "Stage02_01";
    getBgmConductor()->ready(0, "BGM_02_01");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,100,400,1000};
    _paFrame_NextEvent = new frame[4];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 4;
    requestActor(80000000, FormationGeria001, "FormationGeria001-80000000");
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
                FormationGeria001* pF = (FormationGeria001*)receiveActor(80000000);
                getSceneChief()->appendChild(pF);
                break;
            }
            case 400: {
                requestActor(80000002, FormationRis001, "FormationRis001-80000002");
                requestActor(80000003, FormationRis002, "FormationRis002-80000003");
                requestActor(80000004, FormationRis001, "FormationRis001-80000004");
                requestActor(80000005, FormationRis002, "FormationRis002-80000005");
                requestActor(80000006, FormationRis001, "FormationRis001-80000006");
                requestActor(80000007, FormationRis002, "FormationRis002-80000007");
                break;
            }
            case 1000: {
                {
                RotateFormationScene* ta = NEW RotateFormationScene("RotateFormationScene-1");
                ta->setMaxPerformFrame(2000);
                appendChild(ta);
                ta->addFormation(((FormationRis001*)receiveActor(80000002)), 400);
                ta->addFormation(((FormationRis002*)receiveActor(80000003)), 400);
                ta->addFormation(((FormationRis001*)receiveActor(80000004)), 400);
                ta->addFormation(((FormationRis002*)receiveActor(80000005)), 400);
                ta->addFormation(((FormationRis001*)receiveActor(80000006)), 400);
                ta->addFormation(((FormationRis002*)receiveActor(80000007)), 400);
                }
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 4-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end

    if (getBehaveingFrame() == 1 && pGAME_SCENE->getPhase()->getCurrent() == GameScene::PHASE_MAIN) {
        //兄弟シーンのBGMを全てフェードアウトし、自分のシーンBGMをフェードイン
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeoutBgmTree(300);
        getBgmConductor()->performFromTheBegining(0);
    }
    //シーン終了のイベントを通知
    if (getActiveFrame() == _paFrame_NextEvent[_event_num-1] + SEC_F(60)) {
        throwEventUpperTree(EVENT_STAGE02_01_WAS_FINISHED);
    }

}

Stage02_01::~Stage02_01() {

}
