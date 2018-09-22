#include "Stage01PartWall.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "Stage01PartWall/Stage01PartWallSection001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartWall::Stage01PartWall(const char* prm_name) :
        Stage01Part(prm_name, EVENT_STAGE01_PART_WALL_WAS_FINISHED) {
    _class_name = "Stage01PartWall";

    //********* 壁情報 ***********
    coord wall_dep    = DX_C(40);  //壁ブロックモデル１個のX軸方向の幅設定（Xファイルにより決まる）
    coord wall_width  = DX_C(10);  //壁ブロックモデル１個のZ軸方向の幅設定（Xファイルにより決まる）
    coord wall_height = DX_C(10);  //壁ブロックモデル１個のY軸方向の幅設定（Xファイルにより決まる）
    float scale_r = 4.0f;        //今回壁ブロックの拡大率（ここで設定可能）
    //****************************

    //壁ブロック(直方体)デポジトリ生成
    MassWallActor* pWall;
    GgafActorDepository* pDepo_wall = NEW GgafActorDepository("Depo_Wall");
    for (int i = 0; i < 2000; i++) {
        std::string name = "Wall01_"+XTOS(i);
        pWall = NEW Wall01(name.c_str());
        pWall->setScaleR(scale_r);
        pDepo_wall->put(pWall);
    }
    bringSceneMediator()->addSubGroup(pDepo_wall);


//    //シーンセクション生成
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
//    //構築
//    buildWallScene(
//        wall_dep*scale_r, wall_width*scale_r, wall_height*scale_r,
//        pGOD->getSpacetime()->_x_bound_right,
//        (WallSectionScene**)&apSection, 8,
//        pDepo_wall
//    );
    //シーンセクション生成
    WallSectionScene* apSection[] = {
        NEW Stage01PartWallSection001("Stage01-001-0", this, "scene6_wall_0.dat"),
        NEW Stage01PartWallSection001("Stage01-001-1", this, "scene6_wall_1.dat"),
        NEW Stage01PartWallSection001("Stage01-001-2", this, "scene6_wall_2.dat"),
        NEW Stage01PartWallSection001("Stage01-001-3", this, "scene6_wall_3.dat"),
    };
    //構築
    buildWallScene(
        wall_dep*scale_r, wall_width*scale_r, wall_height*scale_r,
        pGOD->getSpacetime()->_x_bound_right,
        (WallSectionScene**)&apSection, 4,
        pDepo_wall
    );

    //初期スクロールスピード
    setScrollSpeed(PX_C(5));

    // 以下の gen01 start 〜 end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,1400,2000,5400,6000};
	_paFrame_NextEvent = new frame[6];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 6;
	requestActor(50000002, EnemyHisbe, "EnemyHisbe-50000002");
    // gen01 end
}

void Stage01PartWall::initialize() {
    WallScene::initialize(); //重要。壁デポジトリの所属シーンを配下に
}

void Stage01PartWall::onActive() {
    pCOMMON_SCENE->setScrollingFunction(CommonScene::scrollX);
    pCOMMON_SCENE->setScrollSpeed(getScrollSpeed());
    _TRACE_(FUNC_NAME<<"  CommonScene にもスクロールを設定します。");
    //pCOMMON_SCENE->dump();
    WallScene::onActive();
}

void Stage01PartWall::processBehavior() {
    WallScene::processBehavior();

    // 以下の gen02 start 〜 end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 100: {
				EnemyHisbe* p = (EnemyHisbe*)receiveActor(50000002);
				bringSceneMediator()->addSubGroup(p);
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
				bringSceneMediator()->addSubGroup(receiveActor(50000000));
				break;
			}
			case 5400: {
				requestActor(50000001, FormationUnomia001b, "FormationUnomia001b-50000001");
				break;
			}
			case 6000: {
				bringSceneMediator()->addSubGroup(receiveActor(50000001));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 6-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

///////////////デバッグ///////////////////////////////
    if (GgafDxInput::isPressedKey(DIK_PGUP)) {
        addScrollSpeed(PX_C(1));
        pCOMMON_SCENE->addScrollSpeed(PX_C(1));
    }
    if (GgafDxInput::isPressedKey(DIK_PGDN)) {
        addScrollSpeed(PX_C(-1));
        pCOMMON_SCENE->addScrollSpeed(PX_C(-1));
    }
//////////////////////////////////////////////////////
}

void Stage01PartWall::onFinishedAllSection() {
    _TRACE_(" Stage01PartWall::onFinishedAllSection()  CommonScene のスクロールを解除します。");
    pCOMMON_SCENE->setScrollingFunction(nullptr);
    pCOMMON_SCENE->setScrollSpeed(0);
    throwEventUpperTree(EVENT_STAGE01_PART_WALL_WAS_FINISHED);
}

Stage01PartWall::~Stage01PartWall() {

}
