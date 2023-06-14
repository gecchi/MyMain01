#include "jp/ggaf/dx/model/SkinAniMeshModel.h"

#include <algorithm>
#include "jp/ggaf/dx/Caretaker.h"
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
#include <D3dx9math.h>

using namespace GgafDx;

SkinAniMeshModel::SkinAniMeshModel(const char* prm_model_id) : Model(prm_model_id) {
    _obj_class |= Obj_GgafDx_SkinAniMeshModel;
    _pAllocHierarchy = nullptr;
    _pFrameRoot = nullptr;
    _pAniControllerBase = nullptr;
    _num_materials = 0L;
    _paVtxBuffer_data = nullptr;
    _paIndex32Buffer_data = nullptr;
    _paIndex16Buffer_data = nullptr;
    _pVertexDeclaration = nullptr;
    _paVertexBuffer = nullptr;
    _paIndexBuffer = nullptr;
    _index_param_num = 0;
    _paIndexParam = nullptr;
    _draw_combined_matrix_set_num = 15;
    _size_vertices = 0;
    _size_vertex_unit = sizeof(SkinAniMeshModel::VERTEX);
    _nFaces = 0;
    _nVertices = 0;
    _tmp_frame_index = 0;
    _num_animation_set = 0;
    _papaBool_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _max_draw_set_num = 1;
    _indexBuffer_fmt = D3DFMT_UNKNOWN;
}

HRESULT SkinAniMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("SkinAniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    HRESULT hr;
    //�ΏۃA�N�^�[
    SkinAniMeshActor* pTargetActor = (SkinAniMeshActor*)prm_pActor_target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    SkinAniMeshEffect* pSkinAniMeshEffect = (SkinAniMeshEffect*)(prm_pActor_target->getEffect());
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pSkinAniMeshEffect->_pID3DXEffect;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //���_�t�H�[�}�b�g
        pDevice->SetStreamSource(0, _paVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetIndices(_paIndexBuffer);
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSkinAniMeshEffect->_h_fog_starts_far_rate, _fog_starts_far_rate);
        checkDxException(hr, D3D_OK, "SetFloat(_h_fog_starts_far_rate) �Ɏ��s���܂����B");
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
    ID3DXAnimationSet* pAs0 = pActorPuppeteer->_apAs[0];
    ID3DXAnimationSet* pAs1 = pActorPuppeteer->_apAs[1];
    int as0_index = pAs0 ? (int)_mapAnimationSet_AniSetindex[pAs0] : -1;
    int as1_index = pAs1 ? (int)_mapAnimationSet_AniSetindex[pAs1] : -1;
    pTargetActor->_stackWorldMat.UpdateFrame(&_matBaseTransformMatrix, _pFrameRoot, as0_index, as1_index, _papaBool_AnimationSetIndex_BoneFrameIndex_is_act);

    std::vector<SkinAniMeshFrame*>::iterator it_1 = _vecBoneIdFrame.begin();

    for (int i = 0; i < _index_param_num; i++) { //i = prev_bone_combi_grp_index

        BoneConbiGrp& bcg_info = _vec_bone_combi_grp_info[i];
        for (int j = 0; j < bcg_info.vec_infl_bone_id_order.size(); j++) {
            DWORD bone_id = bcg_info.vec_infl_bone_id_order[j];
            hr = pID3DXEffect->SetMatrix(pSkinAniMeshEffect->_ah_matBone[j],  &(_vecBoneIdFrame[bone_id]->_combined_matrix));
        }

        const INDEXPARAM& idxparam = _paIndexParam[i];

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
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pSkinAniMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pSkinAniMeshEffect->_effect_name<<"("<<pSkinAniMeshEffect<<")");
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

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_draw++;
#endif
    }
    //�O��`�惂�f�������f
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pSkinAniMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void SkinAniMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        obtainMetaModelInfo(&xdata);
        if (_draw_set_num != 1) {
            _TRACE_("SkinAniMeshModel::restore() �{���f���� "<<_model_id<<" �̓����`��Z�b�g���͏�� 1 �ł��B�i_draw_set_num="<<_draw_set_num<<" �͖�������܂����B�j");
            _draw_set_num = 1;
        }

        struct VERTEX_EX {
            float bone_combi_grp_index; //�{�[���R���r�l�[�V�����̃O���[�v�̃C���f�b�N�X
            byte  infl_bone_id[4];      //�{�[��ID
        };
        struct BoneConbi {
            DWORD vertex_start;
            DWORD vertex_count;
        };

        HRESULT hr;
        std::string xfilepath = Model::getMeshXFilePath(xdata.XFileNames[0]);
        //X�t�@�C���̃t�@�C�����[�h
        _pAllocHierarchy = NEW SkinAniMeshAllocHierarchy(); // CAllocHierarchyBase�̔h���N���X
        hr = D3DXLoadMeshHierarchyFromX(
                xfilepath.c_str(),
                D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
                pCARETAKER->_pID3DDevice9,
                _pAllocHierarchy,
                nullptr,
                (D3DXFRAME**)(&_pFrameRoot),
                &_pAniControllerBase
             );
        _TRACE_("_pAllocHierarchy="<<_pAllocHierarchy<<" _pFrameRoot="<<_pFrameRoot<<" _pAniControllerBase="<<_pAniControllerBase<<" xfile_name.c_str()="<<xfilepath.c_str());
        checkDxException(hr, D3D_OK, xfilepath<<" �ǂݍ��݂Ɏ��s���܂����B�Ώ�="<<xfilepath);
        if (_pFrameRoot == nullptr) {
            throwCriticalException(xfilepath<<" �̃t���[����񂪎擾�ł��܂���I");
        }
        //_vecAllBoneFrame, _vecDrawBoneFrame �y�� _tmp_frame_index ��ݒ�B
        _vecDrawBoneFrame.clear(); // _pFrameRoot �������ĕ`��Ώۂ�����t���[���𒼗񉻂������́A�v�f�ԍ��͂����̘A��
        _vecAllBoneFrame.clear();  // _pFrameRoot �������ăt���[���𒼗񉻂������́A�v�f�ԍ��̓t���[���C���f�b�N�X�ƌď̂���
        _tmp_frame_index = 0;
        setFrameInfo(_pFrameRoot); //�t���[���������������o�ɃZ�b�g

        setAnimationFrameIndex(); //_mapAnimationSet_AniSetindex, _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[][] ��ݒ�

        //���E��
        D3DXVECTOR3 vecCenter;
        FLOAT bounding_sphere_radius;
        D3DXFrameCalculateBoundingSphere((D3DXFRAME*)_pFrameRoot, &vecCenter, &bounding_sphere_radius);
        _bounding_sphere_radius = UTIL::getDistance(0.0f, 0.0f, 0.0f, vecCenter.x, vecCenter.y, vecCenter.z) + bounding_sphere_radius;

        int draw_frame_num = _vecDrawBoneFrame.size();
        int materials_total_num = 0;
        int vertices_total_num = 0;
        int faces_total_num = 0;

        //�`��Ώۃt���[�����X�g������āA���_�����擾
        for (int draw_frame_idx = 0; draw_frame_idx < draw_frame_num; draw_frame_idx++) {
            SkinAniMeshContainer* pMeshContainer = (SkinAniMeshContainer*)(_vecDrawBoneFrame[draw_frame_idx]->pMeshContainer);
            if (pMeshContainer == nullptr) {
                continue;
            }
            ID3DXMesh* pMesh = pMeshContainer->MeshData.pMesh;
            if (!pMesh) {
                continue;
            }
            vertices_total_num += (int)(pMesh->GetNumVertices());  // ���_��
            faces_total_num += (int)(pMesh->GetNumFaces());        // �|���S����
            materials_total_num += (int)(pMeshContainer->NumMaterials); //�}�e���A����
        }

        //���_�����i�z�񐔁j������Ɖ������̂ō쐬
        _num_materials = materials_total_num;
        _nVertices = vertices_total_num;
        _nFaces = faces_total_num;
        _paVtxBuffer_data =  NEW SkinAniMeshModel::VERTEX[_nVertices];
        VERTEX_EX* paVtx_wk = NEW VERTEX_EX[_nVertices];
        _indexBuffer_fmt = D3DFMT_UNKNOWN;

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
        _vec_bone_combi_grp_info.clear();
        int m_cnt = 0;   //�}�e���A���Ɖ����J�E���^�[
        int vtx_idx_thru = 0;   //���_�o�b�t�@�ʂ��J�E���^�[
        int i_cnt = 0;   //�C���f�b�N�X�o�b�t�@�ʂ��J�E���^�[
        char* texture_filename;
        D3DVERTEXELEMENT9 e[MAX_FVF_DECL_SIZE];
        //�`��Ώۃt���[���Ń��[�v�I
        for (int draw_frame_idx = 0; draw_frame_idx < draw_frame_num; draw_frame_idx++) {
            int vtx_idx_frame_start = vtx_idx_thru;

            SkinAniMeshContainer* pMeshContainer = (SkinAniMeshContainer*)(_vecDrawBoneFrame[draw_frame_idx]->pMeshContainer);
            if (pMeshContainer == nullptr) {
                continue;
            }
            ID3DXMesh* pMesh1 = pMeshContainer->MeshData.pMesh;
            if (!pMesh1) {
                continue;
            }
            int nMaterials = (int)(pMeshContainer->NumMaterials);
            for (int n = 0; n < nMaterials; n++) {
                if (pMeshContainer->pMaterials) {
                    _paMaterial_default[m_cnt] = pMeshContainer->pMaterials[n].MatD3D; //�}�e���A�����R�s�[
                    texture_filename = pMeshContainer->pMaterials[n].pTextureFilename;
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

            //D3DXLoadMeshHierarchyFromX() �œǂݍ��܂ꂽ���_���(pMeshContainer->MeshData.pMesh)��
            //_paVtxBuffer_data �ɐݒ�
            pMesh1->GetDeclaration( e );
            int offset_position  = getOffsetFromElem( e, D3DDECLUSAGE_POSITION );
            int offset_normal    = getOffsetFromElem( e, D3DDECLUSAGE_NORMAL );
            int offset_texcoord  = getOffsetFromElem( e, D3DDECLUSAGE_TEXCOORD );

            IDirect3DVertexBuffer9* pVb_load;
            pMesh1->GetVertexBuffer(&pVb_load);
            DWORD size_vertex_unit = pMesh1->GetNumBytesPerVertex(); // 1�̒��_�̃T�C�Y
            void* pVb_load_begin;
            int nVertices = (int)(pMesh1->GetNumVertices()); //���b�V���R���e�i�̒��_��
            pVb_load->Lock(0, nVertices*size_vertex_unit, (void**)&pVb_load_begin, 0);
            for (int vi = 0; vi < nVertices; vi++) {
                char* p = nullptr;
                SkinAniMeshModel::VERTEX*    pVtx_data    = &(_paVtxBuffer_data[vtx_idx_thru]); //��������1���_�̊J�n�A�h���X
                VERTEX_EX* pVtx_data_ex = &(paVtx_wk[vtx_idx_thru]);
                char* pVb_load_base = (char*)pVb_load_begin + (size_vertex_unit*vi);  //�ǂݍ���1���_�̊J�n�A�h���X
                //    float x, y, z;    // ���_���W
                p = pVb_load_base + offset_position;
                memcpy(&(pVtx_data->x), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                memcpy(&(pVtx_data->y), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                memcpy(&(pVtx_data->z), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                //Normal  float nx, ny, nz; // �@��
                if (offset_normal > 0) {
                    p = pVb_load_base + offset_normal;
                    memcpy(&(pVtx_data->nx), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx_data->ny), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx_data->nz), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                } else {
                    pVtx_data->nx = 0.0f;
                    pVtx_data->ny = 0.0f;
                    pVtx_data->nz = 0.0f;
                }
                pVtx_data_ex->bone_combi_grp_index = -999; // ���ݒ�A���ōĐݒ肷��
                //�Đݒ�̏ꏊ�u���_�o�b�t�@�� infl_bone_id_order �� bone_id ����ϊ����Đݒ�v�̏���

                //DWORD color ; //���_�J���[
                pVtx_data->color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[

                //float tu, tv;     // �e�N�X�`�����W
                if (offset_texcoord > 0) {
                    p = pVb_load_base + offset_texcoord;
                    memcpy(&(pVtx_data->tu), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                    memcpy(&(pVtx_data->tv), p, sizeof(FLOAT));  p += sizeof(FLOAT);
                } else {
                    pVtx_data->tu = 0.0f;
                    pVtx_data->tv = 0.0f;
                }
                for (int k = 0; k < 4; k++) {  // ���ŏ����l�ݒ�A���ōĐݒ肷��
                    pVtx_data->infl_weight[k] = 0.0f;
                    pVtx_data_ex->infl_bone_id[k] = 0xFF;
                    pVtx_data->infl_bone_id_order[k] = 0xFF;
                }
                vtx_idx_thru ++;
            }
            pVb_load->Unlock();
            pVb_load->Release();

            /////////////
            //skin���infl_bone_id �� iinfl_weight �̂悤�ȁA���_�ɕt����������擾
            int bc_through_idx = 0;
//            _TRACE_("draw_frsme["<<draw_frame_idx<<"]: idx="<<_vecDrawBoneFrame[draw_frame_idx]->_frame_index<<", name="<<_vecDrawBoneFrame[draw_frame_idx]->Name<<"");
//            _TRACE_("pMeshContainer->_dwMaxInfleNum = "<<pMeshContainer->_dwMaxInfleNum);
//            _TRACE_("pMeshContainer->_dwBoneCombNum = "<<pMeshContainer->_dwBoneCombNum);
            LPD3DXSKININFO pSkinInfo = pMeshContainer->pSkinInfo; //_vecDrawBoneFrame[] �O�� skin��񂪂���͂�
            D3DXBONECOMBINATION* paBoneCombination =
                    (D3DXBONECOMBINATION*)(pMeshContainer->_pBoneCombinationTable->GetBufferPointer());
            //�t���[�����b�V�����e������{�[���̃R���r�l�[�V�������Ń��[�v
            std::vector<BoneConbi> vec_bone_combi_info;
            for (DWORD bc_idx = 0; bc_idx < pMeshContainer->_dwBoneCombNum; ++bc_idx, ++bc_through_idx) { //bc_idx�̓��b�V���T�u�Z�b�gID
                D3DXBONECOMBINATION* pBoneCombination = &(paBoneCombination[bc_idx]);
                BoneConbi bc_info;
                bc_info.vertex_start = pBoneCombination->VertexStart + vtx_idx_frame_start; //vtx_idx_frame_start �͕����t���[���Ƀ��b�V�����������ꍇ�̃I�t�Z�b�g
                bc_info.vertex_count = pBoneCombination->VertexCount;
                vec_bone_combi_info.push_back(bc_info);
//                _TRACE_("paBoneCombination["<<bc_idx<<"] = "<<
//                        " AttribId="<<pBoneCombination->AttribId<<
//                        " FaceStart="<<pBoneCombination->FaceStart<<
//                        " FaceCount="<<pBoneCombination->FaceCount<<
//                        " VertexStart="<<pBoneCombination->VertexStart<<
//                        " VertexCount="<<pBoneCombination->VertexCount<<
//                        ""
//                );
                for (DWORD infl_id = 0; infl_id < pMeshContainer->_dwMaxInfleNum; ++infl_id) { //_dwMaxInfleNum = 4
                    DWORD bone_id = pBoneCombination->BoneId[infl_id]; //0,1,2,3 �� �e�����y�ڂ� bone_id ������
                    DWORD bone_influ_vertices_num = pSkinInfo->GetNumBoneInfluences(bone_id); // �e�����y�ڂ����_��

//_TRACE_("paBoneCombination["<<bc_idx<<"].BoneId["<<infl_id<<"]="<<bone_id<<" bone_influ_vertices_num="<<bone_influ_vertices_num);

                    if (bone_influ_vertices_num > 0) {

                        DWORD* vertices = new DWORD[bone_influ_vertices_num];
                        float* skin_weight  = new float[bone_influ_vertices_num];
                        pSkinInfo->GetBoneInfluence(bone_id, vertices, skin_weight); // �e�����y�ڂ����_�Əd�݂��擾
                        //���_�ɏ��i_paVtxBuffer_data�j�ɏ���ǋL���Ă���
                        for (DWORD v = 0; v < bone_influ_vertices_num; v++) {
                            if (skin_weight[v] > 0.0) {
                                SkinAniMeshModel::VERTEX*    pVtx_data    = &(_paVtxBuffer_data[vertices[v] + vtx_idx_frame_start]);
                                VERTEX_EX* pVtx_data_ex = &(paVtx_wk[vertices[v] + vtx_idx_frame_start]);
                                bool is_exist = false;
                                for (int k = 0; k < 4; k++) {
                                    if (pVtx_data_ex->infl_bone_id[k] == (byte)bone_id) {
                                        is_exist = true;
                                        break;
                                    }
                                }
                                if (is_exist == false) {
                                    for (int k = 0; k < 4; k++) {
                                        if (pVtx_data->infl_weight[k] < skin_weight[v]) { //weight�傫������
                                            for (int j = 3; j > k; j--) {
                                                //�X���C�h
                                                pVtx_data_ex->infl_bone_id[j] = pVtx_data_ex->infl_bone_id[j-1];
                                                pVtx_data->infl_weight[j] = pVtx_data->infl_weight[j-1];
                                            }
                                            pVtx_data_ex->infl_bone_id[k] = (byte)bone_id;
                                            pVtx_data->infl_weight[k] =  skin_weight[v];
                                            break;
                                        }
                                    }

                                }
                            }
                        } //for (DWORD v = 0; v < bone_influ_vertices_num; v++)
                        //�f�o�b�O
//                        _TRACE_N_("Vertices=");
//                        for (int v = 0; v < bone_influ_vertices_num; v++) {
//                            _TRACE_N_("\t"<<vertices[v]<<"");
//                        }
//                        _TRACE_N_("\n");
//                        _TRACE_N_("Weights=");
//                        for (int v = 0; v < bone_influ_vertices_num; v++) {
//                            _TRACE_N_("\t"<<skin_weight[v]<<"");
//                        }
//                        _TRACE_N_("\n");
                    }
                }
            } //for (DWORD bc_idx = 0; bc_idx < pMeshContainer->_dwBoneCombNum; ++bc_idx, ++bc_through_idx)

            //�{�[��ID��Frame�̕R�t����_bone_offset_matrix�̕ێ�
            DWORD dwNumBone = pSkinInfo->GetNumBones();  // �{�[���̐����擾
            // �{�[���̐������Ή��t���[��������
            for (DWORD bone_id = 0; bone_id < dwNumBone; bone_id++) {
                SkinAniMeshFrame* pFrame = nullptr;   // ��v�����t���[���|�C���^
               // �{�[�������擾
               LPCSTR skin_bone_name = pSkinInfo->GetBoneName(bone_id);
               if (skin_bone_name) {
                   // ���O����
                   for (int fram_idx = 0; fram_idx < _vecAllBoneFrame.size(); fram_idx++) {
                       LPSTR frame_bone_name = _vecAllBoneFrame[fram_idx]->Name;
                       if (frame_bone_name) {
                           if (strcmp(skin_bone_name, frame_bone_name) == 0) { //SkinInfo�{�[������Frame�ƈ�v��v
                               pFrame = _vecAllBoneFrame[fram_idx];
                               break;
                           }
                       }
                   }
                   if (pFrame) {
                       if (_vecBoneIdFrame.size() < bone_id+1) {
                           _vecBoneIdFrame.push_back(pFrame);
                       } else {
                           _vecBoneIdFrame[bone_id] = pFrame;
                       }
                       pFrame->_bone_id = bone_id;
                       pFrame->_bone_offset_matrix = *(pSkinInfo->GetBoneOffsetMatrix(bone_id));
                   } else {
                       if (_vecBoneIdFrame.size() < bone_id+1) {
                           _vecBoneIdFrame.push_back(nullptr);
                       }
                   }
               }
            }


            //DEBUG
//            for (DWORD frame_idx = 0; frame_idx < _vecAllBoneFrame.size(); frame_idx++) {
//                _TRACE_("_vecAllBoneFrame["<<frame_idx<<"] Name=\""<<_vecAllBoneFrame[frame_idx]->Name<<"\" "<<
//                                                          "_bone_id="<<_vecAllBoneFrame[frame_idx]->_bone_id<<" "<<
//                                                          "pMeshContainer="<<_vecAllBoneFrame[frame_idx]->pMeshContainer);
//            }
//            _TRACE_("////////////////////////////////////");
//            for (DWORD bone_id = 0; bone_id < _vecBoneIdFrame.size(); bone_id++) {
//                if (_vecBoneIdFrame[bone_id]) {
//                    _TRACE_("_vecBoneIdFrame["<<bone_id<<"] = "<<_vecBoneIdFrame[bone_id]->Name<<" "<<
//                                                              "_frame_index="<<_vecBoneIdFrame[bone_id]->_frame_index<<" ");
//                } else {
//                    _TRACE_("_vecBoneIdFrame["<<bone_id<<"] = nullptr"" "<<
//                            "_frame_index="<<_vecBoneIdFrame[bone_id]->_frame_index<<" ");
//                }
//            }

            std::vector<DWORD> vec_infl_bone_id_order; //���j�[�N��vec_cb_idx_order���}������Ă���
            std::vector<DWORD> vec_cb_idx_order;       //vec_infl_bone_id_order ���}�����ꂽ����
            int grp_cb_vertex_start = 0;
            int grp_cb_vertex_count = 0;
            bool is_break = false;
            int cb_vertex_start;
            int cb_vertex_count;
            //�{�[���R���r�l�[�V���������������A�{�[���R���r�l�[�V�����O���[�v��ǋL
//_TRACE_("�{�[���R���r�l�[�V�����Ń��[�v  vec_bone_combi_info.size()="<< vec_bone_combi_info.size()<<"!!!!!!!!!!!!!!!!!!!!!");
            int bone_cb_idx;
            for (bone_cb_idx = 0; bone_cb_idx < vec_bone_combi_info.size(); bone_cb_idx ++) {
//_TRACE_("bone_cb_idx="<<bone_cb_idx<<"  ���[�v�͂��� bone_cb_idx="<<bone_cb_idx<<"");
                BoneConbi* bone_cb = &(vec_bone_combi_info[bone_cb_idx]);
                cb_vertex_start = bone_cb->vertex_start;
                cb_vertex_count = bone_cb->vertex_count;

                //����A�܂��̓u���C�N������̍ŏ��̃��[�v�̐ݒ�
                if (bone_cb_idx == 0 || is_break == true) {
//_TRACE_("bone_cb_idx="<<bone_cb_idx<<" ����A�܂��̓u���C�N������̍ŏ��̃��[�v�̐ݒ���s bone_cb_idx="<<bone_cb_idx<<" ����ݒ�I�I�I");
                    vec_infl_bone_id_order.clear();
                    vec_cb_idx_order.clear();
                    grp_cb_vertex_start = cb_vertex_start;
                    grp_cb_vertex_count = 0;
                    is_break = false;
                }

                //�{�[���R���r�l�[�V�����̒��_�o�b�t�@�Ń��[�v
                for (int v_idx = cb_vertex_start; v_idx < cb_vertex_start+cb_vertex_count; v_idx++) {
                    SkinAniMeshModel::VERTEX* pVtx_data = &(_paVtxBuffer_data[v_idx]);
                    VERTEX_EX* pVtx_data_ex = &(paVtx_wk[v_idx]);
                    for (int i = 0; i < 4; i++) {
                        byte infl_bone_id = pVtx_data_ex->infl_bone_id[i];
                        if (infl_bone_id == 0xFF) {
                            break;
                        } else {
                            //vec_infl_bone_id_order �� infl_bone_id �����o�^�Ȃ�o�^
                            std::vector<DWORD>::iterator p = std::find(
                                    vec_infl_bone_id_order.begin(),
                                    vec_infl_bone_id_order.end(),
                                    infl_bone_id);
                            if (p == vec_infl_bone_id_order.end()) {
                                //���݂��Ȃ������߂Ă� infl_bone_id
                                if (vec_infl_bone_id_order.size() >= _draw_combined_matrix_set_num) {
                                    //_draw_combined_matrix_set_num �𒴉߂�����A
                                    //���� �{�[���R���r�l�[�V�����܂ł���x�ɕ`�揈������͖̂���������̂�
                                    //�ЂƂO�̃{�[���R���r�l�[�V�����܂ł��ꊇ�`��ΏۂƂ���B
//                                    _TRACE_("bone_cb_idx="<<bone_cb_idx<<"  is_break!!!!!!!!!!!! ");
                                    is_break = true;
                                    break;
                                } else {
//                                    _TRACE_("bone_cb_idx="<<bone_cb_idx<<" : vec_cb_idx_order.push_back("<<(int)bone_cb_idx<<");  vec_infl_bone_id_order.push_back("<<(int)infl_bone_id<<");");
                                    vec_cb_idx_order.push_back(bone_cb_idx);
                                    vec_infl_bone_id_order.push_back(infl_bone_id);
                                }
                            } else {
                                //_TRACE_("bone_cb_idx="<<bone_cb_idx<<"  infl_bone_id="<<(int)infl_bone_id<<" �� vec_infl_bone_id_order �ɂ��łɑ��݂��Ă܂�");
                                //���݂��遁���m�� infl_bone_id �́A����[����
                            }

                        }
                    } //for (int i = 0; i < 4; i++)
                    if (is_break) {
//                        _TRACE_("bone_cb_idx="<<bone_cb_idx<<" is_break �Ńu���C�N");
                        break;
                    }
                } //�{�[���R���r�l�[�V�����̒��_�o�b�t�@�Ń��[�v
                if (!is_break) {
                   grp_cb_vertex_count += cb_vertex_count;
                }
                //�u���C�N�����A�{�[���R���r�l�[�V�����O���[�v�ɏ��ݒ�
                if (is_break) {
                    //�߂��� bone_cb_idx �܂ł̃{�[���R���r�l�[�V�����B����܂Ƃ܂�
//                    _TRACE_("bone_cb_idx="<<bone_cb_idx<<" �u���C�N�����A�{�[���R���r�l�[�V�����O���[�v�ɏ��ݒ�");
                    BoneConbiGrp bone_combi_grp_info;  //�߂��� bone_cb_idx �܂ł̃{�[���R���r�l�[�V�����B�̏��
                    bone_combi_grp_info.bone_combi_start_index = vec_cb_idx_order[0];
                    bone_combi_grp_info.bone_combi_count = (bone_cb_idx-1) - (vec_cb_idx_order[0]) + 1;
                    bone_combi_grp_info.grp_vertex_start = grp_cb_vertex_start;
                    bone_combi_grp_info.grp_vertex_count = grp_cb_vertex_count;

//                    _TRACE_("bone_cb_idx="<<bone_cb_idx<<" vec_infl_bone_id_order.size()="<<vec_infl_bone_id_order.size());

                    for (int i = 0; i < vec_infl_bone_id_order.size(); i++) {
//                        _TRACE_("bone_cb_idx="<<bone_cb_idx<<" vec_cb_idx_order["<<i<<"]="<<vec_cb_idx_order[i]<<"");

                        if (bone_cb_idx > vec_cb_idx_order[i]) {
                            bone_combi_grp_info.vec_infl_bone_id_order.push_back(vec_infl_bone_id_order[i]);
                            bone_combi_grp_info.vec_cb_idx_order.push_back(vec_cb_idx_order[i]);
                            bone_combi_grp_info.map_infl_bone_id_to_order[vec_infl_bone_id_order[i]] = (DWORD)i;
                        } else {
//                            _TRACE_("bone_cb_idx="<<bone_cb_idx<<" �ł��؂�I");
                            break;
                        }
                    }
//                    _TRACE_("bone_cb_idx="<<bone_cb_idx<<"  _vec_bone_combi_grp_info�ɏ��ǉ��I�I");
                    _vec_bone_combi_grp_info.push_back(bone_combi_grp_info);
//                    _TRACE_("bone_cb_idx="<<bone_cb_idx<<" //�߂�  bone_cb_idx="<<bone_cb_idx<<"��"<<(bone_cb_idx-1));
                    bone_cb_idx --; //���Ӄ��[�v�J�E���^��߂�
                } //if (is_break)
            } //�{�[���R���r�l�[�V�����Ń��[�v
//_TRACE_("�{�[���R���r�l�[�V�����Ń��[�v�������A�ŏIbone_cb_idx="<<bone_cb_idx<<"");
            //�ŏI�{�[���R���r�l�[�V�����O���[�v�ɏ��ݒ�
            bone_cb_idx--;
            BoneConbiGrp bone_combi_grp_info;  //�߂��� bone_cb_idx �܂ł̃{�[���R���r�l�[�V�����B�̏��
            bone_combi_grp_info.bone_combi_start_index = vec_cb_idx_order[0];
            bone_combi_grp_info.bone_combi_count = (bone_cb_idx-1) - (vec_cb_idx_order[0]) + 1;
            bone_combi_grp_info.grp_vertex_start = grp_cb_vertex_start;
            bone_combi_grp_info.grp_vertex_count = grp_cb_vertex_count;
            for (int i = 0; i < vec_infl_bone_id_order.size(); i++) {
                bone_combi_grp_info.vec_infl_bone_id_order.push_back(vec_infl_bone_id_order[i]);
                bone_combi_grp_info.vec_cb_idx_order.push_back(vec_cb_idx_order[i]);
                bone_combi_grp_info.map_infl_bone_id_to_order[vec_infl_bone_id_order[i]] = (DWORD)i;
            }
            _vec_bone_combi_grp_info.push_back(bone_combi_grp_info);

            /////////////////////////////////
            IDirect3DIndexBuffer9* pIb;
            pMesh1->GetIndexBuffer(&pIb);
            DWORD nFace = pMesh1->GetNumFaces();
            D3DINDEXBUFFER_DESC desc;
            pIb->GetDesc( &desc );

            if (_indexBuffer_fmt == D3DFMT_UNKNOWN) {
                _indexBuffer_fmt = desc.Format;
                if (_indexBuffer_fmt == D3DFMT_INDEX16) {
                    _paIndex16Buffer_data = NEW uint16_t[_nFaces*3];
                } else {
                    _paIndex32Buffer_data = NEW uint32_t[_nFaces*3];
                }
            }

            if (_indexBuffer_fmt == D3DFMT_INDEX16) {
                void* paIndexBuffer;
                pIb->Lock(0, nFace*3*sizeof(uint16_t), (void**)&paIndexBuffer, 0);
                char* p = (char*)paIndexBuffer;
                for (int f = 0; f < nFace; f++) {
                    uint16_t val1,val2,val3;
                    memcpy(&(val1), p, sizeof(uint16_t));  p += sizeof(uint16_t);
                    memcpy(&(val2), p, sizeof(uint16_t));  p += sizeof(uint16_t);
                    memcpy(&(val3), p, sizeof(uint16_t));  p += sizeof(uint16_t);
                    int offset = (vtx_idx_thru-nVertices); //���_�ԍ���ʂ��ɂ��邽�߂̌v�Z�B
                                                           //vtx_idx_thru�F���b�V���R���e�i�����I������
                                                           //              �ʂ����_�C���f�b�N�X�́{�P �� nVertices
                                                           //              ����̓��b�V���R���e�i�̒��_�� �Ȃ̂� 0 �ƂȂ�B
                    _paIndex16Buffer_data[i_cnt+0] = offset + val1;
                    _paIndex16Buffer_data[i_cnt+1] = offset + val2;
                    _paIndex16Buffer_data[i_cnt+2] = offset + val3;
                    i_cnt+=3;
                }
            } else {
                void* paIndexBuffer;
                pIb->Lock(0, nFace*3*sizeof(uint32_t), (void**)&paIndexBuffer, 0);
                char* p = (char*)paIndexBuffer;
                for (int f = 0; f < nFace; f++) {
                    uint32_t val1,val2,val3;
                    memcpy(&(val1), p, sizeof(uint32_t));  p += sizeof(uint32_t);
                    memcpy(&(val2), p, sizeof(uint32_t));  p += sizeof(uint32_t);
                    memcpy(&(val3), p, sizeof(uint32_t));  p += sizeof(uint32_t);
                    int offset = (vtx_idx_thru-nVertices);
                    _paIndex32Buffer_data[i_cnt+0] = offset + val1;
                    _paIndex32Buffer_data[i_cnt+1] = offset + val2;
                    _paIndex32Buffer_data[i_cnt+2] = offset + val3;
                    i_cnt += 3;
                }
            }
            pIb->Unlock();
            pIb->Release();

            //���͒������̂� Mesh��������I
            GGAF_RELEASE(pMeshContainer->MeshData.pMesh);
            pMeshContainer->MeshData.pMesh = nullptr;
        } //for (int i = 0; i < draw_frame_num; i++) �t���[���Ń��[�v

        ///////////////////////////////////////////////
        //���_�o�b�t�@�� infl_bone_id_order �� bone_id ����ϊ����Đݒ�
        for (int bone_cb_grp_idx = 0; bone_cb_grp_idx < _vec_bone_combi_grp_info.size(); bone_cb_grp_idx ++) {
            BoneConbiGrp&  bone_cb_grp = _vec_bone_combi_grp_info[bone_cb_grp_idx];
            int cb_grp_vertex_start = bone_cb_grp.grp_vertex_start;
            int cb_grp_vertex_count = bone_cb_grp.grp_vertex_count;
            //�{�[���R���r�l�[�V�����̒��_�o�b�t�@�Ń��[�v
            for (int v_idx = cb_grp_vertex_start; v_idx < cb_grp_vertex_start+cb_grp_vertex_count; v_idx++) {
                SkinAniMeshModel::VERTEX* pVtx_data = &(_paVtxBuffer_data[v_idx]);
                VERTEX_EX* pVtx_data_ex = &(paVtx_wk[v_idx]);
                pVtx_data_ex->bone_combi_grp_index = bone_cb_grp_idx;
                for (int i = 0; i < 4; i++) {
                    byte infl_bone_id = pVtx_data_ex->infl_bone_id[i];
                    if (infl_bone_id == 0xFF) {
                        pVtx_data->infl_bone_id_order[i] = 0xFF;
                    } else {
                        DWORD infl_bone_id_order = bone_cb_grp.map_infl_bone_id_to_order[(DWORD)infl_bone_id];
                        pVtx_data->infl_bone_id_order[i] = (byte)infl_bone_id_order;
                    }
                }
            }
        }
////////////////////////////////////////////////
        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        std::vector<SkinAniMeshModel::INDEXPARAM> param_tmp;

        int paramno = 0; // = bone_combi_grp_index �ƂȂ�

        int face_idx_break = 0;
        int prev_face_idx_break = -1;

        int bone_combi_grp_index = 0;
        int prev_bone_combi_grp_index = -1;

        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;
        UINT vtx_idx1,vtx_idx2,vtx_idx3;
        int face_idx;
        for (face_idx = 0; face_idx < _nFaces; face_idx++) {
            //�C���f�b�N�X�o�b�t�@�ԍ��ɑΉ����钸�_�o�b�t�@�� bone_combi_grp_index
            int index_buffer_idx;
            if (_indexBuffer_fmt == D3DFMT_INDEX16) {
                index_buffer_idx = _paIndex16Buffer_data[face_idx*3+0];
            } else {
                index_buffer_idx = _paIndex32Buffer_data[face_idx*3+0];
            }
            bone_combi_grp_index = (int)(paVtx_wk[index_buffer_idx].bone_combi_grp_index);
            if (bone_combi_grp_index != prev_bone_combi_grp_index) {
                prev_face_idx_break = face_idx_break;
                face_idx_break = face_idx;

                param_tmp.push_back(SkinAniMeshModel::INDEXPARAM());
                param_tmp[paramno].MaterialNo = 0;
                param_tmp[paramno].BaseVertexIndex = 0;
                param_tmp[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�K���u���C�N���������ߕςȒl�ɂ��Ƃ�
                param_tmp[paramno].NumVertices = UINT_MAX; //����u���C�N���ɐݒ�
                param_tmp[paramno].StartIndex = face_idx*3;
                param_tmp[paramno].PrimitiveCount = UINT_MAX; //����u���C�N���ɐݒ�

                if (face_idx > 0) {
                    param_tmp[paramno-1].MinIndex = min_num_vertices;
                    param_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    param_tmp[paramno-1].PrimitiveCount = (UINT)(face_idx_break - prev_face_idx_break);
                    //���Z�b�g
                    max_num_vertices = 0;
                    min_num_vertices = UINT_MAX;
                }
                paramno++;
            }
            if (_indexBuffer_fmt == D3DFMT_INDEX16) {
                vtx_idx1 = _paIndex16Buffer_data[face_idx*3 + 0]; //faceNoCnt(�ʔԍ�)�ɑ΂��钸�_�ԍ�
                vtx_idx2 = _paIndex16Buffer_data[face_idx*3 + 1];
                vtx_idx3 = _paIndex16Buffer_data[face_idx*3 + 2];
            } else {
                vtx_idx1 = _paIndex32Buffer_data[face_idx*3 + 0]; //faceNoCnt(�ʔԍ�)�ɑ΂��钸�_�ԍ�
                vtx_idx2 = _paIndex32Buffer_data[face_idx*3 + 1];
                vtx_idx3 = _paIndex32Buffer_data[face_idx*3 + 2];
            }


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
            prev_bone_combi_grp_index = bone_combi_grp_index;
        } //for (faceNoCnt = 0; faceNoCnt < _nFaces; faceNoCnt++)
        if (_nFaces > 0) {
            param_tmp[paramno-1].MinIndex = min_num_vertices;
            param_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            param_tmp[paramno-1].PrimitiveCount = (UINT)(face_idx - face_idx_break);
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

//        _TRACE_("�܂Ƃ߁I------------");
//        for (int i = 0; i < _nVertices; i++) {
//            SkinAniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[i]); //��������1���_�̊J�n�A�h���X
//            VERTEX_EX* pVtx_data_ex = &(paVtx_wk[i]);
//            _TRACE_("["<<i<<"]:"<<
//                    "bone_combi_grp["<<(pVtx_data_ex->bone_combi_grp_index)<<"] "<<
//                    " Vertex=("<<(pVtx->x)<<","<<(pVtx->y)<<","<<(pVtx->z)<<")"<<
//                    " infl_bone_id=("<<(int)(pVtx_data_ex->infl_bone_id[0])<<","<<(int)(pVtx_data_ex->infl_bone_id[1])<<","<<(int)(pVtx_data_ex->infl_bone_id[2])<<","<<(int)(pVtx_data_ex->infl_bone_id[3])<<")"<<
//                    " infl_bone_id_order=("<<(int)(pVtx->infl_bone_id_order[0])<<","<<(int)(pVtx->infl_bone_id_order[1])<<","<<(int)(pVtx->infl_bone_id_order[2])<<","<<(int)(pVtx->infl_bone_id_order[3])<<")"<<
//                    " infl_weight=("<<(pVtx->infl_weight[0])<<","<<(pVtx->infl_weight[1])<<","<<(pVtx->infl_weight[2])<<","<<(pVtx->infl_weight[3])<<")"<<
//                    " Normal=("<<(pVtx->nx)<<","<<(pVtx->ny)<<","<<(pVtx->nz)<<")"
//
//            );
//        }
//        _TRACE_("�{�[���R���r�O���[�v");
//        for (int i = 0; i < _vec_bone_combi_grp_info.size(); i++) {
//            BoneConbiGrp& bcg = _vec_bone_combi_grp_info[i];
//            _TRACE_("["<<i<<"]:"<<
//                     " bone_combi_start_index="<<bcg.bone_combi_start_index<<" "<<
//                     " bone_combi_count="<<bcg.bone_combi_count<<" "<<
//                     " grp_vertex_start="<<bcg.grp_vertex_start<<" "<<
//                     " grp_vertex_count="<<bcg.grp_vertex_count<<" "<<
//                     "");
//            _TRACE_N_("infl_bone_id_order=");
//            for (int j = 0; j < bcg.vec_infl_bone_id_order.size(); ++j) {
//                _TRACE_N_("["<<j<<"]"<<bcg.vec_infl_bone_id_order[j]<<"\t");
//            }
//            _TRACE_N_("\n");
//
//            _TRACE_N_("vec_cb_idx_order  =");
//            for (int j = 0; j < bcg.vec_cb_idx_order.size(); ++j) {
//                _TRACE_N_("["<<j<<"]"<<bcg.vec_cb_idx_order[j]<<"\t");
//            }
//            _TRACE_N_("\n");
//        }
//        _TRACE_("�܂Ƃ߂����I------------");

        GGAF_DELETEARR(paVtx_wk);
    } //if (_paVtxBuffer_data == nullptr)

    if (_pVertexDeclaration == nullptr) {
        HRESULT hr;
        //D3DVERTEXELEMENT9 �\���̂̔z��v�f��
        D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[7];
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
        //DWORD color; // ���_�J���[
        paVtxelem[2].Stream = 0;
        paVtxelem[2].Offset = st0_offset_next;
        paVtxelem[2].Type = D3DDECLTYPE_D3DCOLOR;
        paVtxelem[2].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[2].Usage = D3DDECLUSAGE_COLOR;
        paVtxelem[2].UsageIndex = 0;
        st0_offset_next += sizeof(DWORD);
        //float tu, tv; // �e�N�X�`�����W
        paVtxelem[3].Stream = 0;
        paVtxelem[3].Offset = st0_offset_next;
        paVtxelem[3].Type = D3DDECLTYPE_FLOAT2;
        paVtxelem[3].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[3].Usage = D3DDECLUSAGE_TEXCOORD;
        paVtxelem[3].UsageIndex = 0;
        st0_offset_next += sizeof(float)*2;
        //float infl_weight[4];
        paVtxelem[4].Stream = 0;
        paVtxelem[4].Offset = st0_offset_next;
        paVtxelem[4].Type = D3DDECLTYPE_FLOAT4;
        paVtxelem[4].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[4].Usage = D3DDECLUSAGE_BLENDWEIGHT;
        paVtxelem[4].UsageIndex = 0;
        st0_offset_next += sizeof(float)*4;
        // byte infl_bone_id_order[4];
        paVtxelem[5].Stream = 0;
        paVtxelem[5].Offset = st0_offset_next;
        paVtxelem[5].Type = D3DDECLTYPE_UBYTE4;
        paVtxelem[5].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[5].Usage = D3DDECLUSAGE_BLENDINDICES;
        paVtxelem[5].UsageIndex = 1;
        st0_offset_next += sizeof(byte)*4;
        //D3DDECL_END()
        paVtxelem[6].Stream = 0xFF;
        paVtxelem[6].Offset = 0;
        paVtxelem[6].Type = D3DDECLTYPE_UNUSED;
        paVtxelem[6].Method = 0;
        paVtxelem[6].Usage = 0;
        paVtxelem[6].UsageIndex = 0;

        hr = pCARETAKER->_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "pCARETAKER->_pID3DDevice9->CreateVertexDeclaration ���s model="<<(_model_id));
        //�X�g���[�����擾        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);
        GGAF_DELETEARR(paVtxelem);
    }


    if (_papTextureConnection == nullptr) {
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] = connectToTextureManager(_pa_texture_filenames[n].c_str());
        }
    }

    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //���_�o�b�t�@�쐬
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                0, //SkinAniMeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_id));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *paVertexBuffer;
        hr = _paVertexBuffer->Lock(0, _size_vertices, (void**)&paVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);
        memcpy(paVertexBuffer, _paVtxBuffer_data, _size_vertices); //paVertexBuffer �� paVertex
        _paVertexBuffer->Unlock();
    }

    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        if (_indexBuffer_fmt == D3DFMT_INDEX16) {
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                       sizeof(uint16_t) * _nFaces * 3,
                                       D3DUSAGE_WRITEONLY,
                                       D3DFMT_INDEX16,
                                       D3DPOOL_DEFAULT,
                                       &(_paIndexBuffer),
                                       nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_id));
            void* paIndexBuffer;
            _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
            memcpy(paIndexBuffer , _paIndex16Buffer_data , sizeof(uint16_t) * _nFaces * 3);
            _paIndexBuffer->Unlock();
        } else {
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                       sizeof(uint32_t) * _nFaces * 3,
                                       D3DUSAGE_WRITEONLY,
                                       D3DFMT_INDEX32,
                                       D3DPOOL_DEFAULT,
                                       &(_paIndexBuffer),
                                       nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_id));
            void* paIndexBuffer;
            _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
            memcpy(paIndexBuffer , _paIndex32Buffer_data , sizeof(uint32_t) * _nFaces * 3);
            _paIndexBuffer->Unlock();
        }

    }
    _TRACE3_("_model_id=" << _model_id << " end");
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
void SkinAniMeshModel::setAnimationFrameIndex() {
    _mapAnimationSet_AniSetindex.clear();
    _num_animation_set = _pAniControllerBase->GetMaxNumAnimationSets();
    _papaBool_AnimationSetIndex_BoneFrameIndex_is_act = NEW bool*[_num_animation_set];

    HRESULT hr;
    for (UINT ani_set_index = 0; ani_set_index < _num_animation_set; ani_set_index++) {

        ID3DXAnimationSet* pAnimationSet = nullptr;
        hr = _pAniControllerBase->GetAnimationSet(ani_set_index, &(pAnimationSet)); //�A�j���[�V�����Z�b�g�ێ�
        checkDxException(hr, D3D_OK, "���s���܂���");
        _mapAnimationSet_AniSetindex[pAnimationSet] = ani_set_index;
        int num_animation = pAnimationSet->GetNumAnimations();
        std::vector<LPCSTR> vec_target_bone_frame_name; //�A�j���[�V��������t���[��(�{�[��)�̖��O���X�g
        for (UINT ani_index = 0; ani_index < num_animation; ++ani_index) {
            LPCSTR target_bone_frame_name = nullptr;
            hr = pAnimationSet->GetAnimationNameByIndex(ani_index, &target_bone_frame_name); //�A�j���[�V��������t���[���̖��O
            checkDxException(hr, D3D_OK, "���s���܂���");
            vec_target_bone_frame_name.push_back(target_bone_frame_name);
        }

        //�A�j���[�V��������t���[���̖��O���t���[���ɑ��݂��邩�ǂ����𒲂ׁA
        //�A�j���[�V��������t���[���C���f�b�N�X������ێ����Ă���
        _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index] = NEW bool[_tmp_frame_index+1];
        for (UINT frame_index = 0; frame_index < _vecAllBoneFrame.size(); frame_index++) {
            _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index][frame_index] = false;
            LPSTR frame_name = _vecAllBoneFrame[frame_index]->Name;
            if (frame_name) {
                for (int n = 0; n < vec_target_bone_frame_name.size(); n++) {
                    LPCSTR animation_target_bone_frame_name = vec_target_bone_frame_name[n];
                    if (strcmp(animation_target_bone_frame_name, frame_name) == 0) {
                        _papaBool_AnimationSetIndex_BoneFrameIndex_is_act[ani_set_index][frame_index] = true;
                        break;
                    }
                }
            }
        }
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
    _TRACE3_("_model_id=" << _model_id << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void SkinAniMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //�e�N�X�`���̔z��
    GGAF_RELEASE(_paVertexBuffer);
    GGAF_RELEASE(_paIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);
    _TRACE3_("_model_id=" << _model_id << " end");
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
    GGAF_DELETEARR_NULLABLE(_paIndex16Buffer_data);
    GGAF_DELETEARR_NULLABLE(_paIndex32Buffer_data);
    GGAF_DELETEARR(_paIndexParam);
//    GGAF_DELETE(_pFrameRoot); //_pAllocHierarchy��������_pFrameRoot�͏����Ȃ��ėǂ��Ǝv��
}
