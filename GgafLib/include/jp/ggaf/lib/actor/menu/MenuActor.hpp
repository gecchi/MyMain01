#ifndef MENUACTOR_H_
#define MENUACTOR_H_
namespace GgafLib {

enum MenuItemWay {
    ITEM_RELATION_EX_NEXT = 0,
    ITEM_RELATION_EX_PREV,
    ITEM_RELATION_TO_CANCEL,
};

/**
 * ���j���[GUI�e���v���[�g .
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class MenuActor : public T {

protected:
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
    /** ���肵���u�Ԃ̃t���[������ true */
    bool _is_just_decided;

    bool _will_be_rising_next_frame;

    bool _will_be_sinking_next_frame;

    bool _will_be_just_decide_next_frame;

    bool _can_controll;

    bool _will_be_able_to_controll;
    /**
     * _lstItems �̃A�N�e�B�u�v�f�� next() �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void moveCursorNext();

    /**
     * _lstItems �̃A�N�e�B�u�v�f�� prev() �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void moveCursorPrev();

    /**
     * _lstItems �̃A�N�e�B�u�v�f�� gotoRelation(ITEM_RELATION_EX_NEXT) �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void moveCursorExNext();

    /**
     * _lstItems �̃A�N�e�B�u�v�f�� gotoRelation(ITEM_RELATION_EX_PREV) �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void moveCursorExPrev();

    /**
     *  _lstItems �̃A�N�e�B�u�v�f�� gotoRelation(ITEM_RELATION_TO_CANCEL) �ֈړ������A�J�[�\�����ړ� .
     */
    virtual void moveCursorCancel();

public:

    /** [r]���j���[�A�C�e���̃��X�g */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstItems;
    /** [r]���j���[�J�[�\�� */
    GgafDxCore::GgafDxDrawableActor* _pCursor;
    /** [r]���̑��\���A�C�e���̃��X�g */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor> _lstDispActors;
    /** [r/w]���j���[�t�F�C�h�C���E�A�E�g���̃A���t�@���x */
    float _velo_alpha_fade;
    /** [r]�J�[�\�����A���j���[�A�C�e���Ԃ��ړ�����ۂɔ�₷�X�t���[���� */
    int _cursor_move_frames;
    /** [r]�J�[�\�����ړ����A�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊��� */
    float _cursor_move_p1;
    /** [r]�J�[�\�����ړ����A�A�C�e���Ԉړ������̍ō������猸�����J�n���銄�� */
    float _cursor_move_p2;
    MenuActor<T>* _pActiveSubMenu;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_model ���f�����ʖ�
     */
    MenuActor(const char* prm_name, const char* prm_model);

    virtual void setFadeFrames(frame prm_menu_fade_frames) {
        _velo_alpha_fade = 1.0 / prm_menu_fade_frames;
    }

    /**
     * ���j���[�A�C�e��(�I���\)��ǉ����� .
     * �ǉ����ꂽ�A�C�e���̓��j���[�I�u�W�F�N�g(this)�̃T�u�ɓo�^����邽�߁A
     * ���j���[�I�u�W�F�N�g���^�X�N�c���[�ɓo�^�����Ȃ�� delete ����K�v�͂Ȃ��B
     * @param prm_pItem ���j���[�A�C�e��
     * @param prm_X_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_Z_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void addSelectItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                               coord prm_X_local, coord prm_Y_local, coord prm_Z_local);
    /**
     * ���j���[�A�C�e��(�I���\)��ǉ����� .
     * �ǉ����ꂽ�A�C�e���̓��j���[�I�u�W�F�N�g(this)�̃T�u�ɓo�^����邽�߁A
     * ���j���[�I�u�W�F�N�g���^�X�N�c���[�ɓo�^�����Ȃ�� delete ����K�v�͂Ȃ��B
     * @param prm_pItem ���j���[�A�C�e��
     * @param prm_X_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     */
    virtual void addSelectItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                               coord prm_X_local, coord prm_Y_local) {
        addSelectItem(prm_pItem, prm_X_local, prm_Y_local, T::_Z);
    }

    /**
     * �\���p�A�N�^�[(�I��s��)��ǉ����� .
     * @param prm_pItem �\���p�A�C�e��
     * @param prm_X_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_Z_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void addDispActor(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                              coord prm_X_local, coord prm_Y_local, coord prm_Z_local);
    /**
     * �\���p�A�N�^�[(�I��s��)��ǉ����� .
     * @param prm_pItem �\���p�A�C�e��
     * @param prm_X_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     */
    virtual void addDispActor(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                              coord prm_X_local, coord prm_Y_local) {
        addDispActor(prm_pItem, prm_X_local, prm_Y_local, T::_Z);
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
     * addSelectItem(GgafDxCore::GgafDxDrawableActor*) �ɂ��A�ǉ����s�����ƂŁA�����I��<BR>
     * ���A�O�A�̐��`�I�[�_�[���\�z����Ă���B<BR>
     * ���̃��\�b�h�͂���Ƃ͕ʂɃA�C�e���Ԃ́u���v�A�u�O�v�A�̊֌W��ǉ��ݒ肷��B<BR>
     * �Ⴆ�΁A�u���v�L�[�Łu���v�A�u���v�L�[�Łu�߂�v�Ƃ�������ɂ����ꍇ��
     * �u���v�u���v�̈ړ����ݒ肷��Ƃ������g�p���@��z��B<BR>
     * @param prm_index_of_fromitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X
     * @param prm_index_of_toitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X����
     *                            �u���v�ɑΉ�����A����̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void relationItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem);
//    virtual void relationItemExNext(int prm_index_of_fromitem, ...);

    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(From �� ���g��To) .
     * addSelectItem(GgafDxCore::GgafDxDrawableActor*) �ɂ��A�ǉ����s�����ƂŁA�����I��<BR>
     * ���A�O�A�̐��`�I�[�_�[���\�z����Ă���B<BR>
     * ���̃��\�b�h�͂���Ƃ͕ʂɃA�C�e���Ԃ́u�O�v�A�u���v�A�̊֌W��ǉ��ݒ肷��B<BR>
     * �Ⴆ�΁A�u���v�L�[�Łu���v�A�u���v�L�[�Łu�߂�v�Ƃ�������ɂ����ꍇ��
     * �u���v�u���v�̈ړ����ݒ肷��Ƃ������g�p���@��z��B<BR>
     * @param prm_index_of_fromitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X
     * @param prm_index_of_toitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X����
     *                            �u�O�v�ɑΉ�����A����̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void relationItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * �L�����Z���̃��j���[�A�C�e����ݒ肷��B
     * @param prm_index_of_cancel_item �L�����Z���A�C�e���̃C���f�b�N�X
     */
    virtual void relationItemCancel(int prm_index_of_cancel_item);

    /**
     * �J�[�\�����擾 .
     * @return
     */
    virtual GgafDxCore::GgafDxDrawableActor* getCursor();
    /**
     * �w��̃C���f�b�N�X�̃��j���[�A�C�e���ɁA�J�[�\�����ړ� .
     * ���Ɏw��̃C���f�b�N�X�I�𒆂̏ꍇ�̓J�[�\���͉����ړ������B
     * @param prm_index �^�[�Q�b�g�̃A�C�e���C���f�b�N�X
     * @return �A�C�e���C���f�b�N�X�̃A�C�e���I�u�W�F�N�g
     */
    virtual GgafDxCore::GgafDxDrawableActor* setSelectedItemIndex(int prm_index);

    /**
     * ���݃J�[�\�����I�𒆂̃A�C�e���̃C���f�b�N�X���擾 .
     * @return �I�𒆂̃A�C�e���I�u�W�F�N�g
     */
    virtual int getSelectedIndex();

    /**
     * �u����v���s��ꂽ���ɁA���肳�ꂽ�A�C�e���̃C���f�b�N�X��Ԃ��܂� .
     * @return ���肳�ꂽ���F���̃A�C�e���̃C���f�b�N�X(>=0)�^�������肳��Ă��Ȃ��ꍇ�F��� -1
     */
    virtual int getDecidedIndex();

    /**
     * ���݃J�[�\�����I�𒆂̃A�C�e���̃I�u�W�F�N�g���擾 .
     * @return �I�𒆂̃A�C�e���I�u�W�F�N�g
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItem();


    virtual MenuActor<T>* getSubMenu();
    /**
     * �J�[�\�����u���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorNext() = 0;

    /**
     * �J�[�\�����u�O�v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u�O�v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorPrev() = 0;

    /**
     * �J�[�\�����u������̕ʂ̎��v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u������̕ʂ̎��v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorExNext() = 0;

    /**
     * �J�[�\�����u������̕ʂ̑O�v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u������̕ʂ̑O�v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorExPrev() = 0;

    /**
     * �J�[�\�����u�L�����Z���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u�L�����Z���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorCancel() = 0;

    /**
     * �J�[�\���I�𒆂̃A�C�e���Ō���ł���Ƃ����������������� .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return �u����v�̏������� / false:�s����
     */
    virtual bool condDecision() = 0;

    /**
     * ���j���[�A�C�e����I�����u����v���ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N�B
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * @param prm_pItem ���肳�ꂽ�̃A�C�e��
     * @param prm_item_index ���肳�ꂽ�̃A�C�e���̃C���f�b�N�X
     */
    virtual void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * �J�[�\���� _lstItems �̃A�N�e�B�u�v�f�ֈړ������� .
     * �J�[�\���ړ����̌��ʉ���炷�ꍇ���́A�I�[�o�[���C�h���čĒ�`���Ă��������B<BR>
     * �A���A���̏������ɏ�� moveCursor() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     */
    virtual void moveCursor();

    /**
     * ���j���[��\���J�n .
     * �{�I�u�W�F�N�g�𐶐��A�^�X�N�ɒǉ���A�\�����������^�C�~���O�Ŏ��s���Ă��������B<BR>
     */
    virtual void rise();

    /**
     * �T�u���j���[��\������ .
     * �T�u���j���[��\������ƁA�T�u���j���[�����(sinkSub()) �܂ŁA
     * �Ăяo�������j���[�͑���s�\�ɂȂ�܂��B
     * @param prm_pSubMenu
     */
    virtual void riseSub(MenuActor<T>* prm_pSubMenu);

    /**
     * ���j���[��\���J�n���̏��� .
     * rise() ���s������A�P�񂾂��R�[���o�b�N����܂��B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h���Ă��������B<BR>
     */
    virtual void onRisen();

    /**
     * ���j���[�\���̃g�����W�V�������� .
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
     * ���j���[�������J�n .
     * �{�I�u�W�F�N�g�𐶐��A�^�X�N�ɒǉ���A�\�����������^�C�~���O�Ŏ��s���Ă��������B<BR>
     */
    virtual void sink();

    virtual void sinkSub();
    /**
     * rise()�����s���ꂽ���ォ�ۂ� .
     * @return
     */
    virtual bool isJustRise() {
        return _is_just_risen;
    }

    /**
     * sink()�����s���ꂽ���ォ�ۂ� .
     * @return
     */
    virtual bool isJustSink() {
        return _is_just_sunk;
    }

    virtual bool isJustDecided() {
        return _is_just_decided;
    }

    /**
     * ���j���[�������J�n���̏��� .
     * sink() ���s������A�P�񂾂��R�[���o�b�N����܂��B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h���Ă��������B<BR>
     */
    virtual void onSunk();

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


    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model, NULL),_lstItems(3) { //�S�A�C�e���}���R�ǉ��F�u���̑����v�u���̑��O�v�u�L�����Z���v�̂R��
    T::_class_name = "MenuActor";
    _pCursor = NULL;
    _X_cursor_adjust = 0;
    _Y_cursor_adjust = 0;
    _Z_cursor_adjust = 0;
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
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = false;
    _will_be_just_decide_next_frame = false;
    _can_controll = false;
    _will_be_able_to_controll = false;
    _pActiveSubMenu = NULL;
    T::inactivateImmed();
}
template<class T>
void MenuActor<T>::riseSub(MenuActor<T>* prm_pSubMenu) {
    _pActiveSubMenu = prm_pSubMenu;
    _pActiveSubMenu->rise();
    _will_be_able_to_controll = false;
}
template<class T>
void MenuActor<T>::sinkSub() {
    _pActiveSubMenu->sink();
    _pActiveSubMenu = NULL;
    _will_be_able_to_controll = true;
}

template<class T>
void MenuActor<T>::nextFrame() {
    T::nextFrame();
    _is_just_risen = false;
    if (_will_be_rising_next_frame) {
        _with_rising = true;
        _is_just_risen = true;
        onRisen();
        _will_be_rising_next_frame = false;
    }

    _is_just_sunk = false;
    if (_will_be_sinking_next_frame) {
        _with_sinking = true;
        _is_just_sunk = true;
        onSunk();
        _will_be_sinking_next_frame = false;
    }

    _is_just_decided = false;
    if (_will_be_just_decide_next_frame) {
        onDecision(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
        _is_just_decided = true;
        _will_be_just_decide_next_frame = false;
    }
    _can_controll = _will_be_able_to_controll;
}

template<class T>
void MenuActor<T>::addSelectItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
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
void MenuActor<T>::addDispActor(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                                coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pItem->_X_local = prm_X_local;
    prm_pItem->_Y_local = prm_Y_local;
    prm_pItem->_Z_local = prm_Z_local;
    prm_pItem->_alpha = T::_alpha; //�������������L������B
    prm_pItem->inactivateImmed();
    _lstDispActors.addLast(prm_pItem);
    T::addSubLast(prm_pItem);
}

template<class T>
void MenuActor<T>::relationItemExNext(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

//template<class T>
//void MenuActor<T>::relationItemExNext(int prm_index_of_fromitem, ...) {
//    va_list pArg;
//    va_start(pArg, prm_index_of_fromitem);         //�ϒ���������J�n
//        va_arg( argptr, int );
//
//
//
//    va_end(pArg);      //�ϒ���������I��
//}


template<class T>
void MenuActor<T>::relationItemExPrev(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relationItemCancel(int prm_index_of_cancel_item) {
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
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::setSelectedItemIndex(int prm_index) {
    int n = getSelectedIndex();
    if (n == prm_index) {
        return _lstItems.getCurrent();
    } else {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.current(prm_index);
        moveCursor();
        return pTargetItem;
    }
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
int MenuActor<T>::getDecidedIndex() {
    if (_is_just_decided) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
MenuActor<T>* MenuActor<T>::getSubMenu() {
    return _pActiveSubMenu;
}

template<class T>
void MenuActor<T>::moveCursorNext() {
    if (_pCursor) {
        _pCursor->locatedBy(_lstItems.getCurrent());
    }
    _lstItems.next();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorPrev() {
    if (_pCursor) {
        _pCursor->locatedBy(_lstItems.getCurrent());
    }
    _lstItems.prev();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorExNext() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        if (_pCursor) {
            _pCursor->locatedBy(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursorExPrev() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        if (_pCursor) {
            _pCursor->locatedBy(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursorCancel() {
    if (_lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        if (_pCursor) {
            _pCursor->locatedBy(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_TO_CANCEL);
        moveCursor();
    } else {

    }
}

template<class T>
void MenuActor<T>::moveCursor() {
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        _pCursor->_pKurokoA->setMvAng(
                                pTargetItem->_X + _X_cursor_adjust,
                                pTargetItem->_Y + _Y_cursor_adjust,
                                pTargetItem->_Z + _Z_cursor_adjust
                            );
        _pCursor->_pKurokoA->setMvVelo(0);
        _pCursor->_pKurokoA->setMvAcce(0);
        _pCursor->_pKurokoA->execSmoothMvSequence(
                                 0,
                                 GgafDxCore::GgafDxUtil::getDistance(
                                         _pCursor->_X,
                                         _pCursor->_Y,
                                         _pCursor->_Z,
                                         pTargetItem->_X + _X_cursor_adjust,
                                         pTargetItem->_Y + _Y_cursor_adjust,
                                         pTargetItem->_Z + _Z_cursor_adjust),
                                 _cursor_move_frames,
                                 _cursor_move_p1, _cursor_move_p2);

        _X_cursor_target_prev = pTargetItem->_X;
        _Y_cursor_target_prev = pTargetItem->_Y;
        _Z_cursor_target_prev = pTargetItem->_Z;
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
    _will_be_able_to_controll = true;

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
void MenuActor<T>::onRisen() {
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
            _will_be_just_decide_next_frame = true;
        } else if (condMoveCursorNext()) {
            moveCursorNext();
        } else if (condMoveCursorPrev()) {
            moveCursorPrev();
        } else if (condMoveCursorExNext()) {
            moveCursorExNext();
        } else if (condMoveCursorExPrev()) {
            moveCursorExPrev();
        } else if (condMoveCursorCancel()) {
            moveCursorCancel();
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
        p->setAlpha(T::getAlpha());
        pElem = pElem->_pNext;
    }
    //�\���A�C�e�������j���[�ɒǏ]
    pElem = _lstDispActors.getElemFirst();
    for (int i = 0; i < _lstDispActors.length(); i++) {
        p = pElem->_pValue;
        p->locate(T::_X + p->_X_local,
                  T::_Y + p->_Y_local,
                  T::_Z + p->_Z_local);
        p->setAlpha(T::getAlpha());
        pElem = pElem->_pNext;
    }

    //�J�[�\�������j���[�A�C�e���ɒǏ]
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursor->_pKurokoA->isRunnigSmoothMvSequence()) {
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
}

template<class T>
void MenuActor<T>::sink() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = true;
    _will_be_able_to_controll = false;
}

template<class T>
void MenuActor<T>::onSunk() {
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
