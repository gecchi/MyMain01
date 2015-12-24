#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

LaserChip::LaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
      GgafDxMeshSetActor(prm_name,
                         std::string("11/" + std::string(prm_model)).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         prm_pStat,
                         NEW CollisionChecker3D(this) ) {
    _pMeshSetModel->_set_num = 11; //現在のレーザーの最大セット数は11。
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

    static volatile bool is_init = LaserChip::initStatic(this); //静的メンバ初期化
}

D3DXHANDLE LaserChip::_ah_kind[11];
D3DXHANDLE LaserChip::_ah_force_alpha[11];
D3DXHANDLE LaserChip::_ah_matWorld_infront[11];
bool LaserChip::initStatic(LaserChip* prm_pLaserChip) {
    ID3DXEffect* const pID3DXEffect = prm_pLaserChip->getEffect()->_pID3DXEffect;
    LaserChip::_ah_kind[0]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind001" );
    LaserChip::_ah_kind[1]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind002" );
    LaserChip::_ah_kind[2]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind003" );
    LaserChip::_ah_kind[3]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind004" );
    LaserChip::_ah_kind[4]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind005" );
    LaserChip::_ah_kind[5]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind006" );
    LaserChip::_ah_kind[6]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind007" );
    LaserChip::_ah_kind[7]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind008" );
    LaserChip::_ah_kind[8]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind009" );
    LaserChip::_ah_kind[9]  = pID3DXEffect->GetParameterByName( nullptr, "g_kind010" );
    LaserChip::_ah_kind[10] = pID3DXEffect->GetParameterByName( nullptr, "g_kind011" );
    LaserChip::_ah_force_alpha[0]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha001" );
    LaserChip::_ah_force_alpha[1]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha002" );
    LaserChip::_ah_force_alpha[2]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha003" );
    LaserChip::_ah_force_alpha[3]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha004" );
    LaserChip::_ah_force_alpha[4]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha005" );
    LaserChip::_ah_force_alpha[5]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha006" );
    LaserChip::_ah_force_alpha[6]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha007" );
    LaserChip::_ah_force_alpha[7]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha008" );
    LaserChip::_ah_force_alpha[8]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha009" );
    LaserChip::_ah_force_alpha[9]  = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha010" );
    LaserChip::_ah_force_alpha[10] = pID3DXEffect->GetParameterByName( nullptr, "g_force_alpha011" );
    LaserChip::_ah_matWorld_infront[0]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront001" );
    LaserChip::_ah_matWorld_infront[1]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront002" );
    LaserChip::_ah_matWorld_infront[2]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront003" );
    LaserChip::_ah_matWorld_infront[3]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront004" );
    LaserChip::_ah_matWorld_infront[4]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront005" );
    LaserChip::_ah_matWorld_infront[5]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront006" );
    LaserChip::_ah_matWorld_infront[6]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront007" );
    LaserChip::_ah_matWorld_infront[7]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront008" );
    LaserChip::_ah_matWorld_infront[8]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront009" );
    LaserChip::_ah_matWorld_infront[9]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront010" );
    LaserChip::_ah_matWorld_infront[10] = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_infront011" );
    return true;
}

void LaserChip::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->instanceOf(Obj_WallPartsActor)) { //相手が地形ブロック
        if (_chip_kind == 3 || _can_chikei_hit) {  //3:中間先頭チップ か、1/16の地形当たり判定有りチップ
            GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxFigureActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void LaserChip::onActive() {
    //出現時
    _chip_kind = 0; //未だ不明
    if (_pDepo) {
        _pDepo->_num_chip_active++;
    }
    _force_alpha = 1.00; //最初は奥でもハッキリ映る。
    if (_middle_colli_able) {
        getCollisionChecker()->disable(1);
    }
    GgafDxCollisionArea* pArea = getCollisionChecker()->getArea();
    if (pArea) {
        GgafDxCollisionPart* p = pArea->_papColliPart[0];
        _hdx = p->_hdx;
        _hdy = p->_hdy;
        _hdz = p->_hdz;
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
    setHitAble(true);
    if (pChip_infront) {
        if (pChip_infront->isActive()) {
            if (pChip_behind) {
                if (pChip_behind->isActive()) {
                    if (pChip_infront->_pChip_infront) {
                        _chip_kind = 2; //中間テクスチャチップ
                    } else {
                        _chip_kind = 3; //中間先頭テクスチャチップ
                    }
                } else {
                    _chip_kind = 1; //発射元の末端テクスチャチップ
                }
            } else {
                _chip_kind = 1; //普通の末端テクスチャ
            }
        } else {
            _chip_kind = 4; //先端チップ。何も描画したくない
            _pChip_infront->_pChip_behind = nullptr; //前後のつながりを
            _pChip_infront = nullptr;                //切断
            if (getActiveFrame() > 1 && pChip_behind == nullptr) {
                sayonara();
            }
        }
    } else {
        _chip_kind = 4; //先端チップ。何も描画したくない
        if (getActiveFrame() > 1 && pChip_behind == nullptr) {
            sayonara();
        }
    }


    if (_chip_kind == 4) {
        if (pChip_behind) {
            coord dX =  pChip_behind->_x - _x;
            coord dY =  pChip_behind->_y - _y;
            coord dZ =  pChip_behind->_z - _z;
            int cX = dX / 2;
            int cY = dY / 2;
            int cZ = dZ / 2;
            pChecker->setColliAAB(
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
                    pChecker->setColliAAB(
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

    //最初は奥でもハッキリ映る。が
    //1秒後は距離に寄って薄まる仕様
    if (getActiveFrame() > 60 && _force_alpha > 0) {
        _force_alpha -= 0.01;
    }
    GgafDxMeshSetActor::processSettlementBehavior(); //八分木登録
    //TODO:八分木登録だけならprocessSettlementBehavior()を呼び出すのは少し効率が悪かもしれない。
    //当たり判定領域を更新してからprocessSettlementBehaviorで八分木登録すること。
}

void LaserChip::processPreDraw() {
    if (_chip_kind < 4) {
        //4以外を表示対象にする
        GgafDxFigureActor::processPreDraw();
    }
}

void LaserChip::processDraw() {
    int draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    //基本モデル頂点数
    GgafDxFigureActor* pDrawActor = this;
    LaserChip* pLaserChip = nullptr;
    int model_set_num = _pMeshSetModel->_set_num;

    while (pDrawActor) {
        if (pDrawActor->getModel() == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pLaserChip = (LaserChip*)pDrawActor;
            //もしここらへんで意味不明なエラーになったら、
            //GgafDxSpriteLaserChipActorの[MEMO]を読み直せ！
            if (pLaserChip->_pChip_infront) {
                //自身ワールド変換行列
                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pLaserChip->_matWorld));
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_ah_matWorld) に失敗しました。");
                //一つ前方のワールド変換行列
                hr = pID3DXEffect->SetMatrix(LaserChip::_ah_matWorld_infront[draw_set_num], &(pLaserChip->_pChip_infront->_matWorld));
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_ah_matWorld_infront) に失敗しました。1");
                //チップ種別
                hr = pID3DXEffect->SetInt(LaserChip::_ah_kind[draw_set_num], pLaserChip->_chip_kind);
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetInt(LaserChip::_ah_kind) に失敗しました。2");

                hr = pID3DXEffect->SetFloat(LaserChip::_ah_force_alpha[draw_set_num], pLaserChip->_force_alpha);
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetFloat(LaserChip::_ah_force_alpha) に失敗しました。2");

                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                    break;
                }

            } else {
                //先端チップは描画不要
            }
            pDrawActor = pDrawActor->_pNextActor_in_render_depth;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pLaserChip; //描画セットの最後アクターをセット
    if (draw_set_num > 0) { //描画されない可能性があるためこの判定が必要
        _pMeshSetModel->GgafDxMeshSetModel::draw(this, draw_set_num);
    }
}

void LaserChip::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
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
    pChecker->setColliAAB_Cube(0, prm_edge_length);
    pChecker->setColliAAB_Cube(1, prm_edge_length);
    pChecker->disable(1);
    setHitAble(true);
}

LaserChip::~LaserChip() {
    GGAF_DELETE(_pColliChecker);
}

