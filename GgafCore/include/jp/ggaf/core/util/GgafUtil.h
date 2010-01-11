#ifndef GGAFUTIL_H_
#define GGAFUTIL_H_
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
    static DWORD _timex;

    static DWORD getSystemTime();

    static char* getFileText(std::string prm_filename);

    static std::string itos(int prm_n) {
        std::ostringstream oss;
        oss << prm_n;
        return oss.str();
    }

    /**
     * ASCII���蕶�����r .
     * �W����葬���̂ł͂Ȃ����낤���A�g�p�ɂ͒��ӂ��܂��傤�B
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
     * 10�i��-->2�i���ϊ��֐�
     * @param DecimalNumber
     * @param BinaryString 2�i��������  char[33]  [out]
     */
    static void strbin(unsigned long int DecimalNumber, char* BinaryString, int bitnum = 32){
        /* 10�i��-->2�i���ϊ� */
        int i, k;
        for (i = 0, k = bitnum - 1; k >= 0; i++, k--) {
            if ((DecimalNumber >> i) & 1) BinaryString[k] = '1';
            else BinaryString[k] = '0';
        }
        BinaryString[i] = '\0';

        /* �ϊ����ʂ̗�00011001�ɂ�����A��ʌ���000���폜���鏈�� */
//        for (i = 0; i < BITS_DIGIT; i++) {
//            if (BinaryString[0] == '0') memmove(BinaryString, BinaryString + 1, BITS_DIGIT);
//            else break;
//        }
    }
    /**
     * �ȈՃn�b�V��
     * @param key
     * @return �n�b�V���l
     */
    static unsigned int easy_hash(const char* prm_key) {
        unsigned int n = 0;
        for (unsigned int i = 1; (*prm_key) != '\0'; i++) {
            n = n * 7 +  ((*prm_key) * i); //�v�������̓K���ȃn�b�V���֐��ł��B
            prm_key++;
        }
        return n;
    }
};

}
#endif /*GGAFUTIL_H_*/
