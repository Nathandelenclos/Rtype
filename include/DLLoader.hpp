/*
** EPITECH PROJECT, 2023
** RType
** File description:
** DLLoader.cpp
*/

#pragma once

#include <dlfcn.h>
#include <iostream>
#include "DLLoader.hpp"
#include "IGame.hpp"

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

    IGame* getInstance(const std::string& functionName) {
        dlerror();
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
    typedef IGame* create_t();
    void* handle = nullptr;
};