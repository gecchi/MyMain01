#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace MyStg2nd {

class LaserChip : public GgafDx9Core::GgafDx9MeshSetActor {
    friend class LaserChipDispatcher;
private:
//    D3DXHANDLE _hKind, _hX, _hY, _hZ, _hRevPosZ;
    D3DXHANDLE _ahKind[8];
    D3DXHANDLE _ahRevPosZ[8];
    D3DXHANDLE _ahMatWorld_front[8];

    D3DXHANDLE _h_cnt_vertec;
    void processPreDraw() {
        GgafDx9Core::GgafDx9MeshSetActor::processPreDraw();
    }

    void processAfterDraw();

    /**
     * ��OverRide �ł���
     */
    void processDraw();

    /**
     * �o�����R�[���o�b�N����
     */
    void onActive();

    /**
     * �������R�[���o�b�N����
     */
    void onInactive();

public:
    GgafDx9LibStg::StgChecker* _pStgChecker;
    /** ���W�ړ��x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;


    /** ��O���̃��[�U�[�`�b�v */
    LaserChip* _pChip_front;
    /** �����̃��[�U�[�`�b�v */
	LaserChip* _pChip_behind;
	/** ���[�U�[�e�N�X�`�����  1:���� 2:���� 3:�擪 �i�������擪�͖������D��j */
	int _chiptex_kind;

	/** ���g��World�ϊ��s�� */
    D3DXMATRIX _matWorld;
    /** ��O����World�ϊ��s�� */
    D3DXMATRIX _matWorld_front;
    /** ���g���Ǘ����Ă�A�N�^�[������ */
    LaserChipDispatcher* _pDispatcher;



    LaserChip(const char* prm_name, const char* prm_model);

    /**
     * ���ʃN���X�ŃI�[�o�[���C�h���ĉ������B
     */
    virtual void initialize();

    /**
     * ���ʃN���X�ŃI�[�o�[���C�h���ĉ������B
     */
    virtual void processBehavior();

    /**
     * ���ʃN���X�ŃI�[�o�[���C�h���ĉ������B
     */
    virtual void processJudgement();

    /**
     * ���ʃN���X�ŃI�[�o�[���C�h���ĉ������B
     */

    virtual void processHappen(int prm_no) {
    }

    /**
     * ���ʃN���X�ŃI�[�o�[���C�h���ĉ������B
     */
    virtual void processFinal() {
    }

    /**
     * ���ʃN���X�ŃI�[�o�[���C�h���ĉ������B
     */
    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

