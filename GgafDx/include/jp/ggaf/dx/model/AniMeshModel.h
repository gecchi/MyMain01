#ifndef GGAF_DX_ANIMESHMODELL_H_
#define GGAF_DX_ANIMESHMODELL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

#include "jp/ggaf/dx/util/WorldMatStack.h"

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
    AllocHierarchyWorldFrame* _pAH;
    /** ���[���h�ϊ��s��t���t���[���\���� */
    FrameWorldMatrix* _pFR;
    ID3DXAnimationController* _pAcBase;
    int _anim_ticks_per_second;
    /** 60�t���[��(1�b)��1���[�v����ꍇ��1�t���[���ӂ�̎��� */
//    double _advance_time_per_frame0;//60�t���[��(1�b)��1���[�v���邱�Ƃ�W���ݒ�Ƃ���B

    WorldMatStack _stackWorldMat;
    ///** D3DXLoadMeshFromX�̃I�v�V���� */
    //	LPD3DXBUFFER	_pAdjacency;

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

    int getAnimTicksPerSecond(std::string& prm_xfile_name);
    void getDrawFrameVec(std::vector<FrameWorldMatrix*>* pList, FrameWorldMatrix* frame);
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
