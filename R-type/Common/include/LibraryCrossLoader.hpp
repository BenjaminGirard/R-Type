//
// Created by tetard on 19/01/18.
//

#ifndef CPP_RTYPE_LIBRARYCROSSLOADER_H
#define CPP_RTYPE_LIBRARYCROSSLOADER_H

#include <string>
#if defined(_MSC_VER)
#include <windows.h>
#elif defined(__GNUC__)
#include <dlfcn.h>
#endif

class LibraryCrossLoader {
public:
    LibraryCrossLoader() = delete;
    LibraryCrossLoader(const LibraryCrossLoader &cp) = delete;
    LibraryCrossLoader &operator=(const LibraryCrossLoader &cp) = delete;

  static void *loadLibrary(const char * const path) noexcept {
      std::string sDllName = path;

#if defined(_MSC_VER)
      sDllName += ".dll";
        return (void*)LoadLibrary(sDllName.c_str()); // tester avec un dll voir si ça fonctionne bien sinon remplacer avec le path de base

#elif defined(__GNUC__)
      sDllName += ".so";
      return dlopen(sDllName.c_str(), RTLD_LAZY);
#endif
    }

    static void *loadFunction(void *lib, const char * const functionName) noexcept {
#if defined(_MSC_VER)
      return (void*)GetProcAddress((HINSTANCE)lib, functionName);

#elif defined(__GNUC__)
      return dlsym(lib, functionName);
#endif
    }

  static bool freeLibraryMemory(void *library) noexcept {
#if defined(_MSC_VER)
    return FreeLibrary((HINSTANCE)library);
#elif defined(__GNUC__)
    return dlclose(library);
#endif
  }
};

#endif //CPP_RTYPE_LIBRARYCROSSLOADER_H
