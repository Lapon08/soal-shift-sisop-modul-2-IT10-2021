# soal-shift-sisop-modul-2-IT10-2021
## Anggota Kelompok
- Naufal Aprilian Marsa Mahendra 05311940000007
- Dian Arofati Nur Zamzamy 05311940000011
- Christopher Benedict 05311840000024
# Soal 1
Source Code : [soal1.c](soal1/soal1.c)
### Deskripsi
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. 

Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany.

Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.
### Penyelesaian
## soal 1.a
### Deskripsi
Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg
### Penyelesaian
Untuk membuat program C yang berjalan di background, pertama harus melakukan #include terhadap library yang diperlukan
```
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <string.h>
#include <sys/stat.h>
```

- ```<sys/types.h>``` library tipe data khusus (e.g. pid_t)
- ```<stdio.h>``` library untuk fungsi input-output (e.g. printf(), sprintf())
- ```<stdlib.h>``` library untuk fungsi umum (e.g. exit(), atoi())
- ```<unistd.h> ```library untuk melakukan system call kepada kernel linux(e.g. fork())
- ```<time.h>``` library untuk melakukan manipulasi date dan time (e.g. time(), strftime())
- ```<wait.h>``` Library untuk melakukan wait (e.g. wait())
- ```<sys/stat.h>``` Libaryr untuk melakukan umask untuk mengubah mode file

Setelah itu, kami harus membuat program menjadi daemon.
```
    pid_t pid, sid;
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
```
Pertama, kami akan melakukan fork(). sehingga menghasilkan parent process dengan variable pid berisi PID dari child processnya dan child process dengan variable pid berisi nilai 0. Lalu parent process akan di keluarkan menggunakan fungsi exit() dengan exit statusnya.

```
    umask(0);
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDERR_FILENO);
    close(STDOUT_FILENO);
```
Selanjutnya child process akan membuat session ID (sid) menggunakan fungsi setsid(). Lalu jika gagal, process tersebut akan dikeluarkan. Lalu process akan menutup file descriptor menggunakan fungsi close(). umask digunakan untuk mengatur permission dari suatu file pada saat file itu dibuat. Di sini kita mengatur nilai umask(0) agar kita mendapatkan akses full terhadap file yang dibuat oleh daemon. 

Disini Kita tinggal menggunakan ```mkdir``` menmggunakan execv yaitu folder Musyik, Fylm, Pyoto.
```
        child_id = fork();
        if (child_id == 0) {
        char *argv[] = {"mkdir", "Musyik","Fylm","Pyoto",NULL};
            execv("/bin/mkdir",argv);
        }
        while(wait(NULL) != child_id);
```
## soal 1.b
### Deskripsi
untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).
### Penyelesaian
Menggunakan fork() untuk menciptakan child baru. Child akan menjalankan execv(). Disini tinggal mendownload seluruh filenya menggunakan wget dengan beberapa parameter yaitu:

```--no-check-certificate```

```-O``` untuk outputya

```-a``` untuk menyimpan lognya supaya mengetahui proses berhasil atau tidak

```
        child_id = fork();

        if (child_id == 0) {
            
        char *argv2[] = {"wget", "--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","-O", "MUSIK.zip","-a","log",NULL};
        execv("/usr/bin/wget",argv2);
        }
        while(wait(NULL) != child_id);

        child_id = fork();

        if (child_id == 0) {
            
        char *argv3[] = {"wget", "--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","-O","FILM.zip","-a","log",NULL};
        execv("/usr/bin/wget",argv3);
        }
        while(wait(NULL) != child_id);

        child_id = fork();

        if (child_id == 0) {
            
        char *argv4[] = {"wget","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","-O", "FOTO.zip","-a","log",NULL};
        execv("/usr/bin/wget",argv4);
        }
        
        while(wait(NULL) != child_id);
```
```while(wait(NULL) != child_id);``` Script tersebut dimaksudkan untuk menunggu proses child selesai terlebih dahulu lalu melanjutkan ke proses selanjutnya.

## soal 1.c
### Deskripsi
Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta
### Penyelesaian
Menggunakan fork() untuk menciptakan child baru. Child akan menjalankan execv(). Tinggal menggunakan perintah ```unzip``` pada execv nya. lalu tanda ```*``` menandakan semua file zip yang berada di direktori tersebut di unzip

```
        child_id = fork();

        if (child_id == 0) {
            char *argv5[] = {"/bin/unzip","*",NULL};
            execv("/bin/unzip",argv5);
        }   
        while(wait(NULL) != child_id); 
```
```while(wait(NULL) != child_id);``` Script tersebut dimaksudkan untuk menunggu proses child selesai terlebih dahulu lalu melanjutkan ke proses selanjutnya.
## soal 1.d
### Deskripsi
memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan)
### Penyelesaian
Menggunakan fork() untuk menciptakan child baru. Child akan menjalankan execv(). Disini kami menggunakan ```find``` dikolaborasikan dengan mv. Find tersebut digunakan untuk mencari file apa saja yang terdapat pada direktori terkait. Ouput dari find akan dilakukan ```mv``` ke folder yang diinginkan. Untuk find menggunakan beberapa argumen yaitu
- ```-type f``` Argumen tersebut digunakan untuk mencari file saja bukan direktori
- ```-name *``` Arguman tersebut digunakan untuk 
```
        child_id = fork();

        if (child_id == 0) {
                char *argv8[] = {"find","FOTO","-type","f","-name","*","-exec","mv","-t","Pyoto/","{}","+",NULL};
                execv("/bin/find",argv8);
        }

        while(wait(NULL) != child_id);
        child_id = fork();

        if (child_id == 0) {
                char *argv9[] = {"find","MUSIK","-type","f","-name","*","-exec","mv","-t","Musyik/","{}","+",NULL};
                execv("/bin/find",argv9);
        }  
        while(wait(NULL) != child_id);

        child_id = fork();

        if (child_id == 0) {
                char *argv10[] = {"find","FILM","-type","f","-name","*","-exec","mv","-t","Fylm/","{}","+",NULL};
                execv("/bin/find",argv10);
        }
        while(wait(NULL) != child_id);
```

## soal 1.e
### Deskripsi
Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany).
## soal 1.f
### Deskripsi
Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).
### Penyelesaian
# Soal 2
Source Code : [soal2.c](soal2/soal2.c)
### Deskripsi
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.
## soal 2.a
### Deskripsi
Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
### Penyelesaian
## soal 2.b
### Deskripsi
Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.
### Penyelesaian
## soal 2.c
### Deskripsi
Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”. 
### Penyelesaian
## soal 2.d
### Deskripsi
Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.
### Penyelesaian
## soal 2.e
### Deskripsi
Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.
```
nama : joni
umur  : 3 tahun

nama : miko
umur  : 2 tahun

```
### Penyelesaian

# Soal 3
Source Code : [soal3.c](soal3/soal3.c)
### Deskripsi
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.

## soal 3.a
### Deskripsi
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].
### Penyelesaian
## soal 3.b
### Deskripsi
Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.
### Penyelesaian
## soal 3.c
### Deskripsi
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.
### Penyelesaian
## soal 3.d
### Deskripsi
Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.
### Penyelesaian
## soal 3.e
### Deskripsi
Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).
### Penyelesaian
