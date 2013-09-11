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
#include "jp/ggaf/lib/util/AmountGraph.h"
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

//    MgrActor* pMgrActor1 = NEW MgrActor("TEST1");
//    pMgrActor1->position(C_X, C_Y);
//    getSceneDirector()->addSubGroup(pMgrActor1);


    pBarVal_ = NEW AmountGraph();
    pBarVal_->config(200, 200);
    pBarVal_->set(200);
    TestBar* pTestBar = NEW TestBar("TEST1",pBarVal_);
    pTestBar->position(C_X, C_Y);
    getSceneDirector()->addSubGroup(pTestBar);

    pTeki_ = NEW Teki001("Teki001");
    getSceneDirector()->addSubGroup(MGR_TEKI, pTeki_);

    pMikata_ = NEW Mikata001("Mikata001");
    getSceneDirector()->addSubGroup(MGR_MIKATA, pMikata_) ;

    LabelGecchi16Font* pMsg = NEW LabelGecchi16Font("Msg");
    pMsg->update("HELLO!");
    pMsg->position(LT_X, LT_Y);
    getSceneDirector()->addSubGroup(pMsg);
    VirtualButton::_keyboardmap.BUTTON1 = DIK_SPACE; //�{�^���P=�X�y�[�X�L�[ �Ƃ���B
    VirtualButton::_keyboardmap.UI_DEBUG = DIK_Q;
    vb_ = NEW VirtualButton();
}

void MgrWorld::initialize() {
    pTeki_->position(0, PX_C(240));
    pMikata_->position(0, PX_C(-240));
}

void MgrWorld::processBehavior() {
    //�L�������{�^�����͂ňړ�
    vb_->update(); //���͏󋵍X�V
    if (vb_->isBeingPressed(VB_RIGHT)) {
        pBarVal_->inc(2);
        _TRACE_("+ pBarVal_="<<pBarVal_->get()<<"");
    }
    if (vb_->isBeingPressed(VB_LEFT)) {
        pBarVal_->inc(-2);
        _TRACE_("- pBarVal_="<<pBarVal_->get()<<"");
    }
    //���C���t���[���\���ؑ�
    if (vb_->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
}

void MgrWorld::processJudgement() {
    //�����蔻��`�F�b�N
    CollisionChecker3D::_pLinearOctree->executeAllHitChk(MGR_MIKATA, MGR_TEKI);
    //executeAllHitChk �� processJudgement() �ŌĂԕK�v����
    //(processBehavior())�ł͂܂��o�^����Ă��Ȃ�)
}

MgrWorld::~MgrWorld() {
    GGAF_DELETE(pBarVal_);
}


