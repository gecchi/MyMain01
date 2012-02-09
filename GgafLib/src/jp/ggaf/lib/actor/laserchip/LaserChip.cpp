#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


LaserChip::LaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
     GgafDxMeshSetActor(prm_name,
                         string("11/" + string(prm_model)).c_str(),
                         "LaserChipEffect",
                         "LaserChipTechnique",
                         prm_pStat,
                         NEW CollisionChecker(this) ) {
    _pMeshSetModel->_set_num = 11; //現在のレーザーの最大セット数は11。
    _obj_class |= Obj_LaserChip;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDepo = NULL; //LaserChipDepositoryに追加される時に設定される。通常LaserChipとLaserChipDepositoryはセット。
    _chip_kind = 1;
    _is_regist_hitarea = false;
    _hitarea_edge_length = 0;
    _harf_hitarea_edge_length = 0;
    _can_chikei_hit = false;
    _ahKind[0]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind001" );
    _ahKind[1]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind002" );
    _ahKind[2]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind003" );
    _ahKind[3]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind004" );
    _ahKind[4]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind005" );
    _ahKind[5]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind006" );
    _ahKind[6]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind007" );
    _ahKind[7]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind008" );
    _ahKind[8]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind009" );
    _ahKind[9]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind010" );
    _ahKind[10] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind011" );
//    _ahKind[11] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind012" );
//    _ahKind[12] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind013" );
//    _ahKind[13] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind014" );
//    _ahKind[14] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind015" );
//    _ahKind[15] = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind016" );

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
//    _ah_matWorld_front[11]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front012" );
//    _ah_matWorld_front[12]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front013" );
//    _ah_matWorld_front[13]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front014" );
//    _ah_matWorld_front[14]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front015" );
//    _ah_matWorld_front[15]  = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front016" );

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
}

void LaserChip::processSettlementBehavior() {
    //前方チップと離れすぎた場合に、中間に当たり判定領域を一時的に有効化
    //この処理はprocessBehavior()で行えない。なぜならば、_pChip_front が座標移動済みの保証がないため。

    int dX, dY, dZ,cX, cY, cZ,h;
    if (_is_regist_hitarea) { //registHitAreaCubeメソッドによって登録された場合。
        if (_pChip_front != NULL) {
            dX = _pChip_front->_X - _X;
            dY = _pChip_front->_Y - _Y;
            dZ = _pChip_front->_Z - _Z;
            if (GgafUtil::abs(dX) >= _hitarea_edge_length*3 || GgafUtil::abs(dY) >= _hitarea_edge_length*3 || GgafUtil::abs(dZ) >= _hitarea_edge_length*3) {
                //自身と前方チップの中間に当たり判定を作り出す
                cX = dX / 2;
                cY = dY / 2;
                cZ = dZ / 2;
                h = _hitarea_edge_length / 2;
                _pCollisionChecker->setColliAAB(
                              1,
                              cX - _harf_hitarea_edge_length,
                              cY - _harf_hitarea_edge_length,
                              cZ - _harf_hitarea_edge_length,
                              cX + _harf_hitarea_edge_length,
                              cY + _harf_hitarea_edge_length,
                              cZ + _harf_hitarea_edge_length
                              );
                _pCollisionChecker->enable(1);
            } else {
                _pCollisionChecker->disable(1);
            }
//            //伸びすぎたら切れる
//            if (abs(dX) >= _hitarea_edge_length*5 || abs(dY) >= _hitarea_edge_length*5 || abs(dZ) >= _hitarea_edge_length*5) {
//                sayonara();
//            }
        } else {
            _pCollisionChecker->disable(1);
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
                } else {
                    _chip_kind = 3; //先頭テクスチャチップ
                }
            } else {
                _chip_kind = 1; //発射元の末端テクスチャチップ
            }
        } else {
            _chip_kind = 1; //普通の末端テクスチャ
        }
    } else {
        _chip_kind = 4; //先端チップ。何も描画したくない
        setHitAble(false);
//        if (_pChip_behind == NULL) {
//            sayonara();
//        }
    }
    if (isOutOfUniverse()) {
        sayonara();
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
                    hr = pID3DXEffect->SetInt(this->_ahKind[_draw_set_num], pLaserChip->_chip_kind);
                    checkDxException(hr, D3D_OK, "LaserChip::processDraw() SetInt(_hKind) に失敗しました。2");
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
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_BLENDFACTOR,0x00888888);
        _pMeshSetModel->draw(this, _draw_set_num);
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_BLENDFACTOR,0x00888888);
    }
}

void LaserChip::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
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

}

void LaserChip::registHitAreaCube(int prm_edge_length) {
    //_TRACE_("LaserChip::registHitAreaCube()st "<<getName()<<" bump="<<canHit());
    //下位レーザーチップでオーバーライトされている可能性あり
    _is_regist_hitarea = true;
    _hitarea_edge_length = prm_edge_length;
    _harf_hitarea_edge_length = _hitarea_edge_length / 2;
    _pCollisionChecker->makeCollision(2);
    _pCollisionChecker->setColliAAB_Cube(0, prm_edge_length);
    _pCollisionChecker->setColliAAB_Cube(1, prm_edge_length);
    _pCollisionChecker->disable(1);
    setHitAble(true);
    //_TRACE_("LaserChip::registHitAreaCube()ed "<<getName()<<" bump="<<canHit());

}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
}

