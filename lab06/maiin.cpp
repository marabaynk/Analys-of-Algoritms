#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <limits>
#include <iomanip>

#include "ant.hpp"
#include "town.hpp"
#include "main.hpp"

float rand_FloatRange(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

void initTowns(Town* towns, int** townsMatrix)
{
    for (int i = 0; i < TOWN_COUNT; i++)
    {
        towns[i] = Town(i); // Create town object

        for (int j = 0; j < TOWN_COUNT; j++)
        {
            if (i == j)
            {
                townsMatrix[i][j] = 0;
                continue;
            }

            int distance = 1 + std::rand() % MAX_DISTANCE;
            townsMatrix[i][j] = distance; // Update matrix of distances between towns
            townsMatrix[j][i] = distance;
        }
    }
}

float randomFloat(float min, float max) {
    return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}

void initPheromons(float** pheromonMatrix)
{
    for (int i = 0; i < TOWN_COUNT; i++)
    {
        for (int j = 0; j < TOWN_COUNT; j++)
        {
            if (i == j)
            {
                pheromonMatrix[i][j] = 0;
                continue;
            }

            pheromonMatrix[i][j] = 0.1;
        }
    }
}

template <typename T>
void print_matrix(T **matr, int size){
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            std::cout << matr[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void initAnts(Ant* ants, Town* towns)
{
    std::vector<int>leftTownsIDs(TOWN_COUNT); // Create vector of towns' IDs
    std::iota(std::begin(leftTownsIDs), std::end(leftTownsIDs), 0); //

    for (int ant = 0; ant < ANT_COUNT; ant++) 
    {
        int townID = leftTownsIDs[std::rand() % leftTownsIDs.size()]; // Pick random town from towns, that are left
        towns[townID].addAnt(ants[ant]); // Place ant in this town
        ants[ant] = Ant(townID); // Add this town in ant's route
        leftTownsIDs.erase(std::remove(leftTownsIDs.begin(), leftTownsIDs.end(), townID), leftTownsIDs.end()); // Delete occupied town
    }
}

void showAnts(Ant* ants)
{
    for (int i = 0; i < ANT_COUNT; i++)
    {
        ants[i].showAnt();
    }
}

void showTowns(int** townsMatrix)
{
    for (int i = 0; i < TOWN_COUNT; i++)
    {
        for (int j = 0; j < TOWN_COUNT; j++)
        {
            std::cout << townsMatrix[i][j] << (j < TOWN_COUNT - 1 ? " " : "\n");
        }
    }
}

void initParameters(float& a, float& b, int& e)
{
    a = 0.7;
    b = 0.3;
    e = 1;
}

void planRoute(Ant& ant, int** townsMatrix, float** pheromonMatrix, float alpha, float beta)
{
    float top = 0;
    float bottom = 0;
    int startID;
    int bestID = -1;
    float maxP = -1;
    float rand;
    float P_min = 0;
    float P_max = 0;
    float P;
    std::vector<int> destinations = ant.getDestinations();

    for (int j = 0; j < TOWN_COUNT - 1; j++)
    {   
        maxP = -1;
        bestID = -1;
        destinations = ant.getDestinations();
        std::vector<int> route = ant.getRoute(); 
        startID = route[route.size() - 1];  
        rand = rand_FloatRange(0.3, 1);//std::rand() % 1;
        //std::cout << "Rand = " << rand << std::endl;
        P_min = 0;

        for (int i = 0; i < destinations.size(); i++)
        {
            int endID = destinations[i];

            //std::cout << "start/end = " << startID << " " << endID << std::endl;
            //std::cout << "coef" << alpha << " " << beta << std::endl;
            //std::cout << "1 = " << float(pow(pheromonMatrix[startID][endID], alpha)) << std::endl;
            //std::cout << "2 = " << float(pow(float(1 / float(townsMatrix[startID][endID])), beta)) << std::endl;
            top = float(pow(pheromonMatrix[startID][endID], alpha)) * float(pow(float(1 / float(townsMatrix[startID][endID])), beta));
            //std::cout << "top = " << top << std::endl;
            
            bottom = 0;
            for (int k = 0; k < destinations.size(); k++)
            {   
                int tempID = destinations[k];
                float temp = (float)(1.0 / townsMatrix[startID][tempID]);
                bottom += pow(pheromonMatrix[startID][tempID], alpha) * pow(temp, beta);
            }

            //std::cout << "bottom = " << bottom << std::endl;

            
            
            P = float(top / bottom);
            P_min += P;
            P_max = P + P_min;
            //std::cout << "P = " << P << std::endl;
            //std::cout << "P_min = " << P_min << std::endl;


            //if ((P_min <= rand) && (rand <= P_max)){
            if (P_min >= rand){

                //std::cout << "!!!" << std::endl; 
                //std::cout << "PPP = " << P << std::endl;
                //if (maxP < P)
                //{   
                    maxP = P;
                    bestID = destinations[i];
                //}

            }
            
        }
        //std::cout << "BestID = " << bestID << std::endl;  
        ant.updateRoad(bestID, townsMatrix[startID][bestID]);
        //ant.showAnt();
    }
    //ant.showAnt();
}

void updatePheromon(float** pheromonMatrix, Ant* ants)
{
    int found;

    for (int i = 0; i < TOWN_COUNT; i++)
    {
        for (int j = 0; j < TOWN_COUNT; j++)
        {
            if (i == j)
            {
                continue;
            }

            float pheromonSum = 0;

            for (int ant = 0; ant < ANT_COUNT; ant++)
            {
                found = 0;
                for (int k = 0; k < TOWN_COUNT - 1; k++)
                {
                    std::vector<int> antRoute = ants[ant].getRoute();

                    if (antRoute[k] == i && antRoute[k+1] == j)
                    {
                        float currentPheromon = ants[ant].getPheromon();
                        //std::cout << "Ant " << ant << "        " << "Pheromon " << currentPheromon << std::endl;
                        pheromonSum += currentPheromon;
                    }
                }
            }

            pheromonMatrix[i][j] = (1 - P_COEF) * pheromonMatrix[i][j] + pheromonSum;
        }
    }
}

int elit_ants (float ** pheromonMatrix, Ant* ants)
{
    int minLenght = ants[0].getRouteLenght();
    for (int i = 1; i < ANT_COUNT; i++) {
        if (minLenght > ants[i].getRouteLenght()) {
            minLenght = ants[i].getRouteLenght(); 
        }
    }

    //std::cout << minLenght << std::endl;
    //std::cout<< "Pheromon: " << ELITE_ANT * (float(Q)/float(minLenght)) << std::endl;
    for (int i = 1; i < ANT_COUNT; i++) {
        if (ants[i].getRouteLenght() == minLenght) {
            for (int j = 0; j < ants[i].getRoute().size() - 1; j++) {
                int m = ants[i].getRoute()[j];
                int n = ants[i].getRoute()[j + 1];
                
                pheromonMatrix[m][n] += (ELITE_ANT * (float(Q)/float(minLenght)));
                pheromonMatrix[n][m] += (ELITE_ANT * (float(Q)/float(minLenght)));
            }
        }
    }

    return minLenght;
}

int antAlgorithm(Town* towns, int** townsMatrix, float** pheromonMatrix, Ant* ants, float alpha)
{
    initTowns(towns, townsMatrix);
    initPheromons(pheromonMatrix);
    int currentLenght = 0;
    int Lmin = 1e5;
    for (int gen = 0; gen < GENERATIONS; gen++)
    {
        //std::cout << "GENERATION " << gen << "\n" << std::endl;
        initAnts(ants, towns);
        for (int ant = 0; ant < ANT_COUNT; ant++)
        {
            //std::cout << "ANT " << ant <<  std::endl;ew
            planRoute(ants[ant], townsMatrix, pheromonMatrix, alpha, 1 - alpha);
            //ants[ant].showAnt();
            //std::cout << std::endl;
        }
        updatePheromon(pheromonMatrix, ants);
        //print_matrix<float> (pheromonMatrix, TOWN_COUNT);
        currentLenght = elit_ants(pheromonMatrix, ants);
        //std::cout << "CURRENT LENGTH " << currentLenght << std::endl;
        if (currentLenght < Lmin)
        {
            Lmin = currentLenght;     
        }
        //std::cout << "Lmin: " << Lmin << std::endl;
        //print_matrix<float> (pheromonMatrix, TOWN_COUNT);
    }

    return Lmin;
}

void printParameters(float a, float p, int e, int gen, int length)
{
    std::cout.precision(4);
    std::cout << std::setw(5) << float(a) << " | " << std::setw(5) << p << " | " << std::setw(5) << e << std::setw(5) << " | " << gen << " | " << std::setw(8) << length << std::endl;
}

void parametrization(Town* towns, int** townsMatrix, float** pheromonMatrix, Ant* ants)
{
    float a = 0.0;
    float p = 0.0;
    int length;
    std::cout << "Alpha | " << "Phero | " << "Elite | " << "Gen   | " << "Length" << std::endl;
    int minLen = 1e5;    
    float topA;
    float topP;
    float topE;
    float topGen;            
    while (a <= 2)
    {
        while (b <= 2)
        {
            for (int e = 0; e < 5; e++)
            {
                for (int gen = 1; gen < 10; gen++)
                {
                    length = antAlgorithm(towns, townsMatrix, pheromonMatrix, ants, float(a));
                    printParameters(float(a), p, e, gen, length);
                    if (minLen > length){
                        minLen = length;
                        topA = a;
                        topP = p;
                        topE = e;
                        topGen = gen;
                    }
                }
            }
            b += float(0.2);
        }
        p = 0;
        a = float(a + float(0.2));   
    }
    std::cout << "\n\n\n";
    std::cout << minLen << " | " << topA << " | " << topP << " | " << topE << " | " << topGen << std::endl;
}


int main(void)
{
    srand(time(NULL));
    Town* towns = new Town[TOWN_COUNT];
    int** townsMatrix = new int*[TOWN_COUNT];
    for (int i = 0; i < TOWN_COUNT; i++)
    {
        townsMatrix[i] = new int[TOWN_COUNT];
    }
    //initTowns(towns, townsMatrix);

    Ant* ants = new Ant[ANT_COUNT];

    float alpha, beta;
    int e;

    initParameters(alpha, beta, e);

    float** pheromonMatrix = new float*[TOWN_COUNT];
    for (int i = 0; i < TOWN_COUNT; i++)
    {
        pheromonMatrix[i] = new float[TOWN_COUNT];
    }

    int length = antAlgorithm(towns, townsMatrix, pheromonMatrix, ants, alpha);
    std::cout << length << std::endl;

    parametrization(towns, townsMatrix, pheromonMatrix, ants);
    //initPheromons(pheromonMatrix);

/*     print_matrix<float> (pheromonMatrix, TOWN_COUNT);

    int Lmax = std::numeric_limits<int>::infinity();

    for (int gen = 0; gen < GENERATIONS; gen++)
    {
        std::cout << "GENERATION " << gen << "\n" << std::endl;
        float P = 0.0;
        initAnts(ants, towns);
        
        for (int ant = 0; ant < ANT_COUNT; ant++)
        {
            std::cout << "ANT " << ant <<  std::endl;
            planRoute(ants[ant], townsMatrix, pheromonMatrix, alpha, beta);
            ants[ant].showAnt();
            std::cout << std::endl;
        }

        updatePheromon(pheromonMatrix, ants);

        print_matrix<float> (pheromonMatrix, TOWN_COUNT);

        elit_ants(pheromonMatrix, ants);

        std::cout << std::endl;

        print_matrix<float> (pheromonMatrix, TOWN_COUNT);
    }
 */ 
    return 0;
}
