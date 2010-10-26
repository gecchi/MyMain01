#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_

#define FULL_VAL (-2)
#define KARA_VAL (-2)

namespace GgafDx9LibStg {

/**
 * �O�ǃV�[�� .
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WalledSectionScene : public DefaultScene {

    /**
     * �ǃu���b�N(WallActor)�̔z�u���\����
     */
    struct WallInfo {
        /** �\������Y���W */
        int _Y;
        /** �\������Z���W */
        int _Z;
        /** ���\���ʏ�� */
        int _wall_draw_face;
        /** �����蔻��̈�AAB���         */
        int _aColliBoxStretch[6];
    };
public:
    /** [r]�O�ǃV�[���̒����iX���W���̕ǃu���b�N���j */
    int _area_len;
    /** [r]�O�ǃV�[���̍����iY���W���̕ǃu���b�N���j */
    int _area_height;
    /** [r]�O�ǃV�[���̕��iZ���W���̕ǃu���b�N���j */
    int _area_width;
    /** [r]�ǃu���b�N�̒����i�P��WallActor�I�u�W�F�N�g��X���W�������j*/
    int _wall_dep;
    /** [r]�ǃu���b�N�̍����i�P��WallActor�I�u�W�F�N�g��Y���W�������j*/
    int _wall_height;
    /** [r]�ǃu���b�N�̕��i�P��WallActor�I�u�W�F�N�g��Z���W�������j*/
    int _wall_width;
    /** [r]�O�Ǖ\��X���W�ʒu */
    int _wall_start_X;
    /** [r]�O�ǈړ��X�s�[�h(�l�͐��A�A���ړ�������X�����̕���) */
    int _ground_speed;
    /** [r]�J��Ԃ��� */
    int _loop_num;
    /** [r]�J��Ԃ��J�E���^ */
    int _cnt_loop;
    /** [r]�O�Ǖ\���Ԋu���� */
    frame _frame_of_launch_interval;
    /** [r]�\���ς݊O�ǃV�[���̒��� */
    int _cnt_area_len;
    /** [r]�S�ǃu���b�N(WallActor)�̔z�u��� */
    WallInfo** _papaWallInfo;
    /** [r]�S�ǃu���b�N(WallActor)�̔z�u���́A�O�ǃV�[���̒����ʌ� */
    int* _paWallInfoLen;
    /** [r]�ǃu���b�N(WallActor)�f�B�X�p�b�`���[ */
    GgafCore::GgafActorDispatcher* _pDispatcher_Wall;
    /** [r]��O�u���b�N�̓��ߋ@�\�L�����̊�ƂȂ�A�N�^�[ */
    GgafDx9Core::GgafDx9GeometricActor* _pTarget_FrontAlpha;
    /** [r/w]���t���[��processSettlementBehavior()�ŁA�z���A�N�^�[�S�ĂɎ��s�����֐��B*/
    void (*_pFuncWallMove)(GgafCore::GgafObject*, void*, void*);

    WallActor* _pWallLast;


    /**
     * �R���X�g���N�^ .
     * �ǃu���b�N���t�@�C����ǂݍ��݁A�I�u�W�F�N�g�ɓW�J���܂��B
     * �y�g�p�㒍�Ӂz
     * �R���X�g���N�^���s��Ainitialize() �܂ł̊ԂɁA�ǃu���b�N(WallActor)�f�B�X�p�b�`���[(_pDispatcher_Wall)��
     * ���D���ȕǃu���b�N�iWallActor�����N���X�̃I�u�W�F�N�g�j��o�^���������B
     * @param prm_name �V�[����
     * @param prm_data_filename �ǃu���b�N���t�@�C��
     * @param prm_wall_dep �ǃu���b�N�̒����i�P��WallActor�I�u�W�F�N�g��X���W�������j
     * @param prm_wall_width �ǃu���b�N�̍����i�P��WallActor�I�u�W�F�N�g��Y���W�������j
     * @param prm_wall_height �ǃu���b�N�̍����i�P��WallActor�I�u�W�F�N�g��Z���W�������j
     * @param prm_ground_speed �O�ǈړ��X�s�[�h(�l�͐��A�A���ړ�������X�����̕���)
     * @return
     */
    WalledSectionScene(const char* prm_name,
                const char* prm_data_filename,
                int prm_wall_dep, int prm_wall_width, int prm_wall_height,
                int prm_ground_speed, int prm_loop_num = 1);
    /**
     * �������� .
     * �f�B�X�p�b�`���[(_pDispatcher_Wall)�̃`�F�b�N���s���Ă���̂� .
     */
    virtual void initialize() override;

    /**
     * �O�Ǖ\���Ԋu���ԓ����v�Z���ݒ� .
     * �I�[�o�[���C�h����ꍇ�A���̏����̒��� WalledSectionScene::onActive() ���Ăяo���ĉ������B
     */
    virtual void onActive() override;

    /**
     * �z���A�N�^�[�S�Ă�_pFuncWallMove �����s�B
     * �I�[�o�[���C�h����ꍇ�ADefaultScene::processSettlementBehavior(); ���Ăяo�����Ƃ�Y�ꂸ�ɁB
     */
    virtual void processSettlementBehavior() override;


    /**
     * �O�ǂ��o�������A�ړ�������.
     * �I�[�o�[���C�h����ꍇ�A���̏����̒��� WalledSectionScene::processBehavior() ���Ăяo���ĉ������B
     */
    virtual void processBehavior() override;

    virtual void processFinal() override;

    /**
     * ��O�u���b�N�̓��ߋ@�\��L���ɂ���B
     * �����ɂ������ꍇ�� NULL ��ݒ肷��
     * @param prm_pTarget_FrontAlpha ��O�̊�ɂȂ�A�N�^�[
     */
    void enableFrontAlpha(GgafDx9Core::GgafDx9GeometricActor* prm_pTarget_FrontAlpha) {
        _pTarget_FrontAlpha = prm_pTarget_FrontAlpha;
    }

    /**
     * _pFuncWallMove �Ƀf�t�H���g�Őݒ肳��Ă���֐� .
     * �A�N�^�[��X���̕��̕�����_ground_speed�X�N���[��������
     * @param pThat �A�N�^�[�̃|�C���^
     * @param p1 _ground_speed�̃|�C���^
     * @param p2 NULL�i���g�p�j
     */
    static void moveX(GgafCore::GgafObject* pThat, void* p1, void* p2);

    virtual ~WalledSectionScene();
};

}
#endif /*WALLEDSCENE_H_*/
