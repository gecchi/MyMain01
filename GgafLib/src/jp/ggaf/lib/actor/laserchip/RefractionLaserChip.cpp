#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"



using namespace GgafLib;

RefractionLaserChip::RefractionLaserChip(const char* prm_name, const char* prm_model) :
        LaserChip(prm_name, prm_model) {
    _class_name = "RefractionLaserChip";
    _is_leader = false;
    _num_refraction = 1;
    _frame_standstill_refraction = 10;
    _frame_between_refraction = 20;

    _cnt_refraction = 0;
    _frame_refraction_enter = 0;
    _frame_refraction_out = 0;
    _is_refracting = false;

    _pDepo_refraction_effect = nullptr;
    _pRefractionEffect = nullptr;
    _prev_pRefractionEffect = nullptr;

    _begining_x = _x;
    _begining_y = _y;
    _begining_z = _z;
    _begining_rx = _rx;
    _begining_ry = _ry;
    _begining_rz = _rz;
    _begining_rz_mv = getLocusVehicle()->_rz_mv;
    _begining_ry_mv = getLocusVehicle()->_ry_mv;
    _begining_velo_mv   = getLocusVehicle()->_velo_mv;
    _prev_x  = _x;
    _prev_y  = _y;
    _prev_z  = _z;
    _prev_rx = _rx;
    _prev_ry = _ry;
    _prev_rz = _rz;
    _prev_rz_mv = getLocusVehicle()->_rz_mv;
    _prev_ry_mv = getLocusVehicle()->_ry_mv;
    _prev_velo_mv   = getLocusVehicle()->_velo_mv;
    _prev_is_refracting = false;
    _is_fix_begin_pos = true;
    _refraction_end_frames = 0;
}

void RefractionLaserChip::config(int prm_num_refraction,
                                 frame prm_frame_between_refraction,
                                 frame prm_frame_standstill_refraction,
                                 bool prm_is_fix_begin_pos,
                                 GgafCore::ActorDepository* prm_pDepo_refraction_effect) {
#ifdef MY_DEBUG
    if (prm_frame_between_refraction == 0) {
        throwCriticalException("直進間隔フレーム数が0は設定不可です。name="<<getName());
    }
    if (prm_frame_standstill_refraction == 0) {
        throwCriticalException("屈折溜フレーム数が0は設定不可です。name="<<getName());
    }
#endif
    _num_refraction = prm_num_refraction;
    _frame_between_refraction = prm_frame_between_refraction;
    _frame_standstill_refraction = prm_frame_standstill_refraction;
    _is_fix_begin_pos = prm_is_fix_begin_pos;
    _pDepo_refraction_effect = prm_pDepo_refraction_effect;
    _refraction_end_frames = (_num_refraction * _frame_standstill_refraction) +
                             ((_num_refraction+1) * prm_frame_between_refraction);
}

void RefractionLaserChip::onActive() {
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    RefractionLaserChip* pChip_infront =  (RefractionLaserChip*)_pChip_infront;
    //レーザーチップ出現時処理
    if (pChip_infront == nullptr) {
        _is_leader = true;
        //自身が先頭の場合
        _begining_x = _x;
        _begining_y = _y;
        _begining_z = _z;
        _begining_rx = _rx;
        _begining_ry = _ry;
        _begining_rz = _rz;
        _begining_rz_mv = pLocusVehicle->_rz_mv;
        _begining_ry_mv = pLocusVehicle->_ry_mv;
        _begining_velo_mv   = pLocusVehicle->_velo_mv;
        _cnt_refraction = 0;
        _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction + 1;
        _frame_refraction_out = _frame_refraction_enter + _frame_standstill_refraction;
        //onRefractionInto(_cnt_refraction);
        onRefractionOutOf(_cnt_refraction);  //コールバック 0回目の屈折終了からスタートする
    } else {
        _is_leader = false;
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
            pLocusVehicle->setRzRyMvAng(_begining_rz_mv, _begining_ry_mv);
            pLocusVehicle->setMvVelo(_begining_velo_mv);
        }
        _cnt_refraction = 0;
        _frame_refraction_enter = INT_MAX;
        _frame_refraction_out = INT_MAX;
        _refraction_end_frames = pChip_infront->_refraction_end_frames;
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
    //【注意】
    //もし先頭チップ停止中（移動速度0）に inactive となった場合、停止が引き継がれるため、
    //RefractionLaser はそこに溜まり込んでしまう。これは回避すること。
    if (_pChip_behind) {
        RefractionLaserChip* const pChip_behind = (RefractionLaserChip*)_pChip_behind;
        GgafDx::LocusVehicle* const pChip_behind_pLocusVehicle = pChip_behind->getLocusVehicle();
        GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
        pChip_behind->_rx = _rx;
        pChip_behind->_ry = _ry;
        pChip_behind->_rz = _rz;
        pChip_behind_pLocusVehicle->setRzRyMvAng(pLocusVehicle->_rz_mv, pLocusVehicle->_ry_mv);
        pChip_behind_pLocusVehicle->setMvVelo(pLocusVehicle->_velo_mv);
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
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    RefractionLaserChip* pChip_infront =  (RefractionLaserChip*)_pChip_infront;
    if (getActiveFrame() > 1) { //１フレーム目は、設定座標で表示させるため。移動させない
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
            _prev_rz_mv = pLocusVehicle->_rz_mv;
            _prev_ry_mv = pLocusVehicle->_ry_mv;
            _prev_velo_mv   = pLocusVehicle->_velo_mv;
            _prev_is_refracting = _is_refracting;
            _prev_pRefractionEffect = _pRefractionEffect;

            _pRefractionEffect = nullptr;
            if (!_is_refracting) {
                if (getBehaveingFrame() >= _frame_refraction_enter) {
                    if (_cnt_refraction < _num_refraction) {
                        _cnt_refraction++;
                        onRefractionInto(_cnt_refraction); //コールバック
                        _frame_refraction_out = getBehaveingFrame()  + _frame_standstill_refraction - 1; //0で最速。但し方向転換で１フレムかかる
                        _is_refracting = true;

                        if (_pDepo_refraction_effect) {
                            _pRefractionEffect = (GgafDx::FigureActor*)_pDepo_refraction_effect->dispatch();
                            if (_pRefractionEffect) {
                                _pRefractionEffect->setPositionAt(this);
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
                    onRefractionOutOf(_cnt_refraction); //コールバック
                    _frame_refraction_enter = getBehaveingFrame() + _frame_between_refraction + 1;
                    //↑_frame_refraction_enterの判定は、次フレームである。
                    //getBehaveingFrame() は次フレームで+1されるので+1しておく必要がある
                    //座標を変えず方向だけ転換
                    coord x = _x; coord y = _y; coord z = _z;
                    pLocusVehicle->behave(); //
                    _x = x; _y = y; _z = z;
                    _is_refracting = false;
                    return;
                }
            }

            if (!_is_refracting) {
                //_is_refracting中は停止しなくてはいけないためgetLocusVehicle()->behave()を実行しない。
                //pLocusVehicle->behave();以外で座標を操作している場合は、完全な停止にならないので注意
                pLocusVehicle->behave();
            }

        } else {
            //先頭以外のチップ数珠繋ぎ処理
            _prev_x  = _x;
            _prev_y  = _y;
            _prev_z  = _z;
            _prev_rx = _rx;
            _prev_ry = _ry;
            _prev_rz = _rz;
            _prev_rz_mv = pLocusVehicle->_rz_mv;
            _prev_ry_mv = pLocusVehicle->_ry_mv;
            _prev_velo_mv   = pLocusVehicle->_velo_mv;
            _prev_is_refracting = _is_refracting;
            _prev_pRefractionEffect = _pRefractionEffect;
            _x  = pChip_infront->_prev_x;
            _y  = pChip_infront->_prev_y;
            _z  = pChip_infront->_prev_z;
            _rx = pChip_infront->_prev_rx;
            _ry = pChip_infront->_prev_ry;
            _rz = pChip_infront->_prev_rz;
            pLocusVehicle->setRzRyMvAng(pChip_infront->_prev_rz_mv, pChip_infront->_prev_ry_mv);
            pLocusVehicle->setMvVelo(pChip_infront->_prev_velo_mv);
            _is_refracting =  pChip_infront->_prev_is_refracting;
            _pRefractionEffect = pChip_infront->_prev_pRefractionEffect;
            if (_pChip_behind == nullptr) {
                if (_pRefractionEffect) {
                    _pRefractionEffect->sayonara(_frame_standstill_refraction);
                }
            }
        }
    }
}

RefractionLaserChip::~RefractionLaserChip() {
}

