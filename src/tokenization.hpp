#pragma once
#include <iostream>
class Tokenizer {
    public:
        inline Tokenizer(std::string src) : m_src(std::move(src)) {
            
        }

    private:
        const std::string m_src;
}