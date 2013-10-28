#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxGeometricActor::GgafDxGeometricActor(const char* prm_name,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) : GgafDxBaseActor(prm_name, prm_pStat),
_pKurokoA(new GgafDxKurokoA(this)),
_pKurokoB(new GgafDxKurokoB(this)),
_pSeTx(new GgafDxSeTransmitterForActor(this)) {

    _obj_class |= Obj_GgafDxGeometricActor;
    _class_name = "GgafDxGeometricActor";
    _is_2D = false;
    _x = _y = _z = 0;
    _rx = _ry = _rz = 0;
    _sx = _sy = _sz = R_SC(1.0);
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    _bounding_sphere_radius = 0;
    _rate_of_bounding_sphere_radius = 1.0f;
    _pChecker = prm_pChecker;

    _offscreen_kind = -1;
    _pFunc_calcRotMvWorldMatrix = nullptr;
    _pActor_Base = nullptr;
    _dest_from_vppln_top = 0;
    _dest_from_vppln_bottom = 0;
    _dest_from_vppln_left = 0;
    _dest_from_vppln_right = 0;
    _dest_from_vppln_front = 0;
    _dest_from_vppln_back = 0;
    _x_local  = _x;
    _y_local  = _y;
    _z_local  = _z;
    _rx_local = _rx;
    _ry_local = _ry;
    _rz_local = _rz;
    _x_final  = _x;
    _y_final  = _y;
    _z_final  = _z;
    _rx_final = _rx;
    _ry_final = _ry;
    _rz_final = _rz;
    _pFormation = nullptr;

    _is_local = false;
    _was_calculated_matInvWorldRotMv = false;
}


void GgafDxGeometricActor::processSettlementBehavior() {
    if (_is_2D) {
        return;
    }

    _was_calculated_matInvWorldRotMv = false; //逆行列未計算にリセット

    if (_pActor_Base) {
        //土台あり時ローカル座標に一旦戻す
        changeGeoLocal();
    }

    //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    //World変換行列（_matWorld）を更新
    if (_pFunc_calcRotMvWorldMatrix) {
        //回転×移動のみ計算し _matWorldRotMv に保持
        (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
        //回転×移動 の前に スケールを考慮して、
        //最終的な _matWorld  行列(拡大×回転×移動)を保持
        if (_sx != LEN_UNIT) {
            float sx = SC_R(_sx);
            _matWorld._11 = sx * _matWorldRotMv._11;
            _matWorld._12 = sx * _matWorldRotMv._12;
            _matWorld._13 = sx * _matWorldRotMv._13;
        } else {
            _matWorld._11 = _matWorldRotMv._11;
            _matWorld._12 = _matWorldRotMv._12;
            _matWorld._13 = _matWorldRotMv._13;
        }
        _matWorld._14 = _matWorldRotMv._14;

        if (_sy != LEN_UNIT) {
            float sy = SC_R(_sy);
            _matWorld._21 = sy * _matWorldRotMv._21;
            _matWorld._22 = sy * _matWorldRotMv._22;
            _matWorld._23 = sy * _matWorldRotMv._23;
        } else {
            _matWorld._21 = _matWorldRotMv._21;
            _matWorld._22 = _matWorldRotMv._22;
            _matWorld._23 = _matWorldRotMv._23;
        }
        _matWorld._24 = _matWorldRotMv._24;

        if (_sz != LEN_UNIT) {
            float sz = SC_R(_sz);
            _matWorld._31 = sz * _matWorldRotMv._31;
            _matWorld._32 = sz * _matWorldRotMv._32;
            _matWorld._33 = sz * _matWorldRotMv._33;
        } else {
            _matWorld._31 = _matWorldRotMv._31;
            _matWorld._32 = _matWorldRotMv._32;
            _matWorld._33 = _matWorldRotMv._33;
        }
        _matWorld._34 = _matWorldRotMv._34;

        _matWorld._41 = _matWorldRotMv._41;
        _matWorld._42 = _matWorldRotMv._42;
        _matWorld._43 = _matWorldRotMv._43;
        _matWorld._44 = _matWorldRotMv._44;
    }

    //デフォルトでは、_matWorldRotMv = 回転変換行列 × 平行移動変換行列
    //                _matWorld      = スケール変換行列 × _matWorldRotMv となるようにしている。
    //つまり _matWorld = 拡大縮小＞回転＞平行移動
    //_matWorldRotMv は addSubGroupAsFk() 実行時に使用されるために作成している。
    //従って addSubGroupAsFk() を使用しないならば、processSettlementBehavior() をオーバーライドし、
    //変換行列作成をもっと単純化することで、少し最適化が可能。

    if (_pActor_Base) {
        //絶対座標に変換
        D3DXMatrixMultiply(&_matWorld, &_matWorld, &(_pActor_Base->_matWorldRotMv)); //合成
        D3DXMatrixMultiply(&_matWorldRotMv, &_matWorldRotMv, &(_pActor_Base->_matWorldRotMv)); //合成
        changeGeoFinal();
        //ワールド変換行列から飛行移動を取り出し最終的な座標とする
        _fX = _matWorld._41;
        _fY = _matWorld._42;
        _fZ = _matWorld._43;
        _x = DX_C(_fX);
        _y = DX_C(_fY);
        _z = DX_C(_fZ);

        //UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _rz, _ry);

        //TODO:絶対座標系の_rx, _ry, _rz に変換は保留
        //     現在の最終的な向きを、RzRyで取得求める方法は以下の通り、
        //     フレームワークでは _rx, _ry, _rz はどうでもよく変換行列があれば良い。
        //     したがって計算をスキップできる。
        //     UTIL::convVectorToRzRy() の計算負荷が無視できないと考えたため、ここで計算しない。
        //     計算で求めるんならば以下の方法で行える
        //
        //＜説明＞
        //方向ベクトルはワールド変換行列の積（_matWorldRotMv)で変換され、現在の最終的な向きに向く。
        //大元の方向ベクトルを(Xorg_,Yorg_,Zorg_)、
        //ワールド変換行列の回転部分の積（_matWorldRotMv)の成分を mat_xx、
        //最終的な方向ベクトルを(vX, vY, vZ) とすると
        //
        //                      | mat_11 mat_12 mat_13 |
        //| Xorg_ Yorg_ Zorg_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
        //                      | mat_31 mat_32 mat_33 |
        //となる。
        //
        //vX = Xorg_*mat_11 + Yorg_*mat_21 + Zorg_*mat_31
        //vY = Xorg_*mat_12 + Yorg_*mat_22 + Zorg_*mat_32
        //vZ = Xorg_*mat_13 + Yorg_*mat_23 + Zorg_*mat_33
        //
        //さてここで、大元が前方の単位方向ベクトル(1,0,0)の場合はどうなるか？を考えると
        //
        //vX = Xorg_*mat_11
        //vY = Xorg_*mat_12
        //vZ = Xorg_*mat_13
        //
        //となる。本アプリでは、モデルは全て(1,0,0)を前方としているため
        //最終的な方向ベクトルは（Xorg_*mat_11, Xorg_*mat_12, Xorg_*mat_13) となる。
        //この方向ベクトルを _rz _ry 表現すれば良い。
        //計算しやすいようにXorg_を1と置いて
        //
        //UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _rz, _ry);
        //となる
    }

    //視錐台更新
    GgafDxCamera* pCam = P_CAM;
    _dest_from_vppln_top    = pCam->_plnTop.a * _fX +
                              pCam->_plnTop.b * _fY +
                              pCam->_plnTop.c * _fZ +
                              pCam->_plnTop.d;

    _dest_from_vppln_bottom = pCam->_plnBottom.a * _fX +
                              pCam->_plnBottom.b * _fY +
                              pCam->_plnBottom.c * _fZ +
                              pCam->_plnBottom.d;

    _dest_from_vppln_left   = pCam->_plnLeft.a * _fX +
                              pCam->_plnLeft.b * _fY +
                              pCam->_plnLeft.c * _fZ +
                              pCam->_plnLeft.d;

    _dest_from_vppln_right  = pCam->_plnRight.a * _fX +
                              pCam->_plnRight.b * _fY +
                              pCam->_plnRight.c * _fZ +
                              pCam->_plnRight.d;

    _dest_from_vppln_front  = pCam->_plnFront.a * _fX +
                              pCam->_plnFront.b * _fY +
                              pCam->_plnFront.c * _fZ +
                              pCam->_plnFront.d;

    _dest_from_vppln_back   = pCam->_plnBack.a * _fX +
                              pCam->_plnBack.b * _fY +
                              pCam->_plnBack.c * _fZ +
                              pCam->_plnBack.d;
    _offscreen_kind = -1;

    //８分木登録
    if (_pChecker) {
        if (_can_hit_flg) {
            if (_can_hit_out_of_view == false && isOutOfView()) {
                //視野外当たり判定無効の場合は登録しない
            } else  {
                _pChecker->updateHitArea();
            }
        }
    }
}


GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(actorkind prm_kind,
                                                     GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_x_init_local,
                                                     coord prm_y_init_local,
                                                     coord prm_z_init_local,
                                                     coord prm_rx_init_local,
                                                     coord prm_ry_init_local,
                                                     coord prm_rz_init_local) {
#ifdef MY_DEBUG
    if (_pFunc_calcRotMvWorldMatrix) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxGeometricActor::addSubGroupAsFk() : "<<
                                   "this=("<<this<<")["<<getName()<<"] は、_pFunc_calcRotMvWorldMatrix が nullptrの為、FKベースとなる資格がありません");
    }
#endif
    GgafGroupHead* pGroupHead = addSubGroup(prm_kind, prm_pGeoActor);
    prm_pGeoActor->_pActor_Base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_x = prm_x_init_local;
    prm_pGeoActor->_y = prm_y_init_local;
    prm_pGeoActor->_z = prm_z_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_X]  = prm_rx_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Y]  = prm_ry_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Z]  = prm_rz_init_local;
    prm_pGeoActor->_pKurokoA->_angRzMv = prm_rz_init_local;
    prm_pGeoActor->_pKurokoA->_angRyMv = prm_ry_init_local;
    prm_pGeoActor->_rx = prm_rx_init_local;
    prm_pGeoActor->_ry = prm_ry_init_local;
    prm_pGeoActor->_rz = prm_rz_init_local;
    prm_pGeoActor->changeGeoFinal();
    return pGroupHead;
}

GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_x_init_local,
                                                     coord prm_y_init_local,
                                                     coord prm_z_init_local,
                                                     coord prm_rx_init_local,
                                                     coord prm_ry_init_local,
                                                     coord prm_rz_init_local) {
    return addSubGroupAsFk(prm_pGeoActor->_pStatus->getUint(STAT_DEFAULT_ACTOR_KIND),
                           prm_pGeoActor,
                           prm_x_init_local,
                           prm_y_init_local,
                           prm_z_init_local,
                           prm_rx_init_local,
                           prm_ry_init_local,
                           prm_rz_init_local);
}

bool GgafDxGeometricActor::processHitChkLogic(GgafActor* prm_pOtherActor) {
    if (_can_hit_flg && prm_pOtherActor->_can_hit_flg) {
        //&& prm_pOtherActor->instanceOf(Obj_GgafDxGeometricActor)) { 当たり判定があるのでGgafDxGeometricActor以上と判断
        //_can_hit_flg && prm_pOtherActor->_can_hit_flg のチェックは８分木登録前にもチェックしてるが
        //ここでももう一度チェックするほうがより良い。
        //なぜならば、無駄なヒットチェックを行わないため、onHit(GgafActor*) 処理中で setHitAble(false) が行われ、
        //２重ヒットチェック防止を行っているかもしれないから。
        if (_pChecker) {
            return _pChecker->isHit(((GgafDxGeometricActor*)prm_pOtherActor)->_pChecker);
        }
    }
    return false;
}

int GgafDxGeometricActor::isOutOfView() {
    //_TRACE_("name="<<getName()<<" _bounding_sphere_radius="<<_bounding_sphere_radius);
    if (_offscreen_kind == -1) {
        dxcoord bound = _bounding_sphere_radius * _rate_of_bounding_sphere_radius*2;//掛ける2は境界球を大きくして、画面境界のチラツキを抑える
        if (_dest_from_vppln_top < bound) {
            if (_dest_from_vppln_bottom < bound) {
                if (_dest_from_vppln_left < bound) {
                    if (_dest_from_vppln_right < bound) {
                        if (_dest_from_vppln_front < bound) {
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

bool GgafDxGeometricActor::isOutOfUniverse() {
    if (GgafDxUniverse::_x_gone_left < _x) {
        if (_x < GgafDxUniverse::_x_gone_right) {
            if (GgafDxUniverse::_y_gone_bottom < _y) {
                if (_y < GgafDxUniverse::_y_gone_top) {
                    if (GgafDxUniverse::_z_gone_near < _z) {
                        if (_z < GgafDxUniverse::_z_gone_far) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void GgafDxGeometricActor::defineRotMvWorldMatrix(void (*prm_pFunc)(GgafDxGeometricActor*, D3DXMATRIX&)) {
    _pFunc_calcRotMvWorldMatrix = prm_pFunc;
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
}

void GgafDxGeometricActor::positionAs(GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
    _z = prm_pGeoElem->z;
}

void GgafDxGeometricActor::rotateAs(GgafDxGeometricActor* prm_pActor) {
    _rx = prm_pActor->_rx;
    _ry = prm_pActor->_ry;
    _rz = prm_pActor->_rz;
}
void GgafDxGeometricActor::rotateAs(GgafDxGeoElem* prm_pGeoElem) {
    _rx = prm_pGeoElem->rx;
    _ry = prm_pGeoElem->ry;
    _rz = prm_pGeoElem->rz;
}

void GgafDxGeometricActor::scaleAs(GgafDxGeometricActor* prm_pActor) {
    _sx = prm_pActor->_sx;
    _sy = prm_pActor->_sy;
    _sz = prm_pActor->_sz;
}

void GgafDxGeometricActor::onEnd() {
    GgafDxBaseActor::onEnd();
    _pFormation = nullptr;
}

GgafDxGeometricActor::~GgafDxGeometricActor() {
    delete _pKurokoA;
    delete _pKurokoB;
    delete _pSeTx;
}

void GgafDxGeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
            if (pActor_tmp->getNext()) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがnullptrってます");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_("\t\t\t\t\t\t\t\t└─");
                break;
            }
        }
    }
}

void GgafDxGeometricActor::dump(std::string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"]("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump(prm_parent + "｜");
            if (pActor_tmp->getNext()) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがnullptrってます");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_(prm_parent+"└─");
                break;
            }
        }
    }
}

