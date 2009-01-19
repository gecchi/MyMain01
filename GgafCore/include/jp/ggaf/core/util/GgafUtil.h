#ifndef GGAFUTIL_H_
#define GGAFUTIL_H_
namespace GgafCore {


class GgafUtil {
public:
	static DWORD _timex;

	static DWORD getSystemTime();

	static char* getFileText(string prm_filename);

	static string itos(int prm_n) {
		ostringstream oss;
    	oss << prm_n;
	    return oss.str();
    }
};


}
#endif /*GGAFUTIL_H_*/
