#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"
#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _pSourceActor = nullptr;
    _tmp_source_x = _x;
    _tmp_source_y = _y;
    _tmp_source_z = _y;
    _tmp_source_rx = _rx;
    _tmp_source_ry = _ry;
    _tmp_source_rz = _rz;
    _pSource_x = &_x;
    _pSource_y = &_y;
    _pSource_z = &_z;
    _pSource_rx = &_rx;
    _pSource_ry = &_ry;
    _pSource_rz = &_rz;
    _velo_mv = 100000;
}

void StraightLaserChip::processSettlementBehavior() {
    //�e�A�N�^�[�̍��W�ړ�������������Ɏ��s������
    if (_pSourceActor) {
        //���ˌ��A�N�^�[����������ꍇ
        if (_pSourceActor->wasDeclaredEnd()) {
            _pSourceActor = nullptr;
            //�o�b�N�A�b�v
            _tmp_source_x = (*_pSource_x);
            _tmp_source_y = (*_pSource_y);
            _tmp_source_z = (*_pSource_z);
            _tmp_source_rx = (*_pSource_rx);
            _tmp_source_ry = (*_pSource_ry);
            _tmp_source_rz = (*_pSource_rz);
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
        velo v = _velo_mv * ((velo)getActiveFrame()-1);
        _x = (*_pSource_x) + (vx * v );
        _y = (*_pSource_y) + (vy * v );
        _z = (*_pSource_z) + (vz * v );
    } else {
        //���ˌ��A�N�^�[���񊈓����̏ꍇ
        _rx = _tmp_source_x;
        _ry = _tmp_source_y;
        _rz = _tmp_source_z;
        float vx, vy, vz;
        UTIL::convRzRyToVector(_tmp_source_rz, _tmp_source_ry,
                                vx, vy, vz);
        velo v = _velo_mv * ((velo)getActiveFrame()-1);
        _x = _tmp_source_x + (vx * v );
        _y = _tmp_source_y + (vy * v );
        _z = _tmp_source_z + (vz * v );
    }

    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

void StraightLaserChip::setMvVelo(coord prm_velo) {
    _velo_mv = prm_velo;
}

StraightLaserChip::~StraightLaserChip() {

}

