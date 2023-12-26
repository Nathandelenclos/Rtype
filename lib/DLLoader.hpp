//
// Created by talleux on 12/13/23.
//

#ifndef BOOTSTRAP_DLLOADER_HPP
#define BOOTSTRAP_DLLOADER_HPP


#include <dlfcn.h>
#include <iostream>
#include "DLLoader.hpp"
#include "r_type/RType.hpp"

class DLLoader {
public:
    explicit DLLoader(const std::string& libraryPath) {
        handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Cannot open library: " << dlerror() << '\n';
        }
    }

    ~DLLoader() {
        if (handle) {
            dlclose(handle);
        }
    }

    RType* getInstance(const std::string& functionName) {
        dlerror();  // Clear any existing error
        create_t* create = (create_t*) dlsym(handle, functionName.c_str());
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol '" << functionName << "': " << dlsym_error << '\n';
            return nullptr;
        }
        if (!create) {
            std::cerr << "Function '" << functionName << "' not found in the library.\n";
            return nullptr;
        }
        return create();
    }

private:
    typedef RType* create_t();
    void* handle = nullptr;
};


#endif //BOOTSTRAP_DLLOADER_HPP
