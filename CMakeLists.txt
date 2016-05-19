cmake_minimum_required(VERSION 2.8)
project(htmlparser)
set(CMAKE_BUILD_TYPE Release)

include_directories(.
                    src
                    src/tokens
                    src/elements)

add_library(htmlparser STATIC
    src/Tags.cpp
    src/TextPosition.cpp
    src/tokens/ClosingTagToken.cpp      
    src/tokens/DoctypeToken.cpp          
    src/tokens/EmptyClosingTagToken.cpp  
    src/tokens/EqualsToken.cpp           
    src/tokens/QuoteToken.cpp    
    src/tokens/TagClosingMarkToken.cpp
    src/tokens/TagOpenerToken.cpp
    src/tokens/TextToken.cpp
    src/tokens/Token.cpp
    src/elements/HtmlAttribute.cpp
    src/elements/HtmlElement.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/ResultsAnalyzer.cpp
    src/utils.cpp
    src/main.cpp
   )            
            
					
set(SOURCES
    src/Tags.cpp
    src/TextPosition.cpp
    src/tokens/ClosingTagToken.cpp      
    src/tokens/DoctypeToken.cpp          
    src/tokens/EmptyClosingTagToken.cpp  
    src/tokens/EqualsToken.cpp           
    src/tokens/QuoteToken.cpp    
    src/tokens/TagClosingMarkToken.cpp
    src/tokens/TagOpenerToken.cpp
    src/tokens/TextToken.cpp
    src/tokens/Token.cpp
    src/elements/HtmlAttribute.cpp
    src/elements/HtmlElement.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/ResultsAnalyzer.cpp
    src/utils.cpp
    src/main.cpp
   )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

#add_executable(htmlparser ${SOURCES})
target_link_libraries(htmlparser ${PROJECT_LINK_LIBS})
