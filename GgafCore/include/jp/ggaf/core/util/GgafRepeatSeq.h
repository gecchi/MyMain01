#ifndef GGAFREPEATSEQ_H_
#define GGAFREPEATSEQ_H_
namespace GgafCore {

/**
 * ユーティリティクラス .
 * 汎用的な静的関数はできるだけここに記述。
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class GgafRepeatSeq {
public:
    static std::map<std::string, int> mapNowval;
    static std::map<std::string, int> mapMaxval;
    static std::map<std::string, int> mapMinval;
    static bool isExist(std::string ID);
    static int create(std::string ID, int min, int max);
    static int nextVal(std::string ID);
};

}
#endif /*GGAFREPEATSEQ_H_*/
