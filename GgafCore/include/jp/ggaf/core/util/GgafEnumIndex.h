#ifndef GGAFCORE_GGAFENUMINDEX_H_
#define GGAFCORE_GGAFENUMINDEX_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <map>
#include "jp/ggaf/core/exception/GgafCriticalException.h"

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
 *     GgafCore::GgafEnumIndex itm(ITEM_KEY_CONFIG, ITEM_BACK);
 *     int n, e;
 *     n = itm.n(ITEM_KEY_CONFIG);      //n = 0
 *     n = itm.n(ITEM_SOUND_CONFIG);    //n = 1
 *     n = itm.n(ITEM_SCREEN_CONFIG);   //n = 2
 *     n = itm.n(ITEM_BACK);            //n = 3
 *
 *     e = itm.e(0);                    //e = ITEM_KEY_CONFIG    = 0
 *     e = itm.e(1);                    //e = ITEM_SOUND_CONFIG  = 1
 *     e = itm.e(2);                    //e = ITEM_SCREEN_CONFIG = 2
 *     e = itm.e(3);                    //e = ITEM_BACK          = 3
 *
 *     itm.remove(ITEM_SOUND_CONFIG);   //ITEM_SOUND_CONFIG���폜
 *
 *     n = itm.n(ITEM_KEY_CONFIG);      //n = 0
 *     n = itm.n(ITEM_SOUND_CONFIG);    //�G���[�i�f�o�b�O�r���h��)
 *     n = itm.n(ITEM_SCREEN_CONFIG);   //n = 1
 *     n = itm.n(ITEM_BACK);            //n = 2
 *
 *     e = itm.e(0);                    //e = ITEM_KEY_CONFIG    = 0
 *     e = itm.e(1);                    //e = ITEM_SCREEN_CONFIG = 2
 *     e = itm.e(2);                    //e = ITEM_BACK          = 3
 *     e = itm.e(3);                    //e = -1; (�͈͊O��-1)
 *
 * </code></pre>
 * @version 1.00
 * @since 2014/03/04
 * @author Masatoshi Tsuge
 */
class GgafEnumIndex : public GgafObject {
public:
    /** �񋓂̒l�F����(0�`) */
    std::map<int, int> _n;
    int _enum_start;
    int _enum_end;

    /**
     * �R���X�g���N�^ .
     * @param prm_num �ő�̗񋓂̒l
     * @param prm_enum_start_index �P�Ԗڂ̗񋓂̒l
     */
    GgafEnumIndex(int prm_enum_start, int prm_enum_end) {
        _enum_start = prm_enum_start;
        _enum_end = prm_enum_end;
        for(int i = 0; i <= prm_enum_end-prm_enum_start; i++) {
            _n[(prm_enum_start+i)] = i;
        }
    }

    /**
     * �񋓒l�Ə������X�g�̑Ή������Z�b�g����B
     */
    inline void reset() {
        for(int i = 0; i <= _enum_end-_enum_start; i++) {
            _n[(_enum_start+i)] = i;
        }
    }

    /**
     * �񋓂̒l����A����(0�`)�𓾂� .
     * @param prm_key �񋓂̒l
     * @return ����(0�`)
     */
    inline int n(int prm_key) {
#ifdef MY_DEBUG
        if (_n.find(prm_key) == _n.end()) {
            throwGgafCriticalException("GgafEnumIndex#n() �񋓒l prm_key="<<prm_key<<" ��remove���ꂽ�����݂��܂���");
        }
#endif
        return _n[prm_key];
    }

    /**
     * ����(0�`)���猳�̗񋓂̒l�𓾂�B
     * �͈͊O�̏������w�肵���ꍇ�A-1��Ԃ�
     * @param prm_index ����(0�`)
     * @return ���̗񋓂̒l or �����͈͊O�̏ꍇ�� -1
     */
    inline int e(int prm_index) {
        if ((int)_n.size() <= prm_index) {
            return -1;
        }
        std::map<int, int>::iterator it = _n.begin();
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
        _n.erase(prm_key);
        //value ���l�߂ĐU�蒼��
        int i = 0;
        for(std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
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
        for(int i = prm_from; i <= prm_to; i++) {
            _n.erase(i);
        }
        //value ���l�߂ĐU�蒼��
        int i = 0;
        for(std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
            it->second = i;
            i++;
        }
    }


    void dump() {
        for(std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
            std::cout << it->first << "->" << it->second << std::endl;
        }
    }

    ~GgafEnumIndex() {
    }
};

}
#endif /*GGAFCORE_GGAFENUMINDEX_H_*/
