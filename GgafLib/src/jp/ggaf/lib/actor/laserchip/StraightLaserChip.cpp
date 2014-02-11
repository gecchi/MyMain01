#include "stdafx.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _pSourceActor = nullptr;
    source_x = _x;
    source_y = _y;
    source_z = _y;
    source_rx = _rx;
    source_ry = _ry;
    source_rz = _rz;
    _pSource_x = &_x;
    _pSource_y = &_y;
    _pSource_z = &_z;
    _pSource_rx = &_rx;
    _pSource_ry = &_ry;
    _pSource_rz = &_rz;
    _veloMv = 100000;
}

void StraightLaserChip::processSettlementBehavior() {
    //�e�A�N�^�[�̍��W�ړ�������������Ɏ��s������
    if (_pSourceActor) {
        //���ˌ��A�N�^�[����������ꍇ
        if (_pSourceActor->wasDeclaredEnd()) {
            _pSourceActor = nullptr;
            //�o�b�N�A�b�v
            source_x = (*_pSource_x);
            source_y = (*_pSource_y);
            source_z = (*_pSource_z);
            source_rx = (*_pSource_rx);
            source_ry = (*_pSource_ry);
            source_rz = (*_pSource_rz);
            //�s���|�C���^��������邽�ߌ��̃����o�[�Q�Ƃɖ߂��Ă���
            _pSource_x = &_x;
            _pSource_y = &_y;
            _pSource_z = &_z;
            _pSource_rx = &_rx;
            _pSource_ry = &_ry;
            _pSource_rz = &_rz;
        }
    }

    if (_pSourceActor) {
        //���ˌ��A�N�^�[���������̏ꍇ
        _rx = (*_pSource_rx);
        _ry = (*_pSource_ry);
        _rz = (*_pSource_rz);
        float vx, vy, vz;
        UTIL::convRzRyToVector(_rz, _ry,
                                vx, vy, vz);
        velo v = _veloMv * ((velo)getActiveFrame()-1);
        _x = (*_pSource_x) + (vx * v );
        _y = (*_pSource_y) + (vy * v );
        _z = (*_pSource_z) + (vz * v );
    } else {
        //���ˌ��A�N�^�[���񊈓����̏ꍇ
        _rx = source_x;
        _ry = source_y;
        _rz = source_z;
        float vx, vy, vz;
        UTIL::convRzRyToVector(source_rz, source_ry,
                                vx, vy, vz);
        velo v = _veloMv * ((velo)getActiveFrame()-1);
        _x = source_x + (vx * v );
        _y = source_y + (vy * v );
        _z = source_z + (vz * v );
    }

    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

void StraightLaserChip::setMvVelo(coord prm_velo) {
    _veloMv = prm_velo;
}

StraightLaserChip::~StraightLaserChip() {

}

