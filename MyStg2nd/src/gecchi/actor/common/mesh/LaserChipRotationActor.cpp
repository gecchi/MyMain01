#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

LaserChipRotationActor::LaserChipRotationActor(const char* prm_name) : RotationActor(prm_name) {
    _class_name = "LaserChipRotationActor";
    _num_continual_obtain_count = 0;
    _num_chip_active = 0;
    _is_tear_laser = false;
    _num_chip_max = 0;
    _num_chip_interval = 3;
    _pChip_prev_obtain = NULL;
    _lifeframe_prev_obtain = 0;
    _pSeConnection = NULL;
    _num_interval_frame_count = 0;
}

void LaserChipRotationActor::processBehavior() {
}


LaserChip* LaserChipRotationActor::obtain() {
if (_num_continual_obtain_count > _num_chip_max) { //_num_chip_max連続発射時、5フレーム弾切れにする。
        _is_tear_laser = true;
        _pChip_prev_obtain = NULL;
        _lifeframe_prev_obtain = 0;
        _num_continual_obtain_count = 0;
        _num_interval_frame_count = 0;
        return NULL;
    } else if (_num_interval_frame_count < _num_chip_interval) { //_num_chip_intervalフレーム以内なので弾切れにする。
        _num_interval_frame_count++;
        return NULL;
    } else if (_is_tear_laser && _num_chip_max - _num_chip_active < _num_chip_max/4) { //弾切れの時 _num_chip_max/4 溜まってから発射
        _is_tear_laser = true;
        _pChip_prev_obtain = NULL;
        _lifeframe_prev_obtain = 0;
        _num_continual_obtain_count = 0;
        _num_interval_frame_count++;
        return NULL;
    } else {
        LaserChip* pChip = (LaserChip*)RotationActor::obtain();
        if (pChip != NULL) {

            if (_pChip_prev_obtain != NULL) {
                if (_lifeframe_prev_obtain == _pChip_prev_obtain->_lifeframe) { //アクティブになってフレームが加算されるのは１フレーム次であるため
                    //2フレーム連続でobtainの場合連結とみなす
                    _num_continual_obtain_count++;
                    pChip->_pChip_front = _pChip_prev_obtain;
                    _pChip_prev_obtain->_pChip_behind = pChip;
                    _is_tear_laser = false;
                } else {
                    //2フレーム連続でobtain出来てない場合連結は切れてる
                    _num_continual_obtain_count = 0;
                    pChip->_pChip_front = NULL;
                    _pChip_prev_obtain->_pChip_behind = NULL;
                }
            } else {
                pChip->_pChip_front = NULL;
            }
            _pChip_prev_obtain = pChip;
            _lifeframe_prev_obtain = pChip->_lifeframe;

            return pChip;

        } else {
            _num_continual_obtain_count = 0;
            _is_tear_laser = true;
            _pChip_prev_obtain = NULL;
            _lifeframe_prev_obtain = 0;
            _num_interval_frame_count++;
            return NULL;
        }
    }

}

void LaserChipRotationActor::addLaserChip(LaserChip* prm_pLaserChip) {
    _num_chip_max ++;
    prm_pLaserChip->_pRotation = this;
    addSubLast(prm_pLaserChip);
}

LaserChipRotationActor::~LaserChipRotationActor() {
}
