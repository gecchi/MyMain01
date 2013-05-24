#ifndef GGAFREPEATSEQ_H_
#define GGAFREPEATSEQ_H_
#include <map>
#include <string>

namespace GgafCore {

/**
 * 順序クラス .
 * データベースのシークエンス（順序オブジェクト）のように、採番します。
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class GgafRepeatSeq {
public:
    static std::map<std::string, int> mapNowval;
    static std::map<std::string, int> mapMaxval;
    static std::map<std::string, int> mapMinval;

public:
    /**
     * 順序オブジェクトを作成 .
     * @param ID 紐つける順序オブジェクトID（任意)
     * @param min 最小値
     * @param max 最大値
     */
    static void create(std::string ID, int min, int max);

    static void set(std::string& ID, int val);
    static void set(const char* ID, int val);
    static void setMax(std::string& ID);
    static void setMax(const char* ID);
    static void setMin(std::string& ID);
    static void setMin(const char* ID);
    /**
     * IDの順序オブジェクトが作成済みか調べる .
     * @param ID 順序オブジェクトID
     * @return true:生成済み／false:未生成
     */
    static bool isExist(std::string& ID);
    static bool isExist(const char* ID);
    /**
     * 順序オブジェクトから次の値を採番する .
     * @param ID 作成時の順序オブジェクトID
     * @return 前回値の＋１された値。
     *         但し、生成直後は最小値を返す。
     *         また、最大値の次を採番すると最小値を返す（戻る）。
     */
    static int nextVal(std::string& ID);
    static int nextVal(const char* ID);
};

}
#endif /*GGAFREPEATSEQ_H_*/
