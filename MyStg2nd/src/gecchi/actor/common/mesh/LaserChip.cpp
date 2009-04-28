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
    _pRotation = NULL; //LaserChipRotationActor�� new ���ɐݒ肳���B

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
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //���Ԃ̓����蔻��
      _pChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pChecker->getHitAreaBoxs()->disable(1);
    }
}

void LaserChip::onActive() {
    //�o����
    if (_pChip_front == NULL) {
        if (_pRotation->_pSeConnection) {
            _pRotation->_pSeConnection->view()->play();
        }
    }

    _pRotation->_num_chip_active++;
    //���[�U�[�́A�^��������Ԃ����Ȃ̂ŁA�R�R�ōs�������v�Z�񐔂�ߖ�B
    //���dx,dy,dz�����X�V����B
    GgafDx9UntransformedActor::getWorldMatrix_RxRzRyScMv(this, _matWorld);
}

void LaserChip::onInactive() {
    //������
    _pRotation->_num_chip_active--;
    //�O��̌q�����ؒf
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

    //VIEW�ϊ��s��
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) �Ɏ��s���܂����B");

    hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "LaserChip::processDrawMain() SetTechnique("<<_technique<<") �Ɏ��s���܂����B");
    //�y���Ӂz4/15 ����
    //������`��ƂȂ�̂� processDrawXxxx �́A����t���[������ _pChip_front ���K��������Ɏ��s����Ƃ͌���Ȃ��B
    //processBehavior�� _pChip_front ���K����Ɏ��s�����B
    GgafDx9UntransformedActor::updateWorldMatrix_Mv(this, _matWorld);
    if (_pChip_front != NULL) {
        //�O���ɘA���̃`�b�v������ꍇ
        if (_pChip_front -> _pChip_front == NULL) {
            hr = pID3DXEffect->SetInt(_hKind, 3);
            potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) �Ɏ��s���܂����B1");
        } else {
            if (_pChip_behind == NULL) {
                hr = pID3DXEffect->SetInt(_hKind, 1);
                potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) �Ɏ��s���܂����B1");
            } else {
                hr = pID3DXEffect->SetInt(_hKind, 2);
                potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) �Ɏ��s���܂����B1");
            }
        }
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_pChip_front->_X/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_pChip_front->_Y/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_pChip_front->_Z/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) �Ɏ��s���܂����B1");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &(_pChip_front->_matWorld));
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B1");
    } else {
        //�O���ɘA���̃`�b�v�������ꍇ�B
        hr = pID3DXEffect->SetInt(_hKind, 4);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetInt(_hKind) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hX, 1.0*_X/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hX) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hY, 1.0*_Y/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hY) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetFloat(_hZ, 1.0*_Z/LEN_UNIT/ PX_UNIT);
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetFloat(_hZ) �Ɏ��s���܂����B2");
        hr = pID3DXEffect->SetMatrix(_hMatWorld_front, &_matWorld );
        potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(_hMatWorld_front) �Ɏ��s���܂����B2");
    }

    if (_pChip_behind != NULL) {

    }
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
    potentialDx9Exception(hr, D3D_OK, "LaserChip::processDrawMain() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

	UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
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

void LaserChip::processDrawTerminate() {
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

void LaserChip::processOnHit(GgafActor* prm_pActor_Opponent) {
}

LaserChip::~LaserChip() {

}

