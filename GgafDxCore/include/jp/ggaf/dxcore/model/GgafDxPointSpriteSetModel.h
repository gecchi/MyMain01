#ifndef GGAFDXCORE_GGAFDXPOINTSPRITESETMODEL_H_
#define GGAFDXCORE_GGAFDXPOINTSPRITESETMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteSetModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:

//    struct INDEXPARAM {
//        UINT MaterialNo;
//        INT BaseVertexIndex;
//        UINT MinIndex;
//        UINT NumVertices;
//        UINT StartIndex;
//        UINT PrimitiveCount;
//    };

//    struct VERTEX : public GgafDxModel::VERTEX_3D_BASE {
//        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��Ƃ��Ďg�p�B�V�F�[�_�[���ŉ��Z�b�g�ڂ��𔻒f���邽�߂Ɏg�p�B
//        DWORD color;      // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�j
//        float tu, tv;     // �e�N�X�`�����W
//    };

    struct VERTEX {
        float x, y, z;    // ���_���W
        float psize;      // �|�C���g�T�C�Y
        DWORD color;      // ���_�̐F
        float ini_ptn_no, index;     //
    };

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@�i���L�������j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;

    /** �I�u�W�F�N�g�̂P�ӂ̃T�C�Y(px) */
    float _square_size_px;
    /** �e�N�X�`���̂P�ӂ̒���(px) */
    float _texture_size_px;
    /** �e�N�X�`��������(�P�ŕ��������B�Q�łS�p�^�[���A�R�łX�p�^�[��) */
    int _texture_split_rowcol;
    /** �P���_�̃T�C�Y */
    UINT _size_vertex_unit;
    /** ��{���f���i�P�L�������j���_�T�C�Y�v */
    UINT _size_vertices;
    /** ��{���f���i�P�L�������j���_�� */
    UINT _nVertices;
//    /** ��{���f���i�P�L�������j�̖ʂ̐� */
//    UINT _nFaces;

//    INDEXPARAM** _papaIndexParam;

//    /** �}�e���A�����X�g�̘A���œ���̃}�e���A���ԍ��̉�i�O���[�v�j������邩 */
//    UINT* _paUint_material_list_grp_num;

    VERTEX* _paVtxBuffer_data;
//    WORD* _paIndexBuffer_data;




public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxPointSpriteSetModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxPointSpriteSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITESETMODEL_H_*/
