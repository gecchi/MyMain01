#include "Spacetime.h"

#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

Spacetime::Spacetime(const char* prm_name, Camera* prm_pCamera) : DefaultSpacetime(prm_name, prm_pCamera) {
    _class_name = "Spacetime";
    pWorld_ = nullptr;
    _TRACE_(FUNC_NAME<<"");
    pCameraWorkerChanger_ = NEW VVCameraWorkerChanger("CameraWorkerChanger", prm_pCamera);
    bringSceneMediator()->appendGroupChild(pCameraWorkerChanger_);
    //【めも】
    //ここでActorやSceneのNEWをしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void Spacetime::initialize() {
    pWorld_ = desireScene(VioletVreath::World);
    appendChild(pWorld_);
    _TRACE_(FUNC_NAME<<"");
}

void Spacetime::processBehavior() {
    DefaultSpacetime::processBehavior();
}

void Spacetime::processJudgement() {
    DefaultSpacetime::processJudgement();

    if (getBehaveingFrame() >= 120) {
#ifdef MY_DEBUG
        CollisionChecker::_num_check = 0;
#endif
        //本シーンの所属シーンの所属アクター全てについて当たり判定チェックを行う。
        //空間分割(八分木)アルゴリズムにより、チェック回数の最適化を行っています。
        //詳細は 「種別相関定義コピペツール.xls」 の 「種別相関」 シート参照
        OctreeRounder* pHitCheckRounder = getLinearOctreeHitCheckRounder();
#ifdef MY_DEBUG
        if (GgafDx::Input::isPushedDownKey(DIK_I)) {
           getLinearOctree()->putTree();
        }
#endif
        //八分木アルゴリズムでヒットチェック
        static const kind_t group_A1 = KIND_CHIKEI;
        static const kind_t group_B1 = KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT;
        pHitCheckRounder->executeAll(group_A1, group_B1);

        static const kind_t group_A2 = KIND_ITEM;
        static const kind_t group_B2 = KIND_MY_BODY_CHIKEI_HIT;
        pHitCheckRounder->executeAll(group_A2, group_B2);

        static const kind_t group_A3 = KIND_MY;
        static const kind_t group_B3 = KIND_ENEMY_BODY;
        pHitCheckRounder->executeAll(group_A3, group_B3);

        static const kind_t group_A4 = KIND_ENEMY_SHOT;
        static const kind_t group_B4 = KIND_MY_BODY;
        pHitCheckRounder->executeAll(group_A4, group_B4);


        QuadtreeRounder_b* pHitCheckRounder_b = getLinearQuadtreeHitCheckRounder_b();
        pHitCheckRounder_b->executeAll(KIND_2DFIX_MOUSE_POINTER, KIND_2DFIX_MENU_ITEM);
    }
}

Spacetime::~Spacetime() {
}
