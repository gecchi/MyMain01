#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

LaserChipDispatcher::LaserChipDispatcher(const char* prm_name) : ActorDispatcher(prm_name) {
    _class_name = "LaserChipDispatcher";
    _num_continual_employ_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = false;
    _num_chip_max = 0;
    _num_chip_interval = 20;
    _pChip_prev_employ = NULL;
    _lifeframe_prev_employ = 0;
    _pSeConnection = NULL;
    _num_interval_frame_count = 0;
}

void LaserChipDispatcher::processBehavior() {
}

LaserChip* LaserChipDispatcher::employ() {
    if (_num_continual_employ_count > _num_chip_max) { //_num_chip_max連続発射時、5フレーム弾切れにする。
        _is_tear_laser = true;
        _pChip_prev_employ = NULL;
        _lifeframe_prev_employ = 0;
        _num_continual_employ_count = 0;
        _num_interval_frame_count = 0;
        return NULL;
    } else if (_num_interval_frame_count < _num_chip_interval) { //_num_chip_intervalフレーム以内なので弾切れにする。
        _num_interval_frame_count++;
        return NULL;
    } else if (_is_tear_laser && _num_chip_max - _num_chip_active < _num_chip_max/4) { //弾切れの時 _num_chip_max/4 溜まってから発射
        _is_tear_laser = true;
        _pChip_prev_employ = NULL;
        _lifeframe_prev_employ = 0;
        _num_continual_employ_count = 0;
        _num_interval_frame_count++;
        return NULL;
    } else {
        LaserChip* pChip = (LaserChip*)ActorDispatcher::employ();
        if (pChip != NULL) {
            pChip->activate();
            if (_pChip_prev_employ != NULL) {
                if (_lifeframe_prev_employ == _pChip_prev_employ->_lifeframe) { //アクティブになってフレームが加算されるのは１フレーム次であるため
                    //2フレーム連続でemployの場合連結とみなす
                    _num_continual_employ_count++;
                    pChip->_pChip_front = _pChip_prev_employ;
                    _pChip_prev_employ->_pChip_behind = pChip;
                    _is_tear_laser = false;
                } else {
                    //2フレーム連続でemploy出来てない場合連結は切れてる
                    _num_continual_employ_count = 0;
                    pChip->_pChip_front = NULL;
                    _pChip_prev_employ->_pChip_behind = NULL;
                }
            } else {
                pChip->_pChip_front = NULL;
            }
            _pChip_prev_employ = pChip;
            _lifeframe_prev_employ = pChip->_lifeframe;

            return pChip;

        } else {
            _num_continual_employ_count = 0;
            _is_tear_laser = true;
            _pChip_prev_employ = NULL;
            _lifeframe_prev_employ = 0;
            _num_interval_frame_count++;
            return NULL;
        }
    }

}

void LaserChipDispatcher::addLaserChip(LaserChip* prm_pLaserChip) {
    _num_chip_max ++;
    prm_pLaserChip->_pDispatcher = this;
    addSubLast(prm_pLaserChip);
}

LaserChipDispatcher::~LaserChipDispatcher() {
}
