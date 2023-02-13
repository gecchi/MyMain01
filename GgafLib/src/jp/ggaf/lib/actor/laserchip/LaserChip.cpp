#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
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
                              "LaserChipTechnique",
                              UTIL::createCollisionChecker(this) ) {
//    _pMeshSetModel->_draw_set_num = 11; //現在のレーザーの最大セット数は11。
    _obj_class |= Obj_LaserChip;
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
    _class_name = "LaserChip";
    _pChip_infront = nullptr;
    _pChip_behind = nullptr;
    _pDepo = nullptr; //LaserChipDepositoryに追加される時に設定される。通常LaserChipとLaserChipDepositoryはセット。
    _chip_kind = 0;
    _hitarea_edge_length = 0;
    _hitarea_edge_length_2   = _hitarea_edge_length * 2;
    _hitarea_edge_length_3   = _hitarea_edge_length * 3;
    _hitarea_edge_length_3_2 = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6   = _hitarea_edge_length_3 * 2;
    _hitarea_edge_length_6_2 = _hitarea_edge_length_6 * 2;

    setZEnableDraw(true);    //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    setCullingDraw(false);
    _middle_colli_able = false;
    _rate_of_length = 1.0f;
    _power = 1.0f;
    _pMassMeshModel->registerCallback_VertexInstanceDataInfo(LaserChip::createVertexInstanceData);
    //モデル単位でセットすれば事足りるのだが、めんどうなので、アクター毎にセット
    static volatile bool is_init = LaserChip::initStatic(this); //静的メンバ初期化
}

bool LaserChip::initStatic(LaserChip* prm_pLaserChip) {
    return true;
}

void LaserChip::executeHitChk_MeAnd(GgafCore::Actor* prm_pOtherActor) {
    if (_pChip_infront == nullptr) {  //先端チップ
        GgafDx::FigureActor::executeHitChk_MeAnd(prm_pOtherActor);
    } else {
        if ((prm_pOtherActor->_obj_class & Obj_MassWallActor) == Obj_MassWallActor) {
            //相手が地形ブロックならば、先端だけしか判定しない
            return;
        } else {
            GgafDx::FigureActor::executeHitChk_MeAnd(prm_pOtherActor);
        }
    }
}

void LaserChip::onActive() {
    //出現時
    _chip_kind = 0; //未だ不明
    if (_pDepo) {
        _pDepo->_num_chip_active++;
    }
    _force_alpha = 1.00; //最初は奥でもハッキリ映る。
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    GgafDx::CollisionArea* pArea = pChecker->getActiveCollisionArea();
    if (pArea) {
        pChecker->changeActiveCollisionArea(0);
        pChecker->moveColliAABoxPos(0, 0, 0, 0);
    }
}

void LaserChip::processSettlementBehavior() {
//    if (getSceneMediator()->getPlatformScene()->_was_paused_flg) {
//        GgafDx::MassMeshActor::processSettlementBehavior();
//        return;
//    }
    //ここだめ_was_paused_flg

    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
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
    if (pChecker->getActiveCollisionArea() && _can_hit_flg) {
        if (_chip_kind == 5) { //5:先端チップ
            //先端チップの当たり判定を、後ろチップとの中間の位置に凹ませる。
            if (pChip_behind) {
                coord dX =  pChip_behind->_x - _x;
                coord dY =  pChip_behind->_y - _y;
                coord dZ =  pChip_behind->_z - _z;
                coord cX = dX * 0.25;
                coord cY = dY * 0.25;
                coord cZ = dZ * 0.25;
                pChecker->changeActiveCollisionArea(0);
                pChecker->moveColliAABoxPos(0, cX, cY, cZ);
            }
        } else { //if (_chip_kind != 5)
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

                coord dX = pChip_infront->_x - _x;
                coord dY = pChip_infront->_y - _y;
                coord dZ = pChip_infront->_z - _z;

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
                        setHitAble(false);
                    } else {
                        pChecker->changeActiveCollisionArea(0);  // [0] -□----------
                    }
                } else {
                    if ((ucoord)(dX+_hitarea_edge_length_3) < _hitarea_edge_length_3_2 &&
                        (ucoord)(dY+_hitarea_edge_length_3) < _hitarea_edge_length_3_2 &&
                        (ucoord)(dZ+_hitarea_edge_length_3) < _hitarea_edge_length_3_2)
                    {
                        pChecker->changeActiveCollisionArea(0);  // [0] -□----------
                        _rate_of_length = 4.0f;
                    } else {
                        //前方チップと離れすぎた場合に、中間に当たり判定領域を一時的に有効化
                        //自身と前方チップの中間に当たり判定を作り出す
                        coord cX = dX / 2;
                        coord cY = dY / 2;
                        coord cZ = dZ / 2;
                        if ((ucoord)(dX+_hitarea_edge_length_6) < _hitarea_edge_length_6_2 &&
                            (ucoord)(dY+_hitarea_edge_length_6) < _hitarea_edge_length_6_2 &&
                            (ucoord)(dZ+_hitarea_edge_length_6) < _hitarea_edge_length_6_2)
                        {
                            pChecker->changeActiveCollisionArea(1); // [1] -□----□----
                            pChecker->moveColliAABoxPos(1, cX, cY, cZ);
                            _rate_of_length = 8.0f;
                        } else {
                            pChecker->changeActiveCollisionArea(2); // [2] -□-□-□-□-
                            pChecker->moveColliAABoxPos(2, cX, cY, cZ);
                            coord cX2 = cX / 2;
                            coord cY2 = cY / 2;
                            coord cZ2 = cZ / 2;
                            pChecker->moveColliAABoxPos(1, cX2, cY2, cZ2);
                            coord cX3 = cX2 + cX;
                            coord cY3 = cY2 + cY;
                            coord cZ3 = cZ2 + cZ;
                            pChecker->moveColliAABoxPos(3, cX3, cY3, cZ3);
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
    GgafDx::MassMeshActor::processSettlementBehavior(); //八分木登録
    //TODO:八分木登録だけならprocessSettlementBehavior()を呼び出すのは少し効率が悪かもしれない。
    //当たり判定領域を更新してからprocessSettlementBehaviorで八分木登録すること。
//    }
}

void LaserChip::processPreDraw() {
    if (0 < _chip_kind && _chip_kind < 5) {
        //1~3を表示対象にする
        GgafDx::FigureActor::processPreDraw();
    }
}

void LaserChip::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
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

void LaserChip::registerHitAreaCube_AutoGenMidColli(int prm_edge_length) {
    //下位レーザーチップでオーバーライトされている可能性あり
    _middle_colli_able = true;
    _hitarea_edge_length = prm_edge_length;
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
//    pChecker->enable(0);
//    pChecker->disable(1);
//    pChecker->disable(2);
//    pChecker->disable(3);
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


LaserChip::~LaserChip() {
    GGAF_DELETE(_pColliCollisionChecker);
}

