#ifndef GGAFCORE_GGAFUTIL_H_
#define GGAFCORE_GGAFUTIL_H_

#include "jp/ggaf/core/util/CmRandomNumberGenerator.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <limits.h>
#include <iomanip>
#include "jp/ggaf/core/exception/GgafCriticalException.h"

#define HASHVAL(X) const static hashval X = GgafCore::GgafUtil::easy_hash(#X)

#define XTOS(X) (GgafCore::GgafUtil::_xtos_(X))
#define STOI(X) (GgafCore::GgafUtil::_stoi_(X))
#define ABS(X) (GgafCore::GgafUtil::_abs_(X))
#define SGN(X) (GgafCore::GgafUtil::_sgn_(X))
#define MAX3(a,b,c) (GgafCore::GgafUtil::_max3_(a,b,c))
#define MIN3(a,b,c) (GgafCore::GgafUtil::_min3_(a,b,c))

#define ZEROf_EQ(X) (GgafCore::GgafUtil::_zerof_eq_(X))
#define ONEf_EQ(X) (GgafCore::GgafUtil::_zerof_eq_((X)-1.0f))
#define ZEROd_EQ(X) (GgafCore::GgafUtil::_zerod_eq_(X))
#define ONEd_EQ(X) (GgafCore::GgafUtil::_zerod_eq_((X)-1.0))

#define RND(__FROM__,__TO__) (GgafCore::GgafUtil::_rnd_int32_(__FROM__,__TO__))
#define RND_ABOUT(__BASE_VALUE__, __MARGIN__) (RND((__BASE_VALUE__ - __MARGIN__), (__BASE_VALUE__ + __MARGIN__)))

typedef std::map<std::string, std::string> GgafStrMap;
/** ハッシュ数値 */
typedef uint64_t hashval;

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL GgafCore::GgafUtil

namespace GgafCore {

/**
 * ユーティリティクラス .
 * 汎用的な静的関数はできるだけここに記述。
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class GgafUtil {
public:
    static uint32_t _timex;

public:
    static uint32_t getSystemTime();

    /**
     * ファイル読み込み .
     * 戻り値は呼び元で delete[] する必要があります。
     * @param prm_filename
     * @return
     */
    static char* getFileText(std::string prm_filename);

    /**
     * デミリタで分割 .
     * 空文字要素は飛ばされる。
     * <pre>
     * 【例】
     * std::vector<std::string> data = split("\taaa\tbbb\t\t\tcccc\tddd\teeee\t\t", "\t");
     * ＜結果＞
     * data[0] = aaa
     * data[1] = bbb
     * data[2] = cccc
     * data[3] = ddd
     * data[4] = eeee
     * </pre>
     * @param str 文字列
     * @param delim 分割文字
     * @return 分割されたvector
     */
    static inline std::vector<std::string> split(std::string str, std::string delim) {
        std::vector<std::string> r;
        size_t cutAt;
        while ((cutAt = str.find_first_of(delim)) != str.npos) {
            if (cutAt > 0) {
                r.push_back(str.substr(0, cutAt));
            }
            str = str.substr(cutAt + 1);
        }
        if (str.length() > 0) {
            r.push_back(str);
        }
        return r;
    }



    /**
     * 移動加速度を、「停止時移動距離」「現時点の速度」により求める .
     * <pre><code>
     *
     *    速度(v)
     *     ^       a:減加速度    ・・・今回求める値
     *     |       D:移動距離    ・・・引数
     *     |      V0:現時点の速度・・・引数
     *   V0|      Te:停止するフレーム・・・求めません
     *     |＼
     *     |  ＼
     *     |    ＼ 斜辺の傾きa
     *     |   D  ＼
     *     |        ＼
     *   --+----------＼-----> 時間(t)
     *   0 |          Te
     * </code></pre>
     * 上図のような状態を想定し、引数の距離(D)から、加速度(a)を計算し設定している。<BR>
     * 停止までのフレーム(Te) は 距離(D) により変化するため指定不可。<BR>
     * @param D  v目標到達速度に達するまでに費やす距離(D)
     * @param V0 現時点の速度(V0)
     * @return 必要な加速度(a)
     */
    static inline double getAcceToStop(double D, double V0) {
#ifdef MY_DEBUG
        if (ZEROd_EQ(D)) {
            throwGgafCriticalException("GgafDxUtil::getAcceToStop() DがZEROです。D="<<D);
        }
#endif
        // D = (1/2) V0 Te  ・・・①
        // a = -V0 / Te     ・・・②
        // ①より
        // Te = 2D / V0
        // これを②へ代入
        // a = -V0 / (2D / V0)
        // ∴ a = -(V0^2) / 2D
        return -(V0*V0) / (2.0*D);
    }

    /**
     * 移動加速度を、「移動距離」「現時点の速度」「目標到達速度」により求める .
     * <pre><code>
     *    速度(v)
     *     ^        a:加速度      ・・・今回求める値
     *     |        D:移動距離    ・・・引数
     *     |       V0:現時点の速度・・・引数
     *     |       Vt:目標到達速度・・・引数
     *     |       Te:目標到達速度に達した時の時間・・・求めません
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> 時間(t)
     *   0 |        Te
     *
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、移動距離(D)から、加速度(a)を計算し設定している。<BR>
     * 目標到達まで必要なフレーム(Te) はパラメータにより変化するため指定不可。<BR>
     * @param D  v目標到達速度に達するまでに費やす距離(D)
     * @param V0 現時点の速度(V0)
     * @param Vt 目標到達速度(Vt)
     * @return 必要な加速度(a)
     */
    static inline double getAcceByVd(double V0, double Vt, double D) {
#ifdef MY_DEBUG
        if (ZEROd_EQ(D)) {
            throwGgafCriticalException("GgafDxUtil::getAcceByVd() DがZEROです。D="<<D);
        }
#endif
        //D = (1/2) (V0 + Vt) Te   ・・・①
        //a = (Vt - V0) / Te       ・・・②
        //②より Te = (Vt - V0) / a
        //これを①へ代入
        //D = (Vt^2 - V0^2) / 2a
        //∴ a = (Vt^2 - V0^2) / 2D
        return ((Vt*Vt) - (V0*V0)) / (2.0*D);
    }

//    static inline double getTimeByD(double D, double V0, double Vt) {
//
//
//    }
    /**
     * 移動加速度を、「費やす時間」「現時点の速度」「目標到達速度」により求める .
     * <pre><code>
     *    速度(v)
     *     ^        a:加速度      ・・・今回求める値
     *     |        D:移動距離    ・・・求めません
     *     |       V0:現時点の速度・・・引数
     *     |       Vt:目標到達速度・・・引数
     *     |       Te:目標到達速度に達した時の時間・・・引数
     *   Vt|........
     *     |      ／|
     *     |    ／  |
     *     |  ／    |   斜辺の傾きa
     *     |／      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> 時間(tフレーム)
     *   0 |        Te
     *
     * </code></pre>
     * 上図のような状態を想定し、目標到達速度(Vt)と、その到達時間(Te) から、加速度(a)を計算し設定している。<BR>
     * 移動距離(D)は、パラメータにより変化するため指定不可。<BR>
     * @param Te 費やす時間(Te)
     * @param V0 現時点の速度(V0)
     * @param Vt 目標到達速度(Vt)
     * @return 必要な加速度(a)
     */
    static inline double getAcceByTv(double Te, double V0, double Vt) {
#ifdef MY_DEBUG
        if (ZEROd_EQ(Te)) {
            throwGgafCriticalException("GgafDxUtil::getAcceByTv() TeがZEROです。Te="<<Te);
        }
#endif
        //a = (Vt-V0) / Te
        return (Vt - V0) / Te;
    }


    /**
     * float 用 0 っぽいのかどうか判定 .
     * @param val 判定したい値
     * @param epsilon 0っぽい範囲
     * @return true:0っぽい / false:0っぽくない
     */
    static inline bool _zerof_eq_(float val, float epsilon = 1e-5f ) {
        return (-epsilon < val && val < epsilon);
    }

    /**
     * double 用 0 っぽいのかどうか判定 .
     * @param val 判定したい値
     * @param epsilon 0っぽい範囲
     * @return true:0っぽい / false:0っぽくない
     */
    static inline bool _zerod_eq_(double val, double epsilon = 1e-13) {
        return (-epsilon < val && val < epsilon);
    }

    /**
     * いろいろな型の値を文字列に変換 .
     * @param prm_x
     * @return 文字列
     */
    template<typename T>
    static inline std::string _xtos_(T prm_x) {
        std::ostringstream oss;
        oss << prm_x;
        return oss.str();
    }

    /**
     * いろいろな型の値を文字列に変換の bool 特殊化 .
     * @param prm_x
     * @return
     */
    template<typename T>
    static inline std::string _xtos_(bool prm_x) {
        if (prm_x) {
            return "true";
        } else {
            return "false";
        }
    }

    /**
     * 文字列を int に変換 .
     * @param prm_s
     * @return
     */
    static inline int _stoi_(std::string& prm_s) {
        int n;
        std::istringstream istr(prm_s);
        istr >> n;
        return n;
    }

    /**
     * C文字列比較 .
     * @param s1
     * @param s2
     * @return s1 > s2 で正の値、s1 < s2 で負の値、s1 = s2で 0 を返す。
     */
    static inline int strcmp_ascii(const char* s1, const char* s2) {
        while (*s1 == *s2++)
            if (*s1++ == 0) return (0);
        return (*s1 - *(s2 - 1));
    }

    /**
     * C文字列比較 .
     * @param s1
     * @param s2
     * @return s1 > s2 で正の値、s1 < s2 で負の値、s1 = s2で 0 を返す。
     */
    static inline int strcmp_ascii(char* s1, const char* s2) {
        while (*s1 == *s2++)
            if (*s1++ == 0) return (0);
        return (*s1 - *(s2 - 1));
    }

    /**
     * 10進数-->2進数文字列変換関数
     * @param prm_decimal
     * @param out_binstr 2進数文字列化  char[33]  [out]
     * @param bitnum 所望の２進数ビット数
     */
    static inline void strbin(uint32_t prm_decimal, char* out_binstr, int bitnum = 32){
        /* 10進数-->2進数変換 */
        int i, k;
        for (i = 0, k = bitnum - 1; k >= 0; i++, k--) {
            if ((prm_decimal >> i) & 1) out_binstr[k] = '1';
            else out_binstr[k] = '0';
        }
        out_binstr[i] = '\0';

        /* 変換結果の例00011001における、上位桁の000を削除する処理 */
//        for (i = 0; i < BITS_DIGIT; i++) {
//            if (BinaryString[0] == '0') memmove(BinaryString, BinaryString + 1, BITS_DIGIT);
//            else break;
//        }
    }

//    static inline const hashval easy_hash(const char* str) {
//        hashval hash = 5381;
//        char c;
//        while ((c = *str++) > 0) { //strの\0までループ （演算子 "==" と間違えていません）
//            hash = ((hash << 5) + hash) + c; // hash * 33 + c  33倍してます
//        }
//        return hash;
//    }
//
//    static inline const hashval easy_hash(char* str) {
//        hashval hash = 5381;
//        char c;
//        while ((c = *str++) > 0) { //strの\0までループ （演算子 "==" と間違えていません）
//            hash = ((hash << 5) + hash) + c; // hash * 33 + c  33倍してます
//        }
//        return hash;
//    }



    static inline const hashval easy_hash(const char* str) {
        //APHash
        hashval hash = 0xAAAAAAAA;
        char c;
        for (std::size_t i = 0; (c = *str++) > 0; i++) {
            hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ c * (hash >> 3)) :
                                     (~((hash << 11) + (c ^ (hash >> 5))));
        }
        return hash;
    }

    static inline const hashval easy_hash(char* str) {
        //APHash
        hashval hash = 0xAAAAAAAA;
        char c;
        for (std::size_t i = 0; (c = *str++) > 0; i++) {
            hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ c * (hash >> 3)) :
                                     (~((hash << 11) + (c ^ (hash >> 5))));
        }
        return hash;
    }

    /**
     * 符号判定.
     * @param x
     * @return
     */
    template<typename T>
    static inline T _sgn_(T x) {
        return x<0 ? -1 : x>0;
    }

    /**
     * 絶対値を求める
     * @param x
     * @return
     */
    template<typename T>
    static inline T _abs_(T x) {
        return x < 0 ? -x : x;
    }

    static inline int _abs_(int x) {
        return (x == INT_MIN) ? INT_MAX : (x < 0 ? -x : x);
    }

    template<typename T>
    static inline T _max2_(T a, T b) {
        return ( ((a) > (b) ? (a) : (b))   );
    }

    template<typename T>
    static inline T _max3_(T a, T b, T c) {
        return ( (a)>(b) ? ((a)>(c)?(a):(c)) : ((b)>(c)?(b):(c)) );
    }

    template<typename T>
    static inline T _min3_(T a, T b, T c) {
        return ( (a) < ((b)<(c)?(b):(c)) ? (a) : ((b)<(c)?(b):(c)) );
    }

    static inline size_t hex2dec(const std::string &prm_hex) {
        std::istringstream iss(prm_hex);
        size_t val;
        iss >> std::hex >> val;
        return val;
    }
    static inline const std::string dec2hex(size_t prm_dec) {
        std::ostringstream oss;
        oss << std::hex << std::uppercase << prm_dec;
        return oss.str();
    }
    static inline const std::string dec2hex(size_t prm_dec, int prm_keta) {
        std::ostringstream oss;
        oss << std::setw(prm_keta) << std::hex << std::setfill('0') << std::uppercase << prm_dec;
        return oss.str();
    }

    static inline char m_hex(int nibble) {
        static const char *digits = "0123456789ABCDEF";
        return digits[(nibble & 0xf)];
    }

    static inline std::string trim(std::string& str) {
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ')+1);
        return str;
    }

    /**
     * int32_tランダム関数 .
     * prm_from と prm_to が逆転してはいけない(負の%演算は、VC++での動作は不定のため)
     * @param prm_from
     * @param prm_to
     * @return
     */
    static int32_t _rnd_int32_(int32_t prm_from, int32_t prm_to);

    static void readProperties(std::string filename, GgafStrMap* pMap);
    static void readProperties(std::istream &is, GgafStrMap* pMap);
    static void writeProperties(const char *filename, GgafStrMap* pMap, const char *header = nullptr);
    static void writeProperties(std::ostream &os, GgafStrMap* pMap, const char *header = nullptr);
    static void printProperties(std::ostream &os, GgafStrMap* pMap);

    static bool isExistKey(std::string prm_key, GgafStrMap* p);
    static bool cnvBool(std::string prm_str);

    static std::string getFileBaseNameWithoutExt(const char* prm_filepath);
    static std::string getFileBaseName(const char* prm_filepath);
    static std::string getFileDirName(const char* prm_filepath);
    static std::string getFileExt(const char* prm_filepath);

    static char* reverseStr(char* str);
    static void strReplace(std::string& str, const std::string& from, const std::string& to);

    /**
     * 数値を左ゼロ埋め文字列に変換 .
     * 数値の桁が既に prm_total_keta より多い場合は、
     * prm_data_num の文字列が返る。
     * @param prm_data_num    数値
     * @param prm_total_keta  全体の文字桁数
     * @return 左ゼロ埋めされた文字列
     */
    static std::string padZeroStr(int prm_data_num, int prm_total_keta);

    static std::string getSystemDateTimeStr();
};

}
#endif /*GGAFCORE_GGAFUTIL_H_*/

//printf("01  [%s]\n", UTIL::getFileBaseNameWithoutExt("c:\\cview_gamen_all.pdf").c_str());
//printf("02  [%s]\n", UTIL::getFileBaseNameWithoutExt("c:\\cview_gamen.all.pdf").c_str());
//printf("03  [%s]\n", UTIL::getFileBaseNameWithoutExt("c:\\c.all.pdf").c_str());
//printf("04  [%s]\n", UTIL::getFileBaseNameWithoutExt("c:\\.cproj").c_str());
//printf("05  [%s]\n", UTIL::getFileBaseNameWithoutExt("c:\\cview_gamen_all\\").c_str());
//printf("06  [%s]\n", UTIL::getFileBaseNameWithoutExt("/www/htdocs/index.html").c_str());
//printf("07  [%s]\n", UTIL::getFileBaseNameWithoutExt("/www/htdocs/app").c_str());
//printf("08  [%s]\n", UTIL::getFileBaseNameWithoutExt("/www/htdocs/app/").c_str());
//printf("09  [%s]\n", UTIL::getFileBaseNameWithoutExt("").c_str());
//printf("10  [%s]\n", UTIL::getFileBaseName("c:\\cview_gamen_all.pdf").c_str());
//printf("11  [%s]\n", UTIL::getFileBaseName("c:\\cview_gamen_all\\").c_str());
//printf("12  [%s]\n", UTIL::getFileBaseName("/www/htdocs/index.html").c_str());
//printf("13  [%s]\n", UTIL::getFileBaseName("/www/htdocs/app").c_str());
//printf("14  [%s]\n", UTIL::getFileBaseName("/www/htdocs/app/").c_str());
//printf("15  [%s]\n", UTIL::getFileBaseName("").c_str());
//printf("16  [%s]\n", UTIL::getFileDirName("c:\\www\\htdocs\\index.html").c_str());
//printf("17  [%s]\n", UTIL::getFileDirName("/www/htdocs/app").c_str());
//printf("18  [%s]\n", UTIL::getFileDirName("/www/htdocs/app/").c_str());
//printf("19  [%s]\n", UTIL::getFileDirName("").c_str());
//printf("20  [%s]\n", UTIL::getFileExt("/www/htdocs/index.html").c_str());
//printf("21  [%s]\n", UTIL::getFileExt("/www/htdocs/index.php").c_str());
//printf("22  [%s]\n", UTIL::getFileExt("/www/htdocs/lamda").c_str());
//printf("23  [%s]\n", UTIL::getFileExt("").c_str());
//＜実行結果＞
//01  [cview_gamen_all]
//02  [cview_gamen]
//03  [c]
//04  []
//05  [cview_gamen_all]
//06  [index]
//07  [app]
//08  [app]
//09  []
//10  [cview_gamen_all.pdf]
//11  [cview_gamen_all]
//12  [index.html]
//13  [app]
//14  [app]
//15  []
//16  [c:\www\htdocs]
//17  [/www/htdocs]
//18  [/www/htdocs]
//19  []
//20  [html]
//21  [php]
//22  []
//23  []

