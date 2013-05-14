#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxD3DXMeshModel::GgafDxD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions) : GgafDxModel(prm_model_name) {
    TRACE("GgafDxD3DXMeshModel::GgafDxD3DXMeshModel(" << prm_model_name << ")");
    _pID3DXMesh = nullptr;
    _num_materials = 0L;
    _dwOptions = prm_dwOptions;
    _obj_model |= Obj_GgafDxD3DXMeshModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreD3DXMeshModel(GgafDxD3DXMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

HRESULT GgafDxD3DXMeshModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxD3DXMeshModel::draw("<<prm_pActor_Target->getName()<<")");

    //�ΏۃA�N�^�[
    GgafDxD3DXMeshActor* pTargetActor = (GgafDxD3DXMeshActor*)prm_pActor_Target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    GgafDxMeshEffect* pMeshEffect = (GgafDxMeshEffect*)prm_pActor_Target->_pEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pMeshEffect->_pID3DXEffect;

    GgafDxGod::_pID3DDevice9->SetFVF(GgafDxD3DXMeshActor::FVF);
    HRESULT hr;

    for (DWORD i = 0; i < _num_materials; i++) {
        if (GgafDxModelManager::_pModelLastDraw != this || _num_materials != 1) {
            if (_papTextureConnection[i]) {
                //�e�N�X�`���̃Z�b�g
                GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureConnection[i]->peek()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxD3DXMeshModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                GgafDxGod::_pID3DDevice9->SetTexture(0, nullptr);
            }
            //�}�e���A���̃Z�b�g
            hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[i].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");


            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
        }

        //�`��
        if ((GgafDxEffectManager::_pEffect_Active != pMeshEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDxEffectManager::_pEffect_Active) {
                TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif
            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxD3DXMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMeshEffect->_begin) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxD3DXMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }
        TRACE4("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        hr = _pID3DXMesh->DrawSubset(i);  //�Ȃ�ĕ֗��ȃ��\�b�h�B
        GgafGod::_num_actor_drawing++;
    }
    //�O��`�惂�f�������f
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pMeshEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;

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
//            GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//            hr = _pID3DXMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
//            GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
//        }


void GgafDxD3DXMeshModel::restore() {
    TRACE3("GgafDxD3DXMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreD3DXMeshModel(this);
    TRACE3("GgafDxD3DXMeshModel::restore() " << _model_name << " end");
}

void GgafDxD3DXMeshModel::onDeviceLost() {
    TRACE3("GgafDxD3DXMeshModel::onDeviceLost() " << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    TRACE3("GgafDxD3DXMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxD3DXMeshModel::release() {
    TRACE3("GgafDxD3DXMeshModel::release() " << _model_name << " start");
    if (_pID3DXMesh == nullptr) {
        _TRACE_("���x���� [GgafDxD3DXMeshModel::release()]  "<<_model_name<<" �� _pID3DXMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
    }
    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                TRACE3("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //�e�N�X�`���̔z��
    GGAF_RELEASE(_pID3DXMesh);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);

    TRACE3("GgafDxD3DXMeshModel::release() " << _model_name << " end");
}

GgafDxD3DXMeshModel::~GgafDxD3DXMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}
