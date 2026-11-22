#pragma once
#include "tokenize.hpp"

struct Expr {
    Token int_literal;
     
};

struct Exit {
    Expr expr;
};


class Parser {
    public:
        inline explicit Parser(std::vector<Token> tokens):
            m_tokens(std::move(tokens)) 
        {
        }

        std::optional<Expr> parse_expr() {
            if (peek().has_value() && peek().value().type == TokenType::int_literal) {
                return Expr{.int_literal=consume()};
            } else {
                return {};
            }
        }

        std::optional<Exit> parse() {
            std::optional<Exit> exit_node {};
            while (peek().has_value()) {
                if (peek().value().type == TokenType::_exit) {
                    consume();
                    if (auto node_expr = parse_expr()) {
                        exit_node = Exit{.expr=node_expr.value()};
                    } 
                    else {
                        std::cerr << "Expected expression after 'exit'" << std::endl;
                        exit(EXIT_FAILURE);
                    }

                    if (!peek().has_value() || peek().value().type != TokenType::semicolon) {
                        std::cerr << "Expected semicolon after 'exit'" << std::endl;
                        exit(EXIT_FAILURE);                       
                    }
                }
            }
            m_index = 0;
            return exit_node;
        }

    private:
        [[nodiscard]] inline std::optional<Token> peek(int ahead = 1) const {
            if (m_index + ahead > m_tokens.size()) {
                return {};
            } else {
                return m_tokens.at(m_index + ahead - 1);
            }
        }

        inline Token consume() {
            return m_tokens.at(m_index++); 
        }



        const std::vector<Token> m_tokens;
        size_t m_index = 0;

};