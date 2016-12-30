#ifndef GGAFDXCORE_GGAFDXMASSPOINTSPRITEMODEL_H_
#define GGAFDXCORE_GGAFDXMASSPOINTSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {


/**
 * TODO:���ݎg���܂���B�r�f�I�J�[�h�ˑ��������ׁB
 * @version 1.00
 * @since 2016/05/16
 * @author Masatoshi Tsuge
 */
class GgafDxMassPointSpriteModel : public GgafDxMassModel {
    friend class GgafDxModelManager;

public:
//    struct VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
//        D3DCOLOR color;   // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�\��j
//        float tu, tv;     // �e�N�X�`�����W
//    };

    struct VERTEX_model {
        float x, y, z;    // ���_���W
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
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxMassPointSpriteModel(const char* prm_model_name);

    static void createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMassPointSpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMASSPOINTSPRITEMODEL_H_*/
