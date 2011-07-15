#ifndef GGAFNODE_H_
#define GGAFNODE_H_
namespace GgafCore {

/**
 * �v�f���m����o�����A�����X�g�̃c���[�\������邱�Ƃ��ł���e���v���[�g�ł��B.
 *
 * <B>�y����z</B><BR>
 * <PRE STYLE="font-size:12px">
 * �@�E�E�̂o�́E�E�E
 * �@�@�@��
 * (�d)�̂`�̂a�̂b�̂c�̂d��(�`)
 * �@�@�@�@�@���@����������������������������
 * �@�@�@�@�@���@�@�@�@�@�@�@�@�@�@�@�@�@�@��
 * �@�@(�g)�̂e�̂f�̂g��(�e)�@�@�@�@(�k)�̂h�̂i�̂j�̂k��(�h)
 * �@�@�@�@�@�@�@���@���@�@�@�@�@�@�@�@�@�@�@�@���@�@�@��
 * �@�@�@�@�@�@�@�@�E�E�E�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�E�E�E
 * </PRE>
 * ��}�̂悤�ȍ\�����̂鎖���o���܂��B<BR>
 * ���i�́u(�d)�̂`�̂a�̂b�̂c�̂d��(�`)�v�͗v�f�i�C���X�^���X�j����̑o�����Ń|�C���^���w�������Ă��鎖�������Ă��܂��B<BR>
 * ���[�́u(�d)�v�Ɓu(�`)�v�́A�A�����X�g�̐擪�Ɩ������A���݂��A�����Ă��鎖�𖾎����Ă��܂��B(��ɂȂ��Ă���)<BR>
 * ��}�Ŏ��g�̃C���X�^���X���u�b�v�Ƃ����ꍇ�A�u�b�v�̎��_����e�v�f�����̂悤�Ɍď́A�y�ђ�`���邱�ƂƂ��܂��B<BR>
 * <TABLE BORDER="1">
 * <TR><TD>�u�b�v</TD><TD>���m�[�h</TD></TR>
 * <TR><TD>�u�`�v</TD><TD>�擪(First)�m�[�h�B ���m�[�h����������A�����X�g�̐擪�Ƃ����Ӗ��ł��B�u�`�v �� _is_first_flg �� true �ɂȂ��Ă��܂��B(���m�[�h�� false)</TD></TR>
 * <TR><TD>�u�d�v</TD><TD>����(Last)�m�[�h�B ���m�[�h����������A�����X�g�̍Ō�Ƃ����Ӗ��ł��B�u�d�v �� _is_last_flg �� true �ɂȂ��Ă��܂��B(���̃m�[�h�� false)</TD></TR>
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
 * ���၄<BR>
 * �E���ʂ�Hogehoge�Ŏ������ꂽ�R���R���B<BR>
 * �@�@�� �Ӗ��FHogehoge�N���X���p�����A�����Ŏ�������Ă���R���R��<BR>
 * �E�T�u��Hogehoge�Ŏ������ꂽ�R���R���B<BR>
 * �@�@�� �Ӗ��F�c���[�\���̎q�m�[�h�ɂ�����Hogehoge�N���X�I�u�W�F�N�g���Ŏ�������Ă���R���R��<BR>
 * </TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */

template<class T>
class GgafNode : public GgafObject {

private:
    /** ���[�v�p */
    T* _pNodeTemp;

public:
    /** [r]�m�[�h���ʖ�(50�����܂�) */
    char* _name;
    /** [r]�N���X�� */
    const char* _class_name;

    /** [r]�e�m�[�h */
    T* _pParent;
    /** [r]���m�[�h */
    T* _pNext;
    /** [r]�O�m�[�h */
    T* _pPrev;
    /** [r]�q�m�[�h�̐擪�m�[�h */
    T* _pSubFirst;
    /** [r]�擪�m�[�h�t���O (���m�[�h���擪�m�[�h�̏ꍇ true)*/
    bool _is_first_flg;
    /** [r]�����m�[�h�t���O (���m�[�h�������m�[�h�̏ꍇ true)*/
    bool _is_last_flg;

    int _sub_num;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name �m�[�h���́i���j�[�N�ɂ��ĉ������j
     */
    GgafNode(const char* prm_name);

    /**
     * �f�X�g���N�^�B���c���[�m�[�h��������܂��B .
     * ���m�[�h���q�m�[�h�����ꍇ�A�q�m�[�h��������Ă��玩�g���������B<BR>
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
    virtual char* getName(){
        return _name;
    }

    /**
     * �N���X���擾 .
     * @return �N���X����
     */
    virtual const char* getClassName() {
        return _class_name;
    }

    /**
     * �m�[�h���₢���킹
     */
    //	virtual bool isNamed(const char* prm_name);

    /**
     * �P��̐e�m�[�h��ݒ肷��B
     * @param	prm_pParent	�e�m�[�h
     */
    virtual void setParent(T* prm_pParent){
        _pParent = prm_pParent;
    }

    /**
     * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
     * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
     * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
     * @return	T* ���m�[�h�̃|�C���^
     */
    virtual T* extract();

    /**
     * ���m�[�h���A�ŏI�m�[�h�ֈړ����� .
     * �q�m�[�h�����A��ɂ��Ĉړ����܂��B���m�[�h�Ǝq�m�[�h�̊֌W�͕���܂���B<BR>
     *<PRE STYLE="font-size:18px">
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
    virtual void moveLast();

    /**
     * ���m�[�h���A�擪�m�[�h�ֈړ����� .
     * �q�m�[�h�����A��ɂ��Ĉړ����܂��B���m�[�h�Ǝq�m�[�h�̊֌W�͕���܂���B<BR>
     *<PRE STYLE="font-size:18px">
     * ----------------�u���s�O�v
     * �@�@�@�e
     * �@�@�@��
     * (�d)�̂`�̂a�̂b�̂c�̂d��(�`)
     * -----------------------
     *        �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A���̂悤�ȏ�ԂɂȂ�
     * ----------------�u���s��v
     * �@�@�@�e
     * �@�@�@��
     * (�d)�̂b�̂`�̂a�̂c�̂d��(�b)
     * -----------------------
     * </PRE>
     */
    virtual void moveFirst();

    /**
     * ���̃m�[�h�擾����B
     * @return	T*	���m�[�h
     */
    virtual T* getNext() {
        return _pNext;
    }

    /**
     * �O�̃m�[�h�擾����B
     * @return	T*	�O�m�[�h
     */
    virtual T* getPrev() {
        return _pPrev;
    }

    /**
     * �P��̐e�m�[�h�擾����B
     * @return	T*	�e�m�[�h
     */
    virtual T* getParent();

    /**
     * �e�m�[�h��S�Č������擾����B
     * ���݂��Ȃ��ꍇ�̓G���[ <BR>
     * ������ char* �̔�r��������܂ōs�����߁A�d���ł��B<BR>
     * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
     * @param	prm_parent_name	�e�m�[�h��
     * @return	T*	�e�m�[�h
     */
    virtual T* getParent(char* prm_parent_name);

    /**
     * �����m�[�h���q�m�[�h�Ƃ��Ēǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B<BR>
     *<PRE STYLE="font-size:18px">
     * ----------------�u���s�O�v
     *       �b
     *       ��
     * (�j)�̂h�̂i�̂j��(�h)
     * -----------------------
     *         �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A�����Ƀm�[�h�u�w�vaddSubLast �����
     *         �� ���̂悤�ȏ�ԂɂȂ�
     * ----------------�u���s��v
     *       �b
     *       ��
     * (�w)�̂h�̂i�̂j�̂w��(�h)
     * -----------------------
     * </PRE>
     *
     * @param   prm_pSub    �C���X�^���X�����ς݃m�[�h�̃|�C���^
     */
    virtual void addSubLast(T* prm_pSub);

    /**
     * �q�m�[�h���m�[�h���̂��w�肵�Ď擾���� .
     * ���݂��Ȃ��ꍇ�̓G���[<BR>
     * ������ char* �̔�r��������܂ōs�����߁A���d���ł��B<BR>
     * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
     * @param	prm_sub_actor_name	�q�m�[�h��
     * @return	T*	�ŏ��Ƀq�b�g�����q�m�[�h���ɑΉ�����q�m�[�h�̃|�C���^
     */
    virtual T* getSubByName(const char* prm_sub_name);

    /**
     * �q�m�[�h�����݂���ꍇ�擾���� .
     * @param prm_pSub �q�m�[�h
     * @return ���݂���ꍇ�q�m�[�h���Ԃ�A���݂��Ȃ��ꍇ NULL ���Ԃ�
     */
    virtual T* getSub(T* prm_pSub);
    virtual T* getSub(int prm_index);
    /**
     * �q�m�[�h�̃O���[�v�̐擪�m�[�h���擾���� .
     * �q�m�[�h�����݂��Ȃ��ꍇ�̓G���[�B
     * @return	T*	�q�m�[�h�̐擪�m�[�h
     */
    virtual T* getSubFirst() {
        return _pSubFirst;
    }

    /**
     * �q�m�[�h���݃`�F�b�N .
     * ������ char* �̔�r��������܂ōs�����߁A�d���ł��B<BR>
     * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
     * @param	prm_sub_actor_name	���݃`�F�b�N����q�m�[�h��
     * @return	bool true:���݂���^false:���݂��Ȃ�
     */
    virtual bool hasSub(char* prm_sub_actor_name);


    /**
     * �q�m�[�h�����擾���� .
     * @return  T*  �q�m�[�h��
     */
    virtual int getNumSub();


    /**
     * ���m�[�h���擪�m�[�h�����ׂ� .
     * @return	bool true:�擪�m�[�h�^false:�擪�m�[�h�ł͂Ȃ�
     */
    virtual bool isFirst() {
        return _is_first_flg;
    }

    /**
     * ���m�[�h�������m�[�h�����ׂ� .
     * @return	bool true:�����m�[�h�^false:�����m�[�h�ł͂Ȃ�
     */
    virtual bool isLast(){
        return _is_last_flg;
    }

};

//////////////////////////////////////////////////////////////////

/**
 * ��������͎�����
 */
template<class T>
GgafNode<T>::GgafNode(const char* prm_name) : GgafObject(),
_pNodeTemp(NULL),
_name(NULL),
_class_name("GgafNode<T>"),
_pParent(NULL),
_pNext((T*)this),
_pPrev((T*)this),
_pSubFirst(NULL),
_is_first_flg(false),
_is_last_flg(false),
_sub_num(0)
{
    _name = NEW char[51];
    strcpy(_name, prm_name);
    TRACE("template<class T> GgafNode<T>::GgafNode(" << _name << ")");
}

template<class T>
T* GgafNode<T>::extract() {
    if (_pParent) {
        //�A������O��
        _pParent->_sub_num--;
        T* pMyNext = _pNext;
        T* pMyPrev = _pPrev;
        if (_is_first_flg && _is_last_flg) {
            //�A���������̂ݏꍇ
            _pParent->_pSubFirst = NULL;
        } else {
            //�A�������甲���o���ꍇ
            //���ׂ̃m�[�h���m���q���A�������w���Ȃ�����B
            pMyPrev->_pNext = pMyNext;
            pMyNext->_pPrev = pMyPrev;
            if (_is_last_flg) {
                pMyPrev->_is_last_flg = true;
            }
            if (_is_first_flg) {
                pMyNext->_is_first_flg = true;
                _pParent->_pSubFirst = pMyNext;
            }
        }
        _pParent = NULL;
        _pNext = (T*)this;
        _pPrev = (T*)this;
        _is_first_flg = true;
        _is_last_flg = true;
        return (T*)this;
    } else {
        //�v�f��ǉ����邽�߂̃��\�b�h���A���� addSubLast() �݂̂ł��邽�߁A�c���[�̒��_�͏�K���P�ł���B
        //�e�����Ȃ����Ƃ̓c���[�̒��_�ł��A�ׂ����Ȃ����ƂƓ��l�B
        //TODO:�����AaddNext() �̂悤�ȗׂɗv�f��ǉ����郁�\�b�h�����Ȃ���΂����Ȃ��Ȃ����ꍇ�A
        //     ���̏ꏊ�ɉ��A������̂ݐ؂藣��������ǉ�����̂�Y�ꂸ�ɁB
        TRACE("[GgafNode<" << _class_name << ">::extract()] ���x���� " << getName() << "�́A�����ɂ��������Ă��܂���B���ɓƗ����Ă܂���");
        return (T*)this;
    }
}

template<class T>
void GgafNode<T>::moveLast() {
    if (_is_last_flg) { //���ɍŏI�m�[�h�Ȃ�Ή������Ȃ�
        return;
    } else if (_is_first_flg) { //�擪�m�[�h�Ȃ�΁A�e�̎w���Ă���擪�m�[�h�����ւ��炷
        _pParent->_pSubFirst = _pNext;
        _pPrev->_is_last_flg = false;
        _is_first_flg = false;
        _is_last_flg = true;
        _pNext->_is_first_flg = true;
    } else { //���ԃm�[�h��
        //���ׂ̃m�[�h���m���q��
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        //�����m�[�h�Ɛ擪�m�[�h�̊Ԃɂ����肱�܂���
        _pParent->_pSubFirst->_pPrev->_is_last_flg = false;
        _is_last_flg = true;
        _pPrev = _pParent->_pSubFirst->_pPrev;
        _pNext = _pParent->_pSubFirst;
        _pParent->_pSubFirst->_pPrev->_pNext = (T*)this;
        _pParent->_pSubFirst->_pPrev = (T*)this;
    }
}

template<class T>
void GgafNode<T>::moveFirst() {
    if (_is_first_flg) { //���ɐ擪�m�[�h�Ȃ�Ή������Ȃ�
        return;
    } else if (_is_last_flg) { //�����m�[�h�Ȃ�΁A�e�̎w���Ă���擪�m�[�h��O�ɂ��炷
        _pParent->_pSubFirst = (T*)this;
        _pPrev->_is_last_flg = true;
        _is_first_flg = true;
        _is_last_flg = false;
        _pNext->_is_first_flg = false;
    } else { //���ԃm�[�h��
        //���ׂ̃m�[�h���m���q��
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        //�����m�[�h�Ɛ擪�m�[�h�̊Ԃɂ����肱�܂���
        _pParent->_pSubFirst->_is_first_flg = false;
        _is_first_flg = true;
        _pPrev = _pParent->_pSubFirst->_pPrev;
        _pNext = _pParent->_pSubFirst;
        _pParent->_pSubFirst->_pPrev->_pNext = (T*)this;
        _pParent->_pSubFirst->_pPrev = (T*)this;
        _pParent->_pSubFirst = (T*)this;
    }
}


template<class T>
T* GgafNode<T>::getParent() {
#ifdef MY_DEBUG
    if (_pParent == NULL) {
        //_TRACE_("[GgafNode<" << _class_name << ">::getParent()] ���x���� �e�m�[�h������܂���BNULL��Ԃ��܂��B");
    }
#endif
    return (T*)_pParent;
}

template<class T>
T* GgafNode<T>::getParent(char* prm_parent_name) {
    _pNodeTemp = (T*)this;
    while (true) {
        _pNodeTemp = _pNodeTemp->_pParent;
        if (_pNodeTemp == NULL) {
#ifdef MY_DEBUG
            //_TRACE_("[GgafNode<" << _class_name << ">::getParent("<<prm_parent_name<<")] ���x���� �e�m�[�h��k���Č������܂���������܂���BNULL��Ԃ��܂��B");
#endif
            return NULL;
        } else if (GgafUtil::strcmp_ascii(_pNodeTemp->_name, prm_parent_name) == 0) {
            break;
        }
    }
    return _pNodeTemp;
}

template<class T>
T* GgafNode<T>::getSubByName(const char* prm_sub_name) {
#ifdef MY_DEBUG
    if (_pSubFirst == NULL) {
        throwGgafCriticalException("[GgafNode<" << _class_name << ">::getSub()] Error! _pSubFirst��NULL�ł��B");
    }
#endif
    _pNodeTemp = _pSubFirst;
    do {
        if (GgafUtil::strcmp_ascii(_pNodeTemp->getName(), prm_sub_name) == 0) {
            break;
        }
#ifdef MY_DEBUG
        if (_pNodeTemp->_is_last_flg) {
            throwGgafCriticalException("[GgafNode<" << _class_name << ">::getSub()] Error! �q�m�[�h�͑��݂��܂���B(prm_sub_actor_name=" << prm_sub_name << ")");
        }
#endif
        _pNodeTemp = _pNodeTemp->_pNext;
    } while (true);
    return _pNodeTemp;
}

template<class T>
T* GgafNode<T>::getSub(T* prm_pSub) {
    if (_pSubFirst == NULL) {
        return NULL;
    }
    T* pNodeTemp = _pSubFirst;
    do {
        if (prm_pSub == pNodeTemp) {
            break;
        }
        if (pNodeTemp->_is_last_flg) {
            return NULL;
        }
        pNodeTemp = pNodeTemp->_pNext;
    } while (true);
    return pNodeTemp;
}

template<class T>
T* GgafNode<T>::getSub(int prm_index) {
    T* pNodeTemp = _pSubFirst;
    for (int i = 0; i < prm_index; i++) {
        pNodeTemp = pNodeTemp->_pNext;
    }
    return pNodeTemp;
}

template<class T>
bool GgafNode<T>::hasSub(char* prm_sub_actor_name) {
    if (_pSubFirst == NULL) {
        return false;
    } else {
        _pNodeTemp = _pSubFirst;
        do {
            if (GgafUtil::strcmp_ascii(_pNodeTemp->getName(), prm_sub_actor_name)) {
                return true;
            }
            if (_pNodeTemp->_is_last_flg) {
                return false;
            } else {
                _pNodeTemp = _pNodeTemp->_pNext;
            }
        } while (true);
    }
}

template<class T>
int GgafNode<T>::getNumSub() {
    return _sub_num;
//
//    if (_pSubFirst == NULL) {
//        return 0;
//    }
//    int n = 1;
//    _pNodeTemp = _pSubFirst;
//    do {
//        if (_pNodeTemp->isLast()) {
//            break;
//        }
//        _pNodeTemp = _pNodeTemp->_pNext;
//        n++;
//    } while (true);
//    return n;
}


template<class T>
void GgafNode<T>::addSubLast(T* prm_pSub) {
#ifdef MY_DEBUG
    if (prm_pSub->_pParent) {
        throwGgafCriticalException("[GgafNode<" << _class_name << ">::addSubLast()] Error! �m�[�h�͊��ɏ���("
                << prm_pSub->_pParent->_name << "�ɏ���)���Ă��܂�(this=" << _name << "/prm_pSub=" << prm_pSub->getName() << ")");
    }
#endif

    _sub_num++;
    prm_pSub->_pParent = (T*)this;
    prm_pSub->_is_last_flg = true;
    //prm_pSub->_pScene_Platform = _pScene_Platform;

    if (_pSubFirst == NULL) {
        prm_pSub->_is_first_flg = true;
        _pSubFirst = prm_pSub;
        _pSubFirst->_pNext = prm_pSub;
        _pSubFirst->_pPrev = prm_pSub;
    } else {
        prm_pSub->_is_first_flg = false;
        T* pSubLast = _pSubFirst->_pPrev;
        pSubLast->_is_last_flg = false;
        pSubLast->_pNext = prm_pSub;
        prm_pSub->_pPrev = pSubLast;
        prm_pSub->_pNext = _pSubFirst;
        _pSubFirst->_pPrev = prm_pSub;
    }

}

/*
 template<class T>
 bool GgafNode<T>::isNamed(const char* prm_name) {
 char*::size_type iLen = prm_name.length();
 if (prm_name.rfind('*') == iLen-1) {}


 return _name;
 }
 */


template<class T>
GgafNode<T>::~GgafNode() {
    //�����Ɏq������ꍇ
    if (_pSubFirst) {
        //�܂��q��delete
        if (_pSubFirst->_is_last_flg) {
            //�q�m�[�h�͂P�̏ꍇ
            DELETE_IMPOSSIBLE_NULL(_pSubFirst);
            _pSubFirst = NULL;
        } else {
            //�q�m�[�h�͂Q�ȏ�̏ꍇ
            T* pSubLast = _pSubFirst->_pPrev;
            T* pSubLastPrev = pSubLast->_pPrev;
            while (true) {
                DELETE_IMPOSSIBLE_NULL(pSubLast); //��������delete
                if (pSubLastPrev->_is_first_flg) {
                    DELETE_IMPOSSIBLE_NULL(_pSubFirst); //pSubLastPrev == _pSubFirst �ł���
                    _pSubFirst = NULL;
                    break;
                }
                pSubLast = pSubLastPrev;
                pSubLastPrev = pSubLastPrev->_pPrev;
            }
        }
    }

    //�q���Ȃ���Ԃ̏ꍇ
    if (_pParent) {
        _pParent->_sub_num--;
        //�A������O��
        T* pMyNext = _pNext;
        T* pMyPrev = _pPrev;
        if (_is_first_flg && _is_last_flg) {
            //�A�����Ă���m�[�h�������A�����̂ݏꍇ
            _pParent->_pSubFirst = NULL;
            _pParent = NULL;
            _pNext = (T*)this;
            _pPrev = (T*)this;
            _pSubFirst = NULL;
        } else {
            //�A�������甲���o���ꍇ
            //���ׂ̃m�[�h���m���q���A�������w���Ȃ�����B
            pMyPrev->_pNext = pMyNext;
            pMyNext->_pPrev = pMyPrev;
            if (_is_last_flg) {
                pMyPrev->_is_last_flg = true;
            }
            if (_is_first_flg) {
                pMyNext->_is_first_flg = true;
                _pParent->_pSubFirst = pMyNext;
            }
            _pParent = NULL;
            _pNext = (T*)this;
            _pPrev = (T*)this;
            _pSubFirst = NULL;
            _is_first_flg = true;
            _is_last_flg = true;
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_name);
}

}
#endif /*GGAFNODE_H_*/
