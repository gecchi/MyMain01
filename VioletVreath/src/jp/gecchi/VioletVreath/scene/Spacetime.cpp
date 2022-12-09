#include "Spacetime.h"


#include "jp/ggaf/core/util/LinearQuadtree.h"
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"

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
        WorldCollisionChecker::_num_check = 0;
#endif
        //本シーンの所属シーンの所属アクター全てについて当たり判定チェックを行う。
        //空間分割(八分木)アルゴリズムにより、チェック回数の最適化を行っています。
        //詳細は 「種別相関定義コピペツール.xls」 の 「種別相関」 シート参照
#ifdef MY_DEBUG
        if (GgafDx::Input::isPushedDownKey(DIK_I)) {
           getLinearOctree()->putTree();
        }
#endif
        //八分木アルゴリズムでヒットチェック
        executeWorldHitCheck(KIND_CHIKEI, KIND_MY_CHIKEI_HIT|KIND_ENEMY_CHIKEI_HIT|KIND_ITEM_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_HIT);
        executeWorldHitCheck(KIND_ITEM, KIND_MY_BODY_CHIKEI_HIT);
        executeWorldHitCheck(KIND_MY, KIND_ENEMY_BODY);
        executeWorldHitCheck(KIND_ENEMY_SHOT, KIND_MY_BODY);

#ifdef MY_DEBUG
        if (GgafDx::Input::isPushedDownKey(DIK_J)) {
            _TRACE_("Board用四分木 -->");
            _pLinearQuadtree_b->putTree();
            _TRACE_("<--Board用四分木");
        }
#endif
        executeViewHitCheck(KIND_2DFIX_MOUSE_POINTER, KIND_2DFIX_MENU_ITEM);
    }
}

Spacetime::~Spacetime() {
}
