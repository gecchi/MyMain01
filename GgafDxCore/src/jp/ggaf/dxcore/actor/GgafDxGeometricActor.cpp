#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxGeometricActor::GgafDxGeometricActor(const char* prm_name,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) : GgafDxBaseActor(prm_name, prm_pStat),
    _pKuroko(new GgafDxKuroko(this)),
    _pSeTx(new GgafDxSeTransmitterForActor(this)),
    _is_2D(false),
    _offscreen_kind(-1),
    _x(0), _y(0), _z(0),
    _rx(0), _ry(0), _rz(0),
    _sx(R_SC(1.0)), _sy(R_SC(1.0)), _sz(R_SC(1.0)),
    _pChecker(prm_pChecker),
    _rate_of_bounding_sphere_radius(1.0f),
    _fX(C_DX(_x)), _fY(C_DX(_y)), _fZ(C_DX(_z)),
    _dest_from_vppln_top(0.0f),
    _dest_from_vppln_bottom(0.0f),
    _dest_from_vppln_left(0.0f),
    _dest_from_vppln_right(0.0f),
    _dest_from_vppln_front(0.0f),
    _dest_from_vppln_back(0.0f),
    _pFunc_calc_rot_mv_world_matrix(nullptr),
    _matWorld(),
    _matWorldRotMv(),
    _matInvWorldRotMv(),
    _was_calculated_matInvWorldRotMv(false),
    _pActor_base(nullptr),
    _x_local(_x), _y_local(_y), _z_local(_z),
    _rx_local(_rx), _ry_local(_ry), _rz_local(_rz),
    _x_final(_x), _y_final(_y), _z_final(_z),
    _rx_final(_rx), _ry_final(_ry), _rz_final(_rz),
    _is_local(false)
{
    _obj_class |= Obj_GgafDxGeometricActor;
    _class_name = "GgafDxGeometricActor";
    _pFormation = nullptr;
}

void GgafDxGeometricActor::processSettlementBehavior() {
    if (_is_2D) {
        return;
    }

    _was_calculated_matInvWorldRotMv = false; //逆行列未計算にリセット

    if (_pActor_base) {
        //土台あり時ローカル座標に一旦戻す
        changeGeoLocal();
    }

    //DirectXの単位に座標を変換しておく（World変換行列作成時にも使用されます）
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    //World変換行列（_matWorld）を更新
    if (_pFunc_calc_rot_mv_world_matrix) {
        //回転×移動のみ計算し _matWorldRotMv に保持
        (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
        const D3DXMATRIX& matWorldRotMv = _matWorldRotMv;
        //回転×移動 の前に スケールを考慮して、
        //最終的な _matWorld  行列(拡大×回転×移動)を保持
        if (_sx != LEN_UNIT) {
            const float sx = SC_R(_sx);
            _matWorld._11 = sx * matWorldRotMv._11;
            _matWorld._12 = sx * matWorldRotMv._12;
            _matWorld._13 = sx * matWorldRotMv._13;
        } else {
            _matWorld._11 = matWorldRotMv._11;
            _matWorld._12 = matWorldRotMv._12;
            _matWorld._13 = matWorldRotMv._13;
        }
        _matWorld._14 = matWorldRotMv._14;

        if (_sy != LEN_UNIT) {
            const float sy = SC_R(_sy);
            _matWorld._21 = sy * matWorldRotMv._21;
            _matWorld._22 = sy * matWorldRotMv._22;
            _matWorld._23 = sy * matWorldRotMv._23;
        } else {
            _matWorld._21 = matWorldRotMv._21;
            _matWorld._22 = matWorldRotMv._22;
            _matWorld._23 = matWorldRotMv._23;
        }
        _matWorld._24 = matWorldRotMv._24;

        if (_sz != LEN_UNIT) {
            const float sz = SC_R(_sz);
            _matWorld._31 = sz * matWorldRotMv._31;
            _matWorld._32 = sz * matWorldRotMv._32;
            _matWorld._33 = sz * matWorldRotMv._33;
        } else {
            _matWorld._31 = matWorldRotMv._31;
            _matWorld._32 = matWorldRotMv._32;
            _matWorld._33 = matWorldRotMv._33;
        }
        _matWorld._34 = matWorldRotMv._34;

        _matWorld._41 = matWorldRotMv._41;
        _matWorld._42 = matWorldRotMv._42;
        _matWorld._43 = matWorldRotMv._43;
        _matWorld._44 = matWorldRotMv._44;
    }

    //デフォルトでは、_matWorldRotMv = 回転変換行列 × 平行移動変換行列
    //                _matWorld      = 拡大縮小変換行列 × _matWorldRotMv となるようにしている。
    //つまり _matWorld = 拡大縮小＞回転＞平行移動
    //_matWorldRotMv は addSubGroupAsFk() 実行時に使用されるために作成している。
    //従って addSubGroupAsFk() を絶対使用しないならば、_matWorldRotMvの計算は不要。
    //processSettlementBehavior() をオーバーライドし、
    //変換行列作成をもっと単純化することで、少し最適化が可能。

    if (_pActor_base) {
        //絶対座標に変換
        D3DXMatrixMultiply(&_matWorld     , &_matWorld     , &(_pActor_base->_matWorldRotMv)); //合成
        D3DXMatrixMultiply(&_matWorldRotMv, &_matWorldRotMv, &(_pActor_base->_matWorldRotMv)); //合成
        changeGeoFinal();
        //ワールド変換行列×土台ワールド変換行列の「回転×移動」のみの積）から平行移動部分を取り出し最終的な座標とする
        _fX = _matWorld._41;
        _fY = _matWorld._42;
        _fZ = _matWorld._43;
        _x = DX_C(_fX);
        _y = DX_C(_fY);
        _z = DX_C(_fZ);

        //ローカルでのface方向が合成済みのワールド変換行列の「回転×移動」のみの積(_matWorldRotMv)があるので、
        //ベクトル(1,0,0)に合成済み変換行列を掛ければ最終的なface方向を得れる
        UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _rz, _ry);
        _rx = _rx_local; //そのまま

        //TODO:絶対座標系の_rx, _ry, _rz に変換は保留
        //     現在の最終的な向きを、RzRyで取得求める方法は以下の通り、
        //     フレームワークでは _rx, _ry, _rz はどうでもよく変換行列があれば良い。
        //     したがって計算をスキップできる場合もある。
        //     UTIL::convVectorToRzRy() の計算負荷と相談。
        //
        //＜説明＞
        //方向ベクトルはワールド変換行列の積（_matWorldRotMv)で変換され、現在の最終的な向きに向く。
        //大元の方向ベクトルを(x_org_,y_org_,z_org_)、
        //ワールド変換行列の回転部分の積（_matWorldRotMv)の成分を mat_xx、
        //最終的な方向ベクトルを(vX, vY, vZ) とすると
        //
        //                         | mat_11 mat_12 mat_13 |
        //| x_org_ y_org_ z_org_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
        //                         | mat_31 mat_32 mat_33 |
        //となる。
        //
        //vX = x_org_*mat_11 + y_org_*mat_21 + z_org_*mat_31
        //vY = x_org_*mat_12 + y_org_*mat_22 + z_org_*mat_32
        //vZ = x_org_*mat_13 + y_org_*mat_23 + z_org_*mat_33
        //
        //さてここで、大元が前方の単位方向ベクトル(1,0,0)の場合はどうなるか？を考えると
        //
        //vX = x_org_*mat_11
        //vY = x_org_*mat_12
        //vZ = x_org_*mat_13
        //
        //となる。本アプリでは、モデルは全て(1,0,0)を前方としているため
        //最終的な方向ベクトルは（x_org_*mat_11, x_org_*mat_12, x_org_*mat_13) となる。
        //この方向ベクトルを _rz _ry 表現すれば良い。
        //計算しやすいようにx_org_を1と置いて
        //
        //UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13, _rz, _ry);
        //となる
        processChangeGeoFinal();
    }

    //視錐台面からの距離を更新
    const dxcoord fX = _fX;
    const dxcoord fY = _fY;
    const dxcoord fZ = _fZ;
    const GgafDxCamera* const pCam = P_GOD->getSpacetime()->getCamera();
    const D3DXPLANE& plnTop = pCam->_plnTop;
    _dest_from_vppln_top    = plnTop.a * fX +
                              plnTop.b * fY +
                              plnTop.c * fZ +
                              plnTop.d;
    const D3DXPLANE& plnBottom = pCam->_plnBottom;
    _dest_from_vppln_bottom = plnBottom.a * fX +
                              plnBottom.b * fY +
                              plnBottom.c * fZ +
                              plnBottom.d;
    const D3DXPLANE& plnLeft = pCam->_plnLeft;
    _dest_from_vppln_left   = plnLeft.a * fX +
                              plnLeft.b * fY +
                              plnLeft.c * fZ +
                              plnLeft.d;
    const D3DXPLANE& plnRight = pCam->_plnRight;
    _dest_from_vppln_right  = plnRight.a * fX +
                              plnRight.b * fY +
                              plnRight.c * fZ +
                              plnRight.d;
    const D3DXPLANE& plnFront = pCam->_plnFront;
    _dest_from_vppln_front  = plnFront.a * fX +
                              plnFront.b * fY +
                              plnFront.c * fZ +
                              plnFront.d;
   const D3DXPLANE& plnBack = pCam->_plnBack;
    _dest_from_vppln_back   = plnBack.a * fX +
                              plnBack.b * fY +
                              plnBack.c * fZ +
                              plnBack.d;
    _offscreen_kind = -1;

    //八分木登録
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

//void GgafDxGeometricActor::updateGeoFinalFromLocal() {
//
//}
GgafGroupHead* GgafDxGeometricActor::addSubGroupAsFk(actorkind prm_kind,
                                                     GgafDxGeometricActor* prm_pGeoActor,
                                                     coord prm_x_init_local,
                                                     coord prm_y_init_local,
                                                     coord prm_z_init_local,
                                                     coord prm_rx_init_local,
                                                     coord prm_ry_init_local,
                                                     coord prm_rz_init_local) {
#ifdef MY_DEBUG
    if (_pFunc_calc_rot_mv_world_matrix) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxGeometricActor::addSubGroupAsFk() : "<<
                                   "this="<<NODE_INFO<<" は、_pFunc_calc_rot_mv_world_matrix が nullptrの為、FKベースとなる資格がありません");
    }
#endif
    GgafGroupHead* pGroupHead = addSubGroup(prm_kind, prm_pGeoActor);
    prm_pGeoActor->_pActor_base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_x = prm_x_init_local;
    prm_pGeoActor->_y = prm_y_init_local;
    prm_pGeoActor->_z = prm_z_init_local;
    prm_pGeoActor->_rx = prm_rx_init_local;
    prm_pGeoActor->_ry = prm_ry_init_local;
    prm_pGeoActor->_rz = prm_rz_init_local;
//    prm_pGeoActor->getKuroko()->_ang_rz_mv = prm_rz_init_local;
//    prm_pGeoActor->getKuroko()->_ang_ry_mv = prm_ry_init_local;

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
    return addSubGroupAsFk(prm_pGeoActor->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND),
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
        //_can_hit_flg && prm_pOtherActor->_can_hit_flg のチェックは八分木登録前にもチェックしてるが
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
    //境界半径（モデル自体が無い）ので、PX_DX(1) が画面内にあるかどうかを判定する。
    //モデルが画面内にあるかどうか判定は、GgafDxFigureActor でオーバーライドされてた方で行う。
    if (_offscreen_kind == -1) {
        const dxcoord bound = PX_DX(1); //境界半径
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

bool GgafDxGeometricActor::isOutOfSpacetime() const {
    GgafDxSpacetime* pSpacetime =  P_GOD->getSpacetime();
    if (pSpacetime->_x_bound_left <= _x) {
        if (_x <= pSpacetime->_x_bound_right) {
            if (pSpacetime->_y_bound_bottom <= _y) {
                if (_y <= pSpacetime->_y_bound_top) {
                    if (pSpacetime->_z_bound_near <= _z) {
                        if (_z <= pSpacetime->_z_bound_far) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void GgafDxGeometricActor::defineRotMvWorldMatrix(void (*prm_pFunc)(const GgafDxGeometricActor*, D3DXMATRIX&)) {
    _pFunc_calc_rot_mv_world_matrix = prm_pFunc;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GgafDxGeometricActor::positionAs(const GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
    _z = prm_pGeoElem->z;
}
void GgafDxGeometricActor::positionAboutAs(const GgafDxGeoElem* prm_pGeoElem, coord margin) {
    _x = RND_ABOUT(prm_pGeoElem->x, margin);
    _y = RND_ABOUT(prm_pGeoElem->y, margin);
    _z = RND_ABOUT(prm_pGeoElem->z, margin);
}
void GgafDxGeometricActor::setFaceAngAs(const GgafDxGeometricActor* prm_pActor) {
    _rx = prm_pActor->_rx;
    _ry = prm_pActor->_ry;
    _rz = prm_pActor->_rz;
}
void GgafDxGeometricActor::setFaceAngAs(const GgafDxGeoElem* prm_pGeoElem) {
    _rx = prm_pGeoElem->rx;
    _ry = prm_pGeoElem->ry;
    _rz = prm_pGeoElem->rz;
}

//void GgafDxGeometricActor::setFaceAng(axis prm_axis, angle prm_angFace) {
//    _angFace[prm_axis] = UTIL::simplifyAng(prm_angFace);
//}

void GgafDxGeometricActor::setRzFaceAng(angle prm_angFace) {
    _rz = UTIL::simplifyAng(prm_angFace);
}
void GgafDxGeometricActor::setRyFaceAng(angle prm_angFace) {
    _ry = UTIL::simplifyAng(prm_angFace);
}
void GgafDxGeometricActor::setRxFaceAng(angle prm_angFace) {
    _rx = UTIL::simplifyAng(prm_angFace);
}

void GgafDxGeometricActor::setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
    coord vx = prm_tx - _x;
    coord vy = prm_ty - _y;
    coord vz = prm_tz - _z;
    if (vx == 0 && vy == 0 && vz == 0) {
        //自身の座標に等しいので、何もしない
    } else {
        UTIL::convVectorToRzRy(vx, vy, vz,
                               _rz, _ry );
    }
}

void GgafDxGeometricActor::scaleAs(const GgafDxGeometricActor* prm_pActor) {
    _sx = prm_pActor->_sx;
    _sy = prm_pActor->_sy;
    _sz = prm_pActor->_sz;
}

void GgafDxGeometricActor::onEnd() {
    GgafDxBaseActor::onEnd();
    _pFormation = nullptr;
}

GgafDxGeometricActor::~GgafDxGeometricActor() {
    delete _pKuroko;
    delete _pSeTx;
}

void GgafDxGeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
        if (pActor_tmp->getNext()) {
            pActor_tmp = pActor_tmp->getNext();
        } else {
            _TRACE_("【警告】"<<NODE_INFO<<" のnextがnullptrってます");
            break;
        }
        if (pActor_tmp->isFirst()) {
            _TRACE_("\t\t\t\t\t\t\t\t└─");
            break;
        }
    }
}

void GgafDxGeometricActor::dump(std::string prm_parent) {
    _TRACE_(prm_parent <<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->dump(prm_parent + "｜");
        if (pActor_tmp->getNext()) {
            pActor_tmp = pActor_tmp->getNext();
        } else {
            _TRACE_("【警告】"<<NODE_INFO<<" のnextがnullptrってます");
            break;
        }
        if (pActor_tmp->isFirst()) {
            _TRACE_(prm_parent+"└─");
            break;
        }
    }
}

