# MoraSat projekt rádió mikrovezérlő

Tervezett funkciók:
- 1-wire USART-on fogadott adatokat kiküldi GFSK modulációval és hibajavítással (32 bájtból 18 bájt adat)
- Hasonlóan a fogadott adatokat továbbítja feldolgozásra
- Hierarchikus moduláció: ha a csomagok jele túl gyenge az értelmezéshez, akkor a csomagok kezdete közt eltelt idő vagy a csomagok hordozó frekvenciája közötti eltérések extra információt kódolnak
  - Alapesetben annyit, hogy "MORA", de pl. alacsony akkumulátorszint mellett az ahhoz tartozó figyelmeztetést
  
