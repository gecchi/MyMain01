#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyLaserChip::MyLaserChip(const char* prm_name, MyLaserChipRotationActor* prm_pRotation) :
    GgafDx9MeshActor(prm_name,
                     "X/laser_chip",
                     "X/LaserChipEffect",
                     "LaserChipTechnique",
                     NEW GgafDx9GeometryMover(this),
                     NEW StgChecker(this) ) {
    _pChecker = (StgChecker*)_pGeoChecker;
    _class_name = "MyLaserChip";
    _pChip_front = NULL;
    _pChip_behind = NULL;
    _pRotation = prm_pRotation;
}

void MyLaserChip::initialize() {
    _hX = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_X" );
    _hY = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Y" );
    _hZ = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_Z" );


    _prevX = _X;
    _prevY = _Y;
    _prevZ = _Z;

    _pGeoMover->setMoveVelocity(32000);
    //_pGeoMover->setRotAngleVelocity(AXIS_X, 300);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _pActor_Radical = NULL;
    _SX = 3*1000; _SY=3*1000; _SZ=3*1000;
    _fAlpha = 1.0; //���ʂ���̂�
}

void MyLaserChip::processBehavior() {
    if (onChangeToActive()) {
        _pRotation->_num_chip_active++;
    }
    if (_pChip_front != NULL) {
        _prevX = _pChip_front->_X;
        _prevY = _pChip_front->_Y;
        _prevZ = _pChip_front->_Z;
    }


    //���W�ɔ��f
    _pGeoMover->behave();

}

void MyLaserChip::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    if (isOffScreen()) {
        inactivateTree();
        _pRotation->_num_chip_active--;
        _pChip_front = NULL;
		if (_pChip_behind != NULL) {
			_pChip_behind->_pChip_front = NULL;
		}
        _pChip_behind = NULL;
    }
}

void MyLaserChip::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //WORLD�ϊ��s��
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, matWorld);

    HRESULT hr;
    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "MyLaserChip::processDrawMain() SetTechnique("<<_technique<<") �Ɏ��s���܂����B");


    if (_pChip_front != NULL) {
		//_TRACE_("_pChip_front=("<<_prevX<<","<<_prevY<<","<<_prevZ<<")");
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_prevX/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hX) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_prevY/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hY) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_prevZ/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hZ) �Ɏ��s���܂����B1");
    } else {
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_X/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hX) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_Y/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hY) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_Z/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hZ) �Ɏ��s���܂����B2");

    }


    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

    UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE | D3DXFX_DONOTSAVESHADERSTATE );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() Begin() �Ɏ��s���܂����B");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() BeginPass("<<pass<<") �Ɏ��s���܂����B");
        _pMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() EndPass() �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->End();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() End() �Ɏ��s���܂����B");

}

#ifdef OREDEBUG

void MyLaserChip::processDrawTerminate() {
    //�����蔻��̈�\��
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

