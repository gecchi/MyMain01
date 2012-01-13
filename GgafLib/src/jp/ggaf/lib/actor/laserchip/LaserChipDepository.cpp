#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LaserChipDepository::LaserChipDepository(const char* prm_name, GgafStatus* prm_pStat) : GgafActorDepository(prm_name, prm_pStat) {
    _class_name = "LaserChipDepository";
    _num_continual_employ_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = true;
    _num_chip_max = 0;
    _num_chip_interval = 1;
    _pChip_prev_employ = NULL;
    _frame_of_behaving_prev_employ = 0;

    _num_interval_frame_count = _num_chip_interval; //生成直後はインターバルなど無し
    _num_continual_employ_max = _num_chip_max;
    _pEffectActor_Irradiate = NULL;
}

void LaserChipDepository::config(int prm_num_continual_employ_max,
                                 UINT32 prm_num_chip_interval,
                                 GgafDxCore::GgafDxDrawableActor* prm_pEffectActor_Irradiate) {
    _num_continual_employ_max = prm_num_continual_employ_max;
    _num_chip_interval = prm_num_chip_interval;
    _pEffectActor_Irradiate = prm_pEffectActor_Irradiate;
    if (_pEffectActor_Irradiate) {
        _pEffectActor_Irradiate->inactivateImmed();
    }
}


LaserChip* LaserChipDepository::dispatch(frame prm_offset_frames) {
    if (_num_continual_employ_count > _num_continual_employ_max) { //_num_continual_employ_max連続発射時、弾切れにする(_num_interval_frame_countをリセット)。
        _is_tear_laser = true;
        _pChip_prev_employ = NULL;
        _frame_of_behaving_prev_employ = 0;
        _num_continual_employ_count = 0;
        _num_interval_frame_count = 0;
        return NULL;
    } else if (_num_interval_frame_count < _num_chip_interval) { //_num_chip_intervalフレーム以内なので弾切れにする。
        _is_tear_laser = true;
        _num_interval_frame_count++;
        return NULL;
    } else if (_is_tear_laser && _num_chip_max - _num_chip_active < _num_chip_max/4) { //弾切れの時 _num_chip_max/4 溜まってから発射
        _is_tear_laser = true;
        _pChip_prev_employ = NULL;
        _frame_of_behaving_prev_employ = 0;
        _num_continual_employ_count = 0;
        _num_interval_frame_count++;
        return NULL;
    } else {
        LaserChip* pChip = (LaserChip*)GgafActorDepository::dispatch(prm_offset_frames);
        if (pChip) {
            if (_pChip_prev_employ) {
                //以前のdispatch()したチップ
                if (_frame_of_behaving_prev_employ+1 == _pChip_prev_employ->getBehaveingFrame()) {
                    //2フレーム連続でemployの場合連結とみなす
                    _num_continual_employ_count++;
                    pChip->_pChip_front = _pChip_prev_employ;
                    _pChip_prev_employ->_pChip_behind = pChip;
                    pChip->_pChip_behind = NULL;
                    _is_tear_laser = false;
                } else {
                    //2フレーム連続でemploy出来てない場合連結は切れてる
                    _num_continual_employ_count = 0;
                    pChip->_pChip_front = NULL;
                    pChip->_pChip_behind = NULL;
                    //_pChip_prev_employ->_pChip_behind = NULL;
                    _is_tear_laser = true;
                }
            } else {
                //dispatch()初回
                pChip->_pChip_front = NULL;
                pChip->_pChip_behind = NULL;
                _is_tear_laser = false;
            }
            _pChip_prev_employ = pChip;
            _frame_of_behaving_prev_employ = pChip->getBehaveingFrame();
            //20回に一回は地形ヒットありのチップとする
            if (_num_continual_employ_count % 20 == 0) {
                pChip->_can_chikei_hit = true;
            } else {
                pChip->_can_chikei_hit = false;
            }
            return pChip;

        } else {
            //dispatch()タイミングであったがdispatch()出来なかった場合
            _num_continual_employ_count = 0;
            _is_tear_laser = true;
            _pChip_prev_employ = NULL;
            _frame_of_behaving_prev_employ = 0;
            _num_interval_frame_count++;
            return NULL;
        }
    }
}

void LaserChipDepository::processFinal() {
    //発射中エフェクト表示切り替え
    if (_pEffectActor_Irradiate) {
        if (_pChip_prev_employ && _frame_of_behaving_prev_employ == _pChip_prev_employ->getBehaveingFrame()) {
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

void LaserChipDepository::addSubLast(LaserChip* prm_pLaserChip) {
    _num_chip_max ++;
    _num_continual_employ_max++;
    prm_pLaserChip->_pDepo = this;
    GgafActorDepository::addSubLast(prm_pLaserChip);
}

void LaserChipDepository::onReset() {
    _is_tear_laser = true;
    _num_continual_employ_count = 0;
    _num_chip_active = 0;
    _frame_of_behaving_prev_employ = 0;
    GgafActorDepository::onReset();
}

LaserChipDepository::~LaserChipDepository() {
    _TRACE_("LaserChipDepository::~LaserChipDepository()");
}
