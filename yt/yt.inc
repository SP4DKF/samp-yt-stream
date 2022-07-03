/*	
	---------------------------------------------------------
	-           Odtwarzacz & Streamer YouTube 0.1           -
	-      Data kompilacji: 07.01.2017 by Rimmer (Dusik)    -
	---------------------------------------------------------
	
	----------------------------------------------------------
	- 			   YouTube Player & Streamer 0.1             -
	-    Compilation data: 07/01/2017 by Rimmer (Dusik)      -
	----------------------------------------------------------
*/

#define CONVERSION_SUCCESSFUL		0 // Wszystko OK / Everything OK
#define ERR_INCOMPATIBILITY_HASH	1 // Niezgodnoœæ hashy / Incompatibility hashes
#define ERR_INVALID_LINK			2 // Podany link nie jest linkiem YouTube / The specified link is not a link YouTube
#define ERR_INVALID_CODEC			3 // Wyst¹pi³ b³¹d podczas konwersji pliku (nieznany kodek) / An error occurred while converting the file (unknown codec)
#define ERR_LIMIT_EXCEEDED			4 // Podany klip jest za d³ugi / Given clip is too long
#define ERR_UNKNOWN_ERROR			5 // Wyst¹pi³ nieznany b³¹d / An unknown error occurred
#define ERR_SERVER_NOTFOUND			6 // Wystapil blad podczas laczenia z serwerem konwersji / An error occurred when connecting to the server conversion


/*
	[ # POLSKA WERSJA # ]
	Funkcja inicjuj¹ca plugin mo¿na jej u¿yæ raz w gamemodzie lub skrypcie.
	
	Parametry:
	  ip[] - adres ip lub nazwa domenowa serwera na którym bêdzie plik convert.php (nie mo¿na u¿ywaæ localhost)
	  hash[] - losowy ci¹g znaków do zabezpiecznia skryptu convert.php przed nieautoryzownym u¿yciem (ten sam musi byæ w pliku convert.php)
	  maxsize[] - maksymalna wielkoœæ pliku który zostanie poddany konwersji np. 1024K, 20M, 1G (np. jako zabezpieczenie przed filmikami 10 godzin)
	
	Zwracanie:
	  0 - funkcja nie wykona³a siê poprawnie
	  1 - funkcja wykona³a siê poprawnie
	  
	-------------------------------------------------------- 
	  
	[ # ENGLISH VERSION # ]
	The initialization function plugin you can use it once a gamemode or script.

	Parameters:
	  ip[] - ip address or domain name of the server on which the file will be convert.php (you can not use localhost)
	  hash[] - a random string of characters to Safeguarding script convert.php nieautoryzownym before using (the same must be in the file convert.php)
	  maxsize[] - the maximum file size that will be subjected to such conversion. 1024k, 20M, 1G (eg. as collateral against the cinematics 10 hours)

	Returning:
	  0 - function is not performed correctly
	  1 - function performed correctly
*/
native yt_init(const ip[], const hash[], const maxsize[]);


/*
	[ # POLSKA WERSJA # ]
	Funkcja odtwarzaj¹ca dla danego gracza stream z podanego linku.
	
	Parametry:
	  playerid - id gracza któremu stream ma siê odtworzyæ
	  link[] - pe³ny link do klipu z serwisu youtube.com
	
	Zwracanie:
	  0 - funkcja nie wykona³a siê poprawnie
	  1 - funkcja wykona³a siê poprawnie
	  
	-------------------------------------------------------- 
	  
	[ # ENGLISH VERSION # ]
	This function plays the stream for the player from the given link.

	Parameters:
	  playerid - id player who has to play stream
	  link[] - full link to a clip of the service youtube.com

	Returning:
	  0 - function is not performed correctly
	  1 - function performed correctly
*/
native yt_play(playerid, const link[]);


/*
	[ # POLSKA WERSJA # ]
	Ta funkcja zatrzymuje odtwarzane klipu.
	
	Parametry:
	  playerid - id gracza któremu stream ma siê zatrzymaæ
	
	Zwracanie:
	  Funkcja nie zwraca specyficznej wartoœci
	  
	-------------------------------------------------------- 
	  
	[ # ENGLISH VERSION # ]
	This function stops the playback of the clip.

	Parameters:
	  playerid - id stream player who has to stop

	Returning:
	  The function does not return a specific value
*/
native yt_stop(playerid);


/*
	[ # POLSKA WERSJA # ]
	Ta funkcja odtwarza stream dla wszystkich graczy lub dla graczy na danej pozycji lub œwiecie ew. wnêtrzu
	
	Parametry:
	  link[] - pe³ny link do klipu z serwisu youtube.com
	  Float:posx - pozycja X w której ma byæ s³ychaæ muzykê (opcjonalnie)
	  Float:posy - pozycja Y w której ma byæ s³ychaæ muzykê (opcjonalnie)
	  Float:posz - pozycja Z w której ma byæ s³ychaæ muzykê (opcjonalnie)
	  Float:radius - promieñ od ustalonej pozycji w którym ma byæ s³ychaæ muzykê (opcjonalnie)
	  vw - wirtualny œwiat w którym ma byæ s³ychaæ muzykê (opcjonalnie, wartoœæ -1 dla wszystkich œwiatów)
	  interior - interior œwiat w którym ma byæ s³ychaæ muzykê (opcjonalnie, wartoœæ -1 dla wszystkich interiorów)
	
	Zwracanie:
	  0 - funkcja nie wykona³a siê poprawnie
	  1 - funkcja wykona³a siê poprawnie
	  
	-------------------------------------------------------- 
	  
	[ # ENGLISH VERSION # ]
	This function plays the stream for all players or for players at a given position, or possibly the world, interior

	Parameters:
	  link[] - full link to a clip from the site youtube.com
	  Float:posx - X position where to hear music (optional)
	  Float:posy - Y position where to hear music (optional)
	  Float:posz - Z position where to hear music (optional)
	  Float:radius - radius from a fixed position where to hear music (optional)
	  vw - a virtual world in which to hear music (optional, -1 for all the worlds)
	  interior - interior world in which to hear music (optional, -1 for all interiors)

	Returning:
	  0 - function is not performed correctly
	  1 - function performed correctly
*/
native yt_play_all(const link[], Float:posx = 0.0, Float:posy = 0.0, Float:posz = 0.0, Float:radius = 0.0, vw = -1, interior = -1);


/*
	[ # POLSKA WERSJA # ]
	Ta funkcja publiczna wywo³uje siê gdy plik zostanie przetworzony przez plugin
	
	Parametry:
	  playerid - w przypadku u¿ycia funkcji yt_play(...) zwraca id gracza w przypadku u¿ycia yt_play_all(...) zwraca wartoœæ INVALID_PLAYER_ID
	  response - zwraca odpowiedŸ serwera (patrz linie 13-19 tego pliku)
	
	Zwracanie:
	  0 - funkcja nie wykona³a siê poprawnie
	  1 - funkcja wykona³a siê poprawnie
	  
	--------------------------------------------------------
	
	[ # ENGLISH VERSION # ]
	This callback is executed when the file is processed by the plugin

	Parameters:
	  playerid - when you use yt_play(...) returns the id of the player when using yt_play_all(...) returns INVALID_PLAYER_ID
	  response - returns the server response (for more see lines 13-19 of the file)

	Returning:
	  0 - function is not performed correctly
	  1 - function performed correctly
*/
forward OnYouTubeResponse(playerid, response);