# depo4


Gömülü Sistemler İçin Dinamik Tensör Yönetimi ve Quantization Projesi
1. Proje Özeti ve Mühendislik Yaklaşımı
Bu çalışma, kaynakları kısıtlı mikrodenetleyici birimleri (MCU) üzerinde yapay zeka modellerinin çalıştırılabilmesi için gerekli olan bellek optimizasyon tekniklerini temel almaktadır. Proje kapsamında, bir gömülü sistem mühendisi perspektifiyle, standart 32-bit kayan noktalı sayıların (float) yarattığı bellek yükünü minimize eden dinamik bir veri yapısı tasarlanmıştır. Bu yapı, çalışma zamanında farklı veri hassasiyetleri arasında geçiş yapabilme kabiliyetine sahiptir.

2. Problem Tanımı: Bellek Kısıtları
Yapay zeka modelleri, doğaları gereği milyonlarca parametreden oluşan tensörler barındırır. ESP32 veya Arduino gibi cihazlarda RAM kapasitesi kilobyte seviyeleriyle ölçüldüğü için, her bir parametreyi 4 byte yer kaplayan float formatında saklamak fiziksel olarak imkansızdır. Bu durum, modelin ya hiç yüklenememesine ya da çalışma sırasında bellek taşmasına (stack/heap overflow) neden olur. Çözüm olarak, verinin hassasiyetini düşüren ancak anlamsal bütünlüğünü koruyan "Quantization" (Nicemleme) ve bellek paylaşımlı "Union" yapıları kullanılmıştır.

3. Teknik Mimari ve Veri Yapısı Tasarımı
Projenin temelini oluşturan Tensör yapısı, C dilinin en ilkel (primitive) imkanları kullanılarak inşa edilmiştir.

Union Yapısının Rolü
Tasarımda kullanılan union yapısı, farklı veri tiplerinin (Float32, Int8) aynı fiziksel bellek adresini paylaşmasını sağlar. Bu yöntem, bir veri tipi dönüştürüldüğünde sistemin yeni bir bellek alanı ayırmasına gerek bırakmaz. Böylece hem işlemci döngülerinden tasarruf edilir hem de parçalanmış bellek (memory fragmentation) sorununun önüne geçilir.

Dinamik Tip Yönetimi
Sistem, bir "Enum" etiketi aracılığıyla tensörün o an hangi veri tipinde olduğunu takip eder. Bu, tip güvenliğini (type safety) sağlar ve çalışma sırasında yanlış veri türüne erişilmesini engeller.

4. Quantization (Nicemleme) Metodolojisi
Quantization süreci, 32-bitlik geniş veri aralığını, bilgi kaybını minimize ederek 8-bitlik dar bir aralığa (-128 ile 127 arası) sıkıştırma işlemidir.

Lineer Dönüşüm: Her bir veri hücresi, belirlenen bir ölçekleme faktörü (scale) ve sıfır noktası kayması (zero-point) kullanılarak normalize edilir.

Verimlilik Kazanımı: Bu dönüşüm sonucunda bellek kullanımı %75 oranında azalmaktadır. Bu kazanım, TinyML uygulamalarının gerçek zamanlı çalışabilmesi için kritik bir eşiktir.

5. Agentic Kodlama ve Geliştirme Süreci
Proje, modern yazılım geliştirme metodolojilerinden biri olan "Agentic Kodlama" yaklaşımı ile yürütülmüştür. Bu süreçte Gemini 2.0 Flash modeli, sadece bir kod üretici değil, tasarım kararlarını sorgulayan bir mühendislik ortağı olarak konumlandırılmıştır.

İteratif Optimizasyon: Geliştirme sırasında karşılaşılan "ASCII olmayan karakter yolları" ve "bellek sızıntısı" gibi hatalar, yapay zeka ajanı ile birlikte analiz edilerek sistem standartlarına uygun hale getirilmiştir.

Hata Ayıklama (Debugging): CLion arayüzü üzerinden GDB debugger kullanılarak, bellek adreslerinin doğruluğu ve matris verilerinin dönüşüm sonrası bütünlüğü canlı olarak test edilmiştir.

6. Sonuç ve Değerlendirme
Tasarlanan bu Tensör yapısı, yüksek seviyeli programlama dillerindeki karmaşık yapıların C dilindeki en temel ve performanslı halidir. Proje sonucunda, düşük maliyetli mikrodenetleyicilerde bile yapay zeka çıkarımı yapılabileceği, doğru veri yapısı ve matematiksel optimizasyonlar ile kanıtlanmıştır.
