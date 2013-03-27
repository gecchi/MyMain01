#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : WalledScene(prm_name) {
    _class_name = "Stage01WalledScene";

    //********* 壁情報 ***********
    coord wall_dep    = DX_C(40);  //壁ブロックモデル１個のX軸方向の幅設定（Xファイルにより決まる）
    coord wall_width  = DX_C(10);  //壁ブロックモデル１個のZ軸方向の幅設定（Xファイルにより決まる）
    coord wall_height = DX_C(10);  //壁ブロックモデル１個のY軸方向の幅設定（Xファイルにより決まる）
    float scale_r = 6.0f;        //今回壁ブロックの拡大率（任意）
    //****************************

    //壁ブロック(直方体)デポジトリ生成
    WallAABActor* pWallAABActor;
    GgafActorDepository* pDepo_WallAAB = NEW GgafActorDepository("Dp_WallAAB");
    for (int i = 0; i < 1000; i++) {
        std::string name = "Wall001_"+XTOS(i);
        pWallAABActor = NEW Wall001(name.c_str());
        pWallAABActor->setScaleR(scale_r);
        pDepo_WallAAB->addSubLast(pWallAABActor);
        Sleep(1);
    }
    P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepo_WallAAB);
    //getSceneDirector()->addSubGroup(pDepo_WallAAB); は P_UNIVERSE 配下になってしまう

    //壁ブロック(プリズム)デポジトリ生成
    WallAAPrismActor* pWallAAPrismActor;
    GgafActorDepository* pDepo_WallAAPrism = NEW GgafActorDepository("Dp_WallAAPrism");
    for (int i = 0; i < 100; i++) {
        std::string name = "Wall001Prism_"+XTOS(i);
        pWallAAPrismActor = NEW Wall001Prism(name.c_str());
        pWallAAPrismActor->setScaleR(scale_r);
        pDepo_WallAAPrism->addSubLast(pWallAAPrismActor);
        Sleep(1);
    }
    P_COMMON_SCENE->getSceneDirector()->addSubGroup(pDepo_WallAAPrism);

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
        GgafDxUniverse::_X_gone_right,
        (WalledSectionScene**)&apSection, 4,
        pDepo_WallAAB ,pDepo_WallAAPrism
    );

    //初期スクロールスピード
    setScrollSpeed(10000);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
  frame f[] = {1,200,1000,2000,2200,3200,4000,4200,5000,5200,6000,6200,7000,8000,30000};
  _paFrame_NextEvent = new frame[15];
  memcpy(_paFrame_NextEvent, f, sizeof(f));
  _event_num = 15;
  orderActorToFactory(20000006, FormationThalia, "FormationThalia-1");
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
      case 1: {
        break;
      }
      case 200: {
        orderActorToFactory(20000004, FormationEunomia001a, "FormationEunomia001a-2");
        break;
      }
      case 1000: {
        FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(20000006);
        getSceneDirector()->addSubGroup(pF);
        break;
      }
      case 2000: {
        FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(20000004);
        getSceneDirector()->addSubGroup(pFormationEunomia);
        break;
      }
      case 2200: {
        orderActorToFactory(20000007, FormationThalia, "FormationThalia-3");
        break;
      }
      case 3200: {
        orderActorToFactory(20000000, EnemyHesperia, "EnemyHesperia-4");
        orderActorToFactory(20000003, VarietySylvia003, "VarietySylvia003-5");
        break;
      }
      case 4000: {
        FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(20000007);
        getSceneDirector()->addSubGroup(pF);
        break;
      }
      case 4200: {
        orderActorToFactory(20000005, FormationEunomia001b, "FormationEunomia001b-6");
        break;
      }
      case 5000: {
        EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(20000000);
        getSceneDirector()->addSubGroup(p);
        VarietySylvia003* pSylviaB = (VarietySylvia003*)obtainActorFromFactory(20000003);
        getSceneDirector()->addSubGroup(pSylviaB);
        break;
      }
      case 5200: {
        orderActorToFactory(20000008, FormationThalia, "FormationThalia-7");
        break;
      }
      case 6000: {
        FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(20000005);
        getSceneDirector()->addSubGroup(pFormationEunomia);
        break;
      }
      case 6200: {
        orderActorToFactory(20000001, EnemyHesperia, "EnemyHesperia-8");
        orderActorToFactory(20000002, VarietySylvia002, "VarietySylvia002-9");
        break;
      }
      case 7000: {
        FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(20000008);
        getSceneDirector()->addSubGroup(pF);
        break;
      }
      case 8000: {
        EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(20000001);
        getSceneDirector()->addSubGroup(p);
        VarietySylvia002* pSylviaA = (VarietySylvia002*)obtainActorFromFactory(20000002);
        getSceneDirector()->addSubGroup(pSylviaA);
        break;
      }
      case 30000: {
        // WalledScene は終わったよイベント通知不要
        break;
      }
      default :
        break;
    }
    _cnt_event = (_cnt_event < 15-1 ? _cnt_event+1 : _cnt_event);
  }
    // gen02 end
}

void Stage01WalledScene::onFinishedSection() {
    throwEventUpperTree(EVENT_STG01_WALLED_WAS_BROKEN);
}

Stage01WalledScene::~Stage01WalledScene() {

}
