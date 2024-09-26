#ifndef GGAF_DX_BONEANIMESHMODEL_H_
#define GGAF_DX_BONEANIMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include <map>
#include <vector>

namespace GgafDx {

/**
 * D3DXActor�p���f���N���X.(���g�p�A���O�̃A�j���[�V�����t���[���ŉ����BappendChildAsFk()�Ŏ������)
 * BoneAniMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class BoneAniMeshModel : public Model {
    friend class ModelManager;

public:
    /** ���_��FVF */
    static DWORD FVF;
    struct VERTEX : public Model::VERTEX_POS_NOMAL {
        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��Ƃ��Ďg�p�B���t���[���ڂ����邽�߂Ɏg�p�B
        DWORD color;      // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�j
        float tu, tv;     // �e�N�X�`�����W
    };
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    BoneAniMeshModel::VERTEX* _paVtxBuffer_data;
    D3DFORMAT _indexBuffer_fmt;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;
    /** �C���f�b�N�X�o�b�t�@�ԍ��ɑΉ����钸�_�o�b�t�@�̃t���[�����b�V���ԍ� */
    int* _paIndexBuffer_frame_no;
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
    /** BoneAniMeshFrame��舵��AllocateHierarchy�N���X */
    BoneAniMeshAllocHierarchy* _pAllocHierarchy;
    /** ���[���h�ϊ��s��t���t���[���\���̂̃��[�g */
    BoneAniMeshFrame* _pFrameRoot;
    /** �A�j���[�V�����R���g���[���AActor�������ɂ͂��ꂪ clone �����Actor�ɕێ�����邱�ƂɂȂ� */
    ID3DXAnimationController* _pAniControllerBase;

    /** _pFrameRoot �������ăt���[���𒼗񉻂������́A�v�f�ԍ��̓t���[���C���f�b�N�X�ƌď̂���  */
    std::vector<BoneAniMeshFrame*> _vecAllBoneFrame;
    /** _pFrameRoot �������ă��b�V���R���e�i������`��Ώۃt���[���𒼗񉻂������́A�v�f�ԍ��͂����̘A��  */
    std::vector<BoneAniMeshFrame*> _vecDrawBoneFrame;


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
     * @param prm_model ���f���̎��ʖ��B".modelx"��ǉ�����ƃ��f����`�t�@�C�����ɂȂ�B
     * @return
     */
    BoneAniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    static int getAnimTicksPerSecond(std::string& prm_xfile_name);

    /** �t���[���������ď��擾 */
    void setFrameInfo(BoneAniMeshFrame* prm_pFrame);
    /** setFrameInfo(BoneAniMeshFrame*) �Ŏg�p�����Aframe_index�̒ʂ��ԍ� */
    DWORD _tmp_frame_index;

    int getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage );

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�BoneAniMeshModelManager�ł���<BR>
     */
    virtual ~BoneAniMeshModel();

};

}
#endif /*GGAF_DX_BONEANIMESHMODEL_H_*/
