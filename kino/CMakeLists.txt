cmake_minimum_required(VERSION 3.4)
project(kino)

set(SOURCE_FILES
        include/Client.h
        src/Client.cpp
        src/HallManager.cpp
        include/HallManager.h
        include/HallRepository.h
        src/Hall.cpp
        include/Hall.h
        src/MovieManager.cpp
        include/MovieManager.h
        include/MovieRepository.h
        src/Movie.cpp include/Movie.h
        src/TicketManager.cpp
        include/TicketManager.h
        include/TicketRepository.h
        src/Ticket.cpp
        include/Ticket.h
        src/ClientManager.cpp
        include/ClientManager.h
        include/ClientRepository.h
        src/ShowtimeRepository.cpp
        include/ShowtimeRepository.h
        src/Showtime.cpp
        include/Showtime.h
        src/TicketType.cpp
        include/TicketType.h
        src/StudentTicket.cpp
        include/StudentTicket.h
        src/NormalTicket.cpp
        include/NormalTicket.h
        src/SeniorTicket.cpp
        include/SeniorTicket.h
        src/ClientType.cpp
        include/ClientType.h
        src/PremiumClient.cpp
        include/PremiumClient.h
        src/NormalClient.cpp
        include/NormalClient.h
        include/Repository.h
        src/AvaliableException.cpp
        include/AvaliableException.h
        src/ParameterException.cpp
        include/ParameterException.h
        src/DuplicateException.cpp
        include/DuplicateException.h)

add_library(kino ${SOURCE_FILES})

target_include_directories(kino PUBLIC include)

enable_testing()

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_HUMAN_FILES
        test/master.cpp
        test/BasicTest.cpp
        test/ManagerTest.cpp
        test/RepositoryTest.cpp
        test/ExceptionsTest.cpp)

add_executable (Tests ${SOURCE_TEST_HUMAN_FILES})

target_link_libraries (Tests
        kino
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test Tests. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(TestKina Tests
        --report_level=detailed
        --log_level=all
        --color_output=yes
        --show_progress=true
        )

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
