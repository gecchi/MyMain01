#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace MyStg2nd {

class LaserChip : public GgafDx9Core::GgafDx9MeshActor {

private:
    D3DXHANDLE _hKind, _hX, _hY, _hZ, _hMatWorld_front;

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    void processDrawPrior() {
        GgafDx9Core::GgafDx9MeshActor::processDrawPrior();
    }

    void processDrawTerminate();

    /**
     * ��OverRide �ł���
     */
    void processDrawMain();

    /**
     * �o�����R�[���o�b�N����
     */
    void onActive();

    /**
     * �������R�[���o�b�N����
     */
    void onInactive();

public:
    /** ��O���̃��[�U�[�`�b�v */
    LaserChip* _pChip_front;
    /** �����̃��[�U�[�`�b�v */
	LaserChip* _pChip_behind;
    /** ���g��UNIVERSE�ϊ��s�� */
    D3DXMATRIX _matWorld;
    /** ��O����UNIVERSE�ϊ��s�� */
    D3DXMATRIX _matWorld_front;
    /** ���g���Ǘ����Ă郍�[�e�[�V�����A�N�^�[ */
    LaserChipRotationActor* _pRotation;

    GgafDx9LibStg::StgChecker* _pChecker;


    LaserChip(const char* prm_name, const char* prm_model);

    /**
     * ���ʃN���X�ŃI�[�o�[���C�h���ĉ������B
     */
    virtual void initialize();


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

