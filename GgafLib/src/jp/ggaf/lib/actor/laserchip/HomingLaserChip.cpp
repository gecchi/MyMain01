#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"



using namespace GgafLib;

HomingLaserChip::HomingLaserChip(const char* prm_name, const char* prm_model) :
            LaserChip(prm_name, prm_model) {
    _class_name = "HomingLaserChip";
    _is_leader = false;

    _begining_x = _x;
    _begining_y = _y;
    _begining_z = _z;
    _begining_rx = _rx;
    _begining_ry = _ry;
    _begining_rz = _rz;
    _begining_rz_mv = getLocoVehicle()->_rz_mv;
    _begining_ry_mv = getLocoVehicle()->_ry_mv;
    _begining_velo_mv   = getLocoVehicle()->_velo_mv;
    _prev_x = _x;
    _prev_y = _y;
    _prev_z = _z;
    _prev_rx = _rx;
    _prev_ry = _ry;
    _prev_rz = _rz;
    _prev_rz_mv = getLocoVehicle()->_rz_mv;
    _prev_ry_mv = getLocoVehicle()->_ry_mv;
    _prev_velo_mv   = getLocoVehicle()->_velo_mv;
    _is_fix_begin_pos = true;
}

void HomingLaserChip::onActive() {
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    HomingLaserChip* pChip_infront =  (HomingLaserChip*)_pChip_infront;
    //レーザーチップ出現時処理
    if (pChip_infront == nullptr) {
        //_TRACE_(FUNC_NAME<<" "<<getName()<<" pChip_infront == nullptr");
        _is_leader = true;
        //自身が先頭の場合
        _begining_x = _x;
        _begining_y = _y;
        _begining_z = _z;
        _begining_rx = _rx;
        _begining_ry = _ry;
        _begining_rz = _rz;
        _begining_rz_mv = pLocoVehicle->_rz_mv;
        _begining_ry_mv = pLocoVehicle->_ry_mv;
        _begining_velo_mv   = pLocoVehicle->_velo_mv;
    } else {
        _is_leader = false;
        //_TRACE_(FUNC_NAME<<" "<<getName()<<" pChip_infront =="<<(pChip_infront->getName()));
        _begining_x = pChip_infront->_begining_x;
        _begining_y = pChip_infront->_begining_y;
        _begining_z = pChip_infront->_begining_z;
        _begining_rx = pChip_infront->_begining_rx;
        _begining_ry = pChip_infront->_begining_ry;
        _begining_rz = pChip_infront->_begining_rz;
        _begining_rz_mv = pChip_infront->_begining_rz_mv;
        _begining_ry_mv = pChip_infront->_begining_ry_mv;
        _begining_velo_mv   = pChip_infront->_begining_velo_mv;
        if (_is_fix_begin_pos) {
            _x = _begining_x;
            _y = _begining_y;
            _z = _begining_z;
            _rx = _begining_rx;
            _ry = _begining_ry;
            _rz = _begining_rz;
            pLocoVehicle->setRzRyMvAng(_begining_rz_mv, _begining_ry_mv);
            pLocoVehicle->setMvVelo(_begining_velo_mv);
        }
    }
}

void HomingLaserChip::onInactive() {
    //_TRACE_("A HomingLaserChip::onInactive() _chip_kind ="<<_chip_kind <<")");
    LaserChip* pChip_behind = _pChip_behind;
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();

    if (pChip_behind) {
        //先頭しか動かしていないので、
        //何も考慮しないと、後方チップがその場で停止してしまう。
        //後方チップへ移動のための情報を無理やり設定して移動を継続させる。
        //先端チップ Mover 内部パラメータの移動方向と移動速度の情報をコピーすることでOK
        GgafDx::LocoVehicle* pChip_behind_pLocoVehicle = pChip_behind->getLocoVehicle();
        pChip_behind->_rx = _rx;
        pChip_behind->_ry = _ry;
        pChip_behind->_rz = _rz;
        pChip_behind_pLocoVehicle->setRzRyMvAng(pLocoVehicle->_rz_mv, pLocoVehicle->_ry_mv);
        pChip_behind_pLocoVehicle->setMvVelo(pLocoVehicle->_velo_mv);
    }

    LaserChip::onInactive(); //つながりを切断処理
}

void HomingLaserChip::processBehavior() {
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの processBehavior() メソッドも呼び出してください。
    //座標に反映
    const HomingLaserChip* const pChip_infront =  (HomingLaserChip*)_pChip_infront;
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    if (getActiveFrame() > 1) {
        //ActorDepository::dispatch() は
        //取得できる場合、ポインタを返すと共に、そのアクターはアクター発送者の子の一番後ろに移動される。
        //したがって、レーザーの先頭から順番にprocessBehavior() が呼ばれるため、以下のようにすると
        //数珠繋ぎになる。
        if (pChip_infront == nullptr) {
            //本当の先頭チップか、或いはにわか先頭チップの場合の共通処理
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_rz_mv = pLocoVehicle->_rz_mv;
            _prev_ry_mv = pLocoVehicle->_ry_mv;
            _prev_velo_mv   = pLocoVehicle->_velo_mv;
            processBehaviorHeadChip(); //先頭チップのみ移動実装
        } else {
            //先頭以外のチップ数珠繋ぎ処理
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_rz_mv = pLocoVehicle->_rz_mv;
            _prev_ry_mv = pLocoVehicle->_ry_mv;
            _prev_velo_mv   = pLocoVehicle->_velo_mv;
            _x  = pChip_infront->_prev_x;
            _y  = pChip_infront->_prev_y;
            _z  = pChip_infront->_prev_z;
            _rx = pChip_infront->_prev_rx;
            _ry = pChip_infront->_prev_ry;
            _rz = pChip_infront->_prev_rz;
            pLocoVehicle->setRzRyMvAng(pChip_infront->_prev_rz_mv, pChip_infront->_prev_ry_mv);
            pLocoVehicle->setMvVelo(pChip_infront->_prev_velo_mv);
        }
    }
}

HomingLaserChip::~HomingLaserChip() {
}

