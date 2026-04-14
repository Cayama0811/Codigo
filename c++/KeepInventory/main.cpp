//El programa le permitira al usuario ingresar sus ventas, 
//calcular el profit y mostrarle su balance actual.

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#pragma comment(lib, "user32.lib")

using namespace std;

int exchangeRate;

struct Sale {
    int id;
    int profit;
    int investment;
    string saleString;
};

struct Product {
    int id;
    string name;
    int profit;
    int stock;
    int investment;
};

Sale sale;
Product product;

void AppStart();
int SelectOption();
void AddSales();
int LoadLastID();
void WantToContinue();
void AddProducts();
//void ViewInfo();
void UpdateExchangeRate();
int LoadExchangeRate();
int LoadLastProductID();
void ViewProducts();

int main() {
    sale.id = LoadLastID(); 
    exchangeRate = LoadExchangeRate(); 
    product.id = LoadLastProductID();
    AppStart();
    return 0;
}

void AppStart()
{
    cout << "Bienvenido a la aplicacion de ventas!" << endl;
    cout << "Que deseas ver?" << endl;
    cout << "1. Ingresar ventas" << endl;
    cout << "2. Ver datos" << endl;
    cout << "3. Ver logs" << endl;
    cout << "4. Ver productos" << endl;
    cout << "5. Agregar productos" << endl;
    cout << "6. Actualizar tasa de cambio" << endl;
    cout << "7. Salir" << endl;
    cout << "Seleccione una opcion: " << endl;

    if (exchangeRate == 0) {
        cout << "No se ha establecido una tasa de cambio. Por favor, ingrese la tasa de cambio actual, use 6 para actualizarla." << endl;
    }
    SelectOption();
}

int SelectOption()
{
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
        AddSales();
        break;
    case 2:
        cout << "Ver datos" << endl;
        break;
    case 3:
        cout << "Ver logs" << endl;
        break;
    case 4:
        ViewProducts();
        break;
    case 5:
        AddProducts();
        break;
    case 6:
        UpdateExchangeRate();
        break;
    case 7:
        cout << "Gracias por usar la aplicacion!" << endl;
        Sleep(2000);
        break;
    default:
        cout << "Opcion no valida, saliendo de la aplicacion." << endl;
        Sleep(2000);
        break;
    }
    return 0;
}

void AddSales()
{
    if (exchangeRate == 0) {
        MessageBoxA(NULL, "No se ha establecido una tasa de cambio. Por favor, ingrese la tasa de cambio actual.", "ALERTA", MB_OK | MB_ICONWARNING);
        WantToContinue();
        return;
    }

    ofstream salesFile("sales.txt", ios::app);
    cout << "Ingrese cuanto dinero gano y cuanto gasto: " << endl;
    cin >> sale.profit >> sale.investment;
    sale.id++;

    salesFile << sale.id << ". " << "Profit: " << sale.profit << " Investment: " << sale.investment << endl;
    sale.saleString = to_string(sale.id) + ". Profit: " + to_string(sale.profit) + " Investment: " + to_string(sale.investment);
    cout << sale.saleString << endl;

    if (salesFile.is_open()) 
    {
        salesFile.close();
    } 
    else 
    {
        cout << "No se pudo abrir el archivo para escribir." << endl;
    }
    WantToContinue();
}

void AddProducts()
{
    cout << "Ingrese el nombre del producto: " << endl;
    getline(cin >> ws, product.name);
    cout << "Ingrese el profit del producto: " << endl;
    cin >> product.profit;
    cout << "Ingrese la inversion del producto: " << endl;
    cin >> product.investment;
    cout << "Ingrese el stock del producto: " << endl;
    cin >> product.stock;

    ofstream productsFile("products.txt", ios::app);
    product.id++;
    productsFile << product.id << ". " << "Name: " << product.name << " Profit: " << product.profit << " Investment: " << product.investment << " Stock: " << product.stock << endl;
    productsFile.close();
    WantToContinue();
}

void WantToContinue()
{
    char option;
    cout << "Desea continuar? (Y/N): " << endl;
    cin >> option;

    if (option == 'Y' || option == 'y') {
        system("cls");
        AppStart();
    }
     else if (option == 'N' || option == 'n') {
        cout << "Gracias por usar la aplicacion!" << endl;
        Sleep(2000);
    } 
    else {
        cout << "Opcion no valida, regresando al menu principal." << endl;
        Sleep(2000);
        system("cls");
        AppStart();
    }
}

int LoadLastID() {
    ifstream fileRead("sales.txt");
    string line;
    int count = 0;
    
    if (fileRead.is_open()) {
        while (getline(fileRead, line)) {
            if (!line.empty()) count++; // Cuenta cada línea no vacía como una venta
        }
        fileRead.close();
    }
    return count;
}

int LoadLastProductID() {
    ifstream fileRead("products.txt");
    string line;
    int count = 0;
    
    if (fileRead.is_open()) {
        while (getline(fileRead, line)) {
            if (!line.empty()) count++; // Cuenta cada línea no vacía como un producto
        }
        fileRead.close();
    }
    return count;
}

int LoadExchangeRate() {
    ifstream fileRead("exchange_rate.txt");
    int rate = 0;
    if (fileRead.is_open()) {
        fileRead >> rate;
        fileRead.close();
    }
    return rate;
}

void UpdateExchangeRate() {
    cout << "Ingresa aqui la tasa de cambio actual:" << endl;
    cin >> exchangeRate;

    ofstream file("exchange_rate.txt", ios::trunc); 
    
    if (file.is_open()) {
        file << exchangeRate;
        file.close();
        cout << "Tasa de cambio actualizada con exito." << endl;
    } 
    else {
        cout << "Error: No se pudo actualizar el archivo." << endl;
    }


    WantToContinue();
}

void ViewProducts() {
    ifstream fileRead("products.txt");
    string line;
    
    if (fileRead.is_open()) {
        while (getline(fileRead, line)) {
            cout << line << endl;
        }
        fileRead.close();
    } else {
        cout << "No se pudo abrir el archivo para leer." << endl;
    }
    WantToContinue();
}
