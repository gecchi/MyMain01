#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9SpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9SpriteModel::GgafDx9SpriteModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9SpriteModel::GgafDx9SpriteModel(" << _model_name << ")");

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
    TRACE("GgafDx9SpriteModel::draw("<<prm_pActor_Target->getName()<<")");
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

    //if (GgafDx9ModelManager::_id_lastdraw != _id) {
        //�O��`��ƃ��f�����Ⴄ�I
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertec_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9SpriteModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _pTextureCon->view());
    //}
    if (_pRectUV_drawlast != pRectUV_Active) {
        //�O��`��UV�Ⴄ�I
        hr = pID3DXEffect->SetFloat(pSpriteEffect->_hOffsetU, pRectUV_Active->_aUV[0].tu);
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteModel::draw SetFloat(_hOffsetU) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSpriteEffect->_hOffsetV, pRectUV_Active->_aUV[0].tv);
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteModel::draw SetFloat(_hOffsetV) �Ɏ��s���܂����B");
    }
    //���ݒ�
    hr = pID3DXEffect->SetFloat(pSpriteEffect->_hAlpha, pTargetActor->_fAlpha);
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9MeshModel::draw SetValue(g_MaterialAmbient) �Ɏ��s���܂����B");
    hr = pID3DXEffect->CommitChanges();
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9MeshModel::draw CommitChanges() �Ɏ��s���܂����B");
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//
//        //�O��`��UV�Ⴄ�I
////        static VERTEX* paVertexBuffer;
////        hr = _pIDirect3DVertexBuffer9->Lock(0, _size_vertecs, (void**)&paVertexBuffer, 0);
////        paVertexBuffer[0].tu = pRectUV_Active->_aUV[0].tu;
////        paVertexBuffer[0].tv = pRectUV_Active->_aUV[0].tv;
////        paVertexBuffer[1].tu = pRectUV_Active->_aUV[1].tu;
////        paVertexBuffer[1].tv = pRectUV_Active->_aUV[1].tv;
////        paVertexBuffer[2].tu = pRectUV_Active->_aUV[2].tu;
////        paVertexBuffer[2].tv = pRectUV_Active->_aUV[2].tv;
////        paVertexBuffer[3].tu = pRectUV_Active->_aUV[3].tu;
////        paVertexBuffer[3].tv = pRectUV_Active->_aUV[3].tv;
////        //		if (_isChangedAlpha) { //Alpha�ύX������Ȃ���łɂ���B
////        //			paVertexBuffer[0].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
////        //			paVertexBuffer[1].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
////        //			paVertexBuffer[2].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
////        //			paVertexBuffer[3].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
////        //			_isChangedAlpha = false;
////        //		}
////        _pIDirect3DVertexBuffer9->Unlock();
//    } else {
//        //�O��`�惂�f����UV������
//        // �� ��������ł悢�B�����͂₢�ł����`�I(���Ԃ�)
//    }
//    GgafDx9God::_pID3DDevice9->SetMaterial(&(pSpriteActor_Target->_paD3DMaterial9[0]));
//
//    //	if (_isChangedAlpha) {
//    //		//�O��`��UV�������ł�Alpha�ύX�ȏꍇ
//    //		static VERTEX* paVertexBuffer;
//    //		hr = _pIDirect3DVertexBuffer9->Lock(0, _size_vertecs, (void**)&paVertexBuffer, 0);
//    //		if(hr != D3D_OK) {
//    //			throwGgafCriticalException("[GgafDx9SpriteModelManager::draw] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s�Q model="<<_model_name<<"/hr="<<hr);
//    //		}
//    //		paVertexBuffer[0].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//    //		paVertexBuffer[1].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//    //		paVertexBuffer[2].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//    //		paVertexBuffer[3].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//    //		_isChangedAlpha = false;
//    //		_pIDirect3DVertexBuffer9->Unlock();
//    //	}
//
//
//    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE); //���C�g�I�t
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, 0xffffffff);//�A�e�𖳂������ߊ������ō��ɂ���
//    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, GgafDx9God::_dwAmbientBrightness_default);//���������ʂ�
//    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);
//
//    //����2008/10/24 �̔]�݂���
//    //���C�g��؂炸�ɃA���r�G���g�����߂ăX�v���C�g�炵�����ʓI�ȕ\�������邱�Ƃɂ����i�p�x�ɂ���ĉe���łȂ��j�B
//    //���C�g��؂�Ȃ��̂́A�����_�����O�Ń}�e���A���ɂ�郿�u�����h���s���Ƃ���������݂̂��߁B
//    //�������A���C�g��؂��āA���_���Ƃ����������B���̂ق��������y�����ŏ��͒��_���������B
//    //�������A�X�y�L�������˂̃A�j���[�V�����Ƃ�����肽����������Ȃ��B���_�J���[�ŃX�y�L�����ł���H�̂��킩��Ȃ��̂ŁA
//    //�}�e���A�����ł�����悤�ɂ��Ă����B�����͂��낢��������ׂ��B
//    //TODO
//    //2009/1/15 �v���O���}�u���V�F�[�_�[�ɖڊo�߂��B����Ȃ�������

    //�O��`�惂�f�����ۑ�
    GgafDx9ModelManager::_id_lastdraw = _id;
    //�O��`��UV���W�i�ւ̃|�C���^�j��ۑ�
    _pRectUV_drawlast = pRectUV_Active;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9SpriteModel::restore() {
    _TRACE_("GgafDx9SpriteModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreSpriteModel(this);
    _TRACE_("GgafDx9SpriteModel::restore() " << _model_name << " end");
}

void GgafDx9SpriteModel::onDeviceLost() {
    _TRACE_("GgafDx9SpriteModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9SpriteModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9SpriteModel::release() {
    _TRACE_("GgafDx9SpriteModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    DELETE_IMPOSSIBLE_NULL(_pD3DMaterial9_default);
    if (_pTextureCon != NULL) {
        _pTextureCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    _TRACE_("GgafDx9SpriteModel::release() " << _model_name << " end");

}
GgafDx9SpriteModel::~GgafDx9SpriteModel() {
    _TRACE_("GgafDx9SpriteModel::~GgafDx9SpriteModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9SpriteModel::~GgafDx9SpriteModel() " << _model_name << " end");
}

