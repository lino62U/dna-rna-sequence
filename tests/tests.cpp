#include <gtest/gtest.h>
#include <iostream>
#include <filesystem>
#include "funciones.h"  // tu header con parse_fasta_file, etc.

TEST(FASTAParsingTest, ParsesAndClassifiesCorrectly) {
    std::string path = "sequences.txt";  // Ruta relativa desde build/
    
    std::cout << "Leyendo archivo: " << std::filesystem::absolute(path) << std::endl;
    if (!std::filesystem::exists(path)) {
        std::cerr << "Error: El archivo no existe!" << std::endl;
        FAIL() << "No se encontró el archivo de secuencias: " << path;
    }
    
    auto sequences = parse_fasta_file(path);

    ASSERT_GE(sequences.size(), 2) << "Se esperaban al menos 2 secuencias.";

    for (const auto& [id, seq] : sequences) {
        SequenceType type = detect_sequence_type(seq);
        EXPECT_NE(type, SequenceType::Unknown) << "ID: " << id;

        if (type == SequenceType::Protein) {
            auto acids = extract_amino_acids(seq);
            EXPECT_GE(acids.size(), 5) << "ID: " << id << " - No se encontraron suficientes aminoácidos.";
        }
    }
}
