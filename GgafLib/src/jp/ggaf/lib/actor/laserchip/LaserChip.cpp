#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"

using namespace GgafLib;

LaserChip::VERTEX_instancedata LaserChip::_aInstancedata[GGAFDXMASS_MAX_INSTANCE_NUM];

LaserChip::LaserChip(const char* prm_name, const char* prm_model) :
        GgafDx::MassMeshActor(prm_name,
                              prm_model,
                              "LaserChipEffect",
                              "LaserChipTechnique") {
//    _pMeshSetModel->_draw_set_num = 11; //現在のレーザーの最大セット数は11。
    _obj_class |= Obj_LaserChip;
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
    _class_name = "LaserChip";
    _pChip_infront = nullptr;
    _pChip_behind = nullptr;
    _pDepo = nullptr; //LaserChipDepositoryに追加される時に設定される。通常LaserChipとLaserChipDepositoryはセット。
    _chip_kind = 0;
    _hitarea_edge_length = 0;
    _hitarea_edge_length_harf = _hitarea_edge_length / 2;
    _hitarea_edge_length_2   = _hitarea_edge_length * 2;
    _hitarea_edge_length_3   = _hitarea_edge_length * 3;
    _hitarea_edge_length_3_2 = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6   = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6_2 = _hitarea_edge_length_6 * 2;

    useZBufferDrawing(true);    //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false);  //自身のZバッファを書き込みしない
    setCullingDraw(false);
    _middle_colli_able = false;
    _rate_of_length = 1.0f;
    _power = 1.0f;
    _pUvFlipper = NEW GgafDx::UvFlipper();
    _pMassMeshModel->registerCallback_VertexInstanceDataInfo(LaserChip::createVertexInstanceData);
    _n_dispatch_at_once = 1;
    _dispatch_index = 0;
    //モデル単位でセットすれば事足りるのだが、めんどうなので、アクター毎にセット
    static volatile bool is_init = LaserChip::initStatic(this); //静的メンバ初期化
    (void)is_init;
}

bool LaserChip::initStatic(LaserChip* prm_pLaserChip) {
    return true;
}

void LaserChip::onActive() {
    //出現時
    _chip_kind = 0; //未だ不明
    if (_pDepo) {
        _pDepo->_num_chip_active++;
    }
    _force_alpha = 1.00; //最初は奥でもハッキリ映る。
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    GgafDx::CollisionArea* pArea = pChecker->getCollisionArea();
    if (pArea) {
        pChecker->changeCollisionArea(0);
        pChecker->moveColliAABoxPos(0, 0, 0, 0);
        WorldCollisionChecker* pExChecker = (WorldCollisionChecker*)pChecker->_pNextExChecker;
        if (pExChecker) {
            pExChecker->changeCollisionArea(0);
            pExChecker->moveColliAABoxPos(0, 0, 0, 0);
        }
    }
}

void LaserChip::processSettlementBehavior() {
    //ここだめ_was_paused_flg

    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    WorldCollisionChecker* pExChecker = (WorldCollisionChecker*)pChecker->_pNextExChecker;

    const LaserChip* pChip_infront = _pChip_infront;
    const LaserChip* pChip_behind = _pChip_behind;

    //レーザーチップ種別 設定。
    //シェーダーのパラメータとなります。
    //
    //      -==========<>            レーザーは
    //
    //      -= === === === <>        こんなふうに分断されています。
    //                               縦に区切られている線の箇所が LaserChip オブジェクトです。
    //    | -=|===|===|===|<> ||      左図はレーザーをオブジェクトで区切ったつもりの図
    //
    //    <--><--><--><--><--><>
    //     ^   ^   ^   ^   ^   ^
    //     |   |   |   |   |   |
    //     |   |   |   |   |    `----- 5:先端チップ(非表示で、中間先頭チップを表示するためだけに存在)
    //     |   |   |   |    `----- 4:中間先頭チップ(表示される実質の先頭)
    //     |   |   |    `----- 3:中間チップ
    //     |   |    `----- 3:中間チップ
    //     |    `----- 3:中間チップ
    //      `----- 1:末尾チップ(ただし、前方にチップが5の場合は 2)
    //
    //先頭と先端という言葉で区別しています。
    if (pChip_infront) {
        if (pChip_infront->isActive()) {
            if (pChip_behind) {
                if (pChip_behind->isActive()) {
                    if (pChip_infront->_pChip_infront) {
                        _chip_kind = 3; //中間テクスチャチップ
                        setHitAble(true);
                    } else {
                        _chip_kind = 4; //中間先頭テクスチャチップ
                        setHitAble(true);
                    }
                } else {
                    if (pChip_infront->_chip_kind == 5) {
                        _chip_kind = 2; //先が丸い発射元の末端テクスチャチップ
                        setHitAble(true);
                    } else {
                        _chip_kind = 1; //発射元の末端テクスチャチップ
                        setHitAble(true);
                    }
                }
            } else {
                if (pChip_infront->_chip_kind == 5) {
                   _chip_kind = 2; //先が丸い発射元の末端テクスチャチップ
                } else {
                   _chip_kind = 1; //発射元の末端テクスチャチップ
                }
                if (getActiveFrame() > 2 && pChip_infront->_pChip_infront == nullptr) {
                    //途中でお尻が切れて、この条件が成立する場合。
                    //pChip_behind が nullptr で２チップのみの構成という意味で、
                    //つまり 4:中間先頭チップ  5:先端チップ の構成のみとない、表示するものが無い。
                    //無駄に2チップ飛ばすことは意味がないので、sayonara()する。
                    _chip_kind = 0;
                    sayonara();
                    setHitAble(false);
                } else {
                    setHitAble(true);
                }
            }
        } else {
            _chip_kind = 5; //先端チップ。何も描画したくない
            if (getActiveFrame() > 1 && pChip_behind == nullptr) {
                sayonara();
                setHitAble(false);
            } else {
                setHitAble(true);
            }
        }
    } else {
        _chip_kind = 5; //先端チップ。何も描画したくない
        if (getActiveFrame() > 1 && pChip_behind == nullptr) {
            sayonara();
            setHitAble(false);
        } else {
            setHitAble(true);
        }
    }
    //      ｜          ｜          ｜          ｜
    // [0] -□----------□----------□----------□-
    //      ｜          ｜          ｜          ｜
    // [1] -□----□----□----□----□----□----□-
    //      ｜          ｜          ｜          ｜
    // [2] -□-□-□-□-□-□-□-□-□-□-□-□-□-
    //      ｜          ｜          ｜          ｜
    if (pChecker->getCollisionArea() && _can_hit_flg) {


        if (_chip_kind == 5) { //5:先端チップ
            //先端チップの当たり判定を、後ろチップとの中間の位置に凹ませる。
            if (pChip_behind) {
                coord dX =  pChip_behind->_x - _x;
                coord dY =  pChip_behind->_y - _y;
                coord dZ =  pChip_behind->_z - _z;
                coord cX = dX * 0.25;
                coord cY = dY * 0.25;
                coord cZ = dZ * 0.25;
                pChecker->changeCollisionArea(0);
                pChecker->moveColliAABoxPos(0, cX, cY, cZ);
                if (pExChecker) {
                    pExChecker->changeCollisionArea(0);
                    pExChecker->moveColliAABoxPos(0, cX, cY, cZ);
                }
            }
        } else { //if (_chip_kind != 5)

            coord dX = pChip_infront->_x - _x;
            coord dY = pChip_infront->_y - _y;
            coord dZ = pChip_infront->_z - _z;
            //この処理はprocessBehavior()で行えない。なぜならば、_pChip_infront が座標移動済みの保証がないため。
            if (_middle_colli_able) { //おそらく水撒きレーザーチップの場合
                //レーザーチップの広がった間隔に当たり判定を生成して埋める
                //
                //              | -=|===|===|===|<> |
                // _chip_kind : 1   3   3   3   4   5
                //              2
                //
                //判定領域要素[0]        [1]        [2]        [3]        [0]
                //             |                                           |
                //          ┌-|-┐    ┌---┐    ┌---┐    ┌---┐    ┌-|-┐
                //  +----------+----------+----------+----------+----------+-----------+-
                //          └-|-┘    └---┘    └---┘    └---┘    └-|-┘
                //             |                                           |
                //             <------------------------------------------->
                //                                  dX
                //           <--->
                //         _hitarea_edge_length
                //

                //2025/01/20 下記のように変更
                //判定領域要素  [0]        [1]        [2]        [3]        [0]
                //            │                    │                    │
                //            ├---┐    ┌---┐    ┌---┐    ┌---┐    ├---┐
                //  +---------┼-+-┼----┼-+-┼----┼-+-┼----┼-+-┼----┼-+-┼---->
                //           0├---┘    └---┘    └---┘    └---┘    ├---┘
                //            │                    │                    │
                //             0                    0.5                  1.0
                //             <------------------------------------------>
                //                                  dX
                //             <--->  _hitarea_edge_length
                //             <->    _hitarea_edge_length_harf
                //
                //  [0] の座標
                //   d : 0 + _hitarea_edge_length_harf = 1.0 : r0
                //   r0 =  _hitarea_edge_length_harf/d
                //   ∴ dX * r0
                //      dY * r0
                //      dZ * r0
                //
                //  [1] の座標
                //   d : ((1/4)*d)+_hitarea_edge_length_harf = 1.0 : r1
                //   r1 = (((1/4)*d)+_hitarea_edge_length_harf)/d
                //      = (d+4*_hitarea_edge_length_harf)/(4*d)
                //
                //  [2] の座標
                //   d : ((2/4)*d)+_hitarea_edge_length_harf = 1.0 : r2
                //   r2 = (((2/4)*d)+_hitarea_edge_length_harf)/d
                //      = (d+2*_hitarea_edge_length_harf)/(2*d)
                //
                //  [3] の座標
                //   d : ((3/4)*d)+_hitarea_edge_length_harf = 1.0 : r3
                //   r3 = (((3/4)*d)+_hitarea_edge_length_harf)/d
                //      = (3*d+4*_hitarea_edge_length_harf)/(4*d)
                //
                //coord d = UTIL::getDistance(this, pChip_infront); //前のチップとの距離
                double dX_d = (double)dX;
                double dY_d = (double)dY;
                double dZ_d = (double)dZ;
                double d = sqrt((dX_d * dX_d) + (dY_d * dY_d) + (dZ_d * dZ_d));

//                double r0 = _hitarea_edge_length_harf / d;
//                double r1 = (d + 4*_hitarea_edge_length_harf) / (4*d);
//                double r2 = (d + 2*_hitarea_edge_length_harf) / (2*d);
//                double r3 = (3*d + 4*_hitarea_edge_length_harf) / (4*d);
                double r0 = _hitarea_edge_length_harf / d;

//                if (ABS(dX) < _hitarea_edge_length &&
//                    ABS(dY) < _hitarea_edge_length &&
//                    ABS(dZ) < _hitarea_edge_length)
//                {
//              ↓の意味は、↑と同じ。ちょっと最適化。
                if ((ucoord)(dX+_hitarea_edge_length) < _hitarea_edge_length_2 &&
                    (ucoord)(dY+_hitarea_edge_length) < _hitarea_edge_length_2 &&
                    (ucoord)(dZ+_hitarea_edge_length) < _hitarea_edge_length_2)
                {
                    //前方チップとくっつきすぎた場合に、判定領域を一時的に無効化
                    if (_chip_kind != 1) { //近くても末端だけは当たり判定あり
                        //判定領域を一時的に無効化（ただし２個に１個無効化）
                        if (pChip_infront->_can_hit_flg) {
                            setHitAble(false);
                        } else {
                            coord cX = dX * r0;
                            coord cY = dY * r0;
                            coord cZ = dZ * r0;
                            pChecker->changeCollisionArea(0);  // [0] -□----------
                            pChecker->moveColliAABoxPos(0, cX, cY, cZ);
                            if (pExChecker) {
                                pExChecker->changeCollisionArea(0);
                                pExChecker->moveColliAABoxPos(0, cX, cY, cZ);
                            }
                            _rate_of_length = 4.0f;
                        }
                    } else {
                        coord cX = dX * r0;
                        coord cY = dY * r0;
                        coord cZ = dZ * r0;
                        pChecker->changeCollisionArea(0);  // [0] -□----------
                        pChecker->moveColliAABoxPos(0, cX, cY, cZ);
                        if (pExChecker) {
                            pExChecker->changeCollisionArea(0);
                            pExChecker->moveColliAABoxPos(0, cX, cY, cZ);
                        }
                        _rate_of_length = 4.0f;
                    }
                } else {
                    if ((ucoord)(dX+_hitarea_edge_length_3) < _hitarea_edge_length_3_2 &&
                        (ucoord)(dY+_hitarea_edge_length_3) < _hitarea_edge_length_3_2 &&
                        (ucoord)(dZ+_hitarea_edge_length_3) < _hitarea_edge_length_3_2)
                    {
                        //BOX横並び３個分以上の距離以内の場合
                        //前方チップとくっつきすぎず、離れすぎず場合
                        coord cX = dX * r0;
                        coord cY = dY * r0;
                        coord cZ = dZ * r0;
                        pChecker->changeCollisionArea(0);  // [0] -□----------
                        pChecker->moveColliAABoxPos(0, cX, cY, cZ);
                        if (pExChecker) {
                            pExChecker->changeCollisionArea(0);
                            pExChecker->moveColliAABoxPos(0, cX, cY, cZ);
                        }
                        _rate_of_length = 4.0f;
                    } else {
                        //BOX横並び３個分以上の距離以上の場合
                        if ((ucoord)(dX+_hitarea_edge_length_6) < _hitarea_edge_length_6_2 &&
                            (ucoord)(dY+_hitarea_edge_length_6) < _hitarea_edge_length_6_2 &&
                            (ucoord)(dZ+_hitarea_edge_length_6) < _hitarea_edge_length_6_2)
                        {
                            //BOX横並び３個分以上６個分以内の距離以上の場合
                            //前方チップと離れた場合に、中間に当たり判定領域を一時的に有効化
                            //自身と前方チップの中間に当たり判定を作り出す
                            double r2 = (1.0 + 2.0 * r0) / 2.0;
                            pChecker->changeCollisionArea(1); // [1] -□----□----
                            coord cX0 = dX * r0;
                            coord cY0 = dY * r0;
                            coord cZ0 = dZ * r0;
                            coord cX2 = dX * r2;
                            coord cY2 = dY * r2;
                            coord cZ2 = dZ * r2;
                            pChecker->moveColliAABoxPos(0, cX0, cY0, cZ0);
                            pChecker->moveColliAABoxPos(1, cX2, cY2, cZ2);
                            if (pExChecker) {
                                pExChecker->changeCollisionArea(1);
                                pExChecker->moveColliAABoxPos(0, cX0, cY0, cZ0);
                                pExChecker->moveColliAABoxPos(1, cX2, cY2, cZ2);
                            }
                            _rate_of_length = 8.0f;
                        } else {
                            //BOX横並び６個分以内の距離以上の場合
                            //前方チップと離れすぎた場合に、中間の中間にも当たり判定領域を一時的に有効化
                            double r1 = (1.0 + 4.0 * r0) / 4.0;
                            double r2 = (1.0 + 2.0 * r0) / 2.0;
                            double r3 = (3.0 + 4.0 * r0) / 4.0;
                            pChecker->changeCollisionArea(2); // [2] -□-□-□-□-
                            coord cX0 = dX * r0;
                            coord cY0 = dY * r0;
                            coord cZ0 = dZ * r0;
                            coord cX1 = dX * r1;
                            coord cY1 = dY * r1;
                            coord cZ1 = dZ * r1;
                            coord cX2 = dX * r2;
                            coord cY2 = dY * r2;
                            coord cZ2 = dZ * r2;
                            coord cX3 = dX * r3;
                            coord cY3 = dY * r3;
                            coord cZ3 = dZ * r3;
                            pChecker->moveColliAABoxPos(0, cX0, cY0, cZ0);
                            pChecker->moveColliAABoxPos(1, cX1, cY1, cZ1);
                            pChecker->moveColliAABoxPos(2, cX2, cY2, cZ2);
                            pChecker->moveColliAABoxPos(3, cX3, cY3, cZ3);
                            if (pExChecker) {
                                pExChecker->changeCollisionArea(2);
                                pExChecker->moveColliAABoxPos(0, cX0, cY0, cZ0);
                                pExChecker->moveColliAABoxPos(1, cX1, cY1, cZ1);
                                pExChecker->moveColliAABoxPos(2, cX2, cY2, cZ2);
                                pExChecker->moveColliAABoxPos(3, cX3, cY3, cZ3);
                            }
                            _rate_of_length = 16.0f;
                        }
                    }
                }
            } else { //if (_middle_colli_able) 以外
            }

        } //if (_chip_kind != 5)
    }

    //最初は奥でもハッキリ映る。が
    //1秒後は距離に寄って薄まる仕様
    if (getActiveFrame() > 60 && _force_alpha > 0) {
        _force_alpha -= 0.01;
    }
    GgafDx::MassMeshActor::processSettlementBehavior();
}

void LaserChip::processPreDraw() {
    if (0 < _chip_kind && _chip_kind < 5) {
        //1~4を表示対象にする
        GgafDx::FigureActor::processPreDraw();
    }
}

void LaserChip::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
//    if (_sub_kind > 0) {
//        WorldCollisionChecker::drawHitArea(_pSubChecker);
//    }
#endif
}

void LaserChip::onInactive() {
    //消失時
    if (_pDepo) {
        _pDepo->_num_chip_active--;
        if (_pDepo->_num_chip_active < 0) {
            _pDepo->_num_chip_active = 0;
            //ActorDepository::onReset() による onInactive() があるので、負になる時を免れない
        }
    }
    //前後の繋がりを切断
    if (_pChip_infront) {
        _pChip_infront->_pChip_behind = nullptr;
    }
    _pChip_infront = nullptr;
    if (_pChip_behind) {
        _pChip_behind->_pChip_infront = nullptr;
    }
    _pChip_behind = nullptr;
}

int LaserChip::isOutOfView() {
    if (_offscreen_kind == -1) {
        const dxcoord bound = getModel()->_bounding_sphere_radius * _rate_of_bounding_sphere_radius*_rate_of_length*2.0f;//掛ける2は境界球を大きくして、画面境界のチラツキを抑える
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

void LaserChip::registerHitAreaCube_AutoGenMidColli(int prm_edge_length, int prm_edge_length_ex) {
    //下位レーザーチップでオーバーライトされている可能性あり
    _middle_colli_able = true;
    _hitarea_edge_length = prm_edge_length;
    _hitarea_edge_length_harf = _hitarea_edge_length / 2;
    _hitarea_edge_length_2   = _hitarea_edge_length * 2;
    _hitarea_edge_length_3   = _hitarea_edge_length * 3;
    _hitarea_edge_length_3_2 = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6   = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6_2 = _hitarea_edge_length_6 * 2;
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, prm_edge_length);

    pChecker->addCollisionArea(2);
    pChecker->setColliAACube(0, prm_edge_length);
    pChecker->setColliAACube(1, prm_edge_length);

    pChecker->addCollisionArea(4);
    pChecker->setColliAACube(0, prm_edge_length);
    pChecker->setColliAACube(1, prm_edge_length);
    pChecker->setColliAACube(2, prm_edge_length);
    pChecker->setColliAACube(3, prm_edge_length);

    if (prm_edge_length_ex > 0) {
        // 拡張
        WorldCollisionChecker* pExChecker = (WorldCollisionChecker*)pChecker->addExChecker();
        pExChecker->addCollisionArea(1);
        pExChecker->setColliAACube(0, prm_edge_length_ex);

        pExChecker->addCollisionArea(2);
        pExChecker->setColliAACube(0, prm_edge_length_ex);
        pExChecker->setColliAACube(1, prm_edge_length_ex);

        pExChecker->addCollisionArea(4);
        pExChecker->setColliAACube(0, prm_edge_length_ex);
        pExChecker->setColliAACube(1, prm_edge_length_ex);
        pExChecker->setColliAACube(2, prm_edge_length_ex);
        pExChecker->setColliAACube(3, prm_edge_length_ex);
    }
    setHitAble(true);
}


void LaserChip::createVertexInstanceData(void* prm, GgafDx::MassMeshModel::VertexInstanceDataInfo* out_info) {
    out_info->paElement = NEW D3DVERTEXELEMENT9[9];
    // Stream = 1 ---->
    WORD st1_offset_next = 0;
    //float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
    out_info->paElement[0].Stream = 1;
    out_info->paElement[0].Offset = st1_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[0].UsageIndex = 1;
    st1_offset_next += sizeof(float)*4;
    //float _21, _22, _23, _24;  // : TEXCOORD2  World変換行列、２行目
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*4;
    //float _31, _32, _33, _34;  // : TEXCOORD3  World変換行列、３行目
    out_info->paElement[2].Stream = 1;
    out_info->paElement[2].Offset = st1_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[2].UsageIndex = 3;
    st1_offset_next += sizeof(float)*4;
    //float _41, _42, _43, _44;  // : TEXCOORD4  World変換行列、４行目
    out_info->paElement[3].Stream = 1;
    out_info->paElement[3].Offset = st1_offset_next;
    out_info->paElement[3].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[3].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[3].UsageIndex = 4;
    st1_offset_next += sizeof(float)*4;

    //float _f_11, _f_12, _f_13, _14;   // : TEXCOORD5  前方チップWorld変換行列、１行目
    out_info->paElement[4].Stream = 1;
    out_info->paElement[4].Offset = st1_offset_next;
    out_info->paElement[4].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[4].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[4].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[4].UsageIndex = 5;
    st1_offset_next += sizeof(float)*4;
    //float _f_21, _f_22, _f_23, _24;   // : TEXCOORD6  前方チップWorld変換行列、２行目
    out_info->paElement[5].Stream = 1;
    out_info->paElement[5].Offset = st1_offset_next;
    out_info->paElement[5].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[5].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[5].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[5].UsageIndex = 6;
    st1_offset_next += sizeof(float)*4;
    //float _f_31, _f_32, _f_33, _34;   // : TEXCOORD7  前方チップWorld変換行列、３行目
    out_info->paElement[6].Stream = 1;
    out_info->paElement[6].Offset = st1_offset_next;
    out_info->paElement[6].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[6].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[6].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[6].UsageIndex = 7;
    st1_offset_next += sizeof(float)*4;
    //float _f_41, _f_42, _f_43, _44;   // : TEXCOORD8  前方チップWorld変換行列、４行目
    out_info->paElement[7].Stream = 1;
    out_info->paElement[7].Offset = st1_offset_next;
    out_info->paElement[7].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[7].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[7].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[7].UsageIndex = 8;
    st1_offset_next += sizeof(float)*4;

    //float _chip_kind, _force_alpha, _power, _front_chip_power;   // : TEXCOORD9  チップ種別、強制α、火力率、前方チップ火力率
    out_info->paElement[8].Stream = 1;
    out_info->paElement[8].Offset = st1_offset_next;
    out_info->paElement[8].Type   = D3DDECLTYPE_FLOAT4;
    out_info->paElement[8].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[8].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[8].UsageIndex = 9;
    st1_offset_next += sizeof(float)*4;
    // <---- Stream = 1

    out_info->element_num = 9;
    out_info->size_vertex_unit_instancedata = sizeof(LaserChip::VERTEX_instancedata);
    out_info->pInstancedata = LaserChip::_aInstancedata;
}

void LaserChip::processDraw() {
    int draw_set_num = 0; //MassMeshActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx::MassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_max_draw_set_num = pMassMeshModel->_draw_set_num;
    const hashval hash_technique = _hash_technique;
    VERTEX_instancedata* paInstancedata = LaserChip::_aInstancedata;
    static const size_t size_of_D3DXMATRIX = sizeof(D3DXMATRIX);
    GgafDx::FigureActor* pDrawActor = this;
    LaserChip* pChip = nullptr;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMeshModel && pDrawActor->_hash_technique == hash_technique) {
            pChip = (LaserChip*)pDrawActor;
            if (pChip->_pChip_infront) {
                memcpy(paInstancedata, &(pChip->_matWorld), size_of_D3DXMATRIX);
                _pUvFlipper->getUV(paInstancedata->_14, paInstancedata->_24); //_14 と _24 を u,v座標のオフセット埋め込み（使用時に 0 戻す）
                memcpy(&(paInstancedata->_f_11), &(pChip->_pChip_infront->_matWorld), size_of_D3DXMATRIX);
                paInstancedata->_chip_kind = pChip->_chip_kind;
                paInstancedata->_force_alpha = pChip->_force_alpha;
                paInstancedata->_power = pChip->_power;
                paInstancedata->_infront_chip_power = pChip->_pChip_infront->_power;
                ++paInstancedata;
                draw_set_num++;
            } else {
                //前方チップが無い場合
            }
            if (draw_set_num >= model_max_draw_set_num) {
                break;
            } else {
                pDrawActor = pDrawActor->_pNextRenderActor;
            }
        } else {
            break;
        }
    }
    ((GgafDx::MassMeshModel*)_pMassMeshModel)->GgafDx::MassMeshModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
}

void LaserChip::addModel(const char* prm_model) {
    MassMeshActor::addModel(prm_model);
    GgafDx::MassMeshModel* pModel = (GgafDx::MassMeshModel*)_lstModel.back(); //今追加したモデル
    pModel->registerCallback_VertexInstanceDataInfo(LaserChip::createVertexInstanceData);
}

GgafDx::CollisionChecker* LaserChip::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

LaserChip::~LaserChip() {
    GGAF_DELETE(_pUvFlipper);
//    GGAF_DELETE_NULLABLE(_pSubChecker);
}

