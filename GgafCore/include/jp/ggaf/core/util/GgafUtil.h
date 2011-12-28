#ifndef GGAFUTIL_H_
#define GGAFUTIL_H_

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

    static std::vector<std::string> split(std::string str, std::string delim) {
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

    static std::string itos(int prm_n) {
        std::ostringstream oss;
        oss << prm_n;
        return oss.str();
    }

    /**
     * ASCII限定文字列比較 .
     * @param s1
     * @param s2
     * @return s1 > s2 で正の値、s1 < s2 で負の値、s1 = s2で 0 を返す。
     */
    static int strcmp_ascii(const char* s1, const char* s2) {
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
    static int strcmp_ascii(char* s1, const char* s2) {
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
    static void strbin(UINT32 prm_decimal, char* out_binstr, int bitnum = 32){
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

//    static unsigned int easy_hash(const char* prm_key) {
//        unsigned int n = 0;
//        for (unsigned int i = 1; (*prm_key) != '\0'; i++) {
//            n = n * 33  + ((*prm_key)-32);
//            prm_key++;
//        }
//        return n;
//        //n = n * 33  + ((*prm_key)-32); とした理由メモ
//        //-32 は ' '(ASCII:32番) 以降の文字しか扱わないため
//        //33を乗ずると、なんか衝突が少ないらしい
//    }

    /**
     * 簡易ハッシュ .
     * 文字列 を、さも一意のような64bit数値に変換。
     * もちろん完全ではない。
     * @param str 文字列
     * @return ハッシュ値
     */
    static const hashval easy_hash(const char* str) {
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
    static T sign(T x) {
        if (x < 0) {
            return -1;
        } else if (x > 0) {
            return 1;
        } else {
            return 0;
        }

    }


    /**
     * 絶対値を求める
     * @param x
     * @return
     */
    template<typename T>
    static T abs(T x) {
        if (x < 0) {
            return (T)(-1.0* x);
        } else if (x > 0) {
            return x;
        } else {
            return (T)0.0;
        }
    }

    static int abs(int x) {
        if (x < 0) {
            return -x;
        } else if (x > 0) {
            return x;
        } else {
            return 0;
        }
    }

    /**
     * 平方根の近似を求める .
     * 標準sqrtよりも計算が速いが、アバウト。
     * @param a 平方根を求めたい値
     * @param s 精度（計算ループ回数。回数が多いほど正確。省略時19）
     * @return 引数aの平方根近似値
     */
    static double sqrt_fast(double a, int s = 19) {
        double ret = 1;
        for (int i = 1; i <= s; i++) {
            ret = 0.5 * (ret + a / ret);
        }
        return ret;
    }

    //static DWORD max3(DWORD a, DWORD b, DWORD c);


    static size_t hex2dec(const std::string &prm_hex) {
        std::istringstream iss(prm_hex);
        size_t val;
        iss >> std::hex >> val;
        return val;
    }


    static void readProperties(std::string filename, GgafStrMap* pMap);
    static void readProperties(std::istream &is, GgafStrMap* pMap);
    static void writeProperties(const char *filename, GgafStrMap* pMap, const char *header = NULL);
    static void writeProperties(std::ostream &os, GgafStrMap* pMap, const char *header = NULL);
    static void printProperties(std::ostream &os, GgafStrMap* pMap);
    static inline char m_hex(int nibble) {
        static const char *digits = "0123456789ABCDEF";
        return digits[nibble & 0xf];
    }
    static bool isExistKey(std::string prm_key, GgafStrMap* p);
    static bool cnvBool(std::string prm_str);
};

}
#endif /*GGAFUTIL_H_*/
