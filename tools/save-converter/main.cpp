#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <expected>

using json = nlohmann::json;

std::expected<void, std::string> convert(const std::string& input, const std::string& output) {
    std::ifstream in(input);
    if (!in.is_open()) return std::unexpected("Cannot open input");
    json j;
    in >> j;
    std::ofstream out(output);
    if (!out.is_open()) return std::unexpected("Cannot open output");
    out << j.dump(2);
    return {};
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: save-converter <input> <output>" << std::endl;
        return 1;
    }
    auto res = convert(argv[1], argv[2]);
    if (!res) {
        std::cerr << res.error() << std::endl;
        return 1;
    }
    return 0;
}
