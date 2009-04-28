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
    _pRotation = NULL; //LaserChipRotationActorの new 時に設定される。

    _hKind = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_kind" );
    _hX = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_X" );
    _hY = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Y" );
    _hZ = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Z" );
    _hMatWorld_front = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front" );
}

void LaserChip::initialize() {

    _pGeoMover->setMoveVelocity(30000);
    _pChecker->useHitAreaBoxNum(2);
    _pChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _pChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}

void LaserChip::processBehavior() {

    //座標に反映
    _pGeoMover->behave();

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
}

void LaserChip::onActive() {
    //出現時
    if (_pChip_front == NULL) {
        if (_pRotation->_pSeConnection) {
            _pRotation->_pSeConnection->view()->play();
        }
    }

    _pRotation->_num_chip_active++;
    //レーザーは、真っ直ぐ飛ぶだけなので、ココで行列をつくり計算回数を節約。
    //後でdx,dy,dzだけ更新する。
    GgafDx9UntransformedActor::getWorldMatrix_RxRzRyScMv(this, _matWorld);
}

void LaserChip::onInactive() {
    //消失時
    _pRotation->_num_chip_active--;
    //前後の繋がりを切断
    _pChip_front = NULL;
    if (_pChip_behind != NULL) {
        _pChip_behind->_pChip_front = NULL;
    }
    _pChip_behind = NULL;

}

void LaserChip::processJudgement() {
    if (isOffScreen()) {
        inactivateTree();
    }
}

void LaserChip::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");

    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "LaserChip::processDrawMain() SetTechnique("<<_technique<<") に失敗しました。");
    //【注意】4/15 メモ
    //奥から描画となるので processDrawXxxx は、同一フレーム内で _pChip_front が必ずしも先に実行されとは限らない。
    //processBehaviorは _pChip_front が必ず先に実行される。
    GgafDx9UntransformedActor::updateWorldMatrix_Mv(this, _matWorld);
    if (_pChip_front != NULL) {
        //前方に連続のチップがある場合
        if (_pChip_front -> _pChip_front == NULL) {
            hr = pID3DXEffect->SetInt(_hKind, 3);
            potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) に失敗しました。1");
        } else {
            if (_pChip_behind == NULL) {
                hr = pID3DXEffect->SetInt(_hKind, 1);
                potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) に失敗しました。1");
            } else {
                hr = pID3DXEffect->SetInt(_hKind, 2);
                potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) に失敗しました。1");
            }
        }
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_pChip_front->_X/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) に失敗しました。1");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_pChip_front->_Y/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) に失敗しました。1");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_pChip_front->_Z/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) に失敗しました。1");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &(_pChip_front->_matWorld));
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) に失敗しました。1");
    } else {
        //前方に連続のチップが無い場合。
        hr = pID3DXEffect->SetInt(_hKind, 4);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) に失敗しました。2");
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_X/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) に失敗しました。2");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_Y/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) に失敗しました。2");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_Z/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) に失敗しました。2");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &_matWorld );
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) に失敗しました。2");
    }

    if (_pChip_behind != NULL) {

    }
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
    potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");

	UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() に失敗しました。");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass("<<pass<<") に失敗しました。");
        _pMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() に失敗しました。");
    }
    hr = pID3DXEffect->End();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() に失敗しました。");

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

void DefaultMeshActor::processDrawTerminate() {}

#endif

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {

}

