#ifndef GGAFDXCORE_GGAFDXBOARDMODEL_H_
#define GGAFDXCORE_GGAFDXBOARDMODEL_H_
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * GgafDxBoardActor�p���f���N���X.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDxBoardModel : public GgafDxModel {
    friend class GgafDxModelManager;
    friend class GgafDxBoardActor;

public:
    struct VERTEX {
        float x, y, z; // ���_���W
        float tu, tv; // �e�N�X�`�����W
    };

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;

    float _fSize_BoardModelWidthPx;
    float _fSize_BoardModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxBoardModel(char* prm_model_name);

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxBoardModelManager�ł���<BR>
     */
    virtual ~GgafDxBoardModel(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXBOARDMODEL_H_*/
