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
    bool _is_just_with_rising;
    /** �t�F�[�h�A�E�g���J�n�����u�Ԃ̃t���[������ true */
    bool _is_just_with_sinking;
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
    /** [r/w]���j���[�t�F�C�h�C���E�A�E�g���̃A���t�@���x */
    float _velo_alpha_fade;
    /** [r]�J�[�\�����A���j���[�A�C�e���Ԃ��ړ�����ۂɔ�₷�X�t���[���� */
    int _cursor_move_frames;
    /** [r]�J�[�\�����ړ����A�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊��� */
    float _cursor_move_p1;
    /** [r]�J�[�\�����ړ����A�A�C�e���Ԉړ������̍ō������猸�����J�n���銄�� */
    float _cursor_move_p2;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_model ���f�����ʖ�
     */
    MenuActor(const char* prm_name, const char* prm_model);

    /**
     * ���j���[�A�C�e����ǉ����� .
     * @param prm_pItem ���j���[�A�C�e��
     * @param prm_X_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_Y_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_Z_local ���j���[�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                         coord prm_X_local, coord prm_Y_local, coord prm_Z_local);
    /**
     * ���j���[�J�[�\���I�u�W�F�N�g��ݒ肷�� .
     * �y���Ӂz<BR>
     * �J�[�\���ړ��𐧌䂷�邽�߁AMenuActor<T>::processBehavior() ���ŁA<BR>
     * _pCursor->_pKurokoA->behave(); <BR>
     * �����s���Ă��܂��B���������āA�����̃J�[�\���N���X�ŁA<BR>
     * _pKurokoA->behave(); <BR>
     * �����s����K�v�͂���܂���B<BR>
     * @param prm_pCursor �J�[�\��
     */
    virtual void setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor);

    /**
     * ���j���[�̓�����ݒ肷��B
     * @param prm_menu_fade_frames ���j���[�̃t�F�[�h�C���i�ƃt�F�[�h�A�E�g�j�̃t���[����
     * @param prm_cursor_move_frames �J�[�\�����A�C�e���Ԉړ��ɔ�₷�t���[��(�f�t�H���g8�t���[��)
     * @param prm_cursor_move_p1 �J�[�\�����ړ����A�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊���(�f�t�H���g0.2)
     * @param prm_cursor_move_p2 �J�[�\�����ړ����A�A�C�e���Ԉړ������̍ō������猸�����J�n���銄��(�f�t�H���g0.7)
     */
    virtual void config(int prm_menu_fade_frames,
                        int prm_cursor_move_frames = 8,
                        float prm_cursor_move_p1 = 0.2,
                        float prm_cursor_move_p2 = 0.7);

    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(���g��From �� To) .
     * addItem(GgafDxCore::GgafDxDrawableActor*) �ɂ��A�ǉ����s�����ƂŁA�����I��<BR>
     * ���A�O�A�̐��`�I�[�_�[���\�z����Ă���B<BR>
     * ���̃��\�b�h�͂���Ƃ͕ʂɃA�C�e���Ԃ́u���v�A�u�O�v�A�̊֌W��ݒ肷��B<BR>
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
     * addItem(GgafDxCore::GgafDxDrawableActor*) �ɂ��A�ǉ����s�����ƂŁA�����I��<BR>
     * ���A�O�A�̐��`�I�[�_�[���\�z����Ă���B<BR>
     * ���̃��\�b�h�͂���Ƃ͕ʂɃA�C�e���Ԃ́u�O�v�A�u���v�A�̊֌W��ݒ肷��B<BR>
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
    virtual int getSelectedItemIndex();

    /**
     * ���݃J�[�\�����I�𒆂̃A�C�e���̃I�u�W�F�N�g���擾 .
     * @return �I�𒆂̃A�C�e���I�u�W�F�N�g
     */
    virtual GgafDxCore::GgafDxDrawableActor* getSelectedItem();

    /**
     * �J�[�\�����u���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������Ă��������B
     * @return true:�u���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorNext() = 0;

    /**
     * �J�[�\�����u�O�v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������Ă��������B
     * @return true:�u�O�v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorPrev() = 0;

    /**
     * �J�[�\�����u������̕ʂ̎��v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������Ă��������B
     * @return true:�u������̕ʂ̎��v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorExNext() = 0;


    /**
     * �J�[�\�����u������̕ʂ̑O�v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������Ă��������B
     * @return true:�u������̕ʂ̑O�v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorExPrev() = 0;

    /**
     * �J�[�\�����u�L�����Z���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������Ă��������B
     * @return true:�u�L�����Z���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condMoveCursorCancel() = 0;

    /**
     * �J�[�\���I�𒆂̃A�C�e���Ō���ł���Ƃ����������������� .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������Ă��������B
     * @return �u����v�̏������� / false:�s����
     */
    virtual bool condDecision() = 0;

    /**
     * �J�[�\���� _lstItems �̃A�N�e�B�u�v�f�ֈړ������� .
     * �J�[�\���ړ����̌��ʉ���炷�ꍇ���́A�I�[�o�[���C�h���čĒ�`���Ă��������B<BR>
     * �A���A�������ɏ�� moveCursor() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     */
    virtual void moveCursor();


    virtual void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) = 0;

    /**
     * ���j���[��\���J�n .
     * �{�I�u�W�F�N�g�𐶐��A�^�X�N�ɒǉ���A�\�����������^�C�~���O�Ŏ��s���Ă��������B<BR>
     */
    void rise();

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
     * ���j���[�̐U�镑�� .
     * �J�[�\���̈ړ��y�сA�A�C�e���ƃJ�[�\�������j���[�̕�̍��W�ɒǏ]������
     * �����������ς݂ł��B<BR>
     * ���j���[�̐U�镑����ǉ�����ꍇ�́A�I�[�o�[���C�h���āA<BR>
     * �������ɏ�� moveCursor() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     */
    virtual void processBehavior() override;

    /**
     * ���j���[�������J�n .
     * �{�I�u�W�F�N�g�𐶐��A�^�X�N�ɒǉ���A�\�����������^�C�~���O�Ŏ��s���Ă��������B<BR>
     */
    void sink();

    bool isJustSink() {
        return _is_just_with_sinking;
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
  T(prm_name, prm_model, NULL),_lstItems(3) { //�}���R��
    T::_class_name = "MenuActor";
    _pCursor = NULL;
    _velo_alpha_fade = 1.0;
    _cursor_move_frames = 10;
    _cursor_move_p1 = 0.2;
    _cursor_move_p2 = 0.7;
    _X_cursor_target_prev = T::_X;
    _Y_cursor_target_prev = T::_Y;
    _Z_cursor_target_prev = T::_Z;
    _with_rising = false;
    _with_sinking = false;
    _is_just_with_rising = false;
    _is_just_with_sinking = false;
    T::inactivateImmed();
}


template<class T>
void MenuActor<T>::addItem(GgafDxCore::GgafDxDrawableActor* prm_pItem,
                           coord prm_X_local, coord prm_Y_local, coord prm_Z_local) {
    prm_pItem->_X_local = prm_X_local;
    prm_pItem->_Y_local = prm_Y_local;
    prm_pItem->_Z_local = prm_Z_local;
    prm_pItem->_fAlpha = T::_fAlpha; //�������������L������B
    prm_pItem->inactivateImmed();

    _lstItems.addLast(prm_pItem);
    T::addSubLast(prm_pItem);
}

template<class T>
void MenuActor<T>::config(int prm_menu_fade_frames,
                          int prm_cursor_move_frames,
                          float prm_cursor_move_p1,
                          float prm_cursor_move_p2) {
    _velo_alpha_fade = 1.0 / prm_menu_fade_frames;
    _cursor_move_frames = prm_cursor_move_frames;
    _cursor_move_p1 = prm_cursor_move_p1;
    _cursor_move_p2 = prm_cursor_move_p2;
    if (_pCursor) {
        _pCursor->_fAlpha = T::_fAlpha;
        _pCursor->inactivateImmed();
    }
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
    GgafDxCore::GgafDxDrawableActor* pItem;
    for (int i = 0; i < _lstItems.length(); i++) {
        pElem->connect(ITEM_RELATION_TO_CANCEL, pCancelElem);
        pElem = pElem->_pNext;
    }
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::setSelectedItemIndex(int prm_index) {
    int n = getSelectedItemIndex();
    if (n == prm_index) {
        return _lstItems.getCurrent();
    } else {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.current(prm_index);
        moveCursor();
        return pTargetItem;
    }
}

template<class T>
void MenuActor<T>::setCursor(GgafDxCore::GgafDxDrawableActor* prm_pCursor) {
    _pCursor = prm_pCursor;
    T::addSubLast(_pCursor);
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getCursor() {
    return _pCursor;
}

template<class T>
int MenuActor<T>::getSelectedItemIndex() {
    return _lstItems.getCurrentIndex();
}

template<class T>
GgafDxCore::GgafDxDrawableActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
void MenuActor<T>::moveCursorNext() {
    if (_pCursor) {
        _pCursor->locateAs(_lstItems.getCurrent());
    }
    _lstItems.next();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorPrev() {
    if (_pCursor) {
        _pCursor->locateAs(_lstItems.getCurrent());
    }
    _lstItems.prev();
    moveCursor();
}

template<class T>
void MenuActor<T>::moveCursorExNext() {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        if (_pCursor) {
            _pCursor->locateAs(_lstItems.getCurrent());
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
            _pCursor->locateAs(_lstItems.getCurrent());
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
            _pCursor->locateAs(_lstItems.getCurrent());
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
        _pCursor->_pKurokoA->setMvAng(pTargetItem);
        _pCursor->_pKurokoA->setMvVelo(0);
        _pCursor->_pKurokoA->setMvAcce(0);
        _pCursor->_pKurokoA->execSmoothMvVeloSequence(0, GgafDxCore::GgafDxUtil::getDistance(_pCursor, pTargetItem),
                                                    _cursor_move_frames,
                                                    _cursor_move_p1, _cursor_move_p2);
        _X_cursor_target_prev = pTargetItem->_X;
        _Y_cursor_target_prev = pTargetItem->_Y;
        _Z_cursor_target_prev = pTargetItem->_Z;
    }
}

template<class T>
void MenuActor<T>::rise() {
    _with_rising = true;
    _is_just_with_rising = true;
    _with_sinking = false;
    _is_just_with_sinking = false;
    //���j���[�A�C�e�������z�u
    T::setAlpha(0.0);
    GgafDxCore::GgafDxDrawableActor* pItem;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pItem = pElem->_pValue;
        pItem->locate(T::_X + pItem->_X_local,
                      T::_Y + pItem->_Y_local,
                      T::_Z + pItem->_Z_local);
        pItem->setAlpha(T::getAlpha());
        pElem = pElem->_pNext;
    }
    T::activateTree();
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
        if (_is_just_with_sinking) {
            onSunk();
            _is_just_with_sinking = false;
        }
        processSinking();
    }
    if (_with_rising) {
        if (_is_just_with_rising) {
            onRisen();
            _is_just_with_rising = false;
        }
        processRising();
    }

    if (!_with_sinking) {
		if (condDecision()) {
            onDecision(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
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
    GgafDxCore::GgafDxDrawableActor* pItem;
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxDrawableActor>::Elem* pElem = _lstItems.getElemFirst();
    for (int i = 0; i < _lstItems.length(); i++) {
        pItem = pElem->_pValue;
        pItem->locate(T::_X + pItem->_X_local,
                      T::_Y + pItem->_Y_local,
                      T::_Z + pItem->_Z_local);
        pItem->setAlpha(T::getAlpha());
        pElem = pElem->_pNext;
    }

    //�J�[�\�������j���[�A�C�e���ɒǏ]
    if (_pCursor) {
        GgafDxCore::GgafDxDrawableActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursor->_pKurokoA->isMoveingSmooth()) {
            _pCursor->_X += (pTargetItem->_X - _X_cursor_target_prev);
            _pCursor->_Y += (pTargetItem->_Y - _Y_cursor_target_prev);
            _pCursor->_Z += (pTargetItem->_Z - _Z_cursor_target_prev);
            _X_cursor_target_prev = pTargetItem->_X;
            _Y_cursor_target_prev = pTargetItem->_Y;
            _Z_cursor_target_prev = pTargetItem->_Z;
        } else {
            _pCursor->locateAs(pTargetItem);
        }
        _pCursor->setAlpha(T::getAlpha());
    }
}

template<class T>
void MenuActor<T>::sink() {
    _with_rising = false;
    _is_just_with_rising = false;
    _with_sinking = true;
    _is_just_with_sinking = true;
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
        T::inactivateTreeImmed();
    }
}

template<class T>
MenuActor<T>::~MenuActor() {
}

/** ���j���[�̕�̂� GgafLib::DefaultBoardActor �Ƃ��郁�j���[ */
typedef GgafLib::MenuActor<GgafLib::DefaultBoardActor> DefaultBoardMenu;
/** ���j���[�̕�̂� GgafLib::DefaultBoardSetActor �Ƃ��郁�j���[ */
typedef GgafLib::MenuActor<GgafLib::DefaultBoardSetActor> DefaultBoardSetMenu;

}
#endif /*MENUACTOR_H_*/
