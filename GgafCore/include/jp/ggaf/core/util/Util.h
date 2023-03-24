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
 * �͈͒��̂���l�ɂ��āA�͈͂�ϊ������ꍇ�̑��Βl���擾 .
 * �͈� MIN_A__ �` MAX_A__ �� A__ �̒l���A�͈� MIN_B__ �` MAX_B__ �ɕϊ������ꍇ�� A__ �ɑΉ������l�𓾂�<br>
 */
#define RCNV(MIN_A__,MAX_A__,A__,MIN_B__,MAX_B__)  ( GgafCore::Util::_rcnv_((double)(MIN_A__),(double)(MAX_A__),(double)(A__),(double)(MIN_B__),(double)(MAX_B__)) )

/**
 * 0 �` 1 �͈̔͂̂���l�ɂ��āA�͈͂�ϊ������ꍇ�̑��Βl���擾 .
 * �͈� 0 �` 1 �� X_IN_0_1 �̒l���A�͈� MIN_B__ �` MAX_B__ �ɕϊ������ꍇ�̒l�𓾂�<br>
 */
#define RCNV_0_1_to(X_IN_0_1,MIN_B__,MAX_B__)  ( GgafCore::Util::_rcnv_0_1_to((double)(X_IN_0_1),(double)(MIN_B__),(double)(MAX_B__)) )

/**
 * �͈͒��̂���l�ɂ��āA0 �` 1 �͈̔͂ɕϊ������ꍇ�̑��Βl���擾 .
 * �͈� MIN_A__ �` MAX_A__ �� A__ �̒l���A�͈� 0 �` 1 �ɕϊ������ꍇ�� A__ �ɑΉ������l�𓾂�<br>
 */
#define RCNV_to_0_1(MIN_A__,MAX_A__,A__)  ( GgafCore::Util::_rcnv_to_0_1((double)(MIN_A__),(double)(MAX_A__),(double)(A__)) )


/**
 * �����̗����𓾂� .
 * RND(3, 20)
 * �� 3�`20�̗����𓾂� �߂�� int32_t �^
 */
#define RND(FROM__,TO__) (GgafCore::Util::_rnd_int32_((int32_t)(FROM__),(int32_t)(TO__)))

/**
 * ���鐮���̎��ӂ̗����𓾂� .
 * RND_ABOUT(15, 4)   �Ӗ��F15 �́}4�͈̗̔͂���
 * �� 11 �` 19 �̗����ɂȂ�
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
 * ���[�e�B���e�B�N���X .
 * �ėp�I�ȐÓI�֐��͂ł��邾�������ɋL�q�B
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
     * �t�@�C���ǂݍ��� .
     * �߂�l�͌Ăь��� delete[] ����K�v������܂��B
     * @param prm_filename
     * @return
     */
    static char* getFileText(std::string prm_filename);

    /**
     * �f�~���^�ŕ��� .
     * �󕶎��v�f�͔�΂����B
     * <pre>
     * �y��z
     * std::vector<std::string> data = split("\taaa\tbbb\t\t\tcccc\tddd\teeee\t\t", "\t");
     * �����ʁ�
     * data[0] = aaa
     * data[1] = bbb
     * data[2] = cccc
     * data[3] = ddd
     * data[4] = eeee
     * </pre>
     * @param str ������
     * @param delim ��������
     * @return �������ꂽvector
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
     * �f�~���^�ŕ��� .
     * @param str ������
     * @param delim ��������
     * @param split_number_of_times ������
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
     * �ړ������x���A�u��~���ړ������v�u�����_�̑��x�v�ɂ�苁�߂� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^       a:�������x    �E�E�E���񋁂߂�l
     *     |       D:�ړ�����    �E�E�E����
     *     |      V0:�����_�̑��x�E�E�E����
     *   V0|      Te:��~����t���[���E�E�E���߂܂���
     *     |�_
     *     |  �_
     *     |    �_ �Εӂ̌X��a
     *     |   D  �_
     *     |        �_
     *   --+----------�_-----> ����(t)
     *   0 |          Te
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�����̋���(D)����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * ��~�܂ł̃t���[��(Te) �� ����(D) �ɂ��ω����邽�ߎw��s�B<BR>
     * @param D  v�ڕW���B���x�ɒB����܂łɔ�₷����(D)
     * @param V0 �����_�̑��x(V0)
     * @return �K�v�ȉ����x(a)
     */
    static inline double getAcceToStop(double D, double V0) {
#ifdef MY_DEBUG
        if (ZEROd_EQ(D)) {
            throwCriticalException("D��ZERO�ł��BD="<<D);
        }
#endif
        // D = (1/2) V0 Te  �E�E�E�@
        // a = -V0 / Te     �E�E�E�A
        // �@���
        // Te = 2D / V0
        // ������A�֑��
        // a = -V0 / (2D / V0)
        // �� a = -(V0^2) / 2D
        return -(V0*V0) / (2.0*D);
    }

    /**
     * �ړ������x���A�u�ړ������v�u�����_�̑��x�v�u�ڕW���B���x�v�ɂ�苁�߂� .
     * <pre><code>
     *    ���x(v)
     *     ^        a:�����x      �E�E�E���񋁂߂�l
     *     |        D:�ړ�����    �E�E�E����
     *     |       V0:�����_�̑��x�E�E�E����
     *     |       Vt:�ڕW���B���x�E�E�E����
     *     |       Te:�ڕW���B���x�ɒB�������̎��ԁE�E�E���߂܂���
     *   Vt|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �Εӂ̌X��a
     *     |�^      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> ����(t)
     *   0 |        Te
     *
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�ڕW���B���x(Vt)�ƁA�ړ�����(D)����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * �ڕW���B�܂ŕK�v�ȃt���[��(Te) �̓p�����[�^�ɂ��ω����邽�ߎw��s�B<BR>
     * @param D  v�ڕW���B���x�ɒB����܂łɔ�₷����(D)
     * @param V0 �����_�̑��x(V0)
     * @param Vt �ڕW���B���x(Vt)
     * @return �K�v�ȉ����x(a)
     */
    static inline double getAcceByVd(double V0, double Vt, double D) {
#ifdef MY_DEBUG
        if (ZEROd_EQ(D)) {
            throwCriticalException("D��ZERO�ł��BD="<<D);
        }
#endif
        //D = (1/2) (V0 + Vt) Te   �E�E�E�@
        //a = (Vt - V0) / Te       �E�E�E�A
        //�A��� Te = (Vt - V0) / a
        //������@�֑��
        //D = (Vt^2 - V0^2) / 2a
        //�� a = (Vt^2 - V0^2) / 2D
        return ((Vt*Vt) - (V0*V0)) / (2.0*D);
    }

//    static inline double getTimeByD(double D, double V0, double Vt) {
//
//
//    }
    /**
     * �ړ������x���A�u��₷���ԁv�u�����_�̑��x�v�u�ڕW���B���x�v�ɂ�苁�߂� .
     * <pre><code>
     *    ���x(v)
     *     ^        a:�����x      �E�E�E���񋁂߂�l
     *     |        D:�ړ�����    �E�E�E���߂܂���
     *     |       V0:�����_�̑��x�E�E�E����
     *     |       Vt:�ڕW���B���x�E�E�E����
     *     |       Te:�ڕW���B���x�ɒB�������̎��ԁE�E�E����
     *   Vt|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �Εӂ̌X��a
     *     |�^      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> ����(t�t���[��)
     *   0 |        Te
     *
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�ڕW���B���x(Vt)�ƁA���̓��B����(Te) ����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * �ړ�����(D)�́A�p�����[�^�ɂ��ω����邽�ߎw��s�B<BR>
     * @param Te ��₷����(Te)
     * @param V0 �����_�̑��x(V0)
     * @param Vt �ڕW���B���x(Vt)
     * @return �K�v�ȉ����x(a)
     */
    static inline double getAcceByTv(double Te, double V0, double Vt) {
#ifdef MY_DEBUG
        if (ZEROd_EQ(Te)) {
            throwCriticalException("Te��ZERO�ł��BTe="<<Te);
        }
#endif
        //a = (Vt-V0) / Te
        return (Vt - V0) / Te;
    }


    /**
     * float �p 0 ���ۂ��̂��ǂ������� .
     * @param val ���肵�����l
     * @param epsilon 0���ۂ��͈�
     * @return true:0���ۂ� / false:0���ۂ��Ȃ�
     */
    static inline bool _zerof_eq_(float val, float epsilon = 1e-5f ) {
        return (-epsilon < val && val < epsilon);
    }

    /**
     * double �p 0 ���ۂ��̂��ǂ������� .
     * @param val ���肵�����l
     * @param epsilon 0���ۂ��͈�
     * @return true:0���ۂ� / false:0���ۂ��Ȃ�
     */
    static inline bool _zerod_eq_(double val, double epsilon = 1e-13) {
        return (-epsilon < val && val < epsilon);
    }

    /**
     * ���낢��Ȍ^�̒l�𕶎���ɕϊ� .
     * @param prm_x
     * @return ������
     */
    template<typename T>
    static inline std::string _xtos_(T prm_x) {
        std::ostringstream oss;
        oss << prm_x;
        return oss.str();
    }

    /**
     * ���낢��Ȍ^�̒l�𕶎���ɕϊ��� bool ���ꉻ .
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
     * ������� int �ɕϊ� .
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
     * 10�i��-->2�i��������ϊ��֐�
     * @param prm_decimal
     * @param out_binstr 2�i��������  char[33]  [out]
     * @param bitnum ���]�̂Q�i���r�b�g��
     */
    static inline void strbin(uint32_t prm_decimal, char* out_binstr, int bitnum = 32) {
        /* 10�i��-->2�i���ϊ� */
        int i, k;
        for (i = 0, k = bitnum - 1; k >= 0; i++, k--) {
            if ((prm_decimal >> i) & 1) {
                out_binstr[k] = '1';
            } else {
                out_binstr[k] = '0';
            }
        }
        out_binstr[i] = '\0';

        /* �ϊ����ʂ̗�00011001�ɂ�����A��ʌ���000���폜���鏈�� */
//        for (i = 0; i < BITS_DIGIT; i++) {
//            if (BinaryString[0] == '0') memmove(BinaryString, BinaryString + 1, BITS_DIGIT);
//            else break;
//        }
    }

//    static inline const hashval easy_hash(const char* str) {
//        hashval hash = 5381;
//        char c;
//        while ((c = *str++) > 0) { //str��\0�܂Ń��[�v �i���Z�q "==" �ƊԈႦ�Ă��܂���j
//            hash = ((hash << 5) + hash) + c; // hash * 33 + c  33�{���Ă܂�
//        }
//        return hash;
//    }
//
//    static inline const hashval easy_hash(char* str) {
//        hashval hash = 5381;
//        char c;
//        while ((c = *str++) > 0) { //str��\0�܂Ń��[�v �i���Z�q "==" �ƊԈႦ�Ă��܂���j
//            hash = ((hash << 5) + hash) + c; // hash * 33 + c  33�{���Ă܂�
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
     * ��������.
     * @param x
     * @return
     */
    template<typename T>
    static inline int _sgn_(T x) {
        return x < 0 ? -1 : x > 0;
    }

    /**
     * ��Βl�����߂�
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
     * �͈͒��̂���l�ɂ��āA�͈͂�ϊ������ꍇ�̑��Βl���擾 .
     * �͈� min_a �` max_a �� a �̒l���A�͈� min_b �` max_b �ɕϊ������ꍇ�� a �ɑΉ�����l(b) �𓾂�<br>
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
     * �R�捪�����߂� .
     * @param x
     * @return
     */
    static double _cbrt_(double x);
    /**
     * int32_t�����_���֐� .
     * prm_from �� prm_to ���t�]���Ă͂����Ȃ�(����%���Z�́AVC++�ł̓���͕s��̂���)
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
     * ���l�����[�����ߕ�����ɕϊ� .
     * ���l�̌������� prm_total_keta ��葽���ꍇ�́A
     * prm_data_num �̕����񂪕Ԃ�B
     * @param prm_data_num    ���l
     * @param prm_total_keta  �S�̂̕�������
     * @return ���[�����߂��ꂽ������
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
//�����s���ʁ�
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

