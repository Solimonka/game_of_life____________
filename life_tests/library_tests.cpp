#include <dlfcn.h>
#include <gtest/gtest.h>
#include "../life_backend/include/Life.h"

TEST(Library_test, Open) {
    void *handle = dlopen("libgame_of_life_library.dylib", RTLD_LAZY);
    ASSERT_TRUE(handle != nullptr);
    dlclose(handle);
}

TEST(Library_test, Get_object) {
    void *handle = dlopen("libgame_of_life_library.dylib", RTLD_LAZY);
    ASSERT_TRUE(handle != nullptr);

    void *(*create_life)(size_t width, size_t height) = nullptr;
    void *(*destroy_life)(void *life) = nullptr;
    create_life = (void *(*)(size_t, size_t)) dlsym(handle, "create_life");
    destroy_life = (void *(*)(void *)) dlsym(handle, "create_life");
    ASSERT_TRUE(create_life != nullptr);

    life_backend::Life *life = (life_backend::Life *) create_life(10, 10);
    ASSERT_TRUE(life != nullptr);
    std::cout << life->string();

    destroy_life(life);
    dlclose(handle);
}