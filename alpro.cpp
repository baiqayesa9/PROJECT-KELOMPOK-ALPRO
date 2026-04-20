#include <iostream>
#include <string>

using namespace std;

int main() {
    // VARIABEL
    string namaPembeli, namaBarang;
    int pilihanBarang, qty;
    double harga = 0, subtotal, pajak, diskon = 0, total;
    int statusMember;

    cout << "=== MINI E-COMMERCE SIMPEL ===\n";

    // 1. INPUT DATA PEMBELI (Sequence)
    cout << "Masukkan Nama Anda: ";
    getline(cin, namaPembeli);
    cout << "Apakah Anda Member? (1=Ya, 0=Tidak): ";
    cin >> statusMember;

    // 2. PILIH BARANG (Kondisional)
    cout << "\n--- KATALOG BARANG ---\n";
    cout << "1. Setrika Philips    (Rp 250.000)\n";
    cout << "2. Kemeja Batik       (Rp 120.000)\n";
    cout << "3. Beras Premium 5kg  (Rp 75.000)\n";
    cout << "Pilih ID Barang (1-3): ";
    cin >> pilihanBarang;

    if (pilihanBarang == 1) {
        namaBarang = "Setrika Philips";
        harga = 250000;
    } else if (pilihanBarang == 2) {
        namaBarang = "Kemeja Batik";
        harga = 120000;
    } else if (pilihanBarang == 3) {
        namaBarang = "Beras Premium 5kg";
        harga = 75000;
    } else {
        cout << "Pilihan tidak valid!";
        return 0; // Program berhenti jika salah input
    }

    cout << "Jumlah yang dibeli: ";
    cin >> qty;

    // 3. PERHITUNGAN (Sequence & Kondisional)
    subtotal = harga * qty;

    // Hitung Diskon Member 5% (Kondisional)
    if (statusMember == 1) {
        diskon = 0.05 * subtotal;
    }

    // Hitung Pajak 10% (Sequence)
    pajak = 0.10 * subtotal;

    // Total Akhir
    total = subtotal - diskon + pajak;

    // 4. OUTPUT STRUK (Sequence)
    cout << "\n==============================\n";
    cout << "       STRUK PEMBAYARAN       \n";
    cout << "==============================\n";
    cout << "Nama Pembeli : " << namaPembeli << endl;
    cout << "Barang       : " << namaBarang << endl;
    cout << "Harga Satuan : Rp " << harga << endl;
    cout << "Jumlah       : " << qty << endl;
    cout << "------------------------------\n";
    cout << "Subtotal     : Rp " << subtotal << endl;
    cout << "Diskon Memb. : Rp " << diskon << endl;
    cout << "Pajak (10%)  : Rp " << pajak << endl;
    cout << "------------------------------\n";
    cout << "TOTAL BAYAR  : Rp " << total << endl;
    cout << "==============================\n";
    cout << "Terima kasih sudah belanja!\n";

    return 0;
}