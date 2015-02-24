#include "Stage01WalledScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/actor/WallAABActor.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "Stage01WalledSection001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/wall/Wall001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/wall/Wall001Prism.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : WalledScene(prm_name) {
    _class_name = "Stage01WalledScene";

    //********* �Ǐ�� ***********
    coord wall_dep    = DX_C(40);  //�ǃu���b�N���f���P��X�������̕��ݒ�iX�t�@�C���ɂ�茈�܂�j
    coord wall_width  = DX_C(10);  //�ǃu���b�N���f���P��Z�������̕��ݒ�iX�t�@�C���ɂ�茈�܂�j
    coord wall_height = DX_C(10);  //�ǃu���b�N���f���P��Y�������̕��ݒ�iX�t�@�C���ɂ�茈�܂�j
    float scale_r = 10.0f;        //����ǃu���b�N�̊g�嗦�i�����Őݒ�\�j
    //****************************

    //�ǃu���b�N(������)�f�|�W�g������
    WallAABActor* pWallAABActor;
    GgafActorDepository* pDepo_wall = NEW GgafActorDepository("Dp_WallAAB");
    for (int i = 0; i < 1000; i++) {
        std::string name = "Wall001_"+XTOS(i);
        pWallAABActor = NEW Wall001(name.c_str());
        pWallAABActor->setScaleR(scale_r);
        pDepo_wall->put(pWallAABActor);
        Sleep(1);
    }
    P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepo_wall);
    //getSceneDirector()->addSubGroup(pDepo_wall); �� P_UNIVERSE �z���ɂȂ��Ă��܂�

    //�ǃu���b�N(�v���Y��)�f�|�W�g������
    WallAAPrismActor* pWallAAPrismActor;
    GgafActorDepository* pDepo_prism = NEW GgafActorDepository("Dp_WallAAPrism");
    for (int i = 0; i < 100; i++) {
        std::string name = "Wall001Prism_"+XTOS(i);
        pWallAAPrismActor = NEW Wall001Prism(name.c_str());
        pWallAAPrismActor->setScaleR(scale_r);
        pDepo_prism->put(pWallAAPrismActor);
        Sleep(1);
    }
    P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepo_prism);

    //�V�[���Z�N�V��������
    WalledSectionScene* apSection[] = {
        NEW Stage01WalledSection001("Stage01-001-0", this, "scene4_wall_0.dat"),
        NEW Stage01WalledSection001("Stage01-001-1", this, "scene4_wall_1.dat"),
        NEW Stage01WalledSection001("Stage01-001-2", this, "scene4_wall_2.dat"),
        NEW Stage01WalledSection001("Stage01-001-3", this, "scene4_wall_3.dat"),
    };

    //�\�z
    buildWalledScene(
        wall_dep*scale_r, wall_width*scale_r, wall_height*scale_r,
        GgafDxUniverse::_x_gone_right,
        (WalledSectionScene**)&apSection, 4,
        pDepo_wall ,pDepo_prism
    );

    //�����X�N���[���X�s�[�h
    setScrollSpeed(PX_C(15));

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,100,1400,2000,4400,5000,5400,6000,7400,8000};
	_paFrame_NextEvent = new frame[10];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 10;
	orderActorToFactory(50000000, EnemyEsperia, "EnemyEsperia-1");
    // gen01 end
}

void Stage01WalledScene::initialize() {
    WalledScene::initialize(); //�d�v�B�ǃf�|�W�g���̏����V�[����z����
}

void Stage01WalledScene::onActive() {
    P_COMMON_SCENE->setScrollingFunction(_pFuncScrolling);
    P_COMMON_SCENE->setScrollSpeed(getScrollSpeed());
    _TRACE_("Stage01WalledScene::onActive()  CommonScene �ɂ��X�N���[����ݒ肵�܂��B");
    //P_COMMON_SCENE->dump();
    WalledScene::onActive();
}

void Stage01WalledScene::processBehavior() {
    WalledScene::processBehavior();

    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 100: {
				EnemyEsperia* p = (EnemyEsperia*)obtainActorFromFactory(50000000);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 1400: {
				orderActorToFactory(50000005, FormationUnomia001a, "FormationUnomia001a-2");
				break;
			}
			case 2000: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(50000005);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				break;
			}
			case 4400: {
				orderActorToFactory(50000001, EnemyEsperia, "EnemyEsperia-3");
				orderActorToFactory(50000004, VarietyRatislavia003, "VarietyRatislavia003-4");
				break;
			}
			case 5000: {
				EnemyEsperia* p = (EnemyEsperia*)obtainActorFromFactory(50000001);
				getSceneDirector()->addSubGroup(p);
				VarietyRatislavia003* pRatislaviaB = (VarietyRatislavia003*)obtainActorFromFactory(50000004);
				getSceneDirector()->addSubGroup(pRatislaviaB);
				break;
			}
			case 5400: {
				orderActorToFactory(50000006, FormationUnomia001b, "FormationUnomia001b-5");
				break;
			}
			case 6000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(50000006);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				break;
			}
			case 7400: {
				orderActorToFactory(50000002, EnemyEsperia, "EnemyEsperia-6");
				orderActorToFactory(50000003, VarietyRatislavia002, "VarietyRatislavia002-7");
				break;
			}
			case 8000: {
				EnemyEsperia* p = (EnemyEsperia*)obtainActorFromFactory(50000002);
				getSceneDirector()->addSubGroup(p);
				VarietyRatislavia002* pRatislaviaA = (VarietyRatislavia002*)obtainActorFromFactory(50000003);
				getSceneDirector()->addSubGroup(pRatislaviaA);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 10-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


}

void Stage01WalledScene::onFinishedAllSection() {
    _TRACE_(" Stage01WalledScene::onFinishedAllSection()  CommonScene �̃X�N���[�����������܂��B");
    P_COMMON_SCENE->setScrollingFunction(nullptr);
    P_COMMON_SCENE->setScrollSpeed(0);
    throwEventUpperTree(EVENT_STG01_WALLED_WAS_BROKEN);
}

Stage01WalledScene::~Stage01WalledScene() {

}
