#include "stdafx.h"

std::map<std::size_t, std::string> detectMemoryLeaksMemoryMap;
bool detectMemoryLeaksFlag = false;

void *
operator new(std::size_t size, char* strFileName, int nLineNum)
throw (std::bad_alloc)
{
    void * address = malloc(size);
	if(address == 0) {
		_TRACE_(strFileName << ":" << nLineNum << " bad_alloc....");
        throw std::bad_alloc();
	}

    if(detectMemoryLeaksFlag){
        TRACE("new: " << strFileName << ":" << nLineNum << " size=" << size << " address=" << address );
        std::ostringstream oss;
        oss << strFileName << ":" << nLineNum << " size=" << size  << " address=" << address;
        detectMemoryLeaksMemoryMap.insert( std::pair<std::size_t, std::string>((std::size_t)address, oss.str()) );
    }
    return address;
}

void *
operator new[](std::size_t size, char* strFileName, int nLineNum)
throw (std::bad_alloc)
{
    void * address = malloc(size);
	if(address == 0) {
		_TRACE_(strFileName << ":" << nLineNum << " bad_alloc....");
        throw std::bad_alloc();
	}

    if(detectMemoryLeaksFlag){
    	TRACE("new[]: " << strFileName << ":" << nLineNum << " size=" << size << " address=" << address);
        std::ostringstream oss;
        oss << strFileName << ":" << nLineNum << " size=" << size  << " address=" << address;
        detectMemoryLeaksMemoryMap.insert( std::pair<std::size_t, std::string>((std::size_t)address, oss.str()) );
    }
    return address;
}

void
operator delete(void * address)
{
    if(address == 0) // Depends on environment.
        return;

    if(detectMemoryLeaksFlag){
    	//TRACE("delete: " << " address=" << address );
        std::map<std::size_t, std::string>::iterator it = detectMemoryLeaksMemoryMap.begin();
        std::map<std::size_t, std::string>::iterator itEnd = detectMemoryLeaksMemoryMap.end();
        std::size_t checkAddress = (std::size_t)address;
        for(; it!=itEnd; it++){
            if(it->first == checkAddress){
                detectMemoryLeaksMemoryMap.erase(it);
                break;
            }
        }
    }
    free(address);
}

void
operator delete[](void * address)
{
    if(address == 0) // Depends on environment.
        return;

    if(detectMemoryLeaksFlag){
    	//TRACE("delete[]: " << " address=" << address);
        std::map<std::size_t, std::string>::iterator it = detectMemoryLeaksMemoryMap.begin();
        std::map<std::size_t, std::string>::iterator itEnd = detectMemoryLeaksMemoryMap.end();
        std::size_t checkAddress = (std::size_t)address;
        for(; it!=itEnd; it++){
            if(it->first == checkAddress){
                detectMemoryLeaksMemoryMap.erase(it);
                break;
            }
        }
    }
    free(address);
}

void
detectMemoryLeaksStart(std::ostream& ros)
{
    //ros << "[detect memory leaks] start" << std::endl;
	_TRACE_("[detect memory leaks] start");
	detectMemoryLeaksFlag = true;
}

void
detectMemoryLeaksEnd(std::ostream& ros)
{
    //ros << "[detect memory leaks] end" << std::endl;
	_TRACE_("[detect memory leaks] end");
    if(detectMemoryLeaksMemoryMap.size() > 0){
        //ros << "memory leaks ..." << std::endl;
		_TRACE_("memory leaks ...");
        std::map<std::size_t, std::string>::iterator it = detectMemoryLeaksMemoryMap.begin();
        std::map<std::size_t, std::string>::iterator itEnd = detectMemoryLeaksMemoryMap.end();
		for(; it!=itEnd; it++) {
            //ros << "  " << it->second << std::endl;
			_TRACE_("  " << it->second);
		}
    }else{
        //ros << "memory leak is nothing." << std::endl;
		_TRACE_("memory leak is nothing.");
    }
    detectMemoryLeaksFlag = false;
    detectMemoryLeaksMemoryMap.clear();
}
