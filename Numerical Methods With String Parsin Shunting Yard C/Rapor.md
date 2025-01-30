<a name="br1"></a> 

05\.2024

**Yıldız Teknik Üniversitesi**

**Elektrik-Elektronik Fakültesi**

**Bilgisayar Mühendisliği Bölümü**

**BLM1022**

**Sayısal Analiz**

**Dönem Projesi**

**İsim: Berke Bünyamin Süle**



**E-posta: bunyamin.sule@std.yildiz.edu.tr**

1



<a name="br2"></a> 

İçindekiler

Ön Bilgi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 3

Ana Menü \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 3

Desteklenen Fonksiyonlar \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 4

Polinom \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 4

Üstel \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 4

Logaritmik \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 4

Trigonometrik\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 4

Ters Trigonometrik \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 4

Matris Girişi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 4

Örnek \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 5

Bisection Yöntemi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 6

Regula-Falsi Yöntemi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 7

Newton-Raphson Yöntemi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 8

NXN lik matrisin tersi\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_9

Gauss Eliminasyon Yöntemi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 10

Gauss-Seidel Yöntemi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 11

Sayısal Türev\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 12

Simpson Yöntemi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 13

Trapez Yöntemi \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_14

Değişken Dönüşümsüz Gregory-Newton Enterpolasyonu \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ 15

Kök cevapları desmos\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_16

2



<a name="br3"></a> 

Ön Bilgi:

Program, 10 tane belirli işlemi yerine getirebilmek için tasarlanmıştır. Bu işlemler sırasıyla

şöyledir:

1\. Bisection yöntemi

2\. Regula-Falsi yöntemi

3\. Newton-Rapshon yöntemi

4\. NxN’lik bir matrisin tersi

5\. Gauss eliminasyon yöntemi

6\. Gauss-Seidel yöntemi

7\. Sayısal Türev

8\. Simpson yöntemi

9\. Trapez yöntemi

10\. Değişken dönüşümsüz Gregory-Newton enterpolasyonu

Yöntem Tablosu:

1

1

2

1

3

1

4

1

5

1

6

1

7

1

8

1

9

1

10

1

Ana Menü:

Çalıştırılmak istenilen işlem program çalıştırıldıktan sonra numarası girilip gereken

parametrelerin verilmesiyle çalışır. Ana menüde ‘0’ girdisi verilene kadar program çalışmaya

devam eder.

3



<a name="br4"></a> 

Desteklenen Fonksiyonlar:

Kök bulma yöntemleri (1, 2, 3), sayısal türev ve integral yöntemleri (7, 8, 9) ve enterpolasyon

yöntemleri (10) için ilk istenilen parametre fonksiyondur. Fonksiyonun içinde polinom, üstel,

logaritmik, trigonometrik ve ters trigonometrik fonksiyonlar bulunabilir. Kullanıcı doğrudan

fonksiyonu girip yöntemi kullanabilir.

Polinom:

2x+5 veya 2\*x+5 olabilir

Üstel:

x^2 veya 2^(x+6) veya x^3^3 gibi olabilir

Logaritmik:

log\_2(5x) şeklinde kullanılabilir burada 2 tabanı (5x) ise üstü .

Trigonometrik:

sin(“ifade”)

cos(“ifade”)

tan(“ifade”)

cot(“ifade”) veya direkt sin5 şeklinde de kullanılabilir.

Ters Trigonometrik:

asin(“ifade”)

acos(“ifade”)

atan(“ifade”)

acot(“ifade”) veya direkt asin20 şeklinde de kullanılabilir.

Matris Girişi:

Matris tersi yönteminde (4) kullanıcıdan nxn’lik matrisin boyutu (n) istenir. Bu değer girildikten

sonra matris elemanları satır satır alınır.

4



<a name="br5"></a> 

Gauss Eliminasyon yönteminde (5) kullanıcıdan nxn’lik matrisin boyutu (n) istenir. Bu değer

girildikten sonra matris elemanları ve karşılık gelen değeri satır satır alınır.Örnek olarak n=3

ise 4x3 lük bir matris kullanıcıdan alınır.

Gauss-Seidal yönteminde (6) kullanıcıdan nxn’lik matrisin boyutu (n) istenir. Bu değer

girildikten sonra matris elemanları kullanıcıdan alınır. Matris elemanları alındıktan sonra

kullanıcıdan AX = B şeklindeki bir matrisin B si alınır. Örnek:

5



<a name="br6"></a> 

Bisection Yöntemi

Parametreler:

Fonksiyon

Start: Başlangıç değeri

End: Bitiş değeri

Epsilon: Hata miktarı

Max iteration: Maksimum iterasyon sayısı

Örnek Kullanım:

6



<a name="br7"></a> 

Regula-Falsi Yöntemi

Parametreler:

Fonksiyon

Start: Başlangıç değeri

End: Bitiş değeri

Epsilon: Hata miktarı

Max iteration: Maksimum iterasyon sayısı

Örnek Kullanım:

7



<a name="br8"></a> 

Newton-Raphson Yöntemi

Parametreler:

Fonksiyon

Seçim: seçim ise başlangıç değeri alınır, seçim 2 ise aralık alınır ve başlangıç değeri olarak

aralığın başlangıcı alınır.

Secim == 1 : start: Başlangıç değeri

Seçim == 2 start: Aralığın başı, End aralığın sonu.

Kabul edilebilir en yüksek hata: Hata miktarı

Max iteration: Maksimum iterasyon sayısı

Örnek Kullanım:

8



<a name="br9"></a> 

NxN’lik Bir Matrisin Tersi

Parametreler:

Matrisin Boyutu

Satır Satır Matrisin Elemanları

Örnek Kullanım:

9



<a name="br10"></a> 

Gauss Eliminasyon Yöntemi

Parametreler:

Matrisin Boyutu

Satır Satır Matrisin Elemanları (Matrisin değerleri dahil)

Örnek Kullanım:

10



<a name="br11"></a> 

Gauss-Seidel Yöntemi

Parametreler:

Matrisin Boyutu

Max iter: Maksimum iterasyon sayısı

Kabul Edilebilir Hata Toleransı: Hata miktar

Başlangıç değeri:ı

Satır Satır Matrisin Elemanları

AX = B şeklindeki matrisin B’si

Örnek Kullanım:

11



<a name="br12"></a> 

Sayısal Türev

Parametreler:

Fonksiyon

X: x değişkeninin değeri

h: h değeri

Seçim: ileri fark için1, geri fark için 2 merkezi fark için 3.

Örnek Kullanım:

12



<a name="br13"></a> 

Simpson Yöntemi

Parametreler:

Fonksiyon

İntegralin Sınırları: start end

Adım sayısı: n

Seçim: Simpson 1/3 için 1 Simpson 3/8 için 2

Örnek Kullanım:

13



<a name="br14"></a> 

Trapez Yöntemi

Parametreler:

Fonksiyon

İntegralin Sınırları: start, end

Adım Sayısı: n

Örnek Kullanım:

14



<a name="br15"></a> 

Değişken dönüşümsüz Gregory-Newton enterpolasyonu

Parametreler:

Eleman Sayısı:

Noktalar: x değerleri

Noktalara Karşılık Gelen Değerler: f(x) değerleri

Hangi Değeri Bulmak İstiyorsunuz: Bulunmak istenen f(x) in x değeri

15



<a name="br16"></a> 

16

