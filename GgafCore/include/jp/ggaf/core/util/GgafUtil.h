#ifndef GGAFUTIL_H_
#define GGAFUTIL_H_
namespace GgafCore {

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
     * ASCIIŒÀ’è•¶Žš—ñ”äŠr
     * Žg—p‚É‚Í’ˆÓ‚µ‚Ü‚µ‚å‚¤B
     * @param s1
     * @param s2
     * @return
     */
    static int strcmp_ascii(char* s1, char* s2) {
        while (*s1 == *s2++)
            if (*s1++ == 0) return (0);
        return (*s1 - *(s2 - 1));
    }
};

}
#endif /*GGAFUTIL_H_*/
