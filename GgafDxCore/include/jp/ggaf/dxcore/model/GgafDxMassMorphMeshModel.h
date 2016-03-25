#ifndef GGAFDXCORE_GGAFDXMASSMORPHMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {

/**
 * GgafDxMassMorphMeshModel�p�̃��f���N���X.
 * GgafDxMassMorphMeshModel �� GgafDxMeshModel �̕`�悷��@�\�ɉ����A���[�t�A�j���[�V�����@�\��L���郂�f���ł��B<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMassMorphMeshModel : public GgafDxMassModel {
    friend class GgafDxModelManager;

public:
    struct VERTEX_model_primary : public GgafDxModel::VERTEX_3D_BASE {
        D3DCOLOR color;   // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�\��j
        float tu, tv;     // �e�N�X�`�����W
    };
    VERTEX_model_primary* _paVtxBuffer_data_model;
    WORD* _paIndexBuffer_data;

    /** ���[�t�^�[�Q�b�g�̒��_�t�H�[�}�b�g��` */
    struct VERTEX_model_morph : public GgafDxModel::VERTEX_3D_BASE {
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
    LPDIRECT3DVERTEXBUFFER9* _pVertexBuffer_model_morph;


public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name ���f����`�̎��ʖ�
     */
    GgafDxMassMorphMeshModel(const char* prm_model_name);

    static void createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;


    virtual void resetStreamSourceFreq() override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMassMorphMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMASSMORPHMESHMODEL_H_*/
