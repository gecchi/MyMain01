#ifndef GGAF_CORE_REPEATSEQ_H_
#define GGAF_CORE_REPEATSEQ_H_
#include "jp/ggaf/GgafCommonHeader.h"

#include <map>
#include <string>
#ifndef _MSC_VER
    #include <atomic>
#endif

namespace GgafCore {

/**
 * 順序クラス(単一スレッド用。スレッドセーフでは有りません) .
 * データベースのシークエンス（順序オブジェクト）のように、採番します。
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class RepeatSeq {
private:
    class Seq {
    public:
        int _value;
        int _min;
        int _max;
    public :
        Seq() : _value(0), _min(0), _max(0)  {}
        inline void init(int min, int max) {
            _min = min;
            _max = max;
            _value = _min;
        }
        inline void setMin() {
            _value = _min;
        }
        inline void setMax() {
            _value = _max;
        }
        inline void set(int val) {
            _value = val;
        }
        inline int nextVal() {
            _value++;
            if (_value > _max) {
                _value = _min;
            }
            return _value;
        }
    };

    static std::map<std::string, RepeatSeq::Seq> _mapSeq;

#ifdef _MSC_VER
    //TODO:VC++2005以降(x86) の volatile は、メモリバリア効果がある（と思う）。
    //gcc(x86)は、アトミック保証は無いが std::atomic が使える。VC++に atomic が実装されるまではとりあえず・・・。
    static volatile bool _is_lock;
#else
    static volatile std::atomic<bool> _is_lock;
#endif

public:
    /**
     * 順序オブジェクトを作成 .
     * @param ID 紐つける順序オブジェクトID（任意)
     * @param min 最小値
     * @param max 最大値
     */
    static void create(std::string ID, int min, int max);
    static void create(const char* ID, int min, int max);

    /**
     * IDの順序オブジェクトが作成済みか調べる .
     * @param ID 順序オブジェクトID
     * @return true:生成済み／false:未生成
     */
    static bool isExist(std::string& ID);
    static bool isExist(const char* ID);   static void set(std::string& ID, int val);
    static void set(const char* ID, int val);
    static void setMax(std::string& ID);
    static void setMax(const char* ID);
    static void setMin(std::string& ID);
    static void setMin(const char* ID);

    /**
     * 順序オブジェクトから採番し、内部カウントを次の値にセットしておく .
     * @param ID 作成時の順序オブジェクトID
     * @return 現在の値
     */
    static int nextVal(std::string& ID);
    static int nextVal(const char* ID);
};

}
#endif /*GGAF_CORE_REPEATSEQ_H_*/
