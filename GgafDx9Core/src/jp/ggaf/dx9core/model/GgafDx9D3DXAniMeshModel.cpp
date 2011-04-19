#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXAniMeshModel::GgafDx9D3DXAniMeshModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9D3DXAniMeshModel::GgafDx9D3DXAniMeshModel(" << prm_model_name << ")");
    _pFR = NULL;
    _pAcBase = NULL;
    _dwNumMaterials = 0L;
    _anim_ticks_per_second = 4800; //restoreD3DXAniMeshModel �ŏ㏑�������ꍇ������B
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restoreD3DXAniMeshModel(GgafDx9D3DXAniMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _Ang = 0.0f;
}

HRESULT GgafDx9D3DXAniMeshModel::draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDx9D3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    HRESULT hr;
    //�ΏۃA�N�^�[
    GgafDx9D3DXAniMeshActor* pTargetActor = (GgafDx9D3DXAniMeshActor*)prm_pActor_Target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    GgafDx9D3DXAniMeshEffect* pD3DXAniMeshEffect = (GgafDx9D3DXAniMeshEffect*)prm_pActor_Target->_pGgafDx9Effect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pD3DXAniMeshEffect->_pID3DXEffect;
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9D3DXAniMeshActor::FVF);
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_power, _fPowerBlink);
        checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_threshold, _fBlinkThreshold);
        checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }
    pTargetActor->_pPuppeteer->work(); //�A�j���[�V�������f
    list< D3DXFRAME_WORLD* > *pDrawList = _stackWorldMat.GetDrawList(); // �`�惊�X�g���擾
    list<D3DXFRAME_WORLD*>::iterator it = pDrawList->begin();

    int n = 0;
    //�}�e���A���E�e�N�X�`���̈ꔭ�ڂ��Z�b�g�A
    LPDIRECT3DBASETEXTURE9 pTex = NULL;
    LPDIRECT3DBASETEXTURE9 pLastTex = NULL;
    if (_papTextureCon[n]) {
        pLastTex = _papTextureCon[n]->refer()->_pIDirect3DBaseTexture9;
        GgafDx9God::_pID3DDevice9->SetTexture(0, pLastTex);
    } else {
        //������΃e�N�X�`������
        GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
    }
    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[n].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //�`��
        if ((GgafDx9EffectManager::_pEffect_Active != pD3DXAniMeshEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDx9EffectManager::_pEffect_Active) {
                TRACE4("["<<i<<"],EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDx9EffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pD3DXAniMeshEffect->_begin == true) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pD3DXAniMeshEffect->_begin = true;
            }
#endif

        }
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->WorldTransMatrix));
        checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        if ((*it)->pMeshContainer == NULL) {
            TRACE4("["<<i<<"]�~SetMatrix FrameName="<<((*it)->Name)<<" ��΂��I");
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
                if (n > 0) {
                    pTex = _papTextureCon[n]->refer()->_pIDirect3DBaseTexture9;
                    if (pTex != pLastTex) {
                        //�e�N�X�`�����قȂ�ΐݒ�
                        GgafDx9God::_pID3DDevice9->SetTexture(0, pTex);
                        pLastTex = pTex;
                    }
                    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[n].Diffuse), sizeof(D3DCOLORVALUE) );
                    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
                }
                TRACE4("["<<i<<"]["<<j<<"],SetMaterial");
                hr = pID3DXEffect->CommitChanges();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
                (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
                n++;
                GgafGod::_num_actor_drawing++;
            }
        }
    }
    //�O��`�惂�f�������f
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pD3DXAniMeshEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDx9D3DXAniMeshModel::restore() {
    TRACE3("GgafDx9D3DXAniMeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreD3DXAniMeshModel(this);
    TRACE3("GgafDx9D3DXAniMeshModel::restore() " << _model_name << " end");
}

void GgafDx9D3DXAniMeshModel::onDeviceLost() {
    TRACE3("GgafDx9D3DXAniMeshModel::onDeviceLost() " << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    TRACE3("GgafDx9D3DXAniMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9D3DXAniMeshModel::release() {
    TRACE3("GgafDx9D3DXAniMeshModel::release() " << _model_name << " start");
//    if (_pID3DXAniMesh == NULL) {
//        throwGgafCriticalException("[GgafDx9D3DXAniMeshModel::release] Error! _pID3DXAniMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
//    }
    if (_papTextureCon) {
        for (int i = 0; i < (int)_dwNumMaterials; i++) {
            if (_papTextureCon[i]) {
                TRACE3("close() _papTextureCon["<<i<<"]->"<<(_papTextureCon[i]->getIdStr()));
                _papTextureCon[i]->close();
            }
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //�e�N�X�`���̔z��
//    RELEASE_IMPOSSIBLE_NULL(_pID3DXAniMesh);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    RELEASE_IMPOSSIBLE_NULL(_pAcBase);
    DELETE_IMPOSSIBLE_NULL(_pAH);
    //TODO:�������́H
    TRACE3("GgafDx9D3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDx9D3DXAniMeshModel::~GgafDx9D3DXAniMeshModel() {
    //release();
    //��GgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) �ŌĂяo�����
}
