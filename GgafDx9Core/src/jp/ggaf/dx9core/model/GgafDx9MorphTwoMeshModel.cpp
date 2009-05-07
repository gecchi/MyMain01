#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

//DWORD GgafDx9MorphTwoMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9MorphTwoMeshModel::GgafDx9MorphTwoMeshModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE3("GgafDx9MorphTwoMeshModel::GgafDx9MorphTwoMeshModel(" << _model_name << ")");
    _paModel3D = NULL;
    _paMeshesFront = NULL;

    _paIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DVertexDeclaration9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paD3DMaterial9_default = NULL;
    _papaVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _papTextureCon = NULL;
    _paIndexParam = NULL;
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restoreMeshModel(GgafDx9MorphTwoMeshModel*)
    //�ōs���Ă���B
}

//�`��
HRESULT GgafDx9MorphTwoMeshModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE3("GgafDx9MorphTwoMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    //�ΏۃA�N�^�[
    static GgafDx9MeshActor* pTargetActor;
    pTargetActor = (GgafDx9MeshActor*)prm_pActor_Target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    static GgafDx9MeshEffect* pMeshEffect;
    pMeshEffect = pTargetActor->_pMeshEffect;
    //�ΏۃG�t�F�N�g
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pMeshEffect->_pID3DXEffect;

	HRESULT hr;
    UINT material_no;
    //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
    GgafDx9God::_pID3DDevice9->SetVertexDeclaration( _pIDirect3DVertexDeclaration9);
    GgafDx9God::_pID3DDevice9->SetStreamSource(0, _paIDirect3DVertexBuffer9[0],  0, _size_vertec_unit);
    GgafDx9God::_pID3DDevice9->SetStreamSource(1, _paIDirect3DVertexBuffer9[1],  0, sizeof(float)*(3+3));
    //GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9MorphTwoMeshModel::FVF);
    GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

    //�`��
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (_papTextureCon[material_no] != NULL) {
            //�e�N�X�`����s0���W�X�^�ɃZ�b�g
            GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->view());
        } else {
            _TRACE_("GgafDx9MorphTwoMeshModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���Bwhite.png���ݒ肳���ׂ��ł��B���������ł�");
            //������΃e�N�X�`������
            GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_hMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshModel::draw SetValue(g_MaterialDiffuse) �Ɏ��s���܂����B");
        hr = pID3DXEffect->CommitChanges();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshModel::draw CommitChanges() �Ɏ��s���܂����B");
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
    }
    GgafDx9ModelManager::_id_lastdraw = _id;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9MorphTwoMeshModel::restore() {
    TRACE3("GgafDx9MorphTwoMeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreMorphTwoMeshModel(this);
    TRACE3("GgafDx9MorphTwoMeshModel::restore() " << _model_name << " end");
}

void GgafDx9MorphTwoMeshModel::onDeviceLost() {
    TRACE3("GgafDx9MorphTwoMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9MorphTwoMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9MorphTwoMeshModel::release() {
    TRACE3("GgafDx9MorphTwoMeshModel::release() " << _model_name << " start");

    //�e�N�X�`�������
    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        if (_papTextureCon[i] != NULL) {
            _papTextureCon[i]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //�e�N�X�`���̔z��

    for (int i = 0; i < 2; i++) {
        RELEASE_IMPOSSIBLE_NULL(_paIDirect3DVertexBuffer9[i]);
        DELETEARR_IMPOSSIBLE_NULL(_papaVtxBuffer_org[i]);
        DELETE_IMPOSSIBLE_NULL(_paModel3D[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_paIDirect3DVertexBuffer9);
    DELETEARR_IMPOSSIBLE_NULL(_papaVtxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_paModel3D);

	//_paMeshesFront[0],_paMeshesFront[1] �� _paModel3D ��DELETE���Ă���̂ł���K�v�͖���
    DELETEARR_IMPOSSIBLE_NULL(_paMeshesFront);
    _paMeshesFront = NULL;


    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    DELETEARR_IMPOSSIBLE_NULL(_paIdxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    TRACE3("GgafDx9MorphTwoMeshModel::release() " << _model_name << " end");

}
GgafDx9MorphTwoMeshModel::~GgafDx9MorphTwoMeshModel() {
    TRACE3("GgafDx9MorphTwoMeshModel::~GgafDx9MorphTwoMeshModel() " << _model_name << " start");
    release();
}

