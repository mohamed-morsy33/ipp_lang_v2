#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

#include "parser.hpp"
#include "tokenize.hpp"


using namespace std;



string tokens_to_asm(const vector<Token>& tokens) {
    stringstream output;
    output << "global _start\n_start:\n";

    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);

        if (token.type == TokenType::_exit) {
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

    Tokenizer tokenizer(contents_stream.str());
    vector<Token> tokenized_contents = tokenizer.tokenize();   
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