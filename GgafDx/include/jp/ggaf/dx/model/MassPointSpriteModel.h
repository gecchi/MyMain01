#ifndef GGAF_DX_MASSPOINTSPRITEMODEL_H_
#define GGAF_DX_MASSPOINTSPRITEMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MassModel.h"

namespace GgafDx {


/**
 * TODO:���ݎg���܂���B�r�f�I�J�[�h�ˑ��������ׁB
 * @version 1.00
 * @since 2016/05/16
 * @author Masatoshi Tsuge
 */
class MassPointSpriteModel : public MassModel {
    friend class ModelManager;

public:
//    struct VERTEX_model : public Model::VERTEX_POS_NOMAL {
//        D3DCOLOR color;   // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�\��j
//        float tu, tv;     // �e�N�X�`�����W
//    };

    struct VERTEX_model : public Model::VERTEX_POS {
        float psize;      // �|�C���g�T�C�Y
        DWORD color;      // ���_�̐F
        float tu, tv;     // �e�N�X�`�����W
    };
    VERTEX_model* _paVtxBuffer_data_model;
//    WORD* _paIndexBuffer_data;

    /** �I�u�W�F�N�g�̂P�ӂ̃T�C�Y(px) */
    float _square_size_px;
    /** �e�N�X�`���̂P�ӂ̒���(px) */
    float _texture_size_px;
    /** �e�N�X�`��������(�P�ŕ��������B�Q�łS�p�^�[���A�R�łX�p�^�[��) */
    int _texture_split_rowcol;

    float _inv_texture_split_rowcol;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    MassPointSpriteModel(const char* prm_model_id);

    static void createVertexModel(void* prm, MassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~MassPointSpriteModel();
};

}
#endif /*GGAF_DX_MASSPOINTSPRITEMODEL_H_*/
