#include <cassert>
#include <climits>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int cantObjetos = 4;
string nombres[4] = {"ruby", "lingote", "moneda", "diamante"};
int valores[4] = {10, 7, 5, 20};
int pesos[4] = {5, 6, 2, 3};

bool puedoPodar() {
  return false; // claro que no esto es una optimizacion hacia arriba
}
bool esSolucion(int objIndex) {
  return objIndex == cantObjetos; // termine de evaluar todos los objetos
}
bool esMejorSolucion(int actual, int mejor) { return actual > mejor; }
void clonarSolucion(bool *origen, bool *destino) {
  for (int i = 0; i < cantObjetos; i++) {
    destino[i] = origen[i];
  }
}
bool puedoUsarObjeto(int capacidad, int objIndex) {
  return capacidad >= pesos[objIndex];
}
void aplicarMovimiento(int &capacidad, bool *&objetosUsados, int &valorMochila,
                       int objIndex) {
  capacidad -= pesos[objIndex];
  objetosUsados[objIndex] = true;
  valorMochila += valores[objIndex];
}
void deshacerMovimiento(int &capacidad, bool *&objetosUsados, int &valorMochila,
                        int objIndex) {
  capacidad += pesos[objIndex];
  objetosUsados[objIndex] = false;
  valorMochila -= valores[objIndex];
}

void mochila_bt(int capacidad, int objIndex, bool *objetosUsados,
                int valorActualMochila, bool *&mejorObjetosUsados,
                int &mejorValorMochila) {
  if (!puedoPodar()) {
    if (esSolucion(objIndex)) {
      if (esMejorSolucion(valorActualMochila, mejorValorMochila)) {
        mejorValorMochila = valorActualMochila;
        clonarSolucion(objetosUsados, mejorObjetosUsados);
      }
    } else {
      for (int uso = 0; uso <= 1; uso++) {
        if (uso) {
          if (puedoUsarObjeto(capacidad, objIndex)) {
            aplicarMovimiento(capacidad, objetosUsados, valorActualMochila,
                              objIndex);
            mochila_bt(capacidad, objIndex + 1, objetosUsados,
                       valorActualMochila, mejorObjetosUsados,
                       mejorValorMochila);
            deshacerMovimiento(capacidad, objetosUsados, valorActualMochila,
                               objIndex);
          }
        } else {
          mochila_bt(capacidad, objIndex + 1, objetosUsados, valorActualMochila,
                     mejorObjetosUsados, mejorValorMochila);
        }
      }
    }
  }
}

void mochila_01(int capacidad) {
  bool *usados = new bool[cantObjetos]();
  bool *mejorUsados = new bool[cantObjetos]();
  int mejorValorMochila = -1;
  mochila_bt(capacidad, 0, usados, 0, mejorUsados, mejorValorMochila);
  cout << mejorValorMochila << endl;
}

int main() {
  mochila_01(13);
  return 0;
}
