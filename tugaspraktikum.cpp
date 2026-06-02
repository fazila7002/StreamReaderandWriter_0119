#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <exception>
using namespace std;


class TokoElektronik {
private:
    array<string, 3> etalase; // enkapsulasi

public:
  
    TokoElektronik() {
        etalase = {"Laptop", "Smartphone", "Headset"};
    }

    // ambil produk
    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (out_of_range &) {
            throw string("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};


void tampilkanData() {
    ifstream file("gudang.txt");
    string baris;

    cout << "\n=== Data Gudang ===\n";
    while (getline(file, baris)) {
        cout << baris << endl;
    }
    file.close();
}


void tambahData() {
    ofstream file("gudang.txt", ios::app);
    string data;

    cout << "Masukkan nama barang: ";
    cin.ignore();
    getline(cin, data);

    file << data << endl;
    file.close();

    cout << "Data berhasil ditambahkan\n";
}


void updateData() {
    ifstream file("gudang.txt");
    vector<string> data;
    string baris;

    while (getline(file, baris)) {
        data.push_back(baris);
    }
    file.close();

    int index;
    cout << "Pilih index yang mau diubah: ";
    cin >> index;

    if (index >= 0 && index < data.size()) {
        cout << "Data baru: ";
        cin.ignore();
        getline(cin, data[index]);

        ofstream out("gudang.txt");
        for (string d : data) {
            out << d << endl;
        }
        out.close();

        cout << "Data berhasil diupdate\n";
    } else {
        cout << "Index tidak valid\n";
    }
}
void hapusData() {
    ifstream file("gudang.txt");
    vector<string> data;
    string baris;

    while (getline(file, baris)) {
        data.push_back(baris);
    }
    file.close();

    int index;
    cout << "Pilih index yang mau dihapus: ";
    cin >> index;

    if (index >= 0 && index < data.size()) {
        data.erase(data.begin() + index);

        ofstream out("gudang.txt");
        for (string d : data) {
            out << d << endl;
        }
        out.close();

        cout << "Data berhasil dihapus\n";
    } else {
        cout << "Index tidak valid\n";
    }
}


int main() {
    TokoElektronik toko;
    int pilihan;

    do {
        cout << "\n=== MENU TOKO GIBRAN JAYA ===\n";
        tampilkanData();

        cout << "\n1. Tambah Barang\n";
        cout << "2. Update Barang\n";
        cout << "3. Hapus Barang\n";
        cout << "4. Simulasi Etalase\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahData();
            break;
        case 2:
            updateData();
            break;
        case 3:
            hapusData();
            break;

        case 4:
            cout << "\n=== Simulasi Etalase ===\n";
            try {
                cout << "Ambil rak 1: " << toko.ambilProduk(1) << endl;
                cout << "Ambil rak 5: " << toko.ambilProduk(5) << endl;
            }
            catch (string err) {
                cout << err << endl;
            }
            break;

        case 0:
            cout << "Keluar...\n";
            break;

        default:
            cout << "Pilihan tidak valid\n";
        }

    } while (pilihan != 0);

    return 0;
}