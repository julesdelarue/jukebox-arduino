# jukebox-arduino


## Matériel :

Gotronic:

Module RFID 13,56 MHz TAG RC522
Module RFID 13,56 MHz TAG RC522 	8,25 €	1	9,90 €
Module MP3 DFPlayer
Module MP3 DFPlayer 	6,25 €	1	7,50 €
Interrupteur DS12A
Interrupteur DS12A 	0,83 €	1	1,00 €
Haut-parleur 77 mm LS01-5
Haut-parleur 77 mm LS01-5 	5,67 €	1	6,80 €

Amazon:

Tags NFC : https://www.amazon.fr/dp/B0CM5XHVW3?ref=ppx_yo2ov_dt_b_fed_asin_title
Boutons : https://www.amazon.fr/dp/B09MBQSM44?ref=ppx_yo2ov_dt_b_fed_asin_title
FacadeUsb : https://www.amazon.fr/dp/B09X499JDS?ref=ppx_yo2ov_dt_b_fed_asin_title
PowerBank : https://www.amazon.fr/dp/B09NRG2YT3?ref=ppx_yo2ov_dt_b_fed_asin_title

Déjà à la maison :

Aruino nano pas cher : 

## Schematics

## Dev avec platform.io
Suivre  https://discourse.voss.earth/t/tonuino-software-mit-platformio-aufspielen/13468

-> Ne marche pas sur vscodium sur windows, on utilise VSCode du coup

Pas sur qu'on ait besoin

## Dev avec le classique Arduino IDE

https://www.arduino.cc/en/software/

You need the following libraries for your TonUINO:

    MFRC522 (Githubcommunity)
    DFPlayer Mini Mp3 by Makuna -> version 1.0.7 pour assuer la compilation
    JC-Button

## Carte SD

Formater en FAT32 et bien supprimer les fichiers résiduels (supprimer avec gitbash pour les voir)

Copier coller le contenu de sd-card à la racine

Documentation DFPlayer
https://raw.githubusercontent.com/Arduinolibrary/DFPlayer_Mini_mp3/master/DFPlayer%20Mini%20Manual.pdf

## Code

From : https://github.com/tonuino/TonUINO-TNG

## Fichiers 3D

## Resources et liens 

Source principale : 
https://lab-en-bib.abf.asso.fr/2022/05/17/tonuino-la-boite-a-chansons-diy/
https://www.voss.earth/tonuino/

A regarder plus tard :
https://www.instructables.com/RFID-JukeBox-Using-Arduino-Uno-DFPlayerMini/

Gallerie de réalisation:
https://discourse.voss.earth/t/tonuino-gehaeuse-galerie/786/101

## Ecriture des tags

