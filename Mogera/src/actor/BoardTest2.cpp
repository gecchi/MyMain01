#include "BoardTest2.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "actor/BoardTest2.h"
#include "MgrGod.h"

#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;


BoardTest2::BoardTest2(const char* prm_name) :
        DefaultRegularPolygonBoardActor(prm_name, "12,CW,BoardTest2") {
    _class_name = "BoardTest2";
}

void BoardTest2::onCreateModel() {
}

void BoardTest2::initialize() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 40);
//    GgafDxScaler* const pScaler = getScaler();
//    pScaler->setRange(R_SC(0.1), R_SC(1.5));
//    pScaler->beat(300, 100, 100, 100, -1);
//    setWidth(PX_C(32*4));
//    setHeight(PX_C(32*5));
}

void BoardTest2::onActive() {
}

void BoardTest2::processBehavior() {
     VirtualButton* pVb = P_GOD->getSpacetime()->pVb_;
    if (GgafDxInput::isPressedKey(DIK_C)) {
        setDrawFanNum(getDrawFanNum() + 1);
    }
    if (GgafDxInput::isPressedKey(DIK_V)) {
        setDrawFanNum(getDrawFanNum() - 1);
    }
    if (GgafDxInput::isPressedKey(DIK_Z)) {
        setBeginAngPos(getBeginAngPos() + D_ANG(1));
    }
    if (GgafDxInput::isPressedKey(DIK_X)) {
        setBeginAngPos(getBeginAngPos() - D_ANG(1));
    }
    if (GgafDxInput::isPressedKey(DIK_B)) {
        addRzFaceAng(D_ANG(1));
    }
    if (GgafDxInput::isPressedKey(DIK_N)) {
        addRzFaceAng(D_ANG(-1));
    }

    if (GgafDxInput::isPressedKey(DIK_Q)) {
        setAlign(ALIGN_LEFT);
    }
    if (GgafDxInput::isPressedKey(DIK_W)) {
        setAlign(ALIGN_CENTER);
    }
    if (GgafDxInput::isPressedKey(DIK_E)) {
        setAlign(ALIGN_RIGHT);
    }

    if (GgafDxInput::isPressedKey(DIK_A)) {
        setValign(VALIGN_TOP);
    }
    if (GgafDxInput::isPressedKey(DIK_S)) {
        setValign(VALIGN_MIDDLE);
    }
    if (GgafDxInput::isPressedKey(DIK_D)) {
        setValign(VALIGN_BOTTOM);
    }


    if (pVb->isPressed(VB_BUTTON1)) {
        //�{�^���P�i�X�y�[�X�L�[�j�������Ȃ���̏ꍇ
        if (pVb->isPressed(VB_UP)) {
            _z += PX_C(2); //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _z -= PX_C(2); //��O
        }
    } else {
        //�{�^���P�i�X�y�[�X�L�[�j�𗣂��Ă���ꍇ
        if (pVb->isPressed(VB_RIGHT)) {
            _x += PX_C(2); //�E
        }
        if (pVb->isPressed(VB_LEFT)) {
            _x -= PX_C(2); //��
        }
        if (pVb->isPressed(VB_UP)) {
            _y -= PX_C(2); //��
        }
        if (pVb->isPressed(VB_DOWN)) {
            _y += PX_C(2); //��
        }
    }

    getUvFlipper()->behave();
//    getScaler()->behave();
}

void BoardTest2::processJudgement() {
}

void BoardTest2::onHit(const GgafActor* prm_pOtherActor) {
}

void BoardTest2::onInactive() {
}

BoardTest2::~BoardTest2() {
}


