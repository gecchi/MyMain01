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
    static DWORD _timex;

    static DWORD getSystemTime();

    static char* getFileText(std::string prm_filename);

    static std::string itos(int prm_n) {
        std::ostringstream oss;
        oss << prm_n;
        return oss.str();
    }

    /**
     * ASCII限定文字列比較 .
     * 標準より速いのではないだろうか、使用には注意しましょう。
     * @param s1
     * @param s2
     * @return
     */
    static int strcmp_ascii(char* s1, char* s2) {
        while (*s1 == *s2++)
            if (*s1++ == 0) return (0);
        return (*s1 - *(s2 - 1));
    }

    /*  */

    /**
     * 10進数-->2進数変換関数
     * @param DecimalNumber
     * @param BinaryString 2進数文字列化  char[33]  [out]
     */
    static void strbin(unsigned long int DecimalNumber, char* BinaryString, int bitnum = 32){
        /* 10進数-->2進数変換 */
        int i, k;
        for (i = 0, k = bitnum - 1; k >= 0; i++, k--) {
            if ((DecimalNumber >> i) & 1) BinaryString[k] = '1';
            else BinaryString[k] = '0';
        }
        BinaryString[i] = '\0';

        /* 変換結果の例00011001における、上位桁の000を削除する処理 */
//        for (i = 0; i < BITS_DIGIT; i++) {
//            if (BinaryString[0] == '0') memmove(BinaryString, BinaryString + 1, BITS_DIGIT);
//            else break;
//        }
    }
    /**
     * 簡易ハッシュ
     * @param key
     * @return ハッシュ値
     */
    static unsigned int easy_hash(const char* prm_key) {
        unsigned int n = 0;
        for (unsigned int i = 1; (*prm_key) != '\0'; i++) {
            n = n * 7 +  ((*prm_key) * i); //思いついきの適当なハッシュ関数です。
            prm_key++;
        }
        return n;
    }
};

}
#endif /*GGAFUTIL_H_*/
