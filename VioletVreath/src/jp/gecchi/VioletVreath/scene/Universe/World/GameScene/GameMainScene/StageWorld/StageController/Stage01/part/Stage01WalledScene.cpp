#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : WalledScene(prm_name) {
    _class_name = "Stage01WalledScene";

    //********* �Ǐ�� ***********
    coord wall_dep    = 400000;  //�ǃu���b�N���f���P��X�������̕�
    coord wall_width  = 100000;  //�ǃu���b�N���f���P��Z�������̕�
    coord wall_height = 100000;  //�ǃu���b�N���f���P��Y�������̕�
    float scale_r = 10.0f;       //�ǃu���b�N���f���̌��̑傫������̊g�嗦
    //****************************

    //�ǃu���b�N(������)�f�|�W�g������
    WallAABActor* pWallAABActor;
    GgafActorDepository* pDepo_WallAAB = NEW GgafActorDepository("Dp_WallAAB");
    for (int i = 0; i < 1500; i++) {
        std::string name = "Wall001_"+ITOS(i);
        pWallAABActor = NEW Wall001(name.c_str());
        pWallAABActor->setScaleR(scale_r);
        pDepo_WallAAB->addSubLast(pWallAABActor);
    }
    P_COMMON_SCENE->getDirector()->addSubGroup(pDepo_WallAAB);
    //getDirector()->addSubGroup(pDepo_WallAAB); �� P_UNIVERSE �z���ɂȂ��Ă��܂�

    //�ǃu���b�N(�v���Y��)�f�|�W�g������
    WallAAPrismActor* pWallAAPrismActor;
    GgafActorDepository* pDepo_WallAAPrism = NEW GgafActorDepository("Dp_WallAAPrism");
    for (int i = 0; i < 500; i++) {
        std::string name = "Wall001Prism_"+ITOS(i);
        pWallAAPrismActor = NEW Wall001Prism(name.c_str());
        pWallAAPrismActor->setScaleR(scale_r);
        pDepo_WallAAPrism->addSubLast(pWallAAPrismActor);
    }
    P_COMMON_SCENE->getDirector()->addSubGroup(pDepo_WallAAPrism);

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
        GgafDxUniverse::_X_goneRight*20,
        (WalledSectionScene**)&apSection, 4,
        pDepo_WallAAB ,pDepo_WallAAPrism
    );

    //�����X�N���[���X�s�[�h
    setScrollSpeed(40000);

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,200,1000,2000,3200,5000,6200,8000,30000};
	_paFrame_NextEvent = new frame[9];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 9;
	orderActorToFactory(20000002, VarietySylvia002, "VarietySylvia002_1");
    // gen01 end
}

void Stage01WalledScene::initialize() {
    WalledScene::initialize(); //�d�v
}

void Stage01WalledScene::processBehavior() {
    WalledScene::processBehavior();

    //debug ---->
//    if (GgafDxInput::isPushedDownKey(DIK_O)) {
//        setScrollSpeed(0);
//    }
//    if (GgafDxInput::isPushedDownKey(DIK_P)) {
//        setScrollSpeed(10000);
//    }
    //<---- debug

    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 200: {
				orderActorToFactory(20000003, VarietySylvia003, "VarietySylvia003_2");
				break;
			}
			case 1000: {
				VarietySylvia002* pSylviaA = (VarietySylvia002*)obtainActorFromFactory(20000002);
				getDirector()->addSubGroup(pSylviaA);
				break;
			}
			case 2000: {
				VarietySylvia003* pSylviaB = (VarietySylvia003*)obtainActorFromFactory(20000003);
				getDirector()->addSubGroup(pSylviaB);
				break;
			}
			case 3200: {
				orderActorToFactory(20000000, EnemyHesperia, "EnemyHesperia_3");
				break;
			}
			case 5000: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(20000000);
				getDirector()->addSubGroup(p);
				break;
			}
			case 6200: {
				orderActorToFactory(20000001, EnemyHesperia, "EnemyHesperia_4");
				break;
			}
			case 8000: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(20000001);
				getDirector()->addSubGroup(p);
				break;
			}
			case 30000: {
				// WalledScene �͏I�������C�x���g�ʒm�s�v
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 9-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end
}

void Stage01WalledScene::onFinishedSection() {
    throwEventToUpperTree(EVENT_STG01_WALLED_WAS_BROKEN, this);
}

Stage01WalledScene::~Stage01WalledScene() {

}
