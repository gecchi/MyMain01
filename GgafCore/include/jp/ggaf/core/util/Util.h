#ifndef GGAF_CORE_UTIL_H_
#define GGAF_CORE_UTIL_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/util/CmRandomNumberGenerator.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <limits.h>
#include <iomanip>
#include "jp/ggaf/core/exception/CriticalException.h"

#define DECLARE_EVENT_VAL(X) const static eventval X = (eventval)GgafCore::Util::easy_hash(#X)
#define HASHVAL(X) GgafCore::Util::easy_hash(#X)

#define XTOS(X) (GgafCore::Util::_xtos_(X))
#define STOI(X) (GgafCore::Util::_stoi_(X))
#define ABS(X) (GgafCore::Util::_abs_(X))
#define SGN(X) (GgafCore::Util::_sgn_(X))
#define MAX3(a,b,c) (GgafCore::Util::_max3_((a),(b),(c)))
#define MIN3(a,b,c) (GgafCore::Util::_min3_((a),(b),(c)))

#define ZEROf_EQ(X) (GgafCore::Util::_zerof_eq_(X))
#define ONEf_EQ(X) (GgafCore::Util::_zerof_eq_((X)-1.0f))
#define ZEROd_EQ(X) (GgafCore::Util::_zerod_eq_(X))
#define ONEd_EQ(X) (GgafCore::Util::_zerod_eq_((X)-1.0))

/**
 * 範囲中のある値について、範囲を変換した場合の相対値を取得 .
 * 範囲 MIN_A__ ～ MAX_A__ の A__ の値を、範囲 MIN_B__ ～ MAX_B__ に変換した場合の A__ に対応した値を得る<br>
 */
#define RCNV(MIN_A__,MAX_A__,A__,MIN_B__,MAX_B__)  ( GgafCore::Util::_rcnv_((double)(MIN_A__),(double)(MAX_A__),(double)(A__),(double)(MIN_B__),(double)(MAX_B__)) )

/**
 * 0 ～ 1 の範囲のある値について、範囲を変換した場合の相対値を取得 .
 * 範囲 0 ～ 1 の X_IN_0_1 の値を、範囲 MIN_B__ ～ MAX_B__ に変換した場合の値を得る<br>
 */
#define RCNV_0_1_to(X_IN_0_1,MIN_B__,MAX_B__)  ( GgafCore::Util::_rcnv_0_1_to((double)(X_IN_0_1),(double)(MIN_B__),(double)(MAX_B__)) )

/**
 * 範囲中のある値について、0 ～ 1 の範囲に変換した場合の相対値を取得 .
 * 範囲 MIN_A__ ～ MAX_A__ の A__ の値を、範囲 0 ～ 1 に変換した場合の A__ に対応した値を得る<br>
 */
#define RCNV_to_0_1(MIN_A__,MAX_A__,A__)  ( GgafCore::Util::_rcnv_to_0_1((double)(MIN_A__),(double)(MAX_A__),(double)(A__)) )


/**
 * 整数の乱数を得る .
 * RND(3, 20)
 * → 3～20の乱数を得る 戻りは int32_t 型
 */
#define RND(FROM__,TO__) (GgafCore::Util::_rnd_int32_((int32_t)(FROM__),(int32_t)(TO__)))

/**
 * ある整数の周辺の乱数を得る .
 * RND_ABOUT(15, 4)   意味：15 の±4の範囲の乱数
 * → 11 ～ 19 の乱数になる
 */
#define RND_ABOUT(BASE_VALUE__, MARGIN__) (RND(((int)(BASE_VALUE__) - (int)(MARGIN__)), (BASE_VALUE__ + MARGIN__)))

#define dRND(FROM__,TO__) (GgafCore::Util::_rnd_double_((FROM__),(TO__)))

typedef std::map<std::string, std::string> StrMap;

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL GgafCore::Util

namespace GgafCore {

/**
 * ユーティリティクラス .
 * 汎用的な静的関数はできるだけここに記述。
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class Util {
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
     * デミリタで分割 .
     * @param str 文字列
     * @param delim 分割文字
     * @param split_number_of_times 分割回数
     * @return
     */
    static inline std::vector<std::string> split(std::string str, std::string delim, int split_number_of_times) {
        std::vector<std::string> r;
        size_t cutAt;
        int cnt = 0;
        while ((cutAt = str.find_first_of(delim)) != str.npos) {
            if (cutAt > 0) {
                r.push_back(str.substr(0, cutAt));
            }
            str = str.substr(cutAt + 1);
            cnt++;
            if (split_number_of_times <= cnt) {
                break;
            }
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
            throwCriticalException("DがZEROです。D="<<D);
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
            throwCriticalException("DがZEROです。D="<<D);
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
            throwCriticalException("TeがZEROです。Te="<<Te);
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
     * 10進数-->2進数文字列変換関数
     * @param prm_decimal
     * @param out_binstr 2進数文字列化  char[33]  [out]
     * @param bitnum 所望の２進数ビット数
     */
    static inline void strbin(uint32_t prm_decimal, char* out_binstr, int bitnum = 32) {
        /* 10進数-->2進数変換 */
        int i, k;
        for (i = 0, k = bitnum - 1; k >= 0; i++, k--) {
            if ((prm_decimal >> i) & 1) {
                out_binstr[k] = '1';
            } else {
                out_binstr[k] = '0';
            }
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

    /**
     * 符号判定.
     * @param x
     * @return
     */
    template<typename T>
    static inline int _sgn_(T x) {
        return x < 0 ? -1 : x > 0;
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
     * 範囲中のある値について、範囲を変換した場合の相対値を取得 .
     * 範囲 min_a ～ max_a の a の値を、範囲 min_b ～ max_b に変換した場合の a に対応する値(b) を得る<br>
     */
    static inline double _rcnv_(double min_a, double max_a, double a, double min_b, double max_b) {
        return ( (min_b-max_b)*a - (max_a*min_b) + (max_b*min_a) ) / (min_a-max_a);
    }

    static inline double _rcnv_0_1_to(double x_in_0_1, double min_b, double max_b) {
        return ( (max_b-min_b)*x_in_0_1 + min_b);
    }

    static inline double _rcnv_to_0_1(double min_a, double max_a, double a) {
        return ((min_a-a) / (min_a-max_a));
    }


    /**
     * ３乗根を求める .
     * @param x
     * @return
     */
    static double _cbrt_(double x);
    /**
     * int32_tランダム関数 .
     * prm_from と prm_to が逆転してはいけない(負の%演算は、VC++での動作は不定のため)
     * @param prm_from
     * @param prm_to
     * @return
     */
    static int32_t _rnd_int32_(int32_t prm_from, int32_t prm_to);

    static double _rnd_double_(double prm_from, double prm_to);

    static bool cnvBool(std::string& prm_str);

    static std::string getFileBaseNameWithoutExt(const char* prm_filepath);
    static std::string getFileBaseName(const char* prm_filepath);
    static std::string getFileDirName(const char* prm_filepath);
    static std::string getFileExt(const char* prm_filepath);

    static void reverseStr(char* str);
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
#endif /*GGAF_CORE_UTIL_H_*/

//printf("01  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("c:\\cview_gamen_all.pdf").c_str());
//printf("02  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("c:\\cview_gamen.all.pdf").c_str());
//printf("03  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("c:\\c.all.pdf").c_str());
//printf("04  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("c:\\.cproj").c_str());
//printf("05  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("c:\\cview_gamen_all\\").c_str());
//printf("06  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("/www/htdocs/index.html").c_str());
//printf("07  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("/www/htdocs/app").c_str());
//printf("08  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("/www/htdocs/app/").c_str());
//printf("09  [%s]\n", GgafCore::Util::getFileBaseNameWithoutExt("").c_str());
//printf("10  [%s]\n", GgafCore::Util::getFileBaseName("c:\\cview_gamen_all.pdf").c_str());
//printf("11  [%s]\n", GgafCore::Util::getFileBaseName("c:\\cview_gamen_all\\").c_str());
//printf("12  [%s]\n", GgafCore::Util::getFileBaseName("/www/htdocs/index.html").c_str());
//printf("13  [%s]\n", GgafCore::Util::getFileBaseName("/www/htdocs/app").c_str());
//printf("14  [%s]\n", GgafCore::Util::getFileBaseName("/www/htdocs/app/").c_str());
//printf("15  [%s]\n", GgafCore::Util::getFileBaseName("").c_str());
//printf("16  [%s]\n", GgafCore::Util::getFileDirName("c:\\www\\htdocs\\index.html").c_str());
//printf("17  [%s]\n", GgafCore::Util::getFileDirName("/www/htdocs/app").c_str());
//printf("18  [%s]\n", GgafCore::Util::getFileDirName("/www/htdocs/app/").c_str());
//printf("19  [%s]\n", GgafCore::Util::getFileDirName("").c_str());
//printf("20  [%s]\n", GgafCore::Util::getFileExt("/www/htdocs/index.html").c_str());
//printf("21  [%s]\n", GgafCore::Util::getFileExt("/www/htdocs/index.php").c_str());
//printf("22  [%s]\n", GgafCore::Util::getFileExt("/www/htdocs/lamda").c_str());
//printf("23  [%s]\n", GgafCore::Util::getFileExt("").c_str());
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

