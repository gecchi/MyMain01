#include "jp/ggaf/dx/model/D3DXAniMeshModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/D3DXAniMeshActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/effect/D3DXAniMeshEffect.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"

using namespace GgafDx;

D3DXAniMeshModel::D3DXAniMeshModel(const char* prm_model_id) : Model(prm_model_id) {
    _obj_model |= Obj_GgafDx_D3DXAniMeshModel;
    _pAllocHierarchy = nullptr;
    _pFrameRoot = nullptr;
    _pAniControllerBase = nullptr;
    _num_materials = 0L;
    _anim_ticks_per_second = 4800; //restoreD3DXAniMeshModel �ŏ㏑�������ꍇ������B
    _max_draw_set_num = 1;
}

HRESULT D3DXAniMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("D3DXAniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    HRESULT hr;
    //�ΏۃA�N�^�[
    D3DXAniMeshActor* pTargetActor = (D3DXAniMeshActor*)prm_pActor_target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    D3DXAniMeshEffect* pD3DXAniMeshEffect = (D3DXAniMeshEffect*)(prm_pActor_target->getEffect());
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pD3DXAniMeshEffect->_pID3DXEffect;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        God::_pID3DDevice9->SetFVF(D3DXAniMeshActor::FVF);
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pD3DXAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }

    pTargetActor->_pPuppeteer->updateAnimationTrack(); //�A�j���[�V�������f
    //���f���̃��[���h�ϊ��s��X�V
    pTargetActor->_stackWorldMat.SetWorldMatrix(&(pTargetActor->_matWorld));
    pTargetActor->_stackWorldMat.UpdateFrame(_pFrameRoot);
    std::list< BoneAniMeshFrame* > *pDrawList = pTargetActor->_stackWorldMat.GetDrawList(); // �`�惊�X�g���擾
    std::list<BoneAniMeshFrame*>::iterator it = pDrawList->begin();

    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
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
    checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

    for (int i = 0; it != pDrawList->end(); i++, ++it) {
        //�`��(TODO:�Ȃ񂩖��ʂȃ��[�v�j
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
                _TRACE4_("["<<i<<"],EndPass: /_pEffect_active="<<pEffect_active->_effect_name);
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pD3DXAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pD3DXAniMeshEffect->_effect_name<<"("<<pD3DXAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pD3DXAniMeshEffect->_begin) {
                throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pD3DXAniMeshEffect->_begin = true;
            }
#endif

        }
        hr = pID3DXEffect->SetMatrix(pD3DXAniMeshEffect->_h_matWorld, &((*it)->_world_trans_matrix));
        checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
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
                    checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
                }
                _TRACE4_("["<<i<<"]["<<j<<"],SetMaterial");
                hr = pID3DXEffect->CommitChanges();
                checkDxException(hr, D3D_OK, "["<<i<<"],D3DXAniMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
                (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(j);
                n++;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
            }
        }
    }
    //�O��`�惂�f�������f
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pD3DXAniMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

ID3DXAnimationController* D3DXAniMeshModel::getCloneAnimationController() {
    ID3DXAnimationController* _pAc = nullptr;
    HRESULT hr = _pAniControllerBase->CloneAnimationController(
                                _pAniControllerBase->GetMaxNumAnimationOutputs(),
                                _pAniControllerBase->GetMaxNumAnimationSets(),
                                _pAniControllerBase->GetMaxNumTracks(),
                                _pAniControllerBase->GetMaxNumEvents(),
                                        &_pAc);
    checkDxException(hr, D3D_OK, "�A�j���[�V�����R���g���[���[�̃N���[���Ɏ��s���܂����B");
    return _pAc;
}


void D3DXAniMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //TODO:�쐬���H�I�I�I�I�I�I�I�I
    ModelManager* pModelManager = pGOD->_pModelManager;
    //�yrestoreD3DXAniMeshModel�č\�z�i���������j�����T�v�z
    //1)D3DXLoadMeshFromX���g�p����X�t�@�C����ǂݍ���
    //2)D3DXAniMeshModel�̃����o�ɃZ�b�g
    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��D3DXAniMeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
//    LPD3DXMESH pID3DXAniMesh; //���b�V��(ID3DXAniMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* model_paMaterial = nullptr; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    TextureConnection** model_papTextureConnection = nullptr; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
//    DWORD _num_materials;
    ModelManager::MeshXFileFmt xdata;
    std::string model_def_file = std::string(_model_id) + ".meshx";
    std::string model_def_filepath = ModelManager::getModelDefineFilePath(model_def_file);
    pModelManager->obtainMeshModelInfo(&xdata, model_def_filepath);
    _matBaseTransformMatrix = xdata.BaseTransformMatrix;
    _draw_set_num = xdata.DrawSetNum;
    if (_draw_set_num != 1) {
        _TRACE_("D3DXAniMeshModel::restore() �{���f���� "<<_model_id<<" �̓����`��Z�b�g���� 1 �ɏ㏑������܂����B�i_draw_set_num="<<_draw_set_num<<" �͖�������܂����B�j");
        _draw_set_num = 1;
    }

    std::string xfilepath = ModelManager::getXFilePath(xdata.XFileNames[0]);

//    std::string xfile_name = ModelManager::getModelDefineFilePath(_model_id, "meshx");
//    if (xfile_name == "") {
//         throwCriticalException("���b�V���t�@�C��(*.x)��������܂���Bmodel_id="<<(_model_id));
//    }
    //AnimTicksPerSecond�̒l��Ǝ��Ɏ��o��
    std::ifstream ifs(xfilepath.c_str());
    if (ifs.fail()) {
        throwCriticalException("["<<xfilepath<<"] ���J���܂���");
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
    BoneAniMeshAllocHierarchy* pAllocHierarchy = NEW BoneAniMeshAllocHierarchy(); // CAllocHierarchyBase�̔h���N���X
    BoneAniMeshFrame* pFrameRoot; // ���[���h�ϊ��s��t���t���[���\����
    ID3DXAnimationController* pAC; // �A�j���[�V�����R���g���[��
    hr = D3DXLoadMeshHierarchyFromX(
            xfilepath.c_str(),
            D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
            God::_pID3DDevice9,
            pAllocHierarchy,
            nullptr,
            (D3DXFRAME**)(&pFrameRoot),
            &pAC
         );
    _TRACE_("pAllocHierarchy="<<pAllocHierarchy<<" pFrameRoot="<<pFrameRoot<<" pAC="<<pAC<<" xfile_name.c_str()="<<xfilepath.c_str());
    checkDxException(hr, D3D_OK, xfilepath<<" �ǂݍ��݂Ɏ��s���܂����B�Ώ�="<<xfilepath);
    if (pFrameRoot == nullptr) {
        throwCriticalException(xfilepath<<" �̃t���[����񂪎擾�ł��܂���I");
    }
    //�}�e���A���z����쐬
    std::list<BoneAniMeshFrame*> listFrame;
    getDrawFrameList(&listFrame, pFrameRoot); //�}�e���A��������m�肽�������߁A�t���[�������A���X�g��
    std::list<BoneAniMeshFrame*>::iterator it = listFrame.begin();
    int model_nMaterials = 0;
    //�t���[�����X�g������āA�}�e���A�������擾
    for (int i = 0; it != listFrame.end(); i++, ++it) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            model_nMaterials += (int)((*it)->pMeshContainer->NumMaterials);
        }
    }
    //�z�񐔂�����Ɖ������̂ō쐬
    model_paMaterial = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureConnection  = NEW TextureConnection*[model_nMaterials];
    //���f���ێ��p�}�e���A���A�e�N�X�`���쐬�̂��߁A������x��
    it = listFrame.begin();
    int n = 0;
    char* texture_filename;
    for (int i = 0; it != listFrame.end(); i++, ++it) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
//                (*it)->pMeshContainer->pMaterials[j].MatD3D.Diffuse
                model_paMaterial[n] = (*it)->pMeshContainer->pMaterials[j].MatD3D; //�}�e���A�����R�s�[

                texture_filename = (*it)->pMeshContainer->pMaterials[j].pTextureFilename;
                if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
                    model_papTextureConnection[n] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(texture_filename, this));
                } else {
                    //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
                    model_papTextureConnection[n] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(CONFIG::WHITE_TEXTURE.c_str(), this));
                }
                n ++;
            }
        }
    }
    //���E��
    D3DXVECTOR3 vecCenter;
    FLOAT model_bounding_sphere_radius;
    D3DXFrameCalculateBoundingSphere(pFrameRoot, &vecCenter, &model_bounding_sphere_radius);
    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������

    _pAllocHierarchy = pAllocHierarchy;
    _pFrameRoot = pFrameRoot;
    _pAniControllerBase = pAC;
    _bounding_sphere_radius = model_bounding_sphere_radius;
    _TRACE_("���E�����a="<<model_bounding_sphere_radius);
//    _advance_time_per_frame0 =  advanceTimePerFrame0; //�g���b�N0�ԂP���[�v�̎���
//    _TRACE_("�A�j���[�V�����Z�b�g0��_advance_time_per_frame");

//    _pID3DXAniMesh = pID3DXAniMesh;
    _paMaterial_default = model_paMaterial;
    _papTextureConnection = model_papTextureConnection;
    _num_materials = model_nMaterials;
    _anim_ticks_per_second = anim_ticks_per_second;
    _TRACE3_("_model_id=" << _model_id << " end");
}

void D3DXAniMeshModel::getDrawFrameList(std::list<BoneAniMeshFrame*>* pList, BoneAniMeshFrame* pFrame) {
    if (pFrame->pMeshContainer) {
        //���b�V���R���e�i�L��
        pList->push_back(pFrame); //���X�g�ɒǉ�
    }
    if (pFrame->pFrameFirstChild) {
        // �q�t���[���L��
        getDrawFrameList(pList, (BoneAniMeshFrame*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //�Z��t���[���L��
        getDrawFrameList(pList, (BoneAniMeshFrame*)pFrame->pFrameSibling);
    }
}


void D3DXAniMeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void D3DXAniMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
//    if (_pID3DXAniMesh == nullptr) {
//        throwCriticalException("Error! _pID3DXAniMesh�� �I�u�W�F�N�g�ɂȂ��Ă��Ȃ����� release �ł��܂���I");
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
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_RELEASE(_pAniControllerBase);
    _pAllocHierarchy->DestroyFrame((D3DXFRAME*)_pFrameRoot);
    GGAF_DELETE(_pAllocHierarchy);
    //TODO:�������́H
    _TRACE3_("_model_id=" << _model_id << " end");
}

D3DXAniMeshModel::~D3DXAniMeshModel() {
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}
