#ifndef GGAF_CORE_LINKEDLISTRING_H_
#define GGAF_CORE_LINKEDLISTRING_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * ��o�����A�����X�g(�O�����[)���\�z�B.
 * <B>�y����z</B><BR>
 * �I�u�W�F�N�g�փ|�C���^�̊�o�����A�����X�g���쐬���܂��B<BR>
 * �Ⴆ�΁A���̂悤�ȃR�[�h��������
 * <pre><code>
 * Object* A = new Object();
 * Object* B = new Object();
 * Object* C = new Object();
 * Object* D = new Object();
 * Object* E = new Object();
 * RingLinkedList<Object> ring_list = RingLinkedList<Object>();
 * ring_list.addLast(A);
 * ring_list.addLast(B);
 * ring_list.addLast(C);
 * ring_list.addLast(D);
 * ring_list.addLast(E);
 * </code></pre>
 *
 * �T�̗v�f�ŉ��}�̂悤�ȍ\�����̂鎖���o���܂��B<BR>
 * <pre>
 * -------------------------------------------------
 * ([E])��[A]!��[B]��[C]��[D]��[E]��([A]!)
 * -------------------------------------------------
 *
 * -------------------------------------------------
 * �C���[�W�}   [�`]!
 *             �^  �_
 *          [�d]    [�a]
 *            \      /
 *           [�c]�[[�b]
 * --------------------------------------------------
 * �擪�v�f     :[A]     (=getFirst();)
 * ���ԗv�f     :[B]�`[D]
 * �����v�f     :[E]     (=getLast(); =getFirst()->getPrev();)
 * �J�����g�v�f :[A]     (=getCurrent();)
 * </pre>
 * �e���v���[�g�����͓����ێ�����|�C���^�̌^���w�肵�܂��B<BR>
 * �܂�A�uRingLinkedList<Object*>();�v�ł͂Ȃ��uRingLinkedList<Object>();�v�Ƃ��邱�ƂƂ��܂��B<BR>
 * �w[A]�x�́w [ ] �x �́A�w�v�f�x�ƌĂ΂����ꕨ�i�R���e�i�j��\���A�w[A]�x�́wA�x�͗v�f���ێ�����w�l�x��\���Ă��܂��B<BR>
 * �}�́w�́x�́A�v�f���m�����݂��|�C���^���w�������Ă��鎖�������Ă��܂��B<BR>
 * "!" �̓J�����g�v�f(�J�[�\�����w���Ă���悤�Ȃ���)�ŁA�{�e���v���[�g���\�b�h�ɂ��@�\�̊�ƂȂ�v�f�ł��B<BR>
 * ���[�́w([E])�x�Ɓw([A]!)�x�Ƃ����\�L�́A�v�f���X�g�̐擪�Ɩ������A���݂��A�����Ă��鎖�������Ă��܂��B<BR>
 * ��ɂȂ��Ă��邽�ߏI�[�������A�i���� next ������ prev ���\�ł��B<BR>
 * next ������ prev �ł̏I�[�͂���܂��񂪁A�����t���O�ɂ���ă��X�g�̐擪�v�f�A�����v�f�͊Ǘ�����Ă��܂��B<BR>
 * ��}�ł́A�w[A]�x ��擪�v�f�A�w[E]�x �𖖔��v�f�A�Ƃ��ē����Ǘ�����Ă���A�ʏ�̐��`���X�g�̂悤�Ȏg�������\�ł��B<BR>
 * [�ߑ�]<BR>
 * �{�N���X�̐����ŁA�u�v�f�v�Ƃ����\���́A���̓C���i�[�N���X�� Elem�I�u�W�F�N�g�ւ̃|�C���^�̎����w���A<BR>
 * �u�v�f�̒l�v�Ƃ����\���� Elem �I�u�W�F�N�g�̃����o _pValue ���w���܂��B<BR>
 * �u�v�f�̒l�v�̌^�� T* �ł��B��̗�ł� Object* �^���w���܂��BObject �̒l���̂ł͂���܂���B
 * <BR>
 * @tparam T �Ǘ�����v�f�̌^�i���̌^�̃|�C���^�^�������ŊǗ������B�j
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
template<class T>
class RingLinkedList: public Object {

public:
    /**
     * �R���e�i .
     * �l�����b�v���A�O��|�C���^��ێ��B
     */
    class Elem {
    public:
        /** [r]���ۂ̗v�f�̒l */
        const T* _pValue;
        /** [r]���v�f */
        Elem* _pNext;
        /** [r]�O�v�f */
        Elem* _pPrev;
        /** [r]�֘A�v�f�z�� */
        Elem** _papRelation;
        /** [r]�擪�v�f�t���O (���v�f���擪�v�f�̏ꍇ true)*/
        bool _is_first_flg;
        /** [r]�����v�f�t���O (���v�f�������v�f�̏ꍇ true)*/
        bool _is_last_flg;
        /** [r/w]delete����_pValue��delete���邩�ǂ����̃t���O */
        bool _is_delete_value;
        /** [r]�擪�v�f����̃C���f�b�N�X(0�`)�BcreateIndex()���s�ō쐬����� */
        int _idx;

    public:
        /**
         * �R���X�g���N�^
         * @param prm_pValue �l�i�|�C���^�j
         * @param prm_relation_num �ǉ��m�ۂ���֘A�v�f��
         * @param prm_is_delete_value true  : RingLinkedList�C���X�^���Xdelete���ɁA�v�f(_pValue)��delete����B<BR>
         *                            false : �v�f(_pValue)��delete���Ȃ��B
         */
        Elem(const T* prm_pValue, int prm_relation_num,
                bool prm_is_delete_value = true) {
            _pValue = prm_pValue;
            _pNext = _pPrev = nullptr;
            if (prm_relation_num == 0) {
                _papRelation = nullptr;
            } else {
                _papRelation = NEW Elem*[prm_relation_num];
                for (int i = 0; i < prm_relation_num; i++) {
                    _papRelation[i] = nullptr;
                }
            }
            _is_first_flg = _is_last_flg = false;
            _is_delete_value = prm_is_delete_value;
            _idx = -1;
        }
        /**
         * �v�f�̒l��Ԃ��B
         * @return �l
         */
        inline T* getValue() const {
            return (T*) _pValue;
        }
        /**
         * �v�f������I�Ɋ֘A�t���� .
         * @param prm_connection_index �v�f�֘A�ڑ��ԍ�
         * @param prm_pOppElem ��֘A�v�f
         */
        void connect(int prm_connection_index, Elem* prm_pOppElem) {
            _papRelation[prm_connection_index] = prm_pOppElem;
        }
        /**
         * �f�X�g���N�^.
         * �����ێ�����v�f�̒l��delete����܂��B<BR>
         */
        ~Elem() {
            if (_is_delete_value) {
                GGAF_DELETE(_pValue);
            }
            GGAF_DELETEARR_NULLABLE(_papRelation);
        }
    }; //class Elem

    /** [r]�擪�v�f */
    Elem* _pElem_first;
    /** [r]�J�����g�v�f */
    Elem* _pElemActive;
    /** [r]�v�f�� */
    int _num_elem;
    /** [r]�֘A�v�f�� */
    int _relation_num;
    /** [r]�C���f�b�N�X�ɑ΂���v�f�l�̔z��AcreateIndex()���s�ō쐬����� */
    const T** _papLinearVal;

public:
    /**
     * �R���X�g���N�^ .
     * �g���֘A�v�f���Ƃ́Anext prev �ȊO�Ƀ����[�V�������s���}���ł��B
     * @param prm_extend_relation_num �g���֘A�v�f��
     */
    RingLinkedList(int prm_extend_relation_num = 0);

    /**
     * �f�X�g���N�^.
     * �����ێ�����v�f�̒l�́Anullptr�Ŗ����ꍇ�A���ꂼ�� delete �ɂ��������܂��B<BR>
     * TODO:delete[] �₻�̑��̉�����@�ɑΉ�
     */
    virtual ~RingLinkedList();

    /**
     * �����̒l���A�J�����g�v�f�́u���v�ɒǉ�����B
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� addNext(X) ���s�B�J�����g�v�f [C] �́u���v�ɑ}�������B
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[X]��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * ��{�I�ɃJ�����g�v�f�͕ω����܂���A�A�����߂Ă� addNext �́A<BR>
     * �����̒l�̗v�f�̓J�����g�v�f�ɂȂ�܂��B<BR>
     * �Q��ڈȍ~ addNext() �́A�J�����g�v�f�ɉe����^���܂���B<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * nullptr(�v�f�Ȃ�)
     * -------------------------------------------
     *               �� addNext(A)
     * -------------------------------------------
     * ([A]!)��[A]!��([A]!)
     * -------------------------------------------
     *               �� addNext(B)
     * -------------------------------------------
     * ([B])��[A]!��[B]��([A]!)
     * -------------------------------------------
     *               �� addNext(C)
     * -------------------------------------------
     * ([B])��[A]!��[C]��[B]��([A]!)
     * -------------------------------------------
     * </pre>
     * <BR>
     * �J�����g�v�f�������̏�ԂŖ{���\�b�h�����s���A�����́u���v�ɑ}�����s�����ꍇ�A<BR>
     * �����̒l���A�����̗v�f�l�ɂȂ�܂��B�i�����̒l�̗v�f���A�擪�ɂ͂Ȃ�܂���j<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E]!)��[A]��[B]��[C]��[D]��[E]!��([A])
     * -------------------------------------------
     *               �� addNext(X)
     * ---�u���s��v------------------------------
     * ([X])��[A]��[B]��[C]��[D]��[E]!��[X]��([A])
     * -------------------------------------------
     * </pre>
     * createIndex() �ɂ���č쐬���ꂽ�����C���f�b�N�X�͔j������܂��B
     *
     * @param prm_pNew �C���X�^���X�����ςݗv�f�̃|�C���^
     * @param prm_is_delete_value true  : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��Ă�delete�𔭍s����B(T�̃w�b�_include��Y�ꂸ�ɁI)<BR>
     *                            false : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addNext(const T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * �����̒l���A�J�����g�v�f�́u�O�v�ɒǉ�����B�J�����g�v�f�͕ω����Ȃ� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� addPrev(X)
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[X]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * ��{�I�ɃJ�����g�v�f�͕ω����܂���A�A�����߂Ă� addPrev() �́A
     * �����̒l�̓J�����g�v�f�l�ƂȂ�܂��B<BR>
     * �Q��ڈȍ~ addPrev() �́A�J�����g�v�f�ɉe����^���܂���B<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * nullptr(�v�f�Ȃ�)
     * -------------------------------------------
     *               �� addPrev(A)
     * -------------------------------------------
     * ([A]!)��[A]!��([A]!)
     * -------------------------------------------
     *               �� addPrev(B)
     * -------------------------------------------
     * ([A]!)��[B]��[A]!��([B])
     * -------------------------------------------
     *               �� addPrev(C)
     * -------------------------------------------
     * ([A]!)��[B]��[C]��[A]!��([B])
     * -------------------------------------------
     * </pre>
     * <BR>
     * �J�����g�v�f���擪�̏�ԂŖ{���\�b�h�����s���A�擪�́u�O�v�ɑ}�����s�����ꍇ�A<BR>
     * �����̒l�̗v�f���擪�ɂȂ�܂��B�i�����̒l�̗v�f�������ɂ͂Ȃ�܂���j<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]!��[B]��[C]��[D]��[E]��([A]!)
     * -------------------------------------------
     *               �� addPrev(X)
     * ---�u���s��v------------------------------
     * ([E])��[X]��[A]!��[B]��[C]��[D]��[E]��([X])
     * -------------------------------------------
     * </pre>
     * createIndex() �ɂ���č쐬���ꂽ�����C���f�b�N�X�͔j������܂��B
     *
     * @param prm_pNew �V�����v�f�̒l
     * @param prm_is_delete_value true  : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��Ă�delete�𔭍s����B(T�̃w�b�_include��Y�ꂸ�ɁI)<BR>
     *                            false : ���X�g��delete���ɁA�����̒ǉ��v�f�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addPrev(const T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * �����̒l���A����(_is_last_flg �� true)�Ƃ��Ēǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� addLast(X)
     * ---�u���s��v------------------------------
     * ([X])��[A]��[B]��[C]!��[D]��[E]��[X]��([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * ��{�I�ɃJ�����g�v�f�͕ω����܂���A�A�����߂Ă� addLast() �́A
     * �����̒l�̓J�����g�v�f�ɂȂ�܂��B<BR>
     * �Q��ڈȍ~ addLast() �́A�J�����g�v�f�ɉe����^���܂���B<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * nullptr(�v�f�Ȃ�)
     * -------------------------------------------
     *               �� addLast(A)
     * -------------------------------------------
     * ([A]!)��[A]!��([A]!)
     * -------------------------------------------
     *               �� addLast(B)
     * -------------------------------------------
     * ([B])��[A]!��[B]��([A]!)
     * -------------------------------------------
     *               �� addLast(C)
     * -------------------------------------------
     * ([C])��[A]!��[B]��[C]��([A]!)
     * -------------------------------------------
     * </pre>
     * createIndex() �ɂ���č쐬���ꂽ�����C���f�b�N�X�͔j������܂��B
     *
     * @param prm_pNew �V�����v�f�̒l
     * @param prm_is_delete_value true  : ���X�g�̃C���X�^���Xdelete���ɁA�����̒ǉ��v�f�l�ɂ��Ă�delete�𔭍s����B(T�̃w�b�_include��Y�ꂸ�ɁI)<BR>
     *                            false : ���X�g�̃C���X�^���Xdelete���ɁA�����̒ǉ��v�f�l�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addLast(const T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * �����̒l���A�擪(_is_first_flg �� true)�Ƃ��Ēǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� addFirst(X)
     * ---�u���s��v------------------------------
     * ([E])��[X]��[A]��[B]��[C]!��[D]��[E]��([X])
     * -------------------------------------------
     * </pre>
     * <BR>
     * ��{�I�ɃJ�����g�v�f�͕ω����܂���A�A�����߂Ă� addFirst() �́A
     * �����̒l�̓J�����g�v�f�Ȃ�܂��B<BR>
     * �Q��ڈȍ~ addFirst() �́A�J�����g�v�f�ɉe����^���܂���B<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * nullptr(�v�f�Ȃ�)
     * -------------------------------------------
     *               �� addFirst(A)
     * -------------------------------------------
     * ([A]!)��[A]!��([A]!)
     * -------------------------------------------
     *               �� addFirst(B)
     * -------------------------------------------
     * ([A]!)��[B]��[A]!��([B])
     * -------------------------------------------
     *               �� addFirst(C)
     * -------------------------------------------
     * ([A]!)��[C]��[B]��[A]!��([C])
     * -------------------------------------------
     * </pre>
     * createIndex() �ɂ���č쐬���ꂽ�����C���f�b�N�X�͔j������܂��B
     *
     * @param prm_pNew �V�����v�f�̒l
     * @param prm_is_delete_value true  : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��Ă�delete�𔭍s����B(T�̃w�b�_include��Y�ꂸ�ɁI)<BR>
     *                            false : ���X�g��delete���ɁA�����̒ǉ��v�f�l�ɂ��ĉ����s��Ȃ��B
     */
    virtual void addFirst(const T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * �J�����g�v�f����i�߁A���̗v�f�̒l�𓾂� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� next()���s�B�J�����g�v�f���u���v�ɐi�߁A�l D ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]��[D]!��[E]��([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * �J�����g�v�f�������̏�ԂŖ{���\�b�h�����s����ƁA<BR>
     * �擪���J�����g�v�f�ɂȂ�܂��B<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E]!)��[A]��[B]��[C]��[D]��[E]!��([A])
     * -------------------------------------------
     *               ��  next()���s�B�J�����g�v�f���u��(���擪)�v�ɐi�߁A�l A ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]!��[B]��[C]��[D]��[E]��([A]!)
     * -------------------------------------------
     * </pre>
     * @return �J�����g�v�f����i�߂���A���̗v�f�̒l��Ԃ�
     */
    virtual T* next();

    /**
     * �J�����g�v�f����߂��A���̗v�f�̒l�𓾂� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� prev() ���s�B�l B ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]!��[C]��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * �J�����g�v�f���擪�̏�ԂŖ{���\�b�h�����s����ƁA<BR>
     * �������J�����g�v�f�ɂȂ�܂��B<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]!��[B]��[C]��[D]��[E]��([A]!)
     * -------------------------------------------
     *               ��   prev() ���s�B�J�����g�v�f���u�O(������)�v�Ɉړ��A�l E ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E]!)��[A]��[B]��[C]��[D]��[E]!��([A])
     * -------------------------------------------
     * </pre>
     * @return �J�����g�v�f����O�ɖ߂�����A���̗v�f�̒l��Ԃ�
     */
    virtual T* prev();

    /**
     * �J�����g�v�f��擪�ɖ߂��A���̗v�f�̒l�𓾂� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� �J�����g��擪�Ɉړ��A���̗v�f�̒l A ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]!��[B]��[C]��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * @return �J�����g�v�f��擪�ɖ߂�����A���̗v�f�̒l��Ԃ�
     */
    virtual T* first();
    /**
     * �J�����g�v�f�𖖔��ֈړ��B .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� �J�����g�𖖔��Ɉړ��A���̗v�f�̒l E ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E]!)��[A]��[B]��[C]��[D]��[E]!��([A])
     * -------------------------------------------
     * </pre>
     * @return �J�����g�v�f�𖖔��ֈړ�������́A���̗v�f�̒l
     */
    virtual T* last();

    /**
     * �J�����g�v�f���w��̐擪�v�f����̐�΃C���f�b�N�X�Ɉړ������A���̗v�f�̒l�𓾂� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� current(1); �J�����g���ړ��A���̗v�f�̒l B ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]!��[C]��[D]��[E]��([A])
     *         0    1     2    3    4
     * -------------------------------------------
     * </pre>
     * @param n �擪�v�f����̐�΃C���f�b�N�X
     * @return �J�����g�v�f���ړ�������́A���̗v�f�̒l
     */
    virtual T* current(int n);

    /**
     * �J�����g�v�f���֘A�v�f�ֈړ������A���̗v�f�̒l�𓾂�  .
     * �����̊֘A�v�f�ڑ��ԍ����͈͊O�̏ꍇ�A���͊֘A���ݒ�̏ꍇ�G���[
     * @param prm_connection_index �֘A�v�f�ڑ��ԍ�
     * @return �J�����g�v�f���֘A�v�f�ֈړ�������́A���̗v�f�̒l
     */
    virtual T* gotoRelation(int prm_connection_index);

    /**
     * �J�����g�v�f�̎��̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� getNext() ���s�B���ɕω������ɁA�l D ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * �J�����g�v�f�������̏�ԂŖ{���\�b�h�����s����ƁA<BR>
     * �擪�v�f�̒l���擾���邱�ƂɂȂ�܂��B<BR>
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E]!)��[A]��[B]��[C]��[D]��[E]!��([A])
     * -------------------------------------------
     *               ��  getNext() ���s�B���ɕω������ɁA�l A ���Q�b�g
     * ---�u���s��v------------------------------
     * (![E])��[A]��[B]��[C]��[D]��[E]!��([A])
     * -------------------------------------------
     * </pre>
     * @return ���̗v�f�̒l
     */
    virtual T* getNext() const;

    /**
     * �J�����g�v�f�̂��Ԗڂ̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * getNext(1) �́AgetNext() �Ɠ����ł��BgetNext(0) �� getCurrent()�Ɠ����ł��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     *                   0     1    2     3
     *   2     3    4    5
     * -------------------------------------------
     *               �� getNext(2) ���s�B���ɕω������ɁA�l E ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * @param n �C���f�b�N�X
     * @return �J�����g�v�f���炎�Ԗڂ̗v�f�̒l (�A�� n >= 0)
     */
    virtual T* getNext(int n) const;

    /**
     * �J�����g�v�f���̂P�O�̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� getPrev() ���s�B���ɕω������ɁA�l B ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * @return �O�̗v�f�̒l
     */
    virtual T* getPrev() const;

    /**
     * �J�����g�v�f�̂��ԖڑO�̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * getPrev(1) �́AgetPrev() �Ɠ����ł��BgetPrev(0) �� get()�Ɠ����ł��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     *   3     2    1    0
     *                   5     4    3     2
     * -------------------------------------------
     *               �� getPrev(2) ���s�B���ɕω������ɁA�l A ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * @param n �C���f�b�N�X
     * @return �J�����g�v�f���炎�ԖڑO�̗v�f�̒l (�A�� n >= 0)
     */
    virtual T* getPrev(int n) const;

    /**
     * �擪�̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� �ω�������[A]���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * @return �擪�̗v�f�̒l
     */
    virtual T* getFirst() const;

    /**
     * �擪�v�f�̂��Ԗڂ̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * getFromFirst(0) �́AgetFirst() �Ɠ����ł��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     *         0    1    2     3    4     5
     *   4     5    6
     * -------------------------------------------
     *               �� getFromFirst(3) ���s�B���ɕω������ɁA�l D ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * @param n �C���f�b�N�X
     * @return �擪�v�f���炎�Ԗڂ̗v�f�̒l (�A�� n >= 0)
     */
    virtual T* getFromFirst(int n) const;

    /**
     * �����̗v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� getLast() ���s�B���ɕω������ɁA�l E ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * @return �����̗v�f�̒l
     */
    virtual T* getLast() const;

    /**
     * �J�����g�v�f�̒l�i�ێ����Ă�����e�j���擾���� .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� ���s�B���ɕω������ɁA�l C ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * @return  �J�����g�v�f�̒l
     */
    virtual T* getCurrent() const;

    /**
     * �֘A�v�f�̒l���擾����B�J�����g�v�f�͕ω����Ȃ� .
     * @param prm_connection_index �֘A�v�f�ڑ��ԍ�
     * @return �֘A�v�f�̒l�^�������͈͊O�̏ꍇ�A���͊֘A���ݒ�̏ꍇ nullptr
     */
    virtual T* getRelation(int prm_connection_index) const;

    /**
     * ���݂̃J�����g�v�f�́A�擪���牽�Ԗڂ�(0�`)��Ԃ��B
     * getCurrent() ��nullptr �̏ꍇ�� -1 ��Ԃ��B
     * @return �J�����g�v�f�̃C���f�b�N�X
     */
    virtual int getCurrentIndex() const;

    /**
     * �J�����g�v�f�����X�g�̖����ł��邩�ǂ������肷�� .
     * <pre>
     * -------------------------------------------
     * ([E]!)��[A]��[B]��[C]��[D]��[E]!��([A])
     * -------------------------------------------
     * ��}�̏ꍇ true
     * </pre>
     * @return true:�����ł���^false:�����ł͖���
     */
    virtual bool isLast() const;

    /**
     * �J�����g�v�f�����X�g�̐擪�ł��邩�ǂ������肷�� .
     * <pre>
     * -------------------------------------------
     * ([E])��[A]!��[B]��[C]��[D]��[E]��([A]!)
     * -------------------------------------------
     * ��}�̏ꍇ true
     * </pre>
     * @return true:�����ł���^false:�����ł͖���
     */
    virtual bool isFirst() const;

    /**
     * �J�����g�v�f�ɒl���㏑���ݒ肷��B .
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� replace(X) �c �l X ���㏑�����āA���X�̒l C ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[X]!��[D]��[E]��([A])
     * -------------------------------------------
     *
     * ���A���A�㏑���O�̌��̗v�f�ݒ莞�ɁA���� delete �t���O�͂��̂܂܂ƂȂ�܂��B
     * </pre>
     * @param prm_pVal �V�����v�f�̒l
     * @return ���̐ݒ�v�f������ delete �̏ꍇ nullptr �^ ���̐ݒ�v�f������ delete �ł͂Ȃ��ꍇ�A�㏑�������O�̗v�f(����ɗ��p����鎖��z��B)
     */
    virtual T* replace(const T* prm_pVal);

    /**
     * �J�����g�v�f�𔲂���� .
     * �V���ȃJ�����g�v�f�� next �̗v�f�ɕς��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     *               �� remove() �c �v�f [C] �𔲂����B�����Ēl C ���Q�b�g
     * ---�u���s��v------------------------------
     * ([E])��[A]��[B]��[D]!��[E]��([A])
     * -------------------------------------------
     * </pre>
     *
     * <BR>
     * �J�����g�v�f�������������ꍇ<BR>
     * �V���ȃJ�����g�v�f�͐擪�v�f�ɕς��B
     * <pre>
     * ---�u���s�O�v------------------------------
     * ([E]!)��[A]��[B]��[C]��[D]��[E]!��([A])
     * -------------------------------------------
     *               �� remove() �c �v�f [E] �𔲂����B�����Ēl E ���Q�b�g
     * ---�u���s��v------------------------------
     * ([D])��[A]!��[B]��[C]��[D]��([A]!)
     * -------------------------------------------
     * </pre>
     * createIndex() �ɂ���č쐬���ꂽ�����C���f�b�N�X�͔j������܂��B�i�K�v�ł���΍č쐬���Ă��������j
     * ����������l�̉�������K�v�ȏꍇ�́A�߂�l���g�p���ČĂь��ōs���ĉ������B
     * @return �������O�ɃJ�����g�v�f�������v�f�̒l
     */
    virtual T* remove();

    /**
     * �S�Ă̗v�f�𔲂���� .
     */
    virtual void removeAll();

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
     * RingLinkedList<Object> ring_list = RingLinkedList<Object>();
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
    virtual int indexOf(const T* prm_pVal) const;

    /**
     * �v�f����Ԃ� .
     * <pre>
     * -------------------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * ��}�̏ꍇ�Alength() �� 5 ��Ԃ�
     * �܂��A�v�f�������ꍇ�� 0 ��Ԃ��܂��B
     * @return �v�f��
     */
    virtual int length() const;

    /**
     * �擪�v�f��Ԃ� .
     * <pre>
     * -------------------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * ��}�̏ꍇ�AgetElemFirst() �͗v�f [A] ��Ԃ��i�l A �ł͖����j�B
     * @return
     */
    Elem* getElemFirst() const {
        return _pElem_first;
    }

    /**
     * �J�����g�v�f��Ԃ� .
     * <pre>
     * -------------------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     * -------------------------------------------
     * </pre>
     * ��}�̏ꍇ�AgetElemActive() �͗v�f [C] ��Ԃ��i�l C �ł͖����j�B
     * @return
     */
    Elem* getElemActive() const {
        return _pElemActive;
    }

    /**
     * �擪���炎�Ԗڂ̗v�f��Ԃ� .
     * <pre>
     * -------------------------------------------
     * ([E])��[A]��[B]��[C]!��[D]��[E]��([A])
     *         0    1    2     3    4     5
     *   4     5
     * -------------------------------------------
     * </pre>
     * ��}�̏ꍇ�AgetElemFromFirst(3) �͗v�f [D] ��Ԃ��i�l D �ł͖����j�B
     * @param n �擪����̃C���f�b�N�X(�A�� n >= 0)
     * @return �擪���炎�Ԗڂ̗v�f
     */
    Elem* getElemFromFirst(int n) const {
        if (_pElem_first == nullptr) {
            return nullptr;
        }
        Elem* pElem = _pElem_first;
        int x = n % _num_elem;
        for (int i = 0; i < x; i++) {
            pElem = pElem->_pNext;
        }
        return pElem;
    }

    /**
     * �C���f�b�N�X���쐬 .
     * �v�f�l�ւ̎Q�Ƃ��A�z��ɕʓr�����ێ����Q�Ǝ��ɗ��p���܂��B
     * �C���f�b�N�X�������Œl���擾���郁�\�b�h�̃p�t�H�[�}���X���オ��܂��B
     * �A���v�f����ύX����ƁA�č\�z�̕K�v������܂��B
     * �v�f�l��ǉ���A�v�f�����ω����Ȃ����X�g�Ȃ�΁A�{���\�b�h�����s���܂��傤�B
     */
    void createIndex();

    /**
     * �S�Ă̗v�f�l�ɑ΂��Ďw��̊֐������s������ .
     * �v�f�n�̃|�C���^���A�����֐��|�C���^�� pFunc�̑�P���� T* �ɓn���Ă��܂��B
     * prm1, prm2, prm3 �́A�����֐��|�C���^�� void*, void*, void* �ɓn���Ă��܂��B(�L���v�`���I�Ɏg���āI)<BR>
     * <BR>
     * ���g�p�၄<BR>
     * �t�H�[���[�V�����̕ґ������o�[�̃I�u�W�F�N�g(Actor*)���ARingLinkedList���X�g(listFollowers_)��
     * �Ǘ�����Ă���Ƃ���B<BR>
     * ���̕ґ������o�[�S���ɁA��������(order1)���o���B�����̑��x�� int velo_mv_ �Ƃ���B
     * �Ƃ������ꍇ�A�ȉ��̂悤�Ȋ��ɂȂ�B<BR>
     * <BR>
     * <code><pre>
     *
     * class FormationXXX : public DepositoryFormation {
     * public :
     *     int velo_mv_;
     *     RingLinkedList<Actor> listFollowers_;
     *
     *     static void FormationXXX::order1(Actor* prm_pActor, void* p1, void* p2, void* p3) {
     *         //�X�̃����o�[����
     *         EnemyXXX* pEnemyXXX = (EnemyDelheid*)prm_pActor; //�����̌^�ɃL���X�g
     *         int velo_mv = *((velo*)p1);                       //�L���v�`�����������̌^�ɖ߂�
     *         pEnemyXXX->getVecVehicle()->setMvVelo(velo_mv);         //�����ݒ�
     *     }
     *
     *     void processBehavior() {
     *         //�S�Ă̕ґ������o�[�ɉ����x�����o���B
     *         velo_mv_ = 3000; //���x
     *         listFollowers_.executeFunc(FormationXXX::order1, &velo_mv_, nullptr, nullptr);
     *     }
     * }
     *
     * </pre></code>
     * @param pFunc �v�f�l�Ɏ��s���������֐��B�p�����[�^��(T*, void*, void*, void*) �Œ�BT* �v�f�̒l���n�����B
     * @param prm1 �n�������������̂P
     * @param prm2 �n�������������̂Q
     * @param prm3 �n�������������̂R
     */
    void executeFunc(void (*pFunc)(T*, void*, void*, void*), void* prm1, void* prm2, void* prm3) {
        if (_pElemActive == nullptr) {
            return;
        } else {
            Elem* pElem = _pElem_first;
            int n = _num_elem;
            for (int i = 0; i < n; i++) {
                pFunc((T*) pElem->_pValue, prm1, prm2, prm3);
                pElem = pElem->_pNext;
            }
            return;
        }
    }
};

//////////////////////////////////////////////////////////////////

/**
 * ��������͎�����
 */

template<class T>
RingLinkedList<T>::RingLinkedList(int prm_extend_relation_num) :
        Object() {
    _num_elem = 0;
    _pElemActive = nullptr;
    _pElem_first = nullptr;
    _relation_num = prm_extend_relation_num;
    _papLinearVal = nullptr;
}


template<class T>
void RingLinkedList<T>::addNext(const T* prm_pNew,
        bool prm_is_delete_value) {
//#ifdef MY_DEBUG
//    if (prm_pNew == nullptr) {
//        throwCriticalException("[RingLinkedList::addNext()] Error! ������nullptr�ł�");
//    }
//#endif
    Elem* pElem = NEW Elem(prm_pNew, _relation_num, prm_is_delete_value);
    if (_pElem_first == nullptr) {
        //�ŏ��̂P��
        pElem->_is_last_flg = true;
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElem_first = pElem;
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
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

template<class T>
void RingLinkedList<T>::addPrev(const T* prm_pNew,
        bool prm_is_delete_value) {
//#ifdef MY_DEBUG
//    if (prm_pNew == nullptr) {
//        throwCriticalException("[RingLinkedList::addPrev()] Error! ������nullptr�ł�");
//    }
//#endif
    Elem* pElem = NEW Elem(prm_pNew, _relation_num, prm_is_delete_value);
    if (_pElem_first == nullptr) {
        //�ŏ��̂P��
        pElem->_is_last_flg = true;
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElem_first = pElem;
    } else {
        Elem* pMy = _pElemActive;
        if (pMy->_is_first_flg) {
            pMy->_is_first_flg = false;
            pElem->_is_first_flg = true;
            pElem->_is_last_flg = false;
            _pElem_first = pElem;
        }
        Elem* pMyPrev = _pElemActive->_pPrev;
        pMyPrev->_pNext = pElem;
        pElem->_pPrev = pMyPrev;
        pElem->_pNext = pMy;
        pMy->_pPrev = pElem;
    }
    _num_elem++;
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

template<class T>
void RingLinkedList<T>::addLast(const T* prm_pNew,
        bool prm_is_delete_value) {
//#ifdef MY_DEBUG
//    if (prm_pNew == nullptr) {
//        throwCriticalException("[RingLinkedList::addLast()] Error! ������nullptr�ł�");
//    }
//#endif
    Elem* pElem = NEW Elem(prm_pNew, _relation_num, prm_is_delete_value);

    if (_pElem_first == nullptr) {
        //�ŏ��̂P��
        pElem->_is_first_flg = true;
        pElem->_is_last_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElem_first = pElem;
    } else {
        //�Q�ڈȍ~
        pElem->_is_first_flg = false;
        pElem->_is_last_flg = true;
        Elem* pLastElem = _pElem_first->_pPrev;
        pLastElem->_is_last_flg = false;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = _pElem_first;
        _pElem_first->_pPrev = pElem;
    }
    _num_elem++;
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

template<class T>
void RingLinkedList<T>::addFirst(const T* prm_pNew,
        bool prm_is_delete_value) {
//#ifdef MY_DEBUG
//    if (prm_pNew == nullptr) {
//        throwCriticalException("[RingLinkedList::addFirst()] Error! ������nullptr�ł�");
//    }
//#endif
    Elem* pElem = NEW Elem(prm_pNew, _relation_num, prm_is_delete_value);
    if (_pElem_first == nullptr) {
        //�ŏ��̂P��
        pElem->_is_first_flg = true;
        pElem->_is_last_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElem_first = pElem;
    } else {
        Elem* pFirstElem = _pElem_first;
        Elem* pLastElem = _pElem_first->_pPrev;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = pFirstElem;
        pFirstElem->_pPrev = pElem;
        pFirstElem->_is_first_flg = false;

        pElem->_is_first_flg = true;
        pElem->_is_last_flg = false;
        _pElem_first = pElem;
    }
    _num_elem++;
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

template<class T>
T* RingLinkedList<T>::next() {
    _pElemActive = _pElemActive->_pNext;
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* RingLinkedList<T>::prev() {
    _pElemActive = _pElemActive->_pPrev;
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* RingLinkedList<T>::first() {
    _pElemActive = _pElem_first;
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* RingLinkedList<T>::last() {
    _pElemActive = _pElem_first->_pPrev; //��Ȃ̂ŁA�擪�̈�O�͖���
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* RingLinkedList<T>::current(int n) {
    Elem* pElem = _pElem_first;
    for (int i = 0; i < n; i++) {
        pElem = pElem->_pNext;
    }
    _pElemActive = pElem;
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* RingLinkedList<T>::gotoRelation(int prm_connection_index) {
#ifdef MY_DEBUG
    if (_relation_num-1 < prm_connection_index) {
        throwCriticalException("RingLinkedList<T>::gotoRelation �ڑ��v�f�ԍ��͈̔͊O�ł��Bprm_connection_index="<<prm_connection_index);
    }
#endif
    _pElemActive = _pElemActive->_papRelation[prm_connection_index];
#ifdef MY_DEBUG
    if (_pElemActive == nullptr) {
        throwCriticalException("RingLinkedList<T>::gotoRelation �ڑ��v�f�ԍ��̗v�f�����ݒ�ł��Bprm_connection_index="<<prm_connection_index);
    }
#endif
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* RingLinkedList<T>::getNext() const {
    return (T*) _pElemActive->_pNext->_pValue;
}

template<class T>
T* RingLinkedList<T>::getNext(int n) const {
#ifdef MY_DEBUG
    if (n < 0) {
        throwCriticalException("RingLinkedList<T>::getNext �����ɂ͐��̐�����ݒ肷��K�v������܂� n="<<n);
    }
#endif
    if (_papLinearVal) { //�C���f�b�N�X����
        int i = _pElemActive->_idx + n;
        return (T*) _papLinearVal[(i >= _num_elem ? (i % _num_elem) : i)];
    } else { //�C���f�b�N�X�Ȃ�
        Elem* pElem = _pElemActive;
        int x = n % _num_elem;
        for (int i = 0; i < x; i++) {
            pElem = pElem->_pNext;
        }
        return (T*) pElem->_pValue;
    }
}

//template<class T>
//T* RingLinkedList<T>::getFromCurrent(int n) const {
//    if (_papLinearVal) { //�C���f�b�N�X����
//      int i = _pElemActive->_idx + n;
//      if (i >= _num_elem) {
//          return (T*)_papLinearVal[(i % _num_elem)];
//      } else if (i < 0) {
//          int x = (-i) % _num_elem;
//          if (x == 0) {
//              return (T*)_papLinearVal[0];
//          } else {
//              return (T*)_papLinearVal[_num_elem - x];
//          }
//
//      } else {
//          return (T*)_papLinearVal[i];
//      }
//    } else { //�C���f�b�N�X�Ȃ�
//      Elem* pElem = _pElemActive;
//      if (n > 0) {
//          for (int i = 0; i < n; i++) {
//              pElem = pElem->_pNext;
//          }
//      } else if (n < 0) {
//          for (int i = 0; i > n; i--) {
//              pElem = pElem->_pPrev;
//          }
//      }
//        return (T*)pElem->_pValue;
//    }
//}

template<class T>
T* RingLinkedList<T>::getFromFirst(int n) const {
#ifdef MY_DEBUG
    if (n < 0) {
        throwCriticalException("RingLinkedList<T>::getFromFirst �����ɂ͐��̐�����ݒ肷��K�v������܂� n="<<n);
    }
#endif
    Elem* pElem = _pElem_first;
    if (pElem == nullptr) {
        return nullptr;
    }
    if (_papLinearVal) { //�C���f�b�N�X����
        return (T*) _papLinearVal[(n >= _num_elem ? (n % _num_elem) : n)];
    } else { //�C���f�b�N�X�Ȃ�
        int x = n % _num_elem;
        for (int i = 0; i < x; i++) {
            pElem = pElem->_pNext;
        }
        return (T*) pElem->_pValue;
    }
}

template<class T>
T* RingLinkedList<T>::getPrev() const {
    return (T*) _pElemActive->_pPrev->_pValue;
}

template<class T>
T* RingLinkedList<T>::getPrev(int n) const {
#ifdef MY_DEBUG
    if (n < 0) {
        throwCriticalException("RingLinkedList<T>::getPrev �����ɂ͐��̐�����ݒ肷��K�v������܂� n="<<n);
    }
#endif
    if (_papLinearVal) { //�C���f�b�N�X����
        int i = _pElemActive->_idx - (n % _num_elem);
        return (T*) _papLinearVal[(i >= 0 ? i : _num_elem + i)];
    } else { //�C���f�b�N�X�Ȃ�
        Elem* pElem = _pElemActive;
        int x = n % _num_elem;
        for (int i = 0; i < x; i++) {
            pElem = pElem->_pPrev;
        }
        return (T*) pElem->_pValue;
    }
}

template<class T>
T* RingLinkedList<T>::getFirst() const {
    return (T*) _pElem_first->_pValue;
}

template<class T>
T* RingLinkedList<T>::getLast() const {
    return (T*) _pElem_first->_pPrev->_pValue; //��Ȃ̂ŁA�擪�̈�O�͖���
}

template<class T>
T* RingLinkedList<T>::getCurrent() const {
    if (_pElemActive == nullptr) {
        return nullptr;
    } else {
        return (T*) _pElemActive->_pValue;
    }
}

template<class T>
T* RingLinkedList<T>::getRelation(int prm_connection_index) const {
#ifdef MY_DEBUG
    if (_relation_num-1 < prm_connection_index) {
        throwCriticalException("RingLinkedList<T>::getRelation �ڑ��v�f�ԍ��͈̔͊O�ł��Bprm_connection_index="<<prm_connection_index);
    }
#endif
    Elem* pE = _pElemActive->_papRelation[prm_connection_index];
    if (pE) {
        return (T*) pE->_pValue;
    } else {
        return nullptr;
    }
}

template<class T>
int RingLinkedList<T>::getCurrentIndex() const {
    if (_pElemActive == nullptr) {
        return -1;
    } else {
        if (_papLinearVal) {
            return _pElemActive->_idx;
        } else {
            //�]���̕��@
            Elem* pElem = _pElem_first;
            int n = _num_elem;
            for (int i = 0; i < n; i++) {
                if (pElem == _pElemActive) {
                    return i;
                } else {
                    pElem = pElem->_pNext;
                }
            }
            return -1;
        }
    }
}

template<class T>
bool RingLinkedList<T>::isLast() const {
    return _pElemActive->_is_last_flg;
}

template<class T>
bool RingLinkedList<T>::isFirst() const {
    return _pElemActive->_is_first_flg;
}

template<class T>
T* RingLinkedList<T>::replace(const T* prm_pVal) {
#ifdef MY_DEBUG
    if (_pElemActive == nullptr) {
        throwCriticalException("RingLinkedList<T>::replace �J�����g�v�f�����݂��܂���");
    }
#endif
    const T* pValue = _pElemActive->_pValue;
    bool is_delete_value = _pElemActive->_is_delete_value;
    _pElemActive->_pValue = prm_pVal;

    if (_papLinearVal) {
        _papLinearVal[_pElemActive->_idx] = prm_pVal;
    }

    if (is_delete_value) {
        GGAF_DELETE(pValue);
        return nullptr;
    } else {
        return (T*) pValue;
    }

}

template<class T>
T* RingLinkedList<T>::remove() {
    Elem* pMy = _pElemActive;
    if (pMy) {
        if (_papLinearVal) {
            //�v�f�����ύX�����̂ŃC���f�b�N�X�͖������ɂ���
            GGAF_DELETEARR(_papLinearVal);
        }
        const T* pRetValue =  nullptr;
        _num_elem--;
        if (pMy->_is_first_flg && pMy->_is_last_flg) {
            //�v�f���P�̏ꍇ
            _pElemActive = nullptr;
            _pElem_first = nullptr;
            pRetValue = pMy->_pValue;
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
                _pElem_first = pMyNext;
                pMyNext->_is_first_flg = true; //���̗v�f���V�����擪�ɂȂ�
            }
            _pElemActive = pMyNext; //�J�����g�v�f�� next �ɍX�V�B
            pRetValue = pMy->_pValue;
        }
        if (pMy->_is_delete_value) {
            GGAF_DELETE(pMy); //~Elem() pRetValue �� delete�����
            return nullptr;
        } else {
            GGAF_DELETE(pMy); //~Elem() pRetValue �� delete����Ȃ�
            return (T*) pRetValue;
        }
    } else {
        return nullptr;
    }
}

template<class T>
void RingLinkedList<T>::removeAll() {
    if (_papLinearVal) {
        //�v�f�����ύX�����̂ŃC���f�b�N�X�͖����ɂ���
        GGAF_DELETEARR(_papLinearVal);
    }

    Elem* pElem = _pElem_first;
    while (pElem) {
        if (pElem->_is_last_flg) {
            GGAF_DELETE(pElem);
            break;
        } else {
            Elem* pTmp = pElem->_pNext;
            GGAF_DELETE(pElem);
            pElem = pTmp;
        }
    }
    _num_elem = 0;
    _pElemActive = nullptr;
    _pElem_first = nullptr;
}

template<class T>
int RingLinkedList<T>::indexOf(const T* prm_pVal) const {
    if (_pElem_first == nullptr) {
        return -1;
    }
    int r = 0;
    Elem* pElem = _pElem_first;
    while (true) {
        if (pElem->_pValue == prm_pVal) {
            return r;
        } else {
            if (pElem->_is_last_flg) {
                break;
            } else {
                pElem = pElem->_pNext;
                r++;
            }
        }
    }
    return -1;
}

template<class T>
int RingLinkedList<T>::length() const {
    return _num_elem;
}

template<class T>
void RingLinkedList<T>::createIndex() {
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
    Elem* p = _pElem_first;
    int len = length();
    _papLinearVal = NEW const T*[len];
    for (int i = 0; i < len; i++) {
        p->_idx = i;
        _papLinearVal[i] = p->_pValue;
        p = p->_pNext;
    }
}

template<class T>
RingLinkedList<T>::~RingLinkedList() {
    _TRACE_("RingLinkedList<T>::~RingLinkedList() _num_elem="<<_num_elem);
    //�����Ɏq������ꍇ
    if (_pElem_first) {
        //�܂��q��delete
        if (_num_elem == 1) {
            //�q�v�f�͂P�̏ꍇ
            GGAF_DELETE(_pElem_first);
            _pElem_first = nullptr;
            _pElemActive = nullptr;
            _num_elem = 0;

        } else {
            //�q�v�f�͂Q�ȏ�̏ꍇ
            Elem* pLast = _pElem_first->_pPrev;
            Elem* pLastPrev = pLast->_pPrev;
            while (true) {
                GGAF_DELETE(pLast); //��������delete
                if (pLastPrev->_is_first_flg) {
                    GGAF_DELETE(_pElem_first); //pChildLastPrev == _pChildFirst �ł���
                    _pElem_first = nullptr;
                    _pElemActive = nullptr;
                    _num_elem = 0;
                    break;
                }
                pLast = pLastPrev;
                pLastPrev = pLastPrev->_pPrev;
            }
        }
    }

    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

}
#endif /*GGAF_CORE_LINKEDLISTRING_H_*/