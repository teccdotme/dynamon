if (INSTALL_LOCAL MATCHES ON)
    set(PLATFORM ${CMAKE_SYSTEM_NAME})
    if (MinGW)
        set(PLATFORM mingw)
    endif()
    set(TYPENAME ${PLATFORM}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE})
    message(STATUS "Installing locally (${TYPENAME})")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build/${TYPENAME}")
endif()

install(
        TARGETS dynamon
        CONFIGURATIONS Debug Release
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        OBJECTS DESTINATION obj
)
install(
        FILES ${HEADERS}
        DESTINATION include
)
install(
        FILES LICENSE.txt NOTICE.txt
        DESTINATION .
)
install(
        DIRECTORY licenses
        DESTINATION .
)