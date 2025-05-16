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
     std::unordered_map<std::string, std::string> codon_table = {
        {"UUU", "Phenylalanine"}, {"UUC", "Phenylalanine"},
        {"UUA", "Leucine"}, {"UUG", "Leucine"},
        {"CUU", "Leucine"}, {"CUC", "Leucine"}, {"CUA", "Leucine"}, {"CUG", "Leucine"},
        {"AUU", "Isoleucine"}, {"AUC", "Isoleucine"}, {"AUA", "Isoleucine"},
        {"AUG", "Methionine"}, // Start codon
        {"GUU", "Valine"}, {"GUC", "Valine"}, {"GUA", "Valine"}, {"GUG", "Valine"},
        {"UCU", "Serine"}, {"UCC", "Serine"}, {"UCA", "Serine"}, {"UCG", "Serine"},
        {"CCU", "Proline"}, {"CCC", "Proline"}, {"CCA", "Proline"}, {"CCG", "Proline"},
        {"ACU", "Threonine"}, {"ACC", "Threonine"}, {"ACA", "Threonine"}, {"ACG", "Threonine"},
        {"GCU", "Alanine"}, {"GCC", "Alanine"}, {"GCA", "Alanine"}, {"GCG", "Alanine"},
        {"UAU", "Tyrosine"}, {"UAC", "Tyrosine"},
        {"UAA", "Stop"}, {"UAG", "Stop"}, {"UGA", "Stop"}, // Stop codons
        {"CAU", "Histidine"}, {"CAC", "Histidine"},
        {"CAA", "Glutamine"}, {"CAG", "Glutamine"},
        {"AAU", "Asparagine"}, {"AAC", "Asparagine"},
        {"AAA", "Lysine"}, {"AAG", "Lysine"},
        {"GAU", "Aspartic Acid"}, {"GAC", "Aspartic Acid"},
        {"GAA", "Glutamic Acid"}, {"GAG", "Glutamic Acid"},
        {"UGU", "Cysteine"}, {"UGC", "Cysteine"},
        {"UGG", "Tryptophan"},
        {"CGU", "Arginine"}, {"CGC", "Arginine"}, {"CGA", "Arginine"}, {"CGG", "Arginine"},
        {"AGU", "Serine"}, {"AGC", "Serine"},
        {"AGA", "Arginine"}, {"AGG", "Arginine"},
        {"GGU", "Glycine"}, {"GGC", "Glycine"}, {"GGA", "Glycine"}, {"GGG", "Glycine"}
    };

    std::vector<std::string> proteins;
    for (size_t i = 0; i + 2 < rna.size(); i += 3) {
        std::string codon = rna.substr(i, 3);
        if (codon_table.count(codon)) {
            std::string protein = codon_table[codon];
            if (protein == "Stop") break; // Detiene en codón de parada
            proteins.push_back(protein);
        } else {
            proteins.push_back("Unknown");
        }
    }
    return proteins;
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
