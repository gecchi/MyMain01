#ifndef GGAFLINKEDLISTRING_H_
#define GGAFLINKEDLISTRING_H_
/**
 * ����N���X�v�f�̊�o�����A�����X�g���\�z����e���v���[�g�ł��B.
 *
 * <B>�y����z</B><BR>
 * <PRE>
 * �@���̂o�̥��
 * �@�@�@��
 * (�d)�̂`�̂a�̂b�̂c�̂d��(�`)
 * �@�@�@�@�@�@���@����������������������������
 * �@�@�@�@�@�@���@�@�@�@�@�@�@�@�@�@�@�@�@�@��
 * �@�@�@(�g)�̂e�̂f�̂g��(�e)�@�@�@�@(�k)�̂h�̂i�̂j�̂k��(�h)
 * �@�@�@�@�@�@�@�@���@���@�@�@�@�@�@�@�@�@�@�@�@���@�@�@��
 * �@�@�@�@�@�@�@�@�@����@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���
 * </PRE>
 * ��}�̂悤�ȍ\�����̂鎖���o���܂��B<BR>
 * ���i�́u(�d)�̂`�̂a�̂b�̂c�̂d��(�`)�v�͗v�f�i�C���X�^���X�j����̑o�����Ń|�C���^���w�������Ă��鎖�������Ă��܂��B<BR>
 * ���[�́u(�d)�v�Ɓu(�`)�v�́A�A�����X�g�̐擪�Ɩ������A���݂��A�����Ă��鎖�𖾎����Ă��܂��B(��ɂȂ��Ă���)<BR>
 * ��}�Ŏ��g�̃C���X�^���X���u�b�v�Ƃ����ꍇ�A�u�b�v�̎��_����e�v�f�����̂悤�Ɍď́A�y�ђ�`���邱�ƂƂ��܂��B<BR>
 * <TABLE BORDER="1">
 * <TR><TD>�u�b�v</TD><TD>���v�f</TD></TR>
 * <TR><TD>�u�`�v</TD><TD>�擪(First)�v�f�B ���v�f����������A�����X�g�̐擪�Ƃ����Ӗ��ł��B�u�`�v �� _isFirst �� true �ɂȂ��Ă��܂��B(���v�f�� false)</TD></TR>
 * <TR><TD>�u�d�v</TD><TD>����(Last)�v�f�B ���v�f����������A�����X�g�̍Ō�Ƃ����Ӗ��ł��B�u�d�v �� _isLast �� true �ɂȂ��Ă��܂��B(���̗v�f�� false)</TD></TR>
 * <TR><TD>�u�c�v</TD><TD>��(Next)�v�f�B��}�ł͍�����E���������Ƃ��Ă��܂��B_pNext�|�C���^���w���Ă���v�f�ɂȂ�܂��B</TD></TR>
 * <TR><TD>�u�a�v</TD><TD>�O(Prev)�v�f�B_pPrev ���w���Ă���|�C���^�ł��B</TD></TR>
 * <TR><TD>�u�o�v</TD><TD>�e(Parent)�v�f�B���v�f����������A�����X�g�̂P��̊K�w�̗v�f�ł��B_pParent �|�C���^���w���Ă���v�f�ł��B�S�Ă̗v�f�͒��߂̐e�v�f�̃|�C���^�������Ă��܂��B</TD></TR>
 * <TR><TD>�u�h�C�i�C�j�C�k�v</TD><TD>�u�b�v�q(Sub)�v�f�ƌĂт܂��B</TD></TR>
 * <TR><TD>�u�h�v</TD><TD> �q�v�f�̒��œ��Ɂu�h�v�͎q�v�f�̐擪�v�f�ƌĂсA���v�f�� _pSubFirst �|�C���^���w���Ă���v�f�ƂȂ��Ă��܂��B</TD></TR>
 * </TABLE>
 * <BR>
 *
 * <B>�y���̑��p��⑫�z</B>
 * <TABLE BORDER="1">
 * <TR>
 * <TD>�u���v�f�v�u���v</TD>
 * <TD>���v�f�ȊO�̗v�f�S�Ă��w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�z���v�f�v�u�z���v</TD>
 * <TD>�v�f���m�̃c���[�K�w�\����ɂ����āA���v�f<B>��</B>�Ԃ牺����S�Ă̗v�f���w���Ă��܂��B���v�f�͊܂܂�܂���B</TD>
 * </TR><TR>
 * <TD>�u���c���[�v</TD>
 * <TD>���v�f�𒸓_�Ƃ���A���v�f�{�z���v�f�ō\�������c���[�\�����̂��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�v�f�v</TD>
 * <TD>���v�f�𒸓_�Ƃ���A���v�f�{�z���v�f�ō\�������c���[�\���̗v�f�S�Ă��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u�������c���[�v</TD>
 * <TD>���v�f���܂܂�Ă���c���[�\���̑S�Ă��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u�v�f�N���X�v</TD>
 * <TD>GgafLinkedListRing�����N���X�A������GgafLinkedListRing�����N���X�𒼐ځE�Ԑڌp�����Ă���N���X���w���܂��B</TD>
 * </TR><TR>
 * <TD>�u��ʁv�u���ʁv</TD>
 * <TD>�v�f�N���X�̃N���X�p���֌W��\���Ă��܂��B
 * �N���X�p���֌W�̕\���́u�X�[�p�[�v�u�T�u�v���́u�e�v�u�q�v�ƌ��킸��<B>�u��ʁv�u���ʁv</B>�œ��ꂷ�邱�Ƃɂ��܂��B<BR>
 * �u�e�v�u�q�v�ƕ\�������ꍇ�͂��ꂼ��e�v�f�A�q�v�f�̃c���[�\���̎���\��������̂Ƃ��܂��B�i��₱�����ł��ˁj<BR>
 * ���၄���ʂŎ������ꂽ����B</TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
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


		Elem(T* prm_pValue){
			_pValue = prm_pValue;
			_pNext = _pPrev = NULL;
			_isFirst = _isLast = false;
		};

		T* getVal() {
			return _pValue;
		}

		Elem* getNext() {
			return _pNext;
		};

		Elem* getPrev() {
			return _pPrev;
		};

		/**
		 * �v�f���擪�v�f�����ׂ� .
		 * @return	bool true:�擪�v�f�^false:�擪�v�f�ł͂Ȃ�
		 */
		bool isFirst() {
			return _isFirst;
		};

		/**
		 * �v�f�������v�f�����ׂ� .
		 * @return	bool true:�����v�f�^false:�����v�f�ł͂Ȃ�
		 */
		bool isLast() {
			return _isLast;
		};

		~Elem(){
			DELETE_IMPOSSIBLE_NULL(_pValue);
		};

	};

public:

	/** �擪�v�f */
	Elem* _pFirst;

	/** �A�N�e�B�u�v�f */
	Elem* _pActive;

	/** �v�f�� */
	int _iElemNum;

	/**
	 * �R���X�g���N�^
	 * @param prm_pElem �R�s�[�\�ȍ\���̂�N���X�̃|�C���^
	 */
//	GgafLinkedListRing(int prm_iNum);

	GgafLinkedListRing();

	/**
	 * �f�X�g���N�^�B���c���[�v�f��������܂��B .
	 * ���v�f���q�v�f�����ꍇ�A�q�v�f��������Ă��玩�g���J������B<BR>
	 * ���v�f���ŏI�v�f�������ꍇ�A���v�f��A�����痣�E���A�O�v�f���ŏI�v�f�t���O���Z�b�g���āA���g���������B<BR>
	 * ���v�f���擪�v�f�������ꍇ�A���v�f��A�����痣�E���A���v�f��e�v�f �� �q�v�f�̐擪�v�f�A����� �擪�v�f�t���O���Z�b�g���A���g���������B<BR>
	 * ���v�f�����ԗv�f�������ꍇ�A���ׂ̗v�f�̘A�����č\�z������������B<BR>
	 * ���v�f�̘A�������g���w���i�P�l�ڂ����������j�ꍇ�A�e�v�f �� �q�v�f�̐擪�v�f�i�������w���Ă����j��NULL�ɕύX���Ă���������B<BR>
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
	 * (�j)�̂h�̂i�̂j��(�h)
	 * -----------------------
	 *        �� ��}�͂R�v�f����Ȃ�󃊃X�g�ł��B�u�j�v�������v�f�ł��B
	 *        �� �����ɗv�f�u�w�vaddLast ����Ɖ��}�̂悤�ȏ�ԂɂȂ�A
	 *        �� �v�f�u�w�v���V���Ȗ����v�f�ɂȂ�܂��B
	 * ----------------�u���s��v
	 * (�w)�̂h�̂i�̂j�̂w��(�h)
	 * -----------------------
	 * </PRE>
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
GgafLinkedListRing<T>::GgafLinkedListRing() : GgafObject() {
	_iElemNum = 0;
	_pActive = NULL;
	_pFirst = NULL;
}

template<class T>
T* GgafLinkedListRing<T>::get() {
	if (_pActive == NULL) {
		throw_GgafCriticalException("[GgafLinkedListRing::get()] Error! �A�N�e�B�u�v�f��NULL�ł�");
	}
	return _pActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::next() {
	if (_pActive == NULL) {
		throw_GgafCriticalException("[GgafLinkedListRing::next()] Error! �A�N�e�B�u�v�f��NULL�ł�");
	}
	_pActive = _pActive -> _pNext;
	return _pActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::prev() {
	if (_pActive == NULL) {
		throw_GgafCriticalException("[GgafLinkedListRing::prev()] Error! �A�N�e�B�u�v�f��NULL�ł�");
	}
	_pActive = _pActive -> prev;
	return _pActive->_pValue;
}

template<class T>
void GgafLinkedListRing<T>::addLast(T* prm_pSub) {
	if (prm_pSub == NULL) {
		throw_GgafCriticalException("[GgafLinkedListRing::addLast()] Error! ������NULL�ł�");
	}
	static Elem* pElem;
	static Elem* pLastElem;
	pElem = NEW Elem(prm_pSub);

	pElem -> _isLast = true;

	if (_pFirst == NULL) {
		//�ŏ��̂P��
		pElem->_isFirst = true;
		pElem->_pNext = pElem;
		pElem->_pPrev = pElem;
		_pActive = pElem;
	} else {
		//�Q�ڈȍ~
		pElem -> _isFirst = false;
		pLastElem = _pFirst->_pPrev;
		pLastElem->_isLast = false;
		pLastElem->_pNext = pElem;
		pElem->_pPrev = pLastElem;
		pElem->_pNext = _pFirst;
		_pFirst->_pPrev = pElem;
	}
	_iElemNum++;

}

template<class T>
bool GgafLinkedListRing<T>::isLast() {
	return _pActive->_isLast;
}

template<class T>
bool GgafLinkedListRing<T>::isFirst() {
	return _pActive->_isFirst;
}

template<class T>
GgafLinkedListRing<T>::~GgafLinkedListRing() {
	//�����Ɏq������ꍇ
	if (_pFirst) {
		//�܂��q��delete
		if (_iElemNum == 1) {
			//�q�v�f�͂P�̏ꍇ
			DELETE_IMPOSSIBLE_NULL(_pFirst);
			_pFirst = NULL;
			_pActive = NULL;
			_iElemNum = 0;

		} else {
			//�q�v�f�͂Q�ȏ�̏ꍇ
			Elem* pLast = _pFirst -> _pPrev;
			Elem* pLastPrev = pLast -> _pPrev;
			while(true) {
				DELETE_IMPOSSIBLE_NULL(pLast); //��������delete
				if (pLastPrev -> _isFirst) {
					DELETE_IMPOSSIBLE_NULL(_pFirst); //pSubLastPrev == _pSubFirst �ł���
					_pFirst = NULL;
					_pActive = NULL;
					_iElemNum = 0;
					break;
				}
				pLast = pLastPrev;
				pLastPrev = pLastPrev -> _pPrev;
			}
		}
	}


//	_TRACE_("...deleted GgafLinkedListRing("<<_name<<") ID="<<_id);
	_TRACE_("...deleted GgafLinkedListRing()");
}

#endif /*GGAFLINKEDLISTRING_H_*/
