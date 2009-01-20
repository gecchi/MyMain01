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
};


}
#endif /*GGAFUTIL_H_*/
