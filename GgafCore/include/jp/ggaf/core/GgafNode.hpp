#ifndef GGAFNODE_H_
#define GGAFNODE_H_
/**
 * �v�f���m����o�����A�����X�g�̃c���[�\������邱�Ƃ��ł���e���v���[�g�ł��B.
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
 * <TR><TD>�u�b�v</TD><TD>���m�[�h</TD></TR>
 * <TR><TD>�u�`�v</TD><TD>�擪(First)�m�[�h�B ���m�[�h����������A�����X�g�̐擪�Ƃ����Ӗ��ł��B�u�`�v �� _isFirst �� true �ɂȂ��Ă��܂��B(���m�[�h�� false)</TD></TR>
 * <TR><TD>�u�d�v</TD><TD>����(Last)�m�[�h�B ���m�[�h����������A�����X�g�̍Ō�Ƃ����Ӗ��ł��B�u�d�v �� _isLast �� true �ɂȂ��Ă��܂��B(���̃m�[�h�� false)</TD></TR>
 * <TR><TD>�u�c�v</TD><TD>��(Next)�m�[�h�B��}�ł͍�����E���������Ƃ��Ă��܂��B_pNext�|�C���^���w���Ă���v�f�ɂȂ�܂��B</TD></TR>
 * <TR><TD>�u�a�v</TD><TD>�O(Prev)�m�[�h�B_pPrev ���w���Ă���|�C���^�ł��B</TD></TR>
 * <TR><TD>�u�o�v</TD><TD>�e(Parent)�m�[�h�B���m�[�h����������A�����X�g�̂P��̊K�w�̃m�[�h�ł��B_pParent �|�C���^���w���Ă���v�f�ł��B�S�Ẵm�[�h�͒��߂̐e�m�[�h�̃|�C���^�������Ă��܂��B</TD></TR>
 * <TR><TD>�u�h�C�i�C�j�C�k�v</TD><TD>�u�b�v�q(Sub)�m�[�h�ƌĂт܂��B</TD></TR>
 * <TR><TD>�u�h�v</TD><TD> �q�m�[�h�̒��œ��Ɂu�h�v�͎q�m�[�h�̐擪�m�[�h�ƌĂсA���m�[�h�� _pSubFirst �|�C���^���w���Ă���v�f�ƂȂ��Ă��܂��B</TD></TR>
 * </TABLE>
 * <BR>
 *
 * <B>�y���̑��p��⑫�z</B>
 * <TABLE BORDER="1">
 * <TR>
 * <TD>�u���m�[�h�v�u���v</TD>
 * <TD>���m�[�h�ȊO�̃m�[�h�S�Ă��w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�z���m�[�h�v�u�z���v</TD>
 * <TD>�m�[�h���m�̃c���[�K�w�\����ɂ����āA���m�[�h<B>��</B>�Ԃ牺����S�Ẵm�[�h���w���Ă��܂��B���m�[�h�͊܂܂�܂���B</TD>
 * </TR><TR>
 * <TD>�u���c���[�v</TD>
 * <TD>���m�[�h�𒸓_�Ƃ���A���m�[�h�{�z���m�[�h�ō\�������c���[�\�����̂��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�m�[�h�v</TD>
 * <TD>���m�[�h�𒸓_�Ƃ���A���m�[�h�{�z���m�[�h�ō\�������c���[�\���̃m�[�h�S�Ă��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u�������c���[�v</TD>
 * <TD>���m�[�h���܂܂�Ă���c���[�\���̑S�Ă��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u�m�[�h�N���X�v</TD>
 * <TD>GgafNode�����N���X�A������GgafNode�����N���X�𒼐ځE�Ԑڌp�����Ă���N���X���w���܂��B</TD>
 * </TR><TR>
 * <TD>�u��ʁv�u���ʁv</TD>
 * <TD>�m�[�h�N���X�̃N���X�p���֌W��\���Ă��܂��B
 * �N���X�p���֌W�̕\���́u�X�[�p�[�v�u�T�u�v���́u�e�v�u�q�v�ƌ��킸��<B>�u��ʁv�u���ʁv</B>�œ��ꂷ�邱�Ƃɂ��܂��B<BR>
 * �u�e�v�u�q�v�ƕ\�������ꍇ�͂��ꂼ��e�m�[�h�A�q�m�[�h�̃c���[�\���̎���\��������̂Ƃ��܂��B�i��₱�����ł��ˁj<BR>
 * ���၄���ʂŎ������ꂽ����B</TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */

template<class T>
class GgafNode : public GgafObject {

protected:
public:

	/** ID */
	string _id;
	/** �m�[�h�� */
	string _name;
	/** �N���X�� */
	string _class_name;

	/** �e�m�[�h */
	T* _pParent;
	/** ���m�[�h */
	T* _pNext;
	/** �O�m�[�h */
	T* _pPrev;
	/** �q�m�[�h�̐擪�m�[�h */
	T* _pSubFirst;

	/** �擪�m�[�h�t���O (���m�[�h���擪�m�[�h�̏ꍇ true)*/
	bool _isFirst;
	/** �����m�[�h�t���O (���m�[�h�������m�[�h�̏ꍇ true)*/
	bool _isLast;
	/** ���[�v�p */
	T* _pNodeTemp;

	/**
	 * �R���X�g���N�^
	 * @param prm_name �m�[�h���́i���j�[�N�ɂ��ĉ������j
	 */
	GgafNode(string prm_name);

	/**
	 * �f�X�g���N�^�B���c���[�m�[�h��������܂��B .
	 * ���m�[�h���q�m�[�h�����ꍇ�A�q�m�[�h��������Ă��玩�g���J������B<BR>
	 * ���m�[�h���ŏI�m�[�h�������ꍇ�A���m�[�h��A�����痣�E���A�O�m�[�h���ŏI�m�[�h�t���O���Z�b�g���āA���g���������B<BR>
	 * ���m�[�h���擪�m�[�h�������ꍇ�A���m�[�h��A�����痣�E���A���m�[�h��e�m�[�h �� �q�m�[�h�̐擪�m�[�h�A����� �擪�m�[�h�t���O���Z�b�g���A���g���������B<BR>
	 * ���m�[�h�����ԃm�[�h�������ꍇ�A���ׂ̃m�[�h�̘A�����č\�z������������B<BR>
	 * ���m�[�h�̘A�������g���w���i�P�l�ڂ����������j�ꍇ�A�e�m�[�h �� �q�m�[�h�̐擪�m�[�h�i�������w���Ă����j��NULL�ɕύX���Ă���������B<BR>
	 */
	virtual ~GgafNode();

	/**
	 * �m�[�h���擾 .
	 * @return �m�[�h����
	 */
	virtual string getName();

	/**
	 * �N���X���擾 .
	 * @return �N���X����
	 */
	virtual string getClassName();


	/**
	 * �m�[�h���₢���킹
	 */
//	virtual bool isNamed(string prm_name);


	/**
	 * �P��̐e�m�[�h��ݒ肷��B
	 * @param	prm_pParent	�e�m�[�h
	 */
	void setParent(T* prm_pParent);

	/**
	 * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
	 * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
	 * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
	 * @return	T* ���m�[�h�̃|�C���^
	 *
	 */
	T* tear();

	/**
	 * ���m�[�h���A�ŏI�m�[�h�ֈړ����� .
	 * �q�m�[�h�����A��ɂ��Ĉړ����܂��B���m�[�h�Ǝq�m�[�h�̊֌W�͕���܂���B<BR>
	 *<PRE>
	 * ----------------�u���s�O�v
	 *       �e
	 *       ��
	 * �i�d�j�̂`�̂a�̂b�̂c�̂d�́i�`�j
	 * -----------------------
	 *        �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A���̂悤�ȏ�ԂɂȂ�
	 * ----------------�u���s��v
	 *       �e
	 *       ��
	 * �i�d�j�̂`�̂a�̂c�̂d�̂b�́i�`�j
	 * -----------------------
	 * </PRE>
	 */
	void moveLast();

	/**
	 * ���m�[�h���A�擪�m�[�h�ֈړ����� .
	 * �q�m�[�h�����A��ɂ��Ĉړ����܂��B���m�[�h�Ǝq�m�[�h�̊֌W�͕���܂���B<BR>
	 *<PRE>
	 * ----------------�u���s�O�v
	 *      �e
	 *      ��
	 * (�d)�̂`�̂a�̂b�̂c�̂d��(�`)
	 * -----------------------
	 *        �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A���̂悤�ȏ�ԂɂȂ�
	 * ----------------�u���s��v
	 *      �e
	 *      ��
	 * (�d)�̂b�̂`�̂a�̂c�̂d��(�b)
	 * -----------------------
	 * </PRE>
	 */
	 void moveFirst();


	/**
	 * ���̃m�[�h�擾����B
	 * @return	T*	���m�[�h
	 */
	T* getNext();

	/**
	 * �O�̃m�[�h�擾����B
	 * @return	T*	�O�m�[�h
	 */
	T* getPrev();

	/**
	 * �P��̐e�m�[�h�擾����B
	 * @return	T*	�e�m�[�h
	 */
	T* getParent();

	/**
	 * �e�m�[�h��S�Č������擾����B
	 * ���݂��Ȃ��ꍇ�̓G���[
	 * @param	prm_parent_name	�e�m�[�h��
	 * @return	T*	�e�m�[�h
	 */
	T* getParent(string prm_parent_name);

	/**
	 * �����m�[�h���q�m�[�h�Ƃ��Ēǉ����� .
	 * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B<BR>
	 *<PRE>
	 * ----------------�u���s�O�v
	 *      �b
	 *      ��
	 * (�j)�̂h�̂i�̂j��(�h)
	 * -----------------------
	 *        �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A�����Ƀm�[�h�u�w�vaddSubLast �����
	 *        �� ���̂悤�ȏ�ԂɂȂ�
	 * ----------------�u���s��v
	 *      �b
	 *      ��
	 * (�w)�̂h�̂i�̂j�̂w��(�h)
	 * -----------------------
	 * </PRE>
	 *
	 * @param	prm_pSub	�C���X�^���X�����ς݃m�[�h�̃|�C���^
	 */
	void addSubLast(T* prm_pSub);

	/**
	 * �q�m�[�h���m�[�h���̂��w�肵�Ď擾���� .
	 * ���݂��Ȃ��ꍇ�̓G���[
	 * @param	prm_sub_actor_name	�q�m�[�h��
	 * @return	T*	�ŏ��Ƀq�b�g�����q�m�[�h���ɑΉ�����q�m�[�h�̃|�C���^
	 */
	T* getSub(string prm_sub_actor_name);

	/**
	 * �q�m�[�h�̃O���[�v�̐擪�m�[�h���擾���� .
	 * �q�m�[�h�����݂��Ȃ��ꍇ�̓G���[�B
	 * @return	T*	�q�m�[�h�̐擪�m�[�h
	 */
	T* getSubFirst();

	/**
	 * �q�m�[�h���݃`�F�b�N .
	 * @param	prm_sub_actor_name	���݃`�F�b�N����q�m�[�h��
	 * @return	bool true:���݂���^false:���݂��Ȃ�
	 */
	bool hasSub(string prm_sub_actor_name);

	/**
	 * ���m�[�h���擪�m�[�h�����ׂ� .
	 * @return	bool true:�擪�m�[�h�^false:�擪�m�[�h�ł͂Ȃ�
	 */
	bool isFirst();

	/**
	 * ���m�[�h�������m�[�h�����ׂ� .
	 * @return	bool true:�����m�[�h�^false:�����m�[�h�ł͂Ȃ�
	 */
	bool isLast();

};



//////////////////////////////////////////////////////////////////

/**
 * ��������͎�����
 */

template<class T>
GgafNode<T>::GgafNode(string prm_name) : GgafObject() ,
_name("NOT_OBJECT_YET"),
_pParent(NULL),
_pSubFirst(NULL),
_isFirst(false),
_isLast(false)
{
	_pNext = (T*)this;
	_pPrev = (T*)this;
	_name = prm_name;
	//_id = GgafUtil::itos(GgafObject::_iObjectNo);
	TRACE("template<class T> GgafNode<T>::GgafNode("+_name+")");
	_class_name = "GgafNode<T>";

}


template<class T>
T* GgafNode<T>::tear() {
	if (_pParent != NULL) {
		//�A������O��
		T* pMyNext = _pNext;
		T* pMyPrev = _pPrev;
		if (_isFirst && _isLast) {
			//�A���������̂ݏꍇ
			_pParent -> _pSubFirst = NULL;
		} else {
			//�A�������甲���o���ꍇ
			//���ׂ̃m�[�h���m���q���A�������w���Ȃ�����B
			pMyPrev -> _pNext = pMyNext;
			pMyNext -> _pPrev = pMyPrev;
			if (_isLast) {
				pMyPrev -> _isLast = true;
			}
			if (_isFirst) {
				pMyNext -> _isFirst = true;
				_pParent -> _pSubFirst = pMyNext;
			}
		}
		_pParent = NULL;
		_pNext = (T*)this;
		_pPrev = (T*)this;
		_isFirst = true;
		_isLast = true;
		return (T*)this;
	} else {
		throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::tear()] ���x���� "<<getName()<<"�́A�����ɂ��������Ă��܂���");
	}

}


template<class T>
void GgafNode<T>::moveLast() {
	if (_isLast) { //���ɍŏI�m�[�h�Ȃ�Ή������Ȃ�
		return;
	} else if (_isFirst) {  //�擪�m�[�h�Ȃ�΁A�e�̎w���Ă���擪�m�[�h�����ւ��炷
		_pParent -> _pSubFirst = _pNext;
		_pPrev->_isLast = false;
		_isFirst = false;
		_isLast = true;
		_pNext->_isFirst = true;
	} else { //���ԃm�[�h��
		//���ׂ̃m�[�h���m���q��
		_pPrev -> _pNext = _pNext;
		_pNext -> _pPrev = _pPrev;
		//�����m�[�h�Ɛ擪�m�[�h�̊Ԃɂ����肱�܂���
		_pParent -> _pSubFirst -> _pPrev -> _isLast = false;
		_isLast = true;
		_pPrev = _pParent -> _pSubFirst -> _pPrev;
		_pNext = _pParent -> _pSubFirst;
		_pParent -> _pSubFirst -> _pPrev -> _pNext = (T*)this;
		_pParent -> _pSubFirst -> _pPrev = (T*)this;
	}
}




template<class T>
void GgafNode<T>::moveFirst() {
	if (_isFirst) { //���ɐ擪�m�[�h�Ȃ�Ή������Ȃ�
		return;
	} else if (_isLast) {  //�����m�[�h�Ȃ�΁A�e�̎w���Ă���擪�m�[�h��O�ɂ��炷
		_pParent -> _pSubFirst = (T*)this;
		_pPrev->_isLast = true;
		_isFirst = true;
		_isLast= false;
		_pNext -> _isFirst = false;
	} else { //���ԃm�[�h��
		//���ׂ̃m�[�h���m���q��
		_pPrev -> _pNext = _pNext;
		_pNext -> _pPrev = _pPrev;
		//�����m�[�h�Ɛ擪�m�[�h�̊Ԃɂ����肱�܂���
		_pParent -> _pSubFirst -> _isFirst = false;
		_isFirst = true;
		_pPrev = _pParent -> _pSubFirst -> _pPrev;
		_pNext = _pParent -> _pSubFirst;
		_pParent -> _pSubFirst -> _pPrev -> _pNext = (T*)this;
		_pParent -> _pSubFirst -> _pPrev = (T*)this;
		_pParent -> _pSubFirst = (T*)this;
	}
}


template<class T>
void GgafNode<T>::setParent(T* prm_pParent) {
	_pParent = prm_pParent;
}

template<class T>
T* GgafNode<T>::getNext() {
	return (T*)_pNext;
}

template<class T>
T* GgafNode<T>::getPrev() {
	return (T*)_pPrev;
}


template<class T>
T* GgafNode<T>::getParent() {
	if (_pParent == NULL) {
		throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::getParent()] Error! �e�m�[�h������܂���B");
	}
	return (T*)_pParent;
}


template<class T>
T* GgafNode<T>::getParent(string prm_parent_name) {
	_pNodeTemp = (T*)this;
	while(true) {
		_pNodeTemp = _pNodeTemp->_pParent;
		if (_pNodeTemp == NULL) {
			throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::getParent()] Error! �e�m�[�h������܂���B(prm_parent_name="+prm_parent_name+")");
		} else if (_pNodeTemp->_name == prm_parent_name) {
			break;
		}
	}
	return _pNodeTemp;
}

template<class T>
T* GgafNode<T>::getSub(string prm_sub_actor_name) {
	if (_pSubFirst == NULL) {
		throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::getSub()] Error! _pSubFirst��NULL�ł��B");
	}
	_pNodeTemp = _pSubFirst;
	do {
		if(_pNodeTemp -> getName() == prm_sub_actor_name) {
			break;
		}
		if (_pNodeTemp -> _isLast) {
			throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::getSub()] Error! �q�m�[�h�͑��݂��܂���B(prm_sub_actor_name="+prm_sub_actor_name+")");
		} else {
			_pNodeTemp = _pNodeTemp -> _pNext;
		}
	} while(true);
	return _pNodeTemp;
}

template<class T>
T* GgafNode<T>::getSubFirst() {
	return (T*)_pSubFirst;
}


template<class T>
bool GgafNode<T>::hasSub(string prm_sub_actor_name) {
	if (_pSubFirst == NULL) {
		return false;
	} else {
		_pNodeTemp = _pSubFirst;
		do {
			if(_pNodeTemp -> getName() == prm_sub_actor_name) {
				return true;
			}
			if (_pNodeTemp -> _isLast) {
				return false;
			} else {
				_pNodeTemp = _pNodeTemp -> _pNext;
			}
		} while(true);
	}
}


template<class T>
void GgafNode<T>::addSubLast(T* prm_pSub) {
	if (prm_pSub->_pParent != NULL) {
		throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::addSubLast()] Error! �m�[�h�͊��ɏ������Ă��܂�(this="<<_name<<"/prm_pSub="+prm_pSub->getName()+")");
	}
	prm_pSub -> _pParent = (T*)this;
	prm_pSub -> _isLast = true;
	//prm_pSub -> _pScene_Platform = _pScene_Platform;

	if (_pSubFirst == NULL) {
		prm_pSub -> _isFirst = true;
		_pSubFirst = prm_pSub;
		_pSubFirst->_pNext = prm_pSub;
		_pSubFirst->_pPrev = prm_pSub;
	} else {
		prm_pSub -> _isFirst = false;
		T* pSubLast = _pSubFirst->_pPrev;
		pSubLast -> _isLast = false;
		pSubLast->_pNext = prm_pSub;
		prm_pSub->_pPrev = pSubLast;
		prm_pSub->_pNext = _pSubFirst;
		_pSubFirst->_pPrev = prm_pSub;
	}

}


template<class T>
string GgafNode<T>::getName() {
	return _name;
}

template<class T>
string GgafNode<T>::getClassName() {
	return _class_name;
}
/*
template<class T>
bool GgafNode<T>::isNamed(string prm_name) {
	string::size_type iLen = prm_name.length();
	if (prm_name.rfind('*') == iLen-1) {}


	return _name;
}
*/

template<class T>
bool GgafNode<T>::isLast() {
	return _isLast;
}

template<class T>
bool GgafNode<T>::isFirst() {
	return _isFirst;
}

template<class T>
GgafNode<T>::~GgafNode() {
	//�����Ɏq������ꍇ
	if (_pSubFirst) {
		//�܂��q��delete
		if (_pSubFirst->_isLast) {
			//�q�m�[�h�͂P�̏ꍇ
			DELETE_IMPOSSIBLE_NULL(_pSubFirst);
			_pSubFirst = NULL;
		} else {
			//�q�m�[�h�͂Q�ȏ�̏ꍇ
			T* pSubLast = _pSubFirst -> _pPrev;
			T* pSubLastPrev = pSubLast -> _pPrev;
			while(true) {
				DELETE_IMPOSSIBLE_NULL(pSubLast); //��������delete
				if (pSubLastPrev -> _isFirst) {
					DELETE_IMPOSSIBLE_NULL(_pSubFirst); //pSubLastPrev == _pSubFirst �ł���
					_pSubFirst = NULL;
					break;
				}
				pSubLast = pSubLastPrev;
				pSubLastPrev = pSubLastPrev -> _pPrev;
			}
		}
	}

	//�q���Ȃ���Ԃ̏ꍇ
	if (_pParent) {
		//�A������O��
		T* pMyNext = _pNext;
		T* pMyPrev = _pPrev;
		if (_isFirst && _isLast) {
			//�A�����Ă���m�[�h�������A�����̂ݏꍇ
			_pParent -> _pSubFirst = NULL;
			_pParent = NULL;
			_pNext = (T*)this;
			_pPrev = (T*)this;
			_pSubFirst = NULL;
		} else {
			//�A�������甲���o���ꍇ
			//���ׂ̃m�[�h���m���q���A�������w���Ȃ�����B
			pMyPrev -> _pNext = pMyNext;
			pMyNext -> _pPrev = pMyPrev;
			if (_isLast) {
				pMyPrev -> _isLast = true;
			}
			if (_isFirst) {
				pMyNext -> _isFirst = true;
				_pParent -> _pSubFirst = pMyNext;

			}
			_pParent = NULL;
			_pNext = (T*)this;
			_pPrev = (T*)this;
			_pSubFirst = NULL;
			_isFirst = true;
			_isLast = true;
		}
	}

//	_TRACE_("...deleted GgafNode<"<<_class_name<<">("<<_name<<") ID="<<_id);
	//_TRACE_("...deleted GgafNode<"<<_class_name<<">("<<_name<<")");

}

#endif /*GGAFNODE_H_*/
