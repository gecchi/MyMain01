#ifndef MENUBOARD_H_
#define MENUBOARD_H_

namespace VioletVreath {

/**
 * �{�A�v���̃��j���[�{�[�h�W������ .
 * �X���C�h�̃g�����W�V���������B
 * �L�����Z���̎����B
 * @version 1.00
 * @since 2011/12/26
 * @author Masatoshi Tsuge
 */
class MenuBoard : public GgafLib::StringBoardMenu {

public:
    enum {
        SE_ON_RISEN = 0,
        SE_MOVE_CURSOR,
        SE_DECIDED_CANCEL,
    };
    coord menu_fade_frames_;
    coord slide_from_offset_X_;
    coord slide_from_offset_Y_;
    coord target_X_;
    coord target_Y_;

public:
    MenuBoard(const char* prm_name, const char* prm_model);

    /**
     * ���j���[�\�����̃X���C�h�g�����W�V�����̐ݒ� .
     * @param prm_menu_fade_frames ���j���[�̃t�F�[�h�C���i�ƃt�F�[�h�A�E�g�j�̃t���[����
     * @param prm_slide_from_offset_X ���j���[�̃X���C�h�J�n�̑���X���W
     * @param prm_slide_from_offset_Y ���j���[�̃X���C�h�J�n�̑���X���W
     */
    void setTransition(frame prm_menu_fade_frames,
                       coord prm_slide_from_offset_X, coord prm_slide_from_offset_Y);

    virtual bool condDecision() override;
    virtual bool condCancel() override;
    virtual bool condSelectNext() override;
    virtual bool condSelectPrev() override;
    virtual bool condSelectExNext() override;
    virtual bool condSelectrExPrev() override;
    virtual bool condSelectCancel() override;
    virtual void moveCursor(bool prm_smooth = true) override;
    virtual void onMoveCursor(int prm_from, int prm_to) override;
    virtual void onSelect(int prm_from, int prm_to) override;

    virtual void initialize() override;

    /**
     * �\�������ʒu�����݂�_X, _Y�Őݒ肵���j���[(���g)���N�� .
     * �ʏ�͑��̃I�u�W�F�N�g����Ăяo����郁�\�b�h�ł��B
     */
    virtual void rise() override;

    /**
     * �\�������ʒu���w�肵�ă��j���[(���g)���N�� .
     * �������W�̓X���C�h���������ė����������W���w��B
     * �ʏ�͑��̃I�u�W�F�N�g����Ăяo����郁�\�b�h�ł��B
     * @param prm_target_X �\������X���W
     * @param prm_target_Y �\������Y���W
     */
    virtual void rise(coord prm_target_X, coord prm_target_Y);

    /**
     * �\�������ʒu���w�肵�ăT�u���j���[���N�� .
     * �������W�̓T�u���j���[���X���C�h���������ė����������W���w��B
     * @param prm_index �T�u���j���[�C���f�b�N�X(�ǉ��������ԁB0�`)
     * @param prm_target_X �T�u���j���[�\������X���W
     * @param prm_target_Y �T�u���j���[�\������Y���W
     */
    virtual void riseSubMenu(int prm_index, coord prm_target_X, coord prm_target_Y);

    virtual void onRisen() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onSunk() override;

    virtual ~MenuBoard();
};

}
#endif /*MENUBOARD_H_*/

