#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Struttura per rappresentare le informazioni di un'auto
struct AutoInfo {
    string marca;
    string condizione;
    string alimentazione;
    string cilindrata;
    string colore;
    string sterzo;
    string vetri;
    double kmPercorsi;
    string materialeSedili;
    string tipoCambio;
    double costoTotale;
};

// Funzione per leggere i dati da un file CSV e creare un vettore di AutoInfo
vector<AutoInfo> leggiDatiDaFile(const string& nomeFile) {
    vector<AutoInfo> autoList;

    // Converti la stringa C++ standard in un array di caratteri C-style
    const char* nomeFileCStr = nomeFile.c_str();

    // Apri il file usando l'array di caratteri C-style
    ifstream file(nomeFileCStr);

    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file." << endl;
        exit(EXIT_FAILURE); // o return 1;
    }

    string line;
    getline(file, line); // Ignora l'intestazione

    while (getline(file, line)) {
        stringstream lineStream(line);
        AutoInfo autoInfo;

        getline(lineStream, autoInfo.marca, ',');
        getline(lineStream, autoInfo.condizione, ',');
        getline(lineStream, autoInfo.alimentazione, ',');
        getline(lineStream, autoInfo.cilindrata, ',');
        getline(lineStream, autoInfo.colore, ',');
        getline(lineStream, autoInfo.sterzo, ',');
        getline(lineStream, autoInfo.vetri, ',');
        lineStream >> autoInfo.kmPercorsi;
        getline(lineStream, autoInfo.materialeSedili, ',');
        getline(lineStream, autoInfo.tipoCambio, ',');

        // Conversione del costoTotale in una stringa
        string costoTotaleStr;
        lineStream >> costoTotaleStr;
        autoInfo.costoTotale = stod(costoTotaleStr);  // Converti la stringa in un double

        autoList.push_back(autoInfo);
    }

    file.close();

    return autoList;
}

// Funzione per stampare le informazioni di un'auto
void stampaAuto(const AutoInfo& autoInfo) {
    cout << "Marca: " << autoInfo.marca << endl;
    cout << "Condizione: " << autoInfo.condizione << endl;
    cout << "Alimentazione: " << autoInfo.alimentazione << endl;
    cout << "Cilindrata: " << autoInfo.cilindrata << endl;
    cout << "Colore: " << autoInfo.colore << endl;
    cout << "Sterzo: " << autoInfo.sterzo << endl;
    cout << "Vetri: " << autoInfo.vetri << endl;
    cout << "Km percorsi: " << autoInfo.kmPercorsi << endl;
    cout << "Materiale Sedili: " << autoInfo.materialeSedili << endl;
    cout << "Tipo Cambio: " << autoInfo.tipoCambio << endl;
    cout << "Costo Totale: " << autoInfo.costoTotale << endl;
    cout << "------------------------" << endl;
}

// Funzione per chiedere le preferenze dell'acquirente
void chiediPreferenze(AutoInfo& preferenze) {
    cout << "Vuoi un'auto nuova o usata? (nuova/usata): ";
    cin >> preferenze.condizione;

    cout << "Che tipo di alimentazione preferisci? (elettrica/ibrida/diesel/benzina): ";
    cin >> preferenze.alimentazione;

    cout << "Che tipo di auto stai cercando? (city car/berlina/SUV/coup�/cabriolet): ";
    cin >> preferenze.colore;

    // ... Chiedi ulteriori preferenze ...
}

int main() {
    // Leggi i dati delle auto da file
    vector<AutoInfo> autoList = leggiDatiDaFile("tuofile.csv");

    // Chiedi le preferenze dell'acquirente
    AutoInfo preferenze;
    chiediPreferenze(preferenze);

    // Filtra le auto in base alle preferenze dell'acquirente
    vector<AutoInfo> autoFiltrate;

    for (const auto& autoInfo : autoList) {
        if (autoInfo.condizione == preferenze.condizione &&
            autoInfo.alimentazione == preferenze.alimentazione &&
            autoInfo.colore == preferenze.colore) {
            autoFiltrate.push_back(autoInfo);
        }
    }

    // Stampa le auto filtrate
    cout << "Auto che soddisfano le tue richieste:" << endl;

    for (const auto& autoInfo : autoFiltrate) {
        stampaAuto(autoInfo);
    }

    return 0;
}
