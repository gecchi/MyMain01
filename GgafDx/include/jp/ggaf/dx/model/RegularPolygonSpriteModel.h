#ifndef GGAF_DX_REGULARPOLYGONSPRITEMODEL_H_
#define GGAF_DX_REGULARPOLYGONSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * RegularPolygonSpriteActor�p���f���N���X.
 * @version 1.00
 * @since 2018/10/18
 * @author Masatoshi Tsuge
 */
class RegularPolygonSpriteModel : public Model {
    friend class ModelManager;

public:
    /** ���_�\���� */
    struct VERTEX : public VERTEX_3D_BASE {
        DWORD color;      // ���_�F�i���ݖ��g�p�j
        float tu, tv;     // ���_�̃e�N�X�`�����W
    };

    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** ���_��FVF */
    static DWORD FVF;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;

    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;
    /** FAN�`�揇���� 1:���v���/1�ȊO:�����v��� */
    int _drawing_order;
    /** �����p�`�� */
    int _angle_num;
    /** �ŏ��̒��_�� u ���W */
    float _u_center;
    /** �ŏ��̒��_�� v ���W */
    float _v_center;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    RegularPolygonSpriteModel(const char* prm_model_name);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * FAN�`�揇�������擾�B
     * @return 1:���v���/1�ȊO:�����v���
     */
    int getDrawingOrder() {
        return _drawing_order;
    }

    /**
     * �����p�`�̕`�悩��Ԃ�
     * @return �����p�`�̕`�悩(=FAN�̐�)
     */
    int getAngleNum() {
        return _angle_num;
    }

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~RegularPolygonSpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_REGULARPOLYGONSPRITEMODEL_H_*/