#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

using namespace std;

enum class TokenType {
    _return,
    int_literal,
    semicolon, 
};

struct Token {
    TokenType type;
    optional<string> value {};
};

string tokens_to_asm(const vector<Token>& tokens) {
    stringstream output;
    output << "global _start\n_start:\n";

    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);

        if (token.type == TokenType::_return) {
            if (i + 1 < tokens.size() && tokens.at(i + 1).type == TokenType::int_literal) { 
                if (i + 2 < tokens.size() && tokens.at(i + 2).type == TokenType::semicolon) {
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens.at(i + 1).value.value() << "\n";
                    output << "    syscall";
                }
            }
        }
    }


    return output.str();
}

vector<Token> tokenize(const string& str) {
    vector<Token> tokens {};
    string buf {}; 
    
    for (int i = 0; i < str.length(); i++) {
        char c = str.at(i);
        if (isalpha(c)) {
            buf.push_back(c);
            i++;
            while (i < str.length() && isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if (buf == "return") {
                tokens.push_back({.type=TokenType::_return});
                buf.clear();
                continue;
            }
            else {
                std::cerr << "Unknown token: " << buf << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (isdigit(c)) {
            buf.push_back(c);
            i++;
            while (i < str.length() && isdigit(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type=TokenType::int_literal, .value=buf});
            buf.clear();
            continue;
        }
        else if (c == ';') {
            tokens.push_back({.type=TokenType::semicolon});
        }
        else if (isspace(c)) {
            continue;
        }
        else {
            std::cerr << "Unknown token: " << c << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    /*
    for (const Token& token : tokens) {
        cout << "Token(type=" << static_cast<int>(token.type)
             << ", value=" << token.value.value_or("") << ")" << endl;
    }
    */

    return tokens;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Incorrect usage" << endl;
        cerr << "Usage: " << argv[0] << " <file>" << endl;
        return EXIT_FAILURE;
    }

    fstream input(argv[1], ios::in);
    stringstream contents_stream;
    contents_stream << input.rdbuf();

    input.close();
    vector<Token> tokenized_contents = tokenize(contents_stream.str());   
    // cout << tokens_to_asm(tokenized_contents) << endl;
    
    
    {
        fstream output_file("out.asm", ios::out);
        output_file << tokens_to_asm(tokenized_contents);
    }

    system("wsl nasm -felf64 out.asm");
    system("wsl ld -o out out.o");
    system("wsl ./out; echo $?");
    //system("./program.exe");

    return EXIT_SUCCESS;
}