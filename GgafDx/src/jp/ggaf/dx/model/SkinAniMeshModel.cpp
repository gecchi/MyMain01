#include "jp/ggaf/dx/model/SkinAniMeshModel.h"

#include <algorithm>
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/SkinAniMeshActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/SkinAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/util/SkinAniMeshContainer.h"
#include "jp/ggaf/dx/util/SkinAniMeshFrame.h"

using namespace GgafDx;

SkinAniMeshModel::SkinAniMeshModel(const char* prm_model_name) : Model(prm_model_name) {
    _pAllocHierarchy = nullptr;
    _pFrameRoot = nullptr;
    _pAniControllerBase = nullptr;
    _num_materials = 0L;
//    _anim_ticks_per_second = 4800; //restoreSkinAniMeshModel �ŏ㏑�������ꍇ������B
    _paVtxBuffer_data = nullptr;
    _paIndexBuffer_data = nullptr;
    _pVertexDeclaration = nullptr;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _index_param_num = 0;
    _paIndexParam = nullptr;
    _paIndexBuffer_bone_combi_index = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = sizeof(SkinAniMeshModel::VERTEX);
    _nFaces = 0;
    _nVertices = 0;
    _tmp_frame_index = 0;
    _num_animation_set = 0;
    _papaBool_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _obj_model |= Obj_GgafDx_SkinAniMeshModel;
}

HRESULT SkinAniMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("SkinAniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    HRESULT hr;
    //�ΏۃA�N�^�[
    SkinAniMeshActor* pTargetActor = (SkinAniMeshActor*)prm_pActor_target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    SkinAniMeshEffect* pSkinAniMeshEffect = (SkinAniMeshEffect*)(prm_pActor_target->getEffect());
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pSkinAniMeshEffect->_pID3DXEffect;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //���_�t�H�[�}�b�g
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetIndices(_pIndexBuffer);
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�}�e���A���E�e�N�X�`���̈ꔭ�ڂ��Z�b�g�A
    LPDIRECT3DBASETEXTURE9 pTex = _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9;
    hr = pDevice->SetTexture(0, pTex);
    checkDxException(hr, D3D_OK, "SetTexture �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetValue(pSkinAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
    Puppeteer* pActorPuppeteer = pTargetActor->_pPuppeteer;
    pActorPuppeteer->updateAnimationTrack(); //�A�j���[�V�������f
    //���f���̃��[���h�ϊ��s��X�V
    pTargetActor->_stackWorldMat.SetWorldMatrix(&(pTargetActor->_matWorld));
    ID3DXAnimationSet* pAs0 = pActorPuppeteer->_paAs[0];
    ID3DXAnimationSet* pAs1 = pActorPuppeteer->_paAs[1];
    int as0_index = (int)_mapAnimationSet_AniSetindex[pAs0];
    int as1_index = pAs1 ? _mapAnimationSet_AniSetindex[pAs1] : -1;
    pTargetActor->_stackWorldMat.UpdateFrame(_pFrameRoot, as0_index, as1_index, _papaBool_AnimationSetIndex_BoneFrameIndex_is_act);

    std::vector<SkinAniMeshFrame*>::iterator it_1 = _vecBoneIdFrame.begin();

/////////////////////////////////////////////
///




//    for (int i = 0; i < _vec_infl_bone_id_order.size(); i++) {
//        DWORD bone_id = _vec_infl_bone_id_order[i];
//        hr = pID3DXEffect->SetMatrix(pSkinAniMeshEffect->_ah_matBone[i], &(_vecBoneIdFrame[bone_id]->_combined_matrix));
//    }


    for (int i = 0; i < _vec_infl_bone_id_order.size(); i++) {
        hr = pID3DXEffect->SetMatrix(pSkinAniMeshEffect->_ah_matBone[i], _ap_draw_combined_matrix[i] );
    }

    for (int i = 0; i < _index_param_num; i++) {
        const INDEXPARAM& idxparam = _paIndexParam[i];
//        for (int j = 0; j < SkinAniMeshModel_MAX_BONE_WORLD_MATRIX; j++) {
//            if (it_1 != _vecBoneIdFrame.end()) {
//                hr = pID3DXEffect->SetMatrix(pSkinAniMeshEffect->_ah_matBone[j], &((*it_1)->_combined_matrix));
//                ++it_1;
//            } else {
//                break;
//            }
//        }

        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
                _TRACE4_("EndPass: /_pEffect_active="<<pEffect_active->_effect_name);
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSkinAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSkinAniMeshEffect->_effect_name<<"("<<pSkinAniMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pSkinAniMeshEffect->_begin) {
                throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pSkinAniMeshEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "SkinAniMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
    }

#ifdef MY_DEBUG
    GgafCore::God::_num_drawing++;
#endif
    //�O��`�惂�f�������f
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pSkinAniMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void SkinAniMeshModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    if (_paVtxBuffer_data == nullptr) {
        HRESULT hr;
        std::string xfile_name = ModelManager::getMeshFileName(_model_name);
        TextureManager* pTextureManager = pGOD->_pModelManager->_pModelTextureManager;
        //AnimTicksPerSecond��Ǝ��Ɏ��o���B�f�t�H���g��4800
//        _anim_ticks_per_second = SkinAniMeshModel::getAnimTicksPerSecond(xfile_name);
//DEBUG
//_TRACE_("SkinAniMeshModel::restore() _anim_ticks_per_second="<<_anim_ticks_per_second);
//        if (_anim_ticks_per_second < 0) {
//            _anim_ticks_per_second = 4800;
//        }
        //X�t�@�C���̃t�@�C�����[�h
        _pAllocHierarchy = NEW SkinAniMeshAllocHierarchy(); // CAllocHierarchyBase�̔h���N���X
        hr = D3DXLoadMeshHierarchyFromX(
                xfile_name.c_str(),
                D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
                God::_pID3DDevice9,
                _pAllocHierarchy,
                nullptr,
                (D3DXFRAME**)(&_pFrameRoot),
                &_pAniControllerBase
             );
        _TRACE_("_pAllocHierarchy="<<_pAllocHierarchy<<" _pFrameRoot="<<_pFrameRoot<<" _pAniControllerBase="<<_pAniControllerBase<<" xfile_name.c_str()="<<xfile_name.c_str());
        checkDxException(hr, D3D_OK, xfile_name<<" �ǂݍ��݂Ɏ��s���܂����B�Ώ�="<<xfile_name);
        if (_pFrameRoot == nullptr) {
            throwCriticalException(xfile_name<<" �̃t���[����񂪎擾�ł��܂���I");
        }
        //�f�t�H���g�Őݒ肳��Ă���g���b�N�̃A�j���[�V�����Ŏp����������i�R�s�[�p�j
        //�O���[�o�����Ԃ�0�ɂ���
        hr = _pAniControllerBase->ResetTime();
        checkDxException(hr, D3D_OK, "���s���܂����B");
        //0�b�i�߂�i���Ƃɂ���Ĕ��f������j�B
        hr = _pAniControllerBase->AdvanceTime(0, nullptr);
        checkDxException(hr, D3D_OK, "���s���܂����B");

        _vecDrawBoneFrame.clear();
        _vecAllBoneFrame.clear();
        _tmp_frame_index = 0;

        _TRACE_("setFrameInfo!!!!!!!!!!!!!!!!!1");
        setFrameInfo(_pFrameRoot); //�t���[���������������o�ɃZ�b�g
        //////
        _mapAnimationSet_AniSetindex.clear();
        _mapAnimationSetIndex_AnimationTargetBoneFrameNames.clear();
        _num_animation_set = _pAniControllerBase->GetMaxNumAnimationSets();
        for (UINT ani_set_index = 0; ani_set_index < _num_animation_set; ani_set_index++) {
            ID3DXAnimationSet* pAnimationSet = nullptr;
            hr = _pAniControllerBase->GetAnimationSet(ani_set_index, &(pAnimationSet)); //�A�j���[�V�����Z�b�g�ێ�
            checkDxException(hr, D3D_OK, "���s���܂���");
            _mapAnimationSet_AniSetindex[pAnimationSet] = ani_set_index;
            int num_animation = pAnimationSet->GetNumAnimations();
            for (UINT ani_index = 0; ani_index < num_animation; ++ani_index) {
                LPCSTR target_bone_frame_name = nullptr;
                hr = pAnimationSet->GetAnimationNameByIndex(ani_index, &target_bone_frame_name);
                checkDxException(hr, D3D_OK, "���s���܂���");
                _mapAnimationSetIndex_AnimationTargetBoneFrameNames[ani_set_index].push_back(target_bone_frame_name);

            }
        }

        _papaBool_AnimationSetIndex_BoneFrameIndex_is_act = NEW bool*[_num_animation_set];
        for (UINT ani_set_index = 0; ani_set_index < _num_animation_set; ani_set_index++) {
            _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index] = NEW bool[_tmp_frame_index+1];
            std::vector<LPCSTR>* pAnimationTargetBoneFrameNameList = &(_mapAnimationSetIndex_AnimationTargetBoneFrameNames[ani_set_index]);
            for (UINT frame_index = 0; frame_index < _vecAllBoneFrame.size(); frame_index++) {
                _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index][frame_index] = false;
                LPSTR frame_name = _vecAllBoneFrame[frame_index]->Name;
                if (frame_name) {
                    for (int n = 0; n < pAnimationTargetBoneFrameNameList->size(); n++) {
                        LPCSTR animation_target_bone_frame_name = (*pAnimationTargetBoneFrameNameList)[n];
                        if (strcmp(animation_target_bone_frame_name, frame_name) == 0) {
                            _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index][frame_index] = true;
                            break;
                        }
                    }
                }
            }
        }

        //���E��
        D3DXVECTOR3 vecCenter;
        FLOAT bounding_sphere_radius;
        D3DXFrameCalculateBoundingSphere((D3DXFRAME*)_pFrameRoot, &vecCenter, &bounding_sphere_radius);
        _bounding_sphere_radius = UTIL::getDistance(0.0f, 0.0f, 0.0f, vecCenter.x, vecCenter.y, vecCenter.z) + bounding_sphere_radius;

        _TRACE_("���E�����a="<<_bounding_sphere_radius);


        int draw_frame_num = _vecDrawBoneFrame.size();

        int materials_total_num = 0;
        int vertices_total_num = 0;
        int faces_total_num = 0;

        //�t���[�����X�g������āA�}�e���A�������擾
        for (int i = 0; i < draw_frame_num; i++) {
            SkinAniMeshContainer* pMeshContainer = (SkinAniMeshContainer*)(_vecDrawBoneFrame[i]->pMeshContainer);
            if (pMeshContainer == nullptr) {
                continue;
            }

            ID3DXMesh* pMesh = _vecDrawBoneFrame[i]->pMeshContainer->MeshData.pMesh;
            vertices_total_num += (int)(pMesh->GetNumVertices());  // ���_��
            faces_total_num += (int)(pMesh->GetNumFaces());        // �|���S����
            materials_total_num += (int)(_vecDrawBoneFrame[i]->pMeshContainer->NumMaterials);
        }

        //�z�񐔂�����Ɖ������̂ō쐬
        _num_materials = materials_total_num;
        _nVertices = vertices_total_num;
        _nFaces = faces_total_num;
        _paVtxBuffer_data =  NEW SkinAniMeshModel::VERTEX[_nVertices];
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
        _paIndexBuffer_bone_combi_index = NEW int[_nFaces*3];
        if (!_paMaterial_default) {
            if (materials_total_num > 0) {
                _paMaterial_default = NEW D3DMATERIAL9[_num_materials];
                _pa_texture_filenames = NEW std::string[_num_materials];
                // ���Őݒ�
            } else {
                //�}�e���A����`���P�������̂ŁA�`��̂��߂ɖ������P�}�e���A�����쐬�B
                _num_materials = 1;
                _paMaterial_default  = NEW D3DMATERIAL9[1];
                _pa_texture_filenames = NEW std::string[1];
                setDefaultMaterial(&(_paMaterial_default[0]));
                _pa_texture_filenames[0] = CONFIG::WHITE_TEXTURE;
            }
        } //  if (!_paMaterial_default)


        //���f���ێ��p�}�e���A���A�e�N�X�`���쐬�̂��߁A������x��
        int m_cnt = 0;   //�}�e���A���Ɖ����J�E���^�[
        int v_cnt = 0;   //���_�o�b�t�@�ʂ��J�E���^�[
        int i_cnt = 0;   //�C���f�b�N�X�o�b�t�@�ʂ��J�E���^�[
        char* texture_filename;
        D3DVERTEXELEMENT9 e[MAX_FVF_DECL_SIZE];
        //�t���[���Ń��[�v�I
        for (int i = 0; i < draw_frame_num; i++) {
            SkinAniMeshContainer* pMeshContainer = (SkinAniMeshContainer*)(_vecDrawBoneFrame[i]->pMeshContainer);
            if (pMeshContainer == nullptr) {
                continue;
            }
            int nMaterials = (int)(pMeshContainer->NumMaterials);
            for (int j = 0; j < nMaterials; j++) {
                if (pMeshContainer->pMaterials) {
                    _paMaterial_default[m_cnt] = pMeshContainer->pMaterials[j].MatD3D; //�}�e���A�����R�s�[
                    texture_filename = pMeshContainer->pMaterials[j].pTextureFilename;
                    if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
                        _pa_texture_filenames[m_cnt] = std::string(texture_filename);
                    } else {
                        //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
                        _pa_texture_filenames[m_cnt] = CONFIG::WHITE_TEXTURE;
                    }
                } else {
                    setDefaultMaterial(&(_paMaterial_default[m_cnt]));
                    _pa_texture_filenames[m_cnt] = CONFIG::WHITE_TEXTURE;
                }
                m_cnt ++;
            }

            ID3DXMesh* pMesh = pMeshContainer->MeshData.pMesh;

            pMesh->GetDeclaration( e );
            int offset_position  = getOffsetFromElem( e, D3DDECLUSAGE_POSITION );
            int offset_normal  = getOffsetFromElem( e, D3DDECLUSAGE_NORMAL );
    //        int offset_color  = getOffsetFromElem( e, D3DDECLUSAGE_COLOR );
            int offset_texcoord  = getOffsetFromElem( e, D3DDECLUSAGE_TEXCOORD );

            IDirect3DVertexBuffer9* pVb;
            pMesh->GetVertexBuffer(&pVb);
            DWORD size_vertex_unit = pMesh->GetNumBytesPerVertex(); // 1�̒��_�̃T�C�Y
            void* pVertexBuffer;
            int nVertices = (int)(pMesh->GetNumVertices()); //���b�V���R���e�i�̒��_��
            pVb->Lock(0, nVertices*size_vertex_unit, (void**)&pVertexBuffer, 0);
            for (int j = 0; j < nVertices; j++) {
                char* p = nullptr;
                SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[v_cnt]); //��������1���_�̊J�n�A�h���X
                char* pVertex_base = (char*)pVertexBuffer + (size_vertex_unit*j);  //�ǂݍ���1���_�̊J�n�A�h���X
                //    float x, y, z;    // ���_���W
                p = pVertex_base + offset_position;
                memcpy(&(pVtx->x), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                memcpy(&(pVtx->y), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                memcpy(&(pVtx->z), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                //Normal  float nx, ny, nz; // �@��
                if (offset_normal > 0) {
                    p = pVertex_base + offset_normal;
                    memcpy(&(pVtx->nx), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx->ny), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx->nz), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                } else {
                    pVtx->nx = 0.0f;
                    pVtx->ny = 0.0f;
                    pVtx->nz = 0.0f;
                }
                // float bone_combi_index
                pVtx->bone_combi_index = -1; // ���ݒ�A���ōĐݒ肷��

                //DWORD color ; //���_�J���[
                pVtx->color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[

                //float tu, tv;     // �e�N�X�`�����W
                if (offset_texcoord > 0) {
                    p = pVertex_base + offset_texcoord;
                    memcpy(&(pVtx->tu), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx->tv), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                } else {
                    pVtx->tu = 0.0f;
                    pVtx->tv = 0.0f;
                }
//               _TRACE_("["<<i<<"]["<<j<<"]:pVtx->index="<<pVtx->index<<"  Vertex=("<<(pVtx->x)<<","<<(pVtx->y)<<","<<(pVtx->z)<<")  Normal=("<<(pVtx->nx)<<","<<(pVtx->ny)<<","<<(pVtx->nz)<<")  texcoordl=("<<(pVtx->tu)<<","<<(pVtx->tv)<<")");

                for (int k = 0; k < 4; k++) {  // ���ŏ����l�ݒ�A���ōĐݒ肷��
                    pVtx->infl_weight[k] = 0.0f;
                    pVtx->infl_bone_id[k] = 0xFF;
                    pVtx->infl_bone_id_order[k] = 0xFF;
                }
                v_cnt ++;
            }
            pVb->Unlock();
            pVb->Release();



            //skin���̂��߂ɂ����������[�v
            int vertx_through_count = 0;
            int bc_through_idx = 0;
            for (int i = 0; i < draw_frame_num; i++) {

                SkinAniMeshContainer* pMeshContainer = (SkinAniMeshContainer*)(_vecDrawBoneFrame[i]->pMeshContainer);
                if (pMeshContainer == nullptr) {
                    continue;
                }
                /////////////
                _TRACE_("draw_frsme["<<i<<"]: idx="<<_vecDrawBoneFrame[i]->_frame_index<<", name="<<_vecDrawBoneFrame[i]->Name<<"");
                _TRACE_("pMeshContainer->_dwMaxInfleNum = "<<pMeshContainer->_dwMaxInfleNum);
                _TRACE_("pMeshContainer->_dwBoneCombNum = "<<pMeshContainer->_dwBoneCombNum);
                LPD3DXSKININFO pSkinInfo = pMeshContainer->pSkinInfo;
                D3DXBONECOMBINATION* paBoneCombination =
                        (D3DXBONECOMBINATION*)(pMeshContainer->_pBoneCombinationTable->GetBufferPointer());
                for (DWORD bc_idx = 0; bc_idx < pMeshContainer->_dwBoneCombNum; ++bc_idx, ++bc_through_idx) { //bc_idx�̓��b�V���T�u�Z�b�gID
                    D3DXBONECOMBINATION* pBoneCombination = &(paBoneCombination[bc_idx]);
                    _TRACE_("paBoneCombination["<<bc_idx<<"] = "<<
                            " AttribId="<<pBoneCombination->AttribId<<
                            " FaceStart="<<pBoneCombination->FaceStart<<
                            " FaceCount="<<pBoneCombination->FaceCount<<
                            " VertexStart="<<pBoneCombination->VertexStart<<
                            " VertexCount="<<pBoneCombination->VertexCount<<
                            ""
                    );
                    //���_���Ƀ{�[���R���r�l�[�V�����C���f�b�N�X����������
                    for (DWORD v = 0; v < pBoneCombination->VertexCount; v++, vertx_through_count++) {
                        SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[vertx_through_count]);
                        pVtx->bone_combi_index = (float)bc_through_idx;
                    }
                    DWORD infl_id;
                    for ( infl_id = 0; infl_id < pMeshContainer->_dwMaxInfleNum; ++infl_id) { //
                        DWORD bone_id = pBoneCombination->BoneId[infl_id]; //bone_id�͂Ȃ�Ȃ̂��H
                        DWORD bone_influ_vertices_num = pSkinInfo->GetNumBoneInfluences(bone_id);

                        _TRACE_("paBoneCombination["<<bc_idx<<"].BoneId["<<infl_id<<"]="<<bone_id<<" bone_influ_vertices_num="<<bone_influ_vertices_num);

                        if (bone_influ_vertices_num > 0) {
                            // Get the bone influcences
                            DWORD* vertices = new DWORD[bone_influ_vertices_num];
                            float* skin_weight  = new float[bone_influ_vertices_num];
                            pSkinInfo->GetBoneInfluence(bone_id, vertices, skin_weight);
                            for (DWORD v = 0; v < bone_influ_vertices_num; v++) {
                                if (skin_weight[v] > 0.0) {
                                    SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[vertices[v]]);
                                    bool is_exist = false;
                                    for (int k = 0; k < 4; k++) {
                                        if (pVtx->infl_bone_id[k] == (byte)bone_id) {
                                            is_exist = true;
                                            break;
                                        }
                                    }
                                    if (is_exist == false) {
                                        for (int k = 0; k < 4; k++) {
                                            if (pVtx->infl_weight[k] < skin_weight[v]) { //weight�傫������
                                            //if (pVtx->infl_weight[k] == 0.0 || (pVtx->infl_weight[k] > 0.0 && pVtx->infl_weight[k] > skin_weight[v])) { //weight��������
                                                for (int j = 3; j > k; j--) {
                                                    //�X���C�h
                                                    pVtx->infl_bone_id[j] = pVtx->infl_bone_id[j-1];
                                                    pVtx->infl_weight[j] = pVtx->infl_weight[j-1];
                                                }
                                                pVtx->infl_bone_id[k] = (byte)bone_id;
                                                pVtx->infl_weight[k] =  skin_weight[v];

                                                 std::vector<DWORD>::iterator p = std::find(_vec_infl_bone_id_order.begin(), _vec_infl_bone_id_order.end(), bone_id);
                                                 if (p == _vec_infl_bone_id_order.end()) {
                                                     //���݂��Ȃ������߂Ă� bone_id
                                                     _vec_infl_bone_id_order.push_back(bone_id);
                                                 }
                                                 break;
                                            }
                                        }


//                                        for (int k = 0; k < 4; k++) {
//                                            if (pVtx->infl_bone_idx[k] == 0xFF) {
//                                                 pVtx->infl_bone_idx[k] = (byte)bone_id;
//                                                 pVtx->infl_weight[k] =  skin_weight[v];
//
//                                                 std::vector<DWORD>::iterator p = std::find(_vec_infl_bone_id_order.begin(), _vec_infl_bone_id_order.end(), bone_id);
//                                                 if (p == _vec_infl_bone_id_order.end()) {
//                                                     //���݂��Ȃ������߂Ă� bone_id
//                                                     _vec_infl_bone_id_order.push_back(bone_id);
//                                                 }
//                                                 break;
//                                            }
//                                        }
                                    }
                                }
                            }

                            _TRACE_N_("Vertices=");
                            for (int v = 0; v < bone_influ_vertices_num; v++) {
                                _TRACE_N_("\t"<<vertices[v]<<"");
                            }
                            _TRACE_N_("\n");
                            _TRACE_N_("Weights=");
                            for (int v = 0; v < bone_influ_vertices_num; v++) {
                                _TRACE_N_("\t"<<skin_weight[v]<<"");
                            }
                            _TRACE_N_("\n");
                        }
                    }
                }

                //�{�[��ID��Frame�̕R�t����_bone_offset_matrix�̕ێ�
                DWORD dwNumBone = pSkinInfo->GetNumBones();  // �{�[���̐����擾
                // �{�[���̐������Ή��t���[��������
                for (DWORD bone_id = 0; bone_id < dwNumBone; bone_id++) {
                    SkinAniMeshFrame* pFrame = nullptr;   // ��v�����t���[���|�C���^
                   // �{�[�������擾
                   LPCSTR skin_bone_name = pSkinInfo->GetBoneName(bone_id);
                   if (skin_bone_name) {
                       // ���O����
                       for (int fram_idx = 0; i < _vecAllBoneFrame.size(); fram_idx++) {
                           LPSTR frame_bone_name = _vecAllBoneFrame[fram_idx]->Name;
                           if (frame_bone_name) {
                               if (strcmp(skin_bone_name, frame_bone_name) == 0) { //SkinInfo�{�[������Frame�ƈ�v��v
                                   pFrame = _vecAllBoneFrame[fram_idx];
                                   break;
                               }
                           }
                       }
                       if (pFrame) {
                           _vecBoneIdFrame.push_back(pFrame);
                           pFrame->_bone_id = bone_id;
                           pFrame->_bone_offset_matrix = *(pSkinInfo->GetBoneOffsetMatrix(bone_id));
                       } else {
                           _vecBoneIdFrame.push_back(nullptr);
                       }
                   }
                }


                //DEBUG
                for (DWORD frame_idx = 0; frame_idx < _vecAllBoneFrame.size(); frame_idx++) {
                    _TRACE_("_vecAllBoneFrame["<<frame_idx<<"] Name=\""<<_vecAllBoneFrame[frame_idx]->Name<<"\" "<<
                                                              "_bone_id="<<_vecAllBoneFrame[frame_idx]->_bone_id<<" "<<
                                                              "pMeshContainer="<<_vecAllBoneFrame[frame_idx]->pMeshContainer);
                }
                _TRACE_("////////////////////////////////////");
                for (DWORD bone_id = 0; bone_id < _vecBoneIdFrame.size(); bone_id++) {
                    if (_vecBoneIdFrame[bone_id]) {
                        _TRACE_("_vecBoneIdFrame["<<bone_id<<"] = "<<_vecBoneIdFrame[bone_id]->Name<<" "<<
                                                                  "_frame_index="<<_vecBoneIdFrame[bone_id]->_frame_index<<" ");
                    } else {
                        _TRACE_("_vecBoneIdFrame["<<bone_id<<"] = nullptr"" "<<
                                "_frame_index="<<_vecBoneIdFrame[bone_id]->_frame_index<<" ");
                    }
                }

            } //for (int i = 0; i < draw_frame_num; i++) {


            //�{�[��ID���I�[�_�[�ɏ���������
            _map_infl_bone_id_to_order[0xFF] = 0xFF;
            for (DWORD i = 0; i < _vec_infl_bone_id_order.size(); i++) {
                _map_infl_bone_id_to_order[_vec_infl_bone_id_order[i]]=i;
            }

            for (int i = 0; i < _vec_infl_bone_id_order.size(); i++) {
                _TRACE_("_vec_infl_bone_id_order["<<i<<"]="<<_vec_infl_bone_id_order[i]);
            }

            //    std::map<DWORD, byte> _map_infl_bone_id_to_order;
            for (std::map<DWORD, DWORD>::iterator p = _map_infl_bone_id_to_order.begin();
                    p != _map_infl_bone_id_to_order.end(); p++) {
                    // �C�e���[�^�� pair<const string, int> �^�Ȃ̂ŁA
                    _TRACE_("_map_infl_bone_id_to_order["<<p->first<<"]="<< p->second);
            }


            //���_�o�b�t�@�̃{�[��ID���I�[�_�[�ɏ���������
            for (int i = 0; i < _nVertices; i++) {
                SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[i]);
                pVtx->infl_bone_id_order[0] = (byte)(_map_infl_bone_id_to_order[pVtx->infl_bone_id[0]]);
                pVtx->infl_bone_id_order[1] = (byte)(_map_infl_bone_id_to_order[pVtx->infl_bone_id[1]]);
                pVtx->infl_bone_id_order[2] = (byte)(_map_infl_bone_id_to_order[pVtx->infl_bone_id[2]]);
                pVtx->infl_bone_id_order[3] = (byte)(_map_infl_bone_id_to_order[pVtx->infl_bone_id[3]]);
            }


            for (int i = 0; i < _vec_infl_bone_id_order.size(); i++) {
                DWORD bone_id = _vec_infl_bone_id_order[i];
                _ap_draw_combined_matrix[i] = &(_vecBoneIdFrame[bone_id]->_combined_matrix);
            }

            ///

            /////////////////////////////////
            IDirect3DIndexBuffer9* pIb;
            pMesh->GetIndexBuffer(&pIb);
            DWORD nFace = pMesh->GetNumFaces();
            D3DINDEXBUFFER_DESC desc;
            pIb->GetDesc( &desc );
            if (desc.Format == D3DFMT_INDEX16) {
                void* pIndexBuffer;
                pIb->Lock(0, nFace*3*sizeof(WORD), (void**)&pIndexBuffer, 0);
                char* p = (char*)pIndexBuffer;
    //            _TRACE_("["<<i<<"]:IndexFmt=WORD");
                for (int f = 0; f < nFace; f++) {
                    WORD val1,val2,val3;
                    memcpy(&(val1), p, sizeof(WORD));  p += sizeof(WORD);
                    memcpy(&(val2), p, sizeof(WORD));  p += sizeof(WORD);
                    memcpy(&(val3), p, sizeof(WORD));  p += sizeof(WORD);
    //                _TRACE_("["<<i<<"]["<<f<<"]:Index=("<<val1<<","<<val2<<","<<val3<<")");
                    int offset = (v_cnt-nVertices); //���_�ԍ���ʂ��ɂ��邽�߂̌v�Z�B
                                                    //v_cnt:�ʂ��J�E���^ �� nVertices�F����̓��b�V���R���e�i�̒��_�� �Ȃ̂� 0 �ƂȂ�B
                    _paIndexBuffer_data[i_cnt+0] = offset + val1;
                    _paIndexBuffer_data[i_cnt+1] = offset + val2;
                    _paIndexBuffer_data[i_cnt+2] = offset + val3;
                    _paIndexBuffer_bone_combi_index[i_cnt+0] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+0]].bone_combi_index);
                    _paIndexBuffer_bone_combi_index[i_cnt+1] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+1]].bone_combi_index);
                    _paIndexBuffer_bone_combi_index[i_cnt+2] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+2]].bone_combi_index);
                    i_cnt+=3;
                }
            } else {
                void* pIndexBuffer;
                pIb->Lock(0, nFace*3*sizeof(DWORD), (void**)&pIndexBuffer, 0);
                char* p = (char*)pIndexBuffer;
                for (int f = 0; f < nFace; f++) {
                    WORD val1,val2,val3;
                    memcpy(&(val1), p, sizeof(WORD));  p += sizeof(DWORD);
                    memcpy(&(val2), p, sizeof(WORD));  p += sizeof(DWORD);
                    memcpy(&(val3), p, sizeof(WORD));  p += sizeof(DWORD);
                    int offset = (v_cnt-nVertices); //���_�ԍ���ʂ��ɂ��邽�߂̌v�Z�B
                                                    //v_cnt:�ʂ��J�E���^ �� nVertices�F����̓��b�V���R���e�i�̒��_�� �Ȃ̂� 0 �ƂȂ�B
                    _paIndexBuffer_data[i_cnt+0] = offset + val1;
                    _paIndexBuffer_data[i_cnt+1] = offset + val2;
                    _paIndexBuffer_data[i_cnt+2] = offset + val3;
                    _paIndexBuffer_bone_combi_index[i_cnt+0] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+0]].bone_combi_index);
                    _paIndexBuffer_bone_combi_index[i_cnt+1] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+1]].bone_combi_index);
                    _paIndexBuffer_bone_combi_index[i_cnt+2] = (int)(_paVtxBuffer_data[_paIndexBuffer_data[i_cnt+2]].bone_combi_index);
                    i_cnt += 3;
                }
            }
            pIb->Unlock();
            pIb->Release();

            //���͒������̂� Mesh��������I
            GGAF_RELEASE(pMeshContainer->MeshData.pMesh);
            pMeshContainer->MeshData.pMesh = nullptr;
        }


    ///////////////////////////////////////////////////

////////////////////////////////////////////////
        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        std::vector<SkinAniMeshModel::INDEXPARAM> param_tmp;

        int paramno = 0;

        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;

        int frame_no = 0;
        int prev_frame_no = -1;

        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;
        UINT vtx_idx1,vtx_idx2,vtx_idx3;
        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < _nFaces; faceNoCnt++) {
            frame_no = _paIndexBuffer_bone_combi_index[faceNoCnt*3 + 0]; //faceNoCnt(�ʔԍ�)�ɑ΂��钸�_�̑�����t���[�����b�V���ʂ��ԍ�
            if ((frame_no % SkinAniMeshModel_MAX_BONE_WORLD_MATRIX) == 0 && frame_no != prev_frame_no) {
//                _TRACE_("BREAK! frame_no="<<frame_no);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                param_tmp.push_back(SkinAniMeshModel::INDEXPARAM());
                param_tmp[paramno].MaterialNo = 0;
                param_tmp[paramno].BaseVertexIndex = 0;
                param_tmp[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�K���u���C�N���������ߕςȒl�ɂ��Ƃ�
                param_tmp[paramno].NumVertices = UINT_MAX; //����u���C�N���ɐݒ�
                param_tmp[paramno].StartIndex = faceNoCnt*3;
                param_tmp[paramno].PrimitiveCount = UINT_MAX; //����u���C�N���ɐݒ�

                if (faceNoCnt > 0) {
                    param_tmp[paramno-1].MinIndex = min_num_vertices;
                    param_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    param_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //���Z�b�g
                    max_num_vertices = 0;
                    min_num_vertices = UINT_MAX;
                }
                paramno++;
            }
            vtx_idx1 = _paIndexBuffer_data[faceNoCnt*3 + 0]; //faceNoCnt(�ʔԍ�)�ɑ΂��钸�_�ԍ�
            vtx_idx2 = _paIndexBuffer_data[faceNoCnt*3 + 1];
            vtx_idx3 = _paIndexBuffer_data[faceNoCnt*3 + 2];

            if (max_num_vertices < vtx_idx1) {
                max_num_vertices = vtx_idx1;
            }
            if (max_num_vertices < vtx_idx2) {
                max_num_vertices = vtx_idx2;
            }
            if (max_num_vertices < vtx_idx3) {
                max_num_vertices = vtx_idx3;
            }

            if (min_num_vertices > vtx_idx1) {
                min_num_vertices = vtx_idx1;
            }
            if (min_num_vertices > vtx_idx2) {
                min_num_vertices = vtx_idx2;
            }
            if (min_num_vertices >  vtx_idx3) {
                min_num_vertices = vtx_idx3;
            }
            prev_frame_no = frame_no;
        }
        if (_nFaces > 0) {
            param_tmp[paramno-1].MinIndex = min_num_vertices;
            param_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            param_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }
        _index_param_num = paramno;
        _paIndexParam = NEW SkinAniMeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            _paIndexParam[i].MaterialNo      = param_tmp[i].MaterialNo;
            _paIndexParam[i].BaseVertexIndex = param_tmp[i].BaseVertexIndex;
            _paIndexParam[i].MinIndex        = param_tmp[i].MinIndex;
            _paIndexParam[i].NumVertices     = param_tmp[i].NumVertices;
            _paIndexParam[i].StartIndex      = param_tmp[i].StartIndex;
            _paIndexParam[i].PrimitiveCount  = param_tmp[i].PrimitiveCount;
        }
        _size_vertices = _size_vertex_unit * _nVertices;

        _TRACE_("�܂Ƃ߁I");
        for (int i = 0; i < _nVertices; i++) {
            SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[i]); //��������1���_�̊J�n�A�h���X
            _TRACE_("["<<i<<"]:"<<
                    " ["<<(pVtx->bone_combi_index)<<"] "<<
                    " Vertex=("<<(pVtx->x)<<","<<(pVtx->y)<<","<<(pVtx->z)<<")"<<
                    " infl_bone_id=("<<(int)(pVtx->infl_bone_id[0])<<","<<(int)(pVtx->infl_bone_id[1])<<","<<(int)(pVtx->infl_bone_id[2])<<","<<(int)(pVtx->infl_bone_id[3])<<")"<<
                    " infl_bone_id_order=("<<(int)(pVtx->infl_bone_id_order[0])<<","<<(int)(pVtx->infl_bone_id_order[1])<<","<<(int)(pVtx->infl_bone_id_order[2])<<","<<(int)(pVtx->infl_bone_id_order[3])<<")"<<
                    " infl_weight=("<<(pVtx->infl_weight[0])<<","<<(pVtx->infl_weight[1])<<","<<(pVtx->infl_weight[2])<<","<<(pVtx->infl_weight[3])<<")"<<
                    " Normal=("<<(pVtx->nx)<<","<<(pVtx->ny)<<","<<(pVtx->nz)<<")"

            );
        }
//        for (int i = 0; i < _nFaces; ++i) {
//            _TRACE_("["<<i<<"]:Index=("<<(_paIndexBuffer_data[i*3+0])<<","<<
//                    (_paIndexBuffer_data[i*3+1])<<","<<
//                    (_paIndexBuffer_data[i*3+2])<<")");
//        }

    } //if (_paVtxBuffer_data == nullptr)



    if (_pVertexDeclaration == nullptr) {
        HRESULT hr;
        //D3DVERTEXELEMENT9 �\���̂̔z��v�f��
        D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[9];
        WORD  st0_offset_next = 0;
        //�v���C�}�������_�t�H�[�}�b�g
        //float x, y, z; // ���_���W
        paVtxelem[0].Stream = 0;
        paVtxelem[0].Offset = st0_offset_next;
        paVtxelem[0].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[0].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[0].Usage = D3DDECLUSAGE_POSITION;
        paVtxelem[0].UsageIndex = 0;
        st0_offset_next += sizeof(float)*3;
        //float nx, ny, nz; // �@��
        paVtxelem[1].Stream = 0;
        paVtxelem[1].Offset = st0_offset_next;
        paVtxelem[1].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[1].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[1].Usage = D3DDECLUSAGE_NORMAL;
        paVtxelem[1].UsageIndex = 0;
        st0_offset_next += sizeof(float)*3;
        //float index;
        paVtxelem[2].Stream = 0;
        paVtxelem[2].Offset = st0_offset_next;
        paVtxelem[2].Type = D3DDECLTYPE_FLOAT1;
        paVtxelem[2].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[2].Usage = D3DDECLUSAGE_PSIZE;
        paVtxelem[2].UsageIndex = 0;
        st0_offset_next += sizeof(float)*1;
        //DWORD color; // ���_�J���[
        paVtxelem[3].Stream = 0;
        paVtxelem[3].Offset = st0_offset_next;
        paVtxelem[3].Type = D3DDECLTYPE_D3DCOLOR;
        paVtxelem[3].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[3].Usage = D3DDECLUSAGE_COLOR;
        paVtxelem[3].UsageIndex = 0;
        st0_offset_next += sizeof(DWORD);
        //float tu, tv; // �e�N�X�`�����W
        paVtxelem[4].Stream = 0;
        paVtxelem[4].Offset = st0_offset_next;
        paVtxelem[4].Type = D3DDECLTYPE_FLOAT2;
        paVtxelem[4].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[4].Usage = D3DDECLUSAGE_TEXCOORD;
        paVtxelem[4].UsageIndex = 0;
        st0_offset_next += sizeof(float)*2;
        //float infl_weight[4];
        paVtxelem[5].Stream = 0;
        paVtxelem[5].Offset = st0_offset_next;
        paVtxelem[5].Type = D3DDECLTYPE_FLOAT4;
        paVtxelem[5].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[5].Usage = D3DDECLUSAGE_BLENDWEIGHT;
        paVtxelem[5].UsageIndex = 0;
        st0_offset_next += sizeof(float)*4;
        // byte  infl_bone_id[4];
        paVtxelem[6].Stream = 0;
        paVtxelem[6].Offset = st0_offset_next;
        paVtxelem[6].Type = D3DDECLTYPE_UBYTE4;
        paVtxelem[6].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[6].Usage = D3DDECLUSAGE_BLENDINDICES;
        paVtxelem[6].UsageIndex = 0;
        st0_offset_next += sizeof(byte)*4;
        // byte  infl_bone_id_order[4];
        paVtxelem[7].Stream = 0;
        paVtxelem[7].Offset = st0_offset_next;
        paVtxelem[7].Type = D3DDECLTYPE_UBYTE4;
        paVtxelem[7].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[7].Usage = D3DDECLUSAGE_BLENDINDICES;
        paVtxelem[7].UsageIndex = 1;
        st0_offset_next += sizeof(byte)*4;
        //D3DDECL_END()
        paVtxelem[8].Stream = 0xFF;
        paVtxelem[8].Offset = 0;
        paVtxelem[8].Type = D3DDECLTYPE_UNUSED;
        paVtxelem[8].Method = 0;
        paVtxelem[8].Usage = 0;
        paVtxelem[8].UsageIndex = 0;

        hr = God::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "God::_pID3DDevice9->CreateVertexDeclaration ���s model="<<(_model_name));
        //�X�g���[�����擾        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);
        GGAF_DELETEARR(paVtxelem);
    }


    if (_papTextureConnection == nullptr) {
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        TextureManager* pTextureManager = pGOD->_pModelManager->_pModelTextureManager;
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    if (_pVertexBuffer == nullptr) {
        HRESULT hr;
        //���_�o�b�t�@�쐬
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                0, //SkinAniMeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
        memcpy(pVertexBuffer, _paVtxBuffer_data, _size_vertices); //pVertexBuffer �� paVertex
        _pVertexBuffer->Unlock();
    }

    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (_pIndexBuffer == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateIndexBuffer(
                                   sizeof(WORD) * _nFaces * 3,
                                   D3DUSAGE_WRITEONLY,
                                   D3DFMT_INDEX16,
                                   D3DPOOL_DEFAULT,
                                   &(_pIndexBuffer),
                                   nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_name));
        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , _paIndexBuffer_data , sizeof(WORD) * _nFaces * 3);
        _pIndexBuffer->Unlock();
    }
    _TRACE3_("_model_name=" << _model_name << " end");
}

ID3DXAnimationController* SkinAniMeshModel::getCloneAnimationController() {
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
//int SkinAniMeshModel::getAnimTicksPerSecond(std::string& prm_xfile_name) {
//    if (prm_xfile_name == "") {
//         throwCriticalException("SkinAniMeshModel::getAnimTicksPerSecond() ���b�V���t�@�C��("<<prm_xfile_name<<".x)��������܂���B");
//    }
//    //X�t�@�C������AnimTicksPerSecond�̒l��Ǝ��Ɏ��o��
//    std::ifstream ifs(prm_xfile_name.c_str());
//    if (ifs.fail()) {
//        throwCriticalException("["<<prm_xfile_name<<"] ���J���܂���");
//    }
//    std::string buf;
//    bool isdone = false;
//    int anim_ticks_per_second = -1;
//    std::string data;
//    while (isdone == false && !ifs.eof()) {
//        ifs >> data;
//        if (data == "AnimTicksPerSecond" || data == "AnimTicksPerSecond{") {
//            while (isdone == false) {
//                ifs >> data;
//                if (data == "{") {
//                    continue;
//                } else if (data == "}") {
//                    isdone = true;
//                    break;
//                } else {
//                    anim_ticks_per_second = atoi(data.c_str()); //"60;" �� 60�𓾂�
//                    if (anim_ticks_per_second == 0) {
//                        //���l�ɕϊ��ł��Ȃ��ꍇ�͖���
//                        anim_ticks_per_second = -1;
//                        isdone = false;
//                    } else {
//                        isdone = true;
//                    }
//                    break;
//                }
//            }
//        }
//    }
//    ifs.close();
//    return anim_ticks_per_second;
//}

void SkinAniMeshModel::setFrameInfo(SkinAniMeshFrame* prm_pFrame) {
    prm_pFrame->_frame_index = _tmp_frame_index; //�t���[���C���f�b�N�X��ێ�
    _tmp_frame_index++;

    _vecAllBoneFrame.push_back(prm_pFrame);
    if (prm_pFrame->pMeshContainer) {
        //���b�V���R���e�i�L��
        _vecDrawBoneFrame.push_back(prm_pFrame);
    }
    if (prm_pFrame->pFrameFirstChild) {
        // �q�t���[���L��
        setFrameInfo((SkinAniMeshFrame*)prm_pFrame->pFrameFirstChild);
    }
    if (prm_pFrame->pFrameSibling) {
        //�Z��t���[���L��
        setFrameInfo((SkinAniMeshFrame*)prm_pFrame->pFrameSibling);
    }
}
int SkinAniMeshModel::getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage ) {
    D3DVERTEXELEMENT9 *e = elems;
    while( e->Stream != 0xff ) {
        if ( e->Usage == usage )
            return (int)(e->Offset);
        e = e + 1;
    }
    return -1;
}

void SkinAniMeshModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void SkinAniMeshModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //�e�N�X�`���̔z��
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);
    _TRACE3_("_model_name=" << _model_name << " end");
}

SkinAniMeshModel::~SkinAniMeshModel() {
    for (UINT ani_set_index = 0; ani_set_index < _num_animation_set; ani_set_index++) {
        bool* p = _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index];
        GGAF_DELETEARR(p);
    }
    GGAF_DELETEARR(_papaBool_AnimationSetIndex_BoneFrameIndex_is_act);

    GGAF_RELEASE(_pAniControllerBase);
    _pAllocHierarchy->DestroyFrame((D3DXFRAME*)_pFrameRoot);
    GGAF_DELETE(_pAllocHierarchy);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames); //Model::~Model() �Ŏ��s����Ă�͂�
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_bone_combi_index);
    GGAF_DELETEARR(_paIndexParam);
//    GGAF_DELETE(_pFrameRoot); //_pAllocHierarchy��������_pFrameRoot�͏����Ȃ��ėǂ��Ǝv��
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}
