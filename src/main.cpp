#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
 * Estructura para almacenar una secuencia FASTA:
 * - id: identificador de la secuencia (sin el '>').
 * - seq: secuencia de nucleótidos o aminoácidos.
 */
struct Sequence {
    string id;
    string seq;
};

/*
 * Lee un archivo FASTA y devuelve un vector de estructuras Sequence.
 * Separa cada secuencia al encontrar '>' en el archivo:contentReference[oaicite:8]{index=8}:contentReference[oaicite:9]{index=9}.
 */
vector<Sequence> parse_fasta_file(const string& filename) {
    vector<Sequence> sequences;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: no se pudo abrir el archivo " << filename << endl;
        return sequences;
    }

    string line;
    Sequence current;
    while (getline(file, line)) {
        if (line.empty()) continue; // Ignorar líneas en blanco.
        if (line[0] == '>') {
            // Nueva secuencia: guardar la anterior si existe.
            if (!current.id.empty()) {
                sequences.push_back(current);
                current = Sequence(); // Reiniciar para la siguiente secuencia.
            }
            // Guardar el ID (sin el símbolo '>').
            current.id = line.substr(1);
            current.seq.clear();
        } else {
            // Agregar línea de secuencia (omitimos espacios).
            for (char c : line) {
                if (!isspace(c)) {
                    current.seq += c;
                }
            }
        }
    }
    // Agregar la última secuencia leída.
    if (!current.id.empty()) {
        sequences.push_back(current);
    }
    file.close();
    return sequences;
}

/*
 * Detecta el tipo de secuencia (ADN, ARN, Proteína, Desconocida) según sus caracteres.
 * ADN: sólo A, C, G, T (posiblemente N):contentReference[oaicite:10]{index=10}.
 * ARN: sólo A, C, G, U (posiblemente N):contentReference[oaicite:11]{index=11}.
 * Proteína: contiene letras fuera de los nucleótidos estándar.
 */
string detect_sequence_type(const string& seq) {
    bool hasT = false, hasU = false;
    bool hasNonNuc = false;
    for (char c : seq) {
        char uc = toupper(c);
        if (uc == 'T') hasT = true;
        if (uc == 'U') hasU = true;
        if (!(uc == 'A' || uc == 'C' || uc == 'G' || uc == 'T' || uc == 'U' || uc == 'N')) {
            hasNonNuc = true;
            break;
        }
    }
    if (hasNonNuc) {
        // Caracter no pertenece al alfabeto nucleotídico => Proteína.
        return "Prote\u00EDna";
    }
    if (hasU && !hasT) {
        return "ARN";  // Contiene U pero no T
    }
    if (hasT && !hasU) {
        return "ADN";  // Contiene T pero no U
    }
    if (!hasT && !hasU) {
        return "ADN";  // Sólo A, C, G (y N) => asumimos ADN
    }
    // Caso raro (ambos T y U presentes) o no clasificado.
    return "Desconocida";
}

/*
 * Extrae los aminoácidos (por nombre) de una secuencia proteica.
 * Traduce cada letra a su nombre completo (ej. 'A' -> "Alanine", 'D' -> "Aspartic Acid", etc.):contentReference[oaicite:12]{index=12}.
 */
vector<string> extract_amino_acids(const string& seq) {
    vector<string> acids;
    for (char c : seq) {
        switch (toupper(c)) {
            case 'A': acids.push_back("Alanine"); break;
            case 'R': acids.push_back("Arginine"); break;
            case 'N': acids.push_back("Asparagine"); break;
            case 'D': acids.push_back("Aspartic Acid"); break;
            case 'C': acids.push_back("Cysteine"); break;
            case 'E': acids.push_back("Glutamic Acid"); break;
            case 'Q': acids.push_back("Glutamine"); break;
            case 'G': acids.push_back("Glycine"); break;
            case 'H': acids.push_back("Histidine"); break;
            case 'I': acids.push_back("Isoleucine"); break;
            case 'L': acids.push_back("Leucine"); break;
            case 'K': acids.push_back("Lysine"); break;
            case 'M': acids.push_back("Methionine"); break;
            case 'F': acids.push_back("Phenylalanine"); break;
            case 'P': acids.push_back("Proline"); break;
            case 'S': acids.push_back("Serine"); break;
            case 'T': acids.push_back("Threonine"); break;
            case 'W': acids.push_back("Tryptophan"); break;
            case 'Y': acids.push_back("Tyrosine"); break;
            case 'V': acids.push_back("Valine"); break;
            default: break;
        }
    }
    return acids;
}

/*
 * Transcribe una secuencia de ADN a ARN.
 * Reemplaza todas las 'T' por 'U'.
 */

std::string transcribe_dna_to_rna(const std::string& dna) {
    std::string rna;
    for (char c : dna) {
        switch (toupper(c)) {
            case 'A': rna += 'U'; break;
            case 'T': rna += 'A'; break;
            case 'C': rna += 'G'; break;
            case 'G': rna += 'C'; break;
            default: rna += 'N'; break;
        }
    }
    return rna;
}


int main() {
    // Leer el archivo FASTA (se busca en el directorio actual).
    string filename = "sequences.txt";
    vector<Sequence> sequences = parse_fasta_file(filename);

    // Procesar cada secuencia leída.
    for (const auto& seq : sequences) {
        cout << "> ID: " << seq.id << endl;
        string type = detect_sequence_type(seq.seq);
        cout << "Tipo: " << type << endl;
        
        if (type == "Prote\u00EDna") {
            vector<string> acids = extract_amino_acids(seq.seq);
            if (!acids.empty()) {
                cout << "Amino\u00E1cidos:" << endl;
                for (const auto& aa : acids) {
                    cout << "- " << aa << endl;
                }
            }
        }else if (type == "ADN") {
            string rna = transcribe_dna_to_rna(seq.seq);
            cout << "ARN transcrito: " << rna << endl;
        }

        cout << endl;  // Separación entre secuencias
    }
    return 0;
}
