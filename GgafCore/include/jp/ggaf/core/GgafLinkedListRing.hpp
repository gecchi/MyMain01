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
        bool _isFirstFlg;
        /** �����v�f�t���O (���v�f�������v�f�̏ꍇ true)*/
        bool _isLastFlg;

        /**
         * �R���X�g���N�^
         * @param prm_pValue �l�|�C���^
         */
        Elem(T* prm_pValue) {
            _pValue = prm_pValue;
            _pNext = _pPrev = NULL;
            _isFirstFlg = _isLastFlg = false;
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
            return _isFirstFlg;
        }

        /**
         * �v�f�������v�f�����ׂ� .
         * @return	bool true:�����v�f�^false:�����v�f�ł͂Ȃ�
         */
        bool isLast() {
            return _isLastFlg;
        }

        /**
         * �f�X�g���N�^.
         * �����ێ�����v�f�̒l���J������܂��B<BR>
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
     * �����ێ�����v�f�̊�o�����A�����X�g���J������܂��B<BR>
     */
    virtual ~GgafLinkedListRing();

    /**
     * �A�N�e�B�u�v�f�̒l�i�ێ����Ă�����e�j���擾���� .
     * @return	�A�N�e�B�u�v�f
     */
    T* get();

    /**
     * �A�N�e�B�u�v�f����i�߂���A���̗v�f�̒l���擾���� .
     * @return ���̗v�f
     */
    T* next();

    /**
     * �A�N�e�B�u�v�f����߂�����A���̗v�f�̒l���擾���� .
     * @return �O�̗v�f
     */
    T* prev();

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
     * �����v�f���A����(_isLastFlg �� true)�Ƃ��Ēǉ����� .
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

    pElem->_isLastFlg = true;

    if (_pElemFirst == NULL) {
        //�ŏ��̂P��
        pElem->_isFirstFlg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        //�Q�ڈȍ~
        pElem->_isFirstFlg = false;
        pLastElem = _pElemFirst->_pPrev;
        pLastElem->_isLastFlg = false;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = _pElemFirst;
        _pElemFirst->_pPrev = pElem;
    }
    _num_elem++;

}

template<class T>
bool GgafLinkedListRing<T>::isLast() {
    return _pElemActive->_isLastFlg;
}

template<class T>
bool GgafLinkedListRing<T>::isFirst() {
    return _pElemActive->_isFirstFlg;
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
                if (pLastPrev->_isFirstFlg) {
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
