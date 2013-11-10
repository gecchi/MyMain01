#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LaserChipDepository::LaserChipDepository(const char* prm_name, GgafStatus* prm_pStat) :
        GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "LaserChipDepository";
    _num_continual_dispatch_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = true;
    _num_chip_max = 0;
    _num_chip_interval = 1;
    _num_chip_dispatch_able = 0;
    _pChip_prev_dispatch = nullptr;
    _frame_of_behaving_prev_dispatch = 0;

    _num_interval_frame_count = _num_chip_interval; //生成直後はインターバルなど無し
    _num_continual_dispatch_max = _num_chip_max;
    _pEffectActor_Irradiate = nullptr;
}

void LaserChipDepository::config(int prm_num_continual_dispatch_max,
                                 uint32_t prm_num_chip_interval,
                                 GgafDxCore::GgafDxDrawableActor* prm_pEffectActor_Irradiate) {
    _num_continual_dispatch_max = prm_num_continual_dispatch_max;
    _num_chip_interval = prm_num_chip_interval;
    _pEffectActor_Irradiate = prm_pEffectActor_Irradiate;
    if (_pEffectActor_Irradiate) {
        _pEffectActor_Irradiate->inactivate();
    }
}

LaserChip* LaserChipDepository::dispatch(int prm_offset_frames) {
    if (_num_continual_dispatch_count > _num_continual_dispatch_max) { //_num_continual_dispatch_max連続発射時、弾切れにする(_num_interval_frame_countをリセット)。
        _is_tear_laser = true;
        _pChip_prev_dispatch = nullptr;
        _frame_of_behaving_prev_dispatch = 0;
        _num_continual_dispatch_count = 0;
        _num_interval_frame_count = 1; //ココに処理が来たことにより既に１フレーム弾切れなので１を設定
        return nullptr;
    } else if (_num_interval_frame_count < _num_chip_interval) { //_num_chip_intervalフレーム以内なので弾切れにする。
        _is_tear_laser = true;
        _num_interval_frame_count++;
        return nullptr;
    } else if (_is_tear_laser && _num_chip_max - _num_chip_active < _num_chip_dispatch_able) {
        _is_tear_laser = true;
        _pChip_prev_dispatch = nullptr;
        _frame_of_behaving_prev_dispatch = 0;
        _num_continual_dispatch_count = 0;
        _num_interval_frame_count++;
        return nullptr;
    } else {
        LaserChip* pChip = (LaserChip*)GgafActorDepository::dispatch(prm_offset_frames);
        if (pChip) {
            if (_pChip_prev_dispatch) {
                //以前のdispatch()したチップ
                if (_frame_of_behaving_prev_dispatch+1 == _pChip_prev_dispatch->getBehaveingFrame()) {
                    //2フレーム連続でdispatchの場合連結とみなす
                    _num_continual_dispatch_count++;
                    pChip->_pChip_front = _pChip_prev_dispatch;
                    _pChip_prev_dispatch->_pChip_behind = pChip;
                    pChip->_pChip_behind = nullptr;
                    _is_tear_laser = false;
                } else {
                    //2フレーム連続でdispatch出来てない場合連結は切れてる
                    _num_continual_dispatch_count = 0;
                    pChip->_pChip_front = nullptr;
                    pChip->_pChip_behind = nullptr;
                    _is_tear_laser = true;
                }
            } else {
                //dispatch()初回
                pChip->_pChip_front = nullptr;
                pChip->_pChip_behind = nullptr;
                _is_tear_laser = false;
            }
            _pChip_prev_dispatch = pChip;
            _frame_of_behaving_prev_dispatch = pChip->getBehaveingFrame();
            //8回に一回は地形ヒットありのチップとする
            if (_num_continual_dispatch_count % 8U == 0) {
                pChip->_can_chikei_hit = true;
            } else {
                pChip->_can_chikei_hit = false;
            }
            return pChip;

        } else {
            //dispatch()タイミングであったがdispatch()出来なかった場合
            _num_continual_dispatch_count = 0;
            _is_tear_laser = true;
            _pChip_prev_dispatch = nullptr;
            _frame_of_behaving_prev_dispatch = 0;
            _num_interval_frame_count++;
            return nullptr;
        }
    }
}

void LaserChipDepository::processFinal() {
    //発射中エフェクト表示切り替え
    if (_pEffectActor_Irradiate) {
        if (_pChip_prev_dispatch && _frame_of_behaving_prev_dispatch == _pChip_prev_dispatch->getBehaveingFrame()) {
            if (_pEffectActor_Irradiate->_is_active_flg == false) {
                _pEffectActor_Irradiate->activate();
            }
        } else {
            if (_pEffectActor_Irradiate->_is_active_flg) {
                _pEffectActor_Irradiate->inactivate();
            }
        }
    }
}

void LaserChipDepository::put(LaserChip* prm_pLaserChip) {
    _num_chip_max ++;
    _num_continual_dispatch_max++;
    _num_chip_dispatch_able = _num_chip_max/4; //弾切れの時 _num_chip_max/4 溜まってから発射
    prm_pLaserChip->_pDepo = this;
    GgafActorDepository::put(prm_pLaserChip);
}

void LaserChipDepository::onReset() {
    _is_tear_laser = true;
    _num_continual_dispatch_count = 0;
    _num_chip_active = 0;
    _frame_of_behaving_prev_dispatch = 0;
    GgafActorDepository::onReset();
}

LaserChipDepository::~LaserChipDepository() {
    _TRACE_("LaserChipDepository::~LaserChipDepository()");
}
