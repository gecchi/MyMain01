#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshModel::GgafDx9MeshModel(char* prm_model_name, DWORD prm_dwOptions) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9MeshModel::GgafDx9MeshModel(" << prm_model_name << ")");
    _pID3DXMesh = NULL;
    _paD3DMaterial9_default = NULL;
    _papTexture = NULL;
    _dwNumMaterials = 0L;
    //_pModel_Next     = NULL;
    //��L�̃v���p�e�B�́AGgafDx9God::_pModelManager->restoreMeshModel() ����ݒ肳��邱�ƂɂȂ�B
    _dwOptions = prm_dwOptions;
}

HRESULT GgafDx9MeshModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    static GgafDx9UntransformedActor* pMeshActor_Target;
    //�������ǂ�����ĐU�蕪����GgafDx9MeshActor �� GgafDx9DynaMeshActor
    pMeshActor_Target = (GgafDx9UntransformedActor*)prm_pActor_Target;
    static HRESULT hr;
    if (pMeshActor_Target->_pID3DXEffect != NULL) {
        pMeshActor_Target->_pID3DXEffect->SetTechnique( "BasicTec" );
        UINT numPass;
        pMeshActor_Target->_pID3DXEffect->Begin( &numPass, 0 );
        pMeshActor_Target->_pID3DXEffect->BeginPass( 0 );

        static D3DXMATRIX matrixTransWorld; //WORLD�ϊ��s��
        static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
        static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
        static float sx, sy, sz;
        sinRX = GgafDx9Util::SIN[pMeshActor_Target->_RX / ANGLE_RATE];
        cosRX = GgafDx9Util::COS[pMeshActor_Target->_RX / ANGLE_RATE];
        sinRY = GgafDx9Util::SIN[pMeshActor_Target->_RY / ANGLE_RATE];
        cosRY = GgafDx9Util::COS[pMeshActor_Target->_RY / ANGLE_RATE];
        sinRZ = GgafDx9Util::SIN[pMeshActor_Target->_RZ / ANGLE_RATE];
        cosRZ = GgafDx9Util::COS[pMeshActor_Target->_RZ / ANGLE_RATE];
        sx = pMeshActor_Target->_SX / fRateScale;
        sy = pMeshActor_Target->_SY / fRateScale;
        sz = pMeshActor_Target->_SZ / fRateScale;

        matrixTransWorld._11 = cosRZ * cosRY * sx;
        matrixTransWorld._12 = sinRZ * sy;
        matrixTransWorld._13 = cosRZ * -sinRY * sz;
        matrixTransWorld._14 = 0.0f;

        matrixTransWorld._21 = ((cosRX * -sinRZ * cosRY) + (sinRX * sinRY)) * sx;
        matrixTransWorld._22 = cosRX * cosRZ * sy;
        matrixTransWorld._23 = ((cosRX * -sinRZ * -sinRY) + (sinRX * cosRY)) * sz;
        matrixTransWorld._24 = 0.0f;

        matrixTransWorld._31 = ((-sinRX * -sinRZ * cosRY) + (cosRX * sinRY)) * sx;
        matrixTransWorld._32 = -sinRX * cosRZ * sy;
        matrixTransWorld._33 = ((-sinRX * -sinRZ * -sinRY) + (cosRX * cosRY)) * sz;
        matrixTransWorld._34 = 0.0f;

        matrixTransWorld._41 = (float)(1.0 * pMeshActor_Target->_X / LEN_UNIT / PX_UNIT);
        matrixTransWorld._42 = (float)(1.0 * pMeshActor_Target->_Y / LEN_UNIT / PX_UNIT);
        matrixTransWorld._43 = (float)(1.0 * pMeshActor_Target->_Z / LEN_UNIT / PX_UNIT);
        matrixTransWorld._44 = 1.0f;

        pMeshActor_Target->_pID3DXEffect->SetMatrix( "g_worldMat", &matrixTransWorld );















        for (DWORD i = 0; i < _dwNumMaterials; i++) {
            //�}�e���A���̃Z�b�g
            GgafDx9God::_pID3DDevice9->SetMaterial(&(pMeshActor_Target->_paD3DMaterial9[i]));
            if (_papTexture[i] != NULL) {
                //�e�N�X�`���̃Z�b�g
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTexture[i]->getResource());
            } else {
                //������΃e�N�X�`������
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            //�`��
            if (pMeshActor_Target->_SX == LEN_UNIT &&
                pMeshActor_Target->_SY == LEN_UNIT &&
                pMeshActor_Target->_SZ == LEN_UNIT)
            {
                hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
            } else {
                //�g��k�����Ȃ���Ă��邽�߁A�J������ԂɃg�����X�t�H�[�����ꂽ��Œ��_�@���̐��K������悤�ɐݒ�i���׍��j
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
                hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
            }
        }
        pMeshActor_Target->_pID3DXEffect->EndPass();
        pMeshActor_Target->_pID3DXEffect->End();

    } else {

        for (DWORD i = 0; i < _dwNumMaterials; i++) {
            //�}�e���A���̃Z�b�g
            GgafDx9God::_pID3DDevice9->SetMaterial(&(pMeshActor_Target->_paD3DMaterial9[i]));
            if (_papTexture[i] != NULL) {
                //�e�N�X�`���̃Z�b�g
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTexture[i]->getResource());
            } else {
                //������΃e�N�X�`������
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            //�`��
            if (pMeshActor_Target->_SX == LEN_UNIT &&
                pMeshActor_Target->_SY == LEN_UNIT &&
                pMeshActor_Target->_SZ == LEN_UNIT)
            {
                hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
            } else {
                //�g��k�����Ȃ���Ă��邽�߁A�J������ԂɃg�����X�t�H�[�����ꂽ��Œ��_�@���̐��K������悤�ɐݒ�i���׍��j
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
                hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
            }
        }
    }

    //�O��`�惂�f�������f
    GgafDx9God::_pModelManager->_id_lastdraw = _id;
    GgafGod::_iNumPlayingActor++;
    return D3D_OK;
}

void GgafDx9MeshModel::restore() {
    _TRACE_("GgafDx9MeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreMeshModel(this);
    _TRACE_("GgafDx9MeshModel::restore() " << _model_name << " end");
}

void GgafDx9MeshModel::onDeviceLost() {
    _TRACE_("GgafDx9MeshModel::onDeviceLost() " << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    _TRACE_("GgafDx9MeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9MeshModel::release() {
    _TRACE_("GgafDx9MeshModel::release() " << _model_name << " start");
    if (_pID3DXMesh == NULL) {
        throwGgafCriticalException("[GgafDx9MeshModel::release] Error! _pID3DXMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
    }
    //�e�N�X�`����������邩�ǂ���
    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        //GgafDx9ModelManager::_pTextureManager->releaseResourceLead(_papTexture[i]);
        RELEASE_SAFETY(_papTexture[i]);
    }

    DELETEARR_IMPOSSIBLE_NULL(_papTexture); //�e�N�X�`���̔z��
    RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    _TRACE_("GgafDx9MeshModel::release() " << _model_name << " end");
}

GgafDx9MeshModel::~GgafDx9MeshModel() {
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " << _model_name << " end");
}
