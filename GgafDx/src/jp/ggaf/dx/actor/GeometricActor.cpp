#include "jp/ggaf/dx/actor/GeometricActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/NaviVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"

using namespace GgafDx;

GeometricActor::GeometricActor(const char* prm_name) : GgafCore::MainActor(prm_name),
_pLocusVehicle(nullptr),
_pCoordVehicle(nullptr),
_pNaviVehicle(nullptr),
_pScaler(nullptr),
_pSeTransmitter(nullptr),
_pVehicleLeader(nullptr),
_is_fix_2D(false),
_offscreen_kind(-1),
_x(0), _y(0), _z(0),
_rx(0), _ry(0), _rz(0),
_sx(R_SC(1.0)), _sy(R_SC(1.0)), _sz(R_SC(1.0)),
//_pSubChecker(nullptr),
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
CollisionChecker* GeometricActor::createChecker() {
    return NEW CollisionChecker(this);
}
LocusVehicle* GeometricActor::getLocusVehicle() {
    return _pLocusVehicle ? _pLocusVehicle : _pLocusVehicle = NEW LocusVehicle(this);
}

CoordVehicle* GeometricActor::getCoordVehicle() {
    return _pCoordVehicle ? _pCoordVehicle : _pCoordVehicle = NEW CoordVehicle(this);
}

NaviVehicle* GeometricActor::getNaviVehicle() {
    return _pNaviVehicle ? _pNaviVehicle : _pNaviVehicle = NEW NaviVehicle(this);
}

VehicleLeader* GeometricActor::createCurveVehicleLeader(CurveManufacture* prm_pCurveManufacture) {
    VehicleLeader* pVehicleLeader = nullptr;
    CurveManufacture::MoveDriver move_driver = prm_pCurveManufacture->_move_driver;
    if (move_driver == CurveManufacture::MoveDriver::CoordVehicle) {
        pVehicleLeader = prm_pCurveManufacture->createCoordVehicleLeader(getCoordVehicle());
    } else if (move_driver == CurveManufacture::MoveDriver::LocusVehicle) {
        pVehicleLeader = prm_pCurveManufacture->createLocusVehicleLeader(getLocusVehicle());
    } else {
        throwCriticalException("createCurveVehicleLeader() : CurveManufacture::MoveDrive が設定されていません。"<<
                "ldr_file="<<prm_pCurveManufacture->_ldr_file<<" move_driver="<<move_driver<<" this="<<NODE_INFO<<"");
    }
    return pVehicleLeader;
}


SeTransmitterForActor* GeometricActor::getSeXmtr() {
    return _pSeTransmitter ? _pSeTransmitter : _pSeTransmitter = NEW SeTransmitterForActor(this);
}

Scaler* GeometricActor::getScaler() {
    return _pScaler ? _pScaler : _pScaler = NEW Scaler(this);
}

void GeometricActor::processSettlementBehavior() {
    if (_is_fix_2D) {
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
        //_matWorldRotMv は appendChildAsFk() 実行時に使用されるために作成している。
        //従って appendChildAsFk() を絶対使用しないならば、_matWorldRotMvの計算は不要。
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

        // 視錐台の面からの距離
        //-------------------------------------------------
        //  平面方程式：ax+by+cz+d
        //  平面の法線ベクトル：n = (a, b, c)
        //  平面上の1点を、p = (x0, y0, z0) とすると、
        //  平面の法線ベクトルと平面状の1点の内積：d = n*p
        //
        //  表裏判定をするときは、点 p = (x0, y0, z0)を、
        //  p = (x0, y0, z0, 1) とみなし、
        //  平面との内積：a*x0 + b*y0 + c*z0 + d*1 = ans
        //  ans > 0 なら表、ans < 0 なら裏、ans == 0 なら面上、となる。
        //  DXPlaneDotCoord() は、この処理を行っている
        //
        //  また、p = (x0, y0, z0, 0) とみなして内積の計算を行うと、
        //  角度の関係を調べることができる。
        //  → D3DXPlaneDotNormal()
        //-------------------------------------------------
        //面：a x + b y + c z + d = 0
        //点：(x0, y0, z0)
        //において、面と点の距離は        _______________
        //D = (a x0 + b y0 + cz0 + d) / √a^2 +b^2 + c^2
        //であるが
        //面方程式の法線正規化済みなので、分母＝1 となる

        //視錐台面からの距離を更新
        const dxcoord fX = _fX;
        const dxcoord fY = _fY;
        const dxcoord fZ = _fZ;
        Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
        const D3DXPLANE* pPlnTop = &(pCam->_plnTop);
        _dest_from_vppln_top     = pPlnTop->a * fX +
                                   pPlnTop->b * fY +
                                   pPlnTop->c * fZ +
                                   pPlnTop->d;
        const D3DXPLANE* pPlnBottom = &(pCam->_plnBottom);
        _dest_from_vppln_bottom  = pPlnBottom->a * fX +
                                   pPlnBottom->b * fY +
                                   pPlnBottom->c * fZ +
                                   pPlnBottom->d;
        const D3DXPLANE* pPlnLeft = &(pCam->_plnLeft);
        _dest_from_vppln_left    = pPlnLeft->a * fX +
                                   pPlnLeft->b * fY +
                                   pPlnLeft->c * fZ +
                                   pPlnLeft->d;

        const D3DXPLANE* pPlnRight = &(pCam->_plnRight);
        _dest_from_vppln_right   = pPlnRight->a * fX +
                                   pPlnRight->b * fY +
                                   pPlnRight->c * fZ +
                                   pPlnRight->d;

        const D3DXPLANE* pPlnInfront = &(pCam->_plnInfront);
        _dest_from_vppln_infront = pPlnInfront->a * fX +
                                   pPlnInfront->b * fY +
                                   pPlnInfront->c * fZ +
                                   pPlnInfront->d;
        const D3DXPLANE* pPlnBack = &(pCam->_plnBack);
        _dest_from_vppln_back    = pPlnBack->a * fX +
                                   pPlnBack->b * fY +
                                   pPlnBack->c * fZ +
                                   pPlnBack->d;
        _offscreen_kind = -1;
    }
}

void GeometricActor::judge() {
    if (_is_active_in_the_tree_flg) {
        processJudgement();    //ユーザー実装用

        //当たり判定の為に八分木（四分木）に登録する .
        if (_can_hit_flg) {
            if (_enable_out_of_view_hit_flg == false && isOutOfView()) {
                //視野外当たり判定無効の場合は登録しない
            } else {
                //木登録
                CollisionChecker* pColliChecker = getChecker();
                do {
                    if (pColliChecker->_kind > 0) {
                        pColliChecker->updateHitArea();
                    }
                    pColliChecker = (CollisionChecker*)pColliChecker->_pNextChecker;
                } while (pColliChecker);
            }
        }
        //再帰
        GgafCore::Element<GgafCore::Actor>* pElementTemp = _pChildFirst;
        while (pElementTemp) {
            pElementTemp->judge();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}
void GeometricActor::processAfterDraw() {
#ifdef MY_DEBUG
//    //各所属シーンのαカーテンを設定する。
//    getEffect()->setAlphaMaster(((Scene*)getPlatformScene())->_scene_alpha);
//    _TRACE_("this="<<getName()<<" PlathoneScene="<<((Scene*)getPlatformScene())->getName()<<" _scene_alpha="<<((Scene*)getPlatformScene())->_scene_alpha);
    //当たり判定領域表示
    int draw_hit_area_kind = pCARETAKER->_draw_hit_area_kind;
    if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME) {
        if (draw_hit_area_kind == 1) {
            pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
            drawHitArea();
            pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
        } else if (draw_hit_area_kind == 2) {
            drawHitArea();
        }
    } else {
        //pCARETAKER->_d3dfillmode == D3DFILL_SOLID
        if (draw_hit_area_kind == 1) {
            drawHitArea();
        } else if (draw_hit_area_kind == 2) {
            pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
            drawHitArea();
            pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        }

    }
#endif
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
void GeometricActor::appendChildAsFk( GeometricActor* prm_pGeoActor,
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
        throwCriticalException("GeometricActor::appendChildAsFk() : "<<
                "this="<<NODE_INFO<<" は、_pFunc_calc_rot_mv_world_matrix が nullptrの為、FKベースとなる資格がありません");
    }
#endif
    appendChild( prm_pGeoActor);
    prm_pGeoActor->_pActor_base = this;
    prm_pGeoActor->changeGeoLocal();
    prm_pGeoActor->_x = prm_x_init_local;
    prm_pGeoActor->_y = prm_y_init_local;
    prm_pGeoActor->_z = prm_z_init_local;
    prm_pGeoActor->_rx = prm_rx_init_local;
    prm_pGeoActor->_ry = prm_ry_init_local;
    prm_pGeoActor->_rz = prm_rz_init_local;
//    prm_pGeoActor->getLocusVehicle()->_rz_mv = prm_rz_init_local;
//    prm_pGeoActor->getLocusVehicle()->_ry_mv = prm_ry_init_local;

    prm_pGeoActor->changeGeoFinal();
}

int GeometricActor::isOutOfView() {
    //TODO:アイディア
    //前回の isOutOfView() 値を覚えておき
    //判定する視錐台の面の優先順位を変えると、はやくならるかも。
    //前回視錐台外の面は、今回も視錐台外の面である確率が高いため

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
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
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

void GeometricActor::setPositionByViewCoord(coord prm_view_x, coord prm_view_y, coord prm_depth) {
#ifdef MY_DEBUG
    if (_is_fix_2D) {
        throwCriticalException("GeometricActor::setPositionByViewCoord() : "<<
                "this="<<NODE_INFO<<" は、FIX2Dアクターのため、本メソッドの使用は変ではないですか？（ViewCoordを持っています）");
    }
#endif
    pCARETAKER->getSpacetime()->
            cnvViewCoordToWorld(prm_view_x, prm_view_y, prm_depth,
                                _x, _y, _z);
}

void GeometricActor::getWorldPosition(coord prm_depth, coord& out_world_x, coord& out_world_y, coord& out_world_z) {
#ifdef MY_DEBUG
    if (!_is_fix_2D) {
        throwCriticalException("GeometricActor::getWorldPosition() : "<<
                "this="<<NODE_INFO<<" は、3Dアクターのため、本メソッドの使用は変ではないですか？（WorldCoordを持っています）");
    }
#endif
    pCARETAKER->getSpacetime()->
            cnvViewCoordToWorld(_x, _y, prm_depth,
                    out_world_x, out_world_y, out_world_z);
}

void GeometricActor::setPositionByWorldCoord(coord prm_world_x, coord prm_world_y, coord prm_world_z) {
#ifdef MY_DEBUG
    if (!_is_fix_2D) {
        throwCriticalException("GeometricActor::setPositionByWorldCoord() : "<<
                "this="<<NODE_INFO<<" は、3Dアクターのため、本メソッドの使用は変ではないですか？（WorldCoordを持っています）");
    }
#endif
    pCARETAKER->getSpacetime()->
            cnvWorldCoordToView(prm_world_x, prm_world_y, prm_world_z,
                                _x, _y);
}

void GeometricActor::getViewPosition(coord& out_view_x, coord& out_view_y) {
#ifdef MY_DEBUG
    if (_is_fix_2D) {
        throwCriticalException("GeometricActor::getViewPosition() : "<<
                "this="<<NODE_INFO<<" は、FIX2Dアクターのため、本メソッドの使用は変ではないですか？（ViewCoordを持っています）");
    }
#endif
    pCARETAKER->getSpacetime()->
            cnvWorldCoordToView(_x, _y, _z,
                                out_view_x, out_view_y);
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
void GeometricActor::setFaceAngTwd(const GeometricActor* prm_pActor) {
    setFaceAngTwd(prm_pActor->_x, prm_pActor->_y, prm_pActor->_z);
}

void GeometricActor::onEnd() {
    _pFormation = nullptr;
}

GeometricActor::~GeometricActor() {
    GGAF_DELETE_NULLABLE(_pLocusVehicle);
    GGAF_DELETE_NULLABLE(_pCoordVehicle);
    GGAF_DELETE_NULLABLE(_pNaviVehicle);
    GGAF_DELETE_NULLABLE(_pScaler);
    GGAF_DELETE_NULLABLE(_pSeTransmitter);
}

void GeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<isOutOfView()<<"/"<<isOutOfSpacetime()<<""<<DUMP_FLGS);
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
    _TRACE_(prm_parent <<NODE_INFO<<"("<<_x<<","<<_y<<","<<_z<<")"<<isOutOfView()<<"/"<<isOutOfSpacetime()<<""<<DUMP_FLGS);
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

