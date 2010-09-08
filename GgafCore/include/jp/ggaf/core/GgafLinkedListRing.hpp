#ifndef GGAFLINKEDLISTRING_H_
#define GGAFLINKEDLISTRING_H_
namespace GgafCore {

/**
 * �v�f�i����^�C���X�^���X�ւ̃|�C���^�j�̊�o�����A�����X�g���\�z����e���v���[�g�ł��B.
 * <B>�y����z</B><BR>
 * �A�����X�g�̐擪�Ɩ������q�����Ă���Ƃ������ƂŁA�w��x�ƕ\�����Ă��܂��B<BR>
 *
 * �Ⴆ�΁A���̂悤�ȃR�[�h��`����
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
 * �T�̗v�f�ŉ��}�̂悤�ȍ\�����̂鎖���o���܂��B<BR>
 * <pre>
 * --------------------------------
 * (E)��A!��B��C��D��E��(A!)
 * --------------------------------
 * </pre>
 * �w�́x�́A�v�f�i���m�ɂ͗v�f��ێ�������ꕨ�j���m�����݂��|�C���^���w�������Ă��鎖�������Ă��܂��B<BR>
 * A ��擪�v�f�AE �𖖔��v�f�A!�̓A�N�e�B�u�v�f(�J�[�\�����w���Ă���悤�Ȃ���)�ƌĂԂ��ƂƂ��܂��B<BR>
 * ���W�b�N���AaddLast() �ɂĈ�ԍŏ��ɒǉ������v�f���擪�v�f�ŁA�Ō�ɒǉ������v�f�������v�f�ƂȂ�܂��B<BR>
 * ���[�́u(E)�v�Ɓu(A!)�v�Ƃ����\�L�́A�A�����X�g�̐擪�Ɩ������A���݂��A�����Ă��鎖�������Ă��܂��B<BR>
 * ��ɂȂ��Ă��邽�ߏI�[�������A�i���� next ������ prev ���\�ł��B
 * �|�C���^�̘A���͏I�[�������ł����A�����t���O�ɂ���Đ擪�v�f�A�����v�f�͊Ǘ�����Ă��܂��B
 * <BR>
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafLinkedListRing : public GgafObject {

private:

    /**
     * ��p�̗v�f���b�v�N���X .
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
         * @param prm_pValue �l�|�C���^
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

protected:
    /** [r]�擪�v�f */
    Elem* _pElemFirst;

    /** [r]�A�N�e�B�u�v�f */
    Elem* _pElemActive;

    /** [r]�v�f�� */
    int _num_elem;

public:
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


    /**
     * �A�N�e�B�u�v�f�̒l�i�ێ����Ă�����e�j���擾���� .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �ω�������C���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * @return	�A�N�e�B�u�v�f�̒l
     */
    virtual T* get();

    /**
     * �A�N�e�B�u�v�f����i�߂�B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� next()���s�B�A�N�e�B�u�v�f���u���v�ɐi��D���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C��D!��E��(A)
     * --------------------------
     * </pre>
     * <BR>
     * �A�N�e�B�u�v�f�������̏�ԂŖ{���\�b�h�����s����ƁA<BR>
     * �擪���A�N�e�B�u�v�f�������ɂȂ�܂��B<BR>
     * <pre>
     * ---�u���s�O�v-------------
     * (E!)��A��B��C��D��E!��(A)
     * --------------------------
     *               ��  next()���s�B�A�N�e�B�u�v�f���u���i���擪�j�v�ɐi��A���Q�b�g
     * ---�u���s��v-------------
     * (E)��A!��B��C��D��E��(A!)
     * --------------------------
     * </pre>
     * @return �A�N�e�B�u�v�f����i�߂���́A���̗v�f�̒l�B
     */
    virtual T* next();

    /**
     * �A�N�e�B�u�v�f�̎��̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� getNext()���s�B�ω�������D���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * </pre>
     * �A�N�e�B�u�v�f�������̏�ԂŖ{���\�b�h�����s����ƁA<BR>
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
     * �A�N�e�B�u�v�f�̂��Ԗڂ̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
     * getNext(1) �́AgetNext() �Ɠ����ł��BgetNext(0) �� get()�Ɠ����ł��B
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
     * @return �A�N�e�B�u�v�f���炎�Ԗڂ̗v�f
     */
    virtual T* getNext(int n);

    /**
     * �A�N�e�B�u�v�f����߂��B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� B���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B!��C��D��E��(A)
     * --------------------------
     * </pre>
     * @return �A�N�e�B�u�v�f����߂�����́A���̗v�f�̒l
     */
    virtual T* prev();

    /**
     * �A�N�e�B�u�v�f���̂P�O�̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
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
     * �A�N�e�B�u�v�f�̂��ԖڑO�̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
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
     * @return �A�N�e�B�u�v�f���炎�ԖڑO�̗v�f
     */
    virtual T* getPrev(int n);




    /**
     * �A�N�e�B�u�v�f��擪�ɖ߂��B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �A�N�e�B�u��擪�ɂ���A���Q�b�g
     * ---�u���s��v-------------
     * (E)��A!��B��C��D��E��(A)
     * --------------------------
     * </pre>
     * @return �A�N�e�B�u�v�f��擪�ɖ߂�����́A���̗v�f�̒l
     */
    virtual T* first();

    /**
     * �擪�̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
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
     * �A�N�e�B�u�v�f�𖖔��ֈړ��B .
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� �A�N�e�B�u�𖖔��ɂ���E���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��C��D��E!��(A)
     * --------------------------
     * </pre>
     * @return �A�N�e�B�u�v�f�𖖔��ֈړ�������́A���̗v�f�̒l
     */
    virtual T* last();

    /**
     * �����̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
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
     * �A�N�e�B�u�v�f�����X�g�̖����ł��邩���肷�� .
     *<pre>
     * --------------------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * ��}�̏ꍇ�AE�̂�true����ȊO��false�ƂȂ�
     * </pre>
     * @return true:�����ł���^false:�����ł͖���
     */
    virtual bool isLast();

    /**
     * �A�N�e�B�u�v�f�����X�g�̐擪�ł��邩���肷�� .
     *<pre>
     * --------------------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * ��}�̏ꍇ�AA�̂�true����ȊO��false�ƂȂ�
     * </pre>
     * @return true:�����ł���^false:�����ł͖���
     */
    virtual bool isFirst();

    /**
     * �A�N�e�B�u�v�f�ɒl���㏑���ݒ肷��B .
     * ���̗v�f�̒l�̉�����́A�߂�l���g�p���ČĂь��ōs���ĉ������B
     *<pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� set(X) �c X���㏑�����Č���C���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��X!��D��E��(A)
     * --------------------------
     * </pre>
     * @return �㏑�������O�̗v�f�̒l
     */
    virtual T* set(T* prm_pVal);

    /**
     * �A�N�e�B�u�v�f�𔲂���� .
     * �V���ȃA�N�e�B�u�v�f�� next �̗v�f�ɕς��B
     * <pre>
     * ---�u���s�O�v-------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     *               �� pick() �c �����o����C���Q�b�g
     * ---�u���s��v-------------
     * (E)��A��B��D!��E��(A)
     * --------------------------
     * </pre>
     *
     * <BR>
     * �A�N�e�B�u�v�f�������������ꍇ<BR>
     * �V���ȃA�N�e�B�u�v�f�͐擪�v�f�ɕς��B
     * <pre>
     * ---�u���s�O�v-------------
     * (E!)��A��B��C��D��E!��(A)
     * --------------------------
     *               �� pick() �c �����o����E���Q�b�g
     * ---�u���s��v-------------
     * (D)��A!��B��C��D��(A!)
     * --------------------------
     * </pre>
     *
     * ����������l�̉�������K�v�ȏꍇ�́A�߂�l���g�p���ČĂь��ōs���ĉ������B
     * @return �������O�ɃA�N�e�B�u�v�f�������v�f�̒l
     */
    virtual T* pick();

    virtual bool has(T* prm_pVal);

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
     * �܂��A���߂Ă�addLast�́A�����̃I�u�W�F�N�g�͂ɃA�N�e�B�u�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~addLast���s�Ȃ��Ă��A�N�e�B�u�v�f�͉e������܂���B<BR>
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
     * @param prm_pNew �C���X�^���X�����ςݗv�f�̃|�C���^
     * @param prm_is_delete_value true  : �{�C���X�^���Xdelete���ɁA�����̒ǉ��v�f�ɂ���delete�����s����B
     *                            false : �{�C���X�^���Xdelete���ɁA�����̒ǉ��v�f�ɂ��ĉ����s��Ȃ��B
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
     * �܂��A���߂Ă�addFirst�́A�����̃I�u�W�F�N�g�͂ɃA�N�e�B�u�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~addFirst���s�Ȃ��Ă��A�N�e�B�u�v�f�͉e������܂���B<BR>
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
     * @param prm_pNew �C���X�^���X�����ςݗv�f�̃|�C���^
     * @param prm_is_delete_value true  : �{�C���X�^���Xdelete���ɁA�����̒ǉ��v�f�ɂ���delete�����s����B
     *                            false : �{�C���X�^���Xdelete���ɁA�����̒ǉ��v�f�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addFirst(T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * �����v�f���A�A�N�e�B�u�v�f�́u���v�ɒǉ����� .
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
     * ���߂Ă� addNext �́A�����I�u�W�F�N�g�̓A�N�e�B�u�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~ addNext �́A�A�N�e�B�u�v�f�͉e������܂���B<BR>
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
     * �A�N�e�B�u�v�f�������̏�ԂŖ{���\�b�h�����s����ƁA<BR>
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
     * @param prm_is_delete_value true  : �{�C���X�^���Xdelete���ɁA�����̒ǉ��v�f�ɂ���delete�����s����B
     *                            false : �{�C���X�^���Xdelete���ɁA�����̒ǉ��v�f�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addNext(T* prm_pNew, bool prm_is_delete_value = true);


    /**
     * �����v�f���A�A�N�e�B�u�v�f�́u�O�v�ɒǉ����� .
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
     * ���߂Ă� addPrev �́A�����I�u�W�F�N�g�̓A�N�e�B�u�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~ addPrev �́A�A�N�e�B�u�v�f�͉e������܂���B<BR>
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
     * �A�N�e�B�u�v�f���擪�̏�ԂŖ{���\�b�h�����s����ƁA<BR>
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
     * @param prm_pNew �C���X�^���X�����ςݗv�f�̃|�C���^
     * @param prm_is_delete_value true  : �{�C���X�^���Xdelete���ɁA�����̒ǉ��v�f�ɂ���delete�����s����B
     *                            false : �{�C���X�^���Xdelete���ɁA�����̒ǉ��v�f�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addPrev(T* prm_pNew, bool prm_is_delete_value = true);


    /**
     * �v�f����Ԃ� .
     *<pre>
     * --------------------------
     * (E)��A��B��C!��D��E��(A)
     * --------------------------
     * ��}�̏ꍇ�Alength()��5��Ԃ�
     * </pre>
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
T* GgafLinkedListRing<T>::get() {
    return _pElemActive->_pValue;
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
T* GgafLinkedListRing<T>::pick() {
    Elem* pMy = _pElemActive;
    _num_elem--;
    if (pMy->_is_first_flg && pMy->_is_last_flg) {
        //�v�f���P�̏ꍇ
        _pElemActive = NULL;
        _pElemFirst = NULL;
        return pMy->_pValue;
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
        _pElemActive = pMyNext; //�A�N�e�B�u�v�f�� next �ɍX�V�B
        return pMy->_pValue;
    }
}


template<class T>
bool GgafLinkedListRing<T>::has(T* prm_pVal) {
    if (_pElemFirst == NULL) {
        return false;
    }
    Elem* pElem = _pElemFirst;
    while (true) {
        if (pElem->_pValue == prm_pVal) {
            return true;
        } else {
            if (pElem->_is_last_flg) {
                break;
            } else {
                pElem = pElem -> _pNext;
            }
        }
    }
    return false;
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
