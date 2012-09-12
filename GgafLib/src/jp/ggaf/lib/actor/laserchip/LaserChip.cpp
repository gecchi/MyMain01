#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


LaserChip::LaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
     GgafDxMeshSetActor(prm_name,
                         std::string("11/" + std::string(prm_model)).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         prm_pStat,
                         NEW CollisionChecker(this) ) {
    _pMeshSetModel->_set_num = 11; //現在のレーザーの最大セット数は11。
    _obj_class |= Obj_LaserChip;
    _pColliChecker = (CollisionChecker*)_pChecker;
    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDepo = NULL; //LaserChipDepositoryに追加される時に設定される。通常LaserChipとLaserChipDepositoryはセット。
    _chip_kind = 1;
    _is_regist_hitarea = false;
    _hitarea_edge_length = 0;
    _harf_hitarea_edge_length = 0;
    _can_chikei_hit = false;
    _ah_kind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind001" );
    _ah_kind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind002" );
    _ah_kind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind003" );
    _ah_kind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind004" );
    _ah_kind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind005" );
    _ah_kind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind006" );
    _ah_kind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind007" );
    _ah_kind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind008" );
    _ah_kind[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind009" );
    _ah_kind[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind010" );
    _ah_kind[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind011" );

    _ah_alpha[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha001" );
    _ah_alpha[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha002" );
    _ah_alpha[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha003" );
    _ah_alpha[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha004" );
    _ah_alpha[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha005" );
    _ah_alpha[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha006" );
    _ah_alpha[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha007" );
    _ah_alpha[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha008" );
    _ah_alpha[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha009" );
    _ah_alpha[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha010" );
    _ah_alpha[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_alpha011" );

    _ah_matWorld_front[0]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front001" );
    _ah_matWorld_front[1]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front002" );
    _ah_matWorld_front[2]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front003" );
    _ah_matWorld_front[3]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front004" );
    _ah_matWorld_front[4]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front005" );
    _ah_matWorld_front[5]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front006" );
    _ah_matWorld_front[6]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front007" );
    _ah_matWorld_front[7]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front008" );
    _ah_matWorld_front[8]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front009" );
    _ah_matWorld_front[9]   = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front010" );
    _ah_matWorld_front[10]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front011" );

    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void LaserChip::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (prm_pOtherActor->_obj_class & Obj_WallPartsActor) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void LaserChip::onActive() {
    //出現時
    _chip_kind = 1;
    if (_pDepo) {
        _pDepo->_num_chip_active++;
    }
    _alpha = 0.99; //最初は奥でもハッキリ映る。
}

void LaserChip::processSettlementBehavior() {
    //前方チップと離れすぎた場合に、中間に当たり判定領域を一時的に有効化
    //この処理はprocessBehavior()で行えない。なぜならば、_pChip_front が座標移動済みの保証がないため。
    if (_is_regist_hitarea) { //registHitAreaCubeメソッドによって登録された場合。
        if (_pChip_front != NULL) {
            int dX = _pChip_front->_X - _X;
            int dY = _pChip_front->_Y - _Y;
            int dZ = _pChip_front->_Z - _Z;
            if (ABS(dX) >= _hitarea_edge_length_3 ||
                ABS(dY) >= _hitarea_edge_length_3 ||
                ABS(dZ) >= _hitarea_edge_length_3) {
                //自身と前方チップの中間に当たり判定を作り出す
                int cX = dX / 2;
                int cY = dY / 2;
                int cZ = dZ / 2;
                _pColliChecker->setColliAAB(
                              1,
                              cX - _harf_hitarea_edge_length,
                              cY - _harf_hitarea_edge_length,
                              cZ - _harf_hitarea_edge_length,
                              cX + _harf_hitarea_edge_length,
                              cY + _harf_hitarea_edge_length,
                              cZ + _harf_hitarea_edge_length
                              );
                _pColliChecker->enable(1);
            } else {
                _pColliChecker->disable(1);
            }
//            //伸びすぎたら切れる
//            if (ABS(dX) >= _hitarea_edge_length*5 || ABS(dY) >= _hitarea_edge_length*5 || ABS(dZ) >= _hitarea_edge_length*5) {
//                sayonara();
//            }
        } else {
            _pColliChecker->disable(1);
        }
    }


    //レーザーチップ種別 設定。
    //シェーダーのパラメータとなります。
    //
    //      -==========<>            レーザーは
    //
    //      -= === === === <>        こんなふうに分断されています。
    //
    //    | -=|===|===|===|<> |     左図はレーザーをオブジェクトで区切ったつもりの図
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
    if (_pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActiveInTheTree()) {
                if (_pChip_front->_pChip_front) {
                    _chip_kind = 2; //中間テクスチャチップ
                    _pLeader = _pChip_front->_pLeader;
                } else {
                    _chip_kind = 3; //先頭テクスチャチップ
                    _pLeader = _pChip_front->_pLeader;
                }
            } else {
                _chip_kind = 1; //発射元の末端テクスチャチップ
                _pLeader = _pChip_front->_pLeader;
            }
        } else {
            _chip_kind = 1; //普通の末端テクスチャ
            _pLeader = _pChip_front->_pLeader;
        }
    } else {
        _chip_kind = 4; //先端チップ。何も描画したくない
        _pLeader = this;
        if (getActivePartFrame() > 1 && _pChip_behind == NULL) {
            sayonara();
        }
        setHitAble(false);
    }
    if (isOutOfUniverse()) {
        sayonara();
    }

    //最初は奥でもハッキリ映る。が
    //1秒後は距離に寄って薄まる仕様
    if (getActivePartFrame() > 60 && _alpha > 0) {
        _alpha -= 0.01;
    }
    GgafDxMeshSetActor::processSettlementBehavior(); //８分木登録
    //TODO:８分木登録だけならprocessSettlementBehavior()を呼び出すのは少し効率が悪かもしれない。
    //当たり判定領域を更新してからprocessSettlementBehaviorで８分木登録すること。
}

void LaserChip::processPreDraw() {
    if (_chip_kind < 4) {
        //4以外を表示対象にする
        GgafDxDrawableActor::processPreDraw();
    }
}

void LaserChip::processDraw() {
    _draw_set_num = 0; //GgafDxMeshSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    //基本モデル頂点数
    GgafDxDrawableActor* pDrawActor = this;
    LaserChip* pLaserChip = NULL;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pMeshSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pLaserChip = (LaserChip*)pDrawActor;

                //もしここらへんで意味不明なエラーになったら、
                //GgafDxSpriteLaserChipActorの[MEMO]を読み直せ！
                if (pLaserChip->_pChip_front) {
                    //自身ワールド変換行列
                    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ah_matWorld[_draw_set_num], &(pLaserChip->_matWorld));
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(g_matWorld) に失敗しました。");
                    //一つ前方のワールド変換行列
                    hr = pID3DXEffect->SetMatrix(this->_ah_matWorld_front[_draw_set_num], &(pLaserChip->_pChip_front->_matWorld));
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetMatrix(_h_matWorld_front) に失敗しました。1");
                    //チップ種別
                    hr = pID3DXEffect->SetInt(this->_ah_kind[_draw_set_num], pLaserChip->_chip_kind);
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) に失敗しました。2");

                    hr = pID3DXEffect->SetFloat(this->_ah_alpha[_draw_set_num], pLaserChip->getAlpha());
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetFloat(_ah_alpha) に失敗しました。2");
                } else {
                    //先端チップは描画不要
                    pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
                    continue;
                }

                _draw_set_num++;
                if (_draw_set_num >= _pMeshSetModel->_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDxUniverse::_pActor_DrawActive = pLaserChip; //描画セットの最後アクターをセット
    if (_draw_set_num > 0) { //描画されない可能性があるためこの判定が必要
        _pMeshSetModel->draw(this, _draw_set_num);
    }
}

void LaserChip::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

void LaserChip::onInactive() {
    //消失時
    if (_pDepo) {
        _pDepo->_num_chip_active--;
    }
    //前後の繋がりを切断
    if (_pChip_front) {
        _pChip_front->_pChip_behind = NULL;
    }
    _pChip_front = NULL;
    if (_pChip_behind) {
        _pChip_behind->_pChip_front = NULL;
    }
    _pChip_behind = NULL;
    _pLeader = NULL;
}

void LaserChip::registHitAreaCube(int prm_edge_length) {
    //下位レーザーチップでオーバーライトされている可能性あり
    _is_regist_hitarea = true;
    _hitarea_edge_length = prm_edge_length;
    _hitarea_edge_length_3 = _hitarea_edge_length*3;
    _harf_hitarea_edge_length = _hitarea_edge_length / 2;
    _pColliChecker->makeCollision(2);
    _pColliChecker->setColliAAB_Cube(0, prm_edge_length);
    _pColliChecker->setColliAAB_Cube(1, prm_edge_length);
    _pColliChecker->disable(1);
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
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
}

