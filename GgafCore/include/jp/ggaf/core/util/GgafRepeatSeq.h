#ifndef GGAFCORE_GGAFREPEATSEQ_H_
#define GGAFCORE_GGAFREPEATSEQ_H_
#include "GgafCommonHeader.h"

#include <map>
#include <string>

namespace GgafCore {

/**
 * 順序クラス(単一スレッド用。スレッドセーフでは有りません) .
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
    static void create(std::string& ID, int min, int max);
    static void create(const char* ID, int min, int max);

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
     * 順序オブジェクトから採番し、内部カウントを次の値にセットしておく .
     * @param ID 作成時の順序オブジェクトID
     * @return 現在の値
     */
    static int nextVal(std::string& ID);
    static int nextVal(const char* ID);
};

}
#endif /*GGAFCORE_GGAFREPEATSEQ_H_*/
