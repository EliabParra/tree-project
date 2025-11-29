# Proyecto: Sistema de Sucesión Real en Árbol Binario

Este repositorio implementa un sistema de gestión de la línea de sucesión de una monarquía utilizando estructuras dinámicas en C++ (árbol binario personalizado). Convierte datos desde un archivo CSV en nodos del árbol y aplica reglas complejas para determinar automáticamente quién debe ser el nuevo rey.

## Características

- **Carga de CSV**: Construcción automática del árbol genealógico desde `bin/datos.csv`.
- **Árbol Binario**: Implementación manual de `Node` y `Tree` sin librerías externas de estructuras de datos.
- **Sucesión Automática**: Algoritmo robusto que maneja:
    - Primogenitura (Hijos).
    - Ramas colaterales (Hermanos, Tíos).
    - Ascenso de ancestros.
    - Preferencia masculina con fallback a femenina.
    - Límite de edad (70 años).
- **Interfaz Interactiva**: Menú en español para visualizar la sucesión, actualizar estados (muerte, edad) y evaluar la corona.

## Estructura

```
bin/          # Ejecutable y archivos de datos (CSV de ejemplo)
src/          # Código fuente
  ├── main.cpp
  ├── Node/
  │   └── Node.h
  └── Tree/
      └── Tree.h
```

## Compilación y Ejecución

### Requisitos
- Compilador C++ (g++ recomendado) con soporte C++17.

### Comandos (Windows PowerShell)

1. **Compilar**:
   ```powershell
   g++ -std=c++17 -O2 -Wall -I src src/main.cpp -o bin/sucesion.exe
   ```

2. **Ejecutar**:
   ```powershell
   ./bin/sucesion.exe
   ```

## Reglas de Sucesión Implementadas
1. Hijo primogénito varón vivo (< 70 años).
2. Si no hay hijos, hermano del rey (rama primogénita).
3. Si no hay hermanos, tío del rey.
4. Si no hay varones, mujer más joven (> 15 años).
