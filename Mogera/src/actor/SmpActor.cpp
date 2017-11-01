#include "SmpActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAngAssistant.h"
using namespace Mogera;

SmpActor::SmpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Zako") { //Guruguru.x が参照される。
    //座標設定
    setPosition(PX_C(-200), 0, 0);
    getKuroko()->linkFaceAngByMvAng(true);
    getKuroko()->setMvVelo(PX_C(1));
}

void SmpActor::initialize() {
}

void SmpActor::processBehavior() {
    if (getActiveFrame() == 60) {
        getKuroko()->asstMvAng()->turnRzPendulum(D45ANG-1, -D45ANG+1,
                                                 10, TURN_CLOSE_TO,
                                                 60, 0.5, 0.5,
                                                 0, true);
//        getKuroko()->asstMvAng()->turnRyPendulum(D45ANG-1, -D45ANG+1,
//                                                 10, TURN_CLOSE_TO,
//                                                 60, 0.5, 0.5,
//                                                 0, true);
    }
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

SmpActor::~SmpActor() {
}
