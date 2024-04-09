//
// Created by Hector Murillo on 13/3/24.
//

#include <iostream>
using namespace std;
int main() {
    string equipos[20] = {
            "Arsenal",
            "Liverpool",
            "Manchester City",
            "A Villa",
            "Tottenham",
            "Manchester United",
            "West Ham",
            "Brighton",
            "Wolves",
            "Newcastle",
            "Chelsea",
            "Fulham",
            "Bournemouth",
            "Crystal Palace",
            "Brentford",
            "Everton",
            "Nott'm Forest",
            "Luton",
            "Burnley",
            "Sheffield Utd"
    };
    for (int contadorEquipos = 0; contadorEquipos < 20; contadorEquipos++) {
        cout<<equipos[contadorEquipos]<<endl;
    }
}