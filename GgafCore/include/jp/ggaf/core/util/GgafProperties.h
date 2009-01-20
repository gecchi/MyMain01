#ifndef GGAFPROPERTIES
#define GGAFPROPERTIES
namespace GgafCore {


#define GGAF_PROPERTY(X) (*GgafCore::GgafProperties::X)

class GgafProperties {

public:
	static DWORD* MAX_SKIP_FRAME;

	static void load(std::string prm_properties_filename);
	static void clean();

protected:
	static std::map<std::string, std::string>* _s_pMapProperties;

	static int read(std::string prm_properties_filename);
	static void parse(char* p);
	static bool isExistKey(std::string prm_key);

	static std::string* getStr(std::string prm_key);
	static bool* getBool(std::string prm_key);
	static int* getInt(std::string prm_key);
	static DWORD* getDWORD(std::string prm_key);
	static double* getDouble(std::string prm_key);
};


}
#endif /*GGAFPROPERTIES*/

