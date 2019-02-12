#ifndef GGAF_CORE_NODE_H_
#define GGAF_CORE_NODE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <cstring>
#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * �v�f���m����o�����A�����X�g(�������[)�ŁA�c���[�\������邱�Ƃ��ł���e���v���[�g�ł��B.
 * �����c���[�m�[�h�����A�Z��m�[�h����o�����A�����X�g�Ō������O��ʒu�֌W�̊T�O������B
 * �܂��A�Z��m�[�h�ɐ擪�m�[�h�A�����m�[�h�̊T�O������B�擪�m�[�h�Ɩ����m�[�h�̓t���O�ŊǗ��B
 * ��Ȃ̂Ő擪�m�[�h�A�����m�[�h�݂͌��ɘA�����Ă���B
 * �m�[�h�͎��l�i�v�f�C���X�^���X�j���w���킯�ł͂Ȃ��A�m�[�h�̃I�u�W�F�N�g���g�����l�Ƃ��Ă���B
 * �܂�A�R���e�i�ɔ񂸁B<BR>
 * �����ł��Q�Ɖ񐔂����炵�A�p�t�H�[�}���X���グ�悤�Ƃ��ׁE�E�E�B<BR>
 *
 * <B>�y����z</B><BR>
 * <PRE STYLE="font-size:12px">
 * �E�E�̂o�́E�E�E
 *       ��
 * (�d)�̂`�̂a�̂b�̂c�̂d��(�`)
 *           ��  ����������������������������
 *           ��                            ��
 *     (�g)�̂e�̂f�̂g��(�e)        (�k)�̂h�̂i�̂j�̂k��(�h)
 *               ��  ��                        ��      ��
 *                 �E�E�E                              �E�E�E
 * </PRE>
 * ��}�̂悤�ȍ\�����̂鎖���o���܂��B<BR>
 * ���i�́u(�d)�̂`�̂a�̂b�̂c�̂d��(�`)�v�͗v�f�i�C���X�^���X�j����̑o�����Ń|�C���^���w�������Ă��鎖�������Ă��܂��B<BR>
 * ���[�́u(�d)�v�Ɓu(�`)�v�́A�A�����X�g�̐擪�Ɩ������A���݂��A�����Ă��鎖�𖾎����Ă��܂��B(��ɂȂ��Ă���)<BR>
 * ��}�Ŏ��g�̃C���X�^���X���u�b�v�Ƃ����ꍇ�A�u�b�v�̎��_����e�v�f�����̂悤�Ɍď́A�y�ђ�`���邱�ƂƂ��܂��B<BR>
 * <TABLE BORDER="1">
 * <TR><TD>�u�b�v</TD><TD>���m�[�h</TD></TR>
 * <TR><TD>�u�`�v</TD><TD>�擪(First)�m�[�h�B ���m�[�h����������A�����X�g�i�Z��m�[�h�j�̐擪�Ƃ����Ӗ��ł��B�u�`�v �� _is_first_flg �� true �ɂȂ��Ă��܂��B(���m�[�h�� false)</TD></TR>
 * <TR><TD>�u�d�v</TD><TD>����(Last)�m�[�h�B ���m�[�h����������A�����X�g�i�Z��m�[�h�j�̍Ō�Ƃ����Ӗ��ł��B�u�d�v �� _is_last_flg �� true �ɂȂ��Ă��܂��B(���̃m�[�h�� false)</TD></TR>
 * <TR><TD>�u�c�v</TD><TD>��(Next)�m�[�h�B��}�ł͍�����E���������Ƃ��Ă��܂��B_pNext�|�C���^���w���Ă���v�f�ɂȂ�܂��B</TD></TR>
 * <TR><TD>�u�a�v</TD><TD>�O(Prev)�m�[�h�B_pPrev ���w���Ă���|�C���^�ł��B</TD></TR>
 * <TR><TD>�u�o�v</TD><TD>�e(Parent)�m�[�h�B���m�[�h����������A�����X�g�̂P��̊K�w�̃m�[�h�ł��B_pParent �|�C���^���w���Ă���v�f�ł��B�S�Ẵm�[�h�͒��߂̐e�m�[�h�̃|�C���^�������Ă��܂��B</TD></TR>
 * <TR><TD>�u�h�C�i�C�j�C�k�v</TD><TD>�u�b�v�q(Child)�m�[�h�ƌĂт܂��B</TD></TR>
 * <TR><TD>�u�h�v</TD><TD> �q�m�[�h�̒��œ��Ɂu�h�v�͎q�m�[�h�̐擪�m�[�h�ƌĂсA���m�[�h�� _pChildFirst �|�C���^���w���Ă���v�f�ƂȂ��Ă��܂��B</TD></TR>
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
 * <TD>Node�����N���X�A������Node�����N���X�𒼐ځE�Ԑڌp�����Ă���N���X���w���܂��B</TD>
 * </TR><TR>
 * <TD>�u��ʁv�u���ʁv</TD>
 * <TD>�m�[�h�N���X�̃N���X�p���֌W��\���Ă��܂��B
 * �{�h�L�������g�ł́A�N���X�p���֌W�̕\���́u�X�[�p�[�v�u�q�v���́u�e�v�u�q�v�ƌ��킸��<B>�u��ʁv�u���ʁv</B>�œ��ꂷ�邱�Ƃɂ��܂��B<BR>
 * �u�e�v�u�q�v�ƕ\�������ꍇ�͂��ꂼ��e�m�[�h�A�q�m�[�h�̃c���[�\���̎���\��������̂Ƃ��܂��B�i��₱�����ł��ˁj<BR>
 * ���၄<BR>
 * �E���ʂ�Hogehoge�Ŏ������ꂽ�R���R���B<BR>
 *     �� �Ӗ��FHogehoge�N���X���p�����A�����Ŏ�������Ă���R���R��<BR>
 * �E�q��Hogehoge�Ŏ������ꂽ�R���R���B<BR>
 *     �� �Ӗ��F�c���[�\���̎q�m�[�h�ɂ�����Hogehoge�N���X�I�u�W�F�N�g���Ŏ�������Ă���R���R��<BR>
 * </TD>
 * </TR>
 * </TABLE>
 * @tparam T �Ǘ�����v�f�̌^�i���̌^�̃|�C���^�^�������ŊǗ������B�j
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */

template<class T>
class Node : public Object {

public:
    /** [r]�m�[�h���ʖ�(50�����܂�) */
    char* _name;
    /** [r]�N���X���i�f�o�b�O�Ŏg�p���܂��j */
    const char* _class_name;
    /** [r]�e�m�[�h */
    T* _pParent;
    /** [r]���m�[�h */
    T* _pNext;
    /** [r]�O�m�[�h */
    T* _pPrev;
    /** [r]�q�m�[�h�̐擪�m�[�h */
    T* _pChildFirst;
    /** [r]�擪�m�[�h�t���O (���m�[�h���擪�m�[�h�̏ꍇ true)*/
    bool _is_first_flg;
    /** [r]�����m�[�h�t���O (���m�[�h�������m�[�h�̏ꍇ true)*/
    bool _is_last_flg;
    /** [r]�q�m�[�h�̐� */
    int _child_num;

    hashval _name_hash;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name �m�[�h���́i���j�[�N�ɂ��ĉ������j
     */
    explicit Node(const char* prm_name);

    /**
     * �f�X�g���N�^�B���c���[�m�[�h��������܂��B .
     * ���m�[�h���q�m�[�h�����ꍇ�A�q�m�[�h��������Ă��玩�g���������B<BR>
     * ���m�[�h���ŏI�m�[�h�������ꍇ�A���m�[�h��A�����痣�E���A�O�m�[�h���ŏI�m�[�h�t���O���Z�b�g���āA���g���������B<BR>
     * ���m�[�h���擪�m�[�h�������ꍇ�A���m�[�h��A�����痣�E���A���m�[�h��e�m�[�h �� �q�m�[�h�̐擪�m�[�h�A����� �擪�m�[�h�t���O���Z�b�g���A���g���������B<BR>
     * ���m�[�h�����ԃm�[�h�������ꍇ�A���ׂ̃m�[�h�̘A�����č\�z������������B<BR>
     * ���m�[�h�̘A�������g���w���i�P�l�ڂ����������j�ꍇ�A�e�m�[�h �� �q�m�[�h�̐擪�m�[�h�i�������w���Ă����j��nullptr�ɕύX���Ă���������B<BR>
     * ���̂悤�ȍ\���̏ꍇ�A�m�[�h P ��delete����ƁA������͇@�`�L�̏����ƂȂ�B<BR>
     * �m�[�h�ԂŎQ�Ɗ֌W������ꍇ�́A���ӂ��K�v�B<BR>
     * <pre>
     * (�o)�̇L�o��(�o)
     *         ��
     * (�d)�̇K�`�̇G�a�̇B�b�̇A�c�̇@�d��(�`)
     *         ��    ����������������������������
     *         ��                              ��
     * (�g)�̇J�e�̇I�f�̇H�g��(�e)    (�k)�̇F�h�̇E�i�̇D�j�̇C�k��(�h)
     *
     * ���q�����݂���΂������D��Ŗ����m�[�h���������Ă����B
     * </pre>
     */
    virtual ~Node();

    /**
     * �m�[�h���擾 .
     * @return �m�[�h����
     */
    inline virtual char* getName() const {
        return _name;
    }

    /**
     * �N���X���擾 .
     * @return �N���X����
     */
    inline virtual const char* getClassName() const {
        return _class_name;
    }

    /**
     * �P��̐e�m�[�h��ݒ肷��B
     * @param    prm_pParent    �e�m�[�h
     */
    inline virtual void setParent(T* prm_pParent) {
        _pParent = prm_pParent;
    }

    /**
     * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
     * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
     * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
     * @return    T* ���m�[�h�̃|�C���^
     */
    virtual T* extract();

    /**
     * ���m�[�h���A�ŏI�m�[�h�ֈړ����� .
     * �q�m�[�h�����A��ɂ��Ĉړ����܂��B���m�[�h�Ǝq�m�[�h�̊֌W�͕���܂���B<BR>
     *<PRE>
     * ----------------�u���s�O�v
     *         �e
     *         ��
     * �i�d�j�̂`�̂a�̂b�̂c�̂d�́i�`�j
     * -----------------------
     *        �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A���̂悤�ȏ�ԂɂȂ�
     * ----------------�u���s��v
     *         �e
     *         ��
     * �i�d�j�̂`�̂a�̂c�̂d�̂b�́i�`�j
     * -----------------------
     * </PRE>
     */
    virtual void moveLast();

    /**
     * ���m�[�h���A�擪�m�[�h�ֈړ����� .
     * �q�m�[�h�����A��ɂ��Ĉړ����܂��B���m�[�h�Ǝq�m�[�h�̊֌W�͕���܂���B<BR>
     *<PRE>
     * ----------------�u���s�O�v
     *       �e
     *       ��
     * (�d)�̂`�̂a�̂b�̂c�̂d��(�`)
     * -----------------------
     *        �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A���̂悤�ȏ�ԂɂȂ�
     * ----------------�u���s��v
     *       �e
     *       ��
     * (�d)�̂b�̂`�̂a�̂c�̂d��(�b)
     * -----------------------
     * </PRE>
     */
    virtual void moveFirst();

    /**
     * ���̃m�[�h�擾����B
     * @return    T*    ���m�[�h
     */
    inline virtual T* getNext() const {
        return _pNext;
    }

    /**
     * �O�̃m�[�h�擾����B
     * @return    T*    �O�m�[�h
     */
    inline virtual T* getPrev() const {
        return _pPrev;
    }

    /**
     * �P��̐e�m�[�h�擾����B
     * @return    T*    �e�m�[�h
     */
    inline virtual T* getParent() const {
        return _pParent;
    }

    /**
     * �����m�[�h���q�m�[�h�̍Ō�ɒǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B<BR>
     *<PRE>
     * ----------------�u���s�O�v
     *       �b
     *       ��
     * (�j)�̂h�̂i�̂j��(�h)
     * -----------------------
     *         �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A�����Ƀm�[�h�u�w�vappendChild �����
     *         �� ���̂悤�ȏ�ԂɂȂ�
     * ----------------�u���s��v
     *       �b
     *       ��
     * (�w)�̂h�̂i�̂j�̂w��(�h)
     * -----------------------
     * </PRE>
     *
     * @param   prm_pChild    �C���X�^���X�����ς݃m�[�h�̃|�C���^
     */
    virtual void appendChild(T* prm_pChild);

    /**
     * �����m�[�h���q�m�[�h�̐擪�ɒǉ����� .
     * �ǉ������ꏊ�͈ȉ��̐}�̂悤�ɂȂ�܂��B<BR>
     *<PRE>
     * ----------------�u���s�O�v
     *       �b
     *       ��
     * (�j)�̂h�̂i�̂j��(�h)
     * -----------------------
     *         �� ��}�Ŏ������u�b�v�Ƃ����ꍇ�A�����Ƀm�[�h�u�w�vprependChild �����
     *         �� ���̂悤�ȏ�ԂɂȂ�
     * ----------------�u���s��v
     *       �b
     *       ��
     * (�j)�̂w�̂h�̂i�̂j��(�w)
     * -----------------------
     * </PRE>
     *
     * @param   prm_pChild    �C���X�^���X�����ς݃m�[�h�̃|�C���^
     */
    virtual void prependChild(T* prm_pChild);

    /**
     * �q�m�[�h���m�[�h���̂��w�肵�Ď擾���� .
     * ���݂��Ȃ��ꍇ�̓G���[<BR>
     * ������ char* �̔�r��������܂ōs�����߁A���d���ł��B<BR>
     * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
     * @param    prm_child_name    �q�m�[�h��
     * @return    T*    �ŏ��Ƀq�b�g�����q�m�[�h���ɑΉ�����q�m�[�h�̃|�C���^
     */
    virtual T* getChildByName(const char* prm_child_name);

    /**
     * �����̃m�[�h���q�m�[�h�ɑ��݂���ꍇ�擾���� .
     * @param prm_pChild �q�m�[�h
     * @return ���݂���ꍇ�q�m�[�h���Ԃ�A���݂��Ȃ��ꍇ nullptr ���Ԃ�
     */
    virtual T* getChild(T* prm_pChild) const;

    /**
     * �q�m�[�h��擪����̃C���f�b�N�X�w��Ŏ擾���� .
     * 0 �� _pChildFirst �Ɠ����B
     * @param prm_index �C���f�b�N�X(0�`)
     * @return
     */
    virtual T* getChild(int prm_index) const;

    /**
     * �q�m�[�h�̃O���[�v�̐擪�m�[�h���擾���� .
     * �q�m�[�h�����݂��Ȃ��ꍇ��nullptr�B
     * @return    T*    �q�m�[�h�̐擪�m�[�h
     */
    inline virtual T* getChildFirst() const {
        return _pChildFirst;
    }

    /**
     * �q�m�[�h�̃O���[�v�̖����m�[�h���擾���� .
     * �q�m�[�h�����݂��Ȃ��ꍇ��nullptr�B
     * @return T*   �q�m�[�h�̖����m�[�h
     */
    inline virtual T* getChildLast() const {
        if (_pChildFirst) {
            return _pChildFirst->_pPrev;
        } else {
            return nullptr;
        }
    }

    /**
     * �q�m�[�h���݃`�F�b�N .
     * ������ char* �̔�r��������܂ōs�����߁A�d���ł��B<BR>
     * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
     * @param    prm_child_actor_name    ���݃`�F�b�N����q�m�[�h��
     * @return    bool true:���݂���^false:���݂��Ȃ�
     */
    virtual bool hasChild(char* prm_child_actor_name) const;


    /**
     * �q�m�[�h�����擾���� .
     * @return  T*  �q�m�[�h��
     */
    inline virtual int getNumChild() const {
        return _child_num;
    }

    /**
     * ���m�[�h���擪�m�[�h�����ׂ� .
     * @return    bool true:�擪�m�[�h�^false:�擪�m�[�h�ł͂Ȃ�
     */
    inline virtual bool isFirst() const {
        return _is_first_flg;
    }

    /**
     * ���m�[�h�������m�[�h�����ׂ� .
     * @return    bool true:�����m�[�h�^false:�����m�[�h�ł͂Ȃ�
     */
    inline virtual bool isLast() const {
        return _is_last_flg;
    }

    virtual std::string toString() override {
        return getName();
    }

};

//////////////////////////////////////////////////////////////////

/**
 * ��������͎�����
 */
template<class T>
Node<T>::Node(const char* prm_name) :
    Object(),
    _name(nullptr),
    _class_name("Node<T>"),
    _pParent(nullptr),
    _pNext((T*)this),
    _pPrev((T*)this),
    _pChildFirst(nullptr),
    _is_first_flg(true),
    _is_last_flg(true),
    _child_num(0)
{
    _name_hash = UTIL::easy_hash(prm_name);
    int len = strlen(prm_name);
    _name = NEW char[len+1];
    strcpy(_name, prm_name);


//#ifdef MY_DEBUG
//    if (strlen(prm_name) > 49) {
//        throwCriticalException("[Node �R���X�g���N�^ Error! prm_name �̕������I�[�o�[ prm_name="<<prm_name<<"");
//    }
//    if (strlen(prm_name) == 0) {
//        throwCriticalException("[Node �R���X�g���N�^ Error! prm_name �̕�������0prm_name="<<prm_name<<"");
//
//    }
//#endif
//    _name = NEW char[51];
//    strcpy(_name, prm_name);
}

template<class T>
T* Node<T>::extract() {
    if (_pParent) {
        //�A������O��
        _pParent->_child_num--;
        T* pMyNext = _pNext;
        T* pMyPrev = _pPrev;
        if (_is_first_flg && _is_last_flg) {
            //�A���������̂ݏꍇ
            _pParent->_pChildFirst = nullptr;
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
                _pParent->_pChildFirst = pMyNext;
            }
        }
        _pParent = nullptr;
        _pNext = (T*)this;
        _pPrev = (T*)this;
        _is_first_flg = true;
        _is_last_flg = true;
        //�c���[�͈ێ�����̂ŁA_pChildFirst ���̂܂܁inullptr�ɂ��Ȃ��j
        return ((T*)this);
    } else {
        //TODO:�R�R�ɏ���������ꍇ�́Aextract()����K�v�Ȃ��B
        //_pParent�����Ȃ��������ɂ��������ĂȂ���extract()����K�v�Ȃ��B
        //�ƁA���߂���Ă��邪�A����́A�v�f��ǉ����邽�߂̃��\�b�h������ appendChild() prependChild() �݂̂ł��邱�Ƃ��O��ƂȂ�B
        //appendChild() prependChild() �݂̂ō����c���[�\���́A�e�̒��_�͏�ɗB��ƂȂ邩�炾�B
        //�����������AaddNext() �̂悤�ɗׂɗv�f��ǉ����郁�\�b�h�����Ȃ���΂����Ȃ��Ȃ����ꍇ�A
        //�e�̒��_�������ю���Ȃ��A��`�̂悤�ȍ\�����̂��悤�ɂ����ꍇ�́A
        //�����̏ꏊ�ɉ��A������̂ݐ؂藣��������ǉ�����K�v�����鎖��Y�ꂸ�ɁB

        return ((T*)this);
    }
}

template<class T>
void Node<T>::moveLast() {
    if (_is_last_flg) { //���ɍŏI�m�[�h�Ȃ�Ή������Ȃ�
        return;
    } else if (_is_first_flg) { //�擪�m�[�h�Ȃ�΁A�e�̎w���Ă���擪�m�[�h�����ւ��炷
        _pParent->_pChildFirst = _pNext;
        _pPrev->_is_last_flg = false;
        _is_first_flg = false;
        _is_last_flg = true;
        _pNext->_is_first_flg = true;
    } else { //���ԃm�[�h��
        //���ׂ̃m�[�h���m���q��
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        //�����m�[�h�Ɛ擪�m�[�h�̊Ԃɂ����肱�܂���
        T* pFirst = _pParent->_pChildFirst; //��First
        T* pLast = pFirst->_pPrev;        //��Last
        pLast->_is_last_flg = false;      //��Last��Last���t���O����
        _is_last_flg = true;              //�����VLast���t���O�Z�b�g
        _pPrev = pLast;                   //���̑O�͌�Last��
        _pNext = pFirst;                  //���̎��͌�First���B
        pLast->_pNext = (T*)this;         //��Last�̎��͉���
        pFirst->_pPrev = (T*)this;        //��First�̑O�͉��ƂȂ�B
    }
}

template<class T>
void Node<T>::moveFirst() {
    if (_is_first_flg) { //���ɐ擪�m�[�h�Ȃ�Ή������Ȃ�
        return;
    } else if (_is_last_flg) { //�����m�[�h�Ȃ�΁A�e�̎w���Ă���擪�m�[�h��O�ɂ��炷
        _pParent->_pChildFirst = (T*)this;
        _pPrev->_is_last_flg = true;
        _is_first_flg = true;
        _is_last_flg = false;
        _pNext->_is_first_flg = false;
    } else { //���ԃm�[�h��
        //���ׂ̃m�[�h���m���q��
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        //�����m�[�h�Ɛ擪�m�[�h�̊Ԃɂ����肱�܂���
        T* pFirst = _pParent->_pChildFirst; //��First
        T* pLast = pFirst->_pPrev;        //��Last
        pFirst->_is_first_flg = false;    //��First��First���t���O����
        _is_first_flg = true;             //�����VFirst���t���O�Z�b�g
        _pPrev = pLast;                   //���̑O�͌�Last�ŁA
        _pNext = pFirst;                  //���̎��͌�First���B
        pLast->_pNext = (T*)this;         //��Last�̎��͉��ŁA
        pFirst->_pPrev = (T*)this;        //��First�̑O�͉��ƂȂ�B
        _pParent->_pChildFirst = (T*)this;  //����ɁA�e��ChildFirst�ƂȂ�̂��B
    }
}

template<class T>
T* Node<T>::getChildByName(const char* prm_child_name) {
#ifdef MY_DEBUG
    if (_pChildFirst == nullptr) {
        throwCriticalException("[Node<" << _class_name << ">::getChild()] Error! _pChildFirst��nullptr�ł��B");
    }
#endif
    T* pNodeTemp = _pChildFirst;
    do {
        if (strcmp(pNodeTemp->getName(), prm_child_name) == 0) {
            break;
        }
#ifdef MY_DEBUG
        if (pNodeTemp->_is_last_flg) {
            throwCriticalException("[Node<" << _class_name << ">::getChild()] Error! �q�m�[�h�͑��݂��܂���B(prm_child_actor_name=" << prm_child_name << ")");
        }
#endif
        pNodeTemp = pNodeTemp->_pNext;
    } while (true);
    return pNodeTemp;
}

template<class T>
T* Node<T>::getChild(T* prm_pChild) const {
    if (_pChildFirst == nullptr) {
        return nullptr;
    }
    T* pNodeTemp = _pChildFirst;
    do {
        if (prm_pChild == pNodeTemp) {
            break;
        }
        if (pNodeTemp->_is_last_flg) {
            return nullptr;
        }
        pNodeTemp = pNodeTemp->_pNext;
    } while (true);
    return pNodeTemp;
}

template<class T>
T* Node<T>::getChild(int prm_index) const {
    T* pNodeTemp = _pChildFirst;
    for (int i = 0; i < prm_index; i++) {
        pNodeTemp = pNodeTemp->_pNext;
    }
    return pNodeTemp;
}

template<class T>
bool Node<T>::hasChild(char* prm_child_actor_name) const {
    if (_pChildFirst == nullptr) {
        return false;
    } else {
        T* pNodeTemp = _pChildFirst;
        do {
            if (strcmp(pNodeTemp->getName(), prm_child_actor_name) == 0) {
                return true;
            }
            if (pNodeTemp->_is_last_flg) {
                return false;
            } else {
                pNodeTemp = pNodeTemp->_pNext;
            }
        } while (true);
    }
}

template<class T>
void Node<T>::appendChild(T* prm_pChild) {
#ifdef MY_DEBUG
    if (prm_pChild->_pParent) {
        throwCriticalException("[Node<" << _class_name << ">::appendChild()] Error! �����m�[�h�͊��ɏ���("
                << prm_pChild->_pParent->_name << "�ɏ���)���Ă��܂�(this=" << _name << "/prm_pChild=" << prm_pChild->getName() << ")");
    }
#endif
    prm_pChild->_pParent = (T*)this;
    prm_pChild->_is_last_flg = true;
    if (_pChildFirst == nullptr) { //�ŏ��̎q
        prm_pChild->_is_first_flg = true;
        _pChildFirst = prm_pChild;
        _pChildFirst->_pNext = prm_pChild;
        _pChildFirst->_pPrev = prm_pChild;
    } else {  //�Q�ڈȍ~�̎q
        prm_pChild->_is_first_flg = false;
        T* pChildLast = _pChildFirst->_pPrev;
        pChildLast->_is_last_flg = false;
        pChildLast->_pNext = prm_pChild;
        prm_pChild->_pPrev = pChildLast;
        prm_pChild->_pNext = _pChildFirst;
        _pChildFirst->_pPrev = prm_pChild;
    }
    _child_num++;
}

template<class T>
void Node<T>::prependChild(T* prm_pChild) {
#ifdef MY_DEBUG
    if (prm_pChild->_pParent) {
        throwCriticalException("[Node<" << _class_name << ">::prependChild()] Error! �����m�[�h�͊��ɏ���("
                << prm_pChild->_pParent->_name << "�ɏ���)���Ă��܂�(this=" << _name << "/prm_pChild=" << prm_pChild->getName() << ")");
    }
#endif
    prm_pChild->_pParent = (T*)this;
    prm_pChild->_is_first_flg = true;
    if (_pChildFirst == nullptr) { //�ŏ��̎q
        prm_pChild->_is_last_flg = true;
        prm_pChild->_pNext = prm_pChild;
        prm_pChild->_pPrev = prm_pChild;
    } else {
        prm_pChild->_is_last_flg = false;
        T* pChildLast = _pChildFirst->_pPrev;
        pChildLast->_pNext = prm_pChild;
        prm_pChild->_pPrev = pChildLast;
        prm_pChild->_pNext = _pChildFirst;
        _pChildFirst->_pPrev = prm_pChild;
        _pChildFirst->_is_first_flg = false;
    }
    _pChildFirst = prm_pChild;

    _child_num++;
}

/*
 template<class T>
 bool Node<T>::isNamed(const char* prm_name) {
 char*::size_type iLen = prm_name.length();
 if (prm_name.rfind('*') == iLen-1) {}


 return _name;
 }
 */


template<class T>
Node<T>::~Node() {
    //�����Ɏq������ꍇ
    if (_pChildFirst) {
        //�܂��q��delete
        if (_pChildFirst->_is_last_flg) {
            //�q�m�[�h�͂P�̏ꍇ
            GGAF_DELETE(_pChildFirst);
            _pChildFirst = nullptr;
        } else {
            //�q�m�[�h�͂Q�ȏ�̏ꍇ
            T* pChildLast = _pChildFirst->_pPrev;
            T* pChildLastPrev = pChildLast->_pPrev;
            while (true) {
                GGAF_DELETE(pChildLast); //��������delete
                if (pChildLastPrev->_is_first_flg) {
                    GGAF_DELETE(_pChildFirst); //pChildLastPrev == _pChildFirst �ł���
                    _pChildFirst = nullptr;
                    break;
                }
                pChildLast = pChildLastPrev;
                pChildLastPrev = pChildLastPrev->_pPrev;
            }
        }
    }

    //�q���Ȃ���Ԃ̏ꍇ
    if (_pParent) {
        _pParent->_child_num--;
        //�A������O��
        T* pMyNext = _pNext;
        T* pMyPrev = _pPrev;
        if (_is_first_flg && _is_last_flg) {
            //�A�����Ă���m�[�h�������A�����̂ݏꍇ
            _pParent->_pChildFirst = nullptr;
            _pParent = nullptr;
            _pNext = (T*)this;
            _pPrev = (T*)this;
            _pChildFirst = nullptr;
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
                _pParent->_pChildFirst = pMyNext;
            }
            _pParent = nullptr;
            _pNext = (T*)this;
            _pPrev = (T*)this;
            _pChildFirst = nullptr;
            _is_first_flg = true;
            _is_last_flg = true;
        }
    }
    GGAF_DELETEARR(_name);
}

}
#endif /*GGAF_CORE_NODE_H_*/
