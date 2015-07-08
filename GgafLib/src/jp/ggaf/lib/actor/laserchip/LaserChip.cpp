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
    _pChip_front = nullptr;
    _pChip_behind = nullptr;
    _pDepo = nullptr; //LaserChipDepositoryに追加される時に設定される。通常LaserChipとLaserChipDepositoryはセット。
    _chip_kind = 1;
    _hitarea_edge_length = 0;
    _harf_hitarea_edge_length = 0;
    _can_chikei_hit = false;

    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setAlpha(0.99);
    _middle_colli_able = false;

    static volatile bool is_init = LaserChip::initStatic(); //静的メンバ初期化
}

D3DXHANDLE LaserChip::_ah_kind[11];
D3DXHANDLE LaserChip::_ah_force_alpha[11];
D3DXHANDLE LaserChip::_ah_matWorld_front[11];
bool LaserChip::initStatic() {
    ID3DXEffect* const pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
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
    LaserChip::_ah_matWorld_front[0]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front001" );
    LaserChip::_ah_matWorld_front[1]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front002" );
    LaserChip::_ah_matWorld_front[2]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front003" );
    LaserChip::_ah_matWorld_front[3]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front004" );
    LaserChip::_ah_matWorld_front[4]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front005" );
    LaserChip::_ah_matWorld_front[5]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front006" );
    LaserChip::_ah_matWorld_front[6]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front007" );
    LaserChip::_ah_matWorld_front[7]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front008" );
    LaserChip::_ah_matWorld_front[8]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front009" );
    LaserChip::_ah_matWorld_front[9]  = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front010" );
    LaserChip::_ah_matWorld_front[10] = pID3DXEffect->GetParameterByName( nullptr, "g_matWorld_front011" );
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
    _chip_kind = 1;
    if (_pDepo) {
        _pDepo->_num_chip_active++;
    }
    _force_alpha = 1.00; //最初は奥でもハッキリ映る。
    if (_middle_colli_able) {
        getCollisionChecker()->disable(1);
    }
}

void LaserChip::processSettlementBehavior() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    const LaserChip* pChip_front = _pChip_front;


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
    if (pChip_front) {
        if (pChip_front->isActive()) {
            if (_pChip_behind) {
                if (_pChip_behind->isActiveInTheTree()) {
                    if (pChip_front->_pChip_front) {
                        _chip_kind = 2; //中間テクスチャチップ
                        _pLeader = pChip_front->_pLeader;
                    } else {
                        _chip_kind = 3; //中間先頭テクスチャチップ
                        _pLeader = pChip_front->_pLeader;
                    }
                } else {
                    _chip_kind = 1; //発射元の末端テクスチャチップ
                    _pLeader = pChip_front->_pLeader;
                }
            } else {
                _chip_kind = 1; //普通の末端テクスチャ
                _pLeader = pChip_front->_pLeader;
            }
        } else {
            _chip_kind = 4; //先端チップ。何も描画したくない
            _pLeader = this;
            _pChip_front->_pChip_behind = nullptr; //前後のつながりを
            _pChip_front = nullptr;                //切断
            if (getActiveFrame() > 1 && _pChip_behind == nullptr) {
                sayonara();
            }
            setHitAble(false);
        }
    } else {
        _chip_kind = 4; //先端チップ。何も描画したくない
        _pLeader = this;
        if (getActiveFrame() > 1 && _pChip_behind == nullptr) {
            sayonara();
        }
        setHitAble(false);
    }

    //この処理はprocessBehavior()で行えない。なぜならば、_pChip_front が座標移動済みの保証がないため。
    if (_middle_colli_able) { //おそらく水撒きレーザーチップの場合
        if (_chip_kind != 4) {
            coord dX = pChip_front->_x - _x;
            coord dY = pChip_front->_y - _y;
            coord dZ = pChip_front->_z - _z;
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
                                  cX - _harf_hitarea_edge_length,
                                  cY - _harf_hitarea_edge_length,
                                  cZ - _harf_hitarea_edge_length,
                                  cX + _harf_hitarea_edge_length,
                                  cY + _harf_hitarea_edge_length,
                                  cZ + _harf_hitarea_edge_length
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


    if (isOutOfSpacetime()) {
        sayonara();
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
            if (pLaserChip->_pChip_front) {
                //自身ワールド変換行列
                hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[draw_set_num], &(pLaserChip->_matWorld));
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_ah_matWorld) に失敗しました。");
                //一つ前方のワールド変換行列
                hr = pID3DXEffect->SetMatrix(LaserChip::_ah_matWorld_front[draw_set_num], &(pLaserChip->_pChip_front->_matWorld));
                checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_ah_matWorld_front) に失敗しました。1");
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
            pDrawActor = pDrawActor->_pNextActor_in_render_depth_level;
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
    if (_pChip_front) {
        _pChip_front->_pChip_behind = nullptr;
    }
    _pChip_front = nullptr;
    if (_pChip_behind) {
        _pChip_behind->_pChip_front = nullptr;
    }
    _pChip_behind = nullptr;
    _pLeader = nullptr;
}

void LaserChip::registerHitAreaCube_AutoGenMidColli(int prm_edge_length) {
    //下位レーザーチップでオーバーライトされている可能性あり
    _middle_colli_able = true;
    _hitarea_edge_length = prm_edge_length;
    _hitarea_edge_length_3 = _hitarea_edge_length*3;
    _harf_hitarea_edge_length = _hitarea_edge_length / 2;
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(2);
    pChecker->setColliAAB_Cube(0, prm_edge_length);
    pChecker->setColliAAB_Cube(1, prm_edge_length);
    pChecker->disable(1);
    setHitAble(true);
}

void LaserChip::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //α設定、レーザーチップは、現在_paMaterialは使用しない
}

void LaserChip::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //α設定、レーザーチップは、現在_paMaterialは使用しない
}

LaserChip::~LaserChip() {
    GGAF_DELETE(_pColliChecker);
}

