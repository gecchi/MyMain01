#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9PrimitiveModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9PrimitiveModel::GgafDx9PrimitiveModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9PrimitiveModel::GgafDx9PrimitiveModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;

    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _papTextureCon = NULL;
    _paIndexParam = NULL;
    //�f�o�C�C�X���X�g�Ή��̂��߁A�e�N�X�`���A���_�A�}�e���A���̏�������
    //GgafDx9God::_pModelManager->restorePrimitiveModel �ōs���Ă���B
}

//�`��
HRESULT GgafDx9PrimitiveModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    _TRACE_("GgafDx9PrimitiveModel::draw("<<prm_pActor_Target->getName()<<")");
    GgafDx9PrimitiveActor* pTargetActor = (GgafDx9PrimitiveActor*)prm_pActor_Target;

    _TRACE_("chk1");
    GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertec_unit);
    _TRACE_("chk2");
    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9PrimitiveModel::FVF);
    _TRACE_("chk3");
    GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);
    _TRACE_("chk4");
    for (int i = 0; i < _nMaterialListGrp; i++) {
        _TRACE_("chk5");
        int mno = _paIndexParam[i].MaterialNo;
        _TRACE_("chk6");
        GgafDx9God::_pID3DDevice9->SetMaterial(&(pTargetActor->_paD3DMaterial9[mno]));
        _TRACE_("chk7");
        if (_papTextureCon[mno] != NULL) {
            //�e�N�X�`���̃Z�b�g
            _TRACE_("chk8");
            GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[mno]->view());
            _TRACE_("chk9");
        } else {
            //������΃e�N�X�`������
            _TRACE_("chk10");
            GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            _TRACE_("chk11");
        }
        _TRACE_("chk12");
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
        _TRACE_("chk13");
    }

    GgafDx9God::_pModelManager->_id_lastdraw = _id;
    GgafGod::_num_actor_playing++;
//    //�Ώ�PrimitiveActor
//    GgafDx9PrimitiveActor* pPrimitiveActor_Target = (GgafDx9PrimitiveActor*)prm_pActor_Target;
//    //����`���UV
//    GgafDx9RectUV* pRectUV_Active = _paRectUV + (pPrimitiveActor_Target->_pattno_ani_now);
//
//    static HRESULT hr;
//
//    if (GgafDx9God::_pModelManager->_id_lastdraw != _id) {
//        //�O��`��ƃ��f�����Ⴄ�I
//        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertec_unit);
//        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9PrimitiveModel::FVF);
//        GgafDx9God::_pID3DDevice9->SetTexture(0, _pTextureCon->view());
//    }
//
//    GgafDx9God::_pID3DDevice9->SetMaterial(&(pPrimitiveActor_Target->_paD3DMaterial9[0]));
//
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, 0xffffffff);//�A�e�𖳂������ߊ������ō��ɂ���
//    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, GgafDx9God::_dwAmbientBrightness_default);//���������ʂ�
//    //�O��`�惂�f�����ۑ�
//    GgafDx9God::_pModelManager->_id_lastdraw = _id;
//    //�O��`��UV���W�i�ւ̃|�C���^�j��ۑ�
//    _pRectUV_drawlast = pRectUV_Active;
//    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9PrimitiveModel::restore() {
    _TRACE_("GgafDx9PrimitiveModel::restore() " << _model_name << " start");
//    GgafDx9God::_pModelManager->restorePrimitiveModel(this);
    _TRACE_("GgafDx9PrimitiveModel::restore() " << _model_name << " end");
}

void GgafDx9PrimitiveModel::onDeviceLost() {
    _TRACE_("GgafDx9PrimitiveModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9PrimitiveModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9PrimitiveModel::release() {
    _TRACE_("GgafDx9PrimitiveModel::release() " << _model_name << " start");

    //�e�N�X�`�������
    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        if (_papTextureCon[i] != NULL) {
            _papTextureCon[i]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //�e�N�X�`���̔z��

    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);

    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    DELETEARR_IMPOSSIBLE_NULL(_paVtxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_paIdxBuffer_org);
    DELETE_IMPOSSIBLE_NULL(_pModel3D);
    DELETE_POSSIBLE_NULL(_pMeshesFront);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    _TRACE_("GgafDx9PrimitiveModel::release() " << _model_name << " end");

}
GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() {
    _TRACE_("GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() " << _model_name << " end");
}

