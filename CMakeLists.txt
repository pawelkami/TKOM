cmake_minimum_required(VERSION 2.8)
project(tkom)
set(CMAKE_BUILD_TYPE Debug)

include_directories(.
                    src
                    src/tokens)
					
set(SOURCES
    src/Tags.cpp
    src/TextPosition.cpp
    src/tokens/Token.cpp
    src/tokens/AttributeKeyToken.cpp    
    src/tokens/DoctypeToken.cpp          
    src/tokens/TagClosingMarkToken.cpp
    src/tokens/AttributeValueToken.cpp  
    src/tokens/EmptyClosingTagToken.cpp  
    src/tokens/TagOpenerToken.cpp
    src/tokens/ClosingTagToken.cpp      
    src/tokens/EqualsToken.cpp           
    src/tokens/CommentToken.cpp         
    src/tokens/PlainTextToken.cpp
    src/Lexer.cpp
    src/main.cpp
   )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

add_executable(tkom ${SOURCES})
target_link_libraries(tkom ${PROJECT_LINK_LIBS})
