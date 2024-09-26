#include <iostream>
#include <vector>
#include <string>
using namespace std;

int M, N, P; // M itu baris, N kolom, jumlah perintah gerakan P
vector<string> peta; //Vektor yang digunakan untuk menyimpan peta dalan grid
string arah; //Menyimpan urutan arah gerakan yang akan diikuti robot
int waktu = 0; //Menympan waktu yang diperlukan robot untuk menyelesaikan perjalanan
bool bisaLewatDinding = false;  // Robot bisa melewati dinding setelah bertemu mekanik
bool cepat = false;  // Robot bergerak lebih cepat setelah bertemu dengan Electrical
bool ketemuOfficial = false;  // Menyimpan status jika robot bertemu Official

// Fungsi untuk mengecek batas map (Fungsi ini memeriksa 
//apakah koordinat (x, y) berada di dalam batas peta. Jika berada dalam batas, 
//fungsi mengembalikan true; jika tidak, mengembalikan false.)
bool cekBatas(int x, int y) {
    return (x >= 0 && x < M && y >= 0 && y < N);
}

int main() {
    cin >> M >> N;
    peta.resize(M);
    
    for (int i = 0; i < M; ++i) {
        cin.ignore();
        getline(cin, peta[i]);
    }
    
    cin >> P;
    for (int i = 0; i < P; ++i) {
        char temp;
        cin >> temp;
        arah.push_back(temp);
    }
    
    // Mencari posisi awal robot 'S'
    int x = -1, y = -1;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; j++) {
            if (peta[i][j] == 'S') {
                x = i;
                y = j;
                break;
            }
        }
        if (x != -1) break;
    }

    if (x == -1 || y == -1) {
        cout << "Posisi awal robot tidak ditemukan" << endl;
        return 1;
    }
    
    bool berhasil = false;
    // Loop pergerakan robot
    for (int i = 0; i < arah.size(); ++i) {
        char gerak = arah[i];
        
        // Menentukan waktu berdasarkan kecepatan
        if (cepat) {
            waktu += 1;  // Kecepatan naik, 1 menit per langkah
        } else {
            waktu += 2;  // Normal, 2 menit per langkah
        }

        int nx = x, ny = y;
        
        // Menentukan arah gerakan
        if (gerak == 'U') nx--;
        if (gerak == 'D') nx++;
        if (gerak == 'L') ny--;
        if (gerak == 'R') ny++;
        
        // Mengecek apakah robot berada di dalam peta
        if (!cekBatas(nx, ny)) {
            cout << "Robot nabrak, silahkan diperbaiki" << endl;
            cout << "Robot gagal dalam mencapai tujuan :(" << endl;
            cout << "Robot telah berjalan selama " << waktu << " menit" << endl;
            return 0;
        }

        // Mengecek simbol pada posisi yang akan ditempati
        char target = peta[nx][ny];
        
        switch (target) {
            case '.':
                // Jalan kosong, bisa dilewati
                x = nx;
                y = ny;
                break;
            case 'x':
                // Dinding, bisa dilewati jika robot sudah bertemu dengan mekanik
                if (bisaLewatDinding) {
                    x = nx;
                    y = ny;
                } else {
                    cout << "Robot nabrak, silahkan diperbaiki" << endl;
                    cout << "Robot gagal dalam mencapai tujuan :(" << endl;
                    cout << "Robot telah berjalan selama " << waktu << " menit" << endl;
                    return 0;
                }
                break;
            case 'F':
                // Tujuan tercapai
                cout << "Robot berhasil mencapai tujuan" << endl;
                if (ketemuOfficial) {
                    waktu *= 2;  // Menggandakan waktu perjalanan jika bertemu Official
                }
                cout << "Robot telah berjalan selama " << waktu << " menit" << endl;
                berhasil = true;
                return 0;
            case 'M':
                // Mechanic, bisa lewat dinding
                cout << "Bertemu dengan mekanik, siap membasmi rintangan" << endl;
                bisaLewatDinding = true;
                x = nx;
                y = ny;
                break;
            case 'E':
                // Electrical, robot 2x lebih cepat
                cout << "Bertemu dengan electrical, kecepatan roda naik menjadi 200%" << endl;
                cepat = true;
                x = nx;
                y = ny;
                break;
            case 'P':
                // Programming, output bebas
                cout << "Hi Programmer" << endl;
                x = nx;
                y = ny;
                break;
            case 'O':
                // Official, waktu perjalanan dikali 2
                cout << "Bertemu dengan official, diajak ngonten bareng" << endl;
                ketemuOfficial = true;
                x = nx;
                y = ny;
                break;
        }
    }

    if (!berhasil) {
        cout << "Robot gagal dalam mencapai tujuan :(" << endl;
        cout << "Robot telah berjalan selama " << waktu << " menit" << endl;
    }

    return 0;
}

