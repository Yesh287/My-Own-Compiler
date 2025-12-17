#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <optional>
#include <vector>
#include "./tokenization.hpp"
#include "./parser.hpp"
#include "./generation.hpp"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Incorrect Usage . Please use...." << '\n';
        std::cerr << "hydro <intput>" << '\n';
        return EXIT_FAILURE;
    }
    
    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }
    Tokenizer tokenizer(contents);
    std::vector<Token> tokens = tokenizer.tokenize();
    Parser parser(tokens);
    std::optional <NodeExit> tree = parser.parse();
    if(!tree.has_value()) {
        std::cerr << "No Exit Statement Found" << std::endl;
        exit(EXIT_FAILURE);
    }
    Generator generator(tree.value());
    {
        std::fstream file("./out.asm", std::ios::out);
        file << generator.generate();
    }

    system("nasm -felf64 ./out.asm");
    system("ld -o out out.o");
    return EXIT_SUCCESS;
}