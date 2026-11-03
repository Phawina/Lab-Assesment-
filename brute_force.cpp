
/*
 BITP2113 - ALGORITHM ANALYSIS
 LAB ASSESSMENT 1
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <stdexcept>

using namespace std;

const int MAX_RECORDS = 200;

// ------------------------------------
// POKEMON RECORD
// ------------------------------------

struct Pokemon {
    int recordID;
    string name;
    int hp;
    int attack;
    int defense;
    int speed;
};

struct Metrics {
    int comparisons = 0;
    int swaps = 0;
};

// ------------------------------------
// PROVIDED: READ CSV FILE
// ------------------------------------

int loadPokemonCSV(const string& filename,
    Pokemon data[],
    int capacity) {

    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Cannot open CSV file.");
    }

    string line;
    int count = 0;

    // Skip header
    if (!getline(file, line)) {
        throw runtime_error("CSV file is empty.");
    }

    while (getline(file, line)) {

        if (line.empty() || line == "\r")
            continue;

        if (count >= capacity) {
            throw runtime_error("Too many records.");
        }

        stringstream ss(line);
        string id, name, hp, attack, defense, speed;

        if (!getline(ss, id, ',') ||
            !getline(ss, name, ',') ||
            !getline(ss, hp, ',') ||
            !getline(ss, attack, ',') ||
            !getline(ss, defense, ',') ||
            !getline(ss, speed)) {

            throw runtime_error("Invalid CSV record.");
        }

        Pokemon p;

        p.recordID = stoi(id);
        p.name = name;
        p.hp = stoi(hp);
        p.attack = stoi(attack);
        p.defense = stoi(defense);
        p.speed = stoi(speed);

        data[count] = p;
        count++;
    }

    return count;
}

// ------------------------------------
// PROVIDED: COPY ARRAY RECORDS
// ------------------------------------

void copyRecords(const Pokemon source[],
    Pokemon destination[],
    int n) {

    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

// ------------------------------------
// PROVIDED: DISPLAY RECORDS
// ------------------------------------

void displayPokemon(const Pokemon data[],
    int n, int limit = 5) {

    for (int i = 0; i < n && i < limit; i++) {

        cout << data[i].recordID
            << " | " << data[i].name
            << " | Attack: " << data[i].attack
            << endl;
    }
}

// ------------------------------------
// TASK 1A: SELECTION SORT
// ------------------------------------

void selectionSort(Pokemon data[],
    int n,
    Metrics& metrics) {

    // TODO:
    // Implement Selection Sort.
    // Sort in ascending order of Attack.
    // Count element comparisons and swaps.
    // Do not count self-swaps.

}

// ------------------------------------
// TASK 1B: BUBBLE SORT
// ------------------------------------

void bubbleSort(Pokemon data[],
    int n,
    Metrics& metrics) {

    // TODO:
    // Implement Bubble Sort.
    // Sort in ascending order of Attack.
    // Include early termination.
    // Count element comparisons and swaps.

}

// ------------------------------------
// PROVIDED: EXECUTION TIME
// ------------------------------------

double measureTime(
    void (*sortFunction)(Pokemon[], int, Metrics&),
    Pokemon data[],
    int n,
    Metrics& metrics) {

    auto start = chrono::steady_clock::now();

    sortFunction(data, n, metrics);

    auto end = chrono::steady_clock::now();

    chrono::duration<double, micro> elapsed =
        end - start;

    return elapsed.count();
}

// ------------------------------------
// TASK 2: RUN EXPERIMENT
// ------------------------------------

void runExperiment(int experiment,
    const Pokemon input[],
    int n) {

    // TODO:
    // 1. Make separate copies of input.
    // 2. Run Selection Sort.
    // 3. Run Bubble Sort.
    // 4. Record comparisons and swaps.
    // 5. Measure execution time.
    // 6. Display the results.

}

// ------------------------------------
// MAIN PROGRAM
// ------------------------------------

int main() {

    // Replace the file name with your dataset name
    string filename = "pokemon_dataset_A.csv";

    try {

        Pokemon pokemon[MAX_RECORDS];

        int total = loadPokemonCSV(
            filename, pokemon, MAX_RECORDS);

        if (total != MAX_RECORDS) {
            throw runtime_error(
                "Expected exactly 200 records.");
        }

        cout << "Total records: " << total << endl;

        cout << "\nSample records:\n";
        displayPokemon(pokemon, total);

        // PROVIDED: Prepare input sizes

        Pokemon data100[MAX_RECORDS];
        Pokemon data200[MAX_RECORDS];

        copyRecords(pokemon, data100, 100);
        copyRecords(pokemon, data200, 200);

        cout << "\nDataset preparation completed.\n";

        // ---------------------------------
        // EXPERIMENT 1: 100 ORIGINAL
        // ---------------------------------

        // TODO: Run both algorithms using
        // the first 100 records.

        // ---------------------------------
        // EXPERIMENT 2: 200 ORIGINAL
        // ---------------------------------

        // TODO: Run both algorithms using
        // all 200 records.

        // ---------------------------------
        // EXPERIMENT 3: 200 ASCENDING
        // ---------------------------------

        // TODO: Prepare records in
        // ascending order of Attack.
        // Run both algorithms.

        // ---------------------------------
        // EXPERIMENT 4: 200 DESCENDING
        // ---------------------------------

        // TODO: Prepare records in
        // descending order of Attack.
        // Run both algorithms.

    }
    catch (const exception& e) {

        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
