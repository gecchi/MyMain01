#ifndef GGAF_DX_ANIMESHMODELL_H_
#define GGAF_DX_ANIMESHMODELL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include <map>
#include <vector>

namespace GgafDx {

/**
 * D3DXActor�p���f���N���X.(���g�p�A���O�̃A�j���[�V�����t���[���ŉ����BappendGroupChildAsFk()�Ŏ������)
 * AniMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class AniMeshModel : public Model {
    friend class ModelManager;

public:
    /** ���_��FVF */
    static DWORD FVF;
    struct VERTEX : public Model::VERTEX_3D_BASE {
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

    AniMeshModel::VERTEX* _paVtxBuffer_data;
    WORD* _paIndexBuffer_data;
    /** �C���f�b�N�X�o�b�t�@�ԍ��ɑΉ����钸�_�o�b�t�@�̃t���[�����b�V���ԍ� */
    int* _paIndexBuffer_frame_no;
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
    /** FrameWorldMatrix��舵��AllocateHierarchy�N���X */
    AllocHierarchyWorldFrame* _pAllocHierarchy;
    /** ���[���h�ϊ��s��t���t���[���\���̂̃��[�g */
    FrameWorldMatrix* _pFrameRoot;
    /** �A�j���[�V�����R���g���[���AActor�������ɂ͂��ꂪ clone �����Actor�ɕێ�����邱�ƂɂȂ� */
    ID3DXAnimationController* _pAniControllerBase;

    /** _pFrameRoot �������ăt���[���𒼗񉻂������́A�v�f�ԍ��̓t���[���C���f�b�N�X�ƌď̂���  */
    std::vector<FrameWorldMatrix*> _vecAllBoneFrame;
    /** _pFrameRoot �������ă��b�V���R���e�i������`��Ώۃt���[���𒼗񉻂������́A�v�f�ԍ��͂����̘A��  */
    std::vector<FrameWorldMatrix*> _vecDrawBoneFrame;


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
    AniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    static int getAnimTicksPerSecond(std::string& prm_xfile_name);

    /** �t���[���������ď��擾 */
    void setFrameInfo(FrameWorldMatrix* prm_pFrame);
    /** setFrameInfo(FrameWorldMatrix*) �Ŏg�p�����Aframe_index�̒ʂ��ԍ� */
    UINT _tmp_frame_index;

    int getOffsetFromElem( D3DVERTEXELEMENT9 *elems, D3DDECLUSAGE usage );

    virtual void onDeviceLost() override;

    void release() override;

    void putMat(D3DXMATRIX* pMat) {
        _TRACE_( pMat->_11<<", "<< pMat->_12<<", "<< pMat->_13<<", "<< pMat->_14);
        _TRACE_( pMat->_21<<", "<< pMat->_22<<", "<< pMat->_23<<", "<< pMat->_24);
        _TRACE_( pMat->_31<<", "<< pMat->_32<<", "<< pMat->_33<<", "<< pMat->_34);
        _TRACE_( pMat->_41<<", "<< pMat->_42<<", "<< pMat->_43<<", "<< pMat->_44);
    };

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�AniMeshModelManager�ł���<BR>
     */
    virtual ~AniMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_ANIMESHMODELL_H_*/
