add_executable(services.network_test)
emil_build_for(services.network_test BOOL EMIL_BUILD_TESTS)
emil_add_test(services.network_test)

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang|AppleClang")
    target_compile_options(services.network_test PRIVATE -Wno-braced-scalar-init)
endif()

target_link_libraries(services.network_test PUBLIC
    gmock_main
    services.network
    services.network_test_doubles
    infra.timer_test_helper
    infra.util_test_helper
    hal.generic
    hal.interfaces_test_doubles
    hal.synchronous_interfaces_test_doubles
    protobuf.test_doubles
    services.util
)

target_sources(services.network_test PRIVATE
    TestAddress.cpp
    TestBonjourServer.cpp
    $<$<BOOL:${EMIL_INCLUDE_MBEDTLS}>:TestConnectionMbedTls.cpp>
    TestDnsResolver.cpp
    TestDnsServer.cpp
    TestEchoOnConnection.cpp
    TestExclusiveConnection.cpp
    TestExclusiveStartingConnection.cpp
    TestHttpClient.cpp
    TestHttpClientAuthentication.cpp
    TestHttpClientBasic.cpp
    $<$<BOOL:${EMIL_INCLUDE_MBEDTLS}>:TestHttpClientCachedConnection.cpp>
    TestHttpClientJson.cpp
    TestHttpServer.cpp
    TestLlmnrResponder.cpp
    TestMdnsClient.cpp
    TestMqttClient.cpp
    $<$<BOOL:${EMIL_INCLUDE_MBEDTLS}>:TestNameResolverCache.cpp>
    TestSerialServer.cpp
    TestSingleConnectionListener.cpp
    TestSntpClient.cpp
    TestSsdpDeviceDiscovery.cpp
    TestWebSocketClient.cpp
    $<$<BOOL:${EMIL_INCLUDE_MBEDTLS}>:TestWebSocketClientConnectionObserver.cpp>
    $<$<BOOL:${EMIL_INCLUDE_MBEDTLS}>:TestWebSocketIntegration.cpp>
    $<$<BOOL:${EMIL_INCLUDE_MBEDTLS}>:TestWebSocketServerConnectionObserver.cpp>
    TestWiFiNetwork.cpp
)

add_executable(services.network_test_certificates)
emil_build_for(services.network_test_certificates BOOL EMIL_BUILD_TESTS)
emil_add_test(services.network_test_certificates)

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang|AppleClang")
    target_compile_options(services.network_test_certificates PRIVATE -Wno-braced-scalar-init)
endif()

target_link_libraries(services.network_test_certificates PUBLIC
    gmock_main
    services.network
    services.network_test_doubles
    hal.generic
)

target_sources(services.network_test_certificates PRIVATE
    TestCertificateConvertor.cpp
    $<$<BOOL:${EMIL_INCLUDE_MBEDTLS}>:TestCertificatesMbedTls.cpp>
)
