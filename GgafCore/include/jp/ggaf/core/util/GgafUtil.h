#ifndef GGAFUTIL_H_
#define GGAFUTIL_H_

#define ITOS(X) (GgafCore::GgafUtil::_itos_(X))
#define STOI(X) (GgafCore::GgafUtil::_stoi_(X))
#define ABS(X) (GgafCore::GgafUtil::_abs_(X))
#define SGN(X) (GgafCore::GgafUtil::_sgn_(X))
#define MAX3(a,b,c) (GgafCore::GgafUtil::_max3_(a,b,c))

#define ZEROf_EQ(X) (GgafCore::GgafUtil::_zerof_eq_(X))
#define ONEf_EQ(X) (GgafCore::GgafUtil::_zerof_eq_((X)-1.0f))
#define RND(__FROM__,__TO__) (GgafCore::GgafUtil::_rnd_int32_(__FROM__,__TO__))

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
    static UINT32 _timex;

    static UINT32 getSystemTime();


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
     * @param str
     * @return
     */
    static inline std::vector<std::string> split(std::string str, std::string delim) {
        std::vector<std::string> r;
        int cutAt;
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
    static inline bool _zerof_eq_(float val, float epsilon = 1e-5f ) {
        return (-epsilon < val && val < epsilon);
    }

    static inline std::string _itos_(int prm_n) {
        std::ostringstream oss;
        oss << prm_n;
        return oss.str();
    }

    static inline int _stoi_(std::string& prm_s) {
        int n;
        std::istringstream istr(prm_s);
        istr >> n;
        return n;
    }
    /**
     * ASCII限定文字列比較 .
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
     * ASCII限定文字列比較 .
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
    static inline void strbin(UINT32 prm_decimal, char* out_binstr, int bitnum = 32){
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

    /**
     * 簡易ハッシュ .
     * 文字列 を、さも一意のような64bit数値に変換。
     * もちろん完全ではない。
     * @param str 文字列
     * @return ハッシュ値
     */
    static inline const hashval easy_hash(const char* str) {
        hashval hash = 5381;
        char c;
        while ((c = *str++) > 0) { //strの\0までループ （演算子 "==" と間違えていません）
            hash = ((hash << 5) + hash) + c; // hash * 33 + c  33倍してます
        }
        return hash;
    }

    static inline const hashval easy_hash(char* str) {
        hashval hash = 5381;
        char c;
        while ((c = *str++) > 0) { //strの\0までループ （演算子 "==" と間違えていません）
            hash = ((hash << 5) + hash) + c; // hash * 33 + c  33倍してます
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

    static inline INT32 _abs_(INT32 x) {
        if (x == INT_MIN) {
            return INT_MAX;
        } else {
            return (x ^ (x>>31)) - (x>>31);
        }
    }

    /**
     * 平方根の近似を求める .
     * 標準sqrtよりも計算が速いが、アバウト。
     * @param a 平方根を求めたい値
     * @param s 精度（計算ループ回数。回数が多いほど正確。省略時19）
     * @return 引数aの平方根近似値
     */
    static inline double sqrt_fast(double a, int s = 19) {
        double ret = 1;
        for (int i = 1; i <= s; i++) {
            ret = 0.5 * (ret + a / ret);
        }
        return ret;
    }

    template<typename T>
    static inline T _max2_(T a, T b) {
        return ( ((a) > (b) ? (a) : (b))   );
    }

    template<typename T>
    static inline T _max3_(T a, T b, T c) {
        return ( (a)>(b) ? ((a)>(c)?(a):(c)) : ((b)>(c)?(b):(c)) );
    }

    static inline size_t hex2dec(const std::string &prm_hex) {
        std::istringstream iss(prm_hex);
        size_t val;
        iss >> std::hex >> val;
        return val;
    }


    static inline std::string trim(std::string& str) {
        str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
        str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
        return str;
    }

    /**
     * INT32ランダム関数 .
     * prm_from と prm_to が逆転してはいけない(負の%演算は、VC++での動作は不定のため)
     * @param prm_from
     * @param prm_to
     * @return
     */
    static inline INT32 _rnd_int32_(INT32 prm_from, INT32 prm_to) {
#ifdef MY_DEBUG
        if (prm_from > prm_to) {
            MessageBox(nullptr, "GgafUtil::_rnd_int32_() from toの大小がおかしい", "不本意な事態", MB_OK|MB_ICONQUESTION|MB_SETFOREGROUND);
        }
#endif
        return ((INT32)(GgafCore::CmRandomNumberGenerator::getInstance()->genrand_int32() % (prm_to - prm_from) ) + prm_from );
    }

    static void readProperties(std::string filename, GgafStrMap* pMap);
    static void readProperties(std::istream &is, GgafStrMap* pMap);
    static void writeProperties(const char *filename, GgafStrMap* pMap, const char *header = nullptr);
    static void writeProperties(std::ostream &os, GgafStrMap* pMap, const char *header = nullptr);
    static void printProperties(std::ostream &os, GgafStrMap* pMap);
    static inline char m_hex(int nibble) {
        static const char *digits = "0123456789ABCDEF";
        return digits[(nibble & 0xf)];
    }
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
#endif /*GGAFUTIL_H_*/

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

