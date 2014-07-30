#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

RefractionLaserChip::RefractionLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "RefractionLaserChip";
    _is_leader = false;
    _num_refraction = 2;
    _frame_standstill_refraction = 10;
    _frame_between_refraction = 20;

    _cnt_refraction = 0;
    _frame_refraction_enter = 0;
    _frame_refraction_out = 0;
    _is_refracting = false;

    _pDispatche_RefractionEffect = nullptr;
    _pRefractionEffect = nullptr;
    _prev_pRefractionEffect = nullptr;

    _begining_x = _x;
    _begining_y = _y;
    _begining_z = _z;
    _begining_rx = _rx;
    _begining_ry = _ry;
    _begining_rz = _rz;
    _prev_x  = _x;
    _prev_y  = _y;
    _prev_z  = _z;
    _prev_rx = _rx;
    _prev_ry = _ry;
    _prev_rz = _rz;
    _prev_is_refracting = false;
    _is_fix_begin_pos = true;
}

void RefractionLaserChip::config(int prm_num_refraction,
                                 frame prm_frame_between_refraction,
                                 frame prm_frame_standstill_refraction,
                                 bool prm_is_fix_begin_pos,
                                 GgafActorDepository* prm_pDispatche_RefractionEffect) {
#ifdef MY_DEBUG
    if (prm_frame_between_refraction == 0) {
        throwGgafCriticalException("RefractionLaserChip::config 直進間隔フレーム数が0は設定不可です。name="<<getName());
    }
    if (prm_frame_standstill_refraction == 0) {
        throwGgafCriticalException("RefractionLaserChip::config 屈折溜フレーム数が0は設定不可です。name="<<getName());
    }
#endif
    _num_refraction = prm_num_refraction;
    _frame_between_refraction = prm_frame_between_refraction;
    _frame_standstill_refraction = prm_frame_standstill_refraction;
    _is_fix_begin_pos = prm_is_fix_begin_pos;
    _pDispatche_RefractionEffect = prm_pDispatche_RefractionEffect;
}

void RefractionLaserChip::onActive() {
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();

    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    //レーザーチップ出現時処理
    if (pChip_front == nullptr) {
        _is_leader = true;
        //自身が先頭の場合
        _begining_x = _x;
        _begining_y = _y;
        _begining_z = _z;
        _begining_rx = _rx;
        _begining_ry = _ry;
        _begining_rz = _rz;
        _cnt_refraction = 0;
        _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction;
        _frame_refraction_out = _frame_refraction_enter + _frame_standstill_refraction;
        //onRefractionBegin(_cnt_refraction);
        onRefractionFinish(_cnt_refraction);  //コールバック 0回目の屈折終了からスタートする
    } else {
        _is_leader = false;
        _begining_x = pChip_front->_begining_x;
        _begining_y = pChip_front->_begining_y;
        _begining_z = pChip_front->_begining_z;
        _begining_rx = pChip_front->_begining_rx;
        _begining_ry = pChip_front->_begining_ry;
        _begining_rz = pChip_front->_begining_rz;
        if (_is_fix_begin_pos) {
            _x = _begining_x;
            _y = _begining_y;
            _z = _begining_z;
            _rx = _begining_rx;
            _ry = _begining_ry;
            _rz = _begining_rz;
        }
        _cnt_refraction = 0;
        _frame_refraction_enter = INT_MAX;
        _frame_refraction_out = INT_MAX;
    }

    _is_refracting = false;
    _prev_is_refracting = false;
}

void RefractionLaserChip::onInactive() {
    //レーザーチップ消失時処理

    //一つ後方のチップがあれば、自分の意思（移動など）を引き継がせる
    //これは、レーザーがちぎれた場合、以下のパラメーターのみ引き継がせ、移動を継続させるため。
    //加速度や、移動予約など引き継がれないものが多数あるので、複雑な移動をする際は、ココに注意を払うこと！
    //レーザーがゲーム領域外にたっしたときも、先頭チップから順に連続で引継ぎが発生することになる。
    //ちょっと無駄っぽいけど、さもなくば先頭の次のチップが領域外に向かって移動するとは限らないので、やはり必要。
    if (_pChip_behind) {
        RefractionLaserChip* const pChip_behind = (RefractionLaserChip*)_pChip_behind;
        GgafDxKuroko* const pChip_behind_pKuroko = pChip_behind->getKuroko();
        GgafDxKuroko* pKuroko = getKuroko();
        pChip_behind_pKuroko->_vX = pKuroko->_vX;
        pChip_behind_pKuroko->_vY = pKuroko->_vY;
        pChip_behind_pKuroko->_vZ = pKuroko->_vZ;
        pChip_behind_pKuroko->_ang_rz_mv = pKuroko->_ang_rz_mv;
        pChip_behind_pKuroko->_ang_ry_mv = pKuroko->_ang_ry_mv;
        pChip_behind_pKuroko->_velo_mv  = pKuroko->_velo_mv;
        pChip_behind->_rx = _rx;
        pChip_behind->_ry = _ry;
        pChip_behind->_rz = _rz;
        pChip_behind->_cnt_refraction = _cnt_refraction;
        pChip_behind->_frame_refraction_enter = _frame_refraction_enter;
        pChip_behind->_frame_refraction_out = _frame_refraction_out;
        pChip_behind->_is_refracting = _is_refracting;
        //屈折エフェクトを解除
        if (_pRefractionEffect) {
            _pRefractionEffect->sayonara();
            _pRefractionEffect = nullptr;
        }
        if (_prev_pRefractionEffect) {
            _prev_pRefractionEffect->sayonara();
            _prev_pRefractionEffect = nullptr;
        }
        pChip_behind->_pRefractionEffect = _pRefractionEffect;
    } else {
        //屈折エフェクトを解除
        if (_pRefractionEffect) {
            _pRefractionEffect->sayonara();
            _pRefractionEffect = nullptr;
        }
        if (_prev_pRefractionEffect) {
            _prev_pRefractionEffect->sayonara();
            _prev_pRefractionEffect = nullptr;
        }
    }
    LaserChip::onInactive(); //つながりを切断処理
}

void RefractionLaserChip::processBehavior() {
    //レーザーチップ消失時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの processBehavior() メソッドも呼び出してください。
    //座標に反映
    GgafDxKuroko* pKuroko = getKuroko();
    RefractionLaserChip* pChip_front =  (RefractionLaserChip*)_pChip_front;
    if (getActiveFrame() > 1) {
        //GgafActorDepository::dispatch() は
        //取得できる場合、ポインタを返すと共に、そのアクターはアクター発送者のサブの一番後ろに移動される。
        //したがって、レーザーの先頭から順番にprocessBehavior() が呼ばれるため、以下のようにすると
        //数珠繋ぎになる。
        if (pChip_front == nullptr) {
            //本当の先頭チップか、或いはにわか先頭チップの場合の共通処理
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_is_refracting = _is_refracting;
            _prev_pRefractionEffect = _pRefractionEffect;

            _pRefractionEffect = nullptr;
            if (!_is_refracting) {
                if (getBehaveingFrame() >= _frame_refraction_enter) {
                    if (_cnt_refraction < _num_refraction) {
                        _cnt_refraction++;
                        onRefractionBegin(_cnt_refraction); //コールバック
                        _frame_refraction_out = getBehaveingFrame()  + _frame_standstill_refraction;
                        _is_refracting = true;

                        if (_pDispatche_RefractionEffect) {
                            _pRefractionEffect = (GgafDxDrawableActor*)_pDispatche_RefractionEffect->dispatch();
                            if (_pRefractionEffect) {
                                _pRefractionEffect->positionAs(this);
                                //最長時間の解除予約。
                                //何かの拍子？（TODO:要調査）でレーザーチップが消滅した場合、正しくsayonara()出来ない場合がある。その場合の保険。
                                _pRefractionEffect->inactivateDelay(_pDepo->_num_chip_max +_frame_standstill_refraction);
                            }
                        }
                    }
                }
            }

            if (_is_refracting) {
                if (getBehaveingFrame() >= _frame_refraction_out) {
                    onRefractionFinish(_cnt_refraction); //コールバック
                    _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction;
                    //座標を変えず方向だけ転換
                    coord x = _x; coord y = _y; coord z = _z;
                    pKuroko->behave(); //
                    _x = x; _y = y; _z = z;
                    _is_refracting = false;

                    return;
                }
            }

            if (!_is_refracting) {
                //_is_refracting中は停止しなくてはいけないためgetKuroko()->behave()を実行しない。
                //pKuroko->behave();以外で座標を操作している場合は、完全な停止にならないので注意
                pKuroko->behave();
            }

        } else {
            //先頭以外のチップ数珠繋ぎ処理
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_is_refracting = _is_refracting;
            _prev_pRefractionEffect = _pRefractionEffect;
            _x  = pChip_front->_prev_x;
            _y  = pChip_front->_prev_y;
            _z  = pChip_front->_prev_z;
            _rx = pChip_front->_prev_rx;
            _ry = pChip_front->_prev_ry;
            _rz = pChip_front->_prev_rz;
            _is_refracting =  pChip_front->_prev_is_refracting;
            _pRefractionEffect = pChip_front->_prev_pRefractionEffect;
            if (_pChip_behind == nullptr) {
                if (_pRefractionEffect) {
                    //_TRACE_("_pRefractionEffect->sayonara();");
                    _pRefractionEffect->sayonara(_frame_standstill_refraction);
                }
            }
        }
    }
}

void RefractionLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

RefractionLaserChip::~RefractionLaserChip() {
}

