#ifndef GGAF_DX_D3DXANIMESHMODEL_H_
#define GGAF_DX_D3DXANIMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

#include "jp/ggaf/dx/util/WorldMatStack.h"

namespace GgafDx {

/**
 * D3DXActor�p���f���N���X.(���g�p�A���O�̃A�j���[�V�����t���[���ŉ����BappendGroupChildAsFk()�Ŏ������)
 * D3DXAniMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class D3DXAniMeshModel : public Model {
    friend class ModelManager;

public:
    /** ���b�V��(�C���X�^���X�̓��f�����j */
    AllocHierarchyWorldFrame* _pAllocHierarchy;
    FrameWorldMatrix* _pFrameRoot;
    ID3DXAnimationController* _pAniControllerBase;
    int _anim_ticks_per_second;
    /** 60�t���[��(1�b)��1���[�v����ꍇ��1�t���[���ӂ�̎��� */
//    double _advance_time_per_frame0;//60�t���[��(1�b)��1���[�v���邱�Ƃ�W���ݒ�Ƃ���B

//    WorldMatStack _stackWorldMat;
    ///** D3DXLoadMeshFromX�̃I�v�V���� */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model ���f���̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     * @return
     */
    D3DXAniMeshModel(const char* prm_model);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    ID3DXAnimationController* getCloneAnimationController();

    void getDrawFrameList(std::list<FrameWorldMatrix*>* pList, FrameWorldMatrix* frame);

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
     * delete����̂�D3DXAniMeshModelManager�ł���<BR>
     */
    virtual ~D3DXAniMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_D3DXANIMESHMODEL_H_*/
