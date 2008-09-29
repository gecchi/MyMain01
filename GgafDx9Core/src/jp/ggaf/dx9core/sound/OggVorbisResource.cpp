#include "stdafx.h"
OggVorbisResource::OggVorbisResource() :
		isReady_(false) {
	_TRACE_("OggVorbisResource::OggVorbisResource() !!!!!!!!");
		memset(&oggVorbisFile_, 0, sizeof(OggVorbis_File));
		_TRACE_("OggVorbisResource::OggVorbisResource() !!!!!!!!");

}


void OggVorbisResource::clear() {
	memset(&oggVorbisFile_, 0, sizeof(OggVorbis_File));
	isReady_ = false;
}
