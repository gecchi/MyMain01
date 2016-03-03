#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"

#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LaserChip::VERTEX_instancedata LaserChip::_aInstancedata[GGAFDXMASS_MAX_INSTACE];

LaserChip::LaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        GgafDxMassMeshActor(prm_name,
                         std::string(prm_model).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         prm_pStat,
                         NEW CollisionChecker3D(this) ) {
//    _pMeshSetModel->_set_num = 11; //現在のレーザーの最大セット数は11。
    _obj_class |= Obj_LaserChip;
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _class_name = "LaserChip";
    _pChip_infront = nullptr;
    _pChip_behind = nullptr;
    _pDepo = nullptr; //LaserChipDepositoryに追加される時に設定される。通常LaserChipとLaserChipDepositoryはセット。
    _chip_kind = 0;
    _hitarea_edge_length = 0;
//    _harf_hitarea_edge_length = 0;
    _hdx = _hdy = _hdz = 0;
    _can_chikei_hit = false;

    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setAlpha(0.99);
    _middle_colli_able = false;

    _pMassMeshModel->registerCallback_VertexInstaceDataInfo(LaserChip::createVertexInstaceData);
    //モデル単位でセットすれば事足りるのだが、めんどうなので、アクター毎にセット
    static volatile bool is_init = LaserChip::initStatic(this); //静的メンバ初期化
}

bool LaserChip::initStatic(LaserChip* prm_pLaserChip) {
    ID3DXEffect* const pID3DXEffect = prm_pLaserChip->getEffect()->_pID3DXEffect;

    return true;
}

void LaserChip::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->instanceOf(Obj_WallPartsActor)) {   //相手が地形ブロック
        if (_pChip_infront == nullptr || _can_chikei_hit) {  //先端チップ か、1/16の地形当たり判定有りチップ
            GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void LaserChip::onActive() {
    CollisionChecker3D* pChecker = getCollisionChecker();

    //出現時
    _chip_kind = 0; //未だ不明
    if (_pDepo) {
        _pDepo->_num_chip_active++;
    }
    _force_alpha = 1.00; //最初は奥でもハッキリ映る。

    GgafDxCollisionArea* pArea = pChecker->getArea();
    if (pArea) {
        if (_middle_colli_able) {
            pChecker->disable(1);
        }

        GgafDxCollisionPart* p = pArea->_papColliPart[0];
        _hdx = p->_hdx;
        _hdy = p->_hdy;
        _hdz = p->_hdz;
        pChecker->setColliAABox(
                0,
                -_hdx,
                -_hdy,
                -_hdz,
                +_hdx,
                +_hdy,
                +_hdz
                );
    }
}

void LaserChip::processSettlementBehavior() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    const LaserChip* pChip_infront = _pChip_infront;
    const LaserChip* pChip_behind = _pChip_behind;

    //レーザーチップ種別 設定。
    //シェーダーのパラメータとなります。
    //
    //      -==========<>            レーザーは
    //
    //      -= === === === <>        こんなふうに分断されています。
    //                               縦に区切られている線の箇所が LaserChip オブジェクトです。
    //    | -=|===|===|===|<> |      左図はレーザーをオブジェクトで区切ったつもりの図
    //
    //    <--><--><--><--><-->^
    //    ^   ^   ^   ^   ^   |
    //    |   |   |   |   |   |
    //    |   |   |   |   |    `----- 4:先端チップ(非表示で、中間先頭チップを表示するためだけに存在)
    //    |   |   |   |    `----- 3:中間先頭チップ(表示される実質の先頭)
    //    |   |   |    `----- 2:中間チップ
    //    |   |    `----- 2:中間チップ
    //    |    `----- 2:中間チップ
    //     `----- 1:末尾チップ
    //
    //先頭と先端という言葉で区別しています。
    if (pChip_infront) {
        if (pChip_infront->isActive()) {
            if (pChip_behind) {
                if (pChip_behind->isActive()) {
                    if (pChip_infront->_pChip_infront) {
                        _chip_kind = 2; //中間テクスチャチップ
                        setHitAble(true);
                    } else {
                        _chip_kind = 3; //中間先頭テクスチャチップ
                        setHitAble(true);
                    }
                } else {
                    _chip_kind = 1; //発射元の末端テクスチャチップ
                    setHitAble(true);
                }
            } else {
                _chip_kind = 1; //普通の末端テクスチャ
                if (getActiveFrame() > 2 && pChip_infront->_pChip_infront == nullptr) {
                    _chip_kind = 0;
                    sayonara();
                    setHitAble(false);
                } else {
                    setHitAble(true);
                }
            }
        } else {
            _chip_kind = 4; //先端チップ。何も描画したくない
            if (getActiveFrame() > 1 && pChip_behind == nullptr) {
                sayonara();
                setHitAble(false);
            } else {
                setHitAble(true);
            }
        }
    } else {
        _chip_kind = 4; //先端チップ。何も描画したくない
        if (getActiveFrame() > 1 && pChip_behind == nullptr) {
            sayonara();
            setHitAble(false);
        } else {
            setHitAble(true);
        }
    }

    if (pChecker->getArea()) {
        if (_chip_kind == 4) {
            //先端チップの当たり判定を、後ろチップとの中間の位置に凹ませる。
            if (pChip_behind) {
                coord dX =  pChip_behind->_x - _x;
                coord dY =  pChip_behind->_y - _y;
                coord dZ =  pChip_behind->_z - _z;
                int cX = dX / 2;
                int cY = dY / 2;
                int cZ = dZ / 2;
                pChecker->setColliAABox(
                          0,
                          cX - _hdx,
                          cY - _hdy,
                          cZ - _hdz,
                          cX + _hdx,
                          cY + _hdy,
                          cZ + _hdz
                          );
                setHitAble(true);
            } else {
                setHitAble(false);
            }
        }


        //この処理はprocessBehavior()で行えない。なぜならば、_pChip_infront が座標移動済みの保証がないため。
        if (_middle_colli_able) { //おそらく水撒きレーザーチップの場合
            if (_chip_kind == 1 || _chip_kind == 2) {
                coord dX = pChip_infront->_x - _x;
                coord dY = pChip_infront->_y - _y;
                coord dZ = pChip_infront->_z - _z;
                coord abs_dx = ABS(dX);
                coord abs_dy = ABS(dY);
                coord abs_dz = ABS(dZ);

                if (abs_dx < _hitarea_edge_length &&
                    abs_dy < _hitarea_edge_length &&
                    abs_dz < _hitarea_edge_length) {
                    //前方チップとくっつきすぎた場合に、判定領域を一時的に無効化
                    setHitAble(false);
                } else {
                    setHitAble(true);
                    if (abs_dx >= _hitarea_edge_length_3 ||
                        abs_dy >= _hitarea_edge_length_3 ||
                        abs_dz >= _hitarea_edge_length_3) {
                        //前方チップと離れすぎた場合に、中間に当たり判定領域を一時的に有効化
                        //自身と前方チップの中間に当たり判定を作り出す
                        int cX = dX / 2;
                        int cY = dY / 2;
                        int cZ = dZ / 2;
                        pChecker->setColliAABox(
                                      1,
                                      cX - _hdx,
                                      cY - _hdy,
                                      cZ - _hdz,
                                      cX + _hdx,
                                      cY + _hdy,
                                      cZ + _hdz
                                      );
                        pChecker->enable(1);
                    } else {
                        pChecker->disable(1);
                    }
                }
            } else {
                pChecker->disable(1);
            }
        }
    }

    //最初は奥でもハッキリ映る。が
    //1秒後は距離に寄って薄まる仕様
    if (getActiveFrame() > 60 && _force_alpha > 0) {
        _force_alpha -= 0.01;
    }
    GgafDxMassMeshActor::processSettlementBehavior(); //八分木登録
    //TODO:八分木登録だけならprocessSettlementBehavior()を呼び出すのは少し効率が悪かもしれない。
    //当たり判定領域を更新してからprocessSettlementBehaviorで八分木登録すること。
}

void LaserChip::processPreDraw() {
    if (0 < _chip_kind && _chip_kind < 4) {
        //1~3を表示対象にする
        GgafDxFigureActor::processPreDraw();
    }
}

void LaserChip::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

void LaserChip::onInactive() {
    //消失時
    if (_pDepo) {
        _pDepo->_num_chip_active--;
        if (_pDepo->_num_chip_active < 0) {
            _pDepo->_num_chip_active = 0;
            //GgafActorDepository::onReset() による onInactive() があるので、負になる時を免れない
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

void LaserChip::registerHitAreaCube_AutoGenMidColli(int prm_edge_length) {
    //下位レーザーチップでオーバーライトされている可能性あり
    _middle_colli_able = true;
    _hitarea_edge_length = prm_edge_length;
    _hitarea_edge_length_3 = _hitarea_edge_length*3;
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(2);
    pChecker->setColliAABox_Cube(0, prm_edge_length);
    pChecker->setColliAABox_Cube(1, prm_edge_length);
    pChecker->disable(1);
    setHitAble(true);
}


void LaserChip::createVertexInstaceData(GgafDxMassMeshModel::VertexInstaceDataInfo* out_info) {
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

    //float _chip_kind, _force_alpha;   // : TEXCOORD9  チップ種別、強制α
    out_info->paElement[8].Stream = 1;
    out_info->paElement[8].Offset = st1_offset_next;
    out_info->paElement[8].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[8].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[8].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[8].UsageIndex = 9;
    st1_offset_next += sizeof(float)*2;
    // <---- Stream = 1

    out_info->element_num = 9;
    out_info->size_vertex_unit_instacedata = sizeof(LaserChip::VERTEX_instancedata);
    out_info->pInstancedata = LaserChip::_aInstancedata;
}

void LaserChip::processDraw() {
    int draw_set_num = 0; //GgafDxMassMeshActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDxMassMeshModel* pMassMeshModel = _pMassMeshModel;
    const int model_max_set_num = pMassMeshModel->_set_num;
    const hashval hash_technique = _hash_technique;
    VERTEX_instancedata* paInstancedata = LaserChip::_aInstancedata;
    static const size_t SIZE_D3DXMATRIX = sizeof(D3DXMATRIX);
    static const size_t SIZE_D3DCOLORVALUE = sizeof(D3DCOLORVALUE);
    GgafDxFigureActor* pDrawActor = this;
    while (pDrawActor) {
        if (pDrawActor->getModel() == pMassMeshModel && pDrawActor->_hash_technique == hash_technique) {
            LaserChip* pChip = (LaserChip*)pDrawActor;
            memcpy(paInstancedata, &(pChip->_matWorld), SIZE_D3DXMATRIX);
            memcpy(&(paInstancedata->_f_11), &(pChip->_pChip_infront->_matWorld), SIZE_D3DXMATRIX);
            paInstancedata->_chip_kind = pChip->_chip_kind;
            paInstancedata->_force_alpha =  pChip->_force_alpha;
            paInstancedata++;
            draw_set_num++;
            if (draw_set_num >= model_max_set_num) {
                break;
            }
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    ((GgafDxMassMeshModel*)_pMassMeshModel)->GgafDxMassMeshModel::draw(this, draw_set_num);
}


LaserChip::~LaserChip() {
    GGAF_DELETE(_pColliChecker);
}

