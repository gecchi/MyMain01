#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


LaserChip::LaserChip(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                     prm_model,
                     "x/LaserChipEffect",
                     "LaserChipTechnique",
                     NEW StgChecker(this) ) {
    _pStgChecker = (StgChecker*)_pChecker;
    _pMover = NEW GgafDx9GeometryMover(this);


    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDispatcher = NULL; //LaserChipDispatcherの new 時に設定される。
    _chiptex_kind = 1;

    _hKind = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind" );
//    _hX = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_X" );
//    _hY = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Y" );
//    _hZ = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Z" );
    _hRevPosZ = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ" );
    //_hMatWorld_front = _pMeshSetEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front" );

    _ahMatWorld_front[0]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front001" );

    _ahMatWorld_front[1]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front002" );

    _ahMatWorld_front[2]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front003" );
    _ahMatWorld_front[3]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front004" );

    _ahMatWorld_front[4]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front005" );
    _ahMatWorld_front[5]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front006" );
    _ahMatWorld_front[6]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front007" );
    _ahMatWorld_front[7]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front008" );

    _ahMatWorld_front[8]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front009" );
    _ahMatWorld_front[9]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front010" );
    _ahMatWorld_front[10] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front011" );
    _ahMatWorld_front[11] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front012" );
    _ahMatWorld_front[12] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front013" );
    _ahMatWorld_front[13] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front014" );
    _ahMatWorld_front[14] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front015" );
    _ahMatWorld_front[15] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front016" );

}

void LaserChip::initialize() {

    _pMover->setMoveVelocity(30000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}


void LaserChip::onActive() {
    //出現時
    _chiptex_kind = 1;
    if (_pChip_front == NULL) {
        if (_pDispatcher->_pSeConnection) {
            _pDispatcher->_pSeConnection->view()->play();
        }
    }

    _pDispatcher->_num_chip_active++;
    //レーザーは、真っ直ぐ飛ぶだけなので、ココで行列をつくり計算回数を節約。
    //後でdx,dy,dzだけ更新する。
    GgafDx9UntransformedActor::getWorldMatrix_ScRxRzRyMv(this, _matWorld);
}

void LaserChip::onInactive() {
    //消失時
    _pDispatcher->_num_chip_active--;
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

void LaserChip::processBehavior() {

    //座標に反映
    _pMover->behave();
/*
    //中間地点にも当たり判定
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pStgChecker->setHitAreaBox(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //中間の当たり判定
      _pStgChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pStgChecker->getHitAreaBoxs()->disable(1);

    }
*/

}

void LaserChip::processJudgement() {
    if (isOffScreen()) {
        inactivate();
    }

    //レーザー種別  1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先）
    if (_pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActive()) {
                if (_pChip_front->_pChip_front) {
                    _chiptex_kind = 2; //中間テクスチャ
                } else {
                    _chiptex_kind = 3; //先頭テクスチャ
                }
            } else {
                _chiptex_kind = 1; //発射元の末尾テクスチャ
            }
        } else {
            _chiptex_kind = 1; //末尾テクスチャ
        }
    } else {
        _chiptex_kind = 4; //何も描画したくない
    }

    //【注意】4/15 メモ
    //奥から描画となるので processDrawXxxx は、同一フレーム内で _pChip_front が必ずしも先に実行されとは限らない。
    //processBehavior,processJudgementは _pChip_front が必ず先に実行される。留意せよ。
    GgafDx9UntransformedActor::updateWorldMatrix_Mv(this, _matWorld);
}

void LaserChip::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView);
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshSetEffect SetMatrix(g_matView) に失敗しました。");

//    hr = pID3DXEffect->SetTechnique(_technique);
//    mightDx9Exception(hr, S_OK, "LaserChip::processDrawMain() SetTechnique("<<_technique<<") に失敗しました。");



    //テクスチャ種類
    hr = pID3DXEffect->SetInt(_hKind, _chiptex_kind);
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) に失敗しました。2");

    if (_pChip_front != NULL) {
//        hr = pID3DXEffect->SetFloat(_hX, 1.0*_pChip_front->_X/LEN_UNIT/ PX_UNIT);
//        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) に失敗しました。1");
//        hr = pID3DXEffect->SetFloat(_hY, 1.0*_pChip_front->_Y/LEN_UNIT/ PX_UNIT);
//        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) に失敗しました。1");
//        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_pChip_front->_Z/LEN_UNIT/ PX_UNIT);
//        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) に失敗しました。1");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &(_pChip_front->_matWorld));
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) に失敗しました。1");

        //チップの十字の左右の羽の描画順序を考える。
        static bool rev_pos_Z; //true = 頂点のZを-1を乗ずる。false = 何もしない
        static float slant;
        slant = (_pChip_front->_Z - _Z)*1.0 / (_pChip_front->_X - _X)*1.0;
        if (_pChip_front->_X == _X) {
            rev_pos_Z = false;
        } else if (GgafDx9Universe::_pCamera->_view_border_slant2_XZ < slant && slant < GgafDx9Universe::_pCamera->_view_border_slant1_XZ) {
            if (_pChip_front->_X > _X ) {
                rev_pos_Z = false;
            } else {
                rev_pos_Z = true;
            }
        } else {
            if (_pChip_front->_Z == _Z) {
                rev_pos_Z = false;
            } else {
                //＜2009/5/19 メモ：何を判定しようとしているのか＞
                //XZ平面において、レーザーチップがカメラの右を通過するのか左を通過するのか、
                //２点(X1,Z1)(X2,Z2) を通る直線の方程式において、 Z = CamZ の時のX座標は
                //X = ((CamZ-Z1)*(X2-X1)/ (Z2-Z1))+X1 となる。２点にチップの座標、一つ先のチップの座標を代入し
                //この式のXがCamXより小さければのカメラ左を通過することになる。その場合チップの頂点バッファのZ座標を反転(-1倍)し羽の描画順序を変更する。
                //羽とは下図の①と④のポリゴンのことをさす。①～④がデフォルトの描画順序。
                //特定の角度ではこの①と④の描画順番を変えなければ、半透明のためギザギザになる場合があるということであるのだ。
                //         ↑ｙ軸
                //         │
                //
                //          ＼
                //         │ ＼
                //         │② ＼
                //  (0,0,0)│    ┃        ｚ軸
                // ────┘----┃─   ─→
                //  ＼  ④ ：＼  ┃   ＼
                //    ＼   ：  ＼┃  ① ＼
                //       ━━━━╋━━━━
                //         │    ┃
                //          ＼ ③┃  ＼
                //            ＼ ┃    ＼ ｘ軸（方向）
                //               ┃      ┘

                static float crossCamX;
                crossCamX = ((float)(GgafDx9Universe::_pCamera->_Z - _Z)) * ((float)(_pChip_front->_X - _X) / (float)(_pChip_front->_Z - _Z)) + _X;
                if (crossCamX < GgafDx9Universe::_pCamera->_X) {
                    rev_pos_Z = true;
                } else {
                    rev_pos_Z = false;
                }
            }
            if (_pChip_front->_Z > _Z) {
                //上記の判定はレーザーは奥から手前へ来てる場合の判定、手前から奥へ飛ぶ場合は判定は反転することになる。
                rev_pos_Z = !rev_pos_Z;
            }
        }
        hr = pID3DXEffect->SetBool(_hRevPosZ, rev_pos_Z);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetBool(_hRevPosZ) に失敗しました。1");

    } else {
        //前方に連続のチップが無い場合。
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_X/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) に失敗しました。2");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_Y/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) に失敗しました。2");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_Z/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) に失敗しました。2");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &_matWorld );
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) に失敗しました。2");
        hr = pID3DXEffect->SetBool(_hRevPosZ, false);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetBool(_hRevPosZ) に失敗しました。2");
    }

    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatWorld, &_matWorld );
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");

    _pMeshSetModel->draw(this);

}

#ifdef OREDEBUG

void LaserChip::processDrawTerminate() {
    //当たり判定領域表示
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pStgChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void LaserChip::processDrawTerminate() {}

#endif

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pMover);

}

