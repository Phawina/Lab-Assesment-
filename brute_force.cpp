
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

    // Implement Selection Sort
    for (int i = 0; i < n; i++) {
        
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            // Count element comparisons 
            metrics.comparisons++;
            if (data[j].attack < data[minIndex].attack)
                    minIndex = j;
        }
        // Sort in ascending order of Attack.
        if (minIndex != i) {
            Pokemon temp = data[i];
            data[i] = data[minIndex];
            data[minIndex] = temp;
            // Count element swaps.
            metrics.swaps++;
        }
    }
       
}

// ------------------------------------
// TASK 1B: BUBBLE SORT
// ------------------------------------

void bubbleSort(Pokemon data[],
    int n,
    Metrics& metrics) {

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            metrics.comparisons++;

            if (data[j].attack > data[j + 1].attack) {
                Pokemon temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                metrics.swaps++;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
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

	Pokemon selectionData[MAX_RECORDS];
	Pokemon bubbleData[MAX_RECORDS];

	copyRecords(input, selectionData, n);
	copyRecords(input, bubbleData, n);
   
	Metrics metricsSelection;
    double timeSelection = measureTime(
		selectionSort, selectionData, n, metricsSelection);
    
	Metrics metricsBubble;
    double timeBubble = measureTime(bubbleSort, bubbleData, n, metricsBubble);
  
    cout << left << setw(15) << ("Exp " + to_string(experiment)) << setw(20) << "Selection Sort"
        << setw(15) << metricsSelection.comparisons << setw(15) << metricsSelection.swaps
        << setw(20) << fixed << setprecision(2) << timeSelection << endl;

    cout << left << setw(15) << " " << setw(20) << "Bubble Sort" << setw(15)
        << metricsBubble.comparisons << setw(15) << metricsBubble.swaps << setw(20)
        << fixed << setprecision(2) << timeBubble << endl;

    cout << string(80, '-') << endl;
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

        cout << "Total Pokemon loaded: " << total << endl;

        cout << "\nSample records:\n";
        displayPokemon(pokemon, total);

        // PROVIDED: Prepare input sizes

        Pokemon data100[MAX_RECORDS];
        Pokemon data200[MAX_RECORDS];

        copyRecords(pokemon, data100, 100);
        copyRecords(pokemon, data200, 200);

		//Experiment 3: Prepare records in ascending order of Attack
        Pokemon dataAscending[MAX_RECORDS];
        copyRecords(pokemon, dataAscending, 200);
        Metrics temp;
        selectionSort(dataAscending, 200, temp);

		//Experiment 4: Prepare records in descending order of Attack
        pokemon dataDescending[MAX_RECORDS];
        for (int i = 0; i < 200; i++) {
            dataDescending[i] = dataAscending[199 - i];
		}

        //Table header
        cout << "\nEXPERIMENTAL RESULTS\n" << endl;
        cout << left << setw(15) << "Experiment"
            << setw(20) << "Algorithm"
            << setw(15) << "Comparisons"
            << setw(15) << "Swaps"
            << setw(20) << "Time (us)"
			<< endl;
        cout << string(80, '-') << endl;


        // ---------------------------------
        // EXPERIMENT 1: 100 ORIGINAL
        // ---------------------------------
        runExperiment(1, data100, 100);


        // ---------------------------------
        // EXPERIMENT 2: 200 ORIGINAL
        // ---------------------------------
		runExperiment(2, data200, 200);

        // ---------------------------------
        // EXPERIMENT 3: 200 ASCENDING
        // ---------------------------------
		runExperiment(3, dataAscending, 200);
        
        // ---------------------------------
        // EXPERIMENT 4: 200 DESCENDING
        // ---------------------------------
		runExperiment(4, dataDescending, 200);

        cout << "\nAll experiments completed.\n";
        
    }
    catch (const exception& e) {

        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}


