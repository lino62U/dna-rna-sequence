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
  cd ..
}

function run_tests_only() {
  echo "🚀 Ejecutando solo los tests con test_runner..."
  cd build
  ./test_runner
  cd ..
}

function run_tests_ctest_only() {
  echo "🚀 Ejecutando solo los tests con ctest en modo verbose..."
  cd build
  ctest --verbose
  cd ..
}

function run_main_only() {
  if [ -z "$2" ]; then
    echo "⚠️  Debes proporcionar el nombre de un archivo FASTA en el directorio data."
    echo "Uso: $0 main <archivo_fasta.txt>"
    exit 1
  fi

  input_file="data/$2"

  if [ ! -f "$input_file" ]; then
    echo "❌ El archivo '$input_file' no existe."
    exit 1
  fi

  echo "🧱 Ejecutando el main con el archivo: $input_file"
  cd build
  ./main_app "../$input_file"
  cd ..
}

case "$1" in
  all|"")
    run_all
    ;;
  test)
    run_tests_only
    ;;
  ctest)
    run_tests_ctest_only
    ;;  
  main)
    run_main_only "$@"
    ;;
  *)
    echo "Uso: $0 {all|test|ctest|main <archivo_fasta.txt>}"
    exit 1
    ;;
esac
