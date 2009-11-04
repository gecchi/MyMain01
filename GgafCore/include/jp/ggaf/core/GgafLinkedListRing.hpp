#ifndef GGAFLINKEDLISTRING_H_
#define GGAFLINKEDLISTRING_H_
namespace GgafCore {

/**
 * �v�f�i����^�C���X�^���X�j�̊�o�����A�����X�g���\�z����e���v���[�g�ł��B.
 *
 * <B>�y����z</B><BR>
 * �A�����X�g�̐擪�Ɩ������q�����Ă���Ƃ������ƂŁA�w��x�ƕ\�����Ă��܂��B<BR>
 * <PRE STYLE="font-size:18px">
 * �y��z
 * (�d)�̂`�̂a�̂b*�̂c�̂d��(�`)
 * </PRE>
 * �Ⴆ�΁A�T�̗v�f�ŏ�}�̂悤�ȍ\�����̂鎖���o���܂��B<BR>
 * �w�́x�́A�v�f�i�C���X�^���X�j���m�����݂��|�C���^���w�������Ă��鎖�������Ă��܂��B<BR>
 * �`��擪�v�f�A�d�𖖔��v�f�A*�̓A�N�e�B�u�v�f(�J�[�\�����w���Ă���悤�Ȃ���)�ƌĂԂ��ƂƂ��܂��B<BR>
 * ���W�b�N���AaddLast() �ɂĈ�ԍŏ��ɒǉ������v�f���擪�v�f�ŁA�Ō�ɒǉ������v�f�������v�f�ƂȂ�܂��B<BR>
 * ���[�́u(�d)�v�Ɓu(�`)�v�Ƃ����\�L�́A�A�����X�g�̐擪�Ɩ������A���݂��A�����Ă��鎖�������Ă��܂��B(��ɂȂ��Ă���)<BR>
 * addLast()�łP�v�f�����ǉ������ꍇ�͎��̂悤�ɂȂ�܂��B<BR>
 * <PRE STYLE="font-size:18px">
 * �y��z
 * (�`)�̂`*��(�`)
 * </PRE>
 * �C�e���[�^�̂悤�Ȏg������z�肵�Ă��܂����A��}�������悤�ɁAhasNext() �ɂ�锻��͑��݂��܂���B<BR>
 * <BR>
 * @version 1.00
 * @since 2008/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafLinkedListRing : public GgafObject {

private:

    /**
     * ���ۂ̗v�f�l�����b�s���O���A�|�C���^��ǉ�
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

        /**
         * �R���X�g���N�^
         * @param prm_pValue �l�|�C���^
         */
        Elem(T* prm_pValue) {
            _pValue = prm_pValue;
            _pNext = _pPrev = NULL;
            _is_first_flg = _is_last_flg = false;
        }

        /**
         * �v�f�̒l���擾
         * @return �v�f�̒l
         */
        T* getVal() {
            return _pValue;
        }

        /**
         * ���̗v�f���擾
         * @return ���̗v�f
         */
        Elem* getNext() {
            return _pNext;
        }

        /**
         * �O�̗v�f���擾
         * @return �O�̗v�f
         */
        Elem* getPrev() {
            return _pPrev;
        }

        /**
         * �v�f���擪�v�f�����ׂ� .
         * @return	bool true:�擪�v�f�^false:�擪�v�f�ł͂Ȃ�
         */
        bool isFirst() {
            return _is_first_flg;
        }

        /**
         * �v�f�������v�f�����ׂ� .
         * @return	bool true:�����v�f�^false:�����v�f�ł͂Ȃ�
         */
        bool isLast() {
            return _is_last_flg;
        }

        /**
         * �f�X�g���N�^.
         * �����ێ�����v�f�̒l��delete����܂��B<BR>
         */
        ~Elem() {
            DELETE_IMPOSSIBLE_NULL(_pValue);
        }

    };

protected:
    /** �擪�v�f */
    Elem* _pElemFirst;

    /** �A�N�e�B�u�v�f */
    Elem* _pElemActive;

    /** �v�f�� */
    int _num_elem;

public:
    /**
     * �R���X�g���N�^
     */
    GgafLinkedListRing();

    /**
     * �f�X�g���N�^.
     * �����ێ�����v�f�̒l�́ANULL�Ŗ����ꍇ�A���ꂼ�� delete �ɂ��������܂��B<BR>
     * TODO:�f�X�g���N�^���A�v�f�� delete ���邩���Ȃ����w��ł���悤�ɂ������B
     * TODO:delete[] �₻�̑��̉�����@�ɑΉ�
     */
    virtual ~GgafLinkedListRing();


    /**
     * �A�N�e�B�u�v�f�̒l�i�ێ����Ă�����e�j���擾���� .
     * @return	�A�N�e�B�u�v�f�̒l
     */
    T* get();

    /**
     * �A�N�e�B�u�v�f����i�߂�B .
     * @return �A�N�e�B�u�v�f����i�߂���́A���̗v�f�̒l�B
     */
    T* next();

    /**
     * �A�N�e�B�u�v�f�̎��̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
     * @return ���̗v�f�̒l
     */
    T* getNext();

    /**
     * �A�N�e�B�u�v�f�̂��Ԗڂ̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
     * getNext(1) �́AgetNext() �Ɠ����ł��BgetNext(0) �� get()�Ɠ����ł��B
     * @param �C���f�b�N�X
     * @return �A�N�e�B�u�v�f���炎�Ԗڂ̗v�f
     */
    T* getNext(int n);

    /**
     * �A�N�e�B�u�v�f����߂��B .
     * @return �A�N�e�B�u�v�f����߂�����́A���̗v�f�̒l
     */
    T* prev();



    /**
     * �A�N�e�B�u�v�f���̂P�O�̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
     * @return �O�̗v�f�̒l
     */
    T* getPrev();
    /**
     * �A�N�e�B�u�v�f�̂��ԖڑO�̗v�f�̒l���擾����B�A�N�e�B�u�v�f�͕ω����Ȃ� .
     * getPrev(1) �́AgetPrev() �Ɠ����ł��BgetPrev(0) �� get()�Ɠ����ł��B
     * @param �C���f�b�N�X
     * @return �A�N�e�B�u�v�f���炎�ԖڑO�̗v�f
     */
    T* getPrev(int n);

    /**
     * �A�N�e�B�u�v�f�����X�g�̖����ł��邩���肷�� .
     * @return true:�����ł���^false:�����ł͖���
     */
    bool isLast();

    /**
     * �A�N�e�B�u�v�f�����X�g�̐擪�ł��邩���肷�� .
     * @return true:�����ł���^false:�����ł͖���
     */
    bool isFirst();

    /**
     * �A�N�e�B�u�v�f�ɒl���㏑���ݒ肷��B .
     * ���̗v�f�̒l�̉�����́A�߂�l���g�p���ČĂь��ōs���ĉ������B
     * @return �㏑�������O�̗v�f�̒l
     */
    virtual T* set(T* prm_pVal);

    /**
     * �����v�f���A����(_is_last_flg �� true)�Ƃ��Ēǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B<BR>
     *<PRE STYLE="font-size:18px">
     * ----------------�u���s�O�v
     * (�j)�̂h*�̂i�̂j��(�h)
     * -----------------------
     * �@�@�@�@�� ��}�͂R�v�f����Ȃ�󃊃X�g�ł��B�u�j�v�������v�f�ł��B
     * �@�@�@�@�� �����ɗv�f�u�w�vaddLast ����Ɖ��}�̂悤�ȏ�ԂɂȂ�A
     * �@�@�@�@�� �v�f�u�w�v���V���Ȗ����v�f�ɂȂ�܂��B
     * ----------------�u���s��v
     * (�w)�̂h*�̂i�̂j�̂w��(�h)
     * -----------------------
     * </PRE>
     * ���߂Ă�addLast�́A�����̃I�u�W�F�N�g�͂ɃA�N�e�B�u�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~addLast���s�Ȃ��Ă��ɃA�N�e�B�u�v�f�͉e������܂���B<BR>
     *
     * @param   prm_pSub    �C���X�^���X�����ςݗv�f�̃|�C���^
     */
    virtual void addLast(T* prm_pSub);

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
void GgafLinkedListRing<T>::addLast(T* prm_pSub) {
    if (prm_pSub == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! ������NULL�ł�");
    }
    static Elem* pElem;
    static Elem* pLastElem;
    pElem = NEW Elem(prm_pSub);

    pElem->_is_last_flg = true;

    if (_pElemFirst == NULL) {
        //�ŏ��̂P��
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        //�Q�ڈȍ~
        pElem->_is_first_flg = false;
        pLastElem = _pElemFirst->_pPrev;
        pLastElem->_is_last_flg = false;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = _pElemFirst;
        _pElemFirst->_pPrev = pElem;
    }
    _num_elem++;

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
