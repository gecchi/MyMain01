#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyLaserChip::MyLaserChip(const char* prm_name) :
    GgafDx9MeshActor(prm_name,
                     "X/laser_chip",
                     "X/LaserChipEffect",
                     "LaserChipTechnique",
                     NEW GgafDx9GeometryMover(this),
                     NEW StgChecker(this) ) {
    _pChecker = (StgChecker*)_pGeoChecker;
    _class_name = "MyLaserChip";
    _pChip_prev = NULL;
}

void MyLaserChip::initialize() {
    _hX = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_X" );
    _hY = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Y" );
    _hZ = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Z" );


    _prevX = _X;
    _prevY = _Y;
    _prevZ = _Z;

    _pGeoMover->setMoveVelocity(20*1000);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _pActor_Radical = NULL;
    _SX = 10*1000; _SY=10*1000; _SZ=10*1000;
    _fAlpha = 0.99;
}

void MyLaserChip::processBehavior() {
    if (onChangeToActive()) {
    }
    if (_pChip_prev != NULL) {
        _prevX = _pChip_prev->_X;
        _prevY = _pChip_prev->_Y;
        _prevZ = _pChip_prev->_Z;
    } else {
        _prevX = _X;
        _prevY = _Y;
        _prevZ = _Z;
    }


    //ç¿ïWÇ…îΩâf
    _pGeoMover->behave();

}

void MyLaserChip::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    if (isOffScreen()) {
        inactivateTree();
        _pChip_prev = NULL;
    }
}

void MyLaserChip::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //WORLDïœä∑çsóÒ
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);

    HRESULT hr;
    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "MyLaserChip::processDrawMain() SetTechnique("<<_technique<<") Ç…é∏îsÇµÇ‹ÇµÇΩÅB");



    hr = pID3DXEffect->SetFloat(_hX, 1.0*_prevX/LEN_UNIT/ PX_UNIT);
    potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hX) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    hr = pID3DXEffect->SetFloat(_hY, 1.0*_prevY/LEN_UNIT/ PX_UNIT);
    potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hY) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    hr = pID3DXEffect->SetFloat(_hZ, 1.0*_prevZ/LEN_UNIT/ PX_UNIT);
    potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hZ) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");



    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");


    UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESHADERSTATE );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass("<<pass<<") Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        _pMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    }
    hr = pID3DXEffect->End();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

}

#ifdef OREDEBUG

void MyLaserChip::processDrawTerminate() {
    //ìñÇΩÇËîªíËóÃàÊï\é¶
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    DelineateActor::get()->drawHitarea(_pChecker);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

#else

void DefaultMeshActor::processDrawTerminate() {}

#endif

void MyLaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}


bool MyLaserChip::isOffScreen() {
    if (_X < _X_OffScreenLeft) {
        return true;
    } else {
        if (_X > _X_OffScreenRight) {
            return true;
        } else {
            if (_Y > _Y_OffScreenTop) {
                return true;
            } else {
                if (_Y < _Y_OffScreenBottom) {
                    return true;
                } else {
                    if (_Z < GgafDx9God::_dCamZ * LEN_UNIT * 10) {
                        return true;
                    } else {
                        if (_Z > -1 * GgafDx9God::_dCamZ * LEN_UNIT * 10) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }
    }
}

MyLaserChip::~MyLaserChip() {

}

