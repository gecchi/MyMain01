#ifndef GGAF_DX_SKINANIMESHMODEL_H_
#define GGAF_DX_SKINANIMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include <map>
#include <vector>

namespace GgafDx {

/**
 * D3DXActor�p���f���N���X.(���g�p�A���O�̃A�j���[�V�����t���[���ŉ����BappendGroupChildAsFk()�Ŏ������)
 * SkinAniMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class SkinAniMeshModel : public Model {
    friend class ModelManager;

public:
    /** ���_��FVF */
    struct VERTEX : public Model::VERTEX_3D_BASE {
        float bone_combi_index;      // psize�ł͂Ȃ��Ă͂Ȃ��ă{�[���R���r�l�[�V�����̃C���f�b�N�X�BpaBoneCombination[n] �� n
        DWORD color;      // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�j
        float tu, tv;     // �e�N�X�`�����W

        float infl_weight[4];     // ���_�d��(TODO:�S�ł����́H)
        byte  infl_bone_idx[4];
    };
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

//    struct BONE_CONBI_GRP {
//        DWORD bone_combi_index;
//
//
//        int infl_bone_idx_num;
//
//        float infl_weight[4];
//        byte  infl_bone_idx[4];
//    };
//    std::vector<BONE_CONBI_INFO> _vec_bone_combi_info;


    SkinAniMeshModel::VERTEX* _paVtxBuffer_data;
    WORD* _paIndexBuffer_data;
    /** �C���f�b�N�X�o�b�t�@�ԍ��ɑΉ����钸�_�o�b�t�@�̃t���[�����b�V���ԍ� */
    int* _paIndexBuffer_bone_combi_index;
    /** �V�F�[�_�[���͒��_�t�H�[�}�b�g */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;
    /** ���_�o�b�t�@�i�S�t���[���̃��b�V�����j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** �C���f�b�N�X�o�b�t�@�i�S�t���[���̃��b�V�����j  */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
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

//    struct BoneCombinationGrp {
//        std::vector<DWORD> vecInflBoneId;
//
//
//    };
//    std::vector<BoneCombinationGrp> _vecBoneCombinationGrp;


    std::vector<DWORD> _infl_bone_idx_order;
    std::map<DWORD, DWORD> _map_infl_bone_idx_to_order;

    /** ���A�j���[�V�����Z�b�g�� */
    UINT _num_animation_set;
    /** AnimationSet ����AAnimationSet�C���f�b�N�X���擾�ł���}�b�v */
    std::map<ID3DXAnimationSet*, UINT> _mapAnimationSet_AniSetindex;
    /** �A�j���[�V�����Z�b�g�C���f�b�N�X����AAnimation�̃^�[�Q�b�g��BoneFrame �� Name�̔z�񂪎擾�ł���}�b�v */
    std::map<UINT, std::vector<LPCSTR>> _mapAnimationSetIndex_AnimationTargetBoneFrameNames;
    /** [�A�j���[�V�����Z�b�g�C���f�b�N�X][�t���[���C���f�b�N�X] �� �A�j���[�V�����Z�b�g�̃A�j���[�V�����Ώۂ̃t���[���ł��邩�ǂ������Ԃ� */
    bool** _papaBool_AnimationSetIndex_BoneFrameIndex_is_act;

    int _anim_ticks_per_second;
    /** 60�t���[��(1�b)��1���[�v����ꍇ��1�t���[���ӂ�̎��� */
//    double _advance_time_per_frame0;//60�t���[��(1�b)��1���[�v���邱�Ƃ�W���ݒ�Ƃ���B

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model ���f���̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     * @return
     */
    SkinAniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    static int getAnimTicksPerSecond(std::string& prm_xfile_name);

    /** �t���[���������ď��擾 */
    void setFrameInfo(SkinAniMeshFrame* prm_pFrame);
    /** setFrameInfo(SkinAniMeshFrame*) �Ŏg�p�����Aframe_index�̒ʂ��ԍ� */
    DWORD _tmp_frame_index;

    int getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage );

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�SkinAniMeshModelManager�ł���<BR>
     */
    virtual ~SkinAniMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_SKINANIMESHMODEL_H_*/
