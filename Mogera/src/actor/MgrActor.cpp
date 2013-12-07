#include "stdafx.h"
#include "actor/MgrActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "util/MgrUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrActor::MgrActor(const char* prm_name) :
        GgafLib::DefaultBoardActor(prm_name, "Test") {
    setAlpha(0.8);
}

void MgrActor::initialize() {
//    _pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(1));
//    _pScaler->forceRange(500, 3000);
//    _pScaler->beat(120, 60, 5, -1);
}

void MgrActor::processBehavior() {
//    _pScaler->behave();


//    if (GgafDxInput::isBeingPressedKey(DIK_P)) {
//        _sx+=10; _sy+=10;
//    }

//    _pKuroko->behave();
}

MgrActor::~MgrActor() {
}
