#ifndef GGAF_CORE_ENUMINDEX_H_
#define GGAF_CORE_ENUMINDEX_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <map>
#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * �񋓒l�Ə������X�g .
 * enum �̗񋓒l(0,1,2,3�E�E�E)�𗘗p����v���O�����ŁA
 * enum�錾��ɓ��I�ɗv�f�����炵�����A�Ƃ������ꍇ�Ɏg�p����݌v�B<BR>
 * ���g�p�၄
 * <pre><code>
 *
 *     enum {
 *         ITEM_KEY_CONFIG = 0 ,
 *         ITEM_SOUND_CONFIG,
 *         ITEM_SCREEN_CONFIG,
 *         ITEM_BACK,
 *     };
 *
 *     EnumIndex itm(ITEM_KEY_CONFIG, ITEM_BACK);
 *     int index, enm; //index=����, enm=�񋓒l
 *     index = itm.index(ITEM_KEY_CONFIG);      //index = 0
 *     index = itm.index(ITEM_SOUND_CONFIG);    //index = 1
 *     index = itm.index(ITEM_SCREEN_CONFIG);   //index = 2
 *     index = itm.index(ITEM_BACK);            //index = 3
 *
 *     enm = itm.enm(0);                    //enm = ITEM_KEY_CONFIG    = 0
 *     enm = itm.enm(1);                    //enm = ITEM_SOUND_CONFIG  = 1
 *     enm = itm.enm(2);                    //enm = ITEM_SCREEN_CONFIG = 2
 *     enm = itm.enm(3);                    //enm = ITEM_BACK          = 3
 *
 *     itm.remove(ITEM_SOUND_CONFIG);   //ITEM_SOUND_CONFIG���폜�������Ƃɂ���B
 *
 *     //�񋓒l���p�����[�^�ɂ��āA�����𓾂�B
 *     index = itm.index(ITEM_KEY_CONFIG);      //index = 0
 *     index = itm.index(ITEM_SOUND_CONFIG);    //�G���[�i�f�o�b�O�r���h��)
 *     index = itm.index(ITEM_SCREEN_CONFIG);   //index = 1
 *     index = itm.index(ITEM_BACK);            //index = 2
 *     //�������p�����[�^�ɂ��āA�񋓒l�𓾂�B
 *     enm = itm.enm(0);                    //enm = ITEM_KEY_CONFIG    = 0
 *     enm = itm.enm(1);                    //enm = ITEM_SCREEN_CONFIG = 2
 *     enm = itm.enm(2);                    //enm = ITEM_BACK          = 3
 *     enm = itm.enm(3);                    //enm = -1; (�͈͊O��-1)
 *
 * </code></pre>
 * @version 1.00
 * @since 2014/03/04
 * @author Masatoshi Tsuge
 */
class EnumIndex : public Object {
public:
    /** �񋓂̒l�F����(0�`) */
    std::map<int, int> _index;
    int _enum_start;
    int _enum_end;

    /**
     * �R���X�g���N�^ .
     * @param prm_num �ő�̗񋓂̒l
     * @param prm_enum_start_index �P�Ԗڂ̗񋓂̒l
     */
    EnumIndex(int prm_enum_start, int prm_enum_end) {
        _enum_start = prm_enum_start;
        _enum_end = prm_enum_end;
        for (int i = 0; i <= prm_enum_end-prm_enum_start; i++) {
            _index[(prm_enum_start+i)] = i;
        }
    }

    /**
     * �񋓒l�Ə������X�g�̑Ή������Z�b�g����B
     */
    inline void reset() {
        for (int i = 0; i <= _enum_end-_enum_start; i++) {
            _index[(_enum_start+i)] = i;
        }
    }

    /**
     * �񋓂̒l����A����(0�`)�𓾂� .
     * @param prm_enm_value �񋓂̒l
     * @return ����(0�`)
     */
    inline int index(int prm_enum_value) {
#ifdef MY_DEBUG
        if (_index.find(prm_enum_value) == _index.end()) {
            throwCriticalException("EnumIndex#index() �񋓒l prm_enum_value="<<prm_enum_value<<" ��remove���ꂽ�����݂��܂���");
        }
#endif
        return _index[prm_enum_value];
    }

    /**
     * ����(0�`)���猳�̗񋓂̒l�𓾂�B
     * �͈͊O�̏������w�肵���ꍇ�A-1��Ԃ�
     * @param prm_index ����(0�`)
     * @return ���̗񋓂̒l or �����͈͊O�̏ꍇ�� -1
     */
    inline int enm(int prm_index) {
        if ((int)_index.size() <= prm_index) {
            return -1;
        }
        std::map<int, int>::iterator it = _index.begin();
        for (int i = 0; i < prm_index; i++) {
            ++it;
        }
        return it->first;
    }

    /**
     * �񋓗v�f���폜���A������U�蒼�� .
     * @param prm_key �폜����񋓗v�f�̒l
     */
    void remove(int prm_key) {
        _index.erase(prm_key);
        //value ���l�߂ĐU�蒼��
        int i = 0;
        for (std::map<int, int>::iterator it = _index.begin(); it != _index.end(); ++it) {
            it->second = i;
            i++;
        }
    }
    /**
     * �񋓗v�f���폜(�͈�)���A������U�蒼�� .
     * @param prm_from  �폜����񋓗v�f�̊J�n�l
     * @param prm_to    �폜����񋓗v�f�̏I���l
     */
    void remove(int prm_from, int prm_to) {
        for (int i = prm_from; i <= prm_to; i++) {
            _index.erase(i);
        }
        //value ���l�߂ĐU�蒼��
        int i = 0;
        for (std::map<int, int>::iterator it = _index.begin(); it != _index.end(); ++it) {
            it->second = i;
            i++;
        }
    }

//    void dump() {
//        for (std::map<int, int>::iterator it = _index.begin(); it != _index.end(); ++it) {
//            std::cout << it->first << "->" << it->second << std::endl;
//        }
//    }

    ~EnumIndex() {
    }
};

}
#endif /*GGAF_CORE_ENUMINDEX_H_*/
