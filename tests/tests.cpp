#include <gtest/gtest.h>
#include "funciones.h"
#include <fstream>
#include <filesystem>

// Función auxiliar para crear archivos de prueba
void write_temp_fasta(const std::string& filename, const std::string& content) {
    std::ofstream out(filename);
    out << content;
    out.close();
}

// Test para detectar el tipo de secuencia
TEST(SequenceTypeTest, DetectADN) {
    EXPECT_EQ(detect_sequence_type("ACGT"), "ADN");
    EXPECT_EQ(detect_sequence_type("acgt"), "ADN");
    EXPECT_EQ(detect_sequence_type("NNNN"), "ADN");
}

TEST(SequenceTypeTest, DetectARN) {
    EXPECT_EQ(detect_sequence_type("ACGU"), "ARN");
    EXPECT_EQ(detect_sequence_type("acgu"), "ARN");
}

TEST(SequenceTypeTest, DetectProteina) {
    EXPECT_EQ(detect_sequence_type("ARND"), "Proteína");  // Aminoácidos válidos
    EXPECT_EQ(detect_sequence_type("XYZ"), "Proteína");   // Caracteres no reconocidos como nucleótidos
    EXPECT_EQ(detect_sequence_type("MFT"), "Proteína");   // T está, pero también hay aminoácidos
}

TEST(SequenceTypeTest, DetectDesconocida) {
    EXPECT_EQ(detect_sequence_type("AUT"), "Desconocida"); // Mezcla de T y U
}

// Test para transcripción ADN -> ARN
TEST(TranscriptionTest, DnaToRna) {
    EXPECT_EQ(transcribe_dna_to_rna("ATCG"), "UAGC");
    EXPECT_EQ(transcribe_dna_to_rna("ttagc"), "AAUCG");
    EXPECT_EQ(transcribe_dna_to_rna("NXYZ"), "NNNN");  // Caracteres no válidos se transforman en 'N'
}

// Test para extracción de aminoácidos
TEST(AminoAcidTest, ExtractAminoAcids) {
    auto result = extract_amino_acids("ARND");
    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "Alanine");
    EXPECT_EQ(result[1], "Arginine");
    EXPECT_EQ(result[2], "Asparagine");
    EXPECT_EQ(result[3], "Aspartic Acid");

    auto result2 = extract_amino_acids("xyz"); // minúsculas no válidas, no deberían retornar nada
    EXPECT_EQ(result2[0], "Tyrosine");
}

