#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"
#include "jp/ggaf/lib/util/StgUtil.h"



using namespace GgafLib;

StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model) :
            LaserChip(prm_name, prm_model) {
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
    _view_bound = C_DX(_velo_mv) * 3;
}

void StraightLaserChip::processBehavior() {
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
        double vx, vy, vz;
        UTIL::convRzRyToVector(_rz, _ry,
                                vx, vy, vz);
        velo v = _velo_mv * ((velo)getActiveFrame()-1);
        _x = (*_pSource_x) + (vx * v );
        _y = (*_pSource_y) + (vy * v );
        _z = (*_pSource_z) + (vz * v );
    } else {
        //���ˌ��A�N�^�[���񊈓����̏ꍇ
        _rx = _tmp_source_rx;
        _ry = _tmp_source_ry;
        _rz = _tmp_source_rz;
        double vx, vy, vz;
        UTIL::convRzRyToVector(_tmp_source_rz, _tmp_source_ry,
                                vx, vy, vz);
        velo v = _velo_mv * ((velo)getActiveFrame()-1);
        _x = _tmp_source_x + (vx * v );
        _y = _tmp_source_y + (vy * v );
        _z = _tmp_source_z + (vz * v );
    }

}

int StraightLaserChip::isOutOfView() {
    if (_offscreen_kind == -1) {
        const dxcoord bound = _view_bound;
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_infront < bound) {
                            if (_dest_from_vppln_back < bound) {
                                //Viewport�͈͓�
                                _offscreen_kind = 0;
                            } else {
                                //�����ʂ�艜�Ŕ͈͊O
                                _offscreen_kind = 6;
                            }
                        } else {
                            //��O���ʂ���O�Ŕ͈͊O
                            _offscreen_kind = 5;
                        }
                    } else {
                        //�E���ʂ��E�Ŕ͈͊O
                        _offscreen_kind = 4;
                    }
                } else {
                    //�����ʂ�荶�Ŕ͈͊O
                    _offscreen_kind = 3;
                }
            } else {
                //�����ʂ�艺�Ŕ͈͊O
                _offscreen_kind = 2;
            }
        } else {
            //�㕽�ʂ���Ŕ͈͊O
            _offscreen_kind = 1;
        }
    }
    return _offscreen_kind;
}

void StraightLaserChip::setMvVelo(coord prm_velo) {
    _velo_mv = prm_velo;
    _view_bound = C_DX(_velo_mv) * 3;
}

StraightLaserChip::~StraightLaserChip() {

}

