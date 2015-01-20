#include "PreDrawScene.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
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
#include "jp/gecchi/VioletVreath/actor/_predrawer/StringBoardTestActor.h"
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
//    orderActorToFactory(id, StringBoardTestActor       , "StringBoardTestActor");           id++;
    orderActorToFactory(id, WallAABTestActor           , "WallAABTestActor");               id++;
    orderActorToFactory(id, WallAAPrismTestActor       , "WallAAPrismTestActor");           id++;
    order_id_end_ = id - 1;
    useProgress();
    getProgress()->reset(PreDrawScene::PROG_INIT);
}

void PreDrawScene::onReset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
    _id_ = 0;


//    GgafDxDrawableActor* x;
//    x = (GgafDxDrawableActor*)(new MenuActor<CubeMapMeshActor       >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<CubeMapMeshSetActor    >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<CubeMapMorphMeshActor  >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultD3DXAniMeshActor>("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultBoardActor      >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultBoardSetActor   >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultMeshActor       >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultMeshSetActor    >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultMorphMeshActor  >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultPointSpriteActor>("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultSpriteActor     >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultSpriteSetActor  >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<SpriteMeshActor        >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<SpriteMeshSetActor     >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<StringBoardActor       >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<WallAABActor           >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<WallAAPrismActor       >("aaa","bbb"));

}

void PreDrawScene::processBehavior() {
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PreDrawScene::PROG_INIT: {
            if (pProg->getFrameInProgress() % 20U == 0 && P_GOD->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                if (_id_ > order_id_end_-order_id_begin_) {
                    pProg->changeNext();
                } else {
                    GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)obtainActorFromFactory(_id_+order_id_begin_);
                    pActor->position(PX_C(_id_*70 - 500), PX_C(-100), 0);
                    getSceneDirector()->addSubGroup(pActor);  _id_++;
                }
            }
            if (pProg->getFrameInProgress() > 60*120) {
                //タイムアウト
                _TRACE_("PreDrawScene Time Out!!");
                pProg->changeNext();
            }
            break;
        }
        case PreDrawScene::PROG_CALM: {
            if ((pProg->getFrameInProgress() > 60 && P_GOD->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) ||
                 pProg->getFrameInProgress() > 60*60) {
                fadeoutSceneWithBgmTree(120);
                pProg->changeNext();
            }
            break;
        }
        case PreDrawScene::PROG_WAIT: {
            //World シーンが sayonara をしてくれるまで・・
            break;
        }
    }

//
//    if (getActiveFrame() == 1) {
////
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMeshTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMeshSetTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMorphMeshTestActor
//        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultD3DXAniMeshTestActor
//////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultBoardTestActor
//////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultBoardSetTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMeshTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMeshSetTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMorphMeshTestActor
//////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultPointSpriteTestActor
//////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultSpriteTestActor
//////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultSpriteSetTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //LaserChipTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SingleLaserTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SpriteMeshTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SpriteMeshSetTestActor
//////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //StringBoardTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //WallAABTestActor
////        getSceneDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //WallAAPrismTestActor
//    }

}

PreDrawScene::~PreDrawScene() {
}
