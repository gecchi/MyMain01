#include "Stage01PartWall.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "Stage01PartWall/Stage01PartWallSection001.h"



using namespace GgafLib;
using namespace VioletVreath;

Stage01PartWall::Stage01PartWall(const char* prm_name) :
        Stage01Part(prm_name, EVENT_STAGE01_PART_WALL_WAS_FINISHED) {
    _class_name = "Stage01PartWall";

    //********* �Ǐ�� ***********
    coord wall_dep    = DX_C(40);  //�ǃu���b�N���f���P��X�������̕��ݒ�iX�t�@�C���ɂ�茈�܂�j
    coord wall_width  = DX_C(10);  //�ǃu���b�N���f���P��Z�������̕��ݒ�iX�t�@�C���ɂ�茈�܂�j
    coord wall_height = DX_C(10);  //�ǃu���b�N���f���P��Y�������̕��ݒ�iX�t�@�C���ɂ�茈�܂�j
    float scale_r = 4.0f;        //����ǃu���b�N�̊g�嗦�i�����Őݒ�\�j
    //****************************

    //�ǃu���b�N(������)�f�|�W�g������
    MassWallActor* pWall;
    GgafCore::ActorDepository* pDepo_wall = NEW GgafCore::ActorDepository("Depo_Wall");
    for (int i = 0; i < 2000; i++) {
        std::string name = "Wall01_"+XTOS(i);
        pWall = NEW Wall01(name.c_str());
        pWall->setScaleR(scale_r);
        pDepo_wall->put(pWall);
    }
    bringSceneMediator()->appendGroupChild(pDepo_wall);


//    //�V�[���Z�N�V��������
//    WallSectionScene* apSection[] = {
//        NEW Stage01PartWallSection001("Stage01-001-0", this, "scene5_wall_0.dat"),
//        NEW Stage01PartWallSection001("Stage01-001-1", this, "scene5_wall_1.dat"),
//        NEW Stage01PartWallSection001("Stage01-001-2", this, "scene5_wall_2.dat"),
//        NEW Stage01PartWallSection001("Stage01-001-3", this, "scene5_wall_3.dat"),
//        NEW Stage01PartWallSection001("Stage01-001-4", this, "scene4_wall_0.dat"),
//        NEW Stage01PartWallSection001("Stage01-001-5", this, "scene4_wall_1.dat"),
//        NEW Stage01PartWallSection001("Stage01-001-6", this, "scene4_wall_2.dat"),
//        NEW Stage01PartWallSection001("Stage01-001-7", this, "scene4_wall_3.dat"),
//    };
//    //�\�z
//    buildWallScene(
//        wall_dep*scale_r, wall_width*scale_r, wall_height*scale_r,
//        pGOD->getSpacetime()->_x_bound_right,
//        (WallSectionScene**)&apSection, 8,
//        pDepo_wall
//    );
    //�V�[���Z�N�V��������
    WallSectionScene* apSection[] = {
        NEW Stage01PartWallSection001("Stage01-001-0", this, "scene6_wall_0.dat"),
        NEW Stage01PartWallSection001("Stage01-001-1", this, "scene6_wall_1.dat"),
        NEW Stage01PartWallSection001("Stage01-001-2", this, "scene6_wall_2.dat"),
        NEW Stage01PartWallSection001("Stage01-001-3", this, "scene6_wall_3.dat"),
    };
    //�\�z
    buildWallScene(
        wall_dep*scale_r, wall_width*scale_r, wall_height*scale_r,
        pGOD->getSpacetime()->_x_bound_right,
        (WallSectionScene**)&apSection, 4,
        pDepo_wall
    );

    //�����X�N���[���X�s�[�h
    setScrollSpeed(PX_C(5));

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,100,1400,2000,5400,6000};
	_paFrame_NextEvent = new frame[6];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 6;
	requestActor(50000002, EnemyHisbe, "EnemyHisbe-50000002");
    // gen01 end
}

void Stage01PartWall::initialize() {
    WallScene::initialize(); //�d�v�B�ǃf�|�W�g���̏����V�[����z����
}

void Stage01PartWall::onActive() {
    pCOMMON_SCENE->setScrollingFunction(CommonScene::scrollX);
    pCOMMON_SCENE->setScrollSpeed(getScrollSpeed());
    _TRACE_(FUNC_NAME<<"  CommonScene �ɂ��X�N���[����ݒ肵�܂��B");
    //pCOMMON_SCENE->dump();
    WallScene::onActive();
}

void Stage01PartWall::processBehavior() {
    WallScene::processBehavior();

    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 100: {
				EnemyHisbe* p = (EnemyHisbe*)receiveActor(50000002);
				bringSceneMediator()->appendGroupChild(p);
				p->_x = PX_C(2000);
				p->_y = 0;
				p->_z = 1000000;
				//a
				break;
			}
			case 1400: {
				requestActor(50000000, FormationUnomia001a, "FormationUnomia001a-50000000");
				break;
			}
			case 2000: {
				bringSceneMediator()->appendGroupChild(receiveActor(50000000));
				break;
			}
			case 5400: {
				requestActor(50000001, FormationUnomia001b, "FormationUnomia001b-50000001");
				break;
			}
			case 6000: {
				bringSceneMediator()->appendGroupChild(receiveActor(50000001));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 6-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

///////////////�f�o�b�O///////////////////////////////
    if (GgafDx::Input::isPressedKey(DIK_PGUP)) {
        addScrollSpeed(PX_C(1));
        pCOMMON_SCENE->addScrollSpeed(PX_C(1));
    }
    if (GgafDx::Input::isPressedKey(DIK_PGDN)) {
        addScrollSpeed(PX_C(-1));
        pCOMMON_SCENE->addScrollSpeed(PX_C(-1));
    }
//////////////////////////////////////////////////////
}

void Stage01PartWall::onFinishedAllSection() {
    _TRACE_(" Stage01PartWall::onFinishedAllSection()  CommonScene �̃X�N���[�����������܂��B");
    pCOMMON_SCENE->setScrollingFunction(nullptr);
    pCOMMON_SCENE->setScrollSpeed(0);
    throwEventUpperTree(EVENT_STAGE01_PART_WALL_WAS_FINISHED);
}

Stage01PartWall::~Stage01PartWall() {

}
