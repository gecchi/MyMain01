#ifndef GGAFUTIL_H_
#define GGAFUTIL_H_


    typedef std::map<std::string, std::string>::value_type           value_type;
    typedef std::map<std::string, std::string>::iterator             iteratorP;


namespace GgafCore {

/**
 * ���[�e�B���e�B�N���X .
 * �ėp�I�ȐÓI�֐��͂ł��邾�������ɋL�q�B
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class GgafUtil {
public:
    static UINT32 _timex;

    static UINT32 getSystemTime();

    /**
     * �t�@�C���ǂݍ��� .
     * �߂�l�͌Ăь��� delete[] ����K�v������܂��B
     * @param prm_filename
     * @return
     */
    static char* getFileText(std::string prm_filename);

    static std::string itos(int prm_n) {
        std::ostringstream oss;
        oss << prm_n;
        return oss.str();
    }

    /**
     * ASCII���蕶�����r .
     * �W�����ق�̂���тƑ����̂ł͂Ȃ����낤���A�g�p�ɂ͒��ӂ��܂��傤�B
     * @param s1
     * @param s2
     * @return
     */
    static int strcmp_ascii(const char* s1, const char* s2) {
        while (*s1 == *s2++)
            if (*s1++ == 0) return (0);
        return (*s1 - *(s2 - 1));
    }

    static int strcmp_ascii(char* s1, const char* s2) {
        while (*s1 == *s2++)
            if (*s1++ == 0) return (0);
        return (*s1 - *(s2 - 1));
    }

    /*  */

    /**
     * 10�i��-->2�i��������ϊ��֐�
     * @param prm_decimal
     * @param out_binstr 2�i��������  char[33]  [out]
     * @param bitnum ���]�̂Q�i���r�b�g��
     */
    static void strbin(UINT32 prm_decimal, char* out_binstr, int bitnum = 32){
        /* 10�i��-->2�i���ϊ� */
        int i, k;
        for (i = 0, k = bitnum - 1; k >= 0; i++, k--) {
            if ((prm_decimal >> i) & 1) out_binstr[k] = '1';
            else out_binstr[k] = '0';
        }
        out_binstr[i] = '\0';

        /* �ϊ����ʂ̗�00011001�ɂ�����A��ʌ���000���폜���鏈�� */
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
//        //n = n * 33  + ((*prm_key)-32); �Ƃ������R����
//        //-32 �� ' '(ASCII:32��) �ȍ~�̕�����������Ȃ�����
//        //33���悸��ƁA�Ȃ񂩏Փ˂����Ȃ��炵��
//    }

    /**
     * �ȈՃn�b�V�� .
     * ������ ���A������ӂ̂悤��32bi�����l�ɕϊ��B
     * �X�s�[�h�D��̃n�b�V���֐��̂��߁A�����ł͂Ȃ��B
     * 33���悶��ƁA�Փ˂����Ȃ��炵���Ƃ���������M����B
     * @param str ������
     * @return �n�b�V���l
     */
    static const UINT32 easy_hash(const char* str) {
        UINT32 hash = 5381;
        char c;
        while ((c = *str++) > 0) { //str��\0�܂Ń��[�v �i���Z�q "==" �ƊԈႦ�Ă��܂���j
            hash = ((hash << 5) + hash) + c; // hash * 33 + c  33�{���Ă܂�
        }
        return hash;
    }

    /**
     * ��������.
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
     * ��Βl�����߂�
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
     * �������̋ߎ������߂� .
     * �W��sqrt�����v�Z���������A�A�o�E�g�B
     * @param a �����������߂����l
     * @param s ���x�i�v�Z���[�v�񐔁B�񐔂������قǐ��m�B�ȗ���19�j
     * @return ����a�̕������ߎ��l
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


    static void read(std::string filename, std::map<std::string, std::string>* pMap);
    static void read(std::istream &is, std::map<std::string, std::string>* pMap);
    static void write(const char *filename, std::map<std::string, std::string>* pMap, const char *header = NULL);
    static void write(std::ostream &os, std::map<std::string, std::string>* pMap, const char *header = NULL);
    static void print(std::ostream &os, std::map<std::string, std::string>* pMap);
    static inline char m_hex(int nibble)
    {
        static const char *digits = "0123456789ABCDEF";
        return digits[nibble & 0xf];
    }
    static bool isExistKey(std::string prm_key, std::map<std::string, std::string>* p);

};

}
#endif /*GGAFUTIL_H_*/
