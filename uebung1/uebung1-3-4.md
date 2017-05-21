# 3.a.

Die Anwendungsschicht im TCP/IP-Modell standardisiert die Kommunikation zwischen Rechnern in einem IP-Netzwerk.

Sie bietet zum Beispiel das DNS-Protokoll (Domain Name System), das SMTP-Protokoll (Simple Mail Transfer Protocol) und das HTTP-Protokoll (Hypertext Transfer Protocol) als Dienste an.


# 3.b.

Im TCP/IP-Modell werden die Sicherungs- und Bitübertragungsschicht in eine Netzzugangsschicht zusammengefasst. Die Anwendungs-, Darstellungs- und Sitzungsschicht wird im TCP/IP-Modell nur als Anwendungsschicht zusammengefasst.


# 4.a.

Videodauer = 10 min 25 s = 625 s  
Frames pro Sekunde = 24  
Frames = 625 * 24 = 15000  
Pixel = 1920 * 1080 = 2073600  
Videogröße = Frames * Pixel * 3 Byte = 93312000000 B = 746496000000 b
           = 746496 Mbit


# 4.b.

Entfernung = 7500 km = 7500000 m  
Ausbreitungsgeschwindigkeit = 1,5 * 10^6 m/s

t<sub>lat</sub> = Entfernung / Ausbreitungsgeschwindigkeit = 5 s  
t<sub>trans</sub> = Videogröße / Upload-Geschwindigkeit
                  = 746496 Mbit / 12 Mbit/s = 62208 s

# 4.c.

Lokale Renderingdauer = Frames * 5 s = 75000 s

Online Renderingdauer = Frames * (1 / 20) s = 750 s

Videogröße nach Rendering = Originalgröße * 75 % = 559872 Mbit

t<sub>trans</sub> für Download = Videogröße nach Rendering / Download-Geschwindigkeit
                               = 559872 Mbit / 81 Mbit/s = 6912 s

Upload-Dauer = t<sub>trans</sub> für Upload + t<sub>lat</sub>
             = 62208 s + 5 s = 62213 s
Download-Dauer = t<sub>trans</sub> für Download + t<sub>lat</sub>
               = 6912 s + 5 s = 6917 s

Dauer gesamt = Upload-Dauer + Rendering-Dauer + Download-Dauer
             = 62213 s + 750 s + 6917 s = 69880 s

69880 s < 75000 s, also lohnt es sich in dieser Situation.


# 4.d.

Annahme: Server braucht keine Bestätigungsbits, wenn er das Video wieder zu Heiner „uploadet“.

Paketanzahl für Upload = Videogröße / 100 MByte = 933,12 Pakete = 934 Pakete

Upload-Dauer mit 1-Bit-Bestätigung = t<sub>trans</sub> + t<sub>lat</sub> + Paketanzahl * t<sub>lat</sub>
= 62208 s + 5s + 934 * 5s = 66883 s

Dauer gesamt = Upload-Dauer + Rendering-Dauer + Download-Dauer
             = 66883 s + 750 s + 6917 s = 74550 s

74550 < 75000, also lohnt es sich in dieser Situation immer noch.