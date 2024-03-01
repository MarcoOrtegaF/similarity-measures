#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>      // Include the library to manage files
#include <sstream>      // Include the library to Split a string
#include <iomanip>      // std::setprecision

struct Trajectory;
double SpADeDistance(const Trajectory& , const Trajectory& );
Trajectory Trajectoryfromfile(std::string );

// Structure to represent a trajectory
struct Trajectory {
    std::vector<double> x; // coordinates x
    std::vector<double> y; // coordinates y
};

int main() {
    Trajectory Trajectory1;
    Trajectory Trajectory2;

    // Rute to the files with the two trajecrtories
    std::string nombreArchivo1 = "/workspaces/similarity-measures/Trajectories/Trajectory1.txt";
    std::string nombreArchivo2 = "/workspaces/similarity-measures/Trajectories/Trajectory2.txt";

    Trajectory1 = Trajectoryfromfile(nombreArchivo1);
    Trajectory2 = Trajectoryfromfile(nombreArchivo2);

    // Calculate the SpADe distance between the trajectories
    double spadeDist = SpADeDistance(Trajectory1, Trajectory2);

    std::cout << std::setprecision(15) << "Distancia SpADe entre las trayectorias: \n" << spadeDist << "\n\n\n";

    return 0;
}

// Function to calculate the SpADe distance between two trajectories
double SpADeDistance(const Trajectory& traj1, const Trajectory& traj2) {
    // Implementa la lógica para calcular la distancia SpADe
    double distance = 0.0;

    // For simplicity, we assume that the trajectories have the same length
    size_t length = traj1.x.size();

    for (size_t i = 0; i < length; ++i) {
        double dx = traj1.x[i] - traj2.x[i];
        double dy = traj1.y[i] - traj2.y[i];
        distance += std::sqrt(dx * dx + dy * dy);
    }

    return distance;
}

// Function to open file with coordinates
Trajectory Trajectoryfromfile(std::string nombreArchivo){
    Trajectory Trajectoryfromfile;

    // ifstream object to read the file
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;   // Error while opening the file
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);  // Split the line into two numbers delimited by a comma
        double x, y;
        char delimiter;

        // Read the first number
        iss >> x;

        // Read the delimiter (comma)
        iss >> delimiter;

        // Read the second number
        iss >> y;

        // Check if the read was successful
        if (iss.fail()) {
            std::cerr << "Error obteniendo la informacion" << std::endl;
        }
        //std::cout << "Distancia SpADe entre las trayectorias: \n" << x << " "<< y << " \n";
        Trajectoryfromfile.x.push_back(x);
        Trajectoryfromfile.y.push_back(y);
    }

    archivo.close(); // Close the file

    return Trajectoryfromfile;
}
