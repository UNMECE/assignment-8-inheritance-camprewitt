#include <iostream>
#include <cmath>

const double EPSILON_0 = 8.854187817e-12; // Permittivity of free space (C^2/(N·m^2))
const double MU_0 = 4 * M_PI * 1e-7;      // Permeability of free space (T·m/A)

// Base class definition
class Field {
protected:
    double *value; // Dynamically allocated array for x, y, z components

public:
    // Default constructor
    Field() {
        value = new double[3]{0.0, 0.0, 0.0};
    }

    // Parameterized constructor
    Field(double x, double y, double z) {
        value = new double[3]{x, y, z};
    }

    // Destructor
    virtual ~Field() {
        delete[] value;
    }

    // Method to print the components
    virtual void printMagnitude() const {
        std::cout << "Field Components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")" << std::endl;
        std::cout << "Magnitude: " << calculateMagnitude() << std::endl;
    }

    // Method to calculate magnitude
    double calculateMagnitude() const {
        return std::sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2]);
    }

    // Overload the assignment operator for deep copy
    Field& operator=(const Field& other) {
        if (this != &other) {
            for (int i = 0; i < 3; i++) {
                value[i] = other.value[i];
            }
        }
        return *this;
    }
};

// Derived class for Electric Field
class Electric_Field : public Field {
private:
    double E_calculated;

public:
    // Default constructor
    Electric_Field() : Field(), E_calculated(0.0) {}

    // Parameterized constructor
    Electric_Field(double x, double y, double z) : Field(x, y, z), E_calculated(0.0) {}

    // Method to calculate electric field using Gauss' Law
    void calculateElectricField(double Q, double r) {
        E_calculated = Q / (4 * M_PI * EPSILON_0 * r * r);
    }

    // Print the calculated electric field
    void printElectricField() const {
        std::cout << "Calculated Electric Field: " << E_calculated << " N/C" << std::endl;
    }

    // Overload the '+' operator
    Electric_Field operator+(const Electric_Field& other) const {
        return Electric_Field(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
    }

    // Overload the '<<' operator
    friend std::ostream& operator<<(std::ostream& os, const Electric_Field& field) {
        os << "Electric Field: (" << field.value[0] << ", " << field.value[1] << ", " << field.value[2] << ")";
        return os;
    }
};

// Derived class for Magnetic Field
class Magnetic_Field : public Field {
private:
    double B_calculated;

public:
    // Default constructor
    Magnetic_Field() : Field(), B_calculated(0.0) {}

    // Parameterized constructor
    Magnetic_Field(double x, double y, double z) : Field(x, y, z), B_calculated(0.0) {}

    // Method to calculate magnetic field using Ampere's Law
    void calculateMagneticField(double I, double r) {
        B_calculated = (MU_0 * I) / (2 * M_PI * r);
    }

    // Print the calculated magnetic field
    void printMagneticField() const {
        std::cout << "Calculated Magnetic Field: " << B_calculated << " T" << std::endl;
    }

    // Overload the '+' operator
    Magnetic_Field operator+(const Magnetic_Field& other) const {
        return Magnetic_Field(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
    }

    // Overload the '<<' operator
    friend std::ostream& operator<<(std::ostream& os, const Magnetic_Field& field) {
        os << "Magnetic Field: (" << field.value[0] << ", " << field.value[1] << ", " << field.value[2] << ")";
        return os;
    }
};

// Main function to demonstrate usage
int main() {
    // Create electric and magnetic field objects
    Electric_Field E1(1e5, 2.0, 3.0);
    Electric_Field E2(4e5, 5.5, 6.6);
    Magnetic_Field M1(3.0, 4.0, 5.0);
    Magnetic_Field M2(7.0, 8.0, 9.0);

    // Print initial components
    E1.printMagnitude();
    M1.printMagnitude();

    // Calculate and print electric field using Gauss' Law
    E1.calculateElectricField(1e-6, 0.05);
    E1.printElectricField();

    // Calculate and print magnetic field using Ampere's Law
    M1.calculateMagneticField(10.0, 0.02);
    M1.printMagneticField();

    // Demonstrate operator overloading
    Electric_Field E3 = E1 + E2;
    Magnetic_Field M3 = M1 + M2;

    std::cout << E3 << std::endl;
    std::cout << M3 << std::endl;

    return 0;
}