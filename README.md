# Coordinate Systems — C++

A C++ lab implementing a 3D coordinate system class that supports Cartesian, cylindrical, and spherical representations along with standard geometric transformations.

---

## File

```
RLab.cpp    Single-file implementation and demo
```

---

## CoordinateSystem Class

Stores a point in all three coordinate systems simultaneously. Setting a value in cylindrical or spherical automatically converts it to Cartesian as the internal canonical form.

### Coordinate Structs

| Struct | Fields |
|--------|--------|
| Cartesian | x, y, z |
| Cylindrical | r, φ, z |
| Spherical | ρ, θ, φ |

### Transformations (Cartesian)

rotate_cartesian(angle, axis) — rotates the point around X, Y, or Z axis using a 3×3 rotation matrix.

translate_cartesian(dx, dy, dz) — translates the point using a 4×4 translation matrix.

scale_cartesian(sx, sy, sz) — scales each axis using a 4×4 scale matrix.

transform_cartesian(matrix) — applies any arbitrary 3×3 matrix directly.

### Conversions

| Method | Direction |
|--------|-----------|
| convert_to_cylindrical() | Cartesian → Cylindrical |
| convert_to_spherical() | Cartesian → Spherical |
| convert_to_cartesian_from_cylindrical() | Cylindrical → Cartesian |
| convert_to_cartesian_from_spherical() | Spherical → Cartesian |

---

## Build & Run

```bash
g++ -std=c++17 -o coord RLab.cpp
./coord
```

## Expected Output

The main() function runs two demo sequences on different starting points, each applying a 90° Z-rotation, a translation by (1, 2, 3), and a uniform scale of 2:

```
Cartesian: 1, 2, 3
Cartesian after rotation: -2, 1, 3
Cartesian after translation: -1, 3, 6
Cartesian after scaling: -2, 6, 12
```
