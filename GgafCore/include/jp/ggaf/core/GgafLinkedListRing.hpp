#ifndef GGAFLINKEDLISTRING_H_
#define GGAFLINKEDLISTRING_H_
namespace GgafCore {

/**
 * �v�f�i����^�C���X�^���X�ւ̃|�C���^�j�̊�o�����A�����X�g���\�z����e���v���[�g�ł��B.
 * <B>�y����z</B><BR>
 * �A�����X�g�̐擪�Ɩ������q�����Ă���Ƃ������ƂŁA�w��x�ƕ\�����Ă��܂��B<BR>
 *
 * �Ⴆ�΁A���̂悤�ȃR�[�h��������
 * <pre><code>
 * Object* A = new Object();
 * Object* B = new Object();
 * Object* C = new Object();
 * Object* D = new Object();
 * Object* E = new Object();
 * GgafLinkedListRing<Object> ring_list = GgafLinkedListRing<Object>();
 * ring_list.addLast(A);
 * ring_list.addLast(B);
 * ring_list.addLast(C);
 * ring_list.addLast(D);
 * ring_list.addLast(E);
 * </code></pre>
 *
 * �T�̗v�f�ŉ��}�̂悤�ȍ\�����̂鎖���o���܂��B<BR>
 * <pre>
 * --------------------------------
 * (E)��A!��B��C��D��E��(A!)
 * --------------------------------
 * </pre>
 * �e���v���[�g�����͓����ێ�����|�C���^�̌^���w�肵�܂��B<BR>
 * �܂�A�uGgafLinkedListRing<Object*>();�v�ł͂Ȃ��uGgafLinkedListRing<Object>();�v�Ƃ��邱�ƂƂ��܂��B<BR>
 * �}�́w�́x�́A�v�f�i���m�ɂ͗v�f��ێ�������ꕨ�j���m�����݂��|�C���^���w�������Ă��鎖�������Ă��܂��B<BR>
 * "!" �̓J�����g�v�f(�J�[�\�����w���Ă���悤�Ȃ���)�ŁA�{�e���v���[�g���\�b�h�ɂ��@�\�̊�ƂȂ�v�f�ł��B<BR>
 * ���[�́u(E)�v�Ɓu(A!)�v�Ƃ����\�L�́A�A�����X�g�̐擪�Ɩ������A���݂��A�����Ă��鎖�������Ă��܂��B<BR>
 * ��ɂȂ��Ă��邽�ߏI�[�������A�i���� next ������ prev ���\�ł��B<BR>
 * �I�[�������ł����A�����t���O�ɂ���Đ擪�v�f�A�����v�f�͊Ǘ�����Ă��܂��B<BR>
 * ��}�ł́AA ��擪�v�f�AE �𖖔��v�f�A�Ƃ��ē����Ǘ�����Ă���A�ʏ�̃��X�g�̂悤�Ȏg�������\�ł��B<BR>
 * [����]<BR>
 * �{�N���X�̐����ŁA�u�v�f�v�Ƃ����\���́A���̓C���i�[�N���X�� Elem�I�u�W�F�N�g�ւ̃|�C���^�̎����w���A<BR>
 * �u�v�f�̒l�v�Ƃ����\���͊e�u�v�f�v�� _pValue ���w���܂��B<BR>
 * �u�v�f�̒l�v�̌^�� T* �ł��B��̗�ł� Object* �^���w���܂��BObject �̒l���̂ł͂���܂���B
 * <BR>
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
template<class T>  //T:�Ǘ�����v�f�̃|�C���^�̌^
class GgafLinkedListRing : public GgafObject {

public:

    /**
     * ��p�̗v�f�l���b�v�N���X .
     * ���ۂ̗v�f�l�����b�s���O���A�O��|�C���^��ێ�
     */
    class Elem {
    public:
        /** ���ۂ̗v�f�̒l */
        T* _pValue;
        /** ���v�f */
        Elem* _pNext;
        /** �O�v�f */
        Elem* _pPrev;
        /** �擪�v�f�t���O (���v�f���擪�v�f�̏ꍇ true)*/
        bool _is_first_flg;
        /** �����v�f�t���O (���v�f�������v�f�̏ꍇ true)*/
        bool _is_last_flg;
        /** delete����_pValue��delete���邩�ǂ����̃t���O */
        bool _is_delete_value;

        /**
         * �R���X�g���N�^
         * @param prm_pValue �l�i�|�C���^�j
         * @param prm_is_delete_value true  : GgafLinkedListRing�C���X�^���Xdelete���ɁA�v�f(_pValue)��delete����B
         *                            false : �v�f(_pValue)��delete���Ȃ��B
         */
        Elem(T* prm_pValue, bool prm_is_delete_value = true) {
            _pValue = prm_pValue;
            _pNext = _pPrev = NULL;
            _is_first_flg = _is_last_flg = false;
            _is_delete_value = prm_is_delete_value;
        }

        /**
         * �f�X�g���N�^.
         * �����ێ�����v�f�̒l��delete����܂��B<BR>
         */
        ~Elem() {
            if (_is_delete_value) {
                DELETE_IMPOSSIBLE_NULL(_pValue);
            }
        }
    };

    /** [r]�擪�v�f */
    Elem* _pElemFirst;

    /** [r]�J�����g�v�f */
    Elem* _pElemActive;

    /** [r]�v�f�� */
    int _num_elem;

    /**
     * �R���X�g���N�^
     */
    GgafLinkedListRing();

    /**
     * �f�X�g���N�^.
     * �����ێ�����v�f�̒l�́ANULL�Ŗ����ꍇ�A���ꂼ�� delete �ɂ��������܂��B<BR>
     * TODO:delete[] �₻�̑��̉�����@�ɑΉ�
     */
    virtual ~GgafLinkedListRing();

    Elem* getElemFirst() {
        return _pElemFirst;
    }

    Elem* getElemActive() {
        return _pElemActive;
    }

    /**
     * �J�����g�v�f�̒l�i�ێ����Ă�����e�j���擾���� .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �ω�������C���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * @return	�J�����g�v�f�̒l
     */
    virtual T* getCurrent();

    /**
     * �J�����g�v�f����i�߂�B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� next()���s�B�J�����g�v�f���u���v�ɐi��D���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C��D!��E��(A)
     * --------------------------
     * </pre>
     * <BR>
     * �J�����g�v�f�������̏�ԂŖ{���\�b�h�����s����ƁA<BR>
     * �擪���J�����g�v�f�ɂȂ�܂��B<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * (E!)��A��B��C��D��E!��(A)
     * --------------------------
     *               ��  next()���s�B�J�����g�v�f���u���i���擪�j�v�ɐi��A���Q�b�g
     * ---�u���s��v-------------
     * (E)��A!��B��C��D��E��(A!)
     * --------------------------
     * </pre>
     * @return �J�����g�v�f����i�߂���́A���̗v�f�̒l�B
     */
    virtual T* next();

    /**
     * �J�����g�v�f�̎��̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� getNext()���s�B�ω�������D���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * �J�����g�v�f�������̏�ԂŖ{���\�b�h�����s����ƁA<BR>
     * �擪�v�f�̒l���擾���邱�ƂɂȂ�܂��B<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * (E!)��A��B��C��D��E!��(A)
     * --------------------------
     *               ��  getNext()���s�B�ω�������A���Q�b�g
     * ---�u���s��v-------------
     * (!E)��A��B��C��D��E!��(A)
     * --------------------------
     * </pre>
     * @return ���̗v�f�̒l
     */
    virtual T* getNext();

    /**
     * �J�����g�v�f�̂��Ԗڂ̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * getNext(1) �́AgetNext() �Ɠ����ł��BgetNext(0) �� getCurrent()�Ɠ����ł��B
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� getNext(2) �c �ω�������E���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * @param n �C���f�b�N�X
     * @return �J�����g�v�f���炎�Ԗڂ̗v�f�̒l
     */
    virtual T* getNext(int n);

    virtual T* getNextFromFirst(int n);

    /**
     * �J�����g�v�f����߂��B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� B���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B!��C��D��E��(A)
     * --------------------------
     * </pre>
     * @return �J�����g�v�f����߂�����́A���̗v�f�̒l
     */
    virtual T* prev();

    /**
     * �J�����g�v�f���̂P�O�̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �ω�������B���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * @return �O�̗v�f�̒l
     */
    virtual T* getPrev();

    /**
     * �J�����g�v�f�̂��ԖڑO�̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * getPrev(1) �́AgetPrev() �Ɠ����ł��BgetPrev(0) �� get()�Ɠ����ł��B
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� getPrev(2) �c �ω�������A���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * @param n �C���f�b�N�X
     * @return �J�����g�v�f���炎�ԖڑO�̗v�f�̒l
     */
    virtual T* getPrev(int n);

    /**
     * �J�����g�v�f��擪�ɖ߂��B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �J�����g��擪�ɂ���A���Q�b�g
     * ---�u���s��v-------------
     * (E)��A!��B��C��D��E��(A)
     * --------------------------
     * </pre>
     * @return �J�����g�v�f��擪�ɖ߂�����́A���̗v�f�̒l
     */
    virtual T* first();

    /**
     * �擪�̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �ω�������A���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * @return �擪�̗v�f�̒l
     */
    virtual T* getFirst();

    /**
     * �J�����g�v�f�𖖔��ֈړ��B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �J�����g�𖖔��ɂ���E���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C��D��E!��(A)
     * --------------------------
     * </pre>
     * @return �J�����g�v�f�𖖔��ֈړ�������́A���̗v�f�̒l
     */
    virtual T* last();

    /**
     * �����̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �ω�������E���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * @return �����̗v�f�̒l
     */
    virtual T* getLast();

    /**
     * �J�����g�v�f�����X�g�̖����ł��邩���肷�� .
     *<pre>
     * --------------------------
     * (E)��A��B��C��D��E!��(A)
     * --------------------------
     * ��}�̏ꍇtrue
     * </pre>
     * @return true:�����ł���^false:�����ł͖���
     */
    virtual bool isLast();

    /**
     * �J�����g�v�f�����X�g�̐擪�ł��邩���肷�� .
     *<pre>
     * --------------------------
     * (E)��A!��B��C��D��E��(A)
     * --------------------------
     * ��}�̏ꍇtrue
     * </pre>
     * @return true:�����ł���^false:�����ł͖���
     */
    virtual bool isFirst();

    /**
     * �J�����g�v�f�ɒl���㏑���ݒ肷��B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� set(X) �c X���㏑�����Č���C���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��X!��D��E��(A)
     * --------------------------
     * </pre>
     * ���̗v�f�̒l�̉�����́A�߂�l���g�p���ČĂь��ōs���ĉ������B
     * @return �㏑�������O�̗v�f�̒l
     */
    virtual T* set(T* prm_pVal);

    /**
     * �J�����g�v�f�𔲂���� .
     * �V���ȃJ�����g�v�f�� next �̗v�f�ɕς��B
     * <pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� remove() �c C�����o���ăQ�b�g
     * ---�u���s��v-------------
     * (E)��A��B��D!��E��(A)
     * --------------------------
     * </pre>
     *
     * <BR>
     * �J�����g�v�f�������������ꍇ<BR>
     * �V���ȃJ�����g�v�f�͐擪�v�f�ɕς��B
     * <pre>
     * ---�u���s�O�v-------------
     * (E!)��A��B��C��D��E!��(A)
     * --------------------------
     *               �� remove() �c E�𔲂��o���ăQ�b�g
     * ---�u���s��v-------------
     * (D)��A!��B��C��D��(A!)
     * --------------------------
     * </pre>
     *
     * ����������l�̉�������K�v�ȏꍇ�́A�߂�l���g�p���ČĂь��ōs���ĉ������B
     * @return �������O�ɃJ�����g�v�f�������v�f�̒l
     */
    virtual T* remove();

    /**
     * �������擪���牽�Ԗڂ���Ԃ��B
     * �����ێ����Ă���v�f�̒l�̓|�C���^�̂��߁A�l�̔�r�ł͂Ȃ��|�C���^(�A�h���X)����v����
     * �C���f�b�N�X��Ԃ��܂��B�C���f�b�N�X��0����̐��l�ł��B
     * <pre><code>
     * Object* A = new Object();
     * Object* B = new Object();
     * Object* C = new Object();
     * Object* D = new Object();
     * Object* E = new Object();
     * GgafLinkedListRing<Object> ring_list = GgafLinkedListRing<Object>();
     * ring_list.addLast(A);
     * ring_list.addLast(B);
     * ring_list.addLast(C);
     * ring_list.addLast(D);
     *
     * int a = ring_list.indexOf(A);   // a = 0 �ƂȂ�
     * int b = ring_list.indexOf(B);   // b = 1 �ƂȂ�
     * int c = ring_list.indexOf(C);   // c = 2 �ƂȂ�
     * int d = ring_list.indexOf(D);   // d = 3 �ƂȂ�
     * int e = ring_list.indexOf(E);   // e = -1 �ƂȂ�(���݂��Ȃ��ꍇ�̖߂�l)
     * </code></pre>
     * @param prm_pVal �C���f�b�N�X�𒲂ׂ����v�f
     * @return ���݂���ꍇ�A���̃C���f�b�N�X(0�`)��Ԃ��A���݂��Ȃ��ꍇ -1 ��Ԃ��B
     */
    virtual int indexOf(T* prm_pVal);

    /**
     * �����v�f���A����(_is_last_flg �� true)�Ƃ��Ēǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� addLast(X)
     * ---�u���s��v-------------
     * (X)��A��B��C!��D��E��X��(A)
     * --------------------------
     * </pre>
     * <BR>
     * �܂��A���߂Ă�addLast�́A�����v�f�̓J�����g�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~addLast���s�Ȃ��Ă��J�����g�v�f���e�����܂���B<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * NULL(�v�f�Ȃ�)
     * --------------------------
     *               �� addLast(A)
     * --------------------------
     * (A!)��A!��(A!)
     * --------------------------
     *               �� addLast(B)
     * --------------------------
     * (B)��A!��B��(A!)
     * --------------------------
     *               �� addLast(C)
     * --------------------------
     * (C)��A!��B��C��(A!)
     * --------------------------
     * </pre>
     * @param prm_pNew �V�����v�f�̒l
     * @param prm_is_delete_value true  : ���X�g�̃C���X�^���Xdelete���ɁA�����̒ǉ��v�f�l�ɂ��Ă�delete�𔭍s����B
     *                            false : ���X�g�̃C���X�^���Xdelete���ɁA�����̒ǉ��v�f�l�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addLast(T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * �����v�f���A�擪(_is_first_flg �� true)�Ƃ��Ēǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� addFirst(X)
     * ---�u���s��v-------------
     * (E)��X��A��B��C!��D��E��(X)
     * --------------------------
     * </pre>
     * <BR>
     * �܂��A���߂Ă�addFirst�́A�����v�f�̓J�����g�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~addFirst���s�Ȃ��Ă��J�����g�v�f���e�����܂���B<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * NULL(�v�f�Ȃ�)
     * --------------------------
     *               �� addFirst(A)
     * --------------------------
     * (A!)��A!��(A!)
     * --------------------------
     *               �� addFirst(B)
     * --------------------------
     * (A!)��B��A!��(B)
     * --------------------------
     *               �� addFirst(C)
     * --------------------------
     * (A!)��C��B��A!��(C)
     * --------------------------
     * </pre>
     * @param prm_pNew �V�����v�f�̒l
     * @param prm_is_delete_value true  : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��Ă�delete�𔭍s����B
     *                            false : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addFirst(T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * �����v�f���A�J�����g�v�f�́u���v�ɒǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B
     * <pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� addNext(X)
     * ---�u���s��v-------------
     * (E)��A��B��C!��X��D��E��(A)
     * --------------------------
     * </pre>
     * <BR>
     * ���߂Ă� addNext �́A�����v�f�̓J�����g�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~ addNext �́A�J�����g�v�f���e�����܂���B<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * NULL(�v�f�Ȃ�)
     * --------------------------
     *               �� addNext(A)
     * --------------------------
     * (A!)��A!��(A!)
     * --------------------------
     *               �� addNext(B)
     * --------------------------
     * (B)��A!��B��(A!)
     * --------------------------
     *               �� addNext(C)
     * --------------------------
     * (B)��A!��C��B��(A!)
     * --------------------------
     * </pre>
     * <BR>
     * �J�����g�v�f�������̏�ԂŖ{���\�b�h�����s���Ă��A<BR>
     * �����̗v�f�������ɂȂ�܂��B�i�����̗v�f���擪�ɂ͂Ȃ�܂���j<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * (E!)��A��B��C��D��E!��(A)
     * --------------------------
     *               �� addNext(X)
     * ---�u���s��v-------------
     * (X)��A��B��C��D��E!��X��(A)
     * --------------------------
     * </pre>
     * @param prm_pNew �C���X�^���X�����ςݗv�f�̃|�C���^
     * @param prm_is_delete_value true  : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��Ă�delete�𔭍s����B
     *                            false : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addNext(T* prm_pNew, bool prm_is_delete_value = true);


    /**
     * �����v�f���A�J�����g�v�f�́u�O�v�ɒǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B
     * <pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� addPrev(X)
     * ---�u���s��v-------------
     * (E)��A��B��X��C!��D��E��(A)
     * --------------------------
     * </pre>
     * <BR>
     * ���߂Ă� addPrev �́A�����v�f�̓J�����g�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~ addPrev �́A�J�����g�v�f���e�����܂���B<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * NULL(�v�f�Ȃ�)
     * --------------------------
     *               �� addPrev(A)
     * --------------------------
     * (A!)��A!��(A!)
     * --------------------------
     *               �� addPrev(B)
     * --------------------------
     * (A!)��B��A!��(B)
     * --------------------------
     *               �� addPrev(C)
     * --------------------------
     * (A!)��B��C��A!��(B)
     * --------------------------
     * </pre>
     * <BR>
     * �J�����g�v�f���擪�̏�ԂŖ{���\�b�h�����s���Ă��A<BR>
     * �����̗v�f���擪�ɂȂ�܂��B�i�����̗v�f�������ɂ͂Ȃ�܂���j<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * (E)��A!��B��C��D��E��(A!)
     * --------------------------
     *               �� addPrev(X)
     * ---�u���s��v-------------
     * (E)��X��A!��B��C��D��E��(X)
     * --------------------------
     * </pre>
     * @param prm_pNew �V�����v�f�̒l
     * @param prm_is_delete_value true  : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��Ă�delete�𔭍s����B
     *                            false : ���X�g��delete���ɁA�����̒ǉ��v�f�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addPrev(T* prm_pNew, bool prm_is_delete_value = true);


    /**
     * �v�f����Ԃ� .
     *<pre>
     * --------------------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * ��}�̏ꍇ�Alength()��5��Ԃ�
     * �܂��A�v�f�������ꍇ�� 0 ��Ԃ��܂��B
     * @return �v�f��
     */
    virtual int length();
};

//////////////////////////////////////////////////////////////////

/**
 * ��������͎�����
 */

template<class T>
GgafLinkedListRing<T>::GgafLinkedListRing() :
    GgafObject() {
    _num_elem = 0;
    _pElemActive = NULL;
    _pElemFirst = NULL;
}

template<class T>
T* GgafLinkedListRing<T>::getCurrent() {
    if (_pElemActive == NULL) {
        return NULL;
    } else {
        return _pElemActive->_pValue;
    }
}

template<class T>
T* GgafLinkedListRing<T>::next() {
    _pElemActive = _pElemActive->_pNext;
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getNext() {
    return _pElemActive->_pNext->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getNext(int n) {
    Elem* pElem_return = _pElemActive;
    for (int i = 0; i < n; i++) {
        pElem_return = pElem_return->_pNext;
    }
    return pElem_return->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getNextFromFirst(int n) {
    if (_pElemFirst == NULL) {
        return NULL;
    }
    Elem* pElem_return = _pElemFirst;
    for (int i = 0; i < n; i++) {
        pElem_return = pElem_return->_pNext;
    }
    return pElem_return->_pValue;
}




template<class T>
T* GgafLinkedListRing<T>::prev() {
    _pElemActive = _pElemActive->_pPrev;
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getPrev() {
    return _pElemActive->_pPrev->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getPrev(int n) {
    Elem* pElem_return = _pElemActive;
    for (int i = 0; i < n; i++) {
        pElem_return = pElem_return->_pPrev;
    }
    return pElem_return->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::first() {
    _pElemActive = _pElemFirst;
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getFirst() {
    return _pElemFirst->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::last() {
    _pElemActive = _pElemFirst->_pPrev; //��Ȃ̂ŁA�擪�̈�O�͖���
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getLast() {
    return _pElemFirst->_pPrev->_pValue; //��Ȃ̂ŁA�擪�̈�O�͖���
}


template<class T>
bool GgafLinkedListRing<T>::isLast() {
    return _pElemActive->_is_last_flg;
}

template<class T>
bool GgafLinkedListRing<T>::isFirst() {
    return _pElemActive->_is_first_flg;
}

template<class T>
T* GgafLinkedListRing<T>::set(T* prm_pVal) {
    T* ret = _pElemActive->_pValue;
    _pElemActive->_pValue = prm_pVal;
    return ret;
}

template<class T>
T* GgafLinkedListRing<T>::remove() {
    Elem* pMy = _pElemActive;
    _num_elem--;
    if (pMy->_is_first_flg && pMy->_is_last_flg) {
        //�v�f���P�̏ꍇ
        _pElemActive = NULL;
        _pElemFirst = NULL;
        T* r = pMy->_pValue;
        DELETE_IMPOSSIBLE_NULL(pMy);
        return r;
    } else {
        //�A������O��
        Elem* pMyNext = _pElemActive->_pNext;
        Elem* pMyPrev = _pElemActive->_pPrev;
        //���ׂ̃m�[�h���m���q���A�������w���Ȃ�����B
        pMyPrev->_pNext = pMyNext;
        pMyNext->_pPrev = pMyPrev;
        if (pMy->_is_last_flg) { //���������v�f�������������Ȃ�
            pMyPrev->_is_last_flg = true; //��O�̗v�f���V���������ɂȂ�
        }
        if (pMy->_is_first_flg) { //���������v�f���擪�������Ȃ�
            _pElemFirst = pMyNext;
            pMyNext->_is_first_flg = true; //���̗v�f���V�����擪�ɂȂ�
        }
        _pElemActive = pMyNext; //�J�����g�v�f�� next �ɍX�V�B
        T* r = pMy->_pValue;
        DELETE_IMPOSSIBLE_NULL(pMy);
        return r;
    }
}


template<class T>
int GgafLinkedListRing<T>::indexOf(T* prm_pVal) {
    if (_pElemFirst == NULL) {
        return -1;
    }
    int r = 0;
    Elem* pElem = _pElemFirst;
    while (true) {
        if (pElem->_pValue == prm_pVal) {
            return r;
        } else {
            if (pElem->_is_last_flg) {
                break;
            } else {
                pElem = pElem -> _pNext;
                r++;
            }
        }
    }
    return -1;
}

template<class T>
void GgafLinkedListRing<T>::addLast(T* prm_pNew, bool prm_is_delete_value) {
    if (prm_pNew == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! ������NULL�ł�");
    }
    Elem* pElem = NEW Elem(prm_pNew, prm_is_delete_value);

    if (_pElemFirst == NULL) {
        //�ŏ��̂P��
        pElem->_is_first_flg = true;
        pElem->_is_last_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        //�Q�ڈȍ~
        pElem->_is_first_flg = false;
        pElem->_is_last_flg = true;
        Elem* pLastElem = _pElemFirst->_pPrev;
        pLastElem->_is_last_flg = false;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = _pElemFirst;
        _pElemFirst->_pPrev = pElem;
    }
    _num_elem++;
}


template<class T>
void GgafLinkedListRing<T>::addFirst(T* prm_pNew, bool prm_is_delete_value) {
    if (prm_pNew == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! ������NULL�ł�");
    }
    Elem* pElem = NEW Elem(prm_pNew, prm_is_delete_value);
    if (_pElemFirst == NULL) {
        //�ŏ��̂P��
        pElem->_is_first_flg = true;
        pElem->_is_last_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        Elem* pFirstElem = _pElemFirst;
        Elem* pLastElem = _pElemFirst->_pPrev;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = pFirstElem;
        pFirstElem->_pPrev = pElem;
        pFirstElem->_is_first_flg = false;

        pElem->_is_first_flg = true;
        pElem->_is_last_flg = false;
        _pElemFirst = pElem;
    }
    _num_elem++;
}


template<class T>
void GgafLinkedListRing<T>::addNext(T* prm_pNew, bool prm_is_delete_value) {
    if (prm_pNew == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! ������NULL�ł�");
    }
    Elem* pElem = NEW Elem(prm_pNew, prm_is_delete_value);
    if (_pElemFirst == NULL) {
        //�ŏ��̂P��
        pElem->_is_last_flg = true;
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        Elem* pMy = _pElemActive;
        if (pMy->_is_last_flg) {
            pMy->_is_last_flg = false;
            pElem->_is_last_flg = true;
            pElem->_is_first_flg = false;
        }
        Elem* pMyNext = _pElemActive->_pNext;
        pMy->_pNext = pElem;
        pElem->_pPrev = pMy;
        pElem->_pNext = pMyNext;
        pMyNext->_pPrev = pElem;
    }
    _num_elem++;
}

template<class T>
void GgafLinkedListRing<T>::addPrev(T* prm_pNew, bool prm_is_delete_value) {
    if (prm_pNew == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! ������NULL�ł�");
    }
    Elem* pElem = NEW Elem(prm_pNew, prm_is_delete_value);
    if (_pElemFirst == NULL) {
        //�ŏ��̂P��
        pElem->_is_last_flg = true;
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        Elem* pMy = _pElemActive;
        if (pMy->_is_first_flg) {
            pMy->_is_first_flg = false;
            pElem->_is_first_flg = true;
            pElem->_is_last_flg = false;
            _pElemFirst = pElem;
        }
        Elem* pMyPrev = _pElemActive->_pPrev;
        pMyPrev->_pNext = pElem;
        pElem->_pPrev = pMyPrev;
        pElem->_pNext = pMy;
        pMy->_pPrev = pElem;
    }
    _num_elem++;
}


template<class T>
int GgafLinkedListRing<T>::length() {
    return _num_elem;
}

template<class T>
GgafLinkedListRing<T>::~GgafLinkedListRing() {
    _TRACE_("GgafLinkedListRing<T>::~GgafLinkedListRing() BEGIN _num_elem="<<_num_elem);
    //�����Ɏq������ꍇ
    if (_pElemFirst) {
        //�܂��q��delete
        if (_num_elem == 1) {
            //�q�v�f�͂P�̏ꍇ
            DELETE_IMPOSSIBLE_NULL(_pElemFirst);
            _pElemFirst = NULL;
            _pElemActive = NULL;
            _num_elem = 0;

        } else {
            //�q�v�f�͂Q�ȏ�̏ꍇ
            Elem* pLast = _pElemFirst->_pPrev;
            Elem* pLastPrev = pLast->_pPrev;
            while (true) {
                DELETE_IMPOSSIBLE_NULL(pLast); //��������delete
                if (pLastPrev->_is_first_flg) {
                    DELETE_IMPOSSIBLE_NULL(_pElemFirst); //pSubLastPrev == _pSubFirst �ł���
                    _pElemFirst = NULL;
                    _pElemActive = NULL;
                    _num_elem = 0;
                    break;
                }
                pLast = pLastPrev;
                pLastPrev = pLastPrev->_pPrev;
            }
        }
    }
}

}
#endif /*GGAFLINKEDLISTRING_H_*/
