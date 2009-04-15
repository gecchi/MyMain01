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
    _hMatWorld_front = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_matWorld_front" );

    _pGeoMover->setMoveVelocity(32000);
    _pChecker->useHitAreaBoxNum(2);
    _pChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _pChecker->setHitAreaBox(1, -10000, -10000, -10000, 10000, 10000, 10000);
    setBumpable(true);
    _pActor_Radical = NULL;
    _SX = 30*1000; _SY=30*1000; _SZ=30*1000;
    _fAlpha = 0.9;
}

void MyLaserChip::processBehavior() {
    //���W�ɔ��f
    _pGeoMover->behave();


    //���Ԓn�_�ɂ������蔻��
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pChecker->setHitAreaBox(
                      1,
                      centerX - 10000,
                      centerY - 10000,
                      centerZ - 10000,
                      centerX + 10000,
                      centerY + 10000,
                      centerZ + 10000
                 ); //���Ԃ̓����蔻��
      _pChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pChecker->getHitAreaBoxs()->disable(1);
    }

}

void MyLaserChip::onActive() {
    //�o����
    if (_pChip_front == NULL) {
        _pRotation->_pSeCon_Laser->view()->play();
    }

    _pRotation->_num_chip_active++;
    //���[�U�[�́A�^��������Ԃ����Ȃ̂ŁA�R�R�ōs�������v�Z�񐔂�ߖ�B
    //���dx,dy,dz�����X�V����B
    GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(this, _matWorld);
}

void MyLaserChip::onInactive() {
    //������
    _pRotation->_num_chip_active--;
    //�O��̌q�����ؒf
    _pChip_front = NULL;
    if (_pChip_behind != NULL) {
        _pChip_behind->_pChip_front = NULL;
    }
    _pChip_behind = NULL;

}

void MyLaserChip::processJudgement() {
    if (isOffScreen()) {
        inactivateTree();
    }
}

void MyLaserChip::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;

    HRESULT hr;
    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "MyLaserChip::processDrawMain() SetTechnique("<<_technique<<") �Ɏ��s���܂����B");

    //�y���Ӂz4/15 ����
    //������`��ƂȂ�̂� processDrawXxxx �́A����t���[������ _pChip_front ���K��������Ɏ��s����Ƃ͌���Ȃ��B
    //processBehavior�� _pChip_front ���K����Ɏ��s�����B
    GgafDx9UntransformedActor::updateWorldTransformMv(this, _matWorld);
    if (_pChip_front != NULL && _pChip_front->isActive()) {
        //�O���ɘA���̃`�b�v������ꍇ
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_pChip_front->_X/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hX) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_pChip_front->_Y/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hY) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_pChip_front->_Z/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hZ) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &(_pChip_front->_matWorld));
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B1");
    } else {
        //�O���ɘA���̃`�b�v�������ꍇ�B
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_X/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hX) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_Y/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hY) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_Z/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hZ) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &_matWorld );
        potentialDx9Exception(hr, D3D_OK, "MyLaserChip::processDrawMain() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B2");
    }
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
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
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void DefaultMeshActor::processDrawTerminate() {}

#endif

void MyLaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}


bool MyLaserChip::isOffScreen() {
    if (_X < _X_OffScreenLeft*2) {
        return true;
    } else {
        if (_X > _X_OffScreenRight*2) {
            return true;
        } else {
            if (_Y > _Y_OffScreenTop*2) {
                return true;
            } else {
                if (_Y < _Y_OffScreenBottom*2) {
                    return true;
                } else {
                    if (_Z < GgafDx9God::_dCamZ * LEN_UNIT * 10) {
                        return true;
                    } else {
                        if (_Z > -1 * GgafDx9God::_dCamZ * LEN_UNIT * 30) {
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

