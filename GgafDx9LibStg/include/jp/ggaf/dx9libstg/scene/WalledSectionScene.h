#ifndef WALLEDSECTIONSCENE_H_
#define WALLEDSECTIONSCENE_H_

#define FULL_VAL (-2)
#define KARA_VAL (-2)

namespace GgafDx9LibStg {

/**
 * �O�ǃZ�N�V�����V�[�� .
 * �u�O�ǃV�[���v���\������V�[���ł���A
 * �O�ǃZ�N�V�����V�[�����A���Ĉ�́u�O�ǃV�[���v���\�����܂��B
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WalledSectionScene : public DefaultScene {

    /**
     * �ǃu���b�N(WallPartsActor)�̔z�u���\����
     */
    struct WallInfo {
        /** �v���Y���ʒu���(> 0�̏ꍇ�̓v���Y���A0�̏ꍇ��BOX) */
        int _pos_prism;
        /** �\������Y���W */
        int _Y;
        /** �\������Z���W */
        int _Z;
        /** ���\���ʏ�� */
        int _wall_draw_face;
        /** �����蔻��̈�AAB��� */
        int _aColliBoxStretch[6];
    };
public:
    /** [r]�O�ǃV�[���̒����iX���W���̕ǃu���b�N���j */
    int _area_len;
    /** [r]�O�ǃV�[���̍����iY���W���̕ǃu���b�N���j */
    int _area_height;
    /** [r]�O�ǃV�[���̕��iZ���W���̕ǃu���b�N���j */
    int _area_width;
    /** [r]�ǃu���b�N�̒����i�P��WallPartsActor�I�u�W�F�N�g��X���W�������j*/
    int _wall_dep;
    /** [r]�ǃu���b�N�̍����i�P��WallPartsActor�I�u�W�F�N�g��Y���W�������j*/
    int _wall_height;
    /** [r]�ǃu���b�N�̕��i�P��WallPartsActor�I�u�W�F�N�g��Z���W�������j*/
    int _wall_width;
    /** [r]�O�Ǖ\��X���W�ʒu */
    int _wall_start_X;
    /** [r]�J��Ԃ��� */
    int _loop_num;
    /** [r]�J��Ԃ��J�E���^ */
    int _cnt_loop;
    /** [r]�O�Ǖ\���Ԋu���� */
    frame _frame_of_launch_next;
    /** [r]�\���ς݊O�ǃV�[���̒��� */
    int _cnt_area_len;
    /** [r]�S�ǃu���b�N(WallPartsActor)�̔z�u��� */
    WallInfo** _papaWallInfo;
    /** [r]�S�ǃu���b�N(WallPartsActor)�̔z�u���́A�O�ǃV�[���̒����ʌ� */
    int* _paWallInfoLen;
    /** [r]�ǃu���b�N(WallPartsActor)�X�g�A�[ */
    GgafCore::GgafActorStore* _pStore_WallAAB;
    GgafCore::GgafActorStore* _pStore_WallAAPrism;
    /** [r]��O�u���b�N�̓��ߋ@�\�L�����̊�ƂȂ�A�N�^�[ */
    GgafDx9Core::GgafDx9GeometricActor* _pTarget_FrontAlpha;

    bool _is_loop_end;
    WallPartsActor* _pWallPartsLast;

    ScrolledScene*  _pScrolledScene;

    /**
     * �R���X�g���N�^ .
     * �ǃu���b�N���t�@�C����ǂݍ��݁A�I�u�W�F�N�g�ɓW�J���܂��B
     * @param prm_name �V�[����
     * @param prm_data_filename �ǃu���b�N���t�@�C��
     * @return
     */
    WalledSectionScene(const char* prm_name, const char* prm_data_filename, ScrolledScene* prm_pScrolledScene);



    /**
     * �O�ǃV�[����ݒ�.
     * new ������Ainitialize() �����s�����܂ł� config ���ĉ������B
     * @param prm_pStore_Wall �ǃu���b�N�iWallPartsActor�����N���X�̃I�u�W�F�N�g�j���o�^����Ă���X�g�A�[
     * @param prm_wall_dep �ǃu���b�N�̒����i�P��WallPartsActor�I�u�W�F�N�g��X���W�������j
     * @param prm_wall_width �ǃu���b�N�̍����i�P��WallPartsActor�I�u�W�F�N�g��Y���W�������j
     * @param prm_wall_height �ǃu���b�N�̍����i�P��WallPartsActor�I�u�W�F�N�g��Z���W�������j
     * @param prm_loop_num �Z�N�V�����J��Ԃ���
     */
    virtual void config(
            GgafCore::GgafActorStore* prm_pStore_WallAAB,
            GgafCore::GgafActorStore* prm_pStore_WallAAPrism,
            int prm_wall_dep, int prm_wall_width, int prm_wall_height);
    /**
     * �������� .
     * �X�g�A�[(_pStore_Wall)�̃`�F�b�N���s���Ă���̂� .
     */
    virtual void initialize() override;

    /**
     * �O�Ǖ\���Ԋu���ԓ����v�Z���ݒ� .
     * �I�[�o�[���C�h����ꍇ�A���̏����̒��� WalledSectionScene::onActive() ���Ăяo���ĉ������B
     */
    virtual void onActive() override;


    /**
     * �O�ǂ��o�������A�ړ�������.
     * �I�[�o�[���C�h����ꍇ�A���̏����̒��� WalledSectionScene::processBehavior() ���Ăяo���ĉ������B
     */
    virtual void processBehavior() override;

    virtual void processFinal() override;

    WallPartsActor* getLastWallParts();



    /**
     * ��O�u���b�N�̓��ߋ@�\��L���ɂ���B
     * �����ɂ������ꍇ�� NULL ��ݒ肷��
     * @param prm_pTarget_FrontAlpha ��O�̊�ɂȂ�A�N�^�[
     */
    void enableFrontAlpha(GgafDx9Core::GgafDx9GeometricActor* prm_pTarget_FrontAlpha) {
        _pTarget_FrontAlpha = prm_pTarget_FrontAlpha;
    }


    virtual ~WalledSectionScene();
};

}
#endif /*WALLEDSECTIONSCENE_H_*/
