#ifndef GGAFLIB_WALLEDSECTIONSCENE_H_
#define GGAFLIB_WALLEDSECTIONSCENE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#define FULL_VAL (-2)
#define KARA_VAL (-2)

namespace GgafLib {

/**
 * X�������X�N���[���̕ǃu���b�N�Z�N�V�����V�[�� .
 * WalledScene ���\������V�[���̂P�ł���A
 * WalledSectionScene ���A���Ĉ�� WalledScene ���\�����܂��B<BR>
 * WalledSectionScene �͕ǃu���b�N���t�@�C������Ǐ���ǂݍ��݁A
 * �^�C�~���O�i�X�N���[���X�s�[�h�j���v��Ȃ���A�����ŕǂ��o�������܂��B<BR>
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
        int _pos_info;
        /** �\������Y���W */
        int _y;
        /** �\������Z���W */
        int _z;
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
    coord _wall_dep;
    /** [r]�ǃu���b�N�̍����i�P��WallPartsActor�I�u�W�F�N�g��Y���W�������j*/
    coord _wall_height;
    /** [r]�ǃu���b�N�̕��i�P��WallPartsActor�I�u�W�F�N�g��Z���W�������j*/
    coord _wall_width;
    /** [r]�O�Ǖ\��X���W�ʒu */
    coord _wall_start_x;
    /** [r]�J��Ԃ��� */
    int _loop_num;
    /** [r]�J��Ԃ��J�E���^ */
    int _cnt_loop;
    /** [r]�O�Ǖ\���Ԋu���� */
    frame _frame_of_launch_next;
    /** [r]�\���ς݊O�ǃV�[���̒���(�ǃu���b�N��) */
    int _cnt_area_len;
    /** [r]�S�ǃu���b�N(WallPartsActor)�̔z�u��� */
    WallInfo** _papaWallInfo;
    /** [r]�S�ǃu���b�N(WallPartsActor)�̔z�u���́A�O�ǂ̕ǃu���b�N���B�v�f�����u���b�N�ڂ� */
    int* _paWallInfoLen;
    /** [r]�ǃu���b�N(WallPartsActor)�f�|�W�g�� */
    GgafCore::GgafActorDepository* _pDepo_wall;
    GgafCore::GgafActorDepository* _pDepo_prism;
    /** [r]��O�u���b�N�̓��ߋ@�\�L�����̊�ƂȂ�A�N�^�[ */
    GgafDxCore::GgafDxGeometricActor* _pActor_infront_alpha_target;
    /** �Z�N�V�����V�[���J��Ԃ��t���O */
    bool _is_loop_end;
    WallPartsActor* _pWallPartsLast;

    WalledScene*  _pWalledScene;

public:
    /**
     * �R���X�g���N�^ .
     * �ǃu���b�N���t�@�C����ǂݍ��݁A�I�u�W�F�N�g�ɓW�J���܂��B
     * @param prm_name �V�[����
     * @param prm_data_filename �ǃu���b�N���t�@�C��
     * @param prm_pWalledScene �e�̕ǃV�[���I�u�W�F�N�g
     */
    WalledSectionScene(const char* prm_name, const char* prm_data_filename, WalledScene* prm_pWalledScene);

    /**
     * �O�ǃV�[����ݒ�.
     * new ������Ainitialize() �����s�����܂ł� config ���ĉ������B
     * @param prm_pDepo_wall �ǃu���b�N�iWallAABActor�I�u�W�F�N�g�j���o�^����Ă���f�|�W�g��
     * @param prm_pDepo_prism �ǃv���Y���u���b�N�iWallAAPrismActor�I�u�W�F�N�g�j���o�^����Ă���f�|�W�g��
     * @param prm_wall_start_x �O�Ǐo��X���W�ʒu
     * @param prm_wall_dep �ǃu���b�N�̒����i�P��WallPartsActor�I�u�W�F�N�g��X���W�������j
     * @param prm_wall_width �ǃu���b�N�̍����i�P��WallPartsActor�I�u�W�F�N�g��Y���W�������j
     * @param prm_wall_height �ǃu���b�N�̍����i�P��WallPartsActor�I�u�W�F�N�g��Z���W�������j
     */
    virtual void config(
            GgafCore::GgafActorDepository* prm_pDepo_wall,
            GgafCore::GgafActorDepository* prm_pDepo_prism,
            coord prm_wall_start_x,
            coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height);

    /**
     * �������� .
     * �f�|�W�g��(_pDepo_wall)�̃`�F�b�N���s���Ă���̂� .
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

    WallPartsActor* getLastWallParts() const;

    /**
     * ��O�u���b�N�̓��ߋ@�\��L���ɂ���B
     * �����ɂ������ꍇ�� nullptr ��ݒ肷��
     * @param prm_pActor_infront_alpha_target ��O�̊�ɂȂ�A�N�^�[
     */
    void enableInfrontAlpha(GgafDxCore::GgafDxGeometricActor* prm_pActor_infront_alpha_target) {
        _pActor_infront_alpha_target = prm_pActor_infront_alpha_target;
    }

    /**
     * YZ�ʂɁA�u���b�N�̃Z�b�g���o���������ɌĂяo�����R�[���o�b�N�B .
     * �I�[�o�[���C�h���Ă������̂�B
     * @param prm_loop_count �Z�N�V�����̃��[�v���J�E���g(0�`)
     * @param prm_wall_count �Z�N�V������YZ�ʃu���b�N�Z�b�g���J�E���g(0�`)
     * @param prm_wall_x �o������YZ�ʂ̃u���b�N��X���W
     */
    virtual void onBlockLaunch(int prm_loop_count, int prm_wall_count, coord prm_wall_x) {};

    virtual ~WalledSectionScene();
};

}
#endif /*GGAFLIB_WALLEDSECTIONSCENE_H_*/
