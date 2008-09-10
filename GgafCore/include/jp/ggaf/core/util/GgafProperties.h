#ifndef GGAFPROPERTIES
#define GGAFPROPERTIES
#define GGAF_PROPERTY(X) (*GgafProperties::X)

class GgafProperties {

public:
	static DWORD* MAX_SKIP_FRAME;

	static void load(string prm_properties_filename);
	static void clean();

protected:
	static map<string, string>* _s_pMapProperties;

	static int read(string prm_properties_filename);
	static void parse(char* p);
	static bool isExistKey(string prm_key);

	static string* getStr(string prm_key);
	static bool* getBool(string prm_key);
	static int* getInt(string prm_key);
	static DWORD* getDWORD(string prm_key);
	static double* getDouble(string prm_key);
};

#endif /*GGAFPROPERTIES*/

