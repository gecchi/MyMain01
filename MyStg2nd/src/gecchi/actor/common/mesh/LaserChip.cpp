#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


LaserChip::LaserChip(const char* prm_name, const char* prm_model) :
    GgafDx9MeshActor(prm_name,
                     prm_model,
                     "X/LaserChipEffect",
                     "LaserChipTechnique",
                     NEW GgafDx9GeometryMover(this),
                     NEW StgChecker(this) ) {
    _pChecker = (StgChecker*)_pGeoChecker;
    _class_name = "LaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pDispatcher = NULL; //LaserChipDispatcherの new 時に設定される。
    _chiptex_kind = 1;

    _hKind = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind" );
    _hX = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_X" );
    _hY = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Y" );
    _hZ = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Z" );
    _hRevPosZ = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_RevPosZ" );
    _hMatWorld_front = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front" );
}

void LaserChip::initialize() {

    _pGeoMover->setMoveVelocity(30000);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
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
    GgafDx9UntransformedActor::getWorldMatrix_RxRzRyScMv(this, _matWorld);
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
    _pGeoMover->behave();
/*
    //中間地点にも当たり判定
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pChecker->setHitAreaBox(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //中間の当たり判定
      _pChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pChecker->getHitAreaBoxs()->disable(1);

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
}

void LaserChip::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView);
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");

//    hr = pID3DXEffect->SetTechnique(_technique);
//    mightDx9Exception(hr, S_OK, "LaserChip::processDrawMain() SetTechnique("<<_technique<<") に失敗しました。");

    //【注意】4/15 メモ
    //奥から描画となるので processDrawXxxx は、同一フレーム内で _pChip_front が必ずしも先に実行されとは限らない。
    //processBehaviorは _pChip_front が必ず先に実行される。留意せよ。
    GgafDx9UntransformedActor::updateWorldMatrix_Mv(this, _matWorld);

    //テクスチャ種類
    hr = pID3DXEffect->SetInt(_hKind, _chiptex_kind);
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) に失敗しました。2");

    if (_pChip_front != NULL) {
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_pChip_front->_X/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) に失敗しました。1");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_pChip_front->_Y/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) に失敗しました。1");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_pChip_front->_Z/LEN_UNIT/ PX_UNIT);
        mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) に失敗しました。1");
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
                //２点(X1,Z1)(X2,Z2) を通る直線の方程式 Z = CamZ の時のX座標は
                //X = ((CamZ-Z1)*(X2-X1)/ (Z2-Z1))+X1 となる。２点にチップの座標、一つ先のチップの座標を代入し
                //この式のXがCamXより小さければのカメラ左を通過することになる。その場合チップのZ座標頂点を反転し羽の描画順序を変更する。
                //羽とは下図の①と④のポリゴンのことである。①～④がデフォルトの描画順序。
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
                //上記の判定はレーザーは奥から手前へ来てる場合の判定、手前から奥の場合は判定は反転することになる。
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

    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
    mightDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");

//	UINT numPass;
//    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() に失敗しました。");
//
//    //TODO:2009/05/15 BeginPassの処理はやや重たいことに気がつく。無駄なBeginPassとEndPassを取り除くいい方法が無いものか・・・。
//    hr = pID3DXEffect->BeginPass(0);
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass(0) に失敗しました。");
    _pMeshModel->draw(this);
//    hr = pID3DXEffect->EndPass();
//
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() に失敗しました。");
//    hr = pID3DXEffect->End();
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() に失敗しました。");

}

#ifdef OREDEBUG

void LaserChip::processDrawTerminate() {
    //当たり判定領域表示
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void LaserChip::processDrawTerminate() {}

#endif

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {

}

