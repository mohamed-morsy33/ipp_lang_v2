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
    std::optional<std::string> value {};
};

class Tokenizer {
    public:
        inline explicit Tokenizer(const std::string src) 
            : m_src(std::move(src))
        {
        }
        
        inline std::vector<Token> tokenize() {
            std::vector<Token> tokens {};
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
                        continue;
                    } else{
                        std::cerr << "Unknown identifier: " << buf << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
                else if (std::isdigit(peek().value())) {
                    buf.push_back(consume());
                    while (peek().has_value() && std::isdigit(peek().value())) {
                        buf.push_back(consume());
                    }
                    tokens.push_back({.type=TokenType::int_literal, .value=buf});
                    buf.clear();
                    continue;
                }
                else if (peek().value() == ';') {
                    consume();
                    tokens.push_back({.type=TokenType::semicolon});
                    continue;
                }
                else if (std::isspace(peek().value())) {
                    consume();
                    continue;
                } else {
                    std::cerr << "Unknown character: " << peek().value() << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            
            m_index = 0; 
            return tokens;
        }
       
    private:
        [[nodiscard]] std::optional<char> peek(int ahead = 1) const {
            if (m_index + ahead > m_src.length()) {
                return {};
            } else {
                return m_src.at(m_index + ahead - 1);
            }
        }

        char consume() {
            return m_src.at(m_index++); 
        }

        
        const std::string m_src;
        int m_index = 0;

};