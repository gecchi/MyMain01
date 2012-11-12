#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxGeometricActor::GgafDxGeometricActor(const char* prm_name,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) : GgafDxBaseActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafDxGeometricActor;
    _class_name = "GgafDxGeometricActor";
    _is2DActor = false;
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = LEN_UNIT;
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
    _bounding_sphere_radius = 0;
    _rate_of_bounding_sphere_radius = 1.0f;
    _pChecker = prm_pChecker;
    _pKurokoA = NEW GgafDxKurokoA(this);
    _pKurokoB = NEW GgafDxKurokoB(this);
    _pSeTxer = NEW GgafDxSeTransmitterForActor(this);
    _offscreen_kind = -1;
    _pFunc_calcRotMvWorldMatrix = NULL;
    _pActor_Base = NULL;
    _dest_from_vppln_top = 0;
    _dest_from_vppln_bottom = 0;
    _dest_from_vppln_left = 0;
    _dest_from_vppln_right = 0;
    _dest_from_vppln_front = 0;
    _dest_from_vppln_back = 0;
    _X_local  = _X;
    _Y_local  = _Y;
    _Z_local  = _Z;
    _RX_local = _RX;
    _RY_local = _RY;
    _RZ_local = _RZ;
    _X_final  = _X;
    _Y_final  = _Y;
    _Z_final  = _Z;
    _RX_final = _RX;
    _RY_final = _RY;
    _RZ_final = _RZ;
    _pFormation = NULL;

    _is_local = false;
    _wasCalc_matInvWorldRotMv = false;
}


void GgafDxGeometricActor::processSettlementBehavior() {
    if (_is2DActor) {
        return;
    }

    _wasCalc_matInvWorldRotMv = false;

    if (_pActor_Base) {
        //土台あり時ローカル座標に一旦戻す
        changeGeoLocal();
    }

    //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
    //World変換行列（_matWorld）を更新
    if (_pFunc_calcRotMvWorldMatrix) {
        //回転×移動のみ計算し _matWorldRotMv に保持
        (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
        //スケールを考慮して、最終的な _matWorld を保持
        if (_SX != LEN_UNIT) {
            float Sx = SC_R(_SX);
            _matWorld._11 = Sx * _matWorldRotMv._11;
            _matWorld._12 = Sx * _matWorldRotMv._12;
            _matWorld._13 = Sx * _matWorldRotMv._13;
        } else {
            _matWorld._11 = _matWorldRotMv._11;
            _matWorld._12 = _matWorldRotMv._12;
            _matWorld._13 = _matWorldRotMv._13;
        }
        _matWorld._14 = _matWorldRotMv._14;

        if (_SY != LEN_UNIT) {
            float Sy = SC_R(_SY);
            _matWorld._21 = Sy * _matWorldRotMv._21;
            _matWorld._22 = Sy * _matWorldRotMv._22;
            _matWorld._23 = Sy * _matWorldRotMv._23;
        } else {
            _matWorld._21 = _matWorldRotMv._21;
            _matWorld._22 = _matWorldRotMv._22;
            _matWorld._23 = _matWorldRotMv._23;
        }
        _matWorld._24 = _matWorldRotMv._24;

        if (_SZ != LEN_UNIT) {
            float Sz = SC_R(_SZ);
            _matWorld._31 = Sz * _matWorldRotMv._31;
            _matWorld._32 = Sz * _matWorldRotMv._32;
            _matWorld._33 = Sz * _matWorldRotMv._33;
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
        _X = DX_C(_matWorld._41);
        _Y = DX_C(_matWorld._42);
        _Z = DX_C(_matWorld._43);
        _fX = _matWorld._41;
        _fY = _matWorld._42;
        _fZ = _matWorld._43;
        //UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _RZ, _RY);

        //TODO:絶対座標系の_RX, _RY, _RZ に変換は保留
        //     現在の最終的な向きを、RzRyで取得求める方法は以下の通り、
        //     フレームワークでは _RX, _RY, _RZ はどうでもよく変換行列があれば良い。
        //     したがって計算をスキップできる。
        //     UTIL::getRzRyAng() の計算負荷が無視できないと考えたため、ここで計算しない。
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
        //この方向ベクトルを _RZ _RY 表現すれば良い。
        //計算しやすいようにXorg_を1と置いて
        //
        //UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _RZ, _RY);
        //となる
    }


    //８分木登録
    if (_pChecker) {
        if (_can_hit_out_of_view == false && isOutOfView()) {
            //視野外当たり判定無効の場合は登録しない
        } else if (_can_hit_flg) {
            _pChecker->updateHitArea();
        }
    }
    //視錐台更新
    GgafDxCamera* pCam = P_CAM;

    _dest_from_vppln_top    = pCam->_plnTop.a*_fX +
                              pCam->_plnTop.b*_fY +
                              pCam->_plnTop.c*_fZ +
                              pCam->_plnTop.d;

    _dest_from_vppln_bottom = pCam->_plnBottom.a*_fX +
                              pCam->_plnBottom.b*_fY +
                              pCam->_plnBottom.c*_fZ +
                              pCam->_plnBottom.d;

    _dest_from_vppln_left   = pCam->_plnLeft.a*_fX +
                              pCam->_plnLeft.b*_fY +
                              pCam->_plnLeft.c*_fZ +
                              pCam->_plnLeft.d;

    _dest_from_vppln_right  = pCam->_plnRight.a*_fX +
                              pCam->_plnRight.b*_fY +
                              pCam->_plnRight.c*_fZ +
                              pCam->_plnRight.d;

    _dest_from_vppln_front  = pCam->_plnFront.a*_fX +
                              pCam->_plnFront.b*_fY +
                              pCam->_plnFront.c*_fZ +
                              pCam->_plnFront.d;

    _dest_from_vppln_back   = pCam->_plnBack.a*_fX +
                              pCam->_plnBack.b*_fY +
                              pCam->_plnBack.c*_fZ +
                              pCam->_plnBack.d;
    _offscreen_kind = -1;
}


GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(actorkind prm_kind,
                                                     GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_X_init_local,
                                                     coord prm_Y_init_local,
                                                     coord prm_Z_init_local,
                                                     coord prm_RX_init_local,
                                                     coord prm_RY_init_local,
                                                     coord prm_RZ_init_local) {
    GgafGroupHead* pGroupHead = addSubGroup(prm_kind, prm_pGeoActor);
    prm_pGeoActor->_pActor_Base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_X = prm_X_init_local;
    prm_pGeoActor->_Y = prm_Y_init_local;
    prm_pGeoActor->_Z = prm_Z_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_X]  = prm_RX_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Y]  = prm_RY_init_local;
    prm_pGeoActor->_pKurokoA->_angFace[AXIS_Z]  = prm_RZ_init_local;
    prm_pGeoActor->_pKurokoA->_angRzMv = prm_RZ_init_local;
    prm_pGeoActor->_pKurokoA->_angRyMv = prm_RY_init_local;
    prm_pGeoActor->_RX = prm_RX_init_local;
    prm_pGeoActor->_RY = prm_RY_init_local;
    prm_pGeoActor->_RZ = prm_RZ_init_local;
    prm_pGeoActor->changeGeoFinal();
    return pGroupHead;
}
GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_X_init_local,
                                                     coord prm_Y_init_local,
                                                     coord prm_Z_init_local,
                                                     coord prm_RX_init_local,
                                                     coord prm_RY_init_local,
                                                     coord prm_RZ_init_local) {
    return addSubGroupAsFk(prm_pGeoActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND),
                           prm_pGeoActor,
                           prm_X_init_local,
                           prm_Y_init_local,
                           prm_Z_init_local,
                           prm_RX_init_local,
                           prm_RY_init_local,
                           prm_RZ_init_local);
}

bool GgafDxGeometricActor::processHitChkLogic(GgafActor* prm_pOtherActor) {
    if (_can_hit_flg && prm_pOtherActor->_can_hit_flg) {
        //&& prm_pOtherActor->instanceOf(Obj_GgafDxGeometricActor)) { 当たり判定があるのでGgafDxGeometricActor以上と判断
        //_can_hit_flg && prm_pOtherActor->_can_hit_flg のチェックはここでももう一度チェックが必要。（８分木登録前にもチェックしてる）
        //なぜならば、２重ヒットしないため、onHit(GgafActor*) 処理中で setHitAble(false) を行う場合がある為。
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
    if (GgafDxUniverse::_X_goneLeft < _X) {
        if (_X < GgafDxUniverse::_X_goneRight) {
            if (GgafDxUniverse::_Y_goneBottom < _Y) {
                if (_Y < GgafDxUniverse::_Y_goneTop) {
                    if (GgafDxUniverse::_Z_goneNear < _Z) {
                        if (_Z < GgafDxUniverse::_Z_goneFar) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void GgafDxGeometricActor::locateWith(GgafDxGeoElem* prm_pGeoElem) {
    _X = prm_pGeoElem->_X;
    _Y = prm_pGeoElem->_Y;
    _Z = prm_pGeoElem->_Z;
}

void GgafDxGeometricActor::rotateWith(GgafDxGeometricActor* prm_pActor) {
    _RX = prm_pActor->_RX;
    _RY = prm_pActor->_RY;
    _RZ = prm_pActor->_RZ;
}
void GgafDxGeometricActor::rotateWith(GgafDxGeoElem* prm_pGeoElem) {
    _RX = prm_pGeoElem->_RX;
    _RY = prm_pGeoElem->_RY;
    _RZ = prm_pGeoElem->_RZ;
}

void GgafDxGeometricActor::scaleWith(GgafDxGeometricActor* prm_pActor) {
    _SX = prm_pActor->_SX;
    _SY = prm_pActor->_SY;
    _SZ = prm_pActor->_SZ;
}

void GgafDxGeometricActor::onEnded() {
    GgafDxBaseActor::onEnded();
    _pFormation = NULL;
}

GgafDxGeometricActor::~GgafDxGeometricActor() {
    DELETE_IMPOSSIBLE_NULL(_pKurokoA);
    DELETE_IMPOSSIBLE_NULL(_pKurokoB);
    DELETE_IMPOSSIBLE_NULL(_pSeTxer);
}


void GgafDxGeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
            if (pActor_tmp->getNext()) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLってます");
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
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump(prm_parent + "｜");
            if (pActor_tmp->getNext()) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("【警告】"<<_class_name<<"("<<this<<")["<<getName()<<"]のnextがNULLってます");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_(prm_parent+"└─");
                break;
            }
        }
    }
}

