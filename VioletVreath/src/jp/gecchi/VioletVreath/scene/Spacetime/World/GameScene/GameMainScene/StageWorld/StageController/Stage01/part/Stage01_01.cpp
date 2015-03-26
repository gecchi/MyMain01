#include "Stage01_01.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
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

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,500,1900,2400,2500,2900,3000,3400,3500,3900,4000,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6400,6500,6900,7000,7400,7500,7900,8000,8400,8500,8900,9000,9400,9500,10000};
	_paFrame_NextEvent = new frame[43];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 43;
	
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
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
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
			case 1900: {
				orderActorToFactory(20000013, FormationUnomia001a, "FormationUnomia001a-14");
				orderActorToFactory(20000017, VarietyRatislavia001, "VarietyRatislavia001-15");
				orderActorToFactory(20000019, FormationAppho001a, "FormationAppho001a-16");
				break;
			}
			case 2400: {
				orderActorToFactory(20000015, FormationUnomia001b, "FormationUnomia001b-17");
				orderActorToFactory(20000018, VarietyRatislavia002, "VarietyRatislavia002-18");
				orderActorToFactory(20000027, FormationAppho001b, "FormationAppho001b-19");
				break;
			}
			case 2500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000013);
				bringDirector()->addSubGroup(pFormationUnomia);
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(20000017);
				bringDirector()->addSubGroup(pRatislavia);
				FormationAppho001a* pFA = (FormationAppho001a*)obtainActorFromFactory(20000019);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 2900: {
				orderActorToFactory(20000020, FormationAppho001a, "FormationAppho001a-20");
				break;
			}
			case 3000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(20000015);
				bringDirector()->addSubGroup(pFormationUnomia);
				VarietyRatislavia002* pRatislavia = (VarietyRatislavia002*)obtainActorFromFactory(20000018);
				bringDirector()->addSubGroup(pRatislavia);
				FormationAppho001b* pFA = (FormationAppho001b*)obtainActorFromFactory(20000027);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 3400: {
				orderActorToFactory(20000028, FormationAppho001b, "FormationAppho001b-21");
				break;
			}
			case 3500: {
				FormationAppho001a* pFA = (FormationAppho001a*)obtainActorFromFactory(20000020);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 3900: {
				orderActorToFactory(20000021, FormationAppho001a, "FormationAppho001a-22");
				break;
			}
			case 4000: {
				FormationAppho001b* pFA = (FormationAppho001b*)obtainActorFromFactory(20000028);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 4400: {
				orderActorToFactory(20000029, FormationAppho001b, "FormationAppho001b-23");
				orderActorToFactory(20000035, FormationDelheid001, "FormationDelheid001-24");
				break;
			}
			case 4500: {
				FormationAppho001a* pFA = (FormationAppho001a*)obtainActorFromFactory(20000021);
				bringDirector()->addSubGroup(pFA);
				orderActorToFactory(20000036, FormationDelheid001, "FormationDelheid001-25");
				break;
			}
			case 4600: {
				orderActorToFactory(20000037, FormationDelheid001, "FormationDelheid001-26");
				break;
			}
			case 4700: {
				orderActorToFactory(20000038, FormationDelheid001, "FormationDelheid001-27");
				break;
			}
			case 4800: {
				orderActorToFactory(20000039, FormationDelheid001, "FormationDelheid001-28");
				break;
			}
			case 4900: {
				orderActorToFactory(20000022, FormationAppho001a, "FormationAppho001a-29");
				orderActorToFactory(20000040, FormationDelheid001, "FormationDelheid001-30");
				break;
			}
			case 5000: {
				FormationAppho001b* pFA = (FormationAppho001b*)obtainActorFromFactory(20000029);
				bringDirector()->addSubGroup(pFA);
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000035);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				orderActorToFactory(20000041, FormationDelheid001, "FormationDelheid001-31");
				break;
			}
			case 5100: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000036);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				orderActorToFactory(20000042, FormationDelheid001, "FormationDelheid001-32");
				break;
			}
			case 5200: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000037);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				orderActorToFactory(20000043, FormationDelheid001, "FormationDelheid001-33");
				break;
			}
			case 5300: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000038);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 5400: {
				orderActorToFactory(20000030, FormationAppho001b, "FormationAppho001b-34");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000039);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 5500: {
				FormationAppho001a* pFA = (FormationAppho001a*)obtainActorFromFactory(20000022);
				bringDirector()->addSubGroup(pFA);
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000040);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 5600: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000041);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 5700: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000042);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 5800: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(20000043);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 5900: {
				orderActorToFactory(20000014, FormationUnomia001a, "FormationUnomia001a-35");
				orderActorToFactory(20000023, FormationAppho001a, "FormationAppho001a-36");
				break;
			}
			case 6000: {
				FormationAppho001b* pFA = (FormationAppho001b*)obtainActorFromFactory(20000030);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 6400: {
				orderActorToFactory(20000016, FormationUnomia001b, "FormationUnomia001b-37");
				orderActorToFactory(20000031, FormationAppho001b, "FormationAppho001b-38");
				break;
			}
			case 6500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(20000014);
				bringDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001a* pFA = (FormationAppho001a*)obtainActorFromFactory(20000023);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 6900: {
				orderActorToFactory(20000024, FormationAppho001a, "FormationAppho001a-39");
				break;
			}
			case 7000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(20000016);
				bringDirector()->addSubGroup(pFormationUnomia);
				FormationAppho001b* pFA = (FormationAppho001b*)obtainActorFromFactory(20000031);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 7400: {
				orderActorToFactory(20000032, FormationAppho001b, "FormationAppho001b-40");
				break;
			}
			case 7500: {
				FormationAppho001a* pFA = (FormationAppho001a*)obtainActorFromFactory(20000024);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 7900: {
				orderActorToFactory(20000025, FormationAppho001a, "FormationAppho001a-41");
				break;
			}
			case 8000: {
				FormationAppho001b* pFA = (FormationAppho001b*)obtainActorFromFactory(20000032);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 8400: {
				orderActorToFactory(20000033, FormationAppho001b, "FormationAppho001b-42");
				break;
			}
			case 8500: {
				FormationAppho001a* pFA = (FormationAppho001a*)obtainActorFromFactory(20000025);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 8900: {
				orderActorToFactory(20000026, FormationAppho001a, "FormationAppho001a-43");
				break;
			}
			case 9000: {
				FormationAppho001b* pFA = (FormationAppho001b*)obtainActorFromFactory(20000033);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 9400: {
				orderActorToFactory(20000034, FormationAppho001b, "FormationAppho001b-44");
				break;
			}
			case 9500: {
				FormationAppho001a* pFA = (FormationAppho001a*)obtainActorFromFactory(20000026);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			case 10000: {
				FormationAppho001b* pFA = (FormationAppho001b*)obtainActorFromFactory(20000034);
				bringDirector()->addSubGroup(pFA);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 43-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    if (getBehaveingFrame() == 1 && P_GAME_SCENE->getProgress()->get() == GameScene::PROG_MAIN) {
        //�Z��V�[����BGM��S�ăt�F�[�h�A�E�g���A�����̃V�[��BGM���t�F�[�h�C��
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeout_stop_AllPartSceneBgm();
        getBGMer()->play_fadein(0);
    }
    if (getBehaveingFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        getBGMer()->fadeout_stop(0);
        //�V�[���I���̃C�x���g��ʒm
        throwEventUpperTree(EVENT_STG01_01_WAS_BROKEN);
    }
}

Stage01_01::~Stage01_01() {

}