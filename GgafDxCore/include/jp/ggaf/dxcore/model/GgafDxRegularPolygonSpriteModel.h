#ifndef GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEMODEL_H_
#define GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * GgafDxRegularPolygonSpriteActor�p���f���N���X.
 * @version 1.00
 * @since 2018/10/18
 * @author Masatoshi Tsuge
 */
class GgafDxRegularPolygonSpriteModel : public GgafDxModel {
    friend class GgafDxModelManager;

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


    /** �����p�`�� */
    int _angle_num;
    /** ���p�`�̊J�n�p�x(D_ANG(0)�`D_ANG(360)�A0��XY���ʌ��_���S���a�P�̏ꍇ(1,0)����J�n���邱�Ƃ�\��) */
    angle _start_angle;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxRegularPolygonSpriteModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxRegularPolygonSpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEMODEL_H_*/
