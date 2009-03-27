#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9SpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDx9SpriteModel::GgafDx9SpriteModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE3("GgafDx9SpriteModel::GgafDx9SpriteModel(" << _model_name << ")");

    _fSize_SpriteModelWidthPx = 32.0f;
    _fSize_SpriteModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_ani_Max = 0;
    _pIDirect3DVertexBuffer9 = NULL;
    _pTextureCon = NULL;
    _paRectUV = NULL;
    _pRectUV_drawlast = NULL;
    //�f�o�C�C�X���X�g�Ή��̂��߁A�e�N�X�`���A���_�A�}�e���A���̏�������
    //GgafDx9God::_pModelManager->restoreSpriteModel �ōs���Ă���B
}

//�`��
HRESULT GgafDx9SpriteModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE3("GgafDx9SpriteModel::draw("<<prm_pActor_Target->getName()<<")");
    //�Ώ�Actor
    static GgafDx9SpriteActor* pTargetActor;
    pTargetActor = (GgafDx9SpriteActor*)prm_pActor_Target;
    //�Ώ�SpriteActor�̃G�t�F�N�g���b�p
    static GgafDx9SpriteEffect* pSpriteEffect;
    pSpriteEffect = pTargetActor->_pSpriteEffect;
    //�ΏۃG�t�F�N�g
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pSpriteEffect->_pID3DXEffect;

    //����`���UV
    static GgafDx9RectUV* pRectUV_Active;
    pRectUV_Active = _paRectUV + (pTargetActor->_pattno_ani_now);

    static HRESULT hr;

    GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertec_unit);
    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9SpriteModel::FVF);
    GgafDx9God::_pID3DDevice9->SetTexture(0, _pTextureCon->view());
    hr = pID3DXEffect->SetFloat(pSpriteEffect->_hOffsetU, pRectUV_Active->_aUV[0].tu);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9SpriteModel::draw SetFloat(_hOffsetU) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pSpriteEffect->_hOffsetV, pRectUV_Active->_aUV[0].tv);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9SpriteModel::draw SetFloat(_hOffsetV) �Ɏ��s���܂����B");
    //���ݒ�
    hr = pID3DXEffect->SetFloat(pSpriteEffect->_hAlpha, pTargetActor->_fAlpha);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshModel::draw SetValue(g_MaterialAmbient) �Ɏ��s���܂����B");
    hr = pID3DXEffect->CommitChanges();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshModel::draw CommitChanges() �Ɏ��s���܂����B");
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    //�O��`�惂�f�����ۑ�
    GgafDx9ModelManager::_id_lastdraw = _id;
    //�O��`��UV���W�i�ւ̃|�C���^�j��ۑ�
    _pRectUV_drawlast = pRectUV_Active;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9SpriteModel::restore() {
    TRACE3("GgafDx9SpriteModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreSpriteModel(this);
    TRACE3("GgafDx9SpriteModel::restore() " << _model_name << " end");
}

void GgafDx9SpriteModel::onDeviceLost() {
    TRACE3("GgafDx9SpriteModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9SpriteModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9SpriteModel::release() {
    TRACE3("GgafDx9SpriteModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    DELETE_IMPOSSIBLE_NULL(_pD3DMaterial9_default);
    if (_pTextureCon != NULL) {
        _pTextureCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    TRACE3("GgafDx9SpriteModel::release() " << _model_name << " end");
}

GgafDx9SpriteModel::~GgafDx9SpriteModel() {
    TRACE3("GgafDx9SpriteModel::~GgafDx9SpriteModel() " << _model_name << " start");
    release();
}

