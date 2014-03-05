#ifndef GGAFCORE_GGAFENUMINDEX_H_
#define GGAFCORE_GGAFENUMINDEX_H_
#include "jp/ggaf/core/GgafObject.h"
#include <map>

#include "jp/ggaf/core/exception/GgafCriticalException.h"

namespace GgafCore {

/**
 * �񋓒l�Ə������X�g .
 * enum �̗񋓒l(0,1,2,3�E�E�E)�𗘗p����v���O�����ŁA
 * enum�錾��ɓ��I�ɗv�f�����炵�����A�Ƃ������ꍇ�Ɏg�p����݌v�B
 * @version 1.00
 * @since 2014/03/04
 * @author Masatoshi Tsuge
 */
class GgafEnumIndex : public GgafObject {
public:
    /** �񋓂̒l�F����(0�`) */
    std::map<int, int> _n;

    /**
     *
     * @param prm_num �ő�̗񋓂̒l
     * @param prm_enum_start_index �P�Ԗڂ̗񋓂̒l
     */
    GgafEnumIndex(int prm_enum_start, int prm_enum_end) {
        for(int i = 0; i <= prm_enum_end-prm_enum_start; i++) {
            _n[(prm_enum_start+i)] = i;
        }
    }

    /**
     * �񋓂̒l����A����(0�`)�𓾂� .
     * @param prm_key �񋓂̒l
     * @return ����(0�`)
     */
    inline int n(int prm_key) {
#ifdef MY_DEBUG
        if (_n.find(prm_key) != _n.end()) {
            //OK
        } else {
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
