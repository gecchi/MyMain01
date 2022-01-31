#ifndef GGAF_DX_MASSMORPHMESHMODEL_H_
#define GGAF_DX_MASSMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MassModel.h"

namespace GgafDx {

/**
 * MassMorphMeshModel�p�̃��f���N���X.
 * MassMorphMeshModel �� MeshModel �̕`�悷��@�\�ɉ����A���[�t�A�j���[�V�����@�\��L���郂�f���ł��B<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class MassMorphMeshModel : public MassModel {
    friend class ModelManager;

public:
    struct VERTEX_model_primary : public Model::VERTEX_POS_NOMAL {
        D3DCOLOR color;   // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�\��j
        float tu, tv;     // �e�N�X�`�����W
    };
    VERTEX_model_primary* _paVtxBuffer_data_model;
    WORD* _paIndexBuffer_data;

    /** ���[�t�^�[�Q�b�g�̒��_�t�H�[�}�b�g��` */
    struct VERTEX_model_morph : public Model::VERTEX_POS_NOMAL {
    };
    /** ���[�t�^�[�Q�b�g���_�o�b�t�@�̎ʂ��R�s�[�̒��_�z��̃��[�t�^�[�Q�b�g���z�� */
    VERTEX_model_morph**  _papaVtxBuffer_data_morph_model;
    /** ���_�̃T�C�Y�i���[�t�^�[�Q�b�g�j */
    UINT _size_vertices_morph_model;
    /** 1���_�̃T�C�Y�i���[�t�^�[�Q�b�g�j */
    UINT _size_vertex_unit_morph_model;
    /** ���[�t�^�[�Q�b�g�� */
    int _morph_target_num;
    /** ���[�t�^�[�Q�b�g���_�o�b�t�@�̔z��i�v�f�������[�t�^�[�Q�b�g���j */
    LPDIRECT3DVERTEXBUFFER9* _paVertexBuffer_model_morph;


public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_id ���f����`�̎��ʖ�
     */
    MassMorphMeshModel(const char* prm_model_id);

    static void createVertexModel(void* prm, MassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;


    virtual void resetStreamSourceFreq() override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~MassMorphMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_MASSMORPHMESHMODEL_H_*/
