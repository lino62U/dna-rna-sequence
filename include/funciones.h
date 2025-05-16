// include/funciones.h
#pragma once
#include <string>
#include <vector>

enum class SequenceType { DNA, RNA, Protein, Unknown };

SequenceType detect_sequence_type(const std::string& seq);
std::vector<std::string> extract_amino_acids(const std::string& seq);
std::vector<std::pair<std::string, std::string>> parse_fasta_file(const std::string& filename);

