#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "funciones.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_fasta>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Sequence> sequences = parse_fasta_file(filename);

    for (const auto& seq : sequences) {
        std::cout << "> ID: " << seq.id << std::endl;
        std::string type = detect_sequence_type(seq.seq);
        std::cout << "Tipo: " << type << std::endl;

        if (type == "Proteína") {
            auto acids = extract_amino_acids(seq.seq);
            if (!acids.empty()) {
                std::cout << "Aminoácidos:\n";
                for (const auto& aa : acids) {
                    std::cout << "- " << aa << std::endl;
                }
            }
        } else if (type == "ADN") {
            std::string rna = transcribe_dna_to_rna(seq.seq);
            std::cout << "ARN transcrito: " << rna << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
