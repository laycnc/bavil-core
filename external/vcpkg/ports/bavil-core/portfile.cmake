vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO laycnc/bavil-core
    REF v0.08
    SHA512 4bd8fd18dd408cea06c1797a43f6cfc064f2af3e114455abf07b7fce9bb2038027cada04e6234c88cdfea9099dc3468e305b32ed1e3d1f49c861560bde53cd79
    HEAD_REF main
    PATCHES 
    fix_cmake_install.patch
)

file(COPY "${CMAKE_CURRENT_LIST_DIR}/bavil_coreConfig.cmake.in" DESTINATION "${SOURCE_PATH}")

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DBAVIL_BUILD_TESTS=OFF
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/bavil_core)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

# Install natvis files
file(INSTALL "${SOURCE_PATH}/src/natvis" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}/natvis")

vcpkg_copy_pdbs()

file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)

