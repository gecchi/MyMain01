#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9D3DXAniMeshModel::GgafDx9D3DXAniMeshModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9D3DXAniMeshModel::GgafDx9D3DXAniMeshModel(" << prm_model_name << ")");
    _pFR = NULL;
    _pAC = NULL;
    _dwNumMaterials = 0L;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDx9ModelManager::restoreD3DXAniMeshModel(GgafDx9D3DXAniMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB

    _Ang = 0.0f;
}

HRESULT GgafDx9D3DXAniMeshModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9D3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<")");
    GgafDx9D3DXAniMeshActor* pTargetActor;
    //�ΏۃA�N�^�[
    pTargetActor = (GgafDx9D3DXAniMeshActor*)prm_pActor_Target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    GgafDx9D3DXAniMeshEffect* pD3DXAniMeshEffect;
    pD3DXAniMeshEffect = pTargetActor->_pD3DXAniMeshEffect;
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pD3DXAniMeshEffect->_pID3DXEffect;
    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9D3DXAniMeshActor::FVF);
    static HRESULT hr;



    checkDxException(hr, S_OK, "GgafDx9D3DXAniMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_power, _fPowerBlink);
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_threshold, _fBlinkThreshold);
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    //_Ang += 0.004f;


    // �A�j���[�V�������t���[�����i�߂�
    _pAC->AdvanceTime(_advanceTimePerFrame, NULL );


    //���[���h�ϊ��s��X�^�b�N�ɂ�郏�[���h�ϊ��s��̌v�Z
    D3DXMATRIX WorldMat;
    D3DXMatrixIdentity(&WorldMat);
    //D3DXMatrixRotationYawPitchRoll(&Rot, _Ang, _Ang / 2.37f, 0);
    //D3DXMatrixMultiply(&WorldMat, &WorldMat, &Rot);
    //&(pTargetActor->_matWorld)


    WTMStack.SetWorldMatrix(&WorldMat);
    // �t���[���̃��[���h�ϊ��s����v�Z
    WTMStack.UpdateFrame(_pFR);

    list< D3DXFRAME_WORLD* > *pDrawList;
    pDrawList = WTMStack.GetDrawList(); // �`�惊�X�g���擾

    list<D3DXFRAME_WORLD*>::iterator it = pDrawList->begin();
    int materialnum;


    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //�`��
        if ((GgafDx9EffectManager::_pEffect_Active != pD3DXAniMeshEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
                TRACE4("["<<i<<"],EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() End() �Ɏ��s���܂����B");
            }

            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");
        }

        //GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_WORLD, &(*it)->WorldTransMatrix); // ���[���h�ϊ��s���ݒ�
        //_TRACE_("["<<i<<"]��SetMatrix FrameName="<<((*it)->Name)<<" �`��I");

        D3DXMatrixMultiply(&WorldMat, &((*it)->WorldTransMatrix), &(pTargetActor->_matWorld));

//        _TRACE_("(*it)->WorldTransMatrix=");
//        putMat(&((*it)->WorldTransMatrix));
//        _TRACE_("pTargetActor->_matWorld=");
//        putMat(&(pTargetActor->_matWorld));
//        _TRACE_("WorldMat=");
//        putMat(&WorldMat);
        //hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->WorldTransMatrix));
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &WorldMat);
        checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");




        //hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_h_matWorld, &_matWorld );
            //checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        if ((*it)->pMeshContainer == NULL) {
            TRACE4("["<<i<<"]�~SetMatrix FrameName="<<((*it)->Name)<<" ��΂��I");
            continue;
        } else {

            materialnum = (*it)->pMeshContainer->NumMaterials;
            for (int j = 0; j < materialnum; j++) {
                TRACE4("["<<i<<"]["<<j<<"],SetMaterial");
                //GgafDx9God::_pID3DDevice9->SetMaterial(&(*it)->pMeshContainer->pMaterials[j].MatD3D);

                hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &((*it)->pMeshContainer->pMaterials[j].MatD3D.Diffuse), sizeof(D3DCOLORVALUE) );
                checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

                hr = pID3DXEffect->CommitChanges();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDx9D3DXAniMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");

                (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
            }
        }
    }

//
//
//
//    for (DWORD i = 0; i < _dwNumMaterials; i++) {
//        if (GgafDx9ModelManager::_pModelLastDraw != this || _dwNumMaterials != 1) {
//            if (_papTextureCon[i] != NULL) {
//                //�e�N�X�`���̃Z�b�g
//                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[i]->refer()->_pIDirect3DTexture9);
//            } else {
//                _TRACE_("GgafDx9D3DXAniMeshModel::draw("<<prm_pActor_Target->getName()<<") �e�N�X�`��������܂���Bwhite.png���ݒ肳���ׂ��ł��B���������ł�");
//                //������΃e�N�X�`������
//                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
//            }
//            //�}�e���A���̃Z�b�g
//            //GgafDx9God::_pID3DDevice9->SetMaterial(&(pTargetActor->_paD3DMaterial9[i]));
//            hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[i].Diffuse), sizeof(D3DCOLORVALUE) );
//            checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
//        }
//
//        //�`��
//        if (GgafDx9EffectManager::_pEffect_Active != pD3DXAniMeshEffect && i == 0) {
//            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
//                TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
//                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
//                checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
//                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
//                checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() End() �Ɏ��s���܂����B");
//            }
//
//            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
//            checkDxException(hr, S_OK, "GgafDx9D3DXAniMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");
//            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//            UINT numPass;
//            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
//            checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() Begin() �Ɏ��s���܂����B");
//            hr = pID3DXEffect->BeginPass(0);
//            checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");
//        } else {
//            hr = pID3DXEffect->CommitChanges();
//            checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
//        }
//        TRACE4("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
//        hr = _pID3DXAniMesh->DrawSubset(i);
//
//    }
    //�O��`�惂�f�������f
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pD3DXAniMeshEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

//�V�F�[�_�[�����O
//        if (pTargetActor->_SX == LEN_UNIT &&
//            pTargetActor->_SY == LEN_UNIT &&
//            pTargetActor->_SZ == LEN_UNIT)
//        {
//            hr = _pID3DXAniMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
//        } else {
//            //�g��k�����Ȃ���Ă��邽�߁A�J������ԂɃg�����X�t�H�[�����ꂽ��Œ��_�@���̐��K������悤�ɐݒ�i���׍��j
//            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//            hr = _pID3DXAniMesh->DrawSubset(i); //�Ȃ�ĕ֗��ȃ��\�b�h�I
//            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
//        }


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
    RELEASE_IMPOSSIBLE_NULL(_pAC);
    DELETE_IMPOSSIBLE_NULL(_pAH);
    //TODO:�������́H
    TRACE3("GgafDx9D3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDx9D3DXAniMeshModel::~GgafDx9D3DXAniMeshModel() {
    TRACE3("GgafDx9D3DXAniMeshModel::~GgafDx9D3DXAniMeshModel() " << _model_name << " start");
    release();
}
