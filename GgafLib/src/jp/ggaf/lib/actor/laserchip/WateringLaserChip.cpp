#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"



using namespace GgafLib;

WateringLaserChip::WateringLaserChip(const char* prm_name, const char* prm_model) :
            LaserChip(prm_name, prm_model) {
    _class_name = "WateringLaserChip";
}

void WateringLaserChip::onActive() {
    //レーザーチップ出現時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
}

WateringLaserChip::~WateringLaserChip() {
}

