#include "stdafx.h"
#include "MgrWorld.h"

#include "actor/LabelGecchi16Font.h"
#include "actor/MgrActor.h"
#include "actor/Mikata001.h"
#include "actor/Teki001.h"
#include "actor/TestActor.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "util/MgrUtil.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "actor/TestBar.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

#define MGR_MIKATA 1
#define MGR_TEKI 2

MgrWorld::MgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pBack_ = NEW TestActor("haikei");
    pBack_->position(C_X, C_Y);
    getSceneDirector()->addSubGroup(pBack_);

    pMgrActor1_ = NEW MgrActor("TEST1");
    pMgrActor1_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    pMgrActor1_->position(C_X, C_Y);
    getSceneDirector()->addSubGroup(pMgrActor1_);
//    pBarVal_ = NEW PxQuantity();
//    pBarVal_->graduate(200, 200);
//    pBarVal_->set(200);

    pTestBar_ = NEW TestBar("TEST1");
    pTestBar_->graduatePx(200, 200);
    pTestBar_->setValue(200);
    pTestBar_->position(C_X, C_Y);
    getSceneDirector()->addSubGroup(pTestBar_);
    pTeki_ = NEW Teki001("Teki001");
    getSceneDirector()->addSubGroup(MGR_TEKI, pTeki_);

    pMikata_ = NEW Mikata001("Mikata001");
    getSceneDirector()->addSubGroup(MGR_MIKATA, pMikata_) ;

    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("Msg");
    pMsg->update("HELLO!");
    pMsg->position(LT_X, LT_Y);
    getSceneDirector()->addSubGroup(pMsg);
    VirtualButton::_keyboardmap.BUTTON1 = DIK_SPACE; //ボタン１=スペースキー とする。
    VirtualButton::_keyboardmap.UI_DEBUG = DIK_Q;
    vb_ = NEW VirtualButton();
}

void MgrWorld::initialize() {
    pTeki_->position(0, PX_C(240));
    pMikata_->position(0, PX_C(-240));
}


void MgrWorld::processBehavior() {
    //キャラをボタン入力で移動
    vb_->update(); //入力状況更新
    if (vb_->isBeingPressed(VB_RIGHT)) {
        pTestBar_->incValue(2);
        pMgrActor1_->_SX += 30;
    }
    if (vb_->isBeingPressed(VB_LEFT)) {
        pTestBar_->incValue(-2);
        pMgrActor1_->_SX -= 30;
    }
    //ワイヤフレーム表示切替
    if (vb_->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
}

void MgrWorld::processJudgement() {
    //当たり判定チェック
    CollisionChecker3D::_pLinearOctree->executeAllHitChk(MGR_MIKATA, MGR_TEKI);
    //executeAllHitChk は processJudgement() で呼ぶ必要あり
    //(processBehavior())ではまだ登録されていない)
}

MgrWorld::~MgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

