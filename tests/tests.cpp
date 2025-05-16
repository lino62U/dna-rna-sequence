#include <gtest/gtest.h>
#include "funciones.h"  // Aquí van tus funciones: parse_fasta_file, detect_sequence_type, etc.

TEST(BasicFunctionsTest, TestParseFastaFile) {
    // Archivo de prueba con 1 secuencia mínima
    std::string test_file = "../data/simple_sequences.txt";
    auto sequences = parse_fasta_file(test_file);
    ASSERT_EQ(sequences.size(), 1);
    EXPECT_EQ(sequences[0].id, "seq1");
    EXPECT_EQ(sequences[0].seq, "ACGT");
}

TEST(BasicFunctionsTest, TestDetectSequenceType) {
    EXPECT_EQ(detect_sequence_type("ACGT"), "ADN");
    EXPECT_EQ(detect_sequence_type("ACGU"), "ARN");
    EXPECT_EQ(detect_sequence_type("ACDX"), "Proteína");
    EXPECT_EQ(detect_sequence_type("XYZ"), "Proteína");
}

TEST(BasicFunctionsTest, TestExtractAminoAcids) {
    auto acids = extract_amino_acids("ARND");
    ASSERT_EQ(acids.size(), 4);
    EXPECT_EQ(acids[0], "Alanine");
    EXPECT_EQ(acids[1], "Arginine");
    EXPECT_EQ(acids[2], "Asparagine");
    EXPECT_EQ(acids[3], "Aspartic Acid");
}

TEST(BasicFunctionsTest, TestTranscribeDnaToRna) {
    std::string rna = transcribe_dna_to_rna("ATCG");
    // Según tu función: A->U, T->A, C->G, G->C
    EXPECT_EQ(rna, "UAGC");
}
