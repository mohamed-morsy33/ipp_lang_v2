#pragma once
#include <string>
#include <vector>
#include <optional>

enum class TokenType {
    _exit,
    int_literal,
    semicolon, 
};

struct Token {
    TokenType type;
    optional<string> value {};
};

class Tokenizer {
    public:
        inline Tokenizer(const std::string& src) 
            : m_src(std::move(src))
        {
        }
        
        inline std::vector<Token> tokenize() {
            vector<Token> tokens {};
            std::string buf;
            while(peek().has_value()) {
                if (std::isalpha(peek().value())) {
                    buf.push_back(consume());
                    while (peek().has_value() && std::isalnum(peek().value())) {
                        buf.push_back(consume());
                    }

                    if (buf == "exit") {
                        tokens.push_back({.type=TokenType::_exit});
                        buf.clear();
                    }
                }
            }
        }
       
    private:
        [[nodiscard]] std::optional<char> peek(int ahead = 1) const {
            if (m_index + ahead >= m_src.length()) {
                return {};
            } else {
                return m_src.at(m_index);
            }
        }

        char consume() {
            return m_src.at(m_index++); 
        }

        
        const std::string m_src;
        int m_index;

};