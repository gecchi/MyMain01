
#include "TestScene.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/lib/actor/CappedGraphBarActor.h"
#include "jp/ggaf/lib/actor/debug/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/debug/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/debug/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/debug/ColliSphereActor.h"
#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"
#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"
#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"
//#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultBoneAniMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultDynaD3DXMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultFramedBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultFramedSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/actor/DefaultMassBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMassPointSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteSetActor.h"
#include "jp/ggaf/lib/actor/DefaultRegularPolygonBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultRegularPolygonSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultSceneChief.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"
#include "jp/ggaf/lib/actor/FramedHorizontalBarActor.h"
#include "jp/ggaf/lib/actor/GraphBarActor.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/actor/laserchip/NomalLaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/ggaf/lib/actor/PieGraphSpriteActor.h"
#include "jp/ggaf/lib/actor/SingleLaser.h"
#include "jp/ggaf/lib/actor/SpriteMeshActor.h"
#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"
#include "jp/ggaf/lib/actor/SpriteMeshWorldBoundActor.h"
#include "jp/ggaf/lib/actor/wall/CubeMapMassWallActor.h"
#include "jp/ggaf/lib/actor/wall/MassWallActor.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"

using namespace GgafLib;
using namespace Mogera;

enum {
    PHASE_READY ,
    PHASE_DISP ,
    PHASE_CALM_DOWN ,
    PHASE_WAIT ,
    PHASE_BANPEI,
};

#define requestTestActor(X,Y,Z) requestActor(X, TestActor<Y>, "Test" #Y, Z)
template<class T>
class TestActor : public T {
public:
    TestActor(const char* prm_name, const char* prm_model) : T(prm_name, prm_model) {
        T::setHitAble(false);
    }
    void initialize() override {  }
    void processBehavior() override { T::addRyFaceAng(D_ANG(1));  }
    void processJudgement() override {}
    virtual ~TestActor() {}
};

#define ID_ORDER_BEGIN 111
TestScene::TestScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TestScene";
    _id_ = 0;
    order_id_begin_ = ID_ORDER_BEGIN;
    order_id_end_ = 0;
    getPhase()->reset(PHASE_READY);
}


void TestScene::initialize() {
    GgafDx::Input::updateMouseState();
    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
    _id_ = 0;
}

void TestScene::processBehavior() {
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_READY: {
            if (pPhase->getFrame() == 20) {
                order_id_begin_ = ID_ORDER_BEGIN;
                int id = order_id_begin_;
//                requestTestActor(id, CubeMapMeshActor                   ,"_chk_TestCubeMapMeshActorModel"                     );    id++;
//                requestTestActor(id, CubeMapMeshSetActor                ,"_chk_TestCubeMapMeshSetActorModel"                  );    id++;
//                requestTestActor(id, CubeMapMorphMeshActor              ,"_chk_TestCubeMapMorphMeshActorModel"              );    id++;
////                requestTestActor(id, DefaultD3DXAniMeshActor            ,"_chk_TestDefaultD3DXAniMeshActorModel"              );    id++;
//                requestTestActor(id, DefaultBoneAniMeshActor                ,"_chk_TestDefaultBoneAniMeshActorModel"                  );    id++;
//                requestTestActor(id, DefaultD3DXMeshActor                ,"_chk_TestDefaultD3DXMeshActorModel"                  );    id++;
//                requestTestActor(id, DefaultMeshActor                   ,"_chk_TestDefaultMeshActorModel"                     );    id++;
//                requestTestActor(id, DefaultMeshSetActor                ,"_chk_TestDefaultMeshSetActorModel"                  );    id++;
//                requestTestActor(id, DefaultMassMeshActor               ,"_chk_TestDefaultMassMeshActorModel"                 );    id++;
//                requestTestActor(id, DefaultMorphMeshActor              ,"_chk_TestDefaultMorphMeshActorModel"              );    id++;
//                requestTestActor(id, DefaultMassMorphMeshActor          ,"_chk_TestDefaultMassMorphMeshActorModel"          );    id++;
//                requestTestActor(id, DefaultPointSpriteActor            ,"_chk_TestDefaultPointSpriteActorModel"              );    id++;
//                requestTestActor(id, DefaultPointSpriteSetActor         ,"_chk_TestDefaultPointSpriteSetActorModel"           );    id++;
//                requestTestActor(id, DefaultSpriteActor                 ,"_chk_TestDefaultSpriteActorModel"                   );    id++;
//                requestTestActor(id, DefaultSpriteSetActor              ,"_chk_TestDefaultSpriteSetActorModel"                );    id++;
//                requestTestActor(id, DefaultMassSpriteActor             ,"_chk_TestDefaultMassSpriteActorModel"               );    id++;
//                requestTestActor(id, DefaultRegularPolygonSpriteActor   ,"_chk_TestDefaultRegularPolygonSpriteActorModel");         id++;
//                requestTestActor(id, FontSpriteActor                    ,"_chk_TestFontSpriteActorModel"                      );    id++;
//                requestTestActor(id, SpriteMeshActor                    ,"_chk_TestSpriteMeshActorModel"                      );    id++;
//                requestTestActor(id, SpriteMeshSetActor                 ,"_chk_TestSpriteMeshSetActorModel"                   );    id++;
//                requestTestActor(id, NomalLaserChip                     ,"_chk_TestNomalLaserChipModel"                       );    id++;
//                requestTestActor(id, SingleLaser                        ,"_chk_TestSingleLaserModel"                          );    id++;
//
//                requestTestActor(id, DefaultBoardActor                  ,"_chk_TestDefaultBoardActorModel"                    );    id++;
//                requestTestActor(id, DefaultBoardSetActor               ,"_chk_TestDefaultBoardSetActorModel"                 );    id++;
//                requestTestActor(id, DefaultMassBoardActor              ,"_chk_TestDefaultMassBoardActorModel"                );    id++;
                requestTestActor(id, DefaultFramedBoardActor            ,"_chk_TestDefaultFramedBoardActorModel"              );    id++;
                requestTestActor(id, DefaultFramedSpriteActor           ,"_chk_TestDefaultFramedSpriteActorModel"             );    id++;
//                requestTestActor(id, DefaultRegularPolygonBoardActor    ,"_chk_TestDefaultRegularPolygonBoardActorModel" );    id++;
//                requestTestActor(id, FontBoardActor                     ,"_chk_TestFontBoardActorModel"                        );    id++;

//                requestTestActor(id, HoshiBoshi                         ,"_chk_TestHoshiBoshiModel"                           );    id++;

                order_id_end_ = id - 1;

                pPhase->changeNext();
            }
            break;
        }
        case PHASE_DISP: {
            if (pPhase->hasJustChanged()) {
                _id_ = 0;
            }
            if (pPhase->getFrame() % 10U == 0 && pCARETAKER->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                if (_id_ > order_id_end_-order_id_begin_) {
                    pPhase->changeNext();
                } else {
                    GgafDx::GeometricActor* pActor = (GgafDx::GeometricActor*)receiveActor(_id_+order_id_begin_);
                    if (pActor->_pFunc_calc_rot_mv_world_matrix) {
                        pActor->setPosition(PX_C(_id_*40 - 450), PX_C(-200+_id_*10), 0);
                    } else {
                        pActor->setPosition(PX_C(_id_*40), PX_C(_id_*10), 0);
                    }
                    getSceneChief()->appendGroupChild(pActor);
                    _id_++;
                }
            }
            if (pPhase->getFrame() > 60*120) {
                //タイムアウト
                _TRACE_("PreDrawScene Time Out!!");
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_CALM_DOWN: {
            if ((pPhase->getFrame() > 60 && pCARETAKER->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) || pPhase->getFrame() > 60*60) {
//                fadeoutSceneWithBgmTree(120);
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_WAIT: {
            //World シーンが sayonara をしてくれるまで・・
            break;
        }
    }
}

TestScene::~TestScene() {
}

