#ifndef MENUBOARD_H_
#define MENUBOARD_H_

namespace VioletVreath {

/**
 * �{�A�v���̃��j���[�{�[�h�W������ .
 * @version 1.00
 * @since 2011/12/26
 * @author Masatoshi Tsuge
 */
class MenuBoard : public GgafLib::StringBoardMenu {

public:
    enum {
        SE_MENU_OPEN = 0,
        SE_MOVE_CURSOR,
        SE_DECIDED_NOMAL,
        SE_DECIDED_CANCEL,
        SE_MENU_CLOSE,
    };
    coord menu_fade_frames_;
    coord slide_from_offset_X_;
    coord slide_from_offset_Y_;
    coord target_X_;
    coord target_Y_;

    MenuBoard(const char* prm_name, const char* prm_model);

    /**
     * ���j���[�\�����̃X���C�h�g�����W�V�����̐ݒ� .
     * @param prm_menu_fade_frames ���j���[�̃t�F�[�h�C���i�ƃt�F�[�h�A�E�g�j�̃t���[����
     * @param prm_slide_from_offset_X ���j���[�̃X���C�h�J�n�̑���X���W
     * @param prm_slide_from_offset_Y ���j���[�̃X���C�h�J�n�̑���X���W
     */
    void setTransition(frame prm_menu_fade_frames,
                       coord prm_slide_from_offset_X, coord prm_slide_from_offset_Y);


    virtual bool condMoveCursorNext() override;
    virtual bool condMoveCursorPrev() override;
    virtual bool condMoveCursorExNext() override;
    virtual bool condMoveCursorExPrev() override;
    virtual bool condMoveCursorCancel() override;
    virtual bool condDecision() override;
    virtual bool condCancel() override;

    virtual void moveCursor() override;

    virtual void initialize() override;

    /**
     * �\�������ʒu�����݂�_X, _Y�Őݒ肵���j���[���N�� .
     */
    virtual void rise() override;

    /**
     * �\�������ʒu���w�肵�ă��j���[���N�� .
     * �������W�̓X���C�h���������ė����������W���w��B
     * @param prm_target_X �\������X���W
     * @param prm_target_Y �\������Y���W
     */
    virtual void rise(coord prm_target_X, coord prm_target_Y);

    /**
     * �\�������ʒu���w�肵�ăT�u���j���[���N�� .
     * �������W�̓T�u���j���[���X���C�h���������ė����������W���w��B
     * @param prm_pSubMenu �T�u���j���[
     * @param prm_target_X �\������X���W
     * @param prm_target_Y �\������Y���W
     */
    virtual void riseSub(MenuBoard* prm_pSubMenu,
                         coord prm_target_X, coord prm_target_Y); //�Ӑ}�I�� ��ʂ� riseSub �� hide ���Ă܂��B

    virtual void onRisen() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onSunk() override;

    virtual ~MenuBoard();
};

}
#endif /*MENUBOARD_H_*/

