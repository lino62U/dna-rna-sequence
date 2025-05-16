#include "funciones.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <unordered_map>

std::vector<Sequence> parse_fasta_file(const std::string& filename) {
    std::vector<Sequence> sequences;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: no se pudo abrir el archivo " << filename << std::endl;
        return sequences;
    }

    std::string line;
    Sequence current;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!current.id.empty()) {
                sequences.push_back(current);
                current = Sequence();
            }
            current.id = line.substr(1);
            current.seq.clear();
        } else {
            for (char c : line) {
                if (!std::isspace(c)) {
                    current.seq += c;
                }
            }
        }
    }
    if (!current.id.empty()) {
        sequences.push_back(current);
    }
    file.close();
    return sequences;
}

std::string detect_sequence_type(const std::string& seq) {
    bool hasT = false, hasU = false, hasNonNuc = false;
    for (char c : seq) {
        char uc = std::toupper(c);
        if (uc == 'T') hasT = true;
        if (uc == 'U') hasU = true;
        if (!(uc == 'A' || uc == 'C' || uc == 'G' || uc == 'T' || uc == 'U' || uc == 'N')) {
            hasNonNuc = true;
            break;
        }
    }
    if (hasNonNuc) return "Proteína";
    if (hasU && !hasT) return "ARN";
    if (hasT && !hasU) return "ADN";
    if (!hasT && !hasU) return "ADN";
    return "Desconocida";
}

std::vector<std::string> extract_amino_acids(const std::string& seq) {
    std::vector<std::string> acids;
    std::unordered_map<char, std::string> amino_map = {
        {'A', "Alanine"}, {'R', "Arginine"}, {'N', "Asparagine"}, {'D', "Aspartic Acid"},
        {'C', "Cysteine"}, {'E', "Glutamic Acid"}, {'Q', "Glutamine"}, {'G', "Glycine"},
        {'H', "Histidine"}, {'I', "Isoleucine"}, {'L', "Leucine"}, {'K', "Lysine"},
        {'M', "Methionine"}, {'F', "Phenylalanine"}, {'P', "Proline"}, {'S', "Serine"},
        {'T', "Threonine"}, {'W', "Tryptophan"}, {'Y', "Tyrosine"}, {'V', "Valine"}
    };
    for (char c : seq) {
        char uc = std::toupper(c);
        if (amino_map.count(uc)) {
            acids.push_back(amino_map[uc]);
        }
    }
    return acids;
}

std::string transcribe_dna_to_rna(const std::string& dna) {
    std::string rna;
    for (char c : dna) {
        switch (std::toupper(c)) {
            case 'A': rna += 'U'; break;
            case 'T': rna += 'A'; break;
            case 'C': rna += 'G'; break;
            case 'G': rna += 'C'; break;
            default: rna += 'N'; break;
        }
    }
    return rna;
}
