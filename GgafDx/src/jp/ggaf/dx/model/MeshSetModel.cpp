#include "jp/ggaf/dx/model/MeshSetModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MeshSetActor.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

#define MESHSETMODEL_MAX_DARW_SET_NUM 15

using namespace GgafDx;

DWORD MeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer = nullptr;

MeshSetModel::MeshSetModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_MeshSetModel;
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    _paVertexBuffer = nullptr;
    _paIndexBuffer = nullptr;
    _paUint_material_list_grp_num = nullptr;
    _paVtxBuffer_data = nullptr;
    _paIndex16Buffer_data = nullptr;
    _paIndex32Buffer_data = nullptr;
    _papaIndexParam = nullptr;
    _size_vertex_unit= 0;
    _size_vertices = 0;
    _nVertices = 0;
    _nFaces= 0;
    _max_draw_set_num = MESHSETMODEL_MAX_DARW_SET_NUM;
    _is_65535 = false;
}

HRESULT MeshSetModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("MeshSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        _TRACE_(FUNC_NAME<<" "<<_model_id<<" �̕`��Z�b�g���I�[�o�[�B_draw_set_num="<<_draw_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    //�ΏۃA�N�^�[
    const MeshSetActor* const pTargetActor = (MeshSetActor*)prm_pActor_target;
    //�Ώ�MeshSetActor�̃G�t�F�N�g���b�p
    MeshSetEffect* const pMeshSetEffect = (MeshSetEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    //���f���������ł��A�Z�b�g���������Ȃ�Β��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̐ݒ�̓X�L�b�v�ł���
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetStreamSource(0, _paVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(MeshSetModel::FVF);
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�`��
    const UINT material_list_grp_num = _paUint_material_list_grp_num[prm_draw_set_num-1];
    for (UINT material_grp_index = 0; material_grp_index < material_list_grp_num; material_grp_index++) {
        const INDEXPARAM& idxparam = _papaIndexParam[prm_draw_set_num-1][material_grp_index];
        //���f���������ł��A�Z�b�g�����������A�}�e���A��NO���P�����Ȃ��Ȃ�΁A�e�N�X�`���ݒ���X�L�b�v�ł���
        if (ModelManager::_pModelLastDraw  != this || material_list_grp_num != 1) {
            const UINT material_no = idxparam.MaterialNo;
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //�}�e���A��0�Ԃ́A���ʂɋK��̃e�N�X�`����ݒ肷��d�l
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("MeshSetModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(CONFIG::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                pDevice->SetTexture(0, nullptr);
            }
            //MaterialDiffuse��MeshSetActor���Ń}�e���A����ݒ肷��B�}�e���A���F�͒P�F�Ƃ���B
            //���R��MeshSetActor�̃����yMeshSetActor�̃}�e���A���J���[�ɂ��āz���Q��
        }
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if (material_grp_index == 0 && (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)) {
            if (pEffect_active) {
                _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshSetEffect->_effect_name<<"("<<pMeshSetEffect<<")");
            //UINT numPass;
            hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMeshSetEffect->_begin) {
                throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshSetEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
        }
        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshSetEffect->_effect_name);

        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_draw++;
#endif
        if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
            for (UINT i = 1; i < _num_pass; i++) {
                hr = pID3DXEffect->BeginPass(i);
                checkDxException(hr, D3D_OK, i+1<<"�p�X�� BeginPass("<<i<<") �Ɏ��s���܂����B");
                pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                              idxparam.BaseVertexIndex,
                                              idxparam.MinIndex,
                                              idxparam.NumVertices,
                                              idxparam.StartIndex,
                                              idxparam.PrimitiveCount);
#ifdef MY_DEBUG
                GgafCore::Caretaker::_num_draw++;
#endif
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "�P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
        }
    }
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMeshSetEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void MeshSetModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        obtainMetaModelInfo(&xdata);
        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("MeshSetModel::restore() "<<_model_id<<" �̓����`��Z�b�g���́A�ő�� "<<_max_draw_set_num<<" �ɍĒ�`����܂����B���R�F_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("MeshSetModel::restore() "<<_model_id<<" �̓����`��Z�b�g���� "<<_draw_set_num<<" �ł��B");
        }
        std::string xfilepath = Model::getMeshXFilePath(xdata.XFileNames[0]);
        //�������ޒ��_�o�b�t�@�f�[�^�쐬
        ToolBox::IO_Model_X iox;

        Frm::Model3D* pModel3D = nullptr;
        Frm::Mesh* pMeshesFront = nullptr;

        MeshSetModel::INDEXPARAM** papaIndexParam = nullptr;
        MeshSetModel::VERTEX* unit_paVtxBuffer_data = nullptr;
        MeshSetModel::VERTEX* paVtxBuffer_data = nullptr;
        uint16_t* unit_paIndex16Buffer_data = nullptr;
        uint16_t* paIdx16Buffer_data = nullptr;
        uint32_t* unit_paIndex32Buffer_data = nullptr;
        uint32_t* paIdx32Buffer_data = nullptr;

        D3DMATERIAL9* paMaterial = nullptr;

        int nVertices = 0;
        int nTextureCoords = 0;
        int nFaces = 0;
        pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfilepath, pModel3D);
        if (r == false) {
            throwCriticalException("X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfilepath);
        }

        //���b�V������������O�ɁA�����m�ۂ��Ă���
        int nMesh = (int)pModel3D->_Meshes.size();
        uint32_t* paNumVertices = NEW uint32_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = pModel3D->_Meshes.begin();
                iteMeshes != pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }
        pModel3D->ConcatenateMeshes(); //���b�V�����q����

        pMeshesFront = pModel3D->_Meshes.front();
        nVertices = pMeshesFront->_nVertices;
        nTextureCoords = pMeshesFront->_nTextureCoords;
        nFaces = pMeshesFront->_nFaces;
//        nFaceNormals = pMeshesFront->_nFaceNormals;
        unit_paVtxBuffer_data = NEW MeshSetModel::VERTEX[nVertices];
        _nVertices = nVertices;
        _nFaces = nFaces;
        _size_vertices = sizeof(MeshSetModel::VERTEX) * nVertices;
        _size_vertex_unit = sizeof(MeshSetModel::VERTEX);

        if (_nFaces * 3 * _draw_set_num > 65535) {
            _is_65535 = true;
            _TRACE_("�y�x���z���_�C���f�b�N�X�� 65535 �𒴂�����������܂���B����񂯂ǁB\n�Ώ�Model�F"<<getName()<<"  �C���f�b�N�X:3*"<<_nFaces<<"(faces)*"<<_draw_set_num<<"(sets)  nVertices:"<<nVertices);
        }

        //�@���ȊO�ݒ�
        for (int i = 0; i < nVertices; i++) {
            unit_paVtxBuffer_data[i].x = pMeshesFront->_Vertices[i].data[0];
            unit_paVtxBuffer_data[i].y = pMeshesFront->_Vertices[i].data[1];
            unit_paVtxBuffer_data[i].z = pMeshesFront->_Vertices[i].data[2];
            unit_paVtxBuffer_data[i].nx = 0.0f;
            unit_paVtxBuffer_data[i].ny = 0.0f;
            unit_paVtxBuffer_data[i].nz = 0.0f;
            unit_paVtxBuffer_data[i].color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[
            if (i < nTextureCoords) {
                unit_paVtxBuffer_data[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                unit_paVtxBuffer_data[i].tv = pMeshesFront->_TextureCoords[i].data[1];
            } else {
                unit_paVtxBuffer_data[i].tu = 0;
                unit_paVtxBuffer_data[i].tv = 0;
            }
            unit_paVtxBuffer_data[i].index = 0; //���_�ԍ��i�ނ��薄�ߍ��݁j
        }

        if (nVertices < nTextureCoords) {
            _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfilepath);
        }
        //�@���ݒ��FrameTransformMatrix�K�p
        prepareVtx((void*)unit_paVtxBuffer_data, _size_vertex_unit,
                   pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);
        //����
        FLOAT model_bounding_sphere_radius;
        for (int i = 0; i < nVertices; i++) {
            model_bounding_sphere_radius = (FLOAT)(sqrt(unit_paVtxBuffer_data[i].x * unit_paVtxBuffer_data[i].x +
                                                        unit_paVtxBuffer_data[i].y * unit_paVtxBuffer_data[i].y +
                                                        unit_paVtxBuffer_data[i].z * unit_paVtxBuffer_data[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }
        //�C���f�b�N�X�o�b�t�@�o�^
        if (_is_65535) {
            unit_paIndex32Buffer_data = NEW uint32_t[nFaces*3];
            for (int i = 0; i < nFaces; i++) {
                unit_paIndex32Buffer_data[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
                unit_paIndex32Buffer_data[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
                unit_paIndex32Buffer_data[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
            }
        } else {
            unit_paIndex16Buffer_data = NEW uint16_t[nFaces*3];
            for (int i = 0; i < nFaces; i++) {
                unit_paIndex16Buffer_data[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
                unit_paIndex16Buffer_data[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
                unit_paIndex16Buffer_data[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
            }
        }


        //���_�o�b�t�@���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        paVtxBuffer_data = NEW MeshSetModel::VERTEX[nVertices * _draw_set_num];
        for (int i = 0; i < _draw_set_num; i++) {
            for (int j = 0; j < nVertices; j++) {
                paVtxBuffer_data[(i*nVertices) + j] = unit_paVtxBuffer_data[j];
                paVtxBuffer_data[(i*nVertices) + j].index = (float)i; //+= (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paVtxBuffer_data);

        //�C���f�b�N�X�o�b�t�@���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        if (_is_65535) {
            paIdx32Buffer_data = NEW uint32_t[(nFaces*3) * _draw_set_num];
             for (int i = 0; i < _draw_set_num; i++) {
                 for (int j = 0; j < nFaces; j++) {
                     paIdx32Buffer_data[((i*nFaces*3)+(j*3)) + 0] = unit_paIndex32Buffer_data[j*3 + 0] + (nVertices*i);
                     paIdx32Buffer_data[((i*nFaces*3)+(j*3)) + 1] = unit_paIndex32Buffer_data[j*3 + 1] + (nVertices*i);
                     paIdx32Buffer_data[((i*nFaces*3)+(j*3)) + 2] = unit_paIndex32Buffer_data[j*3 + 2] + (nVertices*i);
                 }
             }
             GGAF_DELETEARR(unit_paIndex32Buffer_data);
        } else {
            paIdx16Buffer_data = NEW uint16_t[(nFaces*3) * _draw_set_num];
             for (int i = 0; i < _draw_set_num; i++) {
                 for (int j = 0; j < nFaces; j++) {
                     paIdx16Buffer_data[((i*nFaces*3)+(j*3)) + 0] = unit_paIndex16Buffer_data[j*3 + 0] + (nVertices*i);
                     paIdx16Buffer_data[((i*nFaces*3)+(j*3)) + 1] = unit_paIndex16Buffer_data[j*3 + 1] + (nVertices*i);
                     paIdx16Buffer_data[((i*nFaces*3)+(j*3)) + 2] = unit_paIndex16Buffer_data[j*3 + 2] + (nVertices*i);
                 }
             }
             GGAF_DELETEARR(unit_paIndex16Buffer_data);
        }


        //�}�e���A�����X�g���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        uint32_t* paFaceMaterials = NEW uint32_t[nFaces * _draw_set_num];
        for (int i = 0; i < _draw_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paFaceMaterials[(i*nFaces) + j] = pMeshesFront->_FaceMaterials[j];
            }
        }

        //�p�����[�^�����Z�b�g�����J��Ԃ��R�s�[�ō쐬
        papaIndexParam = NEW MeshSetModel::INDEXPARAM*[_draw_set_num];
        _paUint_material_list_grp_num = NEW UINT[_draw_set_num];
        for (int set_index = 0; set_index < _draw_set_num; set_index++) {
            MeshSetModel::INDEXPARAM* paParam = NEW MeshSetModel::INDEXPARAM[nFaces * (set_index+1)];
            int prev_materialno = -1;
            int materialno = 0;
            int paramno = 0;
            int faceNoCnt_break = 0;
            int prev_faceNoCnt_break = -1;
            UINT max_num_vertices = 0;
            UINT min_num_vertices = UINT_MAX;

            int faceNoCnt;
            for (faceNoCnt = 0; faceNoCnt < nFaces * (set_index+1); faceNoCnt++) {
                materialno = paFaceMaterials[faceNoCnt];
                if (prev_materialno != materialno) {
                    //_TRACE3_("BREAK! paramno="<<paramno);
                    prev_faceNoCnt_break = faceNoCnt_break;
                    faceNoCnt_break = faceNoCnt;

                    paParam[paramno].MaterialNo = materialno;
                    paParam[paramno].BaseVertexIndex = 0;
                    paParam[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�K���u���C�N���������ߕςȒl�ɂ��Ƃ�
                    paParam[paramno].NumVertices = UINT_MAX; //����u���C�N���ɐݒ�
                    paParam[paramno].StartIndex = faceNoCnt*3;
                    paParam[paramno].PrimitiveCount = UINT_MAX; //����u���C�N���ɐݒ�

                    if (faceNoCnt > 0) {
                        paParam[paramno-1].MinIndex = min_num_vertices;
                        paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                        paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                        //���Z�b�g
                        max_num_vertices = 0;
                        min_num_vertices = UINT_MAX;
                    }
                    paramno++;
                }
                if (_is_65535) {
                    if (max_num_vertices <  paIdx32Buffer_data[faceNoCnt*3 + 0]) {
                        max_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 0];
                    }
                    if (max_num_vertices <  paIdx32Buffer_data[faceNoCnt*3 + 1]) {
                        max_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 1];
                    }
                    if (max_num_vertices <  paIdx32Buffer_data[faceNoCnt*3 + 2]) {
                        max_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 2];
                    }
                    if (min_num_vertices >  paIdx32Buffer_data[faceNoCnt*3 + 0]) {
                        min_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 0];
                    }
                    if (min_num_vertices >  paIdx32Buffer_data[faceNoCnt*3 + 1]) {
                        min_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 1];
                    }
                    if (min_num_vertices >  paIdx32Buffer_data[faceNoCnt*3 + 2]) {
                        min_num_vertices = paIdx32Buffer_data[faceNoCnt*3 + 2];
                    }
                } else {
                    if (max_num_vertices <  paIdx16Buffer_data[faceNoCnt*3 + 0]) {
                        max_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 0];
                    }
                    if (max_num_vertices <  paIdx16Buffer_data[faceNoCnt*3 + 1]) {
                        max_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 1];
                    }
                    if (max_num_vertices <  paIdx16Buffer_data[faceNoCnt*3 + 2]) {
                        max_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 2];
                    }
                    if (min_num_vertices >  paIdx16Buffer_data[faceNoCnt*3 + 0]) {
                        min_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 0];
                    }
                    if (min_num_vertices >  paIdx16Buffer_data[faceNoCnt*3 + 1]) {
                        min_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 1];
                    }
                    if (min_num_vertices >  paIdx16Buffer_data[faceNoCnt*3 + 2]) {
                        min_num_vertices = paIdx16Buffer_data[faceNoCnt*3 + 2];
                    }
                }
                prev_materialno = materialno;
            }
            if (nFaces > 0) {
                paParam[paramno-1].MinIndex = min_num_vertices;
                paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
            }

            papaIndexParam[set_index] = NEW MeshSetModel::INDEXPARAM[paramno];
            for (int i = 0; i < paramno; i++) {
                papaIndexParam[set_index][i].MaterialNo = paParam[i].MaterialNo;
                papaIndexParam[set_index][i].BaseVertexIndex = paParam[i].BaseVertexIndex;
                papaIndexParam[set_index][i].MinIndex = paParam[i].MinIndex;
                papaIndexParam[set_index][i].NumVertices = paParam[i].NumVertices;
                papaIndexParam[set_index][i].StartIndex = paParam[i].StartIndex;
                papaIndexParam[set_index][i].PrimitiveCount = paParam[i].PrimitiveCount;
            }

            _paUint_material_list_grp_num[set_index] = paramno;
            delete[] paParam;
        }

        GGAF_DELETEARR(paFaceMaterials);

        //���f���ɕێ�������
        _pModel3D = pModel3D;
        _pMeshesFront = pMeshesFront;
        _nFaces = _pMeshesFront->_nFaces;
        if (_is_65535) {
            _paIndex32Buffer_data = paIdx32Buffer_data;
        } else {
            _paIndex16Buffer_data = paIdx16Buffer_data;
        }
        _paVtxBuffer_data = paVtxBuffer_data;
        _papaIndexParam = papaIndexParam;

        //�}�e���A���ݒ�
        setMaterial(pMeshesFront);
    }


    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //���_�o�b�t�@�쐬
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _draw_set_num,
                D3DUSAGE_WRITEONLY,
                MeshSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_id));
        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *paVertexBuffer;
        hr = _paVertexBuffer->Lock(
                                      0,
                                      _size_vertices * _draw_set_num,
                                      (void**)&paVertexBuffer,
                                      0
                                    );
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);

        memcpy(
          paVertexBuffer,
          _paVtxBuffer_data,
          _size_vertices * _draw_set_num
        ); //paVertexBuffer �� paVertex
        _paVertexBuffer->Unlock();
    }


    //�������ރC���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        if (_is_65535) {
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                   sizeof(uint32_t) * _nFaces * 3 * _draw_set_num,
                                    D3DUSAGE_WRITEONLY,
                                    D3DFMT_INDEX32,
                                    D3DPOOL_DEFAULT,
                                    &(_paIndexBuffer),
                                    nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_id));
            void* paIndexBuffer;
            _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
            memcpy(paIndexBuffer, _paIndex32Buffer_data, sizeof(uint32_t) * _nFaces * 3 * _draw_set_num);
            _paIndexBuffer->Unlock();
        } else {
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                   sizeof(uint16_t) * _nFaces * 3 * _draw_set_num,
                                    D3DUSAGE_WRITEONLY,
                                    D3DFMT_INDEX16,
                                    D3DPOOL_DEFAULT,
                                    &(_paIndexBuffer),
                                    nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_id));
            void* paIndexBuffer;
            _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
            memcpy(paIndexBuffer, _paIndex16Buffer_data, sizeof(uint16_t) * _nFaces * 3 * _draw_set_num);
            _paIndexBuffer->Unlock();
        }

    }

    if (_papTextureConnection == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    _TRACE3_("_model_id=" << _model_id << " end");
}

void MeshSetModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MeshSetModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //�e�N�X�`�������
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
    _TRACE3_("_model_id=" << _model_id << " end");
}

MeshSetModel::~MeshSetModel() {
    GGAF_DELETE(_pModel3D);
    //_pMeshesFront �� _pModel3D ��DELETE���Ă���̂ł���K�v�͖���
    _pMeshesFront = nullptr;
    if (_papaIndexParam) {
        for (int i = 0; i < _draw_set_num; i++) {
            GGAF_DELETEARR(_papaIndexParam[i]);
        }
    }
    GGAF_DELETEARR(_papaIndexParam);
    GGAF_DELETEARR(_paUint_material_list_grp_num);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR_NULLABLE(_paIndex16Buffer_data);
    GGAF_DELETEARR_NULLABLE(_paIndex32Buffer_data);
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}

