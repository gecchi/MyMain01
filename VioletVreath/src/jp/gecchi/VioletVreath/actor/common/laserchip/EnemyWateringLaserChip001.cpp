#include "EnemyWateringLaserChip001.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyWateringLaserChip001::EnemyWateringLaserChip001(const char* prm_name) :
        VvEnemyActor<WateringLaserChip>(prm_name, "EnemyWateringLaserChip001", StatusReset(EnemyWateringLaserChip001)) {
    _class_name = "EnemyWateringLaserChip001";
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
}

void EnemyWateringLaserChip001::initialize() {
    getLocoVehicle()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(50000);
    setHitAble(true);
    setScaleR(6.0);
    setCullingDraw(false);
}

void EnemyWateringLaserChip001::onCreateModel() {

}

void EnemyWateringLaserChip001::onActive() {
    WateringLaserChip::onActive();
    getLocoVehicle()->setMvVelo(PX_C(100));
    getLocoVehicle()->setMvAcce(PX_C(5));
    getStatus()->reset();
}

void EnemyWateringLaserChip001::processBehavior() {
    if (hasJustChangedToActive()) {
        //アクティブになった瞬間は、
        //利用元アクターが指定した最初の座標で表示したい。
        //移動車両の活動を行うと、ずれるので、最初だけはそのままの座標で表示。
        //とはいうものの、発射元は１フレーム分移動してるので、ピッタリには見えないかもしれない。
    } else {
        GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
        pLocoVehicle->behave();
    }
    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと

    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
}

void EnemyWateringLaserChip001::processSettlementBehavior() {
    //平均曲線座標設定。(レーザーを滑らかにするノーマライズ）
    //processSettlementBehavior() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、全レーザーチップが移動後でないと意味がないので
    //仕方ないのでprocessSettlementBehavior()に食い込んでいます。
    if (getActiveFrame() > 3) {
        EnemyWateringLaserChip001* pF = (EnemyWateringLaserChip001*)getInfrontChip();
        EnemyWateringLaserChip001* pB = (EnemyWateringLaserChip001*)getBehindChip();
        if (pF && pB && pF->isActive() && pB->isActive()) {
            //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
            //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
            //_x,_y,_z にはまだ変な値が入っている。
            //中間座標に再設定
            _x = ((pF->tmp_x_ + pB->tmp_x_)/2 + tmp_x_)/2;
            _y = ((pF->tmp_y_ + pB->tmp_y_)/2 + tmp_y_)/2;
            _z = ((pF->tmp_z_ + pB->tmp_z_)/2 + tmp_z_)/2;
        }
    }
    WateringLaserChip::processSettlementBehavior();
}

void EnemyWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyWateringLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    if (getActiveFrame() <= 2 && (pOther->lookUpKind() & KIND_CHIKEI)) {
        //出現2フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
        return;
    }

    bool is_stamina_zero = performEnemyHit(pOther);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}


EnemyWateringLaserChip001::~EnemyWateringLaserChip001() {
}

