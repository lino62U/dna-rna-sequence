#!/bin/bash
set -e

function run_all() {
  echo "🔄 Limpiando el directorio build..."
  rm -rf build
  mkdir build
  cd build

  echo "⚙️ Configurando el proyecto con CMake..."
  cmake ..

  echo "🧱 Compilando..."
  cmake --build .

  echo "🚀 Ejecutando los tests..."
  ./test_runner
}

function run_tests_only() {
  echo "🚀 Ejecutando solo los tests..."
  cd build
  ./test_runner
  cd ..
}

function build_main_only() {
  echo "🧱 Compilando solo el main..."
  mkdir -p build
  cd build
  cmake ..
  cmake --build . --target sequence_lib
  cd ..
}

case "$1" in
  all|"")
    run_all
    ;;
  test)
    run_tests_only
    ;;
  main)
    build_main_only
    ;;
  *)
    echo "Uso: $0 {all|test|main}"
    exit 1
    ;;
esac
