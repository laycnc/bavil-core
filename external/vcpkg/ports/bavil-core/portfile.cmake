vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO laycnc/bavil-core
    REF 5fdcea181d02e60dc3a05c55d1e3f1c5a621d038
    SHA512 7616540C920241768D7454ED5709505D7A0513C80E991FCAA6A7A99900A271D47EA7B4BC1CBE3F935F224F985F994092DD91384989179C49769CD016CADFB786
    HEAD_REF main
)

file(COPY "${CMAKE_CURRENT_LIST_DIR}/bavil_coreConfig.cmake.in" DESTINATION "${SOURCE_PATH}")

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DBAVIL_BUILD_TESTS=OFF
        -DBAVIL_BUILD_INSTALL=ON
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/bavil_core)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

# Install natvis files
file(INSTALL "${SOURCE_PATH}/src/natvis" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}/natvis")

vcpkg_copy_pdbs()

file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)

