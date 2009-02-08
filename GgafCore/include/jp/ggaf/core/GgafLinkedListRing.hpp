#ifndef GGAFLINKEDLISTRING_H_
#define GGAFLINKEDLISTRING_H_
namespace GgafCore {

/**
 * ����N���X�v�f�̊�o�����A�����X�g���\�z����e���v���[�g�ł��B.
 *
 * <B>�y����z</B><BR>
 * <PRE>
 * (�d)�̂`�̂a�̂b*�̂c�̂d��(�`)
 * </PRE>
 * �Ⴆ�΁A�T�̗v�f�ŏ�}�̂悤�ȍ\�����̂鎖���o���܂��B<BR>
 * �v�f�i�C���X�^���X�j����̑o�����Ń|�C���^���w�������Ă��鎖�������Ă��܂��B<BR>
 * �`��擪�v�f�A�d�𖖔��v�f�A*�̓A�N�e�B�u�v�f(�J�[�\�����w���Ă���悤�Ȃ���)������킵�܂��B<BR>
 * ���[�́u(�d)�v�Ɓu(�`)�v�Ƃ����\�L�́A�A�����X�g�̐擪�Ɩ������A���݂��A�����Ă��鎖�𖾎����Ă��܂��B(��ɂȂ��Ă���)<BR>
 * <BR>
 * @version 1.00
 * @since 2008/12/20
 * @author Masatoshi Tsuge
 */

template<class T>
class GgafLinkedListRing : public GgafObject {

protected:

    class Elem {
    public:
        /** �v�f�̒l */
        T* _pValue;
        /** ���v�f */
        Elem* _pNext;
        /** �O�v�f */
        Elem* _pPrev;
        /** �擪�v�f�t���O (���v�f���擪�v�f�̏ꍇ true)*/
        bool _isFirst;
        /** �����v�f�t���O (���v�f�������v�f�̏ꍇ true)*/
        bool _isLast;

        /**
         * �R���X�g���N�^
         * @param prm_pValue �l�|�C���^
         */
        Elem(T* prm_pValue) {
            _pValue = prm_pValue;
            _pNext = _pPrev = NULL;
            _isFirst = _isLast = false;
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
            return _isFirst;
        }

        /**
         * �v�f�������v�f�����ׂ� .
         * @return	bool true:�����v�f�^false:�����v�f�ł͂Ȃ�
         */
        bool isLast() {
            return _isLast;
        }

        /**
         * �f�X�g���N�^.
         * �����ێ�����v�f�̒l���J������܂��B<BR>
         */
        ~Elem() {
            DELETE_IMPOSSIBLE_NULL(_pValue);
        }

    };

public:

    /** �擪�v�f */
    Elem* _pElemFirst;

    /** �A�N�e�B�u�v�f */
    Elem* _pElemActive;

    /** �v�f�� */
    int _iElemNum;

    /**
     * �R���X�g���N�^
     * @param prm_pElem �R�s�[�\�ȍ\���̂�N���X�̃|�C���^
     */
    //	GgafLinkedListRing(int prm_iNum);

    GgafLinkedListRing();

    /**
     * �f�X�g���N�^.
     * �����ێ�����v�f�̊�o�����A�����X�g���J������܂��B<BR>
     */
    virtual ~GgafLinkedListRing();

    //
    //	/**
    //	 * ���c���[�v�f��A�����X�g����؂藣���A�Ɨ�����B .
    //	 * �؂藣���ꌊ���J���������́A����̗v�f�����𖄂߂܂��i�ĘA�����܂��j<BR>
    //	 * ���v�f�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
    //	 * @return	T* ���v�f�̃|�C���^
    //	 */
    //	virtual T* tear();
    //
    //	/**
    //	 * �A�N�e�B�u�v�f���A�ŏI�v�f�ֈړ����� .
    //	 *<PRE>
    //	 * ----------------�u���s�O�v
    //	 * �i�d�j�̂`�̂a�̂b*�̂c�̂d�́i�`�j
    //	 * -----------------------
    //	 *        �� ��}�ŃA�N�e�B�u�v�f���u�b�v�Ƃ����ꍇ�A���̂悤�ȏ�ԂɂȂ�
    //	 *        �� ( * �̓A�N�e�B�u�v�f�ł��鎖��\���܂��B)
    //	 * ----------------�u���s��v
    //	 * �i�d�j�̂`�̂a�̂c*�̂d�̂b�́i�`�j
    //	 * -----------------------
    //	 * </PRE>
    //	 */
    //	virtual void moveLast();
    //
    //	/**
    //	 * �A�N�e�B�u�v�f���A�擪�v�f�ֈړ����� .
    //	 *<PRE>
    //	 * ----------------�u���s�O�v
    //	 * (�d)�̂`�̂a�̂b*�̂c�̂d��(�`)
    //	 * -----------------------
    //	 *        �� ��}�ŃA�N�e�B�u�v�f���u�b�v�Ƃ����ꍇ�A���̂悤�ȏ�ԂɂȂ�
    //	 *        �� ( * �̓A�N�e�B�u�v�f�ł��鎖��\���܂��B)
    //	 * ----------------�u���s��v
    //	 * (�d)�̂b�̂`�̂a*�̂c�̂d��(�b)
    //	 * -----------------------
    //	 * </PRE>
    //	 */
    //	virtual void moveFirst();


    /**
     * �A�N�e�B�u�v�f�̒l���擾����B
     * @return	�A�N�e�B�u�v�f
     */
    T* get();

    /**
     * �A�N�e�B�u�v�f����i�߂���A���̗v�f�̒l���擾����B
     * @return ���̗v�f
     */
    T* next();

    /**
     * �A�N�e�B�u�v�f����߂�����A���̗v�f�̒l���擾����B
     * @return �O�̗v�f
     */
    T* prev();

    bool isLast();

    bool isFirst();

    //
    //	/**
    //	 * �A�N�e�B�u�v�f����i�߂���A���̗v�f�̒l���擾����B
    //	 * @return	T*	���v�f
    //	 */
    //	virtual T* nextVal();
    //
    //	/**
    //	 * �A�N�e�B�u�v�f����߂�����A���̗v�f�̒l���擾����B
    //	 * @return	T*	�O�v�f
    //	 */
    //	virtual T* prevVal();
    //
    /**
     * �����v�f���A����(_isLast �� true)�Ƃ��Ēǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B<BR>
     *<PRE>
     * ----------------�u���s�O�v
     * (�j)�̂h*�̂i�̂j��(�h)
     * -----------------------
     *        �� ��}�͂R�v�f����Ȃ�󃊃X�g�ł��B�u�j�v�������v�f�ł��B
     *        �� �����ɗv�f�u�w�vaddLast ����Ɖ��}�̂悤�ȏ�ԂɂȂ�A
     *        �� �v�f�u�w�v���V���Ȗ����v�f�ɂȂ�܂��B
     * ----------------�u���s��v
     * (�w)�̂h*�̂i�̂j�̂w��(�h)
     * -----------------------
     * </PRE>
     * ���߂Ă�addLast�́A�����̃I�u�W�F�N�g�͂ɃA�N�e�B�u�v�f�Ȃ�A<BR>
     * �Q��ڈȍ~addLast���s�Ȃ��Ă��ɃA�N�e�B�u�v�f�͉e������܂���B<BR>
     *
     * @param	prm_pSub	�C���X�^���X�����ςݗv�f�̃|�C���^
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
    _iElemNum = 0;
    _pElemActive = NULL;
    _pElemFirst = NULL;
}

template<class T>
T* GgafLinkedListRing<T>::get() {
    if (_pElemActive == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::get()] Error! �A�N�e�B�u�v�f��NULL�ł�");
    }
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::next() {
    if (_pElemActive == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::next()] Error! �A�N�e�B�u�v�f��NULL�ł�");
    }
    _pElemActive = _pElemActive->_pNext;
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::prev() {
    if (_pElemActive == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::prev()] Error! �A�N�e�B�u�v�f��NULL�ł�");
    }
    _pElemActive = _pElemActive->prev;
    return _pElemActive->_pValue;
}

template<class T>
void GgafLinkedListRing<T>::addLast(T* prm_pSub) {
    if (prm_pSub == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! ������NULL�ł�");
    }
    static Elem* pElem;
    static Elem* pLastElem;
    pElem = NEW Elem(prm_pSub);

    pElem->_isLast = true;

    if (_pElemFirst == NULL) {
        //�ŏ��̂P��
        pElem->_isFirst = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        //�Q�ڈȍ~
        pElem->_isFirst = false;
        pLastElem = _pElemFirst->_pPrev;
        pLastElem->_isLast = false;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = _pElemFirst;
        _pElemFirst->_pPrev = pElem;
    }
    _iElemNum++;

}

template<class T>
bool GgafLinkedListRing<T>::isLast() {
    return _pElemActive->_isLast;
}

template<class T>
bool GgafLinkedListRing<T>::isFirst() {
    return _pElemActive->_isFirst;
}

template<class T>
GgafLinkedListRing<T>::~GgafLinkedListRing() {
    //�����Ɏq������ꍇ
    if (_pElemFirst) {
        //�܂��q��delete
        if (_iElemNum == 1) {
            //�q�v�f�͂P�̏ꍇ
            DELETE_IMPOSSIBLE_NULL(_pElemFirst);
            _pElemFirst = NULL;
            _pElemActive = NULL;
            _iElemNum = 0;

        } else {
            //�q�v�f�͂Q�ȏ�̏ꍇ
            Elem* pLast = _pElemFirst->_pPrev;
            Elem* pLastPrev = pLast->_pPrev;
            while (true) {
                DELETE_IMPOSSIBLE_NULL(pLast); //��������delete
                if (pLastPrev->_isFirst) {
                    DELETE_IMPOSSIBLE_NULL(_pElemFirst); //pSubLastPrev == _pSubFirst �ł���
                    _pElemFirst = NULL;
                    _pElemActive = NULL;
                    _iElemNum = 0;
                    break;
                }
                pLast = pLastPrev;
                pLastPrev = pLastPrev->_pPrev;
            }
        }
    }

    //_TRACE_("...deleted GgafLinkedListRing()");
}

}
#endif /*GGAFLINKEDLISTRING_H_*/
