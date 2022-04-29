#include "Stage02_01.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage02PartController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

using namespace GgafLib;
using namespace VioletVreath;

Stage02_01::Stage02_01(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "Stage02_01";
    getBgmConductor()->ready(0, "BGM_02_01");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
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
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
    if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getBehaveingFrame()) {
            case 1: {
                break;
            }
            case 100: {
                FormationGeria001* pF = (FormationGeria001*)receiveActor(80000000);
                bringSceneMediator()->appendGroupChild(pF);
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
                FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-1");
                ta->setMaxPerformFrame(2000);
                appendChild(ta);
                ta->addToTable(((FormationRis001*)receiveActor(80000002)), 400);
                ta->addToTable(((FormationRis002*)receiveActor(80000003)), 400);
                ta->addToTable(((FormationRis001*)receiveActor(80000004)), 400);
                ta->addToTable(((FormationRis002*)receiveActor(80000005)), 400);
                ta->addToTable(((FormationRis001*)receiveActor(80000006)), 400);
                ta->addToTable(((FormationRis002*)receiveActor(80000007)), 400);
                }
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 4-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end

    if (getBehaveingFrame() == 1 && pGAME_SCENE->getPhase()->get() == GameScene::PHASE_MAIN) {
        //�Z��V�[����BGM��S�ăt�F�[�h�A�E�g���A�����̃V�[��BGM���t�F�[�h�C��
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeoutBgmTree(300);
        getBgmConductor()->performFromTheBegining(0);
    }
    //�V�[���I���̃C�x���g��ʒm
    if (getActiveFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventUpperTree(EVENT_STAGE02_01_WAS_FINISHED);
    }

}

Stage02_01::~Stage02_01() {

}
