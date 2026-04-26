#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string namaPembeli, listBelanja = "", metodeNama;
    int kategori, pilihanBarang, qty, lanjut, statusMember, metodeBayar;
    double harga = 0, subtotal = 0, totalPajak = 0, diskon = 0, totalAkhir;
    double uangBayar, kembalian;

    cout << "=== E-COMMERCE SMART CHECKOUT ===\n";
    cout << "Nama Pembeli: ";
    getline(cin, namaPembeli);
    cout << "Status (1=Member, 0=Bukan): ";
    cin >> statusMember;

    // --- PERULANGAN BELANJA ---
    bool belanja = true;
    while (belanja) {
        cout << "\n--- PILIH KATEGORI BARANG ---\n";
        cout << "1. Elektronik\n2. Pakaian\n3. Kebutuhan Pokok\nPilih Kategori (1-3): ";
        cin >> kategori;

        if (kategori == 1) {
            cout << "\n[ Sub-Menu Elektronik ]\n1. Setrika Philips (Rp 250.000)\n2. TV LED 32 Inch (Rp 1.800.000)\nPilih: ";
            cin >> pilihanBarang;
            if (pilihanBarang == 1) { harga = 250000; listBelanja += "Setrika Philips   x"; }
            else { harga = 1800000; listBelanja += "TV LED 32 Inch    x"; }
            totalPajak += (harga * 0.10);
        } 
        else if (kategori == 2) {
            cout << "\n[ Sub-Menu Pakaian ]\n1. Kemeja Batik (Rp 120.000)\n2. Jaket Hoodie (Rp 200.000)\nPilih: ";
            cin >> pilihanBarang;
            if (pilihanBarang == 1) { harga = 120000; listBelanja += "Kemeja Batik      x"; }
            else { harga = 200000; listBelanja += "Jaket Hoodie      x"; }
            totalPajak += (harga * 0.05);
        } 
        else {
            cout << "\n[ Sub-Menu Pokok ]\n1. Beras 5kg (Rp 75.000)\n2. Minyak 2L (Rp 30.000)\nPilih: ";
            cin >> pilihanBarang;
            if (pilihanBarang == 1) { harga = 75000; listBelanja += "Beras 5kg         x"; }
            else { harga = 30000; listBelanja += "Minyak 2L         x"; }
            totalPajak += (harga * 0.02);
        }

        cout << "Jumlah Qty: ";
        cin >> qty;
        listBelanja += to_string(qty) + "  Rp " + to_string((int)(harga * qty)) + "\n";
        subtotal += (harga * qty);

        cout << "Belanja lagi? (1=Ya, 0=Selesai): ";
        cin >> lanjut;
        if (lanjut == 0) belanja = false;
    }

    // --- HITUNG DISKON & TOTAL ---
    if (statusMember == 1) diskon = subtotal * 0.05;
    totalAkhir = subtotal + totalPajak - diskon;

    // --- METODE PEMBAYARAN ---
    cout << "\n--- METODE PEMBAYARAN ---\n1. QRIS/TF\n2. Tunai\nPilih: ";
    cin >> metodeBayar;

    if (metodeBayar == 2) {
        metodeNama = "Tunai";
        cout << "Total: Rp " << totalAkhir << "\nBayar: Rp ";
        cin >> uangBayar;
        kembalian = uangBayar - totalAkhir;
    } else {
        metodeNama = "QRIS/TF";
        uangBayar = totalAkhir;
        kembalian = 0;
    }

    // --- OUTPUT KE LAYAR & FILE TXT ---
    ofstream file("struk_belanja.txt");

    // Baris-baris ini akan muncul di file txt dan juga bisa di-copy ke cout
    string garis = "==================================\n";
    string isiStruk = "";
    isiStruk += garis;
    isiStruk += "        TOKO SERBA ADA 2.0        \n";
    isiStruk += garis;
    isiStruk += "Nama Pelanggan : " + namaPembeli + "\n";
    isiStruk += "Metode Bayar   : " + metodeNama + "\n";
    isiStruk += "----------------------------------\n";
    isiStruk += listBelanja;
    isiStruk += "----------------------------------\n";
    isiStruk += "Subtotal       : Rp " + to_string((int)subtotal) + "\n";
    isiStruk += "Pajak          : Rp " + to_string((int)totalPajak) + "\n";
    isiStruk += "Diskon Member  : Rp " + to_string((int)diskon) + "\n";
    isiStruk += "TOTAL AKHIR    : Rp " + to_string((int)totalAkhir) + "\n";
    isiStruk += "BAYAR          : Rp " + to_string((int)uangBayar) + "\n";
    isiStruk += "KEMBALIAN      : Rp " + to_string((int)kembalian) + "\n";
    isiStruk += garis;
    isiStruk += "   Terima Kasih Telah Belanja!    \n";
    isiStruk += garis;

    // Cetak ke layar
    cout << "\n" << isiStruk;

    // Simpan ke file txt
    file << isiStruk;
    file.close();

    cout << "\n[v] Struk berhasil disimpan ke 'struk_belanja.txt'\n";

    return 0;
}