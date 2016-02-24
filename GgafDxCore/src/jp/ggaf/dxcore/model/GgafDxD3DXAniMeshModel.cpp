#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"

#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxPuppeteer.h"
#include "jp/ggaf/dxcore/effect/GgafDxD3DXAniMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxD3DXAniMeshModel::GgafDxD3DXAniMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
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
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    int n = 0;
    //�}�e���A���E�e�N�X�`���̈ꔭ�ڂ��Z�b�g�A
    LPDIRECT3DBASETEXTURE9 pTex = nullptr;
    LPDIRECT3DBASETEXTURE9 pLastTex = nullptr;
    if (_papTextureConnection[n]) {
        pLastTex = _papTextureConnection[n]->peek()->_pIDirect3DBaseTexture9;
        pDevice->SetTexture(0, pLastTex);
    } else {
        //������΃e�N�X�`������
        pDevice->SetTexture(0, nullptr);
    }
    hr = pID3DXEffect->SetValue(pD3DXAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[n].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "GgafDxD3DXAniMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

    for (int i = 0; it != pDrawList->end(); i++, it++) {
        //�`��(TODO:�Ȃ񂩖��ʂȃ��[�v�j
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((pEffect_active != pD3DXAniMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
                _TRACE4_("GgafDxD3DXAniMeshModel::draw() ["<<i<<"],EndPass: /_pEffect_active="<<pEffect_active->_effect_name);
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],GgafDxD3DXAniMeshModel::draw() End() �Ɏ��s���܂����B");
                if (pEffect_active->_obj_effect & Obj_GgafDxMassMeshEffect) {
                    pDevice->SetStreamSourceFreq( 0, 1 );
                    pDevice->SetStreamSourceFreq( 1, 1 );
                }
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("GgafDxD3DXAniMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("GgafDxD3DXAniMeshModel::draw() BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
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
                        pDevice->SetTexture(0, pTex);
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
                GgafGod::_num_drawing++;
            }
        }
    }
    //�O��`�惂�f�������f
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pD3DXAniMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxD3DXAniMeshModel::restore() {
    _TRACE3_("GgafDxD3DXAniMeshModel::restore() " << _model_name << " start");
    //TODO:�쐬���H�I�I�I�I�I�I�I�I

    //�yrestoreD3DXAniMeshModel�č\�z�i���������j�����T�v�z
    //1)D3DXLoadMeshFromX���g�p����X�t�@�C����ǂݍ���
    //2)GgafDxD3DXAniMeshModel�̃����o�ɃZ�b�g
    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��GgafDxD3DXAniMeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
//    LPD3DXMESH pID3DXAniMesh; //���b�V��(ID3DXAniMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* model_paMaterial = nullptr; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    GgafDxTextureConnection** model_papTextureConnection = nullptr; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
//    DWORD _num_materials;
    std::string xfile_name = GgafDxModelManager::getMeshFileName(_model_name);
    if (xfile_name == "") {
         throwGgafCriticalException("GgafDxModelManager::restoreD3DXAniMeshModel ���b�V���t�@�C��(*.x)��������܂���Bmodel_name="<<(_model_name));
    }
    //AnimTicksPerSecond�̒l��Ǝ��Ɏ��o��
    std::ifstream ifs(xfile_name.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException(" GgafDxModelManager::restoreD3DXAniMeshModel ["<<xfile_name<<"] ���J���܂���");
    }
    std::string buf;
    bool isdone = false;
    int anim_ticks_per_second = 4800;
    std::string data;
    while (isdone == false && !ifs.eof()) {
        ifs >> data;
        if (data == "AnimTicksPerSecond" || data == "AnimTicksPerSecond{") {
            while (isdone == false) {
                ifs >> data;
                if (data == "{") {
                    continue;
                } else if (data == "}") {
                    isdone = true;
                    break;
                } else {
                    anim_ticks_per_second = atoi(data.c_str()); //"60;" �� 60�𓾂�
                    isdone = true;
                    break;
                }
            }
        }
    }
    ifs.close();

//    LPD3DXBUFFER pID3DXBuffer; //�󂯎��p�o�b�t�@�i�}�e���A���p�j
    HRESULT hr;
    //X�t�@�C���̃t�@�C�����[�h
    GgafDxAllocHierarchyWorldFrame* pAH = NEW GgafDxAllocHierarchyWorldFrame(); // CAllocHierarchyBase�̔h���N���X
    D3DXFRAME_WORLD* pFR; // ���[���h�ϊ��s��t���t���[���\����
    ID3DXAnimationController* pAC; // �A�j���[�V�����R���g���[��
    hr = D3DXLoadMeshHierarchyFromX(
            xfile_name.c_str(),
            D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
            GgafDxGod::_pID3DDevice9,
            pAH,
            nullptr,
            (D3DXFRAME**)(&pFR),
            &pAC
         );
    _TRACE_("pAH="<<pAH<<" pFR="<<pFR<<" pAC="<<pAC<<" xfile_name.c_str()="<<xfile_name.c_str());
    checkDxException(hr, D3D_OK, "GgafDxModelManager::restoreD3DXAniMeshModel "<<xfile_name<<" �ǂݍ��݂Ɏ��s���܂����B�Ώ�="<<xfile_name);
    if (pFR == nullptr) {
        throwGgafCriticalException("GgafDxModelManager::restoreD3DXAniMeshModel "<<xfile_name<<" �̃t���[����񂪎擾�ł��܂���I");
    }
    //�}�e���A���z����쐬
    std::list<D3DXFRAME_WORLD*> listFrame;
    getDrawFrameList(&listFrame, pFR); //�}�e���A��������m�肽�������߁A�t���[�������A���X�g��
    std::list<D3DXFRAME_WORLD*>::iterator it = listFrame.begin();
    int model_nMaterials = 0;
    //�t���[�����X�g������āA�}�e���A�������擾
    for (int i = 0; it != listFrame.end(); i++, it++) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            model_nMaterials += (int)((*it)->pMeshContainer->NumMaterials);
        }
    }
    //�z�񐔂�����Ɖ������̂ō쐬
    model_paMaterial = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureConnection  = NEW GgafDxTextureConnection*[model_nMaterials];
    //���f���ێ��p�}�e���A���A�e�N�X�`���쐬�̂��߁A������x��
    it = listFrame.begin();
    int n = 0;
    char* texture_filename;
    for (int i = 0; it != listFrame.end(); i++, it++) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
//                (*it)->pMeshContainer->pMaterials[j].MatD3D.Diffuse
                model_paMaterial[n] = (*it)->pMeshContainer->pMaterials[j].MatD3D; //�}�e���A�����R�s�[

                texture_filename = (*it)->pMeshContainer->pMaterials[j].pTextureFilename;
                if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
                    model_papTextureConnection[n] = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(texture_filename, this));
                } else {
                    //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
                    model_papTextureConnection[n] = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(PROPERTY::WHITE_TEXTURE.c_str(), this));
                }
                n ++;
            }
        }
    }
    //���E��
    D3DXVECTOR3 vecCenter;
    FLOAT model_bounding_sphere_radius;
    D3DXFrameCalculateBoundingSphere(pFR, &vecCenter, &model_bounding_sphere_radius);
    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������

    _pAH = pAH;
    _pFR = pFR;
    _pAcBase = pAC;
    _bounding_sphere_radius = model_bounding_sphere_radius;
    _TRACE_("���E�����a="<<model_bounding_sphere_radius);
//    _advance_time_per_frame0 =  advanceTimePerFrame0; //�g���b�N0�ԂP���[�v�̎���
//    _TRACE_("�A�j���[�V�����Z�b�g0��_advance_time_per_frame");

//    _pID3DXAniMesh = pID3DXAniMesh;
    _paMaterial_default = model_paMaterial;
    _papTextureConnection = model_papTextureConnection;
    _num_materials = model_nMaterials;
    _anim_ticks_per_second = anim_ticks_per_second;
    _TRACE3_("GgafDxD3DXAniMeshModel::restore() " << _model_name << " end");
}

void GgafDxD3DXAniMeshModel::getDrawFrameList(std::list<D3DXFRAME_WORLD*>* pList, D3DXFRAME_WORLD* pFrame) {
    if (pFrame->pMeshContainer) {
        //���b�V���R���e�i�L��
        pList->push_back(pFrame); //���X�g�ɒǉ�
    }
    if (pFrame->pFrameFirstChild) {
        // �q�t���[���L��
        getDrawFrameList(pList, (D3DXFRAME_WORLD*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //�Z��t���[���L��
        getDrawFrameList(pList, (D3DXFRAME_WORLD*)pFrame->pFrameSibling);
    }
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
    GGAF_DELETEARR(_pa_texture_filenames);
    GGAF_RELEASE(_pAcBase);
    GGAF_DELETE(_pAH);
    //TODO:�������́H
    _TRACE3_("GgafDxD3DXAniMeshModel::release() " << _model_name << " end");
}

GgafDxD3DXAniMeshModel::~GgafDxD3DXAniMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}
