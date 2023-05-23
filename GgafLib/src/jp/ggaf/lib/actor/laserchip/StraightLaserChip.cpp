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

void StraightLaserChip::processSettlementBehavior() {
    //各アクターの座標移動が完了した後に実行したい
    if (_pSourceActor) {
        //発射元アクターが消失する場合
        if (_pSourceActor->wasDeclaredEnd()) {
            _pSourceActor = nullptr;
            //バックアップ
            _tmp_source_x = (*_pSource_x);
            _tmp_source_y = (*_pSource_y);
            _tmp_source_z = (*_pSource_z);
            _tmp_source_rx = (*_pSource_rx);
            _tmp_source_ry = (*_pSource_ry);
            _tmp_source_rz = (*_pSource_rz);
            //不正ポインタを回避するため元のメンバー参照に戻しておく
            _pSource_x = &_x;
            _pSource_y = &_y;
            _pSource_z = &_z;
            _pSource_rx = &_rx;
            _pSource_ry = &_ry;
            _pSource_rz = &_rz;
        }
    }

    //_n_dispatch_at_once=1
    //    <- velo->
    //  0 ｘ
    //  1 ｘ === ｘ
    //  2 ｘ === ｘ === ｘ
    //  3 ｘ === ｘ === ｘ === ｘ
    //
    //_n_dispatch_at_once=2
    //    <-- velo_mv -->
    //  0 ｘ === ｘ
    //  1 ｘ === ｘ === x === ｘ
    //  2 ｘ === ｘ === x === ｘ === x === ｘ
    //
    //_n_dispatch_at_once=3
    //    <------ velo_mv ------>
    //  0 ｘ === ｘ === ｘ
    //  1 ｘ === ｘ === ｘ === ｘ === ｘ === ｘ
    //  2 ｘ === ｘ === ｘ === ｘ === ｘ === ｘ === ｘ === ｘ === ｘ
    int n_dispatch_at_once = _n_dispatch_at_once;
    int n = n_dispatch_at_once-1 - _dispatch_index; //同時 dispatch 考慮
    //velo v = _velo_mv * ((velo)getActiveFrame()-1) + ((_velo_mv/_n_dispatch_at_once) * n);
    velo v = (_velo_mv * (n_dispatch_at_once*((velo)getActiveFrame()-1) + n)) / n_dispatch_at_once;

    if (_pSourceActor) {
        //発射元アクターが活動中の場合
        _rx = (*_pSource_rx);
        _ry = (*_pSource_ry);
        _rz = (*_pSource_rz);
        double vx, vy, vz;
        UTIL::convRzRyToVector(_rz, _ry,
                                vx, vy, vz);
        _x = (*_pSource_x) + (vx * v);
        _y = (*_pSource_y) + (vy * v);
        _z = (*_pSource_z) + (vz * v);
    } else {
        //発射元アクターが非活動中の場合
        _rx = _tmp_source_rx;
        _ry = _tmp_source_ry;
        _rz = _tmp_source_rz;
        double vx, vy, vz;
        UTIL::convRzRyToVector(_tmp_source_rz, _tmp_source_ry,
                                vx, vy, vz);
        _x = _tmp_source_x + (vx * v);
        _y = _tmp_source_y + (vy * v);
        _z = _tmp_source_z + (vz * v);
    }
    LaserChip::processSettlementBehavior();
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
                                //Viewport範囲内
                                _offscreen_kind = 0;
                            } else {
                                //奥平面より奥で範囲外
                                _offscreen_kind = 6;
                            }
                        } else {
                            //手前平面より手前で範囲外
                            _offscreen_kind = 5;
                        }
                    } else {
                        //右平面より右で範囲外
                        _offscreen_kind = 4;
                    }
                } else {
                    //左平面より左で範囲外
                    _offscreen_kind = 3;
                }
            } else {
                //下平面より下で範囲外
                _offscreen_kind = 2;
            }
        } else {
            //上平面より上で範囲外
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

