cmake_minimum_required(VERSION 3.10)
project(M1OEP_dkim13 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(blackjack
        main.cpp
        Card.cpp
        Deck.cpp
        Game.cpp
)
target_include_directories(blackjack PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(testing
        testing.cpp
        Card.cpp
        Deck.cpp
        Game.cpp
)
target_include_directories(testing PRIVATE ${CMAKE_SOURCE_DIR})
