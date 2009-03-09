#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXMeshModel::GgafDx9D3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9D3DXMeshModel::GgafDx9D3DXMeshModel(" << prm_model_name << ")");
    _pID3DXMesh = NULL;
    _paD3DMaterial9_default = NULL;
    _papTextureCon = NULL;
    _dwNumMaterials = 0L;
    //_pModel_Next     = NULL;
    //��L�̃v���p�e�B�́AGgafDx9God::_pModelManager->restoreD3DXMeshModel() ����ݒ肳��邱�ƂɂȂ�B
    _dwOptions = prm_dwOptions;
}

HRESULT GgafDx9D3DXMeshModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    static GgafDx9UntransformedActor* pActor_Target;
    //�������ǂ�����ĐU�蕪����GgafDx9D3DXMeshActor �� GgafDx9DynaD3DXMeshActor
    pActor_Target = (GgafDx9UntransformedActor*)prm_pActor_Target;
    static HRESULT hr;


        for (DWORD i = 0; i < _dwNumMaterials; i++) {
            //�}�e���A���̃Z�b�g
            GgafDx9God::_pID3DDevice9->SetMaterial(&(pActor_Target->_paD3DMaterial9[i]));
            if (_papTextureCon[i] != NULL) {
                //�e�N�X�`���̃Z�b�g
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[i]->view());
            } else {
                //������΃e�N�X�`������
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            //�`��
            if (pActor_Target->_SX == LEN_UNIT &&
                pActor_Target->_SY == LEN_UNIT &&
                pActor_Target->_SZ == LEN_UNIT)
            {
                hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
            } else {
                //�g��k�����Ȃ���Ă��邽�߁A�J������ԂɃg�����X�t�H�[�����ꂽ��Œ��_�@���̐��K������悤�ɐݒ�i���׍��j
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
                hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
            }
        }

//    }

    //�O��`�惂�f�������f
    GgafDx9ModelManager::_id_lastdraw = _id;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9D3DXMeshModel::restore() {
    _TRACE_("GgafDx9D3DXMeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreD3DXMeshModel(this);
    _TRACE_("GgafDx9D3DXMeshModel::restore() " << _model_name << " end");
}

void GgafDx9D3DXMeshModel::onDeviceLost() {
    _TRACE_("GgafDx9D3DXMeshModel::onDeviceLost() " << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    _TRACE_("GgafDx9D3DXMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9D3DXMeshModel::release() {
    _TRACE_("GgafDx9D3DXMeshModel::release() " << _model_name << " start");
    if (_pID3DXMesh == NULL) {
        throwGgafCriticalException("[GgafDx9D3DXMeshModel::release] Error! _pID3DXMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
    }
    //�e�N�X�`�������
    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        if (_papTextureCon[i] != NULL) {
            _papTextureCon[i]->close();
        }
    }

    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //�e�N�X�`���̔z��
    RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    _TRACE_("GgafDx9D3DXMeshModel::release() " << _model_name << " end");
}

GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() {
    _TRACE_("GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() " << _model_name << " end");
}
