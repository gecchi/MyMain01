#ifndef FORMATIONEUNOMIA_H_
#define FORMATIONEUNOMIA_H_
namespace MyStg2nd {

/**
 * �G�@�G�E�m�~�A�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia : public GgafDx9LibStg::FormationActor {

public:
    /** �G�E�m�~�A�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon_Eunomia;

    /** �G�E�m�~�A�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* _pDepoCon_shot;
    /** �X�v���C����`�����ւ̐ڑ� */
//    GgafDx9LibStg::SplineSourceConnection* _pSplSrcCon;
    GgafDx9LibStg::SplineManufactureConnection** _papSplManufCon;
    /** �ґ���(RANK�ϓ�) */
    int _num_formation_col;
    /** �P��̕ґ���(RANK�ϓ�) */
    int _num_formation_row;
//    /** �G�E�m�~�A��2�����z��(RANK�ϓ�) */
//    EnemyEunomia*** _papapEunomia;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame _interval_frames;
    /** �ړ����x(RANK�ϓ�) */
    velo _mv_velo;

    int _n;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_col            �ґ��� ( >= 1)
     * @param prm_row            �P��̕ґ��� ( >= 1)
     * @param prm_interval_frames �G�E�m�~�A�̊Ԋu(frame) ( >= 1)
     * @param prm_mv_velo        ���x
     * @param prm_spl_id         �X�v���C����`�t�@�C���v���t�B�N�X
     *                           "FormationEunomia001_0.spl" �� "FormationEunomia001" ��ݒ�
     * @return
     */
    FormationEunomia(const char* prm_name, int   prm_col,
                                           int   prm_row,
                                           frame prm_interval_frames,
                                           velo  prm_mv_velo,
                                           const char* prm_spl_id) ;

    virtual void initialize() override;

    virtual void processOnActiveEunomia(EnemyEunomia* pEnemyEunomia, int col) = 0;

    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) override {
    }

    virtual void processBehavior() override;

    virtual ~FormationEunomia();
};

}
#endif /*FORMATIONEUNOMIA_H_*/
