#include "jp/ggaf/dx/model/MeshModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MeshActor.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

using namespace GgafDx;

//DWORD MeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
DWORD MeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX3 |
                        D3DFVF_TEXCOORDSIZE2(0) | // real texture coord
                        D3DFVF_TEXCOORDSIZE3(1) | // tangent
                        D3DFVF_TEXCOORDSIZE3(2)   // binormal
                                    );
MeshModel::MeshModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_model |= Obj_GgafDx_MeshModel;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _paIndexBuffer_data = nullptr;
    _paIndexParam = nullptr;
    _material_list_grp_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _nVertices = 0;
    _nFaces = 0;
    _max_draw_set_num = 1;
}

HRESULT MeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    //�ΏۃA�N�^�[
    //MeshActor* pTargetActor = (MeshActor*)prm_pActor_target;
    const FigureActor* const pTargetActor = prm_pActor_target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    MeshEffect* const pMeshEffect = (MeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(MeshModel::FVF);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        const INDEXPARAM& idxparam = _paIndexParam[i];
        material_no = idxparam.MaterialNo;
        if (ModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //�}�e���A��0�Ԃ́A���ʂɋK��̃e�N�X�`����ݒ肷��d�l
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("MeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(CONFIG::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            //�{���f���`�揉��
            if (pEffect_active) {
                _TRACE4_("�O�� _pEffect_active != pMeshEffect ?? " <<pEffect_active<<"!="<<pMeshEffect<<"?? (" <<(pEffect_active->_effect_name)<<"!="<<(pMeshEffect->_effect_name)<<")");
                _TRACE4_("�O�� ::_hash_technique_last_draw != prm_pActor_target->_hash_technique ?? " <<FigureActor::_hash_technique_last_draw<<"!="<<prm_pActor_target->_hash_technique<<"?? (prm_pActor_target=" <<prm_pActor_target<<" "<<(prm_pActor_target->getName())<<")");
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
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            hr = pID3DXEffect->Begin( &_num_pass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pMeshEffect->_begin) {
                throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            //�O��`��Ɠ������f��
            hr = pID3DXEffect->CommitChanges(); //�}�e���A�����R�~�b�g���Ȃ���΂����Ȃ��B
            checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
        }
        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
        if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
            for (UINT pass = 1; pass < _num_pass; pass++) {
                hr = pID3DXEffect->BeginPass(pass);
                checkDxException(hr, D3D_OK, pass+1<<"�p�X�� BeginPass("<<pass<<") �Ɏ��s���܂����B");
                pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                              idxparam.BaseVertexIndex,
                                              idxparam.MinIndex,
                                              idxparam.NumVertices,
                                              idxparam.StartIndex,
                                              idxparam.PrimitiveCount);
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "�P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
        }
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    }
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void MeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data == nullptr) {
        //�yMeshModel�č\�z�i���������j�����T�v�z
        //�P�j���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �� new
        //�Q�jX�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �ɗ������ށB
        //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ MeshModel �Ɏ��̃����o���쐬�B
        //      �E���_�o�b�t�@�̎ʂ�
        //      �E���_�C���f�b�N�X�o�b�t�@�̎ʂ�
        //      �E�}�e���A���z��(�v�f�����}�e���A����)
        //      �E�e�N�X�`���z��(�v�f�����}�e���A����)
        //      �EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω�������)
        ModelManager* pModelManager = pGOD->_pModelManager;
        ModelManager::MeshXFileFmt xdata;

        std::string model_def_file = std::string(_model_id) + ".meshx";
        std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);

        std::string xfile = std::string(_model_id) + ".x";
        std::string xfilepath = "";

        if (model_def_filepath != "") {
            pModelManager->obtainMeshModelInfo(&xdata, model_def_filepath);
            _matBaseTransformMatrix = xdata.BaseTransformMatrix;
            _draw_set_num = xdata.DrawSetNum;
            if (_draw_set_num != 1) {
                _TRACE_("MeshModel::restore() �{���f���� "<<_model_id<<" �̓����`��Z�b�g���� 1 �ɏ㏑������܂����B�i_draw_set_num="<<_draw_set_num<<" �͖�������܂����B�j");
                _draw_set_num = 1;
            }
        } else {
            xdata.XFileNum = 1;
            xdata.XFileNames = NEW std::string[1];
            xdata.XFileNames[0] = xfile;
            xdata.DrawSetNum = 1;
            D3DXMatrixIdentity(&(xdata.BaseTransformMatrix));
            _TRACE_("MeshModel::restore() model_def_file="<<model_def_file<<" �����݂��Ȃ��̂ŁA���ʂ� xfile="<<xfile<<" ����݂��񂾂���I�i�ׁA�ׂɁE�E���j");
        }
        xfilepath = Model::getXFilePath(xdata.XFileNames[0]);
        HRESULT hr;
        //�������ޒ��_�o�b�t�@�f�[�^�쐬
        ToolBox::IO_Model_X iox;
        Frm::Model3D* pModel3D = NEW Frm::Model3D();
        bool r = iox.Load(xfilepath, pModel3D);
        if (r == false) {
            throwCriticalException("X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfilepath);
        }
        //���b�V������������O�ɁA�����m�ۂ��Ă���
        int nMesh = (int)pModel3D->_Meshes.size();
        uint16_t* paNumVertices = NEW uint16_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = pModel3D->_Meshes.begin();
                iteMeshes != pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }

        pModel3D->ConcatenateMeshes(); //���b�V�����q����
        Frm::Mesh* pMeshesFront = pModel3D->_Meshes.front();
        _nVertices = pMeshesFront->_nVertices; //���b�V���A����̑����_��
        _nFaces = pMeshesFront->_nFaces;       //���b�V���A����̑��ʐ�
//        nFaceNormals = pMeshesFront->_nFaceNormals; //���b�V���A����̑��@����
        _paVtxBuffer_data = NEW MeshModel::VERTEX[_nVertices];
        _size_vertices = sizeof(MeshModel::VERTEX) * _nVertices;
        _size_vertex_unit = sizeof(MeshModel::VERTEX);
        UINT nTextureCoords = pMeshesFront->_nTextureCoords;
        if (_nVertices < nTextureCoords) {
            _TRACE3_("nTextureCoords="<<nTextureCoords<<"/_nVertices="<<_nVertices);
            _TRACE3_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }

        //���_�o�b�t�@�쐬�J�n�I
        //�@���ȊO�ݒ�
        for (UINT i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data[i].x = pMeshesFront->_Vertices[i].data[0];
            _paVtxBuffer_data[i].y = pMeshesFront->_Vertices[i].data[1];
            _paVtxBuffer_data[i].z = pMeshesFront->_Vertices[i].data[2];
            _paVtxBuffer_data[i].nx = 0.0f;
            _paVtxBuffer_data[i].ny = 0.0f;
            _paVtxBuffer_data[i].nz = 0.0f;
            _paVtxBuffer_data[i].color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[�͍��̏��g���Ă��Ȃ�
            if (i < nTextureCoords) {
                _paVtxBuffer_data[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                _paVtxBuffer_data[i].tv = pMeshesFront->_TextureCoords[i].data[1];
            } else {
                _paVtxBuffer_data[i].tu = 0.0f;
                _paVtxBuffer_data[i].tv = 0.0f;
            }
            _paVtxBuffer_data[i].tan_x = 0.0f;
            _paVtxBuffer_data[i].tan_y = 0.0f;
            _paVtxBuffer_data[i].tan_z = 0.0f;
            _paVtxBuffer_data[i].bin_x = 0.0f;
            _paVtxBuffer_data[i].bin_y = 0.0f;
            _paVtxBuffer_data[i].bin_z = 0.0f;
        }

        //���_�o�b�t�@�쐬
        prepareVtx((void*)_paVtxBuffer_data, _size_vertex_unit,
                    pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);

        //����
        FLOAT model_bounding_sphere_radius;
        for (UINT i = 0; i < _nVertices; i++) {
            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data[i].x * _paVtxBuffer_data[i].x +
                                                        _paVtxBuffer_data[i].y * _paVtxBuffer_data[i].y +
                                                        _paVtxBuffer_data[i].z * _paVtxBuffer_data[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        //�C���f�b�N�X�o�b�t�@�o�^
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
        for (UINT i = 0; i < _nFaces; i++) {
            _paIndexBuffer_data[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
            _paIndexBuffer_data[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
            _paIndexBuffer_data[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        MeshModel::INDEXPARAM* paParam_tmp = NEW MeshModel::INDEXPARAM[_nFaces]; //�ō��Ƀ}�e���A�����o���o���������ꍇnFaces�K�v

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < _nFaces; faceNoCnt++) {
            materialno = pMeshesFront->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //_TRACE3_("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam_tmp[paramno].MaterialNo = materialno;
                paParam_tmp[paramno].BaseVertexIndex = 0;
                paParam_tmp[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�K���u���C�N���������ߕςȒl�ɂ��Ƃ�
                paParam_tmp[paramno].NumVertices = UINT_MAX; //����u���C�N���ɐݒ�
                paParam_tmp[paramno].StartIndex = faceNoCnt*3;
                paParam_tmp[paramno].PrimitiveCount = UINT_MAX; //����u���C�N���ɐݒ�

                if (faceNoCnt > 0) {
                    paParam_tmp[paramno-1].MinIndex = min_num_vertices;
                    paParam_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //���Z�b�g
                    max_num_vertices = 0;
                    min_num_vertices = UINT_MAX;
                }
                paramno++;
            }

            if (max_num_vertices <  _paIndexBuffer_data[faceNoCnt*3 + 0]) {
                max_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 0];
            }
            if (max_num_vertices <  _paIndexBuffer_data[faceNoCnt*3 + 1]) {
                max_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 1];
            }
            if (max_num_vertices <  _paIndexBuffer_data[faceNoCnt*3 + 2]) {
                max_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 2];
            }
            if (min_num_vertices >  _paIndexBuffer_data[faceNoCnt*3 + 0]) {
                min_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 0];
            }
            if (min_num_vertices >  _paIndexBuffer_data[faceNoCnt*3 + 1]) {
                min_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 1];
            }
            if (min_num_vertices >  _paIndexBuffer_data[faceNoCnt*3 + 2]) {
                min_num_vertices = _paIndexBuffer_data[faceNoCnt*3 + 2];
            }
            prev_materialno = materialno;
        }
        if (_nFaces > 0) {
            paParam_tmp[paramno-1].MinIndex = min_num_vertices;
            paParam_tmp[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam_tmp[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        _paIndexParam = NEW MeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            _paIndexParam[i].MaterialNo      = paParam_tmp[i].MaterialNo;
            _paIndexParam[i].BaseVertexIndex = paParam_tmp[i].BaseVertexIndex;
            _paIndexParam[i].MinIndex        = paParam_tmp[i].MinIndex;
            _paIndexParam[i].NumVertices     = paParam_tmp[i].NumVertices;
            _paIndexParam[i].StartIndex      = paParam_tmp[i].StartIndex;
            _paIndexParam[i].PrimitiveCount  = paParam_tmp[i].PrimitiveCount;
        }
        _material_list_grp_num = paramno;

        delete[] paParam_tmp;

        //�}�e���A���ݒ�
        if (_paMaterial_default == nullptr) {
            setMaterial(pMeshesFront);
        }


        GGAF_DELETE(pModel3D);
        //pMeshesFront �� _pModel3D ��DELETE���Ă���̂ł���K�v�͖���
        pMeshesFront = nullptr;
    }

    if (_pVertexBuffer == nullptr) {
        HRESULT hr;
        //���_�o�b�t�@�쐬
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                MeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_id));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);
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
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_id));
        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , _paIndexBuffer_data , sizeof(WORD) * _nFaces * 3);
        _pIndexBuffer->Unlock();
    }

    //�e�N�X�`���쐬
    if (!_papTextureConnection) {
        ModelManager* pModelManager = pGOD->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MeshModel::release() {
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
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    _TRACE3_("_model_id=" << _model_id << " end");
}

MeshModel::~MeshModel() {
    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_data);
    GGAF_DELETEARR(_paIndexParam);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}





//        //�f�o�b�O
//        _TRACE_("#���_�o�b�t�@ _nVertices="<<_nVertices);
//        float x,y,z,nx,ny,nz,tu,tv,tan_x,tan_y,tan_z,bin_x,bin_y,bin_z;
//        for (UINT i = 0; i < _nVertices; i++) {
//            x = _paVtxBuffer_data[i].x;
//            y = _paVtxBuffer_data[i].y;
//            z = _paVtxBuffer_data[i].z;
//            nx = _paVtxBuffer_data[i].nx;
//            ny = _paVtxBuffer_data[i].ny;
//            nz = _paVtxBuffer_data[i].nz;
//            tu = _paVtxBuffer_data[i].tu;
//            tv = _paVtxBuffer_data[i].tv;
//            tan_x = _paVtxBuffer_data[i].tan_x;
//            tan_y = _paVtxBuffer_data[i].tan_y;
//            tan_z = _paVtxBuffer_data[i].tan_z;
//            bin_x = _paVtxBuffer_data[i].bin_x;
//            bin_y = _paVtxBuffer_data[i].bin_y;
//            bin_z = _paVtxBuffer_data[i].bin_z;
//            //�f�o�b�O
//            //_TRACE_("���_["<<i<<"] pos("<<x<<","<<y<<","<<z<<")\tuv("<<tu<<","<<tv<<")\tn("<<nx<<","<<ny<<","<<nz<<")\tt("<<tan_x<<","<<tan_y<<","<<tan_z<<")\tb("<<bin_x<<","<<bin_y<<","<<bin_z<<")");
//        }


//    {
//        //�f�o�b�O
//        _TRACE_("#���_�o�b�t�@ _nVertices="<<_nVertices);
//        float x,y,z,nx,ny,nz,tu,tv;
//        for (UINT i = 0; i < _nVertices; i++) {
//            x = _paVtxBuffer_data[i].x;
//            y = _paVtxBuffer_data[i].y;
//            z = _paVtxBuffer_data[i].z;
//            nx = _paVtxBuffer_data[i].nx;
//            ny = _paVtxBuffer_data[i].ny;
//            nz = _paVtxBuffer_data[i].nz;
//            tu = _paVtxBuffer_data[i].tu;
//            tv = _paVtxBuffer_data[i].tv;
//
//            _TRACE_("���_["<<i<<"] "<<x<<";"<<y<<";"<<z<<";,\t"<<nx<<";"<<ny<<";"<<nz<<";,\t"<<tu<<";"<<tv<<";,");
//        }
//
//
//        _TRACE_("#�C���f�b�N�X�o�b�t�@ _nFaces="<<_nFaces);
//        WORD vtx1,vtx2,vtx3;
//        for (int face = 0; face < _nFaces; face++) {
//            vtx1 = _paIndexBuffer_data[face*3 + 0];
//            vtx2 = _paIndexBuffer_data[face*3 + 1];
//            vtx3 = _paIndexBuffer_data[face*3 + 2];
//            _TRACE_("��["<<face<<"] 3;"<<vtx1<<","<<vtx2<<","<<vtx3<<";,");
//        }
//
//        _TRACE_("�}�e���A��  num_materials="<<num_materials);
//        float a,r,g,b;
//        for (int i = 0; i < num_materials; i++) {
//            a = paMaterial[i].Diffuse.a;
//            r = paMaterial[i].Diffuse.r;
//            g = paMaterial[i].Diffuse.g;
//            b = paMaterial[i].Diffuse.b;
//            _TRACE_("nMaterial["<<i<<"] Diffuse(rgba)=("<<r<<","<<g<<","<<b<<","<<a<<")");
//            a = paMaterial[i].Ambient.a;
//            r = paMaterial[i].Ambient.r;
//            g = paMaterial[i].Ambient.g;
//            b = paMaterial[i].Ambient.b;
//            _TRACE_("nMaterial["<<i<<"] Ambient(rgba)=("<<r<<","<<g<<","<<b<<","<<a<<")");
//        }
//
//        _TRACE_("#�}�e���A�����X�g _material_list_grp_num="<< _material_list_grp_num);
//        for (UINT i = 0; i < _material_list_grp_num; i++) {
//            int material_no = _paIndexParam[i].MaterialNo;
//            _TRACE_("MaterialGrp["<<i<<"] "<<material_no<<",");
//        }
//
//        _TRACE_("#IndexParam  _material_list_grp_num="<< _material_list_grp_num);
//        UINT MaterialNo;
//        INT BaseVertexIndex;
//        UINT MinIndex;
//        UINT NumVertices;
//        UINT StartIndex;
//        UINT PrimitiveCount;
//        for (UINT i = 0; i < _material_list_grp_num; i++) {
//            MaterialNo = _paIndexParam[i].MaterialNo;
//            BaseVertexIndex = _paIndexParam[i].BaseVertexIndex;
//            MinIndex = _paIndexParam[i].MinIndex;
//            NumVertices = _paIndexParam[i].NumVertices;
//            StartIndex = _paIndexParam[i].StartIndex;
//            PrimitiveCount = _paIndexParam[i].PrimitiveCount;
//            _TRACE_("MaterialGrp["<<i<<"] MaterialNo="<<MaterialNo);
//            _TRACE_("MaterialGrp["<<i<<"] BaseVertexIndex="<<BaseVertexIndex);
//            _TRACE_("MaterialGrp["<<i<<"] MinIndex="<<MinIndex);
//            _TRACE_("MaterialGrp["<<i<<"] NumVertices="<<MaterialNo);
//            _TRACE_("MaterialGrp["<<i<<"] StartIndex="<<StartIndex);
//            _TRACE_("MaterialGrp["<<i<<"] PrimitiveCount="<<PrimitiveCount);
//        }
//    }


