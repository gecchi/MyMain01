#ifndef MENUACTOR_H_
#define MENUACTOR_H_
namespace GgafLib {

/**
 * ���j���[ .
 * GUI�ȈՃ��j���[���ȒP�Ɏ������邽�߂̃e���v���[�g�ł��B<BR>
 * <b>�y�܂���킵���p��̋�ʁz</b><BR>
 * �E�L�����Z���i���j���[�A�C�e���j�c �u�L�����Z���v�̓��삪���҂����GUI���i�̎����w���B�i��F [Cancel] �� [������] �̃{�^�����́j<BR>
 * �E����i�U�镑���j              �c ���[�U�[����ŁA�u����v�̈ӎv��\��������w���B�i��F [ENTER]�L�[��A[��]�{�^�����������j<BR>
 * �E�L�����Z���i�U�镑���j        �c ���[�U�[����ŁA�u�L�����Z���v�̈ӎv��\��������w���B�i��F [ESC]�L�[��A[�~]�{�^�����������j<BR>
 * ���Ɂu�L�����Z�������v�ƌ����鎖�ɂ��āA�{�e�ł̐����ł́A<BR>
 * �w�u�L�����Z���i���j���[�A�C�e���j�v�ŁA�u����i�U�镑���j �v�����B�x<BR>
 * �Ƃ����߂�ǂ������\���ɂȂ��Ă��܂��B<BR>
 * <BR>
 * �����Ӂ�<BR>
 * �{�N���X�́u�L�����Z���i���j���[�A�C�e���j�v�u����i�U�镑���j�v�u�L�����Z���i�U�镑���j�v����ʈ������A
 * �l�X�ȋ@�\���T�|�[�g���܂����A[OK]�{�^�����́u����i���j���[�A�C�e���j�v�ɂ��Ă̋@�\�͍��̂Ƃ��날��܂���B<BR>
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class MenuActor : public T {

protected:

    enum MenuItemWay {
        ITEM_RELATION_EX_NEXT = 0,
        ITEM_RELATION_EX_PREV,
        ITEM_RELATION_TO_CANCEL,
    };

    /** �J�[�\���̕␳X���W */
    coord _X_cursor_adjust;
    /** �J�[�\���̕␳Y���W */
    coord _Y_cursor_adjust;
    /** �J�[�\���̕␳Z���W */
    coord _Z_cursor_adjust;

    /** �J�[�\���ړ���A�C�e���̑O�t���[����X���W */
    coord _X_cursor_target_prev;
    /** �J�[�\���ړ���A�C�e���̑O�t���[����Y���W */
    coord _Y_cursor_target_prev;
    /** �J�[�\���ړ���A�C�e���̑O�t���[����Z���W */
    coord _Z_cursor_target_prev;
    /** �t�F�[�h�C������ true */
    bool _with_rising;
    /** �t�F�[�h�A�E�g���� true */
    bool _with_sinking;
    /** �t�F�[�h�C�����J�n�����u�Ԃ̃t���[������ true */
    bool _is_just_risen;
    /** �t�F�[�h�A�E�g���J�n�����u�Ԃ̃t���[������ true */
    bool _is_just_sunk;
    /** �u����i�U�镑���j�v�����u�Ԃ̃t���[������ true */
    bool _is_just_decided;
    /** �u�L�����Z���i�U�镑���j�v�����u�Ԃ̃t���[������ true */
    bool _is_just_cancelled;

    bool _will_be_rising_next_frame;

    bool _will_be_sinking_next_frame;

    bool _will_be_just_decided_next_frame;

    bool _will_be_just_cancelled_next_frame;

    bool _can_controll;

    bool _will_be_able_to_controll;

protected:
    /**
     * _lstItems �̃A�N�e�B�u�v�f�� next() �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void selectNext();

    /**
     * _lstItems �̃A�N�e�B�u�v�f�� prev() �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void selectPrev();

    /**
     * _lstItems �̃A�N�e�B�u�v�f�� gotoRelation(ITEM_RELATION_EX_NEXT) �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void selectExNext();

    /**
     * _lstItems �̃A�N�e�B�u�v�f�� gotoRelation(ITEM_RELATION_EX_PREV) �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void selectExPrev();

    /**
     *  _lstItems �̃A�N�e�B�u�v�f�� gotoRelation(ITEM_RELATION_TO_CANCEL) �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void selectCancel();

public:
    /** [r]���j���[�A�C�e���̃��X�g */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstItems;
    /** [r]���j���[�J�[�\�� */
    GgafDxCore::GgafDxDrawableActor* _pCursor;
    /** [r]���̑��\���A�C�e���̃��X�g */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstDispActors;
    /** [r]�J�[�\�����ړ��������j���[�A�C�e���C���f�b�N�X�̃q�X�g���[(0�`N�A�A�������͑S�� -1 ) */
    GgafCore::GgafLinkedListRing<int> _lstMvCursorHistory;
    /** [r]�I���������j���[�A�C�e���C���f�b�N�X�̃q�X�g���[(0�`N�A�A�������͑S�� -1 ) */
    GgafCore::GgafLinkedListRing<int> _lstMvSelectHistory;

    /** [r]���j���[�t�F�C�h�C���E�A�E�g���̃t���[���� */
    frame _fade_frames;
    /** [r]���j���[�t�F�C�h�C���E�A�E�g���̃A���t�@���x */
    float _velo_alpha_fade;
    /** [r]�J�[�\�����A���j���[�A�C�e���Ԃ��ړ�����ۂɔ�₷�X�t���[���� */
    int _cursor_move_frames;
    /** [r]�J�[�\�����ړ����A�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊��� */
    float _cursor_move_p1;
    /** [r]�J�[�\�����ړ����A�A�C�e���Ԉړ������̍ō������猸�����J�n���銄�� */
    float _cursor_move_p2;
    /** [r]�T�u���j���[�̃��X�g */
    GgafCore::GgafLinkedListRing<MenuActor<T>> _lstSubMenu;

public:
    /**
     * �R���X�g���N�^ .
     * �y���Ӂz��������񊈓���Ԃ��f�t�H���g�Ƃ��Ă��܂��B<BR>
     * ��̓I�ɂ� T::inactivateImmed(); ���R�[�����Ă��܂��B
     * @param prm_name
     * @param prm_model ���f�����ʖ�
     */
    MenuActor(const char* prm_name, const char* prm_model);

    /**
     * ���ݓ��͂��󂯕t�����Ă����Ԃ���Ԃ� .
     * �T�u���j���[���\������Ă���ԓ��́A����s�ɂȂ�A�{���\�b�h��false��Ԃ��܂��B
     * @return true:�R���g���[���\���/false:�R���g���[���s�\���
     */
    virtual bool canControll() {
        return _can_controll;
    }

    /**
     * ���͂��󂯕t���𖳌� .
     * �I��������ɌĂяo���A���̎g�p��z��B
     */
    virtual void disableControll() {
        _will_be_able_to_controll = false;
    }

    /**
     * ���͂��󂯕t����L�� .
     */
    virtual void enableControll() {
        _will_be_able_to_controll = true;
    }

    /**
     * ���j���[�t�F�C�h�C���E�A�E�g���̃A���t�@���x��ݒ� .
     * @param prm_menu_fade_frames �t�F�[�h�t���[������
     */
    virtual void setFadeFrames(frame prm_menu_fade_frames) {
        _fade_frames = prm_menu_fade_frames;
        _velo_alpha_fade = 1.0 / prm_menu_fade_frames;
    }

    /**
     * �I���\���j���[�A�C�e����ǉ����A���j���[�A�C�e���Ԃ̃I�[�_�[���A���ǉ����� .
     * �ǉ����ꂽ�A�C�e���̓��j���[�I�u�W�F�N�g(this)�̃T�u�ɓo�^����邽�߁A
     * ���j���[�I�u�W�F�N�g���^�X�N�c���[�ɓo�^�����Ȃ�� delete ����K�v�͂Ȃ��B
     * �y���Ӂz<BR>
     * ����Z���W�Ȃ�΁A��� addItem() ���������A����O�ɕ\���ƂȂ�B<BR>
     * @param prm_pItem ���j���[�A�C�e��
     * @param prm_X_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_Z_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_X_local, coord prm_Y_local, coord prm_Z_local);
    /**
     * �I���\���j���[�A�C�e���ǉ����A���j���[�A�C�e���Ԃ̃I�[�_�[���A���ǉ����� .
     * �ǉ����ꂽ�A�C�e���̓��j���[�I�u�W�F�N�g(this)�̃T�u�ɓo�^����邽�߁A
     * ���j���[�I�u�W�F�N�g���^�X�N�c���[�ɓo�^�����Ȃ�� delete ����K�v�͂Ȃ��B<BR>
     * �y���Ӂz<BR>
     * ����Z���W�Ȃ�΁A��� addItem() ���������A����O�ɕ\���ƂȂ�B<BR>
     * Z���W�́A�I�t�Z�b�g0���ݒ肳���B�܂�A�C�e���̐��Z���W�́A���݂̃��j���[��Z���W�ƈ�v����B<BR>
     * �������j���[��2D�ŁA�A�C�e���̕\���v���C�I���e�B�̍l�����K�v�ȏꍇ�́A�I�t�Z�b�g��-1���ɖ����ݒ���\�B
     * @param prm_pItem ���j���[�A�C�e��
     * @param prm_X_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     */
    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_X_local, coord prm_Y_local) {
        addItem(prm_pItem, prm_X_local, prm_Y_local, 0);
    }

    /**
     * �I��s�̕\���p���j���[�A�C�e��(���x��)��ǉ����� .
     * �y���Ӂz<BR>
     * ����Z���W�Ȃ�΁A����̏��� addDisp() ���������A����O�ɕ\���ƂȂ�B<BR>
     * @param prm_pItem �\���p���x���̃A�N�^�[
     * @param prm_X_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_Z_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                         coord prm_X_local, coord prm_Y_local, coord prm_Z_local);

    /**
     * �I��s�̕\���p���j���[���x����ǉ����� .
     * �y���Ӂz<BR>
     * ����Z���W�Ȃ�΁A����̏��� addDisp() ���������A����O�ɕ\���ƂȂ�B<BR>
     * Z���W�́A�I�t�Z�b�g0���ݒ肳���B�܂�\���p�A�N�^�[�̐��Z���W�́A���݂̃��j���[��Z���W�ƈ�v����B
     * �������j���[��2D�ŁA�A�C�e���̕\���v���C�I���e�B�̍l�����K�v�ȏꍇ�́A�I�t�Z�b�g��-1���ɖ����ݒ���\�B
     * @param prm_pItem �\���p���x���̃A�N�^�[
     * @param prm_X_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     */
    virtual void addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                         coord prm_X_local, coord prm_Y_local) {
        addDisp(prm_pDisp, prm_X_local, prm_Y_local, 0);
    }

    /**
     * ���j���[�J�[�\���I�u�W�F�N�g��ݒ肷�� .
     * �y���Ӂz<BR>
     * �J�[�\���ړ��𐧌䂷�邽�߁AMenuActor<T>::processBehavior() ���ŁA<BR>
     * _pCursor->_pKurokoA->behave(); <BR>
     * �����s���Ă��܂��B���������āA�����̃J�[�\���N���X�ŁA<BR>
     * _pKurokoA->behave(); <BR>
     * �����s����K�v�͂���܂���B<BR>
     * @param prm_pCursor �J�[�\��
     * @param prm_X_cursor_adjust �A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��X���W
     * @param prm_Y_cursor_adjust �A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��Y���W
     * @param prm_Z_cursor_adjust �A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��Z���W
     * @param prm_cursor_move_frames �J�[�\�����A�C�e���Ԉړ��ɔ�₷�t���[��(�f�t�H���g8�t���[��)
     * @param prm_cursor_move_p1 �J�[�\�����ړ����A�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊���(�f�t�H���g0.2)
     * @param prm_cursor_move_p2 �J�[�\�����ړ����A�A�C�e���Ԉړ������̍ō������猸�����J�n���銄��(�f�t�H���g0.7)
     */
    virtual void setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor,
                           coord prm_X_cursor_adjust = 0,
                           coord prm_Y_cursor_adjust = 0,
                           coord prm_Z_cursor_adjust = 0,
                           int prm_cursor_move_frames = 8,
                           float prm_cursor_move_p1 = 0.2,
                           float prm_cursor_move_p2 = 0.7);
    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(���g��From �� To) .
     * addItem(GgafDxCore::GgafDxDrawableActor*) �ɂ��A�ǉ����s�����ƂŁA�����I��<BR>
     * ���A�O�A�̐��`�I�[�_�[���\�z����Ă��邪�A<BR>
     * ���̃��\�b�h�͂���Ƃ͕ʂɃA�C�e���Ԃ́u���v�A�u�O�v�A�̊֌W��ǉ��ݒ肷��B<BR>
     * �Ⴆ�΁A�u���v�L�[�Łu���v�A�u���v�L�[�Łu�߂�v�Ƃ�������ɂȂ��Ă���Ƃ���ɁA
     * ����Ɂu���v�u���v�̈ړ����ʓr�ݒ肷��Ƃ������g�p���@��z��B<BR>
     * @param prm_index_of_fromitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X
     * @param prm_index_of_toitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X����
     *                            �u���v�ɑΉ�����A����̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void relateItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(item1 �� item2  �� item3) .
     * @param prm_index_of_item1 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X1
     * @param prm_index_of_item2 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X2
     * @param prm_index_of_item3 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X3
     */
    virtual void relateItemExNext(int prm_index_of_item1,
                                  int prm_index_of_item2,
                                  int prm_index_of_item3);
    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(item1 �� item2  �� item3 �� item4) .
     * @param prm_index_of_item1 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X1
     * @param prm_index_of_item2 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X2
     * @param prm_index_of_item3 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X3
     * @param prm_index_of_item4 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X4
     */
    virtual void relateItemExNext(int prm_index_of_item1,
                                  int prm_index_of_item2,
                                  int prm_index_of_item3,
                                  int prm_index_of_item4);
    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(item1 �� item2  �� item3 �� item4 �� item5).
     * @param prm_index_of_item1 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X1
     * @param prm_index_of_item2 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X2
     * @param prm_index_of_item3 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X3
     * @param prm_index_of_item4 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X4
     * @param prm_index_of_item5 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X5
     */
    virtual void relateItemExNext(int prm_index_of_item1,
                                  int prm_index_of_item2,
                                  int prm_index_of_item3,
                                  int prm_index_of_item4,
                                  int prm_index_of_item5);


//    virtual void relateItemExNext(int prm_index_of_fromitem, ...);

    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(From �� ���g��To) .
     * addItem(GgafDxCore::GgafDxDrawableActor*) �ɂ��A�ǉ����s�����ƂŁA�����I��<BR>
     * ���A�O�A�̐��`�I�[�_�[���\�z����Ă��邪�A<BR>
     * ���̃��\�b�h�͂���Ƃ͕ʂɃA�C�e���Ԃ́u�O�v�A�u���v�A�̊֌W��ǉ��ݒ肷��B<BR>
     * �Ⴆ�΁A�u���v�L�[�Łu���v�A�u���v�L�[�Łu�߂�v�Ƃ�������ɂ����ꍇ��
     * �u���v�u���v�̈ړ����ݒ肷��Ƃ������g�p���@��z��B<BR>
     * @param prm_index_of_fromitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X
     * @param prm_index_of_toitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X����
     *                            �u�O�v�ɑΉ�����A����̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void relateItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * �����A�C�e���S�Ăɑ΂��A�u�L�����Z���i���j���[�A�C�e���j�v�ւ̃I�[�_�[�A�����g���ݒ肷�� .
     * @param prm_index_of_cancel_item �L�����Z���A�C�e���ւ̃A�C�e���C���f�b�N�X
     */
    virtual void relateAllItemCancel(int prm_index_of_cancel_item);

    /**
     * ���j���[�ɐݒ肳��Ă���J�[�\�����擾 .
     * @return �J�[�\���I�u�W�F�N�g
     */
    virtual GgafDxCore::GgafDxDrawableActor* getCursor();

    /**
     * �w��̃C���f�b�N�X�̃��j���[�A�C�e���ցA�J�[�\�����Z�b�g .
     * ������ moveCursor() ���R�[���o�b�N����A�J�[�\�����ړ����邱�ƂɂȂ�B<BR>
     * ���Ɏw��̃C���f�b�N�X�I�𒆂̏ꍇ�̓J�[�\���͉����ړ������B<BR>
     * ���łɁA�����C���f�b�N�X�̃A�C�e���I�u�W�F�N�g���Q�b�g�o����B<BR>
     * @param prm_index �^�[�Q�b�g�̃A�C�e���C���f�b�N�X
     * @return prm_index�̃A�C�e���I�u�W�F�N�g
     */
    virtual GgafDxCore::GgafDxDrawableActor* selectItem(int prm_index);

    /**
     * �w��̃��j���[�A�C�e���ցA�J�[�\�����Z�b�g .
     * ������ moveCursor() ���R�[���o�b�N����A�J�[�\�����ړ����邱�ƂɂȂ�B<BR>
     * ���Ɏw��̃C���f�b�N�X�I�𒆂̏ꍇ�̓J�[�\���͉����ړ������B<BR>
     * ���łɁA�����A�C�e���I�u�W�F�N�g�̃C���f�b�N�X���Q�b�g�o����B<BR>
     * @param prm_item �^�[�Q�b�g�̃A�C�e��
     * @return �^�[�Q�b�g�̃A�C�e���C���f�b�N�X
     */
    virtual int selectItem(GgafDxCore::GgafDxDrawableActor* prm_item);

    /**
     * ���݃J�[�\�����I�𒆂̃A�C�e���̃C���f�b�N�X���擾 .
     * @return �I�𒆂̃A�C�e���I�u�W�F�N�g�̃C���f�b�N�X
     */
    virtual int getSelectedIndex();

    /**
     * ���݃J�[�\�����I�𒆂̃A�C�e���̃I�u�W�F�N�g���擾 .
     * @return �I�𒆂̃A�C�e���I�u�W�F�N�g
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItem();

    /**
     * �ߋ��ɃJ�[�\�����I�𒆂������A�C�e���̃C���f�b�N�X���擾 .
     * getMvCursorHistoryIndex(0) �� getSelectedIndex() �Ɠ����ł��B
     * �w��̉ߋ����Ȃ��ꍇ�� -1 ��Ԃ��܂��B
     * @param prm_n ��ߋ��̃J�[�\���ʒu��(0 �`)
     * @return �I�𒆂������̃A�C�e���I�u�W�F�N�g�̃C���f�b�N�X�i�����ꍇ�� -1�j
     */
    virtual int getMvCursorHistoryIndex(int prm_n);

    /**
     * �u����i�U�镑���j�v���s��ꂽ���ɁA���̃��j���[�A�C�e���̃C���f�b�N�X��Ԃ��܂� .
     * ����ȊO�̎��� ��� -1 ��Ԃ��܂�<BR>
     * �����j���[�̑I�����ڂ����肳�ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �� getOnDecidedIndex() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA���莞�̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onDecision() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B<BR>
     * @return ���肳�ꂽ���F���̃A�C�e���̃C���f�b�N�X(>=0)�^�������肳��Ă��Ȃ��ꍇ�F��� -1
     */
    virtual int getOnDecidedIndex();

    /**
     * �u����i�U�镑���j�v���s��ꂽ���ɁA���̃��j���[�A�C�e����Ԃ��܂� .
     * ����ȊO�̎��� ��� nullptr ��Ԃ��܂�<BR>
     * �����j���[�̑I�����ڂ����肳�ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �� getOnDecidedItem() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA���莞�̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onDecision() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B<BR>
     * @return ���肳�ꂽ���F���̃A�C�e���^�������肳��Ă��Ȃ��ꍇ�F��� nullptr
     */
    virtual GgafDxCore::GgafDxDrawableActor* getOnDecidedItem();

    /**
     * �u�L�����Z���i�U�镑���j�v���s��ꂽ���ɁA���̃��j���[�A�C�e���̃C���f�b�N�X��Ԃ��܂� .
     * ����ȊO�̎��� ��� -1 ��Ԃ��܂�<BR>
     * �����j���[�̑I�����ڂ��L�����Z�����ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �� getOnCancelledIndex() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA�L�����Z�����̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onCancel() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B<BR>
     * @return �L�����Z�����ꂽ���F���̃A�C�e���̃C���f�b�N�X(>=0)�^�����L�����Z������Ă��Ȃ��ꍇ�F��� -1
     */
    virtual int getOnCancelledIndex();

    /**
     * �u�L�����Z���i�U�镑���j�v���s��ꂽ���ɁA���̃��j���[�A�C�e����Ԃ��܂� .
     * ����ȊO�̎��� ��� -1 ��Ԃ��܂�<BR>
     * �����j���[�̑I�����ڂ��L�����Z�����ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �� getOnCancelledItem() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA�L�����Z�����̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onCancel() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B<BR>
     * @return �L�����Z�����ꂽ���F���̃A�C�e���^�����L�����Z������Ă��Ȃ��ꍇ�F��� nullptr
     */
    virtual GgafDxCore::GgafDxDrawableActor* getOnCancelledItem();

    /**
     * �I��ΏۃA�C�e���̃I�u�W�F�N�g���擾 .
     * @param prm_index �擾�������I��ΏۃA�C�e���̃C���f�b�N�X(0�`)
     * @return �A�C�e���I�u�W�F�N�g
     */
    virtual GgafDxCore::GgafDxDrawableActor* getItem(int prm_index);

    /**
     * ���̑��\���p�A�C�e���̃I�u�W�F�N�g���擾 .
     * @param prm_index �擾�������\���p�A�C�e���̃C���f�b�N�X(0�`)
     * @return �\���p�A�C�e���I�u�W�F�N�g
     */
    virtual GgafDxCore::GgafDxDrawableActor* getDisp(int prm_index);

    /**
     * �u����i�U�镑���j�v�����A�Ƃ������̐����������������� .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B <BR>
     * ����t���[���� condDecision() �� condCancel() �̏��������͂ǂ��炩������������A
     * ����D�揇�ʂ́AcondDecision() �̕�����ł��B<BR>
     * @return �u����i�U�镑���j�v�̏������� / false:�s����
     */
    virtual bool condDecision() = 0;

    /**
     * �u�L�����Z���i�U�镑���j�v�����A�Ƃ������̐����������������� .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B<BR>
     * ����t���[���� condDecision() �� condCancel() �̏��������͂ǂ��炩������������A
     * ����D�揇�ʂ́AcondDecision() �̕�����ł��B<BR>
     * @return �u�L�����Z���i�U�镑���j�v�̏������� / false:�s����
     */
    virtual bool condCancel() = 0;
    /**
     * �J�[�\�����u���̃��j���[�A�C�e���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u���̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectNext() = 0;

    /**
     * �J�[�\�����u�O�̃��j���[�A�C�e���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u�O�̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectPrev() = 0;

    /**
     * �J�[�\�����u������̕ʂ̎��̃��j���[�A�C�e���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u������̕ʂ̎��̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectExNext() = 0;

    /**
     * �J�[�\�����u������̕ʂ̑O�̃��j���[�A�C�e���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u������̕ʂ̑O�̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectrExPrev() = 0;

    /**
     * �J�[�\�����u�L�����Z���̃��j���[�A�C�e���v�֔�ԏ������������� .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u�L�����Z���̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectCancel() = 0;

    /**
     * �u����i�U�镑���j�v���ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N�B
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * �����j���[�̑I�����ڂ����肳�ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �ŁAgetOnDecidedIndex() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA���莞�̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onDecision() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B
     * @param prm_pItem ���肳�ꂽ�̃A�C�e��
     * @param prm_item_index ���肳�ꂽ�̃A�C�e���̃C���f�b�N�X
     */
    virtual void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * �u�L�����Z���i�U�镑���j�v���ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N�B .
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * �����j���[�̑I�����ڂ��L�����Z�����ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �ŁAgetCancelIndex() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA�L�����Z�����̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onCancel() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B
     * @param prm_pItem
     * @param prm_item_index
     */
    virtual void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * �J�[�\�����ړ������ꍇ�ɌĂяo�����R�[���o�b�N�B .
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * �y�ߑ��z<BR>
     * onMoveCursor(int,int) �� onSelect(int,int) �̃R�[���o�b�N�^�C�~���O�̍��ɂ��āB<BR>
     * onSelect(int,int) �́AselectXxxxx �n �̃��\�b�h�����s���ɁA����Ȃ��Ăяo����܂��B<BR>
     * onMoveCursor(int,int) �́AselectXxxxx �n�̃��\�b�h���s�̍ہA�J�[�\�����ړ������ꍇ�̂݌Ăяo����܂��B<BR>
     * �Ăяo����鏇���́AonMoveCursor(int,int)  �� onSelect(int,int) �̏��ł��B<BR>
     * @param prm_from �ړ����̃A�C�e���̃C���f�b�N�X�i�����i�����́j�ꍇ�� -1�j
     * @param prm_to   �ړ���̃A�C�e���̃C���f�b�N�X
     */
    virtual void onMoveCursor(int prm_from, int prm_to) = 0;


    /**
     * �A�C�e�����I�����ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N�B .
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * �y�ߑ��z<BR>
     * onMoveCursor(int,int) �� onSelect(int,int) �̃R�[���o�b�N�^�C�~���O�̍��ɂ��āB<BR>
     * onSelect(int,int) �́AselectXxxxx �n�̃��\�b�h�����s���ɁA����Ȃ��Ăяo����܂��B<BR>
     * onMoveCursor(int,int) �́AselectXxxxx �n�̃��\�b�h���s�̍ہA�J�[�\�����ړ������ꍇ�̂݌Ăяo����܂��B<BR>
     * �Ăяo����鏇���́AonMoveCursor(int,int)  �� onSelect(int,int) �̏��ł��B<BR>
     * @param prm_from �I�����i����I�������O�j�̃A�C�e���̃C���f�b�N�X�i�����i�����́j�ꍇ�� -1�j
     * @param prm_to   �I���̃A�C�e���̃C���f�b�N�X
     */
    virtual void onSelect(int prm_from, int prm_to) = 0;

    /**
     * �J�[�\���� _lstItems �̃A�N�e�B�u�v�f�ֈړ������� .
     * �J�[�\���ړ����̌��ʉ���炷�ꍇ���́A�I�[�o�[���C�h���čĒ�`���Ă��������B<BR>
     * �A���A���̏������ɏ�� moveCursor() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     * @param prm_smooth �X���[�Y�ړ����邩�ۂ�
     */
    virtual void moveCursor(bool prm_smooth = true);

    /**
     * ���j���[��\���J�n���� .
     * �{�I�u�W�F�N�g�𐶐��A�^�X�N�ɒǉ���A�\�����������^�C�~���O�Ŏ��s���Ă��������B<BR>
     */
    virtual void rise();

    /**
     * ���j���[�\���J�n���̃R�[���o�b�N .
     * rise() ���s������A�P�񂾂��R�[���o�b�N����܂��B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h���Ă��������B<BR>
     */
    virtual void onRise();

    /**
     * ���j���[�\�����g�����W�V�������� .
     * rise() ���s �` �t�F�[�h�C�������܂ł̊ԃR�[�����ꑱ���܂��B
     * �A���t�@�����Z���t�F�[�h�C�����ʂ��s���A�A���t�@��1.0�ɂȂ�ΏI���B
     * �Ƃ����g�����W�V���������������ς݂ł��B<BR>
     * �g�����W�V������Ǝ��ɍs�������ꍇ�̓I�[�o�[���C�h���A�g�����W�V������������<BR>
     * _with_rising = false;<BR>
     * �����s���Ă��������B<BR>
     */
    virtual void processRising();

    /**
     * ��ԃt���O�X�V��ǉ��̂��߃I�[�o�[���C�h .
     * ������ T::nextFrame(); ���R�[�����Ă��܂��B
     */
    virtual void nextFrame() override;

    /**
     * ���j���[�̐U�镑�� .
     * �J�[�\���̈ړ��y�сA�A�C�e���ƃJ�[�\�������j���[�̕�̍��W�ɒǏ]������
     * �����������ς݂ł��B<BR>
     * ���j���[�̐U�镑����ǉ�����ꍇ�́A�I�[�o�[���C�h���āA
     * �������ɏ�� processBehavior() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     */
    virtual void processBehavior() override;

    /**
     * ���j���[����ďI�������� .
     */
    virtual void sink();

    /**
     * rise()�����s���ꂽ���ォ�ۂ���Ԃ� .
     * @return true:�����x rise()�� ���s���ꂽ����ł���/false:�����ł͂Ȃ�
     */
    virtual bool isJustRisen() {
        return _is_just_risen;
    }

    /**
     * sink() �����s���ꂽ���ォ�ۂ���Ԃ� .
     * @return true:�����x sink() �����s���ꂽ����ł���/false:�����ł͂Ȃ�
     */
    virtual bool isJustSunk() {
        return _is_just_sunk;
    }

    /**
     * �u����i�U�镑���j�v���s��ꂽ���ォ�ۂ���Ԃ� .
     * @return rue:�����x �u����i�U�镑���j�v �����s���ꂽ����ł���/false:�����ł͂Ȃ�
     */
    virtual bool isJustDecided() {
        if (_is_just_decided && _can_controll) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * �u�L�����Z���i�U�镑���j�v���s��ꂽ���ォ�ۂ���Ԃ� .
     * @return rue:�����x �u�L�����Z���i�U�镑���j�v �����s���ꂽ����ł���/false:�����ł͂Ȃ�
     */
    virtual bool isJustCancelled() {
        if (_is_just_cancelled && _can_controll) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * ���j���[�������J�n���̃R�[���o�b�N .
     * sink() ���s������A�P�񂾂��R�[���o�b�N����܂��B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h���Ă��������B<BR>
     */
    virtual void onSink();

    /**
     * ���j���[�����̃g�����W�V�������� .
     * sink() ���s �` �t�F�[�h�A�E�g�����܂ł̊ԃR�[�����ꑱ���܂��B
     * �A���t�@�����Z���t�F�[�h�A�E�g���ʂ��s���A�A���t�@��1.0�ɂȂ�ΏI��
     * �Ƃ����g�����W�V���������������ς݂ł��B<BR>
     * �g�����W�V������Ǝ��ɍs�������ꍇ�̓I�[�o�[���C�h���A�g�����W�V������������<BR>
     * _with_sinking = false;<BR>
     * T::inactivateTreeImmed();<BR>
     * �����s���Ă��������B<BR>
     */
    virtual void processSinking();

    /**
     * �T�u���j���[��ǉ�����B
     * @param prm_pSubMenu �T�u���j���[
     */
    virtual void addSubMenu(MenuActor<T>* prm_pSubMenu);

    /**
     * �e���j���[��Ԃ� .
     * @return �e���j���[
     */
    virtual MenuActor<T>* getParentMenu();

    /**
     * �T�u���j���[���擾 .
     * ���O�� addSubMenu() �ŃT�u���j���[��ݒ肷��K�v������܂��B<BR>
     * @param prm_index �T�u���j���[�̃C���f�b�N�X
     * @return
     */
    virtual MenuActor<T>* getSubMenu(int prm_index);

    /**
     * ���݃A�N�e�B�u�ȃT�u���j���[���擾 .
     * �T�u���j���[�����o�^�̏ꍇ�B�����͓o�^���Ă��Ă��A�A�N�e�B�u�ł͂Ȃ��ꍇ�� nullptr ��Ԃ��B
     * @return �A�N�e�B�u�ȃT�u���j���[/nullptr
     */
    virtual MenuActor<T>* getRisingSubMenu();

    /**
     * �T�u���j���[���A�N�e�B�u�ɂ��ĕ\������ .
     * ���O�� addSubMenu() �ŃT�u���j���[��ݒ肷��K�v������܂��B<BR>
     * �܂��A�{���\�b�h�ɂ�茻�݃A�N�e�B�u�ȃT�u���j���[(getRisingSubMenu())�́A
     * �����C���f�b�N�X�̃��j���[�ɕύX����܂��B
     * �T�u���j���[��\������ƁA�T�u���j���[�����(sinkSubMenu()) �܂ŁA
     * �Ăяo�������j���[�͑���s�\�ɂȂ�܂��B
     * @param prm_index �A�N�e�B�u�ɂ���T�u���j���[�̃C���f�b�N�X
     */
    virtual void riseSubMenu(int prm_index);

    /**
     * ���݃A�N�e�B�u�ȃT�u���j���[����ďI�������� .
     * ���O�� addSubMenu() �ŃT�u���j���[��ݒ肷��K�v������܂��B<BR>
     */
    virtual void sinkSubMenu();

    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model, nullptr),_lstItems(3) { //�S�A�C�e���}���R�ǉ��F�u���̑����v�u���̑��O�v�u�L�����Z���v�̂R��
    T::_class_name = "MenuActor";
    _pCursor = nullptr;
    _X_cursor_adjust = 0;
    _Y_cursor_adjust = 0;
    _Z_cursor_adjust = 0;
    _fade_frames = 0;
    _velo_alpha_fade = 1.0;
    _cursor_move_frames = 10;
    _cursor_move_p1 = 0.2;
    _cursor_move_p2 = 0.7;
    _X_cursor_target_prev = T::_X;
    _Y_cursor_target_prev = T::_Y;
    _Z_cursor_target_prev = T::_Z;
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _is_just_decided = false;
    _is_just_cancelled = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = false;
    _will_be_just_decided_next_frame = false;
    _will_be_just_cancelled_next_frame = false;
    _can_controll = false;
    _will_be_able_to_controll = false;
    for (int i = 0; i < 10; i++) {
        _lstMvCursorHistory.addLast(new int(-1), true);
        _lstMvSelectHistory.addLast(new int(-1), true);
    }
    T::inactivateImmed(); //���j���[�Ȃ̂ŁA������Ԃ͔񊈓���Ԃ��f�t�H���g�Ƃ���
}

template<class T>
void MenuActor<T>::nextFrame() {
    T::nextFrame();
    _is_just_risen = false;
    if (_will_be_rising_next_frame) {
        _with_rising = true;
        _is_just_risen = true;
        _will_be_rising_next_frame = false;
        onRise();
    }

    _is_just_sunk = false;
    if (_will_be_sinking_next_frame) {
        _with_sinking = true;
        _is_just_sunk = true;
        _will_be_sinking_next_frame = false;
        onSink();
    }


    if (_will_be_just_decided_next_frame && _can_controll) {
        _is_just_decided = true;
        _will_be_just_decided_next_frame = false;
        onDecision(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
    } else {
        _is_just_decided = false;
        _will_be_just_decided_next_frame = false;
    }

    if (_will_be_just_cancelled_next_frame && _can_controll) {
        _is_just_cancelled = true;
        _will_be_just_cancelled_next_frame = false;
        onCancel(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
    } else {
        _is_just_cancelled = false;
        _will_be_just_cancelled_next_frame = false;
    }

    _can_controll = _will_be_able_to_controll;

}

template<class T>
void MenuActor<T>::addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                           coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pItem->_X_local = prm_X_local;
    prm_pItem->_Y_local = prm_Y_local;
    prm_pItem->_Z_local = prm_Z_local;
    prm_pItem->_alpha = T::_alpha; //�������������L������B
    prm_pItem->inactivateImmed();
    _lstItems.addLast(prm_pItem, false);
    T::addSubLast(prm_pItem);
}

template<class T>
void MenuActor<T>::addDisp(GgafDxCore::GgafDxDrawableActor* prm_pDisp,
                           coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pDisp->_X_local = prm_X_local;
    prm_pDisp->_Y_local = prm_Y_local;
    prm_pDisp->_Z_local = prm_Z_local;
    prm_pDisp->_alpha = T::_alpha; //�������������L������B
    prm_pDisp->inactivateImmed();
    _lstDispActors.addLast(prm_pDisp, false);
    T::addSubLast(prm_pDisp);
}

template<class T>
void MenuActor<T>::relateItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relateItemExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3 ) {
    relateItemExNext(prm_index_of_item1, prm_index_of_item2);
    relateItemExNext(prm_index_of_item2, prm_index_of_item3);
}

template<class T>
void MenuActor<T>::relateItemExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4 ) {
    relateItemExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3);
    relateItemExNext(prm_index_of_item3, prm_index_of_item4);
}

template<class T>
void MenuActor<T>::relateItemExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4,
                                    int prm_index_of_item5 ) {
    relateItemExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3, prm_index_of_item4);
    relateItemExNext(prm_index_of_item4, prm_index_of_item5);
}


//template<class T>
//void MenuActor<T>::relateItemExNext(int prm_index_of_fromitem, ...) {
//    va_list pArg;
//    va_start(pArg, prm_index_of_fromitem);         //�ϒ���������J�n
//        va_arg( argptr, int );
//
//
//
//    va_end(pArg);      //�ϒ���������I��
//}


template<class T>
void MenuActor<T>::relateItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relateAllItemCancel(int prm_index_of_cancel_item) {
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pCancelElem =
            _lstItems.getElemFromFirst(prm_index_of_cancel_item);
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem =
            _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pElem->connect(ITEM_RELATION_TO_CANCEL, pCancelElem);
        pElem = pElem->_pNext;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::selectItem(int prm_index) {
    int n = getSelectedIndex();
#ifdef MY_DEBUG
    if (n == -1) {
        throwGgafCriticalException("MenuActor<T>::selectItem() ���j���[�A�C�e�������o�^�ł� name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
    }
#endif
    if (n == prm_index) {
        //���ɑI�����Ă���B
        *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
        onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
        return _lstItems.getCurrent();
    } else {
#ifdef MY_DEBUG
        if (_lstItems.length() <= prm_index) {
            throwGgafCriticalException("MenuActor<T>::selectItem() ���j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
        }
#endif
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.current(prm_index);
        if (T::getActivePartFrame() > 1) {
            moveCursor(true);  //�X���[�Y�ړ��L��
        } else {
            moveCursor(false); //�X���[�Y�ړ�����
        }
        *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
        onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
        return pTargetItem;
    }
}

template<class T>
int MenuActor<T>::selectItem(GgafDxCore::GgafDxDrawableActor* prm_item) {
    int index = _lstItems.indexOf(prm_item);
    if (index == -1) {
        throwGgafCriticalException("MenuActor<T>::selectItem() ���̑O�Ƀ��j���[�A�C�e�������o�^�ł� name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item="<<prm_item->getName());
    }
    selectItem(index);
    return index;
}

template<class T>
void MenuActor<T>::setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor,
                             coord prm_X_cursor_adjust,
                             coord prm_Y_cursor_adjust,
                             coord prm_Z_cursor_adjust,
                             int prm_cursor_move_frames,
                             float prm_cursor_move_p1,
                             float prm_cursor_move_p2) {
    _pCursor = prm_pCursor;
    if (_pCursor) {
        _pCursor->_alpha = T::_alpha;
        _pCursor->inactivateImmed();
    }
    T::addSubLast(_pCursor);
    _X_cursor_adjust = prm_X_cursor_adjust;
    _Y_cursor_adjust = prm_Y_cursor_adjust;
    _Z_cursor_adjust = prm_Z_cursor_adjust;
    _cursor_move_frames = prm_cursor_move_frames;
    _cursor_move_p1 = prm_cursor_move_p1;
    _cursor_move_p2 = prm_cursor_move_p2;
    selectItem(0);
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getCursor() {
    return _pCursor;
}

template<class T>
int MenuActor<T>::getSelectedIndex() {
    return _lstItems.getCurrentIndex();
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
int MenuActor<T>::getMvCursorHistoryIndex(int prm_n) {
    return (*(_lstMvCursorHistory.getPrev(prm_n)));
}

template<class T>
int MenuActor<T>::getOnDecidedIndex() {
    if (_is_just_decided) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}
template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getOnDecidedItem() {
    if (_is_just_decided) {
        return _lstItems.getCurrent();
    } else {
        return nullptr;
    }
}

template<class T>
int MenuActor<T>::getOnCancelledIndex() {
    if (_is_just_cancelled) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getOnCancelledItem() {
    if (_is_just_cancelled) {
        return _lstItems.getCurrent();
    } else {
        return nullptr;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getItem(int prm_index) {
    return _lstItems.getFromFirst(prm_index);
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getDisp(int prm_index) {
    return _lstDispActors.getFromFirst(prm_index);
}

template<class T>
void MenuActor<T>::selectNext() {
    if (_pCursor) {
        _pCursor->locateWith(_lstItems.getCurrent());
    }
    _lstItems.next();
    moveCursor();
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::selectPrev() {
    if (_pCursor) {
        _pCursor->locateWith(_lstItems.getCurrent());
    }
    _lstItems.prev();
    moveCursor();
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::selectExNext() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
        moveCursor();
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::selectExPrev() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
        moveCursor();
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::selectCancel() {
    if (_lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        if (_pCursor) {
            _pCursor->locateWith(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_TO_CANCEL);
        moveCursor();
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::moveCursor(bool prm_smooth) {
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (prm_smooth) {
            _pCursor->_pKurokoA->setMvAngTwd(
                                    pTargetItem->_X + _X_cursor_adjust,
                                    pTargetItem->_Y + _Y_cursor_adjust,
                                    pTargetItem->_Z + _Z_cursor_adjust
                                );
            _pCursor->_pKurokoA->setMvVelo(0);
            _pCursor->_pKurokoA->setMvAcce(0);
            _pCursor->_pKurokoA->execSmoothMvVeloSequence(
                                     0,
                                     UTIL::getDistance(
                                             _pCursor->_X,
                                             _pCursor->_Y,
                                             _pCursor->_Z,
                                             pTargetItem->_X + _X_cursor_adjust,
                                             pTargetItem->_Y + _Y_cursor_adjust,
                                             pTargetItem->_Z + _Z_cursor_adjust),
                                     _cursor_move_frames,
                                     _cursor_move_p1, _cursor_move_p2
                                 );
            _X_cursor_target_prev = pTargetItem->_X;
            _Y_cursor_target_prev = pTargetItem->_Y;
            _Z_cursor_target_prev = pTargetItem->_Z;
        } else {
            _pCursor->_pKurokoA->stopSmoothMvVeloSequence();
            _pCursor->_pKurokoA->setMvVelo(0);
            _pCursor->_pKurokoA->setMvAcce(0);
            _pCursor->_X = pTargetItem->_X + _X_cursor_adjust;
            _pCursor->_Y = pTargetItem->_Y + _Y_cursor_adjust;
            _pCursor->_Z = pTargetItem->_Z + _Z_cursor_adjust;
        }
        *(_lstMvCursorHistory.next()) = _lstItems.getCurrentIndex();
        onMoveCursor(*(_lstMvCursorHistory.getPrev()), *(_lstMvCursorHistory.getCurrent())); //�R�[���o�b�N
    }
}

template<class T>
void MenuActor<T>::rise() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = true;
    _will_be_sinking_next_frame = false;
    enableControll();

    T::setAlpha(0.0);
    T::activate();
    //���j���[�A�C�e�������z�u
    GgafDxCore::GgafDxDrawableActor* p;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        pElem = pElem->_pNext;
    }
    //�\���A�C�e�������z�u
    pElem = _lstDispActors.getElemFirst();
    for (int i = 0; i < _lstDispActors.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        pElem = pElem->_pNext;
    }
    if (_pCursor) {
        _pCursor->activate();
    }
}

template<class T>
void MenuActor<T>::onRise() {
}

template<class T>
void MenuActor<T>::processRising() {
    T::addAlpha(_velo_alpha_fade);
    if (T::getAlpha() >= 1.0) {
        T::setAlpha(1.0);
        _with_rising = false;
    }
}

template<class T>
void MenuActor<T>::processBehavior() {
    if (_with_sinking) {
        processSinking();
    }
    if (_with_rising) {
        processRising();
    }
    if (_can_controll && T::getActivePartFrame() > 2) {
        if (condDecision()) {
            _will_be_just_decided_next_frame = true;
        } else if (condCancel()) {
            _will_be_just_cancelled_next_frame = true;
        } else if (condSelectNext()) {
            selectNext();
        } else if (condSelectPrev()) {
            selectPrev();
        } else if (condSelectExNext()) {
            selectExNext();
        } else if (condSelectrExPrev()) {
            selectExPrev();
        } else if (condSelectCancel()) {
            selectCancel();
        }
    }
    if (_pCursor) {
        _pCursor->_pKurokoA->behave();
    }

    //���j���[�A�C�e�������j���[�ɒǏ]
    GgafDxCore::GgafDxDrawableActor* p;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        if (_with_sinking || _with_rising) {
            p->setAlpha(T::getAlpha());
        }
        pElem = pElem->_pNext;
    }
    //�\���A�C�e�������j���[�ɒǏ]
    pElem = _lstDispActors.getElemFirst();
    for (int i = 0; i < _lstDispActors.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        if (_with_sinking || _with_rising) {
            p->setAlpha(T::getAlpha());
        }
        pElem = pElem->_pNext;
    }

    //�J�[�\�������j���[�A�C�e���ɒǏ]
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursor->_pKurokoA->isRunnigSmoothMvVeloSequence()) {
            _pCursor->_X += (pTargetItem->_X - _X_cursor_target_prev);
            _pCursor->_Y += (pTargetItem->_Y - _Y_cursor_target_prev);
            _pCursor->_Z += (pTargetItem->_Z - _Z_cursor_target_prev);
            _X_cursor_target_prev = pTargetItem->_X;
            _Y_cursor_target_prev = pTargetItem->_Y;
            _Z_cursor_target_prev = pTargetItem->_Z;
        } else {
            _pCursor->locate(pTargetItem->_X + _X_cursor_adjust,
                             pTargetItem->_Y + _Y_cursor_adjust,
                             pTargetItem->_Z + _Z_cursor_adjust );
        }
        _pCursor->setAlpha(T::getAlpha());
    }

    //�T�u���j���[��rise() sink() ��
    for (int i = 0; i < _lstSubMenu.length(); i++) {
        MenuActor<T>* pSubMenu = _lstSubMenu.getFromFirst(i);
        if (pSubMenu->isJustRisen()) {
            disableControll(); //�T�u���j���[�������オ�����̂ŁA���g�͑���s��
            _can_controll = false; //����
        }
        if (pSubMenu->isJustSunk()) {
            if (_with_sinking || _is_just_sunk || _will_be_sinking_next_frame) {
                disableControll(); //���g�������ɕ��Ă���ꍇ
                _can_controll = false; //����
            } else {
                enableControll(); //�T�u���j���[���������̂ŁA���g�̑��앜�A
            }
        }
    }
}

template<class T>
void MenuActor<T>::sink() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = true;
    disableControll();
    _can_controll = false; //����
}

template<class T>
void MenuActor<T>::onSink() {
}

template<class T>
void MenuActor<T>::processSinking() {
    T::addAlpha(-_velo_alpha_fade);
    if (T::getAlpha() <= 0.0) {
        T::setAlpha(0.0);
        _with_sinking = false;
        T::inactivateTree();
    }
}

template<class T>
void MenuActor<T>::addSubMenu(MenuActor<T>* prm_pSubMenu) {
    _lstSubMenu.addLast(prm_pSubMenu, false);
    T::addSubLast(prm_pSubMenu); //�T�u�ɒǉ�
}

template<class T>
MenuActor<T>* MenuActor<T>::getParentMenu() {
    GgafCore::GgafActor* pActor = T::getParent(); //�T�u�ɒǉ�
#ifdef MY_DEBUG
    MenuActor<T>* pMenuActor = dynamic_cast<MenuActor<T>*>(pActor);
    if (pMenuActor == nullptr) {
        throwGgafCriticalException(" MenuActor<T>::getParentMenu �e�m�[�h�͓������j���[�ł͂���܂���ł����Bname="<<T::getName()<<" this="<<this);
    }
#endif
    return (MenuActor<T>*)pActor;
}

template<class T>
MenuActor<T>* MenuActor<T>::getSubMenu(int prm_index) {
#ifdef MY_DEBUG
    if (_lstSubMenu.length() < prm_index+1) {
        throwGgafCriticalException("MenuActor<T>::getSubMenu() �T�u���j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstSubMenu.length()="<<_lstSubMenu.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstSubMenu.getFromFirst(prm_index);
}

template<class T>
MenuActor<T>* MenuActor<T>::getRisingSubMenu() {
    MenuActor<T>* pSub = _lstSubMenu.getCurrent();
    if (pSub) {
        if (pSub->isActiveInTheTree()) {
            return pSub;
        }
    }
    return nullptr;
}


template<class T>
void MenuActor<T>::riseSubMenu(int prm_index) {
#ifdef MY_DEBUG
    if (_lstSubMenu.length() < prm_index+1) {
        throwGgafCriticalException("MenuActor<T>::riseSubMenu() �T�u���j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstSubMenu.length()="<<_lstSubMenu.length()<<" prm_index="<<prm_index);
    }
#endif
    _lstSubMenu.current(prm_index)->rise();
}

template<class T>
void MenuActor<T>::sinkSubMenu() {
    _lstSubMenu.getCurrent()->sink();
}

template<class T>
MenuActor<T>::~MenuActor() {
}

/** ���j���[�̕�̂� GgafLib::DefaultBoardActor �Ƃ��郁�j���[ */
typedef GgafLib::MenuActor<GgafLib::DefaultBoardActor> DefaultBoardMenu;
/** ���j���[�̕�̂� GgafLib::DefaultBoardSetActor �Ƃ��郁�j���[ */
typedef GgafLib::MenuActor<GgafLib::DefaultBoardSetActor> DefaultBoardSetMenu;
/** ���j���[�̕�̂� GgafLib::DefaultSpriteActor �Ƃ��郁�j���[ */
typedef GgafLib::MenuActor<GgafLib::DefaultSpriteActor> DefaultSpriteMenu;
/** ���j���[�̕�̂� GgafLib::DefaultSpriteSetActor �Ƃ��郁�j���[ */
typedef GgafLib::MenuActor<GgafLib::DefaultSpriteSetActor> DefaultSpriteSetMenu;
/** ���j���[�̕�̂� GgafLib::StringBoardActor �Ƃ��郁�j���[ */
typedef GgafLib::MenuActor<GgafLib::StringBoardActor> StringBoardMenu;
/** ���j���[�̕�̂� GgafLib::StringSpriteActor �Ƃ��郁�j���[ */
typedef GgafLib::MenuActor<GgafLib::StringSpriteActor> StringSpriteMenu;

}
#endif /*MENUACTOR_H_*/
