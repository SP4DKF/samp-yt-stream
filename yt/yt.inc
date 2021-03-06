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
#define ERR_INCOMPATIBILITY_HASH	1 // Niezgodno�� hashy / Incompatibility hashes
#define ERR_INVALID_LINK			2 // Podany link nie jest linkiem YouTube / The specified link is not a link YouTube
#define ERR_INVALID_CODEC			3 // Wyst�pi� b��d podczas konwersji pliku (nieznany kodek) / An error occurred while converting the file (unknown codec)
#define ERR_LIMIT_EXCEEDED			4 // Podany klip jest za d�ugi / Given clip is too long
#define ERR_UNKNOWN_ERROR			5 // Wyst�pi� nieznany b��d / An unknown error occurred
#define ERR_SERVER_NOTFOUND			6 // Wystapil blad podczas laczenia z serwerem konwersji / An error occurred when connecting to the server conversion


/*
	[ # POLSKA WERSJA # ]
	Funkcja inicjuj�ca plugin mo�na jej u�y� raz w gamemodzie lub skrypcie.
	
	Parametry:
	  ip[] - adres ip lub nazwa domenowa serwera na kt�rym b�dzie plik convert.php (nie mo�na u�ywa� localhost)
	  hash[] - losowy ci�g znak�w do zabezpiecznia skryptu convert.php przed nieautoryzownym u�yciem (ten sam musi by� w pliku convert.php)
	  maxsize[] - maksymalna wielko�� pliku kt�ry zostanie poddany konwersji np. 1024K, 20M, 1G (np. jako zabezpieczenie przed filmikami 10 godzin)
	
	Zwracanie:
	  0 - funkcja nie wykona�a si� poprawnie
	  1 - funkcja wykona�a si� poprawnie
	  
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
	Funkcja odtwarzaj�ca dla danego gracza stream z podanego linku.
	
	Parametry:
	  playerid - id gracza kt�remu stream ma si� odtworzy�
	  link[] - pe�ny link do klipu z serwisu youtube.com
	
	Zwracanie:
	  0 - funkcja nie wykona�a si� poprawnie
	  1 - funkcja wykona�a si� poprawnie
	  
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
	  playerid - id gracza kt�remu stream ma si� zatrzyma�
	
	Zwracanie:
	  Funkcja nie zwraca specyficznej warto�ci
	  
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
	Ta funkcja odtwarza stream dla wszystkich graczy lub dla graczy na danej pozycji lub �wiecie ew. wn�trzu
	
	Parametry:
	  link[] - pe�ny link do klipu z serwisu youtube.com
	  Float:posx - pozycja X w kt�rej ma by� s�ycha� muzyk� (opcjonalnie)
	  Float:posy - pozycja Y w kt�rej ma by� s�ycha� muzyk� (opcjonalnie)
	  Float:posz - pozycja Z w kt�rej ma by� s�ycha� muzyk� (opcjonalnie)
	  Float:radius - promie� od ustalonej pozycji w kt�rym ma by� s�ycha� muzyk� (opcjonalnie)
	  vw - wirtualny �wiat w kt�rym ma by� s�ycha� muzyk� (opcjonalnie, warto�� -1 dla wszystkich �wiat�w)
	  interior - interior �wiat w kt�rym ma by� s�ycha� muzyk� (opcjonalnie, warto�� -1 dla wszystkich interior�w)
	
	Zwracanie:
	  0 - funkcja nie wykona�a si� poprawnie
	  1 - funkcja wykona�a si� poprawnie
	  
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
	Ta funkcja publiczna wywo�uje si� gdy plik zostanie przetworzony przez plugin
	
	Parametry:
	  playerid - w przypadku u�ycia funkcji yt_play(...) zwraca id gracza w przypadku u�ycia yt_play_all(...) zwraca warto�� INVALID_PLAYER_ID
	  response - zwraca odpowied� serwera (patrz linie 13-19 tego pliku)
	
	Zwracanie:
	  0 - funkcja nie wykona�a si� poprawnie
	  1 - funkcja wykona�a si� poprawnie
	  
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