#include "PreDrawScene.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMorphMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultD3DXAniMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultBoardTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultBoardSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultD3DXMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMorphMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultPointSpriteTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultSpriteTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultSpriteSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/HoshiboshiTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/LaserChipTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SingleLaserTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SpriteMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SpriteMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/WallAABTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/WallAAPrismTestActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define ID_ORDER_BEGIN 11

PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";
    _id_ = 0;
    order_id_begin_ = ID_ORDER_BEGIN;
    int id = order_id_begin_;
    orderActorToFactory(id, CubeMapMeshTestActor       , "CubeMapMeshTestActor");           id++;
    orderActorToFactory(id, CubeMapMeshSetTestActor    , "CubeMapMeshSetTestActor");        id++;
    orderActorToFactory(id, CubeMapMorphMeshTestActor  , "CubeMapMorphMeshTestActor");      id++;
    orderActorToFactory(id, DefaultD3DXAniMeshTestActor , "DefaultD3DXAniMeshTestActor");   id++;
//    orderActorToFactory(id, DefaultBoardTestActor      , "DefaultBoardTestActor");          id++;
//    orderActorToFactory(id, DefaultBoardSetTestActor   , "DefaultBoardSetTestActor");       id++;
    orderActorToFactory(id, DefaultMeshTestActor       , "DefaultMeshTestActor");           id++;
    orderActorToFactory(id, DefaultMeshSetTestActor    , "DefaultMeshSetTestActor");        id++;
    orderActorToFactory(id, DefaultMorphMeshTestActor  , "DefaultMorphMeshTestActor");      id++;
//    orderActorToFactory(id, DefaultPointSpriteTestActor, "DefaultPointSpriteTestActor");    id++;
//    orderActorToFactory(id, DefaultSpriteTestActor     , "DefaultSpriteTestActor");         id++;
//    orderActorToFactory(id, DefaultSpriteSetTestActor  , "DefaultSpriteSetTestActor");      id++;
    orderActorToFactory(id, HoshiBoshiTestActor        , "HoshiBoshiTestActor");            id++;
    orderActorToFactory(id, LaserChipTestActor         , "LaserChipTestActor");             id++;
    orderActorToFactory(id, SingleLaserTestActor       , "SingleLaserTestActor");           id++;
    orderActorToFactory(id, SpriteMeshTestActor        , "SpriteMeshTestActor");            id++;
    orderActorToFactory(id, SpriteMeshSetTestActor     , "SpriteMeshSetTestActor");         id++;
    orderActorToFactory(id, WallAABTestActor           , "WallAABTestActor");               id++;
    orderActorToFactory(id, WallAAPrismTestActor       , "WallAAPrismTestActor");           id++;
    order_id_end_ = id - 1;
    useProgress();
    getProgress()->reset(PROG_DISP);
}

void PreDrawScene::onReset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
    _id_ = 0;


//    GgafDxFigureActor* x;
//    x = (GgafDxFigureActor*)(new MenuActor<CubeMapMeshActor       >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<CubeMapMeshSetActor    >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<CubeMapMorphMeshActor  >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultD3DXAniMeshActor>("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultBoardActor      >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultBoardSetActor   >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultMeshActor       >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultMeshSetActor    >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultMorphMeshActor  >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultPointSpriteActor>("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultSpriteActor     >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<DefaultSpriteSetActor  >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<SpriteMeshActor        >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<SpriteMeshSetActor     >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<WallAABActor           >("aaa","bbb"));
//    x = (GgafDxFigureActor*)(new MenuActor<WallAAPrismActor       >("aaa","bbb"));

}

void PreDrawScene::processBehavior() {
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_DISP: {
            if (pProg->getFrame() % 10U == 0 && pGOD->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                if (_id_ > order_id_end_-order_id_begin_) {
                    pProg->changeNext();
                } else {
                    GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)obtainActorFromFactory(_id_+order_id_begin_);
                    pActor->setPosition(PX_C(_id_*70 - 700), PX_C(-100), 0);
                    bringSceneMediator()->addSubGroup(pActor);  _id_++;
                }
            }
            if (pProg->getFrame() > 60*120) {
                //タイムアウト
                _TRACE_("PreDrawScene Time Out!!");
                pProg->changeNext();
            }
            break;
        }
        case PROG_CALM_DOWN: {
            if ((pProg->getFrame() > 30 && pGOD->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) ||
                 pProg->getFrame() > 60*60) {
                fadeoutSceneWithBgmTree(120);
                pProg->changeNext();
            }
            break;
        }
        case PROG_WAIT: {
            //World シーンが sayonara をしてくれるまで・・
            break;
        }
    }

//
//    if (getActiveFrame() == 1) {
////
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMeshTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMeshSetTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMorphMeshTestActor
//        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultD3DXAniMeshTestActor
//////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultBoardTestActor
//////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultBoardSetTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMeshTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMeshSetTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMorphMeshTestActor
//////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultPointSpriteTestActor
//////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultSpriteTestActor
//////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultSpriteSetTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //LaserChipTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SingleLaserTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SpriteMeshTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SpriteMeshSetTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //WallAABTestActor
////        bringSceneMediator()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //WallAAPrismTestActor
//    }

}

PreDrawScene::~PreDrawScene() {
}
