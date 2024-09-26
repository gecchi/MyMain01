#ifndef GGAF_DX_SKINANIMESHMODEL_H_
#define GGAF_DX_SKINANIMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"
#include <map>
#include <vector>

namespace GgafDx {

/**
 * D3DXActor�p���f���N���X.(���g�p�A���O�̃A�j���[�V�����t���[���ŉ����BappendChildAsFk()�Ŏ������)
 * SkinAniMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class SkinAniMeshModel : public Model {
    friend class ModelManager;

public:
    /** ���_��FVF */
    struct VERTEX : public Model::VERTEX_POS_NOMAL {
        DWORD color;      // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�j
        float tu, tv;     // �e�N�X�`�����W
        float infl_weight[4];     // ���_�d��(TODO:�S�ł����́H)
        byte  infl_bone_id_order[4]; //�{�[��ID�̒ʂ��ԍ�
    };
    /**
     * ���_�o�b�t�@�̕⑫��� .
     */
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    /**
     * �ꊇ�`��P�ʂ̃{�[���R���r�l�[�V�����O���[�v .
     */
    class BoneConbiGrp {
    public:
        /** �O���[�v�̍ŏ��̃{�[���R���r�l�[�V�����C���f�b�N�X */
        int bone_combi_start_index;
        /** �O���[�v�� bone_combi_start_index ��̃{�[���R���r�l�[�V�����C���f�b�N�X�� */
        int bone_combi_count;
        /** �O���[�v�̒��_�o�b�t�@�J�n�C���f�b�N�X */
        DWORD grp_vertex_start;
        /** �O���[�v�� grp_vertex_start ����̒��_�o�b�t�@�� */
        DWORD grp_vertex_count;

        std::vector<DWORD> vec_infl_bone_id_order; //���j�[�N��vec_cb_idx_order���}������Ă���
        std::vector<DWORD> vec_cb_idx_order;       //vec_infl_bone_id_order ���}�����ꂽ����

        //bone_id ����Abone_id_order �𓾂�MAP
        std::map<DWORD, DWORD> map_infl_bone_id_to_order;
        /** �`�掞�̍ŏI�I�ȕϊ��s��i�ʂ����j */
        BoneConbiGrp() {
            bone_combi_start_index = 0;
            bone_combi_count = 0;
            grp_vertex_start = 0;
            grp_vertex_count = 0;
        }
    };
    std::vector<BoneConbiGrp> _vec_bone_combi_grp_info;

    SkinAniMeshModel::VERTEX* _paVtxBuffer_data;
    D3DFORMAT _indexBuffer_fmt;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;

    /** �V�F�[�_�[���͒��_�t�H�[�}�b�g */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;
    /** ���_�o�b�t�@�i�S�t���[���̃��b�V�����j */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** �C���f�b�N�X�o�b�t�@�i�S�t���[���̃��b�V�����j  */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;
    /** ���f�����_�� */
    UINT _nVertices;
    /** ���f���ʂ̐� */
    UINT _nFaces;
    /** �P���_�̃T�C�Y */
    UINT _size_vertex_unit;
    /** ���f�����_�T�C�Y�v */
    UINT _size_vertices;
    int _index_param_num;
    INDEXPARAM* _paIndexParam;
    /** SkinAniMeshFrame��舵��AllocateHierarchy�N���X */
    SkinAniMeshAllocHierarchy* _pAllocHierarchy;
    /** ���[���h�ϊ��s��t���t���[���\���̂̃��[�g */
    SkinAniMeshFrame* _pFrameRoot;
    /** �A�j���[�V�����R���g���[���AActor�������ɂ͂��ꂪ clone �����Actor�ɕێ�����邱�ƂɂȂ� */
    ID3DXAnimationController* _pAniControllerBase;

    /** _pFrameRoot �������ăt���[���𒼗񉻂������́A�v�f�ԍ��̓t���[���C���f�b�N�X�ƌď̂���  */
    std::vector<SkinAniMeshFrame*> _vecAllBoneFrame;
    /** _pFrameRoot �������ĕ`��Ώۂ�����t���[���𒼗񉻂������́A�v�f�ԍ��͂����̘A��  */
    std::vector<SkinAniMeshFrame*> _vecDrawBoneFrame;


    std::vector<SkinAniMeshFrame*> _vecBoneIdFrame;

    /** ���̕`��ŃZ�b�g�ł���ϊ��s�� */
    int _draw_combined_matrix_set_num;

    /** ���A�j���[�V�����Z�b�g�� */
    UINT _num_animation_set;
    /** AnimationSet ����AAnimationSet�C���f�b�N�X���擾�ł���}�b�v */
    std::map<ID3DXAnimationSet*, UINT> _mapAnimationSet_AniSetindex;
    /** [�A�j���[�V�����Z�b�g�C���f�b�N�X][�t���[���C���f�b�N�X] �� �A�j���[�V�����Z�b�g�̃A�j���[�V�����Ώۂ̃t���[���ł��邩�ǂ������Ԃ� */
    bool** _papaBool_AnimationSetIndex_BoneFrameIndex_is_act;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model ���f���̎��ʖ��B".modelx"��ǉ�����ƃ��f����`�t�@�C�����ɂȂ�B
     * @return
     */
    SkinAniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    /** �t���[���������ď��擾 */
    void setFrameInfo(SkinAniMeshFrame* prm_pFrame);

    void setAnimationFrameIndex();

    /** setFrameInfo(SkinAniMeshFrame*) �Ŏg�p�����Aframe_index�̒ʂ��ԍ� */
    DWORD _tmp_frame_index;

    int getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage );

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�SkinAniMeshModelManager�ł���<BR>
     */
    virtual ~SkinAniMeshModel();

};

}
#endif /*GGAF_DX_SKINANIMESHMODEL_H_*/
