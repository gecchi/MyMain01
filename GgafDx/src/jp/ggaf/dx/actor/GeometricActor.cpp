#include "jp/ggaf/dx/actor/GeometricActor.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/Trucker.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Checker.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

GeometricActor::GeometricActor(const char* prm_name,
                               Checker* prm_pChecker) : BaseActor(prm_name),
_pKuroko(NEW Kuroko(this)),
_pTrucker(nullptr),
_pScaler(nullptr),
_pSeTransmitter(nullptr),
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
_dest_from_vppln_infront(0.0f),
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
    _obj_class |= Obj_GgafDx_GeometricActor;
    _class_name = "GeometricActor";
    _pFormation = nullptr;
}
Kuroko* GeometricActor::getKuroko() {
    return _pKuroko;
}

Trucker* GeometricActor::getTrucker() {
    return _pTrucker ? _pTrucker : _pTrucker = NEW Trucker(this);
}

SeTransmitterForActor* GeometricActor::getSeTransmitter() {
    return _pSeTransmitter ? _pSeTransmitter : _pSeTransmitter = NEW SeTransmitterForActor(this);
}

Scaler* GeometricActor::getScaler() {
    return _pScaler ? _pScaler : _pScaler = NEW Scaler(this);
}

void GeometricActor::processSettlementBehavior() {
    if (_is_2D) {
        // 実装中
    } else {

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
            //回転×移動のみ計算し _matWorldRotMv に
            (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
            _matWorld = _matWorldRotMv; //コピーして保持
            //回転×移動 の前に スケールを考慮して、
            //最終的な _matWorld  行列(拡大×回転×移動)を保持
            if (_sx != LEN_UNIT) {
                const float sx = SC_R(_sx);
                _matWorld._11 *= sx;
                _matWorld._12 *= sx;
                _matWorld._13 *= sx;
            }
            if (_sy != LEN_UNIT) {
                const float sy = SC_R(_sy);
                _matWorld._21 *= sy;
                _matWorld._22 *= sy;
                _matWorld._23 *= sy;
            }
            if (_sz != LEN_UNIT) {
                const float sz = SC_R(_sz);
                _matWorld._31 *= sz;
                _matWorld._32 *= sz;
                _matWorld._33 *= sz;
            }
        }

        //デフォルトでは、_matWorldRotMv = 回転変換行列 × 平行移動変換行列
        //                _matWorld      = 拡大縮小変換行列 × _matWorldRotMv となるようにしている。
        //つまり _matWorld = 拡大縮小＞回転＞平行移動
        //_matWorldRotMv は appendGroupChildAsFk() 実行時に使用されるために作成している。
        //従って appendGroupChildAsFk() を絶対使用しないならば、_matWorldRotMvの計算は不要。
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
            //何をやっているのか説明。
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
            processChangeGeoFinal(); //絶対座標計算後の処理用コールバック
        }

        //視錐台面からの距離を更新
        const dxcoord fX = _fX;
        const dxcoord fY = _fY;
        const dxcoord fZ = _fZ;
        static Camera* pCam = pGOD->getSpacetime()->getCamera();
        static const D3DXPLANE* pPlnTop = &(pCam->_plnTop);
        _dest_from_vppln_top     = pPlnTop->a * fX +
                                   pPlnTop->b * fY +
                                   pPlnTop->c * fZ +
                                   pPlnTop->d;
        static const D3DXPLANE* pPlnBottom = &(pCam->_plnBottom);
        _dest_from_vppln_bottom  = pPlnBottom->a * fX +
                                   pPlnBottom->b * fY +
                                   pPlnBottom->c * fZ +
                                   pPlnBottom->d;
        static const D3DXPLANE* pPlnLeft = &(pCam->_plnLeft);
        _dest_from_vppln_left    = pPlnLeft->a * fX +
                                   pPlnLeft->b * fY +
                                   pPlnLeft->c * fZ +
                                   pPlnLeft->d;
        static const D3DXPLANE* pPlnRight = &(pCam->_plnRight);
        _dest_from_vppln_right   = pPlnRight->a * fX +
                                   pPlnRight->b * fY +
                                   pPlnRight->c * fZ +
                                   pPlnRight->d;
        static const D3DXPLANE* pPlnInfront = &(pCam->_plnInfront);
        _dest_from_vppln_infront = pPlnInfront->a * fX +
                                   pPlnInfront->b * fY +
                                   pPlnInfront->c * fZ +
                                   pPlnInfront->d;
        static const D3DXPLANE* pPlnBack = &(pCam->_plnBack);
        _dest_from_vppln_back    = pPlnBack->a * fX +
                                   pPlnBack->b * fY +
                                   pPlnBack->c * fZ +
                                   pPlnBack->d;
        _offscreen_kind = -1;
    }
}

void GeometricActor::processPreJudgement() {
    if (_pChecker) {
        if (_can_hit_flg) {
            if (_can_hit_out_of_view == false && isOutOfView()) {
                //視野外当たり判定無効の場合は登録しない
            } else  {
                //木登録
                _pChecker->updateHitArea();
            }
        }
    }
}

void GeometricActor::changeGeoLocal() {
#ifdef MY_DEBUG
        if (!_pActor_base) {
            throwCriticalException("changeGeoLocal() : 土台アクターがありません。確認して下さい。this="<<NODE_INFO<<"");
        }
        if (_is_local) {
            throwCriticalException("changeGeoLocal() : 既にローカル座標系です。対応を確認して下さい。this="<<NODE_INFO<<"");
        }
#endif
        _x_final  = _x;
        _y_final  = _y;
        _z_final  = _z;
        _rx_final = _rx;
        _ry_final = _ry;
        _rz_final = _rz;
        _x  = _x_local;
        _y  = _y_local;
        _z  = _z_local;
        _rx = _rx_local;
        _ry = _ry_local;
        _rz = _rz_local;
        _is_local = true;
    }

void GeometricActor::changeGeoFinal() {
#ifdef MY_DEBUG
    if (!_pActor_base) {
        throwCriticalException("changeGeoFinal() : 土台アクターがありません。確認して下さい。this="<<NODE_INFO<<"");
    }
    if (!_is_local) {
        throwCriticalException("changeGeoFinal() : 既にローカル座標系です。対応を確認して下さい。this="<<NODE_INFO<<"");
    }
#endif
    _x_local = _x;
    _y_local = _y;
    _z_local = _z;
    _rx_local = _rx;
    _ry_local = _ry;
    _rz_local = _rz;
    _x  = _x_final;
    _y  = _y_final;
    _z  = _z_final;
    _rx = _rx_final;
    _ry = _ry_final;
    _rz = _rz_final;
    _is_local = false;
}

//void GeometricActor::updateGeoFinalFromLocal() {
//
//}
GgafCore::GroupHead* GeometricActor::appendGroupChildAsFk(kind_t prm_kind,
                                                     GeometricActor* prm_pGeoActor,
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
        throwCriticalException(": "<<
                                   "this="<<NODE_INFO<<" は、_pFunc_calc_rot_mv_world_matrix が nullptrの為、FKベースとなる資格がありません");
    }
#endif
    GgafCore::GroupHead* pGroupHead = appendGroupChild(prm_kind, prm_pGeoActor);
    prm_pGeoActor->_pActor_base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_x = prm_x_init_local;
    prm_pGeoActor->_y = prm_y_init_local;
    prm_pGeoActor->_z = prm_z_init_local;
    prm_pGeoActor->_rx = prm_rx_init_local;
    prm_pGeoActor->_ry = prm_ry_init_local;
    prm_pGeoActor->_rz = prm_rz_init_local;
//    prm_pGeoActor->getKuroko()->_rz_mv = prm_rz_init_local;
//    prm_pGeoActor->getKuroko()->_ry_mv = prm_ry_init_local;

    prm_pGeoActor->changeGeoFinal();
    return pGroupHead;
}

GgafCore::GroupHead* GeometricActor::appendGroupChildAsFk(GeometricActor* prm_pGeoActor,
                                                          coord prm_x_init_local,
                                                          coord prm_y_init_local,
                                                          coord prm_z_init_local,
                                                          coord prm_rx_init_local,
                                                          coord prm_ry_init_local,
                                                          coord prm_rz_init_local) {
    return appendGroupChildAsFk(prm_pGeoActor->getDefaultKind(),
                                prm_pGeoActor,
                                prm_x_init_local,
                                prm_y_init_local,
                                prm_z_init_local,
                                prm_rx_init_local,
                                prm_ry_init_local,
                                prm_rz_init_local);
}

bool GeometricActor::processHitChkLogic(GgafCore::Actor* prm_pOtherActor) {
    if (_can_hit_flg && prm_pOtherActor->_can_hit_flg) {
        //&& prm_pOtherActor->instanceOf(Obj_GgafDx_GeometricActor)) { 当たり判定があるのでGeometricActor以上と判断
        //_can_hit_flg && prm_pOtherActor->_can_hit_flg のチェックは八分木登録前にもチェックしてるが
        //ここでももう一度チェックするほうがより良い。
        //なぜならば、無駄なヒットチェックを行わないため、onHit(GgafCore::Actor*) 処理中で setHitAble(false) が行われ、
        //２重ヒットチェック防止を行っているかもしれないから。
        if (_pChecker) {
            return _pChecker->isHit(((GeometricActor*)prm_pOtherActor)->_pChecker);
        }
    }
    return false;
}

int GeometricActor::isOutOfView() {
    //境界半径（モデル自体が無い）ので、PX_DX(1) が画面内にあるかどうかを判定する。
    //モデルが画面内にあるかどうか判定は、FigureActor でオーバーライドされてた方で行う。
    if (_offscreen_kind == -1) {
        const dxcoord bound = PX_DX(1); //境界半径
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

bool GeometricActor::isOutOfSpacetime() const {
    Spacetime* pSpacetime =  pGOD->getSpacetime();
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

void GeometricActor::defineRotMvWorldMatrix(void (*prm_pFunc)(const GeometricActor*, D3DXMATRIX&)) {
    _pFunc_calc_rot_mv_world_matrix = prm_pFunc;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
}

void GeometricActor::defineRotMvWorldMatrix_Billboard() {
    defineRotMvWorldMatrix(Util::setWorldMatrix_RzBxyzMv);
}

void GeometricActor::setPositionAt(const GeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
    _z = prm_pGeoElem->z;
}

void GeometricActor::setPositionAround(coord x, coord y, coord z, coord r) {
    double out_x, out_y, out_z;
    UTIL::getRndSpherCoord(r, out_x, out_y, out_z);
    setPosition(x+out_x, y+out_y, z+out_z);
}

void GeometricActor::setPositionAround(coord x, coord y, coord r) {
    double out_x, out_y;
    UTIL::getRndCircleCoord(r, out_x, out_y);
    setPosition(x+out_x, y+out_y);
}

void GeometricActor::setPositionAroundAt(const GeometricActor* prm_pActor, coord r) {
    setPositionAround(prm_pActor->_x, prm_pActor->_y, prm_pActor->_z, r);
}
void GeometricActor::setPositionAroundAt(const GeoElem* prm_pGeoElem, coord r) {
    setPositionAround(prm_pGeoElem->x, prm_pGeoElem->y, prm_pGeoElem->z, r);
}
void GeometricActor::setFaceAngAs(const GeometricActor* prm_pActor) {
    setRxFaceAng(prm_pActor->_rx);
    setRyFaceAng(prm_pActor->_ry);
    setRzFaceAng(prm_pActor->_rz);
}
void GeometricActor::setFaceAngAs(const GeoElem* prm_pGeoElem) {
    setRxFaceAng(prm_pGeoElem->rx);
    setRyFaceAng(prm_pGeoElem->ry);
    setRzFaceAng(prm_pGeoElem->rz);
}

//void GeometricActor::setFaceAng(axis prm_axis, angle prm_face) {
//    _face[prm_axis] = UTIL::simplifyAng(prm_face);
//}

void GeometricActor::setRzFaceAng(angle prm_face) {
    _rz = UTIL::simplifyAng(prm_face);
}
void GeometricActor::setRyFaceAng(angle prm_face) {
    _ry = UTIL::simplifyAng(prm_face);
}
void GeometricActor::setRxFaceAng(angle prm_face) {
    _rx = UTIL::simplifyAng(prm_face);
}

void GeometricActor::setRzRyFaceAng(angle prm_rz_face, angle prm_ry_face) {
    setRzFaceAng(prm_rz_face);
    setRyFaceAng(prm_ry_face);
}

void GeometricActor::setFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
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

void GeometricActor::scaleAs(const GeometricActor* prm_pActor) {
    _sx = prm_pActor->_sx;
    _sy = prm_pActor->_sy;
    _sz = prm_pActor->_sz;
}

void GeometricActor::onEnd() {
    BaseActor::onEnd();
    _pFormation = nullptr;
}

GeometricActor::~GeometricActor() {
    GGAF_DELETE(_pKuroko);
    GGAF_DELETE_NULLABLE(_pTrucker);
    GGAF_DELETE_NULLABLE(_pScaler);
    GGAF_DELETE_NULLABLE(_pSeTransmitter);
}

void GeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
    GgafCore::Actor* pActor_tmp = _pChildFirst;
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

void GeometricActor::dump(std::string prm_parent) {
    _TRACE_(prm_parent <<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<DUMP_FLGS);
    GgafCore::Actor* pActor_tmp = _pChildFirst;
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

