#include "jp/ggaf/dx/model/AniMeshModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/AniMeshActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/effect/AniMeshEffect.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/AllocHierarchyWorldFrame.h"

#define MAX_FRAME_WORLD_MATRIX (5)


using namespace GgafDx;
DWORD AniMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

AniMeshModel::AniMeshModel(const char* prm_model_name) : Model(prm_model_name) {
    _pAH = nullptr;
    _pFR = nullptr;
    _pAcBase = nullptr;
    _num_materials = 0L;
    _anim_ticks_per_second = 4800; //restoreAniMeshModel �ŏ㏑�������ꍇ������B
    _paVtxBuffer_data = nullptr;
    _paIndexBuffer_data = nullptr;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _index_param_num = 0;
    _paIndexParam = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = sizeof(AniMeshModel::VERTEX);
    _nFaces = 0;
    _nVertices = 0;
    _obj_model |= Obj_GgafDx_AniMeshModel;
}

HRESULT AniMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("AniMeshModel::draw("<<prm_pActor_target->getName()<<")");
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    HRESULT hr;
    //�ΏۃA�N�^�[
    AniMeshActor* pTargetActor = (AniMeshActor*)prm_pActor_target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    AniMeshEffect* pAniMeshEffect = (AniMeshEffect*)(prm_pActor_target->getEffect());
    //�ΏۃG�t�F�N�g
    ID3DXEffect* pID3DXEffect = pAniMeshEffect->_pID3DXEffect;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(AniMeshModel::FVF);
        pDevice->SetIndices(_pIndexBuffer);
        hr = pID3DXEffect->SetFloat(pAniMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pAniMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
//        hr = pID3DXEffect->SetFloat(pAniMeshEffect->_h_specular, _specular);
//        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
//        hr = pID3DXEffect->SetFloat(pAniMeshEffect->_h_specular_power, _specular_power);
//        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�}�e���A���E�e�N�X�`���̈ꔭ�ڂ��Z�b�g�A
    LPDIRECT3DBASETEXTURE9 pTex = _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9;
    hr = pDevice->SetTexture(0, pTex);
    checkDxException(hr, D3D_OK, "SetTexture �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetValue(pAniMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");

    pTargetActor->_pPuppeteer->updateAnimationTrack(); //�A�j���[�V�������f
    //���f���̃��[���h�ϊ��s��X�V
    _stackWorldMat.SetWorldMatrix(&(pTargetActor->_matWorld));
    _stackWorldMat.UpdateFrame(_pFR);

    std::list<FrameWorldMatrix*> *pDrawList = _stackWorldMat.GetDrawList(); // �`�惊�X�g���擾
    std::list<FrameWorldMatrix*>::iterator it = pDrawList->begin();
    std::list<FrameWorldMatrix*>::iterator it_1 = pDrawList->begin();
    std::list<FrameWorldMatrix*>::iterator it_2 = pDrawList->begin();

/////////////////////////////////////////////
//    for (int index_param = 0; index_param < _index_param_num; index_param++) {
//        for (int i = 0; i < MAX_FRAME_WORLD_MATRIX; i++) {
//            if (it_1 != pDrawList->end()) {
//                hr = pID3DXEffect->SetMatrix(pAniMeshEffect->_ah_matWorld[i], &((*it_1)->WorldTransMatrix));
//                ++it_1;
//            } else {
//                break;
//            }
//        }
//
//
//
//
//
//    }
/////////////////////////////////////////////

    for (int i = 0; it != pDrawList->end(); i++, ++it) {
        hr = pID3DXEffect->SetMatrix(pAniMeshEffect->_ah_matWorld[i], &((*it)->WorldTransMatrix));
    }


    Effect* pEffect_active = EffectManager::_pEffect_active;
    if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) ) {
        if (pEffect_active) {
            _TRACE4_("EndPass: /_pEffect_active="<<pEffect_active->_effect_name);
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "AniMeshModel::draw() EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "AniMeshModel::draw() End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pAniMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pAniMeshEffect->_effect_name<<"("<<pAniMeshEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "AniMeshModel::draw() Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "AniMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pAniMeshEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pAniMeshEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "AniMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
            _paIndexParam[0].BaseVertexIndex,
            _paIndexParam[0].MinIndex,
            _paIndexParam[0].NumVertices,
            _paIndexParam[0].StartIndex,
            _paIndexParam[0].PrimitiveCount);


#ifdef MY_DEBUG
    GgafCore::God::_num_drawing++;
#endif
    //�O��`�惂�f�������f
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pAniMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void AniMeshModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    HRESULT hr;
    if (_paVtxBuffer_data == nullptr) {
        std::string xfile_name = ModelManager::getMeshFileName(_model_name);
        TextureManager* pTextureManager = pGOD->_pModelManager->_pModelTextureManager;
        //AnimTicksPerSecond��Ǝ��Ɏ��o���B�f�t�H���g��4800
        _anim_ticks_per_second = getAnimTicksPerSecond(xfile_name);
        //X�t�@�C���̃t�@�C�����[�h
        _pAH = NEW AllocHierarchyWorldFrame(); // CAllocHierarchyBase�̔h���N���X
        hr = D3DXLoadMeshHierarchyFromX(
                xfile_name.c_str(),
                D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
                God::_pID3DDevice9,
                _pAH,
                nullptr,
                (D3DXFRAME**)(&_pFR),
                &_pAcBase
             );
        _TRACE_("_pAH="<<_pAH<<" _pFR="<<_pFR<<" _pAcBase="<<_pAcBase<<" xfile_name.c_str()="<<xfile_name.c_str());
        checkDxException(hr, D3D_OK, xfile_name<<" �ǂݍ��݂Ɏ��s���܂����B�Ώ�="<<xfile_name);
        if (_pFR == nullptr) {
            throwCriticalException(xfile_name<<" �̃t���[����񂪎擾�ł��܂���I");
        }
        //���E��
        D3DXVECTOR3 vecCenter;
        FLOAT bounding_sphere_radius;
        D3DXFrameCalculateBoundingSphere((D3DXFRAME*)_pFR, &vecCenter, &bounding_sphere_radius);
        _bounding_sphere_radius = UTIL::getDistance(0.0f, 0.0f, 0.0f, vecCenter.x, vecCenter.y, vecCenter.z) + bounding_sphere_radius;

        _TRACE_("���E�����a="<<_bounding_sphere_radius);

        //�}�e���A���z����쐬
        std::vector<FrameWorldMatrix*> vecFrame;
        getDrawFrameVec(&vecFrame, _pFR); //�}�e���A��������m�肽�������߁A�t���[�������A���X�g��
        int frame_num = vecFrame.size();

        int materials_total_num = 0;
        int vertices_total_num = 0;
        int faces_total_num = 0;

        //�t���[�����X�g������āA�}�e���A�������擾
        for (int i = 0; i < frame_num; i++) {
            if (vecFrame[i]->pMeshContainer == nullptr) {
                continue;
            }
            ID3DXMesh* pMesh = vecFrame[i]->pMeshContainer->MeshData.pMesh;
            vertices_total_num += (int)(pMesh->GetNumVertices());  // ���_��
            faces_total_num += (int)(pMesh->GetNumFaces());        // �|���S����
            materials_total_num += (int)(vecFrame[i]->pMeshContainer->NumMaterials);
        }
        //�z�񐔂�����Ɖ������̂ō쐬
        _num_materials = materials_total_num;
        _nVertices = vertices_total_num;
        _nFaces = faces_total_num;
        _paVtxBuffer_data =  NEW AniMeshModel::VERTEX[_nVertices];
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
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
        for (int i = 0; i < frame_num; i++) {
            D3DXMESHCONTAINER* pMeshContainer = vecFrame[i]->pMeshContainer;
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
                AniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[v_cnt]); //��������1���_�̊J�n�A�h���X
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
                // float index
                pVtx->index = i;

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
                v_cnt ++;
            }
            pVb->Unlock();
            pVb->Release();

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
                    _paIndexBuffer_data[i_cnt] = offset + val1;  i_cnt++;
                    _paIndexBuffer_data[i_cnt] = offset + val2;  i_cnt++;
                    _paIndexBuffer_data[i_cnt] = offset + val3;  i_cnt++;
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
                    _paIndexBuffer_data[i_cnt] = offset + val1;  i_cnt++;
                    _paIndexBuffer_data[i_cnt] = offset + val2;  i_cnt++;
                    _paIndexBuffer_data[i_cnt] = offset + val3;  i_cnt++;
                }
            }
            pIb->Unlock();
            pIb->Release();

            //���͒������̂� MeshContainer ����I
//            _pAH->DestroyMeshContainer(pMeshContainer);
//            vecFrame[i]->pMeshContainer = nullptr; //nullptr��ݒ肷�邱�ƂŊJ�����ɃX�L�b�v������
            GGAF_RELEASE(pMeshContainer->MeshData.pMesh);
            pMeshContainer->MeshData.pMesh = nullptr;
        }

    //    _advance_time_per_frame0 =  advanceTimePerFrame0; //�g���b�N0�ԂP���[�v�̎���
    //    _TRACE_("�A�j���[�V�����Z�b�g0��_advance_time_per_frame");




////////////////////////////////////////////////
//        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
//        std::vector<AniMeshModel::INDEXPARAM> param_tmp;
//
//        int paramno = 0;
//        int faceNoCnt_break = 0;
//        int prev_faceNoCnt_break = -1;
//        UINT max_num_vertices = 0;
//        UINT min_num_vertices = UINT_MAX;
//        MAX_FRAME_WORLD_MATRIX;
//        int faceNoCnt;
//        for (faceNoCnt = 0; faceNoCnt < _nFaces; faceNoCnt++) {
//            if (faceNoCnt % MAX_FRAME_WORLD_MATRIX == 0) {
//                //_TRACE3_("BREAK! paramno="<<paramno);
//                prev_faceNoCnt_break = faceNoCnt_break;
//                faceNoCnt_break = faceNoCnt;
//                param_tmp.push_back(AniMeshModel::INDEXPARAM());
//                param_tmp[paramno].MaterialNo = 0;
//                param_tmp[paramno].BaseVertexIndex = 0;
//                param_tmp[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�K���u���C�N���������ߕςȒl�ɂ��Ƃ�
//                param_tmp[paramno].NumVertices = UINT_MAX; //����u���C�N���ɐݒ�
//                param_tmp[paramno].StartIndex = faceNoCnt*3;
//                param_tmp[paramno].PrimitiveCount = UINT_MAX; //����u���C�N���ɐݒ�
//
//                if (faceNoCnt > 0) {
//                    param_tmp[paramno-1].MinIndex = min_num_vertices;
//                    param_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
//                    param_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
//                    //���Z�b�g
//                    max_num_vertices = 0;
//                    min_num_vertices = UINT_MAX;
//                }
//                paramno++;
//            }
//
//            if (max_num_vertices <  _paIndexBuffer_data[faceNoCnt*3 + 0]) {
//                max_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 0];
//            }
//            if (max_num_vertices <  _paIndexBuffer_data[faceNoCnt*3 + 1]) {
//                max_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 1];
//            }
//            if (max_num_vertices <  _paIndexBuffer_data[faceNoCnt*3 + 2]) {
//                max_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 2];
//            }
//            if (min_num_vertices >  _paIndexBuffer_data[faceNoCnt*3 + 0]) {
//                min_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 0];
//            }
//            if (min_num_vertices >  _paIndexBuffer_data[faceNoCnt*3 + 1]) {
//                min_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 1];
//            }
//            if (min_num_vertices >  _paIndexBuffer_data[faceNoCnt*3 + 2]) {
//                min_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 2];
//            }
//        }
//        if (_nFaces > 0) {
//            param_tmp[paramno-1].MinIndex = min_num_vertices;
//            param_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
//            param_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
//        }
//        _index_param_num = paramno;
//        _paIndexParam = NEW MeshModel::INDEXPARAM[paramno];
//        for (int i = 0; i < paramno; i++) {
//            _paIndexParam[i].MaterialNo      = param_tmp[i].MaterialNo;
//            _paIndexParam[i].BaseVertexIndex = param_tmp[i].BaseVertexIndex;
//            _paIndexParam[i].MinIndex        = param_tmp[i].MinIndex;
//            _paIndexParam[i].NumVertices     = param_tmp[i].NumVertices;
//            _paIndexParam[i].StartIndex      = param_tmp[i].StartIndex;
//            _paIndexParam[i].PrimitiveCount  = param_tmp[i].PrimitiveCount;
//        }
///////////////////////////////////////////////////////////////////





        _paIndexParam = NEW AniMeshModel::INDEXPARAM[1];
        for (int i = 0; i < 1; i++) {
            _paIndexParam[i].MaterialNo      = 0;
            _paIndexParam[i].BaseVertexIndex = 0;
            _paIndexParam[i].MinIndex        = 0;
            _paIndexParam[i].NumVertices     = _nVertices;
            _paIndexParam[i].StartIndex      = 0;
            _paIndexParam[i].PrimitiveCount  = _nFaces;
        }
        _size_vertices = _size_vertex_unit * _nVertices;

//        _TRACE_("�܂Ƃ߁I");
//        for (int i = 0; i < _nVertices; i++) {
//            AniMeshModel::VERTEX* pVtx = &(_paVtxBuffer_data[i]); //��������1���_�̊J�n�A�h���X
//            _TRACE_("["<<i<<"]:Vertex=("<<(pVtx->x)<<","<<(pVtx->y)<<","<<(pVtx->z)<<")  Normal=("<<(pVtx->nx)<<","<<(pVtx->ny)<<","<<(pVtx->nz)<<")");
//        }
//        for (int i = 0; i < _nFaces; ++i) {
//            _TRACE_("["<<i<<"]:Index=("<<(_paIndexBuffer_data[i*3+0])<<","<<
//                    (_paIndexBuffer_data[i*3+1])<<","<<
//                    (_paIndexBuffer_data[i*3+2])<<")");
//        }

    } //if (_paVtxBuffer_data == nullptr)


    if (_papTextureConnection == nullptr) {
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        TextureManager* pTextureManager = pGOD->_pModelManager->_pModelTextureManager;
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    if (_pVertexBuffer == nullptr) {
        //���_�o�b�t�@�쐬
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                AniMeshModel::FVF,
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

//        D3DXATTRIBUTERANGE* pAttrTable;
//        DWORD dwNumAttr;
//        pAttrTable = NULL;
//        // ���b�V���̑����e�[�u���̎擾*/
//        //���b�V���̃e�[�u�����擾*/
//        pMesh->GetAttributeTable(NULL,&dwNumAttr);
//        //�e�[�u���̐���
//        pAttrTable = new D3DXATTRIBUTERANGE[dwNumAttr];
//        /*�擾*/
//        if(FAILED(pMesh->GetAttributeTable(pAttrTable,&dwNumAttr))) {
//            throwCriticalException("AniMeshModel::restore() �����e�[�u���̎擾�Ɏ��s���܂����B");
//        }
//        for(DWORD a=0;a<dwNumAttr;a++)
//        {
//            INT BaseVertexIndex = 0;
//            UINT MinIndex = pAttrTable[a].VertexStart; //�ŏ���INDEX
//            UINT NumVertices= pAttrTable[a].VertexCount; //���_��
//            UINT StartIndex = pAttrTable[a].FaceStart*3; //INDEXBUFFER����INDEX
//            UINT PrimitiveCount = pAttrTable[a].FaceCount; //�|���S����
////            _TRACE_("["<<i<<"]["<<a<<"]:att="<<MinIndex<<","<<NumVertices<<","<<StartIndex<<","<<PrimitiveCount);
//        }

ID3DXAnimationController* AniMeshModel::getCloneAnimationController() {
    ID3DXAnimationController* _pAc = nullptr;
    HRESULT hr = _pAcBase->CloneAnimationController(
                                _pAcBase->GetMaxNumAnimationOutputs(),
                                _pAcBase->GetMaxNumAnimationSets(),
                                _pAcBase->GetMaxNumTracks(),
                                _pAcBase->GetMaxNumEvents(),
                                        &_pAc);
    checkDxException(hr, D3D_OK, "�A�j���[�V�����R���g���[���[�̃N���[���Ɏ��s���܂����B");
    return _pAc;
}
int AniMeshModel::getAnimTicksPerSecond(std::string& prm_xfile_name) {
    if (prm_xfile_name == "") {
         throwCriticalException("���b�V���t�@�C��(*.x)��������܂���Bmodel_name="<<(_model_name));
    }
    //X�t�@�C������AnimTicksPerSecond�̒l��Ǝ��Ɏ��o��
    std::ifstream ifs(prm_xfile_name.c_str());
    if (ifs.fail()) {
        throwCriticalException("["<<prm_xfile_name<<"] ���J���܂���");
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
    return anim_ticks_per_second;
}

void AniMeshModel::getDrawFrameVec(std::vector<FrameWorldMatrix*>* pList, FrameWorldMatrix* pFrame) {
    if (pFrame->pMeshContainer) {
        //���b�V���R���e�i�L��
        pList->push_back(pFrame); //���X�g�ɒǉ�
    }
    if (pFrame->pFrameFirstChild) {
        // �q�t���[���L��
        getDrawFrameVec(pList, (FrameWorldMatrix*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //�Z��t���[���L��
        getDrawFrameVec(pList, (FrameWorldMatrix*)pFrame->pFrameSibling);
    }
}
int AniMeshModel::getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage ) {
    D3DVERTEXELEMENT9 *e = elems;
    while( e->Stream != 0xff ) {
        if ( e->Usage == usage )
            return (int)(e->Offset);
        e = e + 1;
    }
    return -1;
}

void AniMeshModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    //�f�o�C�X���X�g���͉�����܂��B
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void AniMeshModel::release() {
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
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_RELEASE(_pAcBase);
    _pAH->DestroyFrame((D3DXFRAME*)_pFR);
    GGAF_DELETE(_pAH);
//    GGAF_DELETE(_pFR); //_pAH��������_pFR�͏����Ȃ��ėǂ��Ǝv��
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_data);
    GGAF_DELETEARR(_paIndexParam);
    _TRACE3_("_model_name=" << _model_name << " end");
}

AniMeshModel::~AniMeshModel() {
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}
