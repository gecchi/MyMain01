#ifndef GGAFDX9PROPERTIES
#define GGAFDX9PROPERTIES

#define GGAFDX9_PROPERTY(X) (*GgafDx9Properties::X)

class GgafDx9Properties : GgafProperties {
public:
	static bool*   FULL_SCREEN;
	static int*    SCREEN_WIDTH;
	static int*    SCREEN_HEIGHT;
	static string* DIR_MESH_MODEL;
	static string* DIR_SPRITE_MODEL;
	static string* DIR_OGG;
	static string* DIR_WAVE;

	static void load(string prm_ini_filename);
	static void clean();
};
#endif /*GGAFDX9PROPERTIES*/

