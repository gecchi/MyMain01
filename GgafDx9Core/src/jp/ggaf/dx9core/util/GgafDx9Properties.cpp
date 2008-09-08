#include "stdafx.h"

bool*   GgafDx9Properties::FULL_SCREEN     = NULL;
int*    GgafDx9Properties::SCREEN_WIDTH     = NULL;
int*    GgafDx9Properties::SCREEN_HEIGHT    = NULL;
string* GgafDx9Properties::DIR_MESH_MODEL   = NULL;
string* GgafDx9Properties::DIR_SPRITE_MODEL = NULL;
string* GgafDx9Properties::DIR_OGG          = NULL;
string* GgafDx9Properties::DIR_WAVE         = NULL;

void GgafDx9Properties::load(string prm_ini_filename) {
	GgafProperties::load(prm_ini_filename);

	FULL_SCREEN      = getBool("FULL_SCREEN");
	SCREEN_WIDTH     = getInt("SCREEN_WIDTH");
	SCREEN_HEIGHT    = getInt("SCREEN_HEIGHT");
	DIR_MESH_MODEL   = getStr("DIR_MESH_MODEL");
	DIR_SPRITE_MODEL = getStr("DIR_SPRITE_MODEL");
	DIR_OGG          = getStr("DIR_OGG");
	DIR_WAVE         = getStr("DIR_WAVE");

	_TRACE_("GGAFDX9_PROPERTY(FULL_SCREEN)="<<GGAFDX9_PROPERTY(FULL_SCREEN));
	_TRACE_("GGAFDX9_PROPERTY(SCREEN_WIDTH)="<<GGAFDX9_PROPERTY(SCREEN_WIDTH));
	_TRACE_("GGAFDX9_PROPERTY(SCREEN_HEIGHT)="<<GGAFDX9_PROPERTY(SCREEN_HEIGHT));
	_TRACE_("GGAFDX9_PROPERTY(DIR_MESH_MODEL)="<<GGAFDX9_PROPERTY(DIR_MESH_MODEL));
	_TRACE_("GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)="<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL));
	_TRACE_("GGAFDX9_PROPERTY(DIR_OGG)="<<GGAFDX9_PROPERTY(DIR_OGG));
	_TRACE_("GGAFDX9_PROPERTY(DIR_WAVE)="<<GGAFDX9_PROPERTY(DIR_WAVE));
	//‘±‚«
}

void GgafDx9Properties::clean() {
	GgafProperties::clean();

	delete DIR_MESH_MODEL;
	delete DIR_SPRITE_MODEL;
	delete DIR_OGG;
	delete DIR_WAVE;
	delete FULL_SCREEN;
	delete SCREEN_WIDTH;
	delete SCREEN_HEIGHT;
}
