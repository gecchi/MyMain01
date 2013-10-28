#ifndef MENUSELECTSUB_H_
#define MENUSELECTSUB_H_
#include "jp/ggaf/lib/actor/menu/MenuActor.hpp"

namespace VioletVreath {

/**
 * �{�A�v���̃��j���[�{�[�h�̃Z���N�g���i .
 * @version 1.00
 * @since 2013/06/06
 * @author Masatoshi Tsuge
 */
class MenuSelectSub : public GgafLib::StringBoardMenu {

public:
    enum {
        SE_MOVE_CURSOR   ,
    };
    coord target_x_;
    coord target_y_;

public:
    MenuSelectSub(const char* prm_name, const char* prm_model);


    virtual bool condDecision() override;
    virtual bool condCancel() override;
    virtual bool condSelectNext() override;
    virtual bool condSelectPrev() override;
    virtual bool condSelectExNext() override;
    virtual bool condSelectExPrev() override;
    virtual bool condSelectCancel() override;
    virtual void moveCursor(bool prm_smooth = true) override;
    virtual void onMoveCursor(int prm_from, int prm_to) override;
    virtual void onSelect(int prm_from, int prm_to) override;

    virtual void initialize() override;

    /**
     * �\�������ʒu�����݂�_x, _y�Őݒ肵���j���[(���g)���N�� .
     * �ʏ�͑��̃I�u�W�F�N�g����Ăяo����郁�\�b�h�ł��B
     */
    virtual void riseMe() override;

    /**
     * �\�������ʒu���w�肵�ă��j���[(���g)���N�� .
     * �������W�̓X���C�h���������ė����������W���w��B
     * �ʏ�͑��̃I�u�W�F�N�g����Ăяo����郁�\�b�h�ł��B
     * @param prm_target_x �\������X���W
     * @param prm_target_y �\������Y���W
     */
    virtual void rise(coord prm_target_x, coord prm_target_y);

    /**
     * �\�������ʒu���w�肵�ăT�u���j���[���N�� .
     * �������W�̓T�u���j���[���X���C�h���������ė����������W���w��B
     * (�� void MenuActor<T>::riseSubMenu(int prm_index) ���B��)
     * @param prm_index �T�u���j���[�C���f�b�N�X(�ǉ��������ԁB0�`)
     * @param prm_target_x �T�u���j���[�\������X���W
     * @param prm_target_y �T�u���j���[�\������Y���W
     */
    virtual void riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y);

    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override {
    }
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override {
    }

    virtual void onRise() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onSink() override;

    virtual ~MenuSelectSub();
};

}
#endif /*MENUBOARD_H_*/

