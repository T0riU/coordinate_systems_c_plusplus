#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class CoordinateSystem {
public:
    struct Cartesian {
        double x;
        double y;
        double z;
    };

    struct Cylindrical {
        double r;
        double phi;
        double z;
    };

    struct Spherical {
        double rho;
        double theta;
        double phi;
    };

    void set_cartesian(Cartesian cartesian) {
        cartesian_ = cartesian;
    }

    void set_cylindrical(Cylindrical cylindrical) {
        cylindrical_ = cylindrical;
    }

    void set_spherical(Spherical spherical) {
        spherical_ = spherical;
    }

    Cartesian get_cartesian() const {
        return cartesian_;
    }

    Cylindrical get_cylindrical() const {
        return cylindrical_;
    }

    Spherical get_spherical() const {
        return spherical_;
    }

    void transform_cartesian(const std::vector<std::vector<double>>& matrix) {
        Cartesian cartesian = cartesian_;
        cartesian_.x = matrix[0][0] * cartesian.x + matrix[0][1] * cartesian.y + matrix[0][2] * cartesian.z;
        cartesian_.y = matrix[1][0] * cartesian.x + matrix[1][1] * cartesian.y + matrix[1][2] * cartesian.z;
        cartesian_.z = matrix[2][0] * cartesian.x + matrix[2][1] * cartesian.y + matrix[2][2] * cartesian.z;
    }

    void rotate_cartesian(double angle, char axis) {
        std::vector<std::vector<double>> matrix(3, std::vector<double>(3, 0.0));

        switch (axis) {
        case 'x':
            matrix[0][0] = 1.0;
            matrix[1][1] = std::cos(angle);
            matrix[1][2] = -std::sin(angle);
            matrix[2][1] = std::sin(angle);
            matrix[2][2] = std::cos(angle);
            break;
        case 'y':
            matrix[0][0] = std::cos(angle);
            matrix[0][2] = std::sin(angle);
            matrix[1][1] = 1.0;
            matrix[2][0] = -std::sin(angle);
            matrix[2][2] = std::cos(angle);
            break;
        case 'z':
            matrix[0][0] = std::cos(angle);
            matrix[0][1] = -std::sin(angle);
            matrix[1][0] = std::sin(angle);
            matrix[1][1] = std::cos(angle);
            matrix[2][2] = 1.0;
            break;
        default:
            std::cerr << "Invalid axis: " << axis << std::endl;
            return;
        }

        transform_cartesian(matrix);
    }

    void translate_cartesian(double dx, double dy, double dz) {
        std::vector<std::vector<double>> matrix = {
            {1.0, 0.0, 0.0, dx},
            {0.0, 1.0, 0.0, dy},
            {0.0, 0.0, 1.0, dz},
            {0.0, 0.0, 0.0, 1.0}
        };

        transform_cartesian(matrix);
    }

    void scale_cartesian(double sx, double sy, double sz) {
        std::vector<std::vector<double>> matrix = {
            {sx, 0.0, 0.0, 0.0},
            {0.0, sy, 0.0, 0.0},
            {0.0, 0.0, sz, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };

        transform_cartesian(matrix);
    }

    void convert_to_cylindrical() {
        cylindrical_.r = std::sqrt(cartesian_.x * cartesian_.x + cartesian_.y * cartesian_.y);
        cylindrical_.phi = std::atan2(cartesian_.y, cartesian_.x);
        cylindrical_.z = cartesian_.z;
    }

    void convert_to_spherical() {
        spherical_.rho = std::sqrt(cartesian_.x * cartesian_.x + cartesian_.y * cartesian_.y + cartesian_.z * cartesian_.z);
        spherical_.theta = std::atan2(std::sqrt(cartesian_.x * cartesian_.x + cartesian_.y * cartesian_.y), cartesian_.z);
        spherical_.phi = std::atan2(cartesian_.y, cartesian_.x);
    }

    void convert_to_cartesian_from_cylindrical() {
        cartesian_.x = cylindrical_.r * std::cos(cylindrical_.phi);
        cartesian_.y = cylindrical_.r * std::sin(cylindrical_.phi);
        cartesian_.z = cylindrical_.z;
    }
    void convert_to_cartesian_from_spherical() {
        cartesian_.x = spherical_.rho * std::sin(spherical_.theta) * std::cos(spherical_.phi);
        cartesian_.y = spherical_.rho * std::sin(spherical_.theta) * std::sin(spherical_.phi);
        cartesian_.z = spherical_.rho * std::cos(spherical_.theta);
    }

    void set_cartesian(double x, double y, double z) {
        cartesian_.x = x;
        cartesian_.y = y;
        cartesian_.z = z;
    }

    void set_cylindrical(double r, double phi, double z) {
        cylindrical_.r = r;
        cylindrical_.phi = phi;
        cylindrical_.z = z;
        convert_to_cartesian_from_cylindrical();
    }

    void set_spherical(double rho, double theta, double phi) {
        spherical_.rho = rho;
        spherical_.theta = theta;
        spherical_.phi = phi;
        convert_to_cartesian_from_spherical();
    }
    private:
        Cartesian cartesian_;
        Cylindrical cylindrical_;
        Spherical spherical_;
};

int main() {
    CoordinateSystem temp;
    temp.set_cartesian(1.0, 2.0, 3.0);
    cout << "Cartesian: " << temp.get_cartesian().x << ", " << temp.get_cartesian().y << ", " << temp.get_cartesian().z << endl;
    temp.rotate_cartesian(M_PI / 2.0, 'z');
    cout << "Cartesian after rotation: " << temp.get_cartesian().x << ", " << temp.get_cartesian().y << ", " << temp.get_cartesian().z << endl;
    temp.translate_cartesian(1.0, 2.0, 3.0);
    cout << "Cartesian after translation: " << temp.get_cartesian().x << ", " << temp.get_cartesian().y << ", " << temp.get_cartesian().z << endl;
    temp.scale_cartesian(2.0, 2.0, 2.0);
    cout << "Cartesian after scaling: " << temp.get_cartesian().x << ", " << temp.get_cartesian().y << ", " << temp.get_cartesian().z << endl;
    temp.set_cartesian(3.3, 2.2, 4.4);
    cout << "Cartesian: " << temp.get_cartesian().x << ", " << temp.get_cartesian().y << ", " << temp.get_cartesian().z << endl;
    temp.rotate_cartesian(M_PI / 2.0, 'z');
    cout << "Cartesian after rotation: " << temp.get_cartesian().x << ", " << temp.get_cartesian().y << ", " << temp.get_cartesian().z << endl;
    temp.translate_cartesian(1.0, 2.0, 3.0);
    cout << "Cartesian after translation: " << temp.get_cartesian().x << ", " << temp.get_cartesian().y << ", " << temp.get_cartesian().z << endl;
    temp.scale_cartesian(2.0, 2.0, 2.0);
    cout << "Cartesian after scaling: " << temp.get_cartesian().x << ", " << temp.get_cartesian().y << ", " << temp.get_cartesian().z << endl;
    return 0;
}