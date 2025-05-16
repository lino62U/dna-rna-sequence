#pragma once
#include <string>
#include <vector>

struct Sequence {
    std::string id;
    std::string seq;
};

std::vector<Sequence> parse_fasta_file(const std::string& filename);
std::string detect_sequence_type(const std::string& seq);
std::vector<std::string> extract_amino_acids(const std::string& seq);
std::string transcribe_dna_to_rna(const std::string& dna);
