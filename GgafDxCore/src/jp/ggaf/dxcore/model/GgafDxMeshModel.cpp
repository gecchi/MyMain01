#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

//DWORD GgafDxMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
DWORD GgafDxMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX3 |
                                    D3DFVF_TEXCOORDSIZE2(0) | // real texture coord
                                    D3DFVF_TEXCOORDSIZE3(1) | // tangent
                                    D3DFVF_TEXCOORDSIZE3(2)   // binormal
                                    );
GgafDxMeshModel::GgafDxMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxMeshModel::GgafDxMeshModel(" << _model_name << ")");
//    _pModel3D = nullptr;
//    _pMeshesFront = nullptr;

    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _paVtxBuffer_org = nullptr;
    _paIdxBuffer_org = nullptr;
    _paIndexParam = nullptr;
//    _pModel3D = nullptr;
//    _pMeshesFront = nullptr;
    _material_list_grp_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDxMeshModel;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreMeshModel(GgafDxMeshModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

//�`��
HRESULT GgafDxMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�ΏۃA�N�^�[
    //GgafDxMeshActor* pTargetActor = (GgafDxMeshActor*)prm_pActor_target;
    const GgafDxFigureActor* const pTargetActor = prm_pActor_target;
    //�Ώ�MeshActor�̃G�t�F�N�g���b�p
    GgafDxMeshEffect* const pMeshEffect = (GgafDxMeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        //���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxMeshModel::FVF);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        const INDEXPARAM& idxparam = _paIndexParam[i];
        material_no = idxparam.MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //�}�e���A��0�Ԃ́A���ʂɋK��̃e�N�X�`����ݒ肷��d�l
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("GgafDxMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(PROPERTY::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((pEffect_active != pMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            //�{���f���`�揉��
            if (pEffect_active) {
                _TRACE4_("�O�� _pEffect_active != pMeshEffect ?? " <<pEffect_active<<"!="<<pMeshEffect<<"?? (" <<(pEffect_active->_effect_name)<<"!="<<(pMeshEffect->_effect_name)<<")");
                _TRACE4_("�O�� ::_hash_technique_last_draw != prm_pActor_target->_hash_technique ?? " <<GgafDxFigureActor::_hash_technique_last_draw<<"!="<<prm_pActor_target->_hash_technique<<"?? (prm_pActor_target=" <<prm_pActor_target<<" "<<(prm_pActor_target->getName())<<")");
                _TRACE4_("GgafDxMeshModel::draw() EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() EndPass() �Ɏ��s���܂����B");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() End() �Ɏ��s���܂����B");
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
            _TRACE4_("GgafDxMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

            _TRACE4_("GgafDxMeshModel::draw() BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            hr = pID3DXEffect->Begin( &_num_pass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() Begin() �Ɏ��s���܂����B");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() BeginPass(0) �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pMeshEffect->_begin) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            //�O��`��Ɠ������f��
            hr = pID3DXEffect->CommitChanges(); //�}�e���A�����R�~�b�g���Ȃ���΂����Ȃ��B
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() CommitChanges() �Ɏ��s���܂����B");
        }
        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
        if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() �P�p�X�� EndPass() �Ɏ��s���܂����B");
            for (UINT pass = 1; pass < _num_pass; pass++) {
                hr = pID3DXEffect->BeginPass(pass);
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() "<<pass+1<<"�p�X�� BeginPass("<<pass<<") �Ɏ��s���܂����B");
                pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                              idxparam.BaseVertexIndex,
                                              idxparam.MinIndex,
                                              idxparam.NumVertices,
                                              idxparam.StartIndex,
                                              idxparam.PrimitiveCount);
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() "<<pass+1<<"�p�X�� EndPass() �Ɏ��s���܂����B");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() �P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
        }
        GgafGod::_num_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMeshModel::restore() {
    _TRACE3_("GgafDxMeshModel::restore() " << _model_name << " start");
    //�yGgafDxMeshModel�č\�z�i���������j�����T�v�z
    //�P�j���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �� new
    //�Q�jX�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �ɗ������ށB
    //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ GgafDxMeshModel �Ɏ��̃����o���쐬�B
    //      �E���_�o�b�t�@�̎ʂ�
    //      �E���_�C���f�b�N�X�o�b�t�@�̎ʂ�
    //      �E�}�e���A���z��(�v�f�����}�e���A����)
    //      �E�e�N�X�`���z��(�v�f�����}�e���A����)
    //      �EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω�������)


    std::string xfile_name = GgafDxModelManager::getMeshFileName(_model_name);
    if (xfile_name == "") {
        throwGgafCriticalException("GgafDxModelManager::restoreMeshModel ���b�V���t�@�C��(*.x)��������܂���B_model_name="<<_model_name);
    }
    HRESULT hr;

    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X iox;



    GgafDxMeshModel::INDEXPARAM* paIndexParam = nullptr;
    GgafDxMeshModel::VERTEX*     paVtxBuffer_org = nullptr;
    WORD*                        paIdxBuffer_org = nullptr;
    GgafDxTextureConnection**    papTextureConnection = nullptr;
    int nVertices = 0;
    int nFaces = 0;
//    int nFaceNormals = 0;
    if (_paVtxBuffer_org == nullptr) {
        Frm::Model3D* pModel3D = NEW Frm::Model3D();
        bool r = iox.Load(xfile_name, pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMeshModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfile_name);
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
        nVertices = pMeshesFront->_nVertices; //���b�V���A����̑����_��
        nFaces = pMeshesFront->_nFaces;       //���b�V���A����̑��ʐ�
//        nFaceNormals = pMeshesFront->_nFaceNormals; //���b�V���A����̑��@����
        paVtxBuffer_org = NEW GgafDxMeshModel::VERTEX[nVertices];
        _size_vertices = sizeof(GgafDxMeshModel::VERTEX) * nVertices;
        _size_vertex_unit = sizeof(GgafDxMeshModel::VERTEX);
        int nTextureCoords = pMeshesFront->_nTextureCoords;
        if (nVertices < nTextureCoords) {
            _TRACE3_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            _TRACE3_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }

        //���_�o�b�t�@�쐬�J�n�I
        //�@���ȊO�ݒ�
        FLOAT model_bounding_sphere_radius;
        for (int i = 0; i < nVertices; i++) {
            paVtxBuffer_org[i].x = pMeshesFront->_Vertices[i].data[0];
            paVtxBuffer_org[i].y = pMeshesFront->_Vertices[i].data[1];
            paVtxBuffer_org[i].z = pMeshesFront->_Vertices[i].data[2];
            paVtxBuffer_org[i].nx = 0.0f;
            paVtxBuffer_org[i].ny = 0.0f;
            paVtxBuffer_org[i].nz = 0.0f;
            paVtxBuffer_org[i].color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[�͍��̏��g���Ă��Ȃ�
            if (i < nTextureCoords) {
                paVtxBuffer_org[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                paVtxBuffer_org[i].tv = pMeshesFront->_TextureCoords[i].data[1];
            } else {
                paVtxBuffer_org[i].tu = 0.0f;
                paVtxBuffer_org[i].tv = 0.0f;
            }
            paVtxBuffer_org[i].tan_x = 0.0f;
            paVtxBuffer_org[i].tan_y = 0.0f;
            paVtxBuffer_org[i].tan_z = 0.0f;
            paVtxBuffer_org[i].bin_x = 0.0f;
            paVtxBuffer_org[i].bin_y = 0.0f;
            paVtxBuffer_org[i].bin_z = 0.0f;


            //����
            model_bounding_sphere_radius = (FLOAT)(sqrt(paVtxBuffer_org[i].x * paVtxBuffer_org[i].x +
                                                        paVtxBuffer_org[i].y * paVtxBuffer_org[i].y +
                                                        paVtxBuffer_org[i].z * paVtxBuffer_org[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        //���_�o�b�t�@�쐬
        prepareVtx((void*)paVtxBuffer_org, _size_vertex_unit,
                    pModel3D, paNumVertices);

        GGAF_DELETE(paNumVertices);

        //�C���f�b�N�X�o�b�t�@�o�^
        paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            paIdxBuffer_org[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
            paIdxBuffer_org[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
            paIdxBuffer_org[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDxMeshModel::INDEXPARAM* paParam = NEW GgafDxMeshModel::INDEXPARAM[nFaces]; //�ō��Ƀ}�e���A�����o���o���������ꍇnFaces�K�v

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < nFaces; faceNoCnt++) {
            materialno = pMeshesFront->_FaceMaterials[faceNoCnt];
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

            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 0]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 1]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 2]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 2];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 0]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 1]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 2]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 2];
            }
            prev_materialno = materialno;
        }
        if (nFaces > 0) {
            paParam[paramno-1].MinIndex = min_num_vertices;
            paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        paIndexParam = NEW GgafDxMeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            paIndexParam[i].MaterialNo = paParam[i].MaterialNo;
            paIndexParam[i].BaseVertexIndex = paParam[i].BaseVertexIndex;
            paIndexParam[i].MinIndex = paParam[i].MinIndex;
            paIndexParam[i].NumVertices = paParam[i].NumVertices;
            paIndexParam[i].StartIndex = paParam[i].StartIndex;
            paIndexParam[i].PrimitiveCount = paParam[i].PrimitiveCount;
        }
        _material_list_grp_num = paramno;

        delete[] paParam;

        _paVtxBuffer_org = paVtxBuffer_org;
        _paIdxBuffer_org = paIdxBuffer_org;
        _paIndexParam = paIndexParam;


        //�}�e���A���ݒ�
        if (_paMaterial_default == nullptr) {
            D3DMATERIAL9* paMaterial = nullptr;
            int num_materials = 0;
            setMaterial(pMeshesFront,
                        &num_materials, &paMaterial, &papTextureConnection);
            _paMaterial_default = paMaterial;
            _num_materials = num_materials;
            _papTextureConnection = papTextureConnection;
        }

        GGAF_DELETE(pModel3D);
        //pMeshesFront �� _pModel3D ��DELETE���Ă���̂ł���K�v�͖���
        pMeshesFront = nullptr;
    }

    if (_pVertexBuffer == nullptr) {
        //���_�o�b�t�@�쐬
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxMeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);
        memcpy(pVertexBuffer, paVtxBuffer_org, _size_vertices); //pVertexBuffer �� paVertex
        _pVertexBuffer->Unlock();
    }


    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (_pIndexBuffer == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_name));
        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        _pIndexBuffer->Unlock();
    }




    //���f���ɕێ�������
//    _pModel3D = pModel3D;
//    _pMeshesFront = pMeshesFront;






//        //�f�o�b�O
//        _TRACE_("#���_�o�b�t�@ nVertices="<<nVertices);
//        float x,y,z,nx,ny,nz,tu,tv,tan_x,tan_y,tan_z,bin_x,bin_y,bin_z;
//        for (int i = 0; i < nVertices; i++) {
//            x = paVtxBuffer_org[i].x;
//            y = paVtxBuffer_org[i].y;
//            z = paVtxBuffer_org[i].z;
//            nx = paVtxBuffer_org[i].nx;
//            ny = paVtxBuffer_org[i].ny;
//            nz = paVtxBuffer_org[i].nz;
//            tu = paVtxBuffer_org[i].tu;
//            tv = paVtxBuffer_org[i].tv;
//            tan_x = paVtxBuffer_org[i].tan_x;
//            tan_y = paVtxBuffer_org[i].tan_y;
//            tan_z = paVtxBuffer_org[i].tan_z;
//            bin_x = paVtxBuffer_org[i].bin_x;
//            bin_y = paVtxBuffer_org[i].bin_y;
//            bin_z = paVtxBuffer_org[i].bin_z;
//            //�f�o�b�O
//            //_TRACE_("���_["<<i<<"] pos("<<x<<","<<y<<","<<z<<")\tuv("<<tu<<","<<tv<<")\tn("<<nx<<","<<ny<<","<<nz<<")\tt("<<tan_x<<","<<tan_y<<","<<tan_z<<")\tb("<<bin_x<<","<<bin_y<<","<<bin_z<<")");
//        }


//    {
//        //�f�o�b�O
//        _TRACE_("#���_�o�b�t�@ nVertices="<<nVertices);
//        float x,y,z,nx,ny,nz,tu,tv;
//        for (int i = 0; i < nVertices; i++) {
//            x = paVtxBuffer_org[i].x;
//            y = paVtxBuffer_org[i].y;
//            z = paVtxBuffer_org[i].z;
//            nx = paVtxBuffer_org[i].nx;
//            ny = paVtxBuffer_org[i].ny;
//            nz = paVtxBuffer_org[i].nz;
//            tu = paVtxBuffer_org[i].tu;
//            tv = paVtxBuffer_org[i].tv;
//
//            _TRACE_("���_["<<i<<"] "<<x<<";"<<y<<";"<<z<<";,\t"<<nx<<";"<<ny<<";"<<nz<<";,\t"<<tu<<";"<<tv<<";,");
//        }
//
//
//        _TRACE_("#�C���f�b�N�X�o�b�t�@ nFaces="<<nFaces);
//        WORD vtx1,vtx2,vtx3;
//        for (int face = 0; face < nFaces; face++) {
//            vtx1 = paIdxBuffer_org[face*3 + 0];
//            vtx2 = paIdxBuffer_org[face*3 + 1];
//            vtx3 = paIdxBuffer_org[face*3 + 2];
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
//            MaterialNo = paIndexParam[i].MaterialNo;
//            BaseVertexIndex = paIndexParam[i].BaseVertexIndex;
//            MinIndex = paIndexParam[i].MinIndex;
//            NumVertices = paIndexParam[i].NumVertices;
//            StartIndex = paIndexParam[i].StartIndex;
//            PrimitiveCount = paIndexParam[i].PrimitiveCount;
//            _TRACE_("MaterialGrp["<<i<<"] MaterialNo="<<MaterialNo);
//            _TRACE_("MaterialGrp["<<i<<"] BaseVertexIndex="<<BaseVertexIndex);
//            _TRACE_("MaterialGrp["<<i<<"] MinIndex="<<MinIndex);
//            _TRACE_("MaterialGrp["<<i<<"] NumVertices="<<MaterialNo);
//            _TRACE_("MaterialGrp["<<i<<"] StartIndex="<<StartIndex);
//            _TRACE_("MaterialGrp["<<i<<"] PrimitiveCount="<<PrimitiveCount);
//        }
//    }
    _TRACE3_("GgafDxMeshModel::restore() " << _model_name << " end");
}

void GgafDxMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMeshModel::release() {
    _TRACE3_("GgafDxMeshModel::release() " << _model_name << " start");
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
    GGAF_DELETEARR(_paVtxBuffer_org);
    GGAF_DELETEARR(_paIdxBuffer_org);
    GGAF_DELETEARR(_paIndexParam);
    GGAF_DELETEARR(_paMaterial_default);
    _TRACE3_("GgafDxMeshModel::release() " << _model_name << " end");
}

GgafDxMeshModel::~GgafDxMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}


