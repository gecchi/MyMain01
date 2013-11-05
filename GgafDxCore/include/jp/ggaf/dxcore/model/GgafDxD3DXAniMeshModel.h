#ifndef GGAFDXCORE_GGAFDXD3DXANIMESHMODEL_H_
#define GGAFDXCORE_GGAFDXD3DXANIMESHMODEL_H_
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

#include "jp/ggaf/dxcore/util/GgafDxWorldMatStack.h"

namespace GgafDxCore {

/**
 * GgafDxD3DXActor�p���f���N���X.(���g�p�A���O�̃A�j���[�V�����t���[���ŉ����BaddSubGroupAsFk()�Ŏ������)
 * GgafDxD3DXAniMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXAniMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    /** ���b�V��(�C���X�^���X�̓��f�����j */
    GgafDxAllocHierarchyWorldFrame* _pAH;
    D3DXFRAME_WORLD* _pFR;
    ID3DXAnimationController* _pAcBase;
    int _anim_ticks_per_second;
    /** 60�t���[��(1�b)��1���[�v����ꍇ��1�t���[���ӂ�̎��� */
//    double _advance_time_per_frame0;//60�t���[��(1�b)��1���[�v���邱�Ƃ�W���ݒ�Ƃ���B

    GgafDxWorldMatStack _stackWorldMat;
    ///** D3DXLoadMeshFromX�̃I�v�V���� */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model ���f���̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxD3DXAniMeshModel(char* prm_model);

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

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
     * delete����̂�GgafDxD3DXAniMeshModelManager�ł���<BR>
     */
    virtual ~GgafDxD3DXAniMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXD3DXANIMESHMODEL_H_*/
