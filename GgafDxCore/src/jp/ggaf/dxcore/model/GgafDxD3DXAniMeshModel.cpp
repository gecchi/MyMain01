#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxD3DXAniMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxPuppeteer.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxD3DXAniMeshModel::GgafDxD3DXAniMeshModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    _pAH = nullptr;
    _pFR = nullptr;
    _pAcBase = nullptr;
    _num_materials = 0L;
    _anim_ticks_per_second = 4800; //restoreD3DXAniMeshModel �ŏ㏑�������ꍇ������B

    _obj_model |= Obj_GgafDxD3DXAniMeshModel;


    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreD3DXAniMeshModel(GgafDxD3DXAniMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

HRESULT GgafDxD3DXAniMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxD3DXAniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    HRESULT hr;
    //�ΏۃA�N�^�[
    GgafDxD3DXAniMeshActor* pTargetActor = (GgafDxD3DXAniMeshActor*)prm_pActor_target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    GgafDxD3DXAniMeshEffect* pD3DXAniMeshEffect = (GgafDxD3DXAniMeshEffect*)(prm_pActor_target->getEffect());
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
    std::list< D3DXFRAME_WORLD* > *pDrawList = _stackWorldMat.GetDrawList(); // �`�惊�X�g���擾
    std::list<D3DXFRAME_WORLD*>::iterator it = pDrawList->begin();

    int n = 0;
    //�}�e���A���E�e�N�X�`���̈ꔭ�ڂ��Z�b�g�A
    LPDIRECT3DBASETEXTURE9 pTex = nullptr;
    LPDIRECT3DBASETEXTURE9 pLastTex = nullptr;
    if (_papTextureConnection[n]) {
        pLastTex = _papTextureConnection[n]->peek()->_pIDirect3DBaseTexture9;
        GgafDxGod::_pID3DDevice9->SetTexture(0, pLastTex);
    } else {
        //������΃e�N�X�`������
        GgafDxGod::_pID3DDevice9->SetTexture(0, nullptr);
    }
    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //�`��
        if ((GgafDxEffectManager::_pEffect_active != pD3DXAniMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (GgafDxEffectManager::_pEffect_active) {
                _TRACE4_("["<<i<<"],EndPass: /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name);
                hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() End() �Ɏ��s���܂����B");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_active->_begin = false;
                }
#endif

            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pD3DXAniMeshEffect->_begin) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pD3DXAniMeshEffect->_begin = true;
            }
#endif

        }
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->WorldTransMatrix));
        checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        if ((*it)->pMeshContainer == nullptr) {
            _TRACE4_("["<<i<<"]�~SetMatrix FrameName="<<((*it)->Name)<<" ��΂��I");
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
                if (n > 0) {
                    pTex = _papTextureConnection[n]->peek()->_pIDirect3DBaseTexture9;
                    if (pTex != pLastTex) {
                        //�e�N�X�`�����قȂ�ΐݒ�
                        GgafDxGod::_pID3DDevice9->SetTexture(0, pTex);
                        pLastTex = pTex;
                    }
                    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
                    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
                }
                _TRACE4_("["<<i<<"]["<<j<<"],SetMaterial");
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
    GgafDxEffectManager::_pEffect_active = pD3DXAniMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxD3DXAniMeshModel::restore() {
    _TRACE3_("GgafDxD3DXAniMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreD3DXAniMeshModel(this);
    _TRACE3_("GgafDxD3DXAniMeshModel::restore() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxD3DXAniMeshModel::onDeviceLost() " << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    _TRACE3_("GgafDxD3DXAniMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::release() {
    _TRACE3_("GgafDxD3DXAniMeshModel::release() " << _model_name << " start");
//    if (_pID3DXAniMesh == nullptr) {
//        throwGgafCriticalException("[GgafDxD3DXAniMeshModel::release] Error! _pID3DXAniMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
//    }
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //�e�N�X�`���̔z��
//    GGAF_RELEASE(_pID3DXAniMesh);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_RELEASE(_pAcBase);
    GGAF_DELETE(_pAH);
    //TODO:�������́H
    _TRACE3_("GgafDxD3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDxD3DXAniMeshModel::~GgafDxD3DXAniMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}
