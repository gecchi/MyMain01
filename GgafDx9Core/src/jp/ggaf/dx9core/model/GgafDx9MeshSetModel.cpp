#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9MeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9MeshSetModel::GgafDx9MeshSetModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE3("GgafDx9MeshSetModel::GgafDx9MeshSetModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;

    _setnum = 6;
    _paIDirect3DVertexBuffer9 = NULL;
    _paIDirect3DIndexBuffer9 = NULL;
    _pa_nMaterialListGrp = NULL;
    _papaVtxBuffer_org = NULL;
    _papaIdxBuffer_org = NULL;
    _papaIndexParam = NULL;
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshSetModel*)
    //�ōs���Ă���B
}

//�`��
HRESULT GgafDx9MeshSetModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE3("GgafDx9MeshSetModel::draw("<<prm_pActor_Target->getName()<<")");
    //�ΏۃA�N�^�[
    static GgafDx9MeshSetActor* pTargetActor;
    pTargetActor = (GgafDx9MeshSetActor*)prm_pActor_Target;
    //�Ώ�MeshSetActor�̃G�t�F�N�g���b�p
    static GgafDx9MeshSetEffect* pMeshSetEffect;
    pMeshSetEffect = pTargetActor->_pMeshSetEffect;
    //�ΏۃG�t�F�N�g
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

	HRESULT hr;
    UINT material_no;
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _paIDirect3DVertexBuffer9[0],  0, _size_vertec_unit * 1);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9MeshSetModel::FVF);
        GgafDx9God::_pID3DDevice9->SetIndices(_paIDirect3DIndexBuffer9[0]);
    }

    //�`��
    for (UINT i = 0; i < _pa_nMaterialListGrp[0]; i++) {
        if (GgafDx9ModelManager::_pModelLastDraw != this || _pa_nMaterialListGrp[0] != 1) {
            material_no = _papaIndexParam[0][i].MaterialNo;
            if (_papTextureCon[material_no] != NULL) {
                //�e�N�X�`����s0���W�X�^�ɃZ�b�g
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->view());
            } else {
                _TRACE_("GgafDx9MeshSetModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���Bwhite.png���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            hr = pID3DXEffect->SetValue(pMeshSetEffect->_hMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
            mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_MaterialDiffuse) �Ɏ��s���܂����B");
        }


        if (GgafDx9EffectManager::_pEffect_Active != pMeshSetEffect) {
            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
                TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() End() �Ɏ��s���܂����B");
            }

            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            mightDx9Exception(hr, S_OK, "GgafDx9MeshSetModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");
            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() BeginPass(0) �Ɏ��s���܂����B");
        } else {
            hr = pID3DXEffect->CommitChanges();
            mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }
        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _papaIndexParam[0][i].BaseVertexIndex,
                                                        _papaIndexParam[0][i].MinIndex,
                                                        _papaIndexParam[0][i].NumVertices,
                                                        _papaIndexParam[0][i].StartIndex,
                                                        _papaIndexParam[0][i].PrimitiveCount);
    }
//    if (_nMaterialListGrp > 0) {
        GgafDx9ModelManager::_pModelLastDraw = this;
        GgafDx9EffectManager::_pEffect_Active = pMeshSetEffect;
        GgafGod::_num_actor_playing++;
//    }
    return D3D_OK;
}

void GgafDx9MeshSetModel::restore() {
    TRACE3("GgafDx9MeshSetModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreMeshSetModel(this);
    TRACE3("GgafDx9MeshSetModel::restore() " << _model_name << " end");
}

void GgafDx9MeshSetModel::onDeviceLost() {
    TRACE3("GgafDx9MeshSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9MeshSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9MeshSetModel::release() {
    TRACE3("GgafDx9MeshSetModel::release() " << _model_name << " start");

    //�e�N�X�`�������
	for (DWORD i = 0; i < _dwNumMaterials; i++) {
		if (_papTextureCon[i] != NULL) {
			_papTextureCon[i]->close();
		}
	}
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //�e�N�X�`���̔z��
    for (int i = 0; i < _setnum; i++) {
        RELEASE_IMPOSSIBLE_NULL(_paIDirect3DVertexBuffer9[i]);
        RELEASE_IMPOSSIBLE_NULL(_paIDirect3DIndexBuffer9[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_paIDirect3DVertexBuffer9);
    DELETEARR_IMPOSSIBLE_NULL(_paIDirect3DIndexBuffer9);

    for (int i = 0; i < _setnum; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaVtxBuffer_org[i]);
        DELETEARR_IMPOSSIBLE_NULL(_papaIdxBuffer_org[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaVtxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_papaIdxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_pa_nMaterialListGrp);
    DELETE_IMPOSSIBLE_NULL(_pModel3D);
	//_pMeshesFront �� _pModel3D ��DELETE���Ă���̂ł���K�v�͖���
    _pMeshesFront = NULL;
    for (int i = 0; i < _setnum; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaIndexParam[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaIndexParam);
    TRACE3("GgafDx9MeshSetModel::release() " << _model_name << " end");

}
GgafDx9MeshSetModel::~GgafDx9MeshSetModel() {
    TRACE3("GgafDx9MeshSetModel::~GgafDx9MeshSetModel() " << _model_name << " start");
    release();
}

