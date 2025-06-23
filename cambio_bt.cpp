#include <cassert>
#include <climits>
#include <iostream>
#include <limits>
#include <string>
using namespace std;
int cantMonedas = 6;

int monedas[6] = {1, 2, 5, 10, 12, 500};

bool puedoPodar(int actual, int mejor) { return actual >= mejor; }

bool esSolucion(int resto) { return resto == 0; }

bool esMejorSolucion(int actual, int mejor) { return actual < mejor; }

bool puedoAplicarMovimiento(int resto, int valorMoneda) {
  return resto >= valorMoneda;
}

void aplicarMovimiento(int &resto, int &cantidadMonedasUsadas, int valorMoneda,
                       int *cantPorMonedaActual, int i) {
  resto -= valorMoneda;
  cantidadMonedasUsadas++;
  cantPorMonedaActual[i]++;
}

void deshacerMovimiento(int &resto, int &cantidadMonedasUsadas, int valorMoneda,
                        int *cantPorMonedaActual, int i) {
  resto += valorMoneda;
  cantidadMonedasUsadas--;
  cantPorMonedaActual[i]--;
}

void clonarSolucion(int *origen, int *destino) {
  for (int i = 0; i < cantMonedas; i++) {
    destino[i] = origen[i];
  }
}

void cambio_bt(int resto, int *cantPorMonedaActual, int cantMonedasActual,
               int *&mejorPorMoneda, int &mejorCantMonedas) {
  if (!puedoPodar(cantMonedasActual, mejorCantMonedas)) {
    if (esSolucion(resto) &&
        esMejorSolucion(cantMonedasActual, mejorCantMonedas)) {
      mejorCantMonedas = cantMonedasActual;
      clonarSolucion(cantPorMonedaActual, mejorPorMoneda);
    } else {
      for (int i = cantMonedas - 1; i >= 0; i--) {
        int valorMoneda = monedas[i];
        if (puedoAplicarMovimiento(resto, valorMoneda)) {
          aplicarMovimiento(resto, cantMonedasActual, valorMoneda,
                            cantPorMonedaActual, i);
          cambio_bt(resto, cantPorMonedaActual, cantMonedasActual,
                    mejorPorMoneda, mejorCantMonedas);
          deshacerMovimiento(resto, cantMonedasActual, valorMoneda,
                             cantPorMonedaActual, i);
        }
      }
    }
  }
}

void cambio(int resto) {
  int cantMonedasActual = 0;
  int mejorCantMonedas = INT_MAX;
  int *cantPorMoneda = new int[cantMonedas];
  int *mejorPorMoneda = new int[cantMonedas];
  cambio_bt(resto, cantPorMoneda, cantMonedasActual, mejorPorMoneda,
            mejorCantMonedas);
  if (mejorCantMonedas == INT_MAX) {
    cout << "No puedo dar cambio :(";
  } else {
    cout << "La cantidad necesaria es " << mejorCantMonedas << endl << endl;
    for (int i = 0; i < cantMonedas; i++) {
      if (mejorPorMoneda[i] > 0) {
        cout << "Use " << mejorPorMoneda[i] << " monedas de " << monedas[i]
             << endl;
      }
    }
  }
}

int main() {
  int resto;
  cin >> resto;
  cambio(resto);

  return 0;
}
