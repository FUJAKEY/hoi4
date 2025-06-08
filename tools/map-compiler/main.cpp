#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <expected>

std::expected<void, std::string> compile(const std::string& input, const std::string& output) {
    std::ifstream in(input);
    if (!in.is_open()) return std::unexpected("Failed to open input");
    std::ofstream out(output, std::ios::binary);
    if (!out.is_open()) return std::unexpected("Failed to open output");
    std::string line;
    while (std::getline(in, line)) {
        out.write(line.c_str(), line.size());
    }
    return {};
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: map-compiler <input.svg> <output.bin>" << std::endl;
        return 1;
    }
    auto res = compile(argv[1], argv[2]);
    if (!res) {
        std::cerr << res.error() << std::endl;
        return 1;
    }
    return 0;
}
