#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXMeshModel::GgafDx9D3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9D3DXMeshModel::GgafDx9D3DXMeshModel(" << prm_model_name << ")");
    _pID3DXMesh = NULL;
    _dwNumMaterials = 0L;
    _dwOptions = prm_dwOptions;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restoreD3DXMeshModel(GgafDx9D3DXMeshModel*)
    //�ōs���Ă���B
}

HRESULT GgafDx9D3DXMeshModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9D3DXMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    GgafDx9D3DXMeshActor* pTargetActor;
    //�ΏۃA�N�^�[
    pTargetActor = (GgafDx9D3DXMeshActor*)prm_pActor_Target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    GgafDx9MeshEffect* pMeshEffect;
    pMeshEffect = pTargetActor->_pMeshEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pMeshEffect->_pID3DXEffect;
    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9D3DXMeshActor::FVF);
    static HRESULT hr;

    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        if (GgafDx9ModelManager::_pModelLastDraw != this || _dwNumMaterials != 1) {
            if (_papTextureCon[i] != NULL) {
                //�e�N�X�`���̃Z�b�g
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[i]->view());
            } else {
                _TRACE_("GgafDx9D3DXMeshModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���Bwhite.png���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            //�}�e���A���̃Z�b�g
            //GgafDx9God::_pID3DDevice9->SetMaterial(&(pTargetActor->_paD3DMaterial9[i]));
            hr = pID3DXEffect->SetValue(pMeshEffect->_hMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[i].Diffuse), sizeof(D3DCOLORVALUE) );
            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() SetValue(g_MaterialDiffuse) �Ɏ��s���܂����B");
        }

        //�`��
        if ((GgafDx9EffectManager::_pEffect_Active != pMeshEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
                TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() End() �Ɏ��s���܂����B");
            }

            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            mightDx9Exception(hr, S_OK, "GgafDx9D3DXMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");
            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");
        } else {
            hr = pID3DXEffect->CommitChanges();
            mightDx9Exception(hr, D3D_OK, "GgafDx9D3DXMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }
        TRACE4("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        hr = _pID3DXMesh->DrawSubset(i);
    }
    //�O��`�惂�f�������f
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pMeshEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

//�V�F�[�_�[�����O
//        if (pTargetActor->_SX == LEN_UNIT &&
//            pTargetActor->_SY == LEN_UNIT &&
//            pTargetActor->_SZ == LEN_UNIT)
//        {
//            hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
//        } else {
//            //�g��k�����Ȃ���Ă��邽�߁A�J������ԂɃg�����X�t�H�[�����ꂽ��Œ��_�@���̐��K������悤�ɐݒ�i���׍��j
//            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//            hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
//            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
//        }


void GgafDx9D3DXMeshModel::restore() {
    TRACE3("GgafDx9D3DXMeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreD3DXMeshModel(this);
    TRACE3("GgafDx9D3DXMeshModel::restore() " << _model_name << " end");
}

void GgafDx9D3DXMeshModel::onDeviceLost() {
    TRACE3("GgafDx9D3DXMeshModel::onDeviceLost() " << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    TRACE3("GgafDx9D3DXMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9D3DXMeshModel::release() {
    TRACE3("GgafDx9D3DXMeshModel::release() " << _model_name << " start");
    if (_pID3DXMesh == NULL) {
        throwGgafCriticalException("[GgafDx9D3DXMeshModel::release] Error! _pID3DXMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
    }
    //�e�N�X�`�������
	if (_papTextureCon) {
		for (DWORD i = 0; i < _dwNumMaterials; i++) {
			if (_papTextureCon[i] != NULL) {
				_papTextureCon[i]->close();
			}
		}
	}
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //�e�N�X�`���̔z��
    RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);

    TRACE3("GgafDx9D3DXMeshModel::release() " << _model_name << " end");
}

GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() {
    TRACE3("GgafDx9D3DXMeshModel::~GgafDx9D3DXMeshModel() " << _model_name << " start");
    release();
}
