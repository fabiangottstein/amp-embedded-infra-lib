if (EMIL_HOST_BUILD)
    add_library(services.network_instantiations ${EMIL_EXCLUDE_FROM_ALL} STATIC)
    install(TARGETS services.network_instantiations EXPORT emilServicesTargets)

    target_sources(services.network_instantiations PRIVATE
        NameLookup.cpp
        NameLookup.hpp
        NetworkAdapter.cpp
        NetworkAdapter.hpp
    )

    target_link_libraries(services.network_instantiations PUBLIC
        services.network
    )

    if (EMIL_BUILD_WIN)
        target_sources(services.network_instantiations PRIVATE
            ConnectionWin.cpp
            ConnectionWin.hpp
            DatagramWin.cpp
            DatagramWin.hpp
            EventDispatcherWithNetworkWin.cpp
            EventDispatcherWithNetworkWin.hpp
        )

        target_link_libraries(services.network_instantiations PUBLIC
            ws2_32.lib
            iphlpapi.lib
        )

        target_compile_definitions(services.network_instantiations PUBLIC EMIL_NETWORK_WIN)
    endif()

    if (EMIL_BUILD_UNIX OR EMIL_BUILD_DARWIN)
        target_sources(services.network_instantiations PRIVATE
            ConnectionBsd.cpp
            ConnectionBsd.hpp
            DatagramBsd.cpp
            DatagramBsd.hpp
            EventDispatcherWithNetworkBsd.cpp
            EventDispatcherWithNetworkBsd.hpp
        )

        target_link_libraries(services.network_instantiations PUBLIC
            pthread
        )

        target_compile_definitions(services.network_instantiations PUBLIC EMIL_NETWORK_BSD)
    endif()

    emil_clangformat_target(services.network_instantiations)
endif()