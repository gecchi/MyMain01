#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxConfig.h"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMorphMeshModel::GgafDxMorphMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _TRACE_("GgafDxMorphMeshModel::GgafDxMorphMeshModel(" << _model_name << ") Begin");
    // ���ʎ����N���X���w�肷�郂�f������"M/4/xxxxx"�Ƃ����`���ŁAGgafDxModelManager��
    // "M"����GgafDxMorphMeshModel�Ɣ��f���A"M"����菜����"4/XXXX"�����f�����Ƃ��Ĉ����B
    // prm_model_name �ɂ� "4/XXXX" ���A�n���Ă���B
    // �v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c����
    // ���f��������t�^�[�Q�b�g�����擾
    _TRACE_("GgafDxMorphMeshModel prm_model_name="<<prm_model_name);

    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() != 2) {
        throwGgafCriticalException("���f��ID�Ƀ��[�t�^�[�Q�b�g�����w�肳��Ă܂���Bprm_model_name="<<prm_model_name);
    } else {
        _morph_target_num = STOI(names[0]);
        _TRACE_("GgafDxMorphMeshModel ���[�t�^�[�Q�b�g���͎w�肠��A_morph_target_num="<<_morph_target_num);
        if (_morph_target_num > 6) {
            _TRACE_(FUNC_NAME<<" ���[�t�^�[�Q�b�g�����ő�6�ȏ�w�肳��Ă܂��B�Ӑ}���Ă��܂����H _morph_target_num="<<_morph_target_num<<"/_model_name="<<_model_name);
        }
    }

    _papModel3D = nullptr;
    _papMeshesFront = nullptr;

    _pVertexDeclaration = nullptr;
    _pVertexBuffer_primary = nullptr;
    _paIDirect3DVertexBuffer9_morph = nullptr;
    _pIndexBuffer = nullptr;
    _paVtxBuffer_data_primary = nullptr;
    _papaVtxBuffer_data_morph = nullptr;
    _paIndexBuffer_data = nullptr;
    _paIndexParam = nullptr;
    _material_list_grp_num = 0;
    _size_vertices_primary = 0;
    _size_vertex_unit_primary = 0;
    _size_vertices_morph = 0;
    _size_vertex_unit_morph = 0;

    _obj_model |= Obj_GgafDxMorphMeshModel;
}

HRESULT GgafDxMorphMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    _TRACE4_("GgafDxMorphMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());

    //�ΏۃA�N�^�[
    const GgafDxMorphMeshActor* const pTargetActor = (GgafDxMorphMeshActor*)prm_pActor_target;
    //�ΏۃA�N�^�[�̃G�t�F�N�g���b�p
    GgafDxMorphMeshEffect* const pMorphMeshEffect = (GgafDxMorphMeshEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    //���_�o�b�t�@�ݒ�
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetVertexDeclaration( _pVertexDeclaration); //���_�t�H�[�}�b�g
        pDevice->SetStreamSource(0, _pVertexBuffer_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            pDevice->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //�C���f�b�N�X�o�b�t�@�ݒ�
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) �Ɏ��s���܂����B");
    }

    //�`��
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        const UINT material_no = _paIndexParam[i].MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //�}�e���A��0�Ԃ́A���ʂɋK��̃e�N�X�`����ݒ肷��d�l
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("GgafDxMorphMeshModel::draw("<<prm_pActor_target->getName()<<") �e�N�X�`��������܂���B"<<(CONFIG::WHITE_TEXTURE)<<"���ݒ肳���ׂ��ł��B���������ł�");
                //������΃e�N�X�`������
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMorphMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) �Ɏ��s���܂����B");
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            if (pEffect_active) {
               _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
             }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");


            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name<<"("<<pMorphMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
            //���[�t�^�[�Q�b�g�̐��ɂ�� pass ��؂�ւ��Ă���
            //�v���}�����b�V���̂�                             = pass0
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���P�� = pass1
            //�v���C�}�����b�V���{���[�t�^�[�Q�b�g���b�V���Q�� = pass2
            //�ȉ��ő�X�܂�
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "BeginPass("<<_morph_target_num<<") �Ɏ��s���܂����B");

#ifdef MY_DEBUG
            if (pMorphMeshEffect->_begin) {
                throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMorphMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
        }

        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      _paIndexParam[i].BaseVertexIndex,
                                      _paIndexParam[i].MinIndex,
                                      _paIndexParam[i].NumVertices,
                                      _paIndexParam[i].StartIndex,
                                      _paIndexParam[i].PrimitiveCount);
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMorphMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}

void GgafDxMorphMeshModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    //�yGgafDxMorphMeshModel�č\�z�i���������j�����T�v�z
    //��{�I�ɂ�restoreMeshModel�̏�����������i�z��j�𑝂₵���悤�Ȃ���
    //�P�j�v���C�}���{���[�t�^�[�Q�b�g��N �́A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ ���쐬
    //�Q�j���ꂼ���X�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �ɗ������ށB
    //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ GgafDxMeshModel �Ɏ��̃����o���쐬�B
    //�@�@�@�@�E�v���C�}�����b�V�����_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E���[�t�^�[�Q�b�g��N �̒��_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E���_�C���f�b�N�X�o�b�t�@�̎ʂ��i�v���C�}�����b�V���̂݁j
    //�@�@�@�@�E�}�e���A���z��(�v�f�����}�e���A�����B�v���C�}�����b�V���̂�)
    //�@�@�@�@�E�e�N�X�`���z��(�v�f�����}�e���A�����B�v���C�}�����b�V���̂�)
    //�@�@�@�@�EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω��������B�v���C�}�����b�V���̂�)
    int morph_target_num = _morph_target_num;

    std::string* paXfileName = NEW std::string[morph_target_num+1];

    for (int i = 0; i < morph_target_num+1; i++) {
        char* xfilename_base = _model_name + 2; //�Q�����ڈȍ~  "2/ceres" �� "ceres"
        paXfileName[i] = GgafDxModelManager::getMeshFileName(std::string(xfilename_base) + "_" + (char)('0'+i));
        if (paXfileName[i] == "") {
             throwGgafCriticalException("���b�V���t�@�C��(*.x)��������܂���Bmodel_name="<<(std::string(xfilename_base) + "_" + (char)('0'+i)));
        }
    }
    HRESULT hr;
    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X* paIOX = nullptr;
    Frm::Model3D**                        papModel3D = nullptr;
    Frm::Mesh**                           papMeshesFront = nullptr;

    GgafDxMorphMeshModel::INDEXPARAM*     paIndexParam = nullptr;
    GgafDxMorphMeshModel::VERTEX_PRIMARY* paVtxBuffer_data_primary = nullptr;
    GgafDxMorphMeshModel::VERTEX_MORPH**  papaVtxBuffer_data_morph = nullptr;
    WORD*                                 paIdxBuffer_data = nullptr;
    D3DMATERIAL9*                         paMaterial = nullptr;

    GgafDxTextureConnection** model_papTextureConnection = nullptr;

    if (_papModel3D == nullptr) {
        paIOX = NEW ToolBox::IO_Model_X[morph_target_num+1];
        papModel3D = NEW Frm::Model3D*[morph_target_num+1];
        papMeshesFront = NEW Frm::Mesh*[morph_target_num+1];
        papaVtxBuffer_data_morph = NEW GgafDxMorphMeshModel::VERTEX_MORPH*[morph_target_num];
        int nVertices = 0;
        int nTextureCoords = 0;
        int nFaces = 0;
//        int nFaceNormals = 0;
        FLOAT model_bounding_sphere_radius;
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {
            papModel3D[pattern] = NEW Frm::Model3D();
            bool r = paIOX[pattern].Load(paXfileName[pattern], papModel3D[pattern]);
            if (r == false) {
                throwGgafCriticalException("X�t�@�C���̓Ǎ��ݎ��s�B2/ �Ƃ��Y��Ă܂��񂩁H �Ώ�="<<paXfileName[pattern]);
            }
            //���b�V������������O�ɁA�����m�ۂ��Ă���
            int nMesh = (int)papModel3D[pattern]->_Meshes.size();
            uint16_t* paNumVertices = NEW uint16_t[nMesh];
            int index_Mesh = 0;
            for (std::list<Frm::Mesh*>::iterator iteMeshes = papModel3D[pattern]->_Meshes.begin();
                    iteMeshes != papModel3D[pattern]->_Meshes.end(); iteMeshes++) {
                paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
                index_Mesh++;
            }
            papModel3D[pattern]->ConcatenateMeshes(); //���b�V�����q����
            papMeshesFront[pattern] = papModel3D[pattern]->_Meshes.front();
            nVertices = papMeshesFront[pattern]->_nVertices;
            nTextureCoords = papMeshesFront[pattern]->_nTextureCoords;
            nFaces = papMeshesFront[pattern]->_nFaces;
//            nFaceNormals = papMeshesFront[pattern]->_nFaceNormals;

            if (nVertices*(morph_target_num+1) > 65535) {
                throwGgafCriticalException("���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  nVertices:"<<nVertices<<"  �Z�b�g��:"<<(morph_target_num+1));
            }

            if (pattern == 0) {
                //�v���C�}�����b�V��
                paVtxBuffer_data_primary = NEW GgafDxMorphMeshModel::VERTEX_PRIMARY[nVertices];
                _size_vertices_primary = sizeof(GgafDxMorphMeshModel::VERTEX_PRIMARY) * nVertices;
                _size_vertex_unit_primary = sizeof(GgafDxMorphMeshModel::VERTEX_PRIMARY);
                //�@���ȊO�ݒ�
                for (int i = 0; i < nVertices; i++) {
                    paVtxBuffer_data_primary[i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    paVtxBuffer_data_primary[i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    paVtxBuffer_data_primary[i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    paVtxBuffer_data_primary[i].nx = 0.0f;
                    paVtxBuffer_data_primary[i].ny = 0.0f;
                    paVtxBuffer_data_primary[i].nz = 0.0f;
                    paVtxBuffer_data_primary[i].color = D3DCOLOR_ARGB(255,255,255,255);
                    if (i < nTextureCoords) {
                        paVtxBuffer_data_primary[i].tu = papMeshesFront[pattern]->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                        paVtxBuffer_data_primary[i].tv = papMeshesFront[pattern]->_TextureCoords[i].data[1];
                    } else {
                        paVtxBuffer_data_primary[i].tu = 0.0f;
                        paVtxBuffer_data_primary[i].tv = 0.0f;
                    }

                    //����
                    model_bounding_sphere_radius = (FLOAT)(sqrt(paVtxBuffer_data_primary[i].x * paVtxBuffer_data_primary[i].x +
                                                                paVtxBuffer_data_primary[i].y * paVtxBuffer_data_primary[i].y +
                                                                paVtxBuffer_data_primary[i].z * paVtxBuffer_data_primary[i].z));
                    if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                        _bounding_sphere_radius = model_bounding_sphere_radius;
                    }
                }
            } else {
                //���[�t�^�[�Q�b�g���b�V��
                papaVtxBuffer_data_morph[pattern-1] = NEW GgafDxMorphMeshModel::VERTEX_MORPH[nVertices];
                _size_vertices_morph = sizeof(GgafDxMorphMeshModel::VERTEX_MORPH) * nVertices;
                _size_vertex_unit_morph = sizeof(GgafDxMorphMeshModel::VERTEX_MORPH);
                //�@���ȊO�ݒ�
                for (int i = 0; i < nVertices; i++) {
                    papaVtxBuffer_data_morph[pattern-1][i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    papaVtxBuffer_data_morph[pattern-1][i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    papaVtxBuffer_data_morph[pattern-1][i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    papaVtxBuffer_data_morph[pattern-1][i].nx = 0.0f;
                    papaVtxBuffer_data_morph[pattern-1][i].ny = 0.0f;
                    papaVtxBuffer_data_morph[pattern-1][i].nz = 0.0f;
                }
            }

            if (nVertices < nTextureCoords) {
                _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
                _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<paXfileName[pattern]);
            }

            //�@���ݒ��FrameTransformMatrix�K�p
            if (pattern == 0) { //�v���C�}�����b�V��
                prepareVtx((void*)paVtxBuffer_data_primary, _size_vertex_unit_primary,
                           papModel3D[pattern], paNumVertices);
            } else {            //�^�[�Q�b�g���b�V��
                prepareVtx((void*)(papaVtxBuffer_data_morph[pattern-1]), _size_vertex_unit_morph,
                           papModel3D[pattern], paNumVertices);
            }
            GGAF_DELETE(paNumVertices);

        }

        //�C���f�b�N�X�o�b�t�@�擾
        paIdxBuffer_data = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            paIdxBuffer_data[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
            paIdxBuffer_data[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
            paIdxBuffer_data[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDxMorphMeshModel::INDEXPARAM* paParam = NEW GgafDxMorphMeshModel::INDEXPARAM[nFaces];

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < nFaces; faceNoCnt++) {
            materialno = papMeshesFront[0]->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //_TRACE3_("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam[paramno].MaterialNo = materialno;
                paParam[paramno].BaseVertexIndex = 0;
                paParam[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�ςȒl�ɂ��Ƃ�
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

            if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 0]) {
                max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 0];
            }
            if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 1]) {
                max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 1];
            }
            if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 2]) {
                max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 2];
            }
            if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 0]) {
                min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 0];
            }
            if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 1]) {
                min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 1];
            }
            if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 2]) {
                min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 2];
            }
            prev_materialno = materialno;
        }
        if (nFaces > 0) {
            paParam[paramno-1].MinIndex = min_num_vertices;
            paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        paIndexParam = NEW GgafDxMorphMeshModel::INDEXPARAM[paramno];
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
    }

    if (_pVertexDeclaration == nullptr) {

        int elemnum = (4+(2*morph_target_num))+1; //D3DVERTEXELEMENT9 �\���̂̔z��v�f��
        D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[elemnum];
                                                         // 4 = �v���C�}�����b�V��
                                                         // (2*morph_target_num) = ���[�t�^�[�Q�b�g���b�V��
                                                         // 1 = D3DDECL_END()
        //�v���C�}�����b�V�������_�t�H�[�}�b�g
        //FVF�͎g���Ȃ��̂ŁACreateVertexDeclaration��
        //TODO:���_�t�H�[�}�b�g�𖈉�\�z�ł͂Ȃ��āA���f�����ɕێ����������B
        //�v���C�}�������_�t�H�[�}�b�g
        //float x, y, z; // ���_���W
        paVtxelem[0].Stream = 0;
        paVtxelem[0].Offset = 0;
        paVtxelem[0].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[0].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[0].Usage = D3DDECLUSAGE_POSITION;
        paVtxelem[0].UsageIndex = 0;
        //float nx, ny, nz; // �@��
        paVtxelem[1].Stream = 0;
        paVtxelem[1].Offset = sizeof(float)*3;
        paVtxelem[1].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[1].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[1].Usage = D3DDECLUSAGE_NORMAL;
        paVtxelem[1].UsageIndex = 0;
        //DWORD color; // ���_�J���[
        paVtxelem[2].Stream = 0;
        paVtxelem[2].Offset = sizeof(float)*6;
        paVtxelem[2].Type = D3DDECLTYPE_D3DCOLOR;
        paVtxelem[2].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[2].Usage = D3DDECLUSAGE_COLOR;
        paVtxelem[2].UsageIndex = 0;
        //float tu, tv; // �e�N�X�`�����W
        paVtxelem[3].Stream = 0;
        paVtxelem[3].Offset = sizeof(float)*6+sizeof(DWORD);
        paVtxelem[3].Type = D3DDECLTYPE_FLOAT2;
        paVtxelem[3].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[3].Usage = D3DDECLUSAGE_TEXCOORD;
        paVtxelem[3].UsageIndex = 0;
        //���[�t�^�[�Q�b�g���b�V�������_�t�H�[�}�b�g
        for (int i = 4, s = 1; i < elemnum-1; i+=2, s++) {
            //float x, y, z; // ���_���W
            paVtxelem[i].Stream = s;
            paVtxelem[i].Offset = 0;
            paVtxelem[i].Type = D3DDECLTYPE_FLOAT3;
            paVtxelem[i].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[i].Usage = D3DDECLUSAGE_POSITION;
            paVtxelem[i].UsageIndex = s;
            //float nx, ny, nz; // �@��
            paVtxelem[i+1].Stream = s;
            paVtxelem[i+1].Offset = sizeof(float)*3;
            paVtxelem[i+1].Type = D3DDECLTYPE_FLOAT3;
            paVtxelem[i+1].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[i+1].Usage = D3DDECLUSAGE_NORMAL;
            paVtxelem[i+1].UsageIndex = s;
        }
        //D3DDECL_END()
        paVtxelem[elemnum-1].Stream = 0xFF;
        paVtxelem[elemnum-1].Offset = 0;
        paVtxelem[elemnum-1].Type = D3DDECLTYPE_UNUSED;
        paVtxelem[elemnum-1].Method = 0;
        paVtxelem[elemnum-1].Usage = 0;
        paVtxelem[elemnum-1].UsageIndex = 0;

        hr = GgafDxGod::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pVertexDeclaration) );
        checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->CreateVertexDeclaration ���s model="<<(_model_name));
        //�X�g���[�����擾        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);

        GGAF_DELETEARR(paVtxelem);
    }

    //���_�o�b�t�@�쐬
    if (_pVertexBuffer_primary == nullptr) {
        _paIDirect3DVertexBuffer9_morph = NEW LPDIRECT3DVERTEXBUFFER9[morph_target_num];
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {

            if (pattern == 0) {
                //�v���C�}�����_�o�b�t�@
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_primary,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDxMorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(_pVertexBuffer_primary),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s�i�v���C�}���j model="<<(_model_name));
                void *pVertexBuffer;
                hr = _pVertexBuffer_primary->Lock(0, _size_vertices_primary, (void**)&pVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i�v���C�}���j model="<<_model_name);
                memcpy(pVertexBuffer, paVtxBuffer_data_primary, _size_vertices_primary); //pVertexBuffer �� paVertex
                _pVertexBuffer_primary->Unlock();
            } else {
                //���[�t�^�[�Q�b�g���_�o�b�t�@
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_morph,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDxMorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(_paIDirect3DVertexBuffer9_morph[pattern-1]),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s�i���[�t:"<<pattern-1<<"�j model="<<(_model_name));
                void *pVertexBuffer;
                hr = _paIDirect3DVertexBuffer9_morph[pattern-1]->Lock(0, _size_vertices_morph, (void**)&pVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i���[�t:"<<pattern-1<<"�j model="<<_model_name);
                memcpy(pVertexBuffer, papaVtxBuffer_data_morph[pattern-1], _size_vertices_morph); //pVertexBuffer �� paVertex
                _paIDirect3DVertexBuffer9_morph[pattern-1]->Unlock();
            }
        }
    }


    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬�i�v���C�}���A���[�t�^�[�Q�b�g���ɓ����j
    if (_pIndexBuffer == nullptr) {
        int nFaces = papMeshesFront[0]->_nFaces;

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_name));
        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , paIdxBuffer_data , sizeof(WORD) * nFaces * 3);
        _pIndexBuffer->Unlock();
    }



    //�}�e���A���ݒ�
    //�}�e���A���̓v���C�}�����b�V���̃}�e���A�������A
    //�v���C�}���y�ёS���[�t�^�[�Q�b�g�̃}�e���A���Ƃ���B
    //�����papMeshesFront[0]�����g���A�c��͎g��Ȃ��B
    //TODO:�����I�ɂ̓��[�t�^�[�Q�b�g�ʂɃ}�e���A���ݒ�ł���Ε\���������B�������悤���A���������Ԑ�B
    setMaterial(papMeshesFront[0]);


    if (!_papTextureConnection) {
        _papTextureConnection = NEW GgafDxTextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    GGAF_DELETEARR(paIOX);
    GGAF_DELETEARR(paXfileName);

    //���f���ɕێ�������
    _papModel3D              = papModel3D;
    _papMeshesFront          = papMeshesFront;
    _paIndexBuffer_data         = paIdxBuffer_data;
    _paVtxBuffer_data_primary = paVtxBuffer_data_primary;
    _papaVtxBuffer_data_morph = papaVtxBuffer_data_morph;
    _paIndexParam            = paIndexParam;

    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMorphMeshModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMorphMeshModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");

    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (DWORD i = 0; i < _num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //�e�N�X�`���̔z��

    for (int pattern = 0; pattern <= _morph_target_num; pattern++) {
        if (pattern == 0) {
            GGAF_RELEASE(_pVertexBuffer_primary);
            GGAF_DELETEARR(_paVtxBuffer_data_primary);
        } else {
            GGAF_RELEASE(_paIDirect3DVertexBuffer9_morph[pattern-1]);
            GGAF_DELETEARR(_papaVtxBuffer_data_morph[pattern-1]);
        }
        if (_papModel3D) {
            Frm::Model3D* p = _papModel3D[pattern];
            GGAF_DELETE(p);
        }
    }

    GGAF_DELETEARR(_paIDirect3DVertexBuffer9_morph);
    GGAF_DELETEARR(_papaVtxBuffer_data_morph);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pVertexDeclaration);

    GGAF_DELETEARR(_papModel3D);
    //_papMeshesFront[0],_papMeshesFront[1] �� _papModel3D ��DELETE���Ă���̂ł���K�v�͖���
    GGAF_DELETEARR(_papMeshesFront);
    _papMeshesFront = nullptr;
    GGAF_DELETEARR(_paIndexBuffer_data);
    GGAF_DELETEARR(_paIndexParam);

    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");

}
GgafDxMorphMeshModel::~GgafDxMorphMeshModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}

