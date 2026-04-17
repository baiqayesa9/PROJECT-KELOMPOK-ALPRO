// =================================================
// E-Commerce Smart Checkout System v2.0
// Fitur: Katalog Barang, Keranjang Belanja,
//        Poin Reward, Garansi, Riwayat Transaksi
// =================================================
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace std;

// ---- Struct: Barang di Katalog ----
struct Barang {
    int    id;
    string nama;
    double harga;
    int    stok;
    int    kategori;   // 1=Elektronik 2=Pakaian 3=Pokok
    int    garansi;    // bulan (0=tidak ada)
};

// ---- Struct: Item di Keranjang ----
struct ItemKeranjang {
    Barang barang;
    int    qty;
};

// ---- Katalog Global ----
Barang katalog[] = {
    // id  nama                  harga      stok  kat  garansi
    { 1,  "Setrika Philips",      250000,   10,   1,   12  },
    { 2,  "Kulkas Sharp 2 Pintu", 3500000,  5,    1,   24  },
    { 3,  "Mesin Cuci Samsung",   2800000,  4,    1,   24  },
    { 4,  "TV LED 32\" Polytron",  1800000,  7,    1,   12  },
    { 5,  "Kipas Angin Cosmos",   185000,   15,   1,   6   },
    { 6,  "Kemeja Batik Pria",    120000,   20,   2,   0   },
    { 7,  "Celana Jeans Wrangler",350000,   12,   2,   0   },
    { 8,  "Dress Casual Wanita",  175000,   18,   2,   0   },
    { 9,  "Jaket Hoodie Polos",   220000,   25,   2,   0   },
    { 10, "Beras Premium 5kg",    75000,    50,   3,   0   },
    { 11, "Minyak Goreng 2L",     28000,    100,  3,   0   },
    { 12, "Gula Pasir 1kg",       15000,    80,   3,   0   },
    { 13, "Sabun Mandi Lifebuoy", 8500,     200,  3,   0   },
    { 14, "Deterjen Rinso 1kg",   22000,    60,   3,   0   },
};
const int TOTAL_BARANG = 14;

// ---- Konstanta ----
const string KODE_PROMO[]    = { "HEMATBAHAGIA", "DISKON50RB", "NEWMEMBER" };
const double NILAI_PROMO[]   = { 20000, 50000, 30000 };
const int    TOTAL_PROMO     = 3;
const double POIN_PER_RUPIAH = 0.001; // 1 poin per Rp1.000

// ---- Fungsi Pajak ----
double getPajak(int k) {
    if (k == 1) return 0.10;
    if (k == 2) return 0.05;
    return 0.02;
}
string namaKat(int k) {
    if (k == 1) return "Elektronik";
    if (k == 2) return "Pakaian";
    return "Kebutuhan Pokok";
}

// ---- Fungsi: Format Rupiah ----
string rupiah(double n) {
    string s = to_string((long long)n);
    int ins = s.length() - 3;
    while (ins > 0) { s.insert(ins, "."); ins -= 3; }
    return "Rp " + s;
}

// ---- Fungsi: Cetak Garis ----
void garis(char c = '=', int n = 44) {
    for (int i = 0; i < n; i++) cout << c;
    cout << "\n";
}

// ---- Fungsi: Tampilkan Katalog ----
void tampilKatalog(int filterKat = 0) {
    garis();
    cout << left << setw(4) << "ID"
         << setw(24) << "Nama Barang"
         << setw(12) << "Harga"
         << setw(6)  << "Stok"
         << "Garansi\n";
    garis('-');
    for (int i = 0; i < TOTAL_BARANG; i++) {
        if (filterKat != 0 && katalog[i].kategori != filterKat) continue;
        string gar = (katalog[i].garansi > 0)
            ? to_string(katalog[i].garansi) + " bln" : "-";
        cout << left  << setw(4)  << katalog[i].id
             << setw(24) << katalog[i].nama
             << setw(12) << rupiah(katalog[i].harga)
             << setw(6)  << katalog[i].stok
             << gar << "\n";
    }
    garis();
}

// ---- Fungsi: Cari Barang by ID ----
int cariBarang(int id) {
    for (int i = 0; i < TOTAL_BARANG; i++)
        if (katalog[i].id == id) return i;
    return -1;
}

// ---- Fungsi: Cek Kode Promo ----
double cekPromo(string kode) {
    for (int i = 0; i < TOTAL_PROMO; i++)
        if (kode == KODE_PROMO[i]) return NILAI_PROMO[i];
    return 0;
}

// ---- Fungsi: Tanggal Sekarang ----
string getTanggal() {
    time_t t = time(0);
    tm* now = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", now);
    return string(buf);
}

// ================================================
//  MAIN
// ================================================
int main() {
    // -- Data Pembeli --
    string nama;
    int    statusMember;
    int    poinAwal = 0;

    garis();
    cout << "    E-COMMERCE SMART CHECKOUT v2.0\n";
    garis();

    cout << "\n[1] DATA PEMBELI\n";
    cout << "Nama              : "; cin.ignore(); getline(cin, nama);
    cout << "Status (1=Member / 2=Bukan): "; cin >> statusMember;
    if (statusMember == 1) {
        cout << "Poin Reward saat ini : "; cin >> poinAwal;
    }

    // -- Pilih Kategori --
    int pilihKat;
    cout << "\n[2] PILIH KATEGORI\n";
    cout << "  1. Elektronik\n  2. Pakaian\n  3. Kebutuhan Pokok\n  0. Semua\n";
    cout << "Filter: "; cin >> pilihKat;

    // -- Tampilkan Katalog --
    cout << "\n[3] KATALOG BARANG\n";
    tampilKatalog(pilihKat);

    // -- Keranjang Belanja --
    vector<ItemKeranjang> keranjang;
    int totalItem = 0;

    cout << "\n[4] TAMBAH KE KERANJANG\n";
    cout << "(Masukkan ID barang dan qty, ketik 0 untuk selesai)\n";

    while (true) {
        int idPilih, qty;
        cout << "ID Barang: "; cin >> idPilih;
        if (idPilih == 0) break;

        int idx = cariBarang(idPilih);
        if (idx == -1) {
            cout << "  [!] ID tidak ditemukan.\n"; continue;
        }
        cout << "Qty      : "; cin >> qty;
        if (qty <= 0 || qty > katalog[idx].stok) {
            cout << "  [!] Stok tidak cukup (stok: "
                 << katalog[idx].stok << ").\n"; continue;
        }
        // Cek jika sudah ada di keranjang
        bool sudahAda = false;
        for (auto& item : keranjang) {
            if (item.barang.id == idPilih) {
                item.qty += qty; sudahAda = true; break;
            }
        }
        if (!sudahAda) keranjang.push_back({ katalog[idx], qty });
        katalog[idx].stok -= qty;
        totalItem += qty;
        cout << "  [v] " << katalog[idx].nama << " x" << qty << " ditambahkan.\n";
    }

    if (keranjang.empty()) {
        cout << "Keranjang kosong. Program selesai.\n";
        return 0;
    }

    // -- Kode Promo --
    string inputPromo;
    cout << "\n[5] KODE PROMO (SKIP jika tidak ada): ";
    cin.ignore(); getline(cin, inputPromo);
    double diskonPromo = cekPromo(inputPromo);
    if (diskonPromo > 0)
        cout << "  [v] Promo valid! Hemat " << rupiah(diskonPromo) << "\n";
    else if (inputPromo != "SKIP" && inputPromo != "")
        cout << "  [!] Kode promo tidak valid.\n";

    // -- Tukar Poin (Member) --
    double diskonPoin = 0;
    if (statusMember == 1 && poinAwal > 0) {
        cout << "\n[6] TUKAR POIN\n";
        cout << "Poin kamu: " << poinAwal
             << " (1 poin = Rp1)\nTukar berapa poin? (0=skip): ";
        int tukarPoin;
        cin >> tukarPoin;
        if (tukarPoin > poinAwal) tukarPoin = poinAwal;
        diskonPoin = tukarPoin;
        poinAwal -= tukarPoin;
        if (diskonPoin > 0)
            cout << "  [v] Diskon poin: " << rupiah(diskonPoin) << "\n";
    }

    // -- Metode Pembayaran --
    int metodeBayar;
    cout << "\n[7] METODE PEMBAYARAN\n";
    cout << "  1. Transfer Bank  (admin Rp 2.500)\n";
    cout << "  2. E-Wallet       (admin Rp 1.000)\n";
    cout << "  3. COD            (admin Rp 5.000)\n";
    cout << "Pilih: "; cin >> metodeBayar;
    string namaMetode;
    double adminBayar;
    if      (metodeBayar == 1) { namaMetode = "Transfer Bank"; adminBayar = 2500; }
    else if (metodeBayar == 2) { namaMetode = "E-Wallet";     adminBayar = 1000; }
    else                       { namaMetode = "COD";           adminBayar = 5000; }

    // ================================================
    //  PERHITUNGAN TOTAL
    // ================================================
    double subtotal = 0, totalPajak = 0;
    for (const auto& item : keranjang) {
        double hargaItem = item.barang.harga * item.qty;
        subtotal   += hargaItem;
        totalPajak += hargaItem * getPajak(item.barang.kategori);
    }
    double diskonMember = (statusMember == 1) ? subtotal * 0.05 : 0;
    double total = subtotal + totalPajak - diskonMember
                 - diskonPromo - diskonPoin + adminBayar;
    if (total < 0) total = 0;

    // -- Hitung Poin Baru --
    int poinDapat = (statusMember == 1) ? (int)(total * POIN_PER_RUPIAH) : 0;
    int poinAkhir = poinAwal + poinDapat;

    // ================================================
    //  CETAK STRUK
    // ================================================
    cout << "\n\n";
    garis();
    cout << "        STRUK DIGITAL BELANJA\n";
    garis();
    cout << "No. Transaksi : TRX-" << (int)(total + totalItem * 137) << "\n";
    cout << "Tanggal       : " << getTanggal() << "\n";
    cout << "Nama          : " << nama << "\n";
    cout << "Status        : "
         << (statusMember==1 ? "Member" : "Bukan Member") << "\n";
    garis('-');
    cout << left << setw(22) << "Barang"
         << setw(5) << "Qty"
         << right << setw(13) << "Subtotal\n";
    garis('-');
    for (const auto& item : keranjang) {
        string gar = (item.barang.garansi > 0)
            ? " [G:"+to_string(item.barang.garansi)+"bln]" : "";
        string label = item.barang.nama + gar;
        if (label.length() > 21) label = label.substr(0,18) + "...";
        cout << left  << setw(22) << label
             << setw(5)  << item.qty
             << right << setw(13)
             << rupiah(item.barang.harga * item.qty) << "\n";
    }
    garis('-');
    cout << right << setw(27) << "Subtotal : " << setw(13) << rupiah(subtotal) << "\n";
    cout << setw(27) << "Pajak    : " << setw(13) << rupiah(totalPajak) << "\n";
    if (diskonMember > 0)
        cout << setw(27) << "Diskon Member: " << setw(13) << "-"+rupiah(diskonMember) << "\n";
    if (diskonPromo > 0)
        cout << setw(27) << "Diskon Promo : " << setw(13) << "-"+rupiah(diskonPromo) << "\n";
    if (diskonPoin > 0)
        cout << setw(27) << "Diskon Poin  : " << setw(13) << "-"+rupiah(diskonPoin) << "\n";
    cout << setw(27) << "Admin (" +namaMetode+"): " << setw(13) << rupiah(adminBayar) << "\n";
    garis();
    cout << right << setw(27) << "TOTAL BAYAR : "
         << setw(13) << rupiah(total) << "\n";
    garis();
    if (statusMember == 1) {
        cout << "Poin didapat  : +" << poinDapat << " poin\n";
        cout << "Total poin    : "  << poinAkhir << " poin\n";
        garis('-');
    }
    cout << "   Terima kasih, " << nama << "! Belanja lagi ya :)\n";
    garis();

    return 0;
}
