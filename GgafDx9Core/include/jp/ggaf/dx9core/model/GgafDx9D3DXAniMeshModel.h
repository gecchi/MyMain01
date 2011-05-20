#ifndef GGAFDX9D3DXANIMESHMODEL_H_
#define GGAFDX9D3DXANIMESHMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9D3DXActor�p���f���N���X.(���g�p�A���O�̃A�j���[�V�����t���[���ŉ����BaddSubBone()�Ŏ������)
 * GgafDx9D3DXAniMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXAniMeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

public:
    /** ���b�V��(�C���X�^���X�̓��f�����j */
    GgafDx9AllocHierarchyWorldFrame* _pAH;
    D3DXFRAME_WORLD* _pFR;
    ID3DXAnimationController* _pAcBase;
    FLOAT _Ang;
    int _anim_ticks_per_second;
    /** 60�t���[��(1�b)��1���[�v����ꍇ��1�t���[���ӂ�̎��� */
//    double _advance_time_per_frame0;//60�t���[��(1�b)��1���[�v���邱�Ƃ�W���ݒ�Ƃ���B

    GgafDx9WorldBoundMatStack _stackWorldMat;
    ///** D3DXLoadMeshFromX�̃I�v�V���� */
    //	LPD3DXBUFFER	_pAdjacency;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model ���f���̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDx9D3DXAniMeshModel(char* prm_model);

    /**
     * GgafDx9D3DXAniMeshModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9D3DXAniMeshActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

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
     * delete����̂�GgafDx9D3DXAniMeshModelManager�ł���<BR>
     */
    virtual ~GgafDx9D3DXAniMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9D3DXANIMESHMODEL_H_*/
