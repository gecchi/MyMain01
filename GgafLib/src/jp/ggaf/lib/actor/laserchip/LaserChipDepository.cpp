#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"



using namespace GgafLib;

LaserChipDepository::LaserChipDepository(const char* prm_name) :
        GgafCore::ActorDepository(prm_name) {
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
    _pEffectActor = nullptr;
}

void LaserChipDepository::config(int prm_num_continual_dispatch_max,
                                 uint32_t prm_num_chip_interval,
                                 GgafDx::FigureActor* prm_pEffectActor) {
    _num_continual_dispatch_max = prm_num_continual_dispatch_max;
    _num_chip_interval = prm_num_chip_interval;
    _pEffectActor = prm_pEffectActor;
    if (_pEffectActor) {
        _pEffectActor->inactivate();
    }
}

std::vector<LaserChip*> LaserChipDepository::dispatchN(int prm_number_of_chip, int prm_offset_frames) {
    std::vector<LaserChip*> ret;
    for (int i = 0; i < prm_number_of_chip; i++) {
        LaserChip* pLaserChip = dispatch(prm_offset_frames);
        if (pLaserChip) {
            pLaserChip->_n_dispatch_at_once = prm_number_of_chip;
            pLaserChip->_dispatch_index = i;
            ret.push_back(pLaserChip);
        } else {
            ret.push_back(nullptr);
        }
    }
    return ret;
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
        LaserChip* const pChip = (LaserChip*)GgafCore::ActorDepository::dispatch(prm_offset_frames);
        if (pChip) {
            if (_pChip_prev_dispatch) {
                //以前のdispatch()したチップ
                if ( ( _frame_of_behaving_prev_dispatch+1 == _pChip_prev_dispatch->getBehaveingFrame()  &&  _pChip_prev_dispatch->isActive() ) ||
                       _frame_of_behaving_prev_dispatch   == _pChip_prev_dispatch->getBehaveingFrame()
                ) {
                    //同フレームでdispatch() 或いは１フレーム差で連続でdispatch() の場合連結とみなす
                    _num_continual_dispatch_count++;
                    pChip->_pChip_infront = _pChip_prev_dispatch;
                    _pChip_prev_dispatch->_pChip_behind = pChip;
                    pChip->_pChip_behind = nullptr;
                    _is_tear_laser = false;
                } else {
                    //連結は切れてる
                    _num_continual_dispatch_count = 0;
                    pChip->_pChip_infront = nullptr;
                    pChip->_pChip_behind = nullptr;
                    _is_tear_laser = true;
                }
            } else {
                //dispatch()初回
                pChip->_pChip_infront = nullptr;
                pChip->_pChip_behind = nullptr;
                _is_tear_laser = false;
            }
            _pChip_prev_dispatch = pChip;
            _frame_of_behaving_prev_dispatch = pChip->getBehaveingFrame();
            pChip->_n_dispatch_at_once = 1;
            pChip->_dispatch_index = 0;
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
    if (_pEffectActor) {
        if (_pChip_prev_dispatch && _frame_of_behaving_prev_dispatch == _pChip_prev_dispatch->getBehaveingFrame()) {
            if (_pEffectActor->_is_active_flg == false) {
                _pEffectActor->activate();
            }
        } else {
            if (_pEffectActor->_is_active_flg) {
                _pEffectActor->inactivate();
            }
        }
    }
}
void LaserChipDepository::put(GgafCore::Actor* prm_pChild) {
#ifdef MY_DEBUG
    if (!prm_pChild->instanceOf(Obj_LaserChip)) {
        throwCriticalException("LaserChipDepository::put() 引数には LaserChip を渡してください。prm_pChild="<<prm_pChild->getName()<<"("<<prm_pChild<<")");
    }
#endif
    LaserChip* pLaserChip = (LaserChip*)prm_pChild;
    _num_chip_max ++;
    _num_continual_dispatch_max++;
    _num_chip_dispatch_able = _num_chip_max/4; //弾切れの時 _num_chip_max/4 溜まってから発射
    pLaserChip->_pDepo = this;
    GgafCore::ActorDepository::put(pLaserChip);
}

void LaserChipDepository::onReset() {
    _is_tear_laser = true;
    _num_continual_dispatch_count = 0;
    _num_chip_active = 0;
    _frame_of_behaving_prev_dispatch = 0;
    GgafCore::ActorDepository::onReset();
}

LaserChipDepository::~LaserChipDepository() {
    _TRACE_("LaserChipDepository::~LaserChipDepository()");
}
