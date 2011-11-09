#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxD3DXAniMeshModel::GgafDxD3DXAniMeshModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE("GgafDxD3DXAniMeshModel::GgafDxD3DXAniMeshModel(" << prm_model_name << ")");
    _pAH = NULL;
    _pFR = NULL;
    _pAcBase = NULL;
    _dwNumMaterials = 0L;
    _anim_ticks_per_second = 4800; //restoreD3DXAniMeshModel �ŏ㏑�������ꍇ������B
    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreD3DXAniMeshModel(GgafDxD3DXAniMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
    _Ang = 0.0f;
}

HRESULT GgafDxD3DXAniMeshModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxD3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    HRESULT hr;
    //�ΏۃA�N�^�[
    GgafDxD3DXAniMeshActor* pTargetActor = (GgafDxD3DXAniMeshActor*)prm_pActor_Target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    GgafDxD3DXAniMeshEffect* pD3DXAniMeshEffect = (GgafDxD3DXAniMeshEffect*)prm_pActor_Target->_pEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pD3DXAniMeshEffect->_pID3DXEffect;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxD3DXAniMeshActor::FVF);
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }
    pTargetActor->_pPuppeteer->work(); //�A�j���[�V�������f
    list< D3DXFRAME_WORLD* > *pDrawList = _stackWorldMat.GetDrawList(); // �`�惊�X�g���擾
    list<D3DXFRAME_WORLD*>::iterator it = pDrawList->begin();

    int n = 0;
    //�}�e���A���E�e�N�X�`���̈ꔭ�ڂ��Z�b�g�A
    LPDIRECT3DBASETEXTURE9 pTex = NULL;
    LPDIRECT3DBASETEXTURE9 pLastTex = NULL;
    if (_papTextureCon[n]) {
        pLastTex = _papTextureCon[n]->use()->_pIDirect3DBaseTexture9;
        GgafDxGod::_pID3DDevice9->SetTexture(0, pLastTex);
    } else {
        //������΃e�N�X�`������
        GgafDxGod::_pID3DDevice9->SetTexture(0, NULL);
    }
    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //�`��
        if ((GgafDxEffectManager::_pEffect_Active != pD3DXAniMeshEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDxEffectManager::_pEffect_Active) {
                TRACE4("["<<i<<"],EndPass: /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name);
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pD3DXAniMeshEffect->_begin == true) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pD3DXAniMeshEffect->_begin = true;
            }
#endif

        }
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->WorldTransMatrix));
        checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        if ((*it)->pMeshContainer == NULL) {
            TRACE4("["<<i<<"]�~SetMatrix FrameName="<<((*it)->Name)<<" ��΂��I");
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
                if (n > 0) {
                    pTex = _papTextureCon[n]->use()->_pIDirect3DBaseTexture9;
                    if (pTex != pLastTex) {
                        //�e�N�X�`�����قȂ�ΐݒ�
                        GgafDxGod::_pID3DDevice9->SetTexture(0, pTex);
                        pLastTex = pTex;
                    }
                    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
                    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
                }
                TRACE4("["<<i<<"]["<<j<<"],SetMaterial");
                hr = pID3DXEffect->CommitChanges();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
                (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
                n++;
                GgafGod::_num_actor_drawing++;
            }
        }
    }
    //�O��`�惂�f�������f
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pD3DXAniMeshEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxD3DXAniMeshModel::restore() {
    TRACE3("GgafDxD3DXAniMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreD3DXAniMeshModel(this);
    TRACE3("GgafDxD3DXAniMeshModel::restore() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::onDeviceLost() {
    TRACE3("GgafDxD3DXAniMeshModel::onDeviceLost() " << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    TRACE3("GgafDxD3DXAniMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::release() {
    TRACE3("GgafDxD3DXAniMeshModel::release() " << _model_name << " start");
//    if (_pID3DXAniMesh == NULL) {
//        throwGgafCriticalException("[GgafDxD3DXAniMeshModel::release] Error! _pID3DXAniMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
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
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);
    RELEASE_IMPOSSIBLE_NULL(_pAcBase);
    DELETE_IMPOSSIBLE_NULL(_pAH);
    //TODO:�������́H
    TRACE3("GgafDxD3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDxD3DXAniMeshModel::~GgafDxD3DXAniMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}