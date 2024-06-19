# UPOTREBA UGRAĐENOG SUSTAVA ZA PRIPREMU NAPITAKA


# Opis projekta
Ovaj projekt je reultat rada na predmetu Razvoj ugradbenih sustava na Tehničko veleučilište u Zagrebu.

Cilj ovog projekta je projektiranje i izrada sustava za miješanje napitaka koja se upravlja preko mobilne aplikacije pomoću bluetooth modula za bežićno komuniciranje sa mobitelom.

# Funkcijski zahtjevi
uređaj nudi uparivanje prilikom paljenja
uređaj ima prekidal za paljenje
rgb dioda za 3 faze rada sustava
# Opis sustava 
Sustav za pripremu napitaka je uređaj koji na zanimljiv i interaktivan način priprema razne napitke za svaku osobu koja poželi napitak. Upravo zbog toga njegova glavna funkcija je da pomogne osobama, a ponajprije organizatorima zabava. Zašto njima? Glavni razlog tome je da na zabavama domaćin ne stigne sve nadgledati kada je zaokupljen točenjem napitaka, a to je uvijek glavni razlog prolivenog napitka i kasnije čišćenja istog. Još jedan razlog tome je da mala djeca ne bi trebala sama sebi točiti pića, a odrasla osoba ne stigne svakome natočiti piće, a uz sve to  i paziti na ostalu djecu. Zbog toga bi sustav za pripremu napitaka bio koristan jer bi to domaćine riješilo glavnih problema opisanih iznad. Sustav bi na jedan pritisak gumba točio od jednostavnih pa sve do kompleksnih napitaka bez prolivene kapi, a sam domaćin bi se mogao koncentrirati na bitnije stvari. 
# Specifikacija vanjskog okruženja 
saustav funkcionira na vjetru i vlagi, ali nije vodootporan
# Specifikacije ulaza i izlaza sustava
#* Ulazi sustava -> mobilna aplikacija
#** Visoka razina opisa
#*** Sustav mora očitati parametre koje je dobio prilikom pritiska gumba u apliakciji
#** Detaljnije specifikacije svakog dijela
#*** komunikacijska veza ostvarena je pomoću bluetootha te hc-05 koristi serijsku komunikaciju između arduina i aplikacije
#* Izlazi sustava -> membranske pumpe, koračni motori
#** Visoka razina opisa izlaza sustava
#*** Sustav mora upravljati brzinom motora kao i vremenom paljenja membranskih pumpi
# Korisničko sučelje 
#* Aplikacija sama po sebi je jednostavna, na početnom zaslonu se pritišće gumb za uspostavljanje konekcije, te nakon toga se pojavi ekran gdje su svi napitci te se samo odabere željeni napitak
# Funkcionalna specifikacija sustava 
#* Funkcionalni opis onoga što sustav treba obaviti interno
#* Sustav mora miješati napitke po odabiru korisnika
#* Sustav također mora stati na svakom mjestu gdje se toči napitak
[comment]# Detaljnije specifikacije svake unutarnje funkcije
#* Vrijeme pretakanja izračunato je preko vrmena istiska pumpe i količine tekučine u drugoj postudi
[/comment]
# Specifikacije radnih značajki 
#* Opis radnih karakteristika sustava, kao što je potreban redoslijed u kojem se moraju provesti interne operacije.

sustav najprije vrača platformu na početnu poziciju
nakon toga koračni motor kreče pokretati platformu prema prvoj lokaciji gdje treba stati te kada stane pokrene druge koračne motore za istis tekućine iz dozatora ili pokretat pumpu koja vadi iz jednos spremnika tekućinu te ju prelijeva u čašu.

# Tehnologije
Arduino IDE
CURA slicer
FUSION 360
MIT APP INVENTRO

# Članovi tima
Nikola Platnjak