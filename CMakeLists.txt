cmake_minimum_required(VERSION 3.21)
project(boom_gate_application)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(gates)
add_subdirectory(payments)
add_subdirectory(parking)
add_subdirectory(billing)

add_executable(boom_gate app/main.cpp
        app/private/random_events_producer.cpp)
target_link_libraries(boom_gate gates parking payments billing)


include(CTest)
add_test(NAME GatesTests COMMAND Gates_Tests_run)
add_test(NAME PaymentsTests COMMAND Payments_Tests_run)
add_test(NAME ParkingTests COMMAND Parking_Tests_run)
add_test(NAME BillingTests COMMAND Billing_Tests_run)