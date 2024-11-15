#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Buku{
	protected:
		string judul;
		string pengarang;
		int tahun_terbit;
		string ISBN;
		bool status;
		
	public:
		Buku(string j, string p, int t, string i) : judul(j), pengarang(p), tahun_terbit(t), ISBN(i), status(true){}
		
		string get_judul() const {return judul;}
		string get_pengarang() const {return pengarang;}
		int get_tahun_terbit()const {return tahun_terbit;}
		string get_ISBN() const {return ISBN;}
		bool valid() const {return status;}
		void set_status(bool s) {status = s;}
		
		virtual void info() const {
			cout<<"Judul\t\t: "<<judul<<endl;
			cout<<"Pengarang\t: "<<pengarang<<endl;
			cout<<"Tahun Terbit\t: "<<tahun_terbit<<endl;
			cout<<"ISBN\t\t: "<<ISBN<<endl;
		}
};

class Anggota{
	private:
		string nama;
		string no_anggota;
		string alamat;
		vector<Buku*> buku_pinjaman;
		
	public:
		Anggota(string n, string na, string a) : nama(n), no_anggota(na), alamat(a) {}
		
		string get_no_anggota() const {return no_anggota;}
		string get_nama() const {return nama;}
		
		void pinjam_buku(Buku* buku){
			buku_pinjaman.push_back(buku);
		}
		
		void kembalikan_buku(const string& judul_buku){
			for(size_t i=0; i<buku_pinjaman.size(); ++i){
				if(buku_pinjaman[i]->get_judul() == judul_buku){
					buku_pinjaman[i]->set_status(true);
					buku_pinjaman.erase(buku_pinjaman.begin()+1);
					cout<<"Buku \""<<judul_buku<<"\" BERHASIL Dikembalikan.\n";
					return;
				}
			}
			cout<<"buku \""<<judul_buku<<"\" TIDAK DITEMUKAN dalam daftar pinjaman.\n";
		}
		
		void info_pinjaman() const{
			cout<<"Nama : "<<nama<<", ID : "<<no_anggota<<endl;
			cout<<"Buku yang dipinjam:\n";
			if(buku_pinjaman.empty()){
				cout<<"- Tidak ada buku yang dipinjam\n";
			}else{
				for(size_t i=0; i<buku_pinjaman.size(); ++i){
					cout<<"- "<<buku_pinjaman[i]->get_judul()<<" (ISBN : "<<buku_pinjaman[i]->get_ISBN()<<")\n";
				}
			}
		}
};

class Perpustakaan{
	private:
		vector<Buku*> daftar_buku;
		vector<Anggota> daftar_anggota;
	
	public: 
		void tambah_buku(Buku* buku){
			daftar_buku.push_back(buku);
		}
		
		void tambah_anggota(Anggota anggota){
			daftar_anggota.push_back(anggota);
		}
		
		void daftar_buku_tersedia() const {
			cout<<"Daftar Buku tersedia : \n";
			for(size_t i=0; i<daftar_buku.size(); ++i){
				if(daftar_buku[i]->valid()){
					daftar_buku[i]->info();
					cout<<endl;
				}
			}
		}
		
		void pinjam_buku(const string& no_anggota, const string& judul_buku){
			for(size_t i=0; i<daftar_anggota.size(); ++i){
				if(daftar_anggota[i].get_no_anggota() == no_anggota){
					for(size_t j=0; j<daftar_buku.size(); ++j){
						if(daftar_buku[j]->get_judul() == judul_buku && daftar_buku[j]->valid()){
							daftar_buku[j]->set_status(false);
							daftar_anggota[i].pinjam_buku(daftar_buku[j]);
							cout<<"Buku \""<<judul_buku<<"\" BERHASIL dipinjam oleh "<<daftar_anggota[i].get_nama()<<endl;
							return;
						}
					}
					cout<<"Buku \""<<judul_buku<<"\" TIDAK Tersedia."<<endl;
					return;
				}
			}
			cout<<"Anggota dengan ID \""<<no_anggota<<"\" TIDAK Ditemukan. \n";
		}
		
		void kembalikan_buku(const string& no_anggota, const string& judul_buku){
			for(size_t i=0; i<daftar_anggota.size(); ++i){
				if(daftar_anggota[i].get_no_anggota() == no_anggota){
					daftar_anggota[i].kembalikan_buku(judul_buku);
					return;
				}
			}
			cout<<"Anggota dengan ID \""<<no_anggota<<"\"TIDAK ditemukkan.\n";
		}
		
		void info_anggota() const{
			for(size_t i=0; i<daftar_anggota.size(); ++i){
				daftar_anggota[i].info_pinjaman();
				cout<<endl;
			}
		}
};

void menu(){
	Perpustakaan perpustakaan;	
	perpustakaan.tambah_buku(new Buku("Sejarah Batik", "Khalil", 2022, "123-456-789"));
	perpustakaan.tambah_buku(new Buku("Teknoligi dan Literasi", "Alfin", 2021, "987-654-321"));
	perpustakaan.tambah_buku(new Buku("Antropologi", "Hakim", 2020, "543-120-789"));
	perpustakaan.tambah_anggota(Anggota("Achmad Farhan", "P001", "Medan"));
	perpustakaan.tambah_anggota(Anggota("Nurjaman", "P002", "Brebes"));
	perpustakaan.tambah_anggota(Anggota("Bagas Ilham", "P003", "Semarang"));
	
	int pilihan;
	do{
		cout<<"\n========= Menu Perpustakaan =========\n";
		cout<<"1. Daftar Buku Tersedia\n";
		cout<<"2. Tambah Anggota\n";
		cout<<"3. Pinjam Buku\n";
		cout<<"4. Kembalikan Buku\n";
		cout<<"5. Info Anggota\n";
		cout<<"0. Keluar\n";
		cout<<"Pilihan: ";
		cin>>pilihan;
		
		if(pilihan==1){
			cout<<endl;
			perpustakaan.daftar_buku_tersedia();
		}else if (pilihan==2){
			string nama, no_anggota, alamat;
			cout<<"\nNama\t\t: ";
			cin.ignore();
			getline(cin, nama);
			cout<<"ID anggota\t: ";
			getline(cin, no_anggota);
			cout<<"Alamat\t\t: ";
			getline(cin, alamat);
			perpustakaan.tambah_anggota(Anggota(nama, no_anggota, alamat));
		}else if(pilihan==3){
			string no_anggota, judul_buku;
			cout<<"\nID Anggota\t: ";
			cin>>no_anggota;
			cout<<"Judul Buku\t: ";
			cin.ignore();
			getline(cin, judul_buku);
			perpustakaan.pinjam_buku(no_anggota, judul_buku);
		}else if(pilihan==4){
			string no_anggota, judul_buku;
			cout<<"\nID Anggota\t: ";
			cin>>no_anggota;
			cout<<"Judul Buku\t: ";
			cin.ignore();
			getline(cin, judul_buku);
			perpustakaan.kembalikan_buku(no_anggota, judul_buku);
		}else if(pilihan==5){
			cout<<endl;
			perpustakaan.info_anggota();
		}
	}while (pilihan !=0);
	
	cout<<"Terima Kasih telah menggunakan sistem perpustakaan.\n";
}

int main(){
	menu();
	return 0;
}
