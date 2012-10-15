#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : WalledScene(prm_name) {
    _class_name = "Stage01WalledScene";

    //********* 壁情報 ***********
    coord wall_dep    = 400000;  //壁ブロックモデル１個のX軸方向の幅
    coord wall_width  = 100000;  //壁ブロックモデル１個のZ軸方向の幅
    coord wall_height = 100000;  //壁ブロックモデル１個のY軸方向の幅
    float scale_r = 50.0f;       //壁ブロックモデルの元の大きさからの拡大率
    //****************************

    //壁ブロック(直方体)デポジトリ生成
    WallAABActor* pWallAABActor;
    GgafActorDepository* pDepo_WallAAB = NEW GgafActorDepository("Dp_WallAAB");
    for (int i = 0; i < 1500; i++) {
        std::string name = "Wall001_"+ITOS(i);
        pWallAABActor = NEW Wall001(name.c_str());
        pWallAABActor->setScaleR(scale_r);
        pDepo_WallAAB->addSubLast(pWallAABActor);
    }
    P_COMMON_SCENE->getDirector()->addSubGroup(pDepo_WallAAB);
    //getDirector()->addSubGroup(pDepo_WallAAB); は P_UNIVERSE 配下になってしまう

    //壁ブロック(プリズム)デポジトリ生成
    WallAAPrismActor* pWallAAPrismActor;
    GgafActorDepository* pDepo_WallAAPrism = NEW GgafActorDepository("Dp_WallAAPrism");
    for (int i = 0; i < 500; i++) {
        std::string name = "Wall001Prism_"+ITOS(i);
        pWallAAPrismActor = NEW Wall001Prism(name.c_str());
        pWallAAPrismActor->setScaleR(scale_r);
        pDepo_WallAAPrism->addSubLast(pWallAAPrismActor);
    }
    P_COMMON_SCENE->getDirector()->addSubGroup(pDepo_WallAAPrism);

    //シーンセクション生成
    WalledSectionScene* apSection[] = {
        NEW Stage01WalledSection001("Stage01-001-0", this, "scene4_wall_0.dat"),
        NEW Stage01WalledSection001("Stage01-001-1", this, "scene4_wall_1.dat"),
        NEW Stage01WalledSection001("Stage01-001-2", this, "scene4_wall_2.dat"),
        NEW Stage01WalledSection001("Stage01-001-3", this, "scene4_wall_3.dat"),
    };

    //構築
    buildWalledScene(
        wall_dep*scale_r, wall_width*scale_r, wall_height*scale_r,
        GgafDxUniverse::_X_goneRight*20,
        (WalledSectionScene**)&apSection, 4,
        pDepo_WallAAB ,pDepo_WallAAPrism
    );

    //初期スクロールスピード
    setScrollSpeed(40000);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {30000};
	_paFrame_NextEvent = new frame[1];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1;
    // gen01 end
}

void Stage01WalledScene::initialize() {
    WalledScene::initialize(); //重要
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

    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 30000: {
				// WalledScene は終わったよイベント通知不要
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 1-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end
}

Stage01WalledScene::~Stage01WalledScene() {

}
